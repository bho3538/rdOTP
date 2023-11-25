
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
            this.secrent_key_value = new System.Windows.Forms.Label();
            this.secret_generate_btn = new System.Windows.Forms.Button();
            this.qrcode = new System.Windows.Forms.PictureBox();
            this.qr_show_btn = new System.Windows.Forms.Button();
            this.displayname_label = new System.Windows.Forms.Label();
            this.displayname_input = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.qrcode)).BeginInit();
            this.SuspendLayout();
            // 
            // secret_label
            // 
            this.secret_label.AutoSize = true;
            this.secret_label.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.secret_label.Location = new System.Drawing.Point(13, 13);
            this.secret_label.Name = "secret_label";
            this.secret_label.Size = new System.Drawing.Size(85, 16);
            this.secret_label.TabIndex = 0;
            this.secret_label.Text = "Secret Key : ";
            // 
            // secrent_key_value
            // 
            this.secrent_key_value.AutoSize = true;
            this.secrent_key_value.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.secrent_key_value.Location = new System.Drawing.Point(15, 41);
            this.secrent_key_value.Name = "secrent_key_value";
            this.secrent_key_value.Size = new System.Drawing.Size(11, 15);
            this.secrent_key_value.TabIndex = 1;
            this.secrent_key_value.Text = "-";
            // 
            // secret_generate_btn
            // 
            this.secret_generate_btn.Location = new System.Drawing.Point(589, 12);
            this.secret_generate_btn.Name = "secret_generate_btn";
            this.secret_generate_btn.Size = new System.Drawing.Size(141, 24);
            this.secret_generate_btn.TabIndex = 2;
            this.secret_generate_btn.Text = "Generate New";
            this.secret_generate_btn.UseVisualStyleBackColor = true;
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
            this.qr_show_btn.Location = new System.Drawing.Point(12, 342);
            this.qr_show_btn.Name = "qr_show_btn";
            this.qr_show_btn.Size = new System.Drawing.Size(183, 23);
            this.qr_show_btn.TabIndex = 4;
            this.qr_show_btn.Text = "Show QR Code";
            this.qr_show_btn.UseVisualStyleBackColor = true;
            this.qr_show_btn.Click += new System.EventHandler(this.qr_show_btn_Click);
            // 
            // displayname_label
            // 
            this.displayname_label.AutoSize = true;
            this.displayname_label.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.displayname_label.Location = new System.Drawing.Point(9, 285);
            this.displayname_label.Name = "displayname_label";
            this.displayname_label.Size = new System.Drawing.Size(85, 15);
            this.displayname_label.TabIndex = 5;
            this.displayname_label.Text = "Display Name";
            // 
            // displayname_input
            // 
            this.displayname_input.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.displayname_input.Location = new System.Drawing.Point(12, 312);
            this.displayname_input.Name = "displayname_input";
            this.displayname_input.Size = new System.Drawing.Size(183, 21);
            this.displayname_input.TabIndex = 6;
            this.displayname_input.Text = "My Remote Computer";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(15, 71);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(267, 15);
            this.label1.TabIndex = 7;
            this.label1.Text = "WARNING : Do not share secret key or QR code";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(430, 13);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(143, 23);
            this.button1.TabIndex = 8;
            this.button1.Text = "OTP Test";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // KeySettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(747, 377);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.displayname_input);
            this.Controls.Add(this.displayname_label);
            this.Controls.Add(this.qr_show_btn);
            this.Controls.Add(this.qrcode);
            this.Controls.Add(this.secret_generate_btn);
            this.Controls.Add(this.secrent_key_value);
            this.Controls.Add(this.secret_label);
            this.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "KeySettings";
            this.Text = "KeySettings";
            ((System.ComponentModel.ISupportInitialize)(this.qrcode)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label secret_label;
        private System.Windows.Forms.Label secrent_key_value;
        private System.Windows.Forms.Button secret_generate_btn;
        private System.Windows.Forms.PictureBox qrcode;
        private System.Windows.Forms.Button qr_show_btn;
        private System.Windows.Forms.Label displayname_label;
        private System.Windows.Forms.TextBox displayname_input;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
    }
}