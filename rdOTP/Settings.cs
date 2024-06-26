using Microsoft.Win32;
using rdOTP.Locale;
using rdOTP.UI;
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

            this.Version_label.Text = $"{Resource.Main_Version} : { Application.ProductVersion}";

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
            this.status_value_label.Text = Resource.Main_NotInstalled;
            this.status_value_label.ForeColor = Color.Red;

            //check registry
            try
            {
                RegistryKey key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows\CurrentVersion\Authentication\Credential Providers\{0C34E73F-B241-48F3-8C7C-C5C7698BF717}");
                if(key != null)
                {
                    this.status_value_label.Text = Resource.Main_Installed;
                    this.status_value_label.ForeColor = Color.Green;
                    key.Close();
                }
            }
            catch
            {
                // not installed
            }
        }

        private void additional_config_btn_Click(object sender, EventArgs e)
        {
            AdvancedSettings settings = new AdvancedSettings();
            settings.ShowDialog();
        }
    }
}
