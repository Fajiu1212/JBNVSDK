using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Collections.Specialized;
using System.Net;
using System.IO;

namespace TestC_
{
    public partial class Form1 : Form
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct Point
        {
            public int x;
            public int y;
        }
        [StructLayout(LayoutKind.Explicit)]
        public struct Rect {
            [FieldOffset(0)] public int left;
            [FieldOffset(4)] public int top;
            [FieldOffset(8)] public int right;
            [FieldOffset(12)] public int bottom;
        }
        //根据路径不同，请进行调整
        [DllImport(@"D:\\ZHXNVClient\\ZHXSDKDemo\\bin\\JBNVSDK.dll")]
        extern static int JBNV_GetFaceImage(
            string strImageFile,    //原始图片（输入）
            string strFaceImage,    //截取的人脸图片（输出）
            ref Point lpInputImage, //输入图片的大小
            ref Rect lpSrcFacePos,  //输入图片的大小
            ref Rect lpDstFacePos); //原始图片中人脸位置

        [DllImport(@"D:\\ZHXNVClient\\ZHXSDKDemo\\bin\\JBNVSDK.dll")]
        extern static int JBNV_SearchServer(IntPtr hWnd, uint dwMsg);

        public Form1()
        {
            InitializeComponent();
        }

        const int VFD_ERROR_LOAD_IMAGE = -10001;    //加载图片失败

        private void Form1_Load(object sender, EventArgs e)
        {
            Rect DstFacePos = new Rect();
            Rect SrcFacePos = new Rect();
            Point pInputImage = new Point();
            int nReturn = JBNV_GetFaceImage("D:\\Doc\\明星照片女\\刘诗诗.jpg","D:\\Test.jpg",ref pInputImage,ref SrcFacePos,ref DstFacePos);
            if(nReturn == VFD_ERROR_LOAD_IMAGE)
            {

            }
        }

        public const int WM_USER = 0x0400;
        public const int WM_SEARCH_MSG = WM_USER + 0x1000;

        

        private void Button_Search_Click(object sender, EventArgs e)
        {
            JBNV_SearchServer(this.Handle, WM_SEARCH_MSG);
        }

        public struct JBNV_SERVER_MSG_DATA
        {
            public  uint dwSize;
            public  uint dwPackFlag;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
            public  char[] szIp;          //服务器Ip
            public  ushort wMediaPort;            //流端口
            public  ushort wWebPort;          //Http端口号
            public  ushort wChannelCount;     //通道数量
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public char[] szServerName;  //服务器名
            public ushort wReserved1;
            public uint dwDeviceType;     //服务器类型
            public uint dwServerVersion;  //服务器版本
            public ushort wReserved2;            //wChannelStatic 通道状态(是否视频丢失)
            public ushort wSensorStatic;     //探头状态
            public ushort wAlarmOutStatic;   //报警输出状态
            public ushort wReserved3;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
            public byte[] bMac;
            public ushort wReserved4;
            public uint bEnableDHCP;
            public uint bEnableDNS;
            public uint dwNetMask;
            public uint dwGateway;
            public uint dwDNS;
            public uint dwComputerIP;
            public uint dwSupportFunc;

