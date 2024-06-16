
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
            resources.ApplyResources(this.secret_label, "secret_label");
            this.secret_label.Name = "secret_label";
            // 
            // secret_generate_btn
            // 
            resources.ApplyResources(this.secret_generate_btn, "secret_generate_btn");
            this.secret_generate_btn.BackColor = System.Drawing.Color.PaleTurquoise;
            this.secret_generate_btn.Name = "secret_generate_btn";
            this.secret_generate_btn.UseVisualStyleBackColor = false;
            this.secret_generate_btn.Click += new System.EventHandler(this.secret_generate_btn_Click);
            // 
            // qrcode
            // 
            resources.ApplyResources(this.qrcode, "qrcode");
            this.qrcode.Name = "qrcode";
            this.qrcode.TabStop = false;
            // 
            // qr_show_btn
            // 
            resources.ApplyResources(this.qr_show_btn, "qr_show_btn");
            this.qr_show_btn.Name = "qr_show_btn";
            this.qr_show_btn.UseVisualStyleBackColor = true;
            this.qr_show_btn.Click += new System.EventHandler(this.qr_show_btn_Click);
            // 
            // displayname_label
            // 
            resources.ApplyResources(this.displayname_label, "displayname_label");
            this.displayname_label.Name = "displayname_label";
            // 
            // displayname_input
            // 
            resources.ApplyResources(this.displayname_input, "displayname_input");
            this.displayname_input.Name = "displayname_input";
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Name = "label1";
            // 
            // button1
            // 
            resources.ApplyResources(this.button1, "button1");
            this.button1.BackColor = System.Drawing.SystemColors.Info;
            this.button1.Name = "button1";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // secrent_key_value
            // 
            resources.ApplyResources(this.secrent_key_value, "secrent_key_value");
            this.secrent_key_value.Name = "secrent_key_value";
            this.secrent_key_value.ReadOnly = true;
            // 
            // secret_view_check
            // 
            resources.ApplyResources(this.secret_view_check, "secret_view_check");
            this.secret_view_check.Name = "secret_view_check";
            this.secret_view_check.UseVisualStyleBackColor = true;
            this.secret_view_check.CheckedChanged += new System.EventHandler(this.secret_view_check_CheckedChanged);
            // 
            // qrgroupbox
            // 
            resources.ApplyResources(this.qrgroupbox, "qrgroupbox");
            this.qrgroupbox.Controls.Add(this.displayname_label);
            this.qrgroupbox.Controls.Add(this.displayname_input);
            this.qrgroupbox.Name = "qrgroupbox";
            this.qrgroupbox.TabStop = false;
            // 
            // otpInfoGroup
            // 
            resources.ApplyResources(this.otpInfoGroup, "otpInfoGroup");
            this.otpInfoGroup.Controls.Add(this.timestep_label);
            this.otpInfoGroup.Controls.Add(this.digest_length_label);
            this.otpInfoGroup.Controls.Add(this.key_mode_label);
            this.otpInfoGroup.Name = "otpInfoGroup";
            this.otpInfoGroup.TabStop = false;
            // 
            // timestep_label
            // 
            resources.ApplyResources(this.timestep_label, "timestep_label");
            this.timestep_label.Name = "timestep_label";
            // 
            // digest_length_label
            // 
            resources.ApplyResources(this.digest_length_label, "digest_length_label");
            this.digest_length_label.Name = "digest_length_label";
            // 
            // key_mode_label
            // 
            resources.ApplyResources(this.key_mode_label, "key_mode_label");
            this.key_mode_label.Name = "key_mode_label";
            // 
            // expKey_btn
            // 
            resources.ApplyResources(this.expKey_btn, "expKey_btn");
            this.expKey_btn.Name = "expKey_btn";
            this.expKey_btn.UseVisualStyleBackColor = true;
            this.expKey_btn.Click += new System.EventHandler(this.expKey_btn_Click);
            // 
            // impKey_btn
            // 
            resources.ApplyResources(this.impKey_btn, "impKey_btn");
            this.impKey_btn.Name = "impKey_btn";
            this.impKey_btn.UseVisualStyleBackColor = true;
            this.impKey_btn.Click += new System.EventHandler(this.impKey_btn_Click);
            // 
            // KeySettings
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
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
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "KeySettings";
            this.ShowIcon = false;
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