using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace rdOTPSvc
{
    class Impersonate
    {

        public static bool LockActiveWorkstation()
        {
            IntPtr hUserToken = IntPtr.Zero;
            PROCESS_INFORMATION procInfo = new PROCESS_INFORMATION();
            STARTUPINFO startInfo = new STARTUPINFO();
            startInfo.cb = Marshal.SizeOf(typeof(STARTUPINFO));

            GetSessionUserToken(ref hUserToken);

            if (hUserToken == IntPtr.Zero)
            {
                Trace.WriteLine("Cannot found active user token");
                return false;
            }

            if(CreateProcessAsUserW(hUserToken, @"C:\Users\wizvera\Desktop\test\rdOTPHelper.exe", null, IntPtr.Zero, IntPtr.Zero, false, 0, IntPtr.Zero, null, ref startInfo, ref procInfo))
            {
                CloseHandle(procInfo.hThread);
                CloseHandle(procInfo.hProcess);
            }

            CloseHandle(hUserToken);


            return true;
        }

        private static void GetSessionUserToken(ref IntPtr phUserToken)
        {
            IntPtr hUserToken = IntPtr.Zero;
            uint activeSession = WTSGetActiveConsoleSessionId();

            if (WTSQueryUserToken(activeSession, ref hUserToken) != 0)
            {
                DuplicateTokenEx(hUserToken, 0, IntPtr.Zero, (int)SECURITY_IMPERSONATION_LEVEL.SecurityImpersonation, 1, ref phUserToken); // TOKEN_PRIMARY
                CloseHandle(hUserToken);
            }
        }

        #region marshal

        [DllImport("advapi32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
        private static extern bool CreateProcessAsUserW(
            IntPtr hToken,
            [MarshalAs(UnmanagedType.LPWStr)] string lpApplicationName,
            StringBuilder lpCommandLine,
            IntPtr lpProcessAttributes,
            IntPtr lpThreadAttributes,
            [MarshalAs(UnmanagedType.Bool)] bool bInheritHandle,
            uint dwCreationFlags,
            IntPtr lpEnvironment,
            [MarshalAs(UnmanagedType.LPWStr)] String lpCurrentDirectory,
            ref STARTUPINFO lpStartupInfo,
            ref PROCESS_INFORMATION lpProcessInformation);

        [DllImport("advapi32.dll")]
        private static extern bool DuplicateTokenEx(
            IntPtr ExistingTokenHandle,
            uint dwDesiredAccess,
            IntPtr lpThreadAttributes,
            int TokenType,
            int ImpersonationLevel,
            ref IntPtr DuplicateTokenHandle);

        [DllImport("kernel32.dll")]
        private static extern bool CloseHandle(IntPtr handle);

        [DllImport("kernel32.dll")]
        private static extern uint WTSGetActiveConsoleSessionId();

        [DllImport("Wtsapi32.dll")]
        private static extern uint WTSQueryUserToken(uint SessionId, ref IntPtr phToken);


        [StructLayout(LayoutKind.Sequential)]
        private struct PROCESS_INFORMATION
        {
            public IntPtr hProcess;
            public IntPtr hThread;
            public uint dwProcessId;
            public uint dwThreadId;
        }

        private enum SECURITY_IMPERSONATION_LEVEL
        {
            SecurityAnonymous = 0,
            SecurityIdentification = 1,
            SecurityImpersonation = 2,
            SecurityDelegation = 3,
        }

        [StructLayout(LayoutKind.Sequential)]
        private struct STARTUPINFO
        {
            public int cb;
            public String lpReserved;
            public String lpDesktop;
            public String lpTitle;
            public uint dwX;
            public uint dwY;
            public uint dwXSize;
            public uint dwYSize;
            public uint dwXCountChars;
            public uint dwYCountChars;
            public uint dwFillAttribute;
            public uint dwFlags;
            public short wShowWindow;
            public short cbReserved2;
            public IntPtr lpReserved2;
            public IntPtr hStdInput;
            public IntPtr hStdOutput;
            public IntPtr hStdError;
        }

        #endregion
    }
}
