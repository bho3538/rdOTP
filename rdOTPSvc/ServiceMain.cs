using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Management;
using System.Runtime.InteropServices;
using System.ServiceProcess;
using System.Text;
using System.Threading.Tasks;

namespace rdOTPSvc
{
    public partial class ServiceMain : ServiceBase
    {
        private ManagementEventWatcher _processStartWatch = null;
        private ManagementEventWatcher _processStopWatch = null;
        private object _lock = new object();

        private uint _watchTargetPid = uint.MaxValue;

        public ServiceMain()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            _processStartWatch = new ManagementEventWatcher(new WqlEventQuery("SELECT * FROM Win32_ProcessStartTrace"));
            _processStartWatch.EventArrived += ProcessStarted;
            _processStartWatch.Start();

            _processStopWatch = new ManagementEventWatcher(new WqlEventQuery("SELECT * FROM Win32_ProcessStopTrace"));
            _processStopWatch.EventArrived += ProcessStoped;
            _processStopWatch.Start();
        }

        protected override void OnStop()
        {
            if (_processStartWatch != null)
            {
                _processStartWatch.EventArrived -= ProcessStarted;
                _processStartWatch.Dispose();
                _processStartWatch = null;
            }

            if (_processStopWatch != null)
            {
                _processStopWatch.EventArrived -= ProcessStoped;
                _processStopWatch.Dispose();
                _processStopWatch = null;
            }

            _watchTargetPid = uint.MaxValue;
        }

        private void ProcessStarted(object sender, EventArrivedEventArgs args)
        {
            // 크롬 원격 데스크톱에 사용자가 접속한 경우 실행되는 프로세스를 찾기
            // remoting_desktop.exe (SYSTEM , user workstation session)

            try
            {
                uint sessoinId = (uint)args.NewEvent.Properties["SessionID"].Value;
                if (sessoinId > 0)
                {
                    string processName = (string)args.NewEvent.Properties["ProcessName"].Value;
                    uint pid = (uint)args.NewEvent.Properties["ProcessID"].Value;

                    if (processName.ToLowerInvariant() == "remoting_desktop.exe" && IsChromeRemoteDesktop(pid))
                    {
                        // 이미 크롬 원격 데스크톱이 관리되고 있는 경우
                        if (IsChromeRemoteDesktopWatched())
                        {
                            // 무시
                            return;
                        }

                        SetChromeRemoteDesktopWatch(pid);

                        // 잠금 화면을 갱신해야 함.
                        // 때때로 rdOTPCred 가 아닌 기본 Cred 가 이미 Load 되어 otp 인증을 수행할 수 없기 때문
                        try
                        {
                            string systemLogonUIPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.System), "logonui.exe").ToLower();
                            Process[] logonUIs = Process.GetProcessesByName("logonui");
                            foreach (var logonUI in logonUIs)
                            {
                                if (logonUI.MainModule.FileName.ToLowerInvariant() == systemLogonUIPath)
                                {
                                    logonUI.Kill();
                                }
                            }
                        }
                        catch
                        {
                            // 종료 실패하는 경우에는 무시
                        }


                        // Lock Workstation
                        if (Impersonate.LockActiveWorkstation() == false)
                        {
                            Trace.WriteLine("Failed to execute rdOTPHelper.exe");
                        }
                    }
                }
            }
            catch
            {
                // ignore
            }
            finally
            {
                args.NewEvent.Dispose();
            }
        }

        private void ProcessStoped(object sender, EventArrivedEventArgs args)
        {
            uint pid = uint.MaxValue;

            try
            {
                pid = (uint)args.NewEvent.Properties["ProcessID"].Value;
            }
            catch
            {
                // 어떠한 프로세스가 종료되었는지 확인할 수 없으므로 관리중인 크롬 원격 데스크톱 프로세스 정보를 초기화 후 종료
                SetChromeRemoteDesktopWatch(uint.MaxValue);
                args.NewEvent.Dispose();
                return;
            }


            try
            {
                // 이미 관리중인 크롬 원격 데스크톱이 종료된 경우
                if (IsWatchedChromeRemoteDesktop(pid))
                {
                    // 실행중인 크롬 원격 데스크톱 연결이 종료됨
                    // 화면을 다시 lock
                    SetChromeRemoteDesktopWatch(uint.MaxValue);

                    // Lock Workstation
                    if (Impersonate.LockActiveWorkstation() == false)
                    {
                        Trace.WriteLine("Failed to execute rdOTPHelper.exe");
                    }
                }
            }
            catch
            {
                
            }
            finally
            {
                args.NewEvent.Dispose();
            }
        }

        private bool IsChromeRemoteDesktopWatched()
        {
            lock (_lock)
            {
                return _watchTargetPid != uint.MaxValue;
            }
        }

        private bool IsWatchedChromeRemoteDesktop(uint pid)
        {
            lock (_lock)
            {
                return _watchTargetPid == pid;
            }
        }

        private void SetChromeRemoteDesktopWatch(uint pid)
        {
            lock (_lock)
            {
                _watchTargetPid = pid;
            }
        }

        private bool IsChromeRemoteDesktop(uint pid)
        {
            bool re = false;
            const uint PROCESS_QUERY_LIMITED_INFORMATION = 0x1000;

            IntPtr hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, pid);
            if (hProcess != IntPtr.Zero)
            {
                StringBuilder exePath = new StringBuilder(1024);
                int len = exePath.Capacity;

                if (QueryFullProcessImageName(hProcess, 0, exePath, ref len))
                {
                    try
                    {
                        FileVersionInfo verInfo = FileVersionInfo.GetVersionInfo(exePath.ToString());
                        if (verInfo.CompanyName == "Google LLC")
                        {
                            re = true;
                        }
                    }
                    catch (FileNotFoundException)
                    {
                        // ignore
                    }

                }

                CloseHandle(hProcess);
            }

            return re;
        }

        #region marshal

        [DllImport("kernel32.dll")]
        private static extern IntPtr OpenProcess(uint dwDesiredAccess, [MarshalAs(UnmanagedType.Bool)] bool bInheritHandle, uint dwProcessId);

        [DllImport("kernel32.dll")]
        private static extern bool CloseHandle(IntPtr hHandle);

        [DllImport("kernel32.dll")]
        private static extern bool QueryFullProcessImageName(IntPtr hProcess, int dwFlags, StringBuilder lpExeName, ref int size);


        #endregion
    }
}
