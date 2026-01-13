using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace VideoPlayerDemo
{
    /// <summary>
    /// JBNVOCX ActiveX控件的AxHost包装类
    /// 用于在WinForms中使用JBNVOCX.ocx控件
    /// </summary>
    [ComImport]
    [Guid("97197A3A-091E-488D-B5BA-58EAD9819B4C")]
    public interface IJBNVOCX
    {
        [DispId(2)]
        bool OpenServer(string strIp, int nPort, string strUserName, string strPassword);
        
        [DispId(3)]
        bool OpenChannel(int nChannel, int hVideoWnd);
        
        [DispId(67)]
        bool OpenChannelEx(int nChannel, int hVideoWnd, int nStreamType, int bShowError);
        
        [DispId(39)]
        void CloseChannel(int nChannelNo);
        
        [DispId(40)]
        void CloseServer();
        
        [DispId(31)]
        int GetChannelCount();
        
        [DispId(7)]
        bool VideoRecord(int nChannelNo, string szRootPath);
        
        [DispId(71)]
        bool VideoRecordEx(int nChannel, string szRootPath, int bOn);
        
        [DispId(11)]
        bool SnapShot(int nChannelNo);
        
        [DispId(92)]
        string SnapShotEx(int nChannel, string strPath);
        
        [DispId(33)]
        void SetShowWindows(int nWindowsMode);
        
        [DispId(8)]
        bool isConnect();
    }

    /// <summary>
    /// JBNVOCX ActiveX控件的AxHost包装器
    /// </summary>
    public class AxJBNVOCX : AxHost
    {
        private IJBNVOCX ocx;

        public AxJBNVOCX() : base("97197A3A-091E-488D-B5BA-58EAD9819B4C")
        {
        }

        protected override void AttachInterfaces()
        {
            try
            {
                ocx = (IJBNVOCX)GetOcx();
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine("AttachInterfaces error: " + ex.Message);
            }
        }

        /// <summary>
        /// 打开服务器连接
        /// </summary>
        public bool OpenServer(string ip, int port, string username, string password)
        {
            if (ocx == null) return false;
            try
            {
                return ocx.OpenServer(ip, port, username, password);
            }
            catch (Exception ex)
            {
                MessageBox.Show("连接服务器失败: " + ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
        }

        /// <summary>
        /// 打开视频通道
        /// </summary>
        public bool OpenChannel(int channel, int videoWnd)
        {
            if (ocx == null) return false;
            try
            {
                return ocx.OpenChannel(channel, videoWnd);
            }
            catch (Exception ex)
            {
                MessageBox.Show("打开通道失败: " + ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
        }

        /// <summary>
        /// 打开视频通道（扩展版本）
        /// </summary>
        public bool OpenChannelEx(int channel, int videoWnd, int streamType, bool showError)
        {
            if (ocx == null) return false;
            try
            {
                return ocx.OpenChannelEx(channel, videoWnd, streamType, showError ? 1 : 0);
            }
            catch (Exception ex)
            {
                if (showError)
                    MessageBox.Show("打开通道失败: " + ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
        }

        /// <summary>
        /// 关闭视频通道
        /// </summary>
        public void CloseChannel(int channel)
        {
            if (ocx == null) return;
            try
            {
                ocx.CloseChannel(channel);
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine("CloseChannel error: " + ex.Message);
            }
        }

        /// <summary>
        /// 关闭服务器连接
        /// </summary>
        public void CloseServer()
        {
            if (ocx == null) return;
            try
            {
                ocx.CloseServer();
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine("CloseServer error: " + ex.Message);
            }
        }

        /// <summary>
        /// 获取通道数量
        /// </summary>
        public int GetChannelCount()
        {
            if (ocx == null) return 0;
            try
            {
                return ocx.GetChannelCount();
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine("GetChannelCount error: " + ex.Message);
                return 0;
            }
        }

        /// <summary>
        /// 检查是否已连接
        /// </summary>
        public bool IsConnected()
        {
            if (ocx == null) return false;
            try
            {
                return ocx.isConnect();
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine("IsConnected error: " + ex.Message);
                return false;
            }
        }

        /// <summary>
        /// 截图
        /// </summary>
        public bool TakeSnapshot(int channel)
        {
            if (ocx == null) return false;
            try
            {
                return ocx.SnapShot(channel);
            }
            catch (Exception ex)
            {
                MessageBox.Show("截图失败: " + ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
        }

        /// <summary>
        /// 截图（扩展版本）
        /// </summary>
        public string TakeSnapshotEx(int channel, string savePath)
        {
            if (ocx == null) return null;
            try
            {
                return ocx.SnapShotEx(channel, savePath);
            }
            catch (Exception ex)
            {
                MessageBox.Show("截图失败: " + ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return null;
            }
        }

        /// <summary>
        /// 设置显示窗口模式 (1=单画面, 4=四画面, 9=九画面等)
        /// </summary>
        public void SetWindowMode(int mode)
        {
            if (ocx == null) return;
            try
            {
                ocx.SetShowWindows(mode);
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine("SetWindowMode error: " + ex.Message);
            }
        }

        /// <summary>
        /// 录像
        /// </summary>
        public bool StartRecording(int channel, string savePath)
        {
            if (ocx == null) return false;
            try
            {
                return ocx.VideoRecordEx(channel, savePath, 1);
            }
            catch (Exception ex)
            {
                MessageBox.Show("录像失败: " + ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
        }

        /// <summary>
        /// 停止录像
        /// </summary>
        public bool StopRecording(int channel)
        {
            if (ocx == null) return false;
            try
            {
                return ocx.VideoRecordEx(channel, "", 0);
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine("StopRecording error: " + ex.Message);
                return false;
            }
        }
    }
}
