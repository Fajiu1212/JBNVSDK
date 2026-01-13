using System;
using System.Drawing;
using System.Windows.Forms;

namespace VideoPlayerDemo
{
    /// <summary>
    /// 简单的视频播放器窗体
    /// 演示如何使用JBNVOCX控件播放网络摄像头视频
    /// </summary>
    public partial class VideoPlayerForm : Form
    {
        private AxJBNVOCX videoPlayer;
        private TextBox txtServerIp;
        private TextBox txtPort;
        private TextBox txtUsername;
        private TextBox txtPassword;
        private Button btnConnect;
        private Button btnDisconnect;
        private Button btnSnapshot;
        private Label lblStatus;
        private Panel panelVideo;
        private Label lblServerIp;
        private Label lblPort;
        private Label lblUsername;
        private Label lblPassword;

        public VideoPlayerForm()
        {
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            this.SuspendLayout();

            // 窗体设置
            this.Text = "简单视频播放器 - JBNVSDK演示";
            this.Size = new Size(800, 600);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.MinimumSize = new Size(640, 480);

            // 创建控制面板
            Panel controlPanel = new Panel
            {
                Dock = DockStyle.Top,
                Height = 120,
                BackColor = Color.FromArgb(240, 240, 240)
            };
            this.Controls.Add(controlPanel);

            // 服务器IP标签和文本框
            lblServerIp = new Label
            {
                Text = "服务器IP:",
                Location = new Point(10, 15),
                AutoSize = true
            };
            controlPanel.Controls.Add(lblServerIp);

            txtServerIp = new TextBox
            {
                Location = new Point(90, 12),
                Width = 150,
                Text = "192.168.1.100"  // 默认IP
            };
            controlPanel.Controls.Add(txtServerIp);

            // 端口标签和文本框
            lblPort = new Label
            {
                Text = "端口:",
                Location = new Point(260, 15),
                AutoSize = true
            };
            controlPanel.Controls.Add(lblPort);

            txtPort = new TextBox
            {
                Location = new Point(300, 12),
                Width = 80,
                Text = "34567"  // 默认端口
            };
            controlPanel.Controls.Add(txtPort);

            // 用户名标签和文本框
            lblUsername = new Label
            {
                Text = "用户名:",
                Location = new Point(10, 45),
                AutoSize = true
            };
            controlPanel.Controls.Add(lblUsername);

            txtUsername = new TextBox
            {
                Location = new Point(90, 42),
                Width = 150,
                Text = "admin"  // 默认用户名
            };
            controlPanel.Controls.Add(txtUsername);

            // 密码标签和文本框
            lblPassword = new Label
            {
                Text = "密码:",
                Location = new Point(260, 45),
                AutoSize = true
            };
            controlPanel.Controls.Add(lblPassword);

            txtPassword = new TextBox
            {
                Location = new Point(300, 42),
                Width = 150,
                PasswordChar = '*',
                Text = ""  // 默认密码
            };
            controlPanel.Controls.Add(txtPassword);

            // 连接按钮
            btnConnect = new Button
            {
                Text = "连接并播放",
                Location = new Point(10, 75),
                Width = 100,
                Height = 30
            };
            btnConnect.Click += BtnConnect_Click;
            controlPanel.Controls.Add(btnConnect);

            // 断开按钮
            btnDisconnect = new Button
            {
                Text = "断开连接",
                Location = new Point(120, 75),
                Width = 100,
                Height = 30,
                Enabled = false
            };
            btnDisconnect.Click += BtnDisconnect_Click;
            controlPanel.Controls.Add(btnDisconnect);

            // 截图按钮
            btnSnapshot = new Button
            {
                Text = "截图",
                Location = new Point(230, 75),
                Width = 100,
                Height = 30,
                Enabled = false
            };
            btnSnapshot.Click += BtnSnapshot_Click;
            controlPanel.Controls.Add(btnSnapshot);

            // 状态标签
            lblStatus = new Label
            {
                Text = "状态: 未连接",
                Location = new Point(350, 80),
                AutoSize = true,
                ForeColor = Color.Red
            };
            controlPanel.Controls.Add(lblStatus);

            // 视频显示面板
            panelVideo = new Panel
            {
                Dock = DockStyle.Fill,
                BackColor = Color.Black
            };
            this.Controls.Add(panelVideo);

            // 创建视频播放器控件
            try
            {
                videoPlayer = new AxJBNVOCX
                {
                    Dock = DockStyle.Fill
                };
                panelVideo.Controls.Add(videoPlayer);
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    "无法加载JBNVOCX控件，请确保已正确注册JBNVOCX.ocx文件。\n\n" +
                    "注册方法：在命令行中运行：\n" +
                    "regsvr32 JBNVOCX.ocx\n\n" +
                    "错误信息: " + ex.Message,
                    "初始化错误",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error
                );
                lblStatus.Text = "状态: 控件加载失败";
            }

