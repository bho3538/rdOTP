
namespace rdOTP
{
    partial class KeySettings
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(KeySettings));
            this.secret_label = new System.Windows.Forms.Label();
            this.secret_generate_btn = new System.Windows.Forms.Button();
            this.qrcode = new System.Windows.Forms.PictureBox();
            this.qr_show_btn = new System.Windows.Forms.Button();
            this.displayname_label = new System.Windows.Forms.Label();
            this.displayname_input = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.secrent_key_value = new System.Windows.Forms.TextBox();
            this.secret_view_check = new System.Windows.Forms.CheckBox();
            this.qrgroupbox = new System.Windows.Forms.GroupBox();
            this.otpInfoGroup = new System.Windows.Forms.GroupBox();
            this.timestep_label = new System.Windows.Forms.Label();
            this.digest_length_label = new System.Windows.Forms.Label();
            this.key_mode_label = new System.Windows.Forms.Label();
            this.expKey_btn = new System.Windows.Forms.Button();
            this.impKey_btn = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.qrcode)).BeginInit();
            this.qrgroupbox.SuspendLayout();
            this.otpInfoGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // secret_label
            // 
            this.secret_label.AutoSize = true;
            this.secret_label.Font = new System.Drawing.Font("Arial", 10F);
            this.secret_label.Location = new System.Drawing.Point(13, 13);
            this.secret_label.Name = "secret_label";
            this.secret_label.Size = new System.Drawing.Size(88, 16);
            this.secret_label.TabIndex = 0;
            this.secret_label.Text = "Secret Key : ";
            // 
            // secret_generate_btn
            // 
            this.secret_generate_btn.BackColor = System.Drawing.Color.PaleTurquoise;
            this.secret_generate_btn.Location = new System.Drawing.Point(587, 9);
            this.secret_generate_btn.Name = "secret_generate_btn";
            this.secret_generate_btn.Size = new System.Drawing.Size(141, 24);
            this.secret_generate_btn.TabIndex = 2;
            this.secret_generate_btn.Text = "Generate New";
            this.secret_generate_btn.UseVisualStyleBackColor = false;
            this.secret_generate_btn.Click += new System.EventHandler(this.secret_generate_btn_Click);
            // 
            // qrcode
            // 
            this.qrcode.Location = new System.Drawing.Point(395, 71);
            this.qrcode.Name = "qrcode";
            this.qrcode.Size = new System.Drawing.Size(333, 291);
            this.qrcode.TabIndex = 3;
            this.qrcode.TabStop = false;
            // 
            // qr_show_btn
            // 
            this.qr_show_btn.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.qr_show_btn.Location = new System.Drawing.Point(12, 204);
            this.qr_show_btn.Name = "qr_show_btn";
            this.qr_show_btn.Size = new System.Drawing.Size(307, 23);
            this.qr_show_btn.TabIndex = 4;
            this.qr_show_btn.Text = "Show QR Code";
            this.qr_show_btn.UseVisualStyleBackColor = true;
            this.qr_show_btn.Click += new System.EventHandler(this.qr_show_btn_Click);
            // 
            // displayname_label
            // 
            this.displayname_label.AutoSize = true;
            this.displayname_label.Font = new System.Drawing.Font("Arial", 10F);
            this.displayname_label.Location = new System.Drawing.Point(6, 24);
            this.displayname_label.Name = "displayname_label";
            this.displayname_label.Size = new System.Drawing.Size(93, 16);
            this.displayname_label.TabIndex = 5;
            this.displayname_label.Text = "Display Name";
            // 
            // displayname_input
            // 
            this.displayname_input.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.displayname_input.Location = new System.Drawing.Point(9, 48);
            this.displayname_input.Name = "displayname_input";
            this.displayname_input.Size = new System.Drawing.Size(204, 21);
            this.displayname_input.TabIndex = 6;
            this.displayname_input.Text = "My Remote Computer";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Arial", 10F);
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(12, 71);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(310, 16);
            this.label1.TabIndex = 7;
            this.label1.Text = "WARNING : Do not share secret key or QR code";
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.SystemColors.Info;
            this.button1.Location = new System.Drawing.Point(438, 9);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(143, 24);
            this.button1.TabIndex = 8;
            this.button1.Text = "OTP Test";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // secrent_key_value
            // 
            this.secrent_key_value.Location = new System.Drawing.Point(12, 38);
            this.secrent_key_value.MaxLength = 128;
            this.secrent_key_value.Name = "secrent_key_value";
            this.secrent_key_value.PasswordChar = '*';
            this.secrent_key_value.ReadOnly = true;
            this.secrent_key_value.Size = new System.Drawing.Size(311, 21);
            this.secrent_key_value.TabIndex = 9;
            // 
            // secret_view_check
            // 
            this.secret_view_check.AutoSize = true;
            this.secret_view_check.Location = new System.Drawing.Point(271, 13);
            this.secret_view_check.Name = "secret_view_check";
            this.secret_view_check.Size = new System.Drawing.Size(52, 19);
            this.secret_view_check.TabIndex = 10;
            this.secret_view_check.Text = "View";
            this.secret_view_check.UseVisualStyleBackColor = true;
            this.secret_view_check.CheckedChanged += new System.EventHandler(this.secret_view_check_CheckedChanged);
            // 
            // qrgroupbox
            // 
            this.qrgroupbox.Controls.Add(this.displayname_label);
            this.qrgroupbox.Controls.Add(this.displayname_input);
            this.qrgroupbox.Font = new System.Drawing.Font("Arial", 10F);
            this.qrgroupbox.Location = new System.Drawing.Point(12, 114);
            this.qrgroupbox.Name = "qrgroupbox";
            this.qrgroupbox.Size = new System.Drawing.Size(307, 84);
            this.qrgroupbox.TabIndex = 11;
            this.qrgroupbox.TabStop = false;
            this.qrgroupbox.Text = "QR Code Options";
            // 
            // otpInfoGroup
            // 
            this.otpInfoGroup.Controls.Add(this.timestep_label);
            this.otpInfoGroup.Controls.Add(this.digest_length_label);
            this.otpInfoGroup.Controls.Add(this.key_mode_label);
            this.otpInfoGroup.Font = new System.Drawing.Font("Arial", 10F);
            this.otpInfoGroup.Location = new System.Drawing.Point(12, 249);
            this.otpInfoGroup.Name = "otpInfoGroup";
            this.otpInfoGroup.Size = new System.Drawing.Size(307, 113);
            this.otpInfoGroup.TabIndex = 12;
            this.otpInfoGroup.TabStop = false;
            this.otpInfoGroup.Text = "OTP Info";
            // 
            // timestep_label
            // 
            this.timestep_label.AutoSize = true;
            this.timestep_label.Location = new System.Drawing.Point(9, 78);
            this.timestep_label.Name = "timestep_label";
            this.timestep_label.Size = new System.Drawing.Size(153, 16);
            this.timestep_label.TabIndex = 2;
            this.timestep_label.Text = "Time step : 30 seconds";
            // 
            // digest_length_label
            // 
            this.digest_length_label.AutoSize = true;
            this.digest_length_label.Location = new System.Drawing.Point(9, 51);
            this.digest_length_label.Name = "digest_length_label";
            this.digest_length_label.Size = new System.Drawing.Size(67, 16);
            this.digest_length_label.TabIndex = 1;
            this.digest_length_label.Text = "Digest : 6";
            // 
            // key_mode_label
            // 
            this.key_mode_label.AutoSize = true;
            this.key_mode_label.Location = new System.Drawing.Point(9, 23);
            this.key_mode_label.Name = "key_mode_label";
            this.key_mode_label.Size = new System.Drawing.Size(152, 16);
            this.key_mode_label.TabIndex = 0;
            this.key_mode_label.Text = "Key hash mode : SHA1";
            // 
            // expKey_btn
            // 
            this.expKey_btn.Location = new System.Drawing.Point(587, 38);
            this.expKey_btn.Name = "expKey_btn";
            this.expKey_btn.Size = new System.Drawing.Size(141, 23);
            this.expKey_btn.TabIndex = 13;
            this.expKey_btn.Text = "Export key";
            this.expKey_btn.UseVisualStyleBackColor = true;
            this.expKey_btn.Click += new System.EventHandler(this.expKey_btn_Click);
            // 
            // impKey_btn
            // 
            this.impKey_btn.Location = new System.Drawing.Point(438, 38);
            this.impKey_btn.Name = "impKey_btn";
            this.impKey_btn.Size = new System.Drawing.Size(143, 23);
            this.impKey_btn.TabIndex = 14;
            this.impKey_btn.Text = "Import key";
            this.impKey_btn.UseVisualStyleBackColor = true;
            this.impKey_btn.Click += new System.EventHandler(this.impKey_btn_Click);
            // 
            // KeySettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(747, 377);
            this.Controls.Add(this.impKey_btn);
            this.Controls.Add(this.expKey_btn);
            this.Controls.Add(this.otpInfoGroup);
            this.Controls.Add(this.qrgroupbox);
            this.Controls.Add(this.secret_view_check);
            this.Controls.Add(this.qr_show_btn);
            this.Controls.Add(this.secrent_key_value);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.qrcode);
            this.Controls.Add(this.secret_generate_btn);
            this.Controls.Add(this.secret_label);
            this.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "KeySettings";
            this.ShowIcon = false;
            this.Text = "RDOTP KeySettings";
            ((System.ComponentModel.ISupportInitialize)(this.qrcode)).EndInit();
            this.qrgroupbox.ResumeLayout(false);
            this.qrgroupbox.PerformLayout();
            this.otpInfoGroup.ResumeLayout(false);
            this.otpInfoGroup.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label secret_label;
        private System.Windows.Forms.Button secret_generate_btn;
        private System.Windows.Forms.PictureBox qrcode;
        private System.Windows.Forms.Button qr_show_btn;
        private System.Windows.Forms.Label displayname_label;
        private System.Windows.Forms.TextBox displayname_input;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox secrent_key_value;
        private System.Windows.Forms.CheckBox secret_view_check;
        private System.Windows.Forms.GroupBox qrgroupbox;
        private System.Windows.Forms.GroupBox otpInfoGroup;
        private System.Windows.Forms.Label key_mode_label;
        private System.Windows.Forms.Label digest_length_label;
        private System.Windows.Forms.Label timestep_label;
        private System.Windows.Forms.Button expKey_btn;
        private System.Windows.Forms.Button impKey_btn;
    }
}