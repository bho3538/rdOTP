
namespace rdOTP
{
    partial class Settings
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Settings));
            this.status_label = new System.Windows.Forms.Label();
            this.secret_label = new System.Windows.Forms.Label();
            this.secret_config_btn = new System.Windows.Forms.Button();
            this.status_value_label = new System.Windows.Forms.Label();
            this.WebSite_link = new System.Windows.Forms.LinkLabel();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.intstall_btn = new System.Windows.Forms.Button();
            this.uninstall_btn = new System.Windows.Forms.Button();
            this.IconInfo_link = new System.Windows.Forms.LinkLabel();
            this.Version_label = new System.Windows.Forms.Label();
            this.logo = new System.Windows.Forms.PictureBox();
            this.MainTitle = new System.Windows.Forms.Label();
            this.aboutGroup = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.logo)).BeginInit();
            this.aboutGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // status_label
            // 
            this.status_label.AutoSize = true;
            this.status_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.status_label.Location = new System.Drawing.Point(9, 53);
            this.status_label.Name = "status_label";
            this.status_label.Size = new System.Drawing.Size(103, 18);
            this.status_label.TabIndex = 0;
            this.status_label.Text = "Module Status";
            // 
            // secret_label
            // 
            this.secret_label.AutoSize = true;
            this.secret_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.secret_label.Location = new System.Drawing.Point(9, 92);
            this.secret_label.Name = "secret_label";
            this.secret_label.Size = new System.Drawing.Size(129, 18);
            this.secret_label.TabIndex = 1;
            this.secret_label.Text = "Auth Configuration";
            // 
            // secret_config_btn
            // 
            this.secret_config_btn.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.secret_config_btn.Location = new System.Drawing.Point(286, 88);
            this.secret_config_btn.Name = "secret_config_btn";
            this.secret_config_btn.Size = new System.Drawing.Size(231, 28);
            this.secret_config_btn.TabIndex = 2;
            this.secret_config_btn.Text = "Configuration";
            this.secret_config_btn.UseVisualStyleBackColor = true;
            this.secret_config_btn.Click += new System.EventHandler(this.secret_config_btn_Click);
            // 
            // status_value_label
            // 
            this.status_value_label.AutoSize = true;
            this.status_value_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.status_value_label.Location = new System.Drawing.Point(160, 53);
            this.status_value_label.Name = "status_value_label";
            this.status_value_label.Size = new System.Drawing.Size(89, 18);
            this.status_value_label.TabIndex = 3;
            this.status_value_label.Text = "Not Installed";
            // 
            // WebSite_link
            // 
            this.WebSite_link.AutoSize = true;
            this.WebSite_link.Font = new System.Drawing.Font("Arial", 9F);
            this.WebSite_link.Location = new System.Drawing.Point(6, 53);
            this.WebSite_link.Name = "WebSite_link";
            this.WebSite_link.Size = new System.Drawing.Size(85, 15);
            this.WebSite_link.TabIndex = 5;
            this.WebSite_link.TabStop = true;
            this.WebSite_link.Text = "View Web Site";
            this.WebSite_link.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // intstall_btn
            // 
            this.intstall_btn.Font = new System.Drawing.Font("Arial", 10F);
            this.intstall_btn.Location = new System.Drawing.Point(286, 51);
            this.intstall_btn.Name = "intstall_btn";
            this.intstall_btn.Size = new System.Drawing.Size(107, 24);
            this.intstall_btn.TabIndex = 6;
            this.intstall_btn.Text = "Install";
            this.intstall_btn.UseVisualStyleBackColor = true;
            this.intstall_btn.Click += new System.EventHandler(this.intstall_btn_Click);
            // 
            // uninstall_btn
            // 
            this.uninstall_btn.Font = new System.Drawing.Font("Arial", 10F);
            this.uninstall_btn.Location = new System.Drawing.Point(399, 51);
            this.uninstall_btn.Name = "uninstall_btn";
            this.uninstall_btn.Size = new System.Drawing.Size(118, 24);
            this.uninstall_btn.TabIndex = 7;
            this.uninstall_btn.Text = "Uninstall";
            this.uninstall_btn.UseVisualStyleBackColor = true;
            this.uninstall_btn.Click += new System.EventHandler(this.uninstall_btn_Click);
            // 
            // IconInfo_link
            // 
            this.IconInfo_link.AutoSize = true;
            this.IconInfo_link.Font = new System.Drawing.Font("Arial", 9F);
            this.IconInfo_link.Location = new System.Drawing.Point(6, 80);
            this.IconInfo_link.Name = "IconInfo_link";
            this.IconInfo_link.Size = new System.Drawing.Size(114, 15);
            this.IconInfo_link.TabIndex = 8;
            this.IconInfo_link.TabStop = true;
            this.IconInfo_link.Text = "Lock icon by Icons8";
            this.IconInfo_link.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.iconInfo_link_LinkClicked);
            // 
            // Version_label
            // 
            this.Version_label.AutoSize = true;
            this.Version_label.Font = new System.Drawing.Font("Arial", 9F);
            this.Version_label.Location = new System.Drawing.Point(6, 27);
            this.Version_label.Name = "Version_label";
            this.Version_label.Size = new System.Drawing.Size(72, 15);
            this.Version_label.TabIndex = 9;
            this.Version_label.Text = "Version : {0}";
            // 
            // logo
            // 
            this.logo.ErrorImage = null;
            this.logo.Image = ((System.Drawing.Image)(resources.GetObject("logo.Image")));
            this.logo.InitialImage = null;
            this.logo.Location = new System.Drawing.Point(12, 180);
            this.logo.Name = "logo";
            this.logo.Size = new System.Drawing.Size(68, 62);
            this.logo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.logo.TabIndex = 10;
            this.logo.TabStop = false;
            // 
            // MainTitle
            // 
            this.MainTitle.AutoSize = true;
            this.MainTitle.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MainTitle.Location = new System.Drawing.Point(7, 9);
            this.MainTitle.Name = "MainTitle";
            this.MainTitle.Size = new System.Drawing.Size(444, 25);
            this.MainTitle.TabIndex = 11;
            this.MainTitle.Text = "rdOTP - Serverless Windows RDP OTP Auth";
            this.MainTitle.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // aboutGroup
            // 
            this.aboutGroup.Controls.Add(this.Version_label);
            this.aboutGroup.Controls.Add(this.WebSite_link);
            this.aboutGroup.Controls.Add(this.IconInfo_link);
            this.aboutGroup.Font = new System.Drawing.Font("Arial", 10F);
            this.aboutGroup.Location = new System.Drawing.Point(286, 132);
            this.aboutGroup.Name = "aboutGroup";
            this.aboutGroup.Size = new System.Drawing.Size(231, 112);
            this.aboutGroup.TabIndex = 12;
            this.aboutGroup.TabStop = false;
            this.aboutGroup.Text = "About";
            // 
            // Settings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(528, 256);
            this.Controls.Add(this.aboutGroup);
            this.Controls.Add(this.MainTitle);
            this.Controls.Add(this.logo);
            this.Controls.Add(this.uninstall_btn);
            this.Controls.Add(this.intstall_btn);
            this.Controls.Add(this.status_value_label);
            this.Controls.Add(this.secret_config_btn);
            this.Controls.Add(this.secret_label);
            this.Controls.Add(this.status_label);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Settings";
            this.ShowIcon = false;
            this.Text = "rdOTP Settings";
            ((System.ComponentModel.ISupportInitialize)(this.logo)).EndInit();
            this.aboutGroup.ResumeLayout(false);
            this.aboutGroup.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label status_label;
        private System.Windows.Forms.Label secret_label;
        private System.Windows.Forms.Button secret_config_btn;
        private System.Windows.Forms.Label status_value_label;
        private System.Windows.Forms.LinkLabel WebSite_link;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Button intstall_btn;
        private System.Windows.Forms.Button uninstall_btn;
        private System.Windows.Forms.LinkLabel IconInfo_link;
        private System.Windows.Forms.Label Version_label;
        private System.Windows.Forms.PictureBox logo;
        private System.Windows.Forms.Label MainTitle;
        private System.Windows.Forms.GroupBox aboutGroup;
    }
}