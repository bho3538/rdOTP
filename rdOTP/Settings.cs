using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace rdOTP
{
    public partial class Settings : Form
    {
        public Settings()
        {
            InitializeComponent();

            CheckInstallStatus();
        }

        private void secret_config_btn_Click(object sender, EventArgs e)
        {
            KeySettings settings = new KeySettings();
            settings.ShowDialog();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start("https://github.com/bho3538/rdOTP");
        }

        private void intstall_btn_Click(object sender, EventArgs e)
        {
            IntPtr hModule = LoadLibrary("rdOTPWrap.dll");
            if (hModule == IntPtr.Zero)
            {
                MessageBox.Show("Failed to load rdOTPWrap.dll\nPlease install 'Visual C++ Redistributable 2022' or re-install this program", "RDOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            FreeLibrary(hModule);

            Process.Start("regsvr32.exe", "rdOTPCred.dll").WaitForExit();
            CheckInstallStatus();
        }

        private void uninstall_btn_Click(object sender, EventArgs e)
        {
            Process.Start("regsvr32.exe", "/u rdOTPCred.dll").WaitForExit();
            CheckInstallStatus();
        }

        private void iconInfo_link_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start("https://icons8.com/icon/EHyUO6ZGSRkX/lock");
        }

        private void CheckInstallStatus()
        {
            this.status_value_label.Text = "Not Installed";

            IntPtr hModule = LoadLibrary("rdOTPCred.dll");
            if (hModule == IntPtr.Zero)
            {
                MessageBox.Show("Failed to load rdOTPCred.dll\nPlease re-install this program", "RDOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            FreeLibrary(hModule);

            hModule = LoadLibrary("rdOTPWrap.dll");
            if(hModule == IntPtr.Zero)
            {
                MessageBox.Show("Failed to load rdOTPWrap.dll\nPlease install 'Visual C++ Redistributable 2022' or re-install this program", "RDOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            FreeLibrary(hModule);

            //check registry

            try
            {
                RegistryKey key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows\CurrentVersion\Authentication\Credential Providers\{0C34E73F-B241-48F3-8C7C-C5C7698BF717}");
                if(key != null)
                {
                    this.status_value_label.Text = "Installed";
                    key.Close();
                }
            }
            catch
            {

            }
        }

        [DllImport("kernel32.dll")]
        private static extern IntPtr LoadLibrary(string dllToLoad);

        [DllImport("kernel32.dll")]
        private static extern int FreeLibrary(IntPtr hModule);
    }
}
