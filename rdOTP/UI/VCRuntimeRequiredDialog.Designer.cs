
namespace rdOTP.UI
{
    partial class VCRuntimeRequiredDialog
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(VCRuntimeRequiredDialog));
            this.title_label = new System.Windows.Forms.Label();
            this.link_label = new System.Windows.Forms.LinkLabel();
            this.close_btn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // title_label
            // 
            resources.ApplyResources(this.title_label, "title_label");
            this.title_label.Name = "title_label";
            // 
            // link_label
            // 
            resources.ApplyResources(this.link_label, "link_label");
            this.link_label.Name = "link_label";
            this.link_label.TabStop = true;
            this.link_label.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.link_label_LinkClicked);
            // 
            // close_btn
            // 
            resources.ApplyResources(this.close_btn, "close_btn");
            this.close_btn.Name = "close_btn";
            this.close_btn.UseVisualStyleBackColor = true;
            this.close_btn.Click += new System.EventHandler(this.close_btn_Click);
            // 
            // VCRuntimeRequiredDialog
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.close_btn);
            this.Controls.Add(this.link_label);
            this.Controls.Add(this.title_label);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "VCRuntimeRequiredDialog";
            this.ShowIcon = false;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label title_label;
        private System.Windows.Forms.LinkLabel link_label;
        private System.Windows.Forms.Button close_btn;
    }
}