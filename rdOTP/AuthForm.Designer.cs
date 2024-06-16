namespace rdOTP
{
    partial class AuthForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AuthForm));
            this.code_input = new System.Windows.Forms.TextBox();
            this.submit_btn = new System.Windows.Forms.Button();
            this.title_label = new System.Windows.Forms.Label();
            this.title_des_label = new System.Windows.Forms.Label();
            this.time_label = new System.Windows.Forms.Label();
            this.time_value_label = new System.Windows.Forms.Label();
            this.wrong_msg = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.leftTime_label = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // code_input
            // 
            resources.ApplyResources(this.code_input, "code_input");
            this.code_input.Name = "code_input";
            // 
            // submit_btn
            // 
            resources.ApplyResources(this.submit_btn, "submit_btn");
            this.submit_btn.Name = "submit_btn";
            this.submit_btn.UseVisualStyleBackColor = true;
            this.submit_btn.Click += new System.EventHandler(this.submit_btn_Click);
            // 
            // title_label
            // 
            resources.ApplyResources(this.title_label, "title_label");
            this.title_label.Name = "title_label";
            // 
            // title_des_label
            // 
            resources.ApplyResources(this.title_des_label, "title_des_label");
            this.title_des_label.Name = "title_des_label";
            // 
            // time_label
            // 
            resources.ApplyResources(this.time_label, "time_label");
            this.time_label.Name = "time_label";
            // 
            // time_value_label
            // 
            resources.ApplyResources(this.time_value_label, "time_value_label");
            this.time_value_label.Name = "time_value_label";
            // 
            // wrong_msg
            // 
            resources.ApplyResources(this.wrong_msg, "wrong_msg");
            this.wrong_msg.ForeColor = System.Drawing.Color.Red;
            this.wrong_msg.Name = "wrong_msg";
            // 
            // pictureBox1
            // 
            resources.ApplyResources(this.pictureBox1, "pictureBox1");
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.TabStop = false;
            // 
            // leftTime_label
            // 
            resources.ApplyResources(this.leftTime_label, "leftTime_label");
            this.leftTime_label.Name = "leftTime_label";
            // 
            // AuthForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            resources.ApplyResources(this, "$this");
            this.Controls.Add(this.leftTime_label);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.wrong_msg);
            this.Controls.Add(this.time_value_label);
            this.Controls.Add(this.time_label);
            this.Controls.Add(this.title_des_label);
            this.Controls.Add(this.title_label);
            this.Controls.Add(this.submit_btn);
            this.Controls.Add(this.code_input);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AuthForm";
            this.TopMost = true;
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox code_input;
        private System.Windows.Forms.Button submit_btn;
        private System.Windows.Forms.Label title_label;
        private System.Windows.Forms.Label title_des_label;
        private System.Windows.Forms.Label time_label;
        private System.Windows.Forms.Label time_value_label;
        private System.Windows.Forms.Label wrong_msg;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label leftTime_label;
    }
}