            this.ResumeLayout(false);
        }

        /// <summary>
        /// 连接按钮点击事件
        /// </summary>
        private void BtnConnect_Click(object sender, EventArgs e)
        {
            if (videoPlayer == null)
            {
                MessageBox.Show("视频控件未初始化", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            // 验证输入
            if (string.IsNullOrWhiteSpace(txtServerIp.Text))
            {
                MessageBox.Show("请输入服务器IP地址", "提示", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txtServerIp.Focus();
                return;
            }

            if (!int.TryParse(txtPort.Text, out int port) || port <= 0 || port > 65535)
            {
                MessageBox.Show("请输入有效的端口号 (1-65535)", "提示", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txtPort.Focus();
                return;
            }

            // 禁用控件防止重复点击
            SetControlsEnabled(false);
            lblStatus.Text = "状态: 正在连接...";
            lblStatus.ForeColor = Color.Orange;

            try
            {
                // 连接到服务器
                bool success = videoPlayer.OpenServer(
                    txtServerIp.Text,
                    port,
                    txtUsername.Text,
                    txtPassword.Text
                );

                if (success)
                {
                    // 获取通道数量
                    int channelCount = videoPlayer.GetChannelCount();
                    
                    // 打开第一个通道（通道号从0开始，-1表示自动选择）
                    bool channelOpened = videoPlayer.OpenChannel(-1, 0);

                    if (channelOpened)
                    {
                        lblStatus.Text = $"状态: 已连接 (通道数: {channelCount})";
                        lblStatus.ForeColor = Color.Green;
                        btnConnect.Enabled = false;
                        btnDisconnect.Enabled = true;
                        btnSnapshot.Enabled = true;
                    }
                    else
                    {
                        lblStatus.Text = "状态: 打开通道失败";
                        lblStatus.ForeColor = Color.Red;
                        videoPlayer.CloseServer();
                        SetControlsEnabled(true);
                    }
                }
                else
                {
                    lblStatus.Text = "状态: 连接失败";
                    lblStatus.ForeColor = Color.Red;
                    MessageBox.Show(
                        "无法连接到服务器，请检查：\n" +
                        "1. IP地址和端口是否正确\n" +
                        "2. 用户名和密码是否正确\n" +
                        "3. 网络连接是否正常\n" +
                        "4. 服务器是否在线",
                        "连接失败",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                    );
                    SetControlsEnabled(true);
                }
            }
            catch (Exception ex)
            {
                lblStatus.Text = "状态: 连接异常";
                lblStatus.ForeColor = Color.Red;
                MessageBox.Show("连接过程中发生错误: " + ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                SetControlsEnabled(true);
            }
        }

        /// <summary>
        /// 断开按钮点击事件
        /// </summary>
        private void BtnDisconnect_Click(object sender, EventArgs e)
        {
            if (videoPlayer == null) return;

            try
            {
                videoPlayer.CloseChannel(-1);
                videoPlayer.CloseServer();
                lblStatus.Text = "状态: 已断开";
                lblStatus.ForeColor = Color.Red;
                SetControlsEnabled(true);
                btnDisconnect.Enabled = false;
                btnSnapshot.Enabled = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show("断开连接时发生错误: " + ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// 截图按钮点击事件
        /// </summary>
        private void BtnSnapshot_Click(object sender, EventArgs e)
        {
            if (videoPlayer == null || !videoPlayer.IsConnected())
            {
                MessageBox.Show("请先连接到服务器", "提示", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            try
            {
                // 使用默认路径截图
                bool success = videoPlayer.TakeSnapshot(-1);
                if (success)
                {
                    MessageBox.Show("截图成功！图片已保存到默认路径。", "成功", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                else
                {
                    MessageBox.Show("截图失败", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("截图时发生错误: " + ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// 设置控件启用状态
        /// </summary>
        private void SetControlsEnabled(bool enabled)
        {
            txtServerIp.Enabled = enabled;
            txtPort.Enabled = enabled;
            txtUsername.Enabled = enabled;
            txtPassword.Enabled = enabled;
            btnConnect.Enabled = enabled;
        }

        /// <summary>
        /// 窗体关闭事件
        /// </summary>
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            if (videoPlayer != null && videoPlayer.IsConnected())
            {
                try
                {
                    videoPlayer.CloseChannel(-1);
                    videoPlayer.CloseServer();
                }
                catch { }
            }
            base.OnFormClosing(e);
        }
    }
}
