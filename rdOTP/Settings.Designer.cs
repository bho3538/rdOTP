
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
            this.credit_label = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.logo)).BeginInit();
            this.aboutGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // status_label
            // 
            resources.ApplyResources(this.status_label, "status_label");
            this.status_label.Name = "status_label";
            // 
            // secret_label
            // 
            resources.ApplyResources(this.secret_label, "secret_label");
            this.secret_label.Name = "secret_label";
            // 
            // secret_config_btn
            // 
            resources.ApplyResources(this.secret_config_btn, "secret_config_btn");
            this.secret_config_btn.Name = "secret_config_btn";
            this.secret_config_btn.UseVisualStyleBackColor = true;
            this.secret_config_btn.Click += new System.EventHandler(this.secret_config_btn_Click);
            // 
            // status_value_label
            // 
            resources.ApplyResources(this.status_value_label, "status_value_label");
            this.status_value_label.Name = "status_value_label";
            // 
            // WebSite_link
            // 
            resources.ApplyResources(this.WebSite_link, "WebSite_link");
            this.WebSite_link.Name = "WebSite_link";
            this.WebSite_link.TabStop = true;
            this.WebSite_link.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // intstall_btn
            // 
            resources.ApplyResources(this.intstall_btn, "intstall_btn");
            this.intstall_btn.Name = "intstall_btn";
            this.intstall_btn.UseVisualStyleBackColor = true;
            this.intstall_btn.Click += new System.EventHandler(this.intstall_btn_Click);
            // 
            // uninstall_btn
            // 
            resources.ApplyResources(this.uninstall_btn, "uninstall_btn");
            this.uninstall_btn.Name = "uninstall_btn";
            this.uninstall_btn.UseVisualStyleBackColor = true;
            this.uninstall_btn.Click += new System.EventHandler(this.uninstall_btn_Click);
            // 
            // IconInfo_link
            // 
            resources.ApplyResources(this.IconInfo_link, "IconInfo_link");
            this.IconInfo_link.Name = "IconInfo_link";
            this.IconInfo_link.TabStop = true;
            this.IconInfo_link.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.iconInfo_link_LinkClicked);
            // 
            // Version_label
            // 
            resources.ApplyResources(this.Version_label, "Version_label");
            this.Version_label.Name = "Version_label";
            // 
            // logo
            // 
            resources.ApplyResources(this.logo, "logo");
            this.logo.Name = "logo";
            this.logo.TabStop = false;
            // 
            // MainTitle
            // 
            resources.ApplyResources(this.MainTitle, "MainTitle");
            this.MainTitle.Name = "MainTitle";
            // 
            // aboutGroup
            // 
            resources.ApplyResources(this.aboutGroup, "aboutGroup");
            this.aboutGroup.Controls.Add(this.credit_label);
            this.aboutGroup.Controls.Add(this.Version_label);
            this.aboutGroup.Controls.Add(this.WebSite_link);
            this.aboutGroup.Controls.Add(this.IconInfo_link);
            this.aboutGroup.Name = "aboutGroup";
            this.aboutGroup.TabStop = false;
            // 
            // credit_label
            // 
            resources.ApplyResources(this.credit_label, "credit_label");
            this.credit_label.ForeColor = System.Drawing.Color.Green;
            this.credit_label.Name = "credit_label";
            // 
            // Settings
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.Controls.Add(this.aboutGroup);
            this.Controls.Add(this.MainTitle);
            this.Controls.Add(this.logo);
            this.Controls.Add(this.uninstall_btn);
            this.Controls.Add(this.intstall_btn);
            this.Controls.Add(this.status_value_label);
            this.Controls.Add(this.secret_config_btn);
            this.Controls.Add(this.secret_label);
            this.Controls.Add(this.status_label);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Settings";
            this.ShowIcon = false;
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
        private System.Windows.Forms.Label credit_label;
    }
}