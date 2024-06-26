
namespace rdOTP.UI
{
    partial class AdvancedSettings
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AdvancedSettings));
            this.other_remote_settings_group = new System.Windows.Forms.GroupBox();
            this.stop_btn = new System.Windows.Forms.Button();
            this.start_btn = new System.Windows.Forms.Button();
            this.uninstall_btn = new System.Windows.Forms.Button();
            this.install_btn = new System.Windows.Forms.Button();
            this.service_install_status = new System.Windows.Forms.Label();
            this.service_install_status_label = new System.Windows.Forms.Label();
            this.service_running_status = new System.Windows.Forms.Label();
            this.service_run_status_label = new System.Windows.Forms.Label();
            this.chrome_rd_enable_chk = new System.Windows.Forms.CheckBox();
            this.chrome_rd_label = new System.Windows.Forms.Label();
            this.warning_beta_label = new System.Windows.Forms.Label();
            this.lock_btn = new System.Windows.Forms.Button();
            this.other_remote_settings_group.SuspendLayout();
            this.SuspendLayout();
            // 
            // other_remote_settings_group
            // 
            resources.ApplyResources(this.other_remote_settings_group, "other_remote_settings_group");
            this.other_remote_settings_group.Controls.Add(this.stop_btn);
            this.other_remote_settings_group.Controls.Add(this.start_btn);
            this.other_remote_settings_group.Controls.Add(this.uninstall_btn);
            this.other_remote_settings_group.Controls.Add(this.install_btn);
            this.other_remote_settings_group.Controls.Add(this.service_install_status);
            this.other_remote_settings_group.Controls.Add(this.service_install_status_label);
            this.other_remote_settings_group.Controls.Add(this.service_running_status);
            this.other_remote_settings_group.Controls.Add(this.service_run_status_label);
            this.other_remote_settings_group.Controls.Add(this.chrome_rd_enable_chk);
            this.other_remote_settings_group.Controls.Add(this.chrome_rd_label);
            this.other_remote_settings_group.Name = "other_remote_settings_group";
            this.other_remote_settings_group.TabStop = false;
            // 
            // stop_btn
            // 
            resources.ApplyResources(this.stop_btn, "stop_btn");
            this.stop_btn.Name = "stop_btn";
            this.stop_btn.UseVisualStyleBackColor = true;
            this.stop_btn.Click += new System.EventHandler(this.stop_btn_Click);
            // 
            // start_btn
            // 
            resources.ApplyResources(this.start_btn, "start_btn");
            this.start_btn.Name = "start_btn";
            this.start_btn.UseVisualStyleBackColor = true;
            this.start_btn.Click += new System.EventHandler(this.start_btn_Click);
            // 
            // uninstall_btn
            // 
            resources.ApplyResources(this.uninstall_btn, "uninstall_btn");
            this.uninstall_btn.Name = "uninstall_btn";
            this.uninstall_btn.UseVisualStyleBackColor = true;
            this.uninstall_btn.Click += new System.EventHandler(this.uninstall_btn_Click);
            // 
            // install_btn
            // 
            resources.ApplyResources(this.install_btn, "install_btn");
            this.install_btn.Name = "install_btn";
            this.install_btn.UseVisualStyleBackColor = true;
            this.install_btn.Click += new System.EventHandler(this.install_btn_Click);
            // 
            // service_install_status
            // 
            resources.ApplyResources(this.service_install_status, "service_install_status");
            this.service_install_status.Name = "service_install_status";
            // 
            // service_install_status_label
            // 
            resources.ApplyResources(this.service_install_status_label, "service_install_status_label");
            this.service_install_status_label.Name = "service_install_status_label";
            // 
            // service_running_status
            // 
            resources.ApplyResources(this.service_running_status, "service_running_status");
            this.service_running_status.Name = "service_running_status";
            // 
            // service_run_status_label
            // 
            resources.ApplyResources(this.service_run_status_label, "service_run_status_label");
            this.service_run_status_label.Name = "service_run_status_label";
            // 
            // chrome_rd_enable_chk
            // 
            resources.ApplyResources(this.chrome_rd_enable_chk, "chrome_rd_enable_chk");
            this.chrome_rd_enable_chk.Name = "chrome_rd_enable_chk";
            this.chrome_rd_enable_chk.UseVisualStyleBackColor = true;
            // 
            // chrome_rd_label
            // 
            resources.ApplyResources(this.chrome_rd_label, "chrome_rd_label");
            this.chrome_rd_label.Name = "chrome_rd_label";
            // 
            // warning_beta_label
            // 
            resources.ApplyResources(this.warning_beta_label, "warning_beta_label");
            this.warning_beta_label.ForeColor = System.Drawing.Color.Red;
            this.warning_beta_label.Name = "warning_beta_label";
            // 
            // lock_btn
            // 
            resources.ApplyResources(this.lock_btn, "lock_btn");
            this.lock_btn.Name = "lock_btn";
            this.lock_btn.UseVisualStyleBackColor = true;
            this.lock_btn.Click += new System.EventHandler(this.lock_btn_Click);
            // 
            // AdvancedSettings
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.lock_btn);
            this.Controls.Add(this.warning_beta_label);
            this.Controls.Add(this.other_remote_settings_group);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "AdvancedSettings";
            this.ShowIcon = false;
            this.other_remote_settings_group.ResumeLayout(false);
            this.other_remote_settings_group.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox other_remote_settings_group;
        private System.Windows.Forms.Label service_running_status;
        private System.Windows.Forms.Label service_run_status_label;
        private System.Windows.Forms.CheckBox chrome_rd_enable_chk;
        private System.Windows.Forms.Label chrome_rd_label;
        private System.Windows.Forms.Label warning_beta_label;
        private System.Windows.Forms.Label service_install_status;
        private System.Windows.Forms.Label service_install_status_label;
        private System.Windows.Forms.Button stop_btn;
        private System.Windows.Forms.Button start_btn;
        private System.Windows.Forms.Button uninstall_btn;
        private System.Windows.Forms.Button install_btn;
        private System.Windows.Forms.Button lock_btn;
    }
}