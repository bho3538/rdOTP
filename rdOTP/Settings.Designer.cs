
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
            this.linkLabel1 = new System.Windows.Forms.LinkLabel();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.intstall_btn = new System.Windows.Forms.Button();
            this.uninstall_btn = new System.Windows.Forms.Button();
            this.iconInfo_link = new System.Windows.Forms.LinkLabel();
            this.SuspendLayout();
            // 
            // status_label
            // 
            this.status_label.AutoSize = true;
            this.status_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.status_label.Location = new System.Drawing.Point(13, 13);
            this.status_label.Name = "status_label";
            this.status_label.Size = new System.Drawing.Size(60, 24);
            this.status_label.TabIndex = 0;
            this.status_label.Text = "Status";
            // 
            // secret_label
            // 
            this.secret_label.AutoSize = true;
            this.secret_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.secret_label.Location = new System.Drawing.Point(13, 46);
            this.secret_label.Name = "secret_label";
            this.secret_label.Size = new System.Drawing.Size(165, 24);
            this.secret_label.TabIndex = 1;
            this.secret_label.Text = "Auth Configuration";
            // 
            // secret_config_btn
            // 
            this.secret_config_btn.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.secret_config_btn.Location = new System.Drawing.Point(352, 46);
            this.secret_config_btn.Name = "secret_config_btn";
            this.secret_config_btn.Size = new System.Drawing.Size(156, 28);
            this.secret_config_btn.TabIndex = 2;
            this.secret_config_btn.Text = "Configuration";
            this.secret_config_btn.UseVisualStyleBackColor = true;
            this.secret_config_btn.Click += new System.EventHandler(this.secret_config_btn_Click);
            // 
            // status_value_label
            // 
            this.status_value_label.AutoSize = true;
            this.status_value_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.status_value_label.Location = new System.Drawing.Point(114, 13);
            this.status_value_label.Name = "status_value_label";
            this.status_value_label.Size = new System.Drawing.Size(112, 24);
            this.status_value_label.TabIndex = 3;
            this.status_value_label.Text = "Not Installed";
            // 
            // linkLabel1
            // 
            this.linkLabel1.AutoSize = true;
            this.linkLabel1.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.linkLabel1.Location = new System.Drawing.Point(375, 200);
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.Size = new System.Drawing.Size(133, 24);
            this.linkLabel1.TabIndex = 5;
            this.linkLabel1.TabStop = true;
            this.linkLabel1.Text = "View Web Site";
            this.linkLabel1.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // intstall_btn
            // 
            this.intstall_btn.Font = new System.Drawing.Font("Arial", 10F);
            this.intstall_btn.Location = new System.Drawing.Point(277, 12);
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
            this.uninstall_btn.Location = new System.Drawing.Point(390, 12);
            this.uninstall_btn.Name = "uninstall_btn";
            this.uninstall_btn.Size = new System.Drawing.Size(118, 24);
            this.uninstall_btn.TabIndex = 7;
            this.uninstall_btn.Text = "Uninstall";
            this.uninstall_btn.UseVisualStyleBackColor = true;
            this.uninstall_btn.Click += new System.EventHandler(this.uninstall_btn_Click);
            // 
            // iconInfo_link
            // 
            this.iconInfo_link.AutoSize = true;
            this.iconInfo_link.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.iconInfo_link.Location = new System.Drawing.Point(375, 227);
            this.iconInfo_link.Name = "iconInfo_link";
            this.iconInfo_link.Size = new System.Drawing.Size(157, 19);
            this.iconInfo_link.TabIndex = 8;
            this.iconInfo_link.TabStop = true;
            this.iconInfo_link.Text = "Lock icon by Icons8";
            this.iconInfo_link.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.iconInfo_link_LinkClicked);
            // 
            // Settings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(543, 257);
            this.Controls.Add(this.iconInfo_link);
            this.Controls.Add(this.uninstall_btn);
            this.Controls.Add(this.intstall_btn);
            this.Controls.Add(this.linkLabel1);
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
            this.Text = "RDOTP Settings";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label status_label;
        private System.Windows.Forms.Label secret_label;
        private System.Windows.Forms.Button secret_config_btn;
        private System.Windows.Forms.Label status_value_label;
        private System.Windows.Forms.LinkLabel linkLabel1;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Button intstall_btn;
        private System.Windows.Forms.Button uninstall_btn;
        private System.Windows.Forms.LinkLabel iconInfo_link;
    }
}