            public uint bP2PStatus; //Old Name:dwCenterIpAddress
            public ushort wStreamWidth;//Old Name:dwCenterPort
            public ushort wStreamHeight;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 52)]
            public char[] csP2Pid; //Old Name:csServerNo
            public uint ipAutoStatus;//IP地址自适应状态
            public ushort wSubStreamW;
            public ushort wSubStreamH;
            public ushort wMainStreamType;//2 - H264,8 H265,
            public ushort wSubStreamType; //2 - H264,8 H265,
            public int bEncodeAudio;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public char[] csCenterIpAddress;
        };
 

        protected override void DefWndProc(ref System.Windows.Forms.Message m)
        {
            switch (m.Msg)
            {
                case WM_SEARCH_MSG:   //处理消息
                    {
                        JBNV_SERVER_MSG_DATA Msg = (JBNV_SERVER_MSG_DATA)Marshal.PtrToStructure(m.WParam, typeof(JBNV_SERVER_MSG_DATA));
                        string strIpaddr = new string(Msg.szIp);
                        strIpaddr = strIpaddr.Replace("\0", "");
                        System.Diagnostics.Debug.WriteLine(strIpaddr);
                    }
                    break;
                default:
                    base.DefWndProc(ref m);   //调用基类函数处理非自定义消息。
                    break;
            }
        }

        public const string MULTIPART_FORM_DATA = "multipart/form-data";

        public string CreateFormDataBoundary()
        {
            return "------webformdata-boundary";
        }

        public int UploadFormByMultipart(string url, string[] fileFullNames,
            NameValueCollection kVDatas = null, string method = WebRequestMethods.Http.Post, int timeOut = -1)
        {
            #region 说明
             /* 说明：multipart/form-data 方式提交文件
             *  (1) Header 一定要有 Content-Type: multipart/form-data; boundary={boundary}。
             *  (2) Header 和bod y之间由 \r\n--{boundary} 分割。
             *  (3) 表单域格式 ：Content-Disposition: form-data; name="{key}"\r\n\r\n
             *     {value}\r\n
             *     --{boundary}
             *  (4)表单域名称大小写敏感，如policy、key、file、OSSAccessKeyId、OSSAccessKeyId、Content-Disposition。
             *  (5)注意:表单域 file 必须为最后一个表单域。即必须放在最后写。
             */
            #endregion

            #region ContentType 说明
            /* 该ContentType的属性包含请求的媒体类型。分配给ContentType属性的值在请求发送Content-typeHTTP标头时替换任何现有内容。

             要清除Content-typeHTTP标头，请将ContentType属性设置为null。

             * 注意：此属性的值存储在WebHeaderCollection中。如果设置了WebHeaderCollection，则属性值将丢失。
             *  所以放置在Headers 属性之后设置
             */
            #endregion

            #region Method 说明
            /* 如果 ContentLength 属性设置为-1以外的任何值，则必须将 Method 属性设置为上载数据的协议属性。 */
            #endregion


            #region 校验

            if (fileFullNames == null || fileFullNames.Length == 0)
            {
                return -1;
            }

            List<string> lstFiles = new List<string>();
            foreach (string fileFullName in fileFullNames)
            {
                if (File.Exists(fileFullName))
                {
                    lstFiles.Add(fileFullName);
                }
            }


            #endregion

            string boundary = CreateFormDataBoundary();          // 边界符
            byte[] beginBoundaryBytes = Encoding.UTF8.GetBytes("--" + boundary + "\r\n");  // 边界符开始。【☆】右侧必须要有 \r\n 。
            byte[] endBoundaryBytes = Encoding.UTF8.GetBytes("\r\n--" + boundary + "--\r\n"); // 边界符结束。【☆】两侧必须要有 --\r\n 。
            byte[] newLineBytes = Encoding.UTF8.GetBytes("\r\n"); //换一行
            MemoryStream memoryStream = new MemoryStream();

            HttpWebRequest httpWebRequest = null;
            try
            {
                httpWebRequest = WebRequest.Create(url) as HttpWebRequest; // 创建请求
                httpWebRequest.ContentType = string.Format(MULTIPART_FORM_DATA + "; boundary={0}", boundary);
                httpWebRequest.Method = method;
                httpWebRequest.KeepAlive = true;
                httpWebRequest.Timeout = timeOut;
                httpWebRequest.UserAgent = "write by ice";

                #region 步骤1：写入键值对
                if (kVDatas != null)
                {
                    string formDataTemplate = "Content-Disposition: form-data; name=\"{0}\"\r\n\r\n" + "{1}\r\n";

                    foreach (string key in kVDatas.Keys)
                    {
                        string formItem = string.Format(formDataTemplate, key, kVDatas[key]);
                        byte[] formItemBytes = Encoding.UTF8.GetBytes(formItem);

                        memoryStream.Write(beginBoundaryBytes, 0, beginBoundaryBytes.Length); // 1.1 写入FormData项的开始边界符
                        memoryStream.Write(formItemBytes, 0, formItemBytes.Length);   // 1.2 将键值对写入FormData项中
                    }
                }
                #endregion

                #region 步骤2：写入文件(表单域 file 必须为最后一个表单域)

                const string filePartHeaderTemplate = "Content-Disposition: form-data; name=\"{0}\"; filename=\"{1}\"\r\n" +
                          "Content-Type: application/octet-stream\r\n\r\n";

                int i = 0;
                foreach (var fileFullName in lstFiles)
                {
                    FileInfo fileInfo = new FileInfo(fileFullName);
                    string fileName = fileInfo.Name;

                    string fileHeaderItem = string.Format(filePartHeaderTemplate, "image", fileName);
                    byte[] fileHeaderItemBytes = Encoding.UTF8.GetBytes(fileHeaderItem);

                    if (i > 0)
                    {
                        // 第一笔及第一笔之后的数据项之间要增加一个换行 
                        memoryStream.Write(newLineBytes, 0, newLineBytes.Length);
                    }
                    memoryStream.Write(beginBoundaryBytes, 0, beginBoundaryBytes.Length);  // 2.1 写入FormData项的开始边界符
                    memoryStream.Write(fileHeaderItemBytes, 0, fileHeaderItemBytes.Length); // 2.2 将文件头写入FormData项中

                    int bytesRead;
                    byte[] buffer = new byte[1024];

                    FileStream fileStream = new FileStream(fileFullName, FileMode.Open, FileAccess.Read);
                    while ((bytesRead = fileStream.Read(buffer, 0, buffer.Length)) != 0)
                    {
                        memoryStream.Write(buffer, 0, bytesRead);        // 2.3 将文件流写入FormData项中
                    }

                    i++;
                }

                memoryStream.Write(endBoundaryBytes, 0, endBoundaryBytes.Length);    // 2.4 写入FormData的结束边界符

                #endregion

                #region 步骤3：将表单域(内存流)写入 httpWebRequest 的请求流中，并发起请求
                httpWebRequest.ContentLength = memoryStream.Length;

                Stream requestStream = httpWebRequest.GetRequestStream();

                memoryStream.Position = 0;
                byte[] tempBuffer = new byte[memoryStream.Length];
                memoryStream.Read(tempBuffer, 0, tempBuffer.Length);
                memoryStream.Close();

                requestStream.Write(tempBuffer, 0, tempBuffer.Length);  // 将内存流中的字节写入 httpWebRequest 的请求流中
                requestStream.Close();
                #endregion

                HttpWebResponse httpWebResponse = httpWebRequest.GetResponse() as HttpWebResponse; // 获取响应
                if (httpWebResponse != null)
                {
                    //GetHeaders(ref httpResult, httpWebResponse);
                    //GetResponse(ref httpResult, httpWebResponse);
                    httpWebResponse.Close();
                }
            }
            catch (WebException webException)
            {
                System.Diagnostics.Debug.WriteLine(webException.Message);
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
            }
            finally
            {
                if (httpWebRequest != null)
                {
                    httpWebRequest.Abort();
                }
            }

            return 0;
        }
        /*
            //key=person    value={"faceId":"002","username":"测试员","idcard":"111222199909090000","sex":"1","wgId":"15768","nation":"汉","state":"1"}
            //key=image     value=...
            //key=facepos   value={"x":"10","y":"10","w":"20","h":"20"}
        */
        private void Button_addface_Click(object sender, EventArgs e)
        {
            NameValueCollection namevalue = new NameValueCollection();
            string[] fileattr = new string[1];
            fileattr[0] = "d://122217.jpg";
            namevalue.Add("person", "{\"faceId\":\"002\",\"username\":\"测试员\",\"idcard\":\"111222199909090000\",\"sex\":\"1\",\"wgId\":\"15768\",\"nation\":\"汉\",\"state\":\"1\"}");
            namevalue.Add("facepos","{\"x\":0,\"y\":0,\"w\":0,\"h\":0}");
            UploadFormByMultipart("http://172.16.6.251/person/add", fileattr, namevalue);
        }
    }
}
