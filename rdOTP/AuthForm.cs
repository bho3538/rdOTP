using OtpNet;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace rdOTP
{
    public partial class AuthForm : Form
    {
        private System.Windows.Forms.Timer _timer = null;
        private int retryCnt = 0;
        private bool valid = false;
        private bool firstFocused = false;

        private KeySettings _settings = new KeySettings();
        private string _otpKey = "";
        private int _seconds = 30;

        public AuthForm()
        {
            InitializeComponent();

            _otpKey = _settings.GetGlobalSecretKey();

            wrong_msg.Visible = false;
            if (string.IsNullOrEmpty(_otpKey))
            {
                wrong_msg.Text = "OTP not configured. Click 'submit' and setting it first!";
                wrong_msg.Visible = true;
            }

            _timer = new System.Windows.Forms.Timer();
            _timer.Tick += _timer_Tick;
            _timer.Interval = 1000;
            _timer.Start();
        }

        private void _timer_Tick(object sender, EventArgs e)
        {
            //update machine time label
            DateTime dt = DateTime.Now;
            this.time_value_label.Text = dt.ToString("yyyy-mm-dd HH:mm:ss");

            _seconds -= 1;
            this.leftTime_label.Text = string.Format("Dialog will be closed in {0} seconds.", _seconds);

            if(_seconds == 0)
            {
                //prevent LogonUI.exe HANG
                this.Close();
            }

            if (!firstFocused)
            {
                firstFocused = true;
                this.Activate();
            }
        }

        protected override void OnClosed(EventArgs e)
        {
            _timer.Stop();
            _timer.Tick -= _timer_Tick;

            base.OnClosed(e);
        }

        public bool ShowAndValidateCode()
        {
            this.ShowDialog();

            return this.valid;
        }

        private void submit_btn_Click(object sender, EventArgs e)
        {
            string code = this.code_input.Text;

            if (string.IsNullOrEmpty(_otpKey))
            {
                valid = true;
                this.Close();
                return;
            }

            var totp = new Totp(Base32Encoding.ToBytes(_otpKey), 30, OtpHashMode.Sha1, 6);

            long matched = 0;
            if(totp.VerifyTotp(code.Trim(), out matched, VerificationWindow.RfcSpecifiedNetworkDelay))
            {
                valid = true;
                this.Close();
            }
            else
            {
                this.code_input.Text = "";
                this.wrong_msg.Visible = true;
                valid = false;
                retryCnt++;

                if (retryCnt >= 3)
                {
                    this.Close();
                }

            }

        }
    }
}
