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
            this.code_input.Font = new System.Drawing.Font("Arial", 9.5F);
            this.code_input.Location = new System.Drawing.Point(12, 82);
            this.code_input.Name = "code_input";
            this.code_input.Size = new System.Drawing.Size(406, 22);
            this.code_input.TabIndex = 0;
            this.code_input.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // submit_btn
            // 
            this.submit_btn.Location = new System.Drawing.Point(305, 145);
            this.submit_btn.Name = "submit_btn";
            this.submit_btn.Size = new System.Drawing.Size(113, 27);
            this.submit_btn.TabIndex = 1;
            this.submit_btn.Text = "Submit";
            this.submit_btn.UseVisualStyleBackColor = true;
            this.submit_btn.Click += new System.EventHandler(this.submit_btn_Click);
            // 
            // title_label
            // 
            this.title_label.AutoSize = true;
            this.title_label.Font = new System.Drawing.Font("Arial", 14F);
            this.title_label.Location = new System.Drawing.Point(13, 13);
            this.title_label.Name = "title_label";
            this.title_label.Size = new System.Drawing.Size(202, 22);
            this.title_label.TabIndex = 2;
            this.title_label.Text = "Autherication Required";
            // 
            // title_des_label
            // 
            this.title_des_label.AutoSize = true;
            this.title_des_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.title_des_label.Location = new System.Drawing.Point(12, 50);
            this.title_des_label.Name = "title_des_label";
            this.title_des_label.Size = new System.Drawing.Size(260, 17);
            this.title_des_label.TabIndex = 3;
            this.title_des_label.Text = "Enter OTP Code from registered phone.";
            // 
            // time_label
            // 
            this.time_label.AutoSize = true;
            this.time_label.Font = new System.Drawing.Font("Arial", 8.5F);
            this.time_label.Location = new System.Drawing.Point(11, 152);
            this.time_label.Name = "time_label";
            this.time_label.Size = new System.Drawing.Size(93, 15);
            this.time_label.TabIndex = 4;
            this.time_label.Text = "Machine Time : ";
            // 
            // time_value_label
            // 
            this.time_value_label.AutoSize = true;
            this.time_value_label.Location = new System.Drawing.Point(113, 152);
            this.time_value_label.Name = "time_value_label";
            this.time_value_label.Size = new System.Drawing.Size(0, 14);
            this.time_value_label.TabIndex = 5;
            // 
            // wrong_msg
            // 
            this.wrong_msg.AutoSize = true;
            this.wrong_msg.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.wrong_msg.ForeColor = System.Drawing.Color.Red;
            this.wrong_msg.Location = new System.Drawing.Point(10, 120);
            this.wrong_msg.Name = "wrong_msg";
            this.wrong_msg.Size = new System.Drawing.Size(190, 15);
            this.wrong_msg.TabIndex = 6;
            this.wrong_msg.Text = "Autherication code does not valid.";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(366, 13);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(50, 55);
            this.pictureBox1.TabIndex = 7;
            this.pictureBox1.TabStop = false;
            // 
            // leftTime_label
            // 
            this.leftTime_label.AutoSize = true;
            this.leftTime_label.Font = new System.Drawing.Font("Arial", 8.5F);
            this.leftTime_label.Location = new System.Drawing.Point(12, 178);
            this.leftTime_label.Name = "leftTime_label";
            this.leftTime_label.Size = new System.Drawing.Size(205, 15);
            this.leftTime_label.TabIndex = 8;
            this.leftTime_label.Text = "Dialog will be closed in 30 seconds.";
            // 
            // AuthForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(432, 203);
            this.Controls.Add(this.leftTime_label);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.wrong_msg);
            this.Controls.Add(this.time_value_label);
            this.Controls.Add(this.time_label);
            this.Controls.Add(this.title_des_label);
            this.Controls.Add(this.title_label);
            this.Controls.Add(this.submit_btn);
            this.Controls.Add(this.code_input);
            this.Font = new System.Drawing.Font("Arial", 8.25F);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AuthForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "RDOTP";
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

