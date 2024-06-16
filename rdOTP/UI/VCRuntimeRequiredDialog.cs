using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace rdOTP.UI
{
    public partial class VCRuntimeRequiredDialog : Form
    {
        public VCRuntimeRequiredDialog()
        {
            InitializeComponent();
        }

        private void link_label_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            string url = string.Empty;

            if (!Environment.Is64BitOperatingSystem)
            {
                // x86 system
                url = "https://aka.ms/vs/17/release/vc_redist.x86.exe";
            }
            else
            {
                // x64 + ARM64
                url = "https://aka.ms/vs/17/release/vc_redist.x64.exe";
            }

            // open web browser and download it.
            Process.Start(url);
        }

        private void close_btn_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
