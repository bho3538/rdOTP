using Microsoft.Win32;
using OtpNet;
using QRCoder;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace rdOTP
{
    public partial class KeySettings : Form
    {
        public KeySettings()
        {
            InitializeComponent();
            this.secrent_key_value.Text = GetGlobalSecretKey();
        }

        private void SetQRCode()
        {
            string displayName = this.displayname_input.Text;
            if (string.IsNullOrEmpty(displayName))
            {
                displayName = "MY COMPUTER";
            }

            string url = new OtpUri(OtpType.Totp, this.secrent_key_value.Text, "RDOTP", displayName).ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(url, QRCodeGenerator.ECCLevel.Q);

            QRCode qrCode = new QRCode(qrCodeData);
            Bitmap bm = qrCode.GetGraphic(20);
            this.qrcode.SizeMode = PictureBoxSizeMode.StretchImage;

            if (this.qrcode.Image != null)
            {
                this.qrcode.Image.Dispose();
            }
            this.qrcode.Image = bm;
        }

        public string GetGlobalSecretKey()
        {
            return GetStringValueFromReg(Registry.LocalMachine, "SOFTWARE\\RDOTP", "GlobalSecretKey");
        }

       
        private void secret_generate_btn_Click(object sender, EventArgs e)
        {
            var op = MessageBox.Show("If you change secret key, You need change all OTP information at your phone.\nContinue?", "RDOTP", MessageBoxButtons.YesNo);
            if(op != DialogResult.Yes)
            {
                return;
            }

            var key = KeyGeneration.GenerateRandomKey(20);
            if(key == null)
            {
                return;
            }
            var base32String = Base32Encoding.ToString(key);

            SetStringValueFromReg(Registry.LocalMachine, "SOFTWARE\\RDOTP", "GlobalSecretKey", base32String);

            this.secrent_key_value.Text = base32String;

            if(this.qrcode.Image != null)
            {
                this.qrcode.Image.Dispose();
            }
            this.qrcode.Image = null;

            MessageBox.Show("Key generation complete!.\nPlease run 'OTP Test' before lock remote session");
        }

        private string GetStringValueFromReg(RegistryKey hive, string key, string name)
        {
            string val = string.Empty;

            try
            {
                var reg = hive.OpenSubKey(key);
                if (reg == null)
                {
                    return val;
                }

                object obj = reg.GetValue(name, "", RegistryValueOptions.None);
                if (obj is string str)
                {
                    val = str;
                }
            }
            catch
            {
            }

            return val;
        }

        private string SetStringValueFromReg(RegistryKey hive, string key, string name, string val)
        {
            try
            {
                var reg = hive.OpenSubKey(key, true);
                if (reg == null)
                {
                    reg = hive.CreateSubKey(key, true);
                }

                reg.SetValue(name, val, RegistryValueKind.String);
            }
            catch (UnauthorizedAccessException e)
            {
                MessageBox.Show("Please launch program with Admin rights", "Access Denied");
            }
            catch
            {

            }

            return val;
        }

        private void qr_show_btn_Click(object sender, EventArgs e)
        {
            SetQRCode();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            AuthForm form = new AuthForm();
            if (form.ShowAndValidateCode())
            {
                MessageBox.Show("Test success!", "RDOTP");
            }
            else
            {
                MessageBox.Show("Test Failed!\nTry again or re-register QR Code at your phone", "RDOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
