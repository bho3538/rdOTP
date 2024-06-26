using rdOTP.Locale;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.ServiceProcess;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace rdOTP.UI
{
    public partial class AdvancedSettings : Form
    {
        private const string SERVICE_NAME = "rdOTPSvc";
        private const string SERVICE_FILE_NAME = "rdOTPSvc.exe";
        private const string EXT_NAME = "rdOTPExt.exe";

        public AdvancedSettings()
        {
            InitializeComponent();

            SetServiceStatusUI();
        }

        private void SetServiceStatusUI()
        {
            bool serviceInstalled = IsServiceInstalled();
            bool serviceRunning = IsServiceRunning();

            this.install_btn.Enabled = !serviceInstalled;
            this.uninstall_btn.Enabled = serviceInstalled && !serviceRunning;
            this.start_btn.Enabled = serviceInstalled && !serviceRunning;
            this.stop_btn.Enabled = serviceInstalled && serviceRunning;

            this.service_install_status.Text = serviceInstalled ? Resource.Service_Installed : Resource.Service_NotInstalled;
            this.service_running_status.Text = serviceRunning ? Resource.Service_runnning : Resource.Service_Notrunning;

            this.chrome_rd_enable_chk.CheckedChanged += Chrome_rd_enable_chk_CheckedChanged;
        }

        private void Chrome_rd_enable_chk_CheckedChanged(object sender, EventArgs e)
        {
            this.chrome_rd_enable_chk.Checked = false;
        }

        private void lock_btn_Click(object sender, EventArgs e)
        {
            try
            {
                string path = GetFilePath(EXT_NAME);
                Process.Start(path);
            }
            catch
            {

            }
        }

        private void install_btn_Click(object sender, EventArgs e)
        {
            try
            {
                InstallService();
                SetServiceStatusUI();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"{"Failed to install service"}\n{ex.Message}", "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void uninstall_btn_Click(object sender, EventArgs e)
        {
            try
            {
                UninstallService();
                SetServiceStatusUI();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"{"Failed to uninstall service"}\n{ex.Message}", "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void start_btn_Click(object sender, EventArgs e)
        {
            try
            {
                StartService();
                SetServiceStatusUI();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"{"Failed to start service"}\n{ex.Message}", "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void stop_btn_Click(object sender, EventArgs e)
        {
            try
            {
                StopService();
                SetServiceStatusUI();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"{"Failed to stop service"}\n{ex.Message}", "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private bool IsServiceInstalled()
        {
            return GetRDOTPService() != null ? true : false;
        }

        private bool IsServiceRunning()
        {
            var service = GetRDOTPService();

            if (service != null)
            {
                if (service.Status == ServiceControllerStatus.Stopped)
                {
                    return false;
                }
                
                for (int i = 0; i < 50; i++)
                {
                    if (service.Status == ServiceControllerStatus.Running)
                    {
                        return true;
                    }

                    // check pending
                    Thread.Sleep(200);
                    service.Refresh();
                }
            }

            return false;
        }

        private void InstallService()
        {
            string serviceBinPath = GetFilePath(SERVICE_FILE_NAME);
            if (!File.Exists(serviceBinPath))
            {
                throw new Exception($"Service file not found. ({serviceBinPath})");
            }

            IntPtr scm = OpenSCManagerW(null, null, ScmAccessRights.AllAccess);
            if (scm != IntPtr.Zero)
            {
                IntPtr service = CreateService(scm, SERVICE_NAME, SERVICE_NAME, ServiceAccessRights.AllAccess, SERVICE_WIN32_OWN_PROCESS, ServiceBootFlag.AutoStart, ServiceError.Normal, serviceBinPath, null, IntPtr.Zero, null, null, null);

                if (service != IntPtr.Zero)
                {
                    CloseServiceHandle(service);
                }

                CloseServiceHandle(scm);
            }
        }

        private void UninstallService()
        {
            IntPtr scm = OpenSCManagerW(null, null, ScmAccessRights.AllAccess);
            if (scm != IntPtr.Zero)
            {
                IntPtr service = OpenService(scm, SERVICE_NAME, ServiceAccessRights.AllAccess);
                if (service != IntPtr.Zero)
                {
                    DeleteService(service);
                    CloseServiceHandle(service);
                }

                CloseServiceHandle(scm);
            }
        }

        private void StartService()
        {
            var service = GetRDOTPService();
            if (service != null)
            {
                service.Start();
            }
        }

        private void StopService()
        {
            var service = GetRDOTPService();
            if (service != null)
            {
                service.Stop();
            }
        }

        private ServiceController GetRDOTPService()
        {
            var services = ServiceController.GetServices();

            foreach (var service in services)
            {
                if (service.ServiceName == SERVICE_NAME)
                {
                    return service;
                }
            }

            return null;
        }

        private string GetFilePath(string filename)
        {
            try
            {
                string path = Process.GetCurrentProcess().MainModule.FileName;
                path = Path.GetDirectoryName(path);
                path = Path.Combine(path, filename);

                return path;
            }
            catch
            {
                return string.Empty;
            }
        }

        #region marshal
        private const int SERVICE_WIN32_OWN_PROCESS = 0x00000010;

        [DllImport("advapi32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        private static extern IntPtr OpenSCManagerW([MarshalAs(UnmanagedType.LPWStr)] string machineName, [MarshalAs(UnmanagedType.LPWStr)] string databaseName, ScmAccessRights dwDesiredAccess);

        [DllImport("advapi32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern IntPtr OpenService(IntPtr hSCManager, [MarshalAs(UnmanagedType.LPWStr)] string lpServiceName, ServiceAccessRights dwDesiredAccess);

        [DllImport("advapi32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern IntPtr CreateService(IntPtr hSCManager, [MarshalAs(UnmanagedType.LPWStr)] string lpServiceName, [MarshalAs(UnmanagedType.LPWStr)] string lpDisplayName, ServiceAccessRights dwDesiredAccess, int dwServiceType, ServiceBootFlag dwStartType, ServiceError dwErrorControl,
            [MarshalAs(UnmanagedType.LPWStr)] string lpBinaryPathName, [MarshalAs(UnmanagedType.LPWStr)] string lpLoadOrderGroup, IntPtr lpdwTagId, [MarshalAs(UnmanagedType.LPWStr)] string lpDependencies, [MarshalAs(UnmanagedType.LPWStr)] string lp, [MarshalAs(UnmanagedType.LPWStr)] string lpPassword);

        [DllImport("advapi32.dll", SetLastError = true)]
        private static extern bool DeleteService(IntPtr hService);

        [DllImport("advapi32.dll", SetLastError = true)]
        private static extern bool CloseServiceHandle(IntPtr hSCObject);

        [Flags]
        private enum ServiceAccessRights
        {
            QueryConfig = 0x1,
            ChangeConfig = 0x2,
            QueryStatus = 0x4,
            EnumerateDependants = 0x8,
            Start = 0x10,
            Stop = 0x20,
            PauseContinue = 0x40,
            Interrogate = 0x80,
            UserDefinedControl = 0x100,
            Delete = 0x00010000,
            StandardRightsRequired = 0xF0000,
            AllAccess = (StandardRightsRequired | QueryConfig | ChangeConfig |
             QueryStatus | EnumerateDependants | Start | Stop | PauseContinue |
             Interrogate | UserDefinedControl)
        }

        [Flags]
        private enum ScmAccessRights
        {
            Connect = 0x0001,
            CreateService = 0x0002,
            EnumerateService = 0x0004,
            Lock = 0x0008,
            QueryLockStatus = 0x0010,
            ModifyBootConfig = 0x0020,
            StandardRightsRequired = 0xF0000,
            AllAccess = (StandardRightsRequired | Connect | CreateService |
             EnumerateService | Lock | QueryLockStatus | ModifyBootConfig)
        }

        private enum ServiceBootFlag
        {
            Start = 0x00000000,
            SystemStart = 0x00000001,
            AutoStart = 0x00000002,
            DemandStart = 0x00000003,
            Disabled = 0x00000004
        }

        private enum ServiceError
        {
            Ignore = 0x00000000,
            Normal = 0x00000001,
            Severe = 0x00000002,
            Critical = 0x00000003
        }

        #endregion
    }
}
