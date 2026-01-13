namespace TestC_
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button_Search = new System.Windows.Forms.Button();
            this.button_addface = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button_Search
            // 
            this.button_Search.Location = new System.Drawing.Point(493, 56);
            this.button_Search.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_Search.Name = "button_Search";
            this.button_Search.Size = new System.Drawing.Size(117, 42);
            this.button_Search.TabIndex = 0;
            this.button_Search.Text = "搜索";
            this.button_Search.UseVisualStyleBackColor = true;
            this.button_Search.Click += new System.EventHandler(this.Button_Search_Click);
            // 
            // button_addface
            // 
            this.button_addface.Location = new System.Drawing.Point(156, 56);
            this.button_addface.Name = "button_addface";
            this.button_addface.Size = new System.Drawing.Size(116, 46);
            this.button_addface.TabIndex = 1;
            this.button_addface.Text = "添加人脸";
            this.button_addface.UseVisualStyleBackColor = true;
            this.button_addface.Click += new System.EventHandler(this.Button_addface_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(711, 375);
            this.Controls.Add(this.button_addface);
            this.Controls.Add(this.button_Search);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_Search;
        private System.Windows.Forms.Button button_addface;
    }
}

