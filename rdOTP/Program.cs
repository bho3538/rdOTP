using rdOTP.Locale;
using rdOTP.UI;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace rdOTP
{
    internal static class Program
    {
        /// <summary>
        /// 해당 애플리케이션의 주 진입점입니다.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            if (Environment.OSVersion.Version.Major < 6 || (Environment.OSVersion.Version.Major == 6 && Environment.OSVersion.Version.Minor <= 1))
            {
                MessageBox.Show(Resource.Error_osrequired, "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            if (!CheckModuleExists())
            {
                return;
            }

            Application.Run(new Settings());
        }

        private static List<string> _moduleNames = new List<string>() { "rdOTPCred.dll", "rdOTPAuth.dll" };

        private static bool CheckModuleExists()
        {
            bool pass = true;
            string installedPath = Assembly.GetExecutingAssembly().Location;
            installedPath = Path.GetDirectoryName(installedPath);

            foreach (var moduleName in _moduleNames)
            {
                string fullPath = Path.Combine(installedPath, moduleName);

                if (!File.Exists(fullPath))
                {
                    MessageBox.Show(string.Format(Resource.Error_moduleNotFound, moduleName), "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    pass = false;
                    break;
                }
            }

            return pass;
        }

        private static bool CheckVCRuntime()
        {
            IntPtr hModule = LoadLibrary("rdOTPWrap.dll");

            if (hModule == IntPtr.Zero)
            {
                return false;
            }

            FreeLibrary(hModule);
            return true;
        }


        [DllImport("kernel32.dll")]
        private static extern IntPtr LoadLibrary(string dllToLoad);

        [DllImport("kernel32.dll")]
        private static extern int FreeLibrary(IntPtr hModule);
    }
}
