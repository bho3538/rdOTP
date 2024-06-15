using OtpNet;
using rdOTP.Locale;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.InteropServices;
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

        private const string TIME_FORMAT = "yyyy-mm-dd HH:mm:ss";

        public AuthForm()
        {
            InitializeComponent();
            SetLayout();

            this.code_input.MaxLength = 16;
            this.code_input.TextChanged += Code_input_TextChanged;
            this.time_value_label.Text = DateTime.Now.ToString(TIME_FORMAT);

            _otpKey = _settings.GetGlobalSecretKey();

            wrong_msg.Visible = false;
            if (string.IsNullOrEmpty(_otpKey))
            {
                this.code_input.Enabled = false;
                wrong_msg.Text = Resource.Auth_NotConfigured;
                wrong_msg.Visible = true;
            }

            _timer = new System.Windows.Forms.Timer();
            _timer.Tick += _timer_Tick;
            _timer.Interval = 1000;
            _timer.Start();
        }

        private void Code_input_TextChanged(object sender, EventArgs e)
        {
            if(this.code_input.TextLength > 0)
            {
                wrong_msg.Visible = false;
            }
        }

        private void SetLayout()
        {
            bool bHack = false;
            float dpiX = 0;
            Graphics graphics = this.CreateGraphics();
            dpiX = graphics.DpiX;
            graphics.Dispose();

            float scale = dpiX / 96;

            if(scale == 1)
            {
                int width = System.Windows.Forms.Screen.PrimaryScreen.WorkingArea.Size.Width;
                if (width > 1920)
                {
                    scale = (float)width / 1920;
                    scale += 1;
                    bHack = true;
                }
            }

            if(scale > 1)
            {
                this.Width = (int)(this.Width * scale);
                this.Height = (int)(this.Height * scale);

                int cnt = this.Controls.Count;

                for(int i = 0; i < cnt; i++)
                {
                    Control ctrl = this.Controls[i];

                    ctrl.Width = (int)(ctrl.Width * scale);
                    ctrl.Height = (int)(ctrl.Height * scale);
                    ctrl.Location = new Point((int)(ctrl.Location.X * scale), (int)(ctrl.Location.Y * scale));

                    if(ctrl is Label lb)
                    {
                        float fontSize = lb.Font.Size + scale;
                        if (bHack)
                        {
                            fontSize += 6;
                        }

                        lb.Font = new Font("Arial", fontSize, lb.Font.Style);
                    }
                    else if(ctrl is Button btn)
                    {
                        float fontSize = btn.Font.Size + scale;
                        if (bHack)
                        {
                            fontSize += 6;
                        }

                        btn.Font = new Font("Arial", fontSize, btn.Font.Style);
                    }
                    else if (ctrl is TextBox box)
                    {
                        float fontSize = box.Font.Size + scale;
                        if (bHack)
                        {
                            fontSize += 6;
                        }

                        box.Font = new Font("Arial", fontSize, box.Font.Style);
                    }
                }
            }
        }

        private void _timer_Tick(object sender, EventArgs e)
        {
            //update machine time label
            DateTime dt = DateTime.Now;
            this.time_value_label.Text = dt.ToString(TIME_FORMAT);

            _seconds -= 1;
            this.leftTime_label.Text = string.Format(Resource.Auth_Timeout, _seconds);

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

            if(string.IsNullOrWhiteSpace(code) || code.Length != 6)
            {
                HandleCodeError();
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
                HandleCodeError();
            }

        }

        private void HandleCodeError()
        {
            this.code_input.Text = "";
            this.wrong_msg.Visible = true;
            valid = false;
            retryCnt++;

            Thread.Sleep(700);

            if (retryCnt >= 3)
            {
                Thread.Sleep(2000);
                this.Close();
            }
        }
    }
}
