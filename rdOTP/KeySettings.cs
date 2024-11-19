using Microsoft.Win32;
using OtpNet;
using QRCoder;
using rdOTP.Locale;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SaveFileDialog = System.Windows.Forms.SaveFileDialog;

namespace rdOTP
{
    public partial class KeySettings : Form
    {
        public KeySettings()
        {
            InitializeComponent();
            this.secrent_key_value.Text = GetGlobalSecretKey();
            this.displayname_input.MaxLength = 32;
        }

        private void SetQRCode()
        {
            EraseQRCode();

            string displayName = this.displayname_input.Text;
            if (string.IsNullOrEmpty(displayName))
            {
                displayName = "MY COMPUTER";
            }

            string key = this.secrent_key_value.Text;
            if (string.IsNullOrEmpty(key))
            {
                return;
            }

            string url = new OtpUri(OtpType.Totp, key, "RDOTP", displayName).ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(url, QRCodeGenerator.ECCLevel.Q);

            QRCode qrCode = new QRCode(qrCodeData);
            Bitmap bm = qrCode.GetGraphic(20);
            this.qrcode.SizeMode = PictureBoxSizeMode.StretchImage;

            this.qrcode.Image = bm;
        }

        public string GetGlobalSecretKey()
        {
            return GetStringValueFromReg(Registry.LocalMachine, "SOFTWARE\\RDOTP", "GlobalSecretKey");
        }

       
        private void secret_generate_btn_Click(object sender, EventArgs e)
        {
            var op = MessageBox.Show(Resource.KeySettings_changeconfirm, "rdOTP", MessageBoxButtons.YesNo, MessageBoxIcon.None , MessageBoxDefaultButton.Button2);
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

            EraseQRCode();

            MessageBox.Show(Resource.KeySettings_complete);
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
            if (string.IsNullOrEmpty(this.secrent_key_value.Text))
            {
                MessageBox.Show(Resource.KeySettings_keynotfound, "rdOTP");
                return;
            }
            SetQRCode();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(this.secrent_key_value.Text))
            {
                MessageBox.Show(Resource.KeySettings_keynotfound, "rdOTP");
                return;
            }

            if (!RDOTP_InitializeAuthWindow(this.Handle))
            {
                MessageBox.Show("RDOTP_InitializeAuthWindow failed", "rdOTP");
                return;
            }

            if (RDOTP_CreateAuthWindow() == IntPtr.Zero)
            {
                MessageBox.Show("RDOTP_CreateAuthWindow failed", "rdOTP");
                return;
            }

            if (RDOTP_ShowAuthWindow() == false)
            {
                MessageBox.Show(Resource.KeySettings_testFailed, "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                MessageBox.Show(Resource.KeySettings_testPassed, "rdOTP");
            }
        }

        private void secret_view_check_CheckedChanged(object sender, EventArgs e)
        {
            if (this.secret_view_check.Checked)
            {
                this.secrent_key_value.PasswordChar = '\0';
            }
            else
            {
                this.secrent_key_value.PasswordChar = '*';
            }
        }

        private void expKey_btn_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(this.secrent_key_value.Text))
            {
                MessageBox.Show(Resource.KeySettings_keynotfound, "rdOTP");
                return;
            }

            using (SaveFileDialog saveDialog = new SaveFileDialog())
            {
                saveDialog.Filter = "rdOTP Key File|*.rdotpkey";
                saveDialog.Title = Resource.KeySettings_ExportDialogTitle;
                saveDialog.OverwritePrompt= true;

                var result = saveDialog.ShowDialog();
                if (result != DialogResult.OK)
                {
                    return;
                }

                string path = saveDialog.FileName;
                if (string.IsNullOrEmpty(path))
                {
                    return;
                }
                try
                {
                    File.WriteAllText(path, this.secrent_key_value.Text, Encoding.UTF8);
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"{Resource.KeySettings_ExportFailed}\n" + ex.Message, "rdOTP" ,MessageBoxButtons.OK , MessageBoxIcon.Error);
                }
            }

            MessageBox.Show(Resource.KeySettings_ExportSuccess, "rdOTP");
        }

        private void impKey_btn_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(this.secrent_key_value.Text))
            {
                var op = MessageBox.Show(Resource.KeySettings_importConfirm, "rdOTP", MessageBoxButtons.YesNo , MessageBoxIcon.None, MessageBoxDefaultButton.Button2);
                if(op != DialogResult.Yes)
                {
                    return;
                }
            }

            using (System.Windows.Forms.OpenFileDialog openDialog = new System.Windows.Forms.OpenFileDialog())
            {
                openDialog.Filter = "rdOTP Key File|*.rdotpkey";
                openDialog.Title = Resource.KeySettings_ImportDialogTitle;

                var result = openDialog.ShowDialog();
                if (result != DialogResult.OK)
                {
                    return;
                }

                string path = openDialog.FileName;
                if (string.IsNullOrEmpty(path) || !File.Exists(path))
                {
                    return;
                }

                // check file validation
                try
                {
                    FileInfo fileInfo = new FileInfo(path);
                    if (fileInfo.Length > 1024)
                    {
                        MessageBox.Show(Resource.KeySettings_ImportInvalidKey, "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"{Resource.KeySettings_ImportInvalidKey}\n{ ex.Message}", "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                string data = string.Empty;

                try
                {
                    data = File.ReadAllText(path, Encoding.UTF8);
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"{Resource.KeySettings_ImportReadFailed}\n{ex.Message}", "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                if (string.IsNullOrEmpty(data))
                {
                    MessageBox.Show(Resource.KeySettings_ImportInvalidKey, "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                if (data.Length != 32)
                {
                    MessageBox.Show(Resource.KeySettings_ImportInvalidKey, "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                // check invalid char in key data
                foreach (var c in data)
                {
                    if(c >= 128) // check ascii
                    {
                        // invalid char
                        MessageBox.Show(Resource.KeySettings_ImportInvalidKey, "rdOTP", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                }

                SetStringValueFromReg(Registry.LocalMachine, "SOFTWARE\\RDOTP", "GlobalSecretKey", data);

                this.secrent_key_value.Text = data;

                EraseQRCode();
            }

            MessageBox.Show(Resource.KeySettings_ImportSuccess, "rdOTP");
        }

        private void EraseQRCode()
        {
            if (this.qrcode.Image != null)
            {
                this.qrcode.Image.Dispose();
            }
            this.qrcode.Image = null;
        }

        [DllImport("rdOTPAuth.dll")]
        private static extern bool RDOTP_InitializeAuthWindow(IntPtr hwnd);

        [DllImport("rdOTPAuth.dll")]
        private static extern IntPtr RDOTP_CreateAuthWindow();

        [DllImport("rdOTPAuth.dll")]
        private static extern bool RDOTP_ShowAuthWindow();
    }
}
