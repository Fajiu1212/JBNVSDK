# WinForms 视频播放器开发教程

## 简介

本教程将指导您从零开始使用 WinForms 创建一个简单的桌面视频播放应用程序。该应用程序使用 JBNVSDK 提供的 JBNVOCX ActiveX 控件来播放从网络摄像头或视频服务器获取的视频流。

## 目录

1. [准备工作](#准备工作)
2. [注册 ActiveX 控件](#注册-activex-控件)
3. [创建 WinForms 项目](#创建-winforms-项目)
4. [项目结构说明](#项目结构说明)
5. [核心代码解析](#核心代码解析)
6. [编译和运行](#编译和运行)
7. [常见问题](#常见问题)

---

## 准备工作

### 环境要求

- **操作系统**: Windows 7 或更高版本
- **开发工具**: Visual Studio 2015 或更高版本（推荐 Visual Studio 2017/2019）
- **.NET Framework**: 4.6.1 或更高版本
- **JBNVSDK**: 包含在本仓库的 `bin` 目录中

### 需要的文件

从本仓库的 `bin` 目录中，您需要以下文件：

- `JBNVOCX.ocx` - ActiveX 视频播放控件
- `JBNVSDK.dll` - SDK 核心库
- `avcodec-58.dll` - 视频解码库
- `avutil-56.dll` - 视频工具库
- `HW_H265dec_Win32D.dll` - H.265 解码库
- `hi_h264dec_w.dll` - H.264 解码库
- 其他依赖的 DLL 文件

---

## 注册 ActiveX 控件

在使用 JBNVOCX 控件之前，必须先在系统中注册它。

### 注册步骤

1. **以管理员身份打开命令提示符**
   - 按 `Win + X` 键
   - 选择"命令提示符(管理员)"或"Windows PowerShell(管理员)"

2. **切换到 bin 目录**
   ```cmd
   cd C:\path\to\JBNVSDK\bin
   ```
   将路径替换为您实际的 JBNVSDK bin 目录路径

3. **注册 OCX 控件**
   ```cmd
   regsvr32 JBNVOCX.ocx
   ```

4. **验证注册成功**
   - 如果看到"DllRegisterServer in JBNVOCX.ocx succeeded"消息，说明注册成功

### 注销控件（如需要）

如果需要注销控件，使用以下命令：
```cmd
regsvr32 /u JBNVOCX.ocx
```

---

## 创建 WinForms 项目

### 方法一：使用本仓库提供的示例项目

最简单的方法是直接使用本仓库 `VideoPlayerDemo` 目录中的示例项目：

1. 用 Visual Studio 打开 `VideoPlayerDemo/VideoPlayerDemo.csproj`
2. 确保所有 DLL 文件在 bin 目录中
3. 按 F5 编译并运行

### 方法二：从零开始创建（学习用）

如果您想学习如何从零开始创建，请按照以下步骤：

#### 步骤 1: 创建新项目

1. 打开 Visual Studio
2. 文件 → 新建 → 项目
3. 选择 "Windows 窗体应用(.NET Framework)"
4. 项目名称: `VideoPlayerDemo`
5. .NET Framework 版本: 4.6.1 或更高
6. 平台目标: **x86** (重要！必须是 32 位)

> **注意**: JBNVOCX.ocx 是 32 位控件，因此项目必须设置为 x86 平台。

#### 步骤 2: 设置项目平台

1. 右键点击项目 → 属性
2. 在"生成"选项卡中
3. 将"平台目标"设置为 **x86**
4. 保存设置

---

## 项目结构说明

完整的项目包含以下文件：

```
VideoPlayerDemo/
├── Program.cs                          # 程序入口点
├── VideoPlayerForm.cs                  # 主窗体代码
├── VideoPlayerForm.Designer.cs         # 窗体设计器代码
├── VideoPlayerForm.resx                # 窗体资源文件
├── AxJBNVOCX.cs                       # ActiveX 控件包装类
├── App.config                          # 应用程序配置
├── VideoPlayerDemo.csproj              # 项目文件
└── Properties/
    ├── AssemblyInfo.cs                 # 程序集信息
    ├── Resources.resx                  # 资源文件
    ├── Resources.Designer.cs           # 资源设计器代码
    ├── Settings.settings               # 设置文件
    └── Settings.Designer.cs            # 设置设计器代码
```

---

## 核心代码解析

### 1. Program.cs - 程序入口点

这是应用程序的入口点，非常简单：

```csharp
using System;
using System.Windows.Forms;

namespace VideoPlayerDemo
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new VideoPlayerForm());
        }
    }
}
```

**关键点**:
- `[STAThread]` 特性：COM 组件（如 ActiveX 控件）需要单线程单元模式
- `Application.EnableVisualStyles()`: 启用视觉样式
- `Application.Run(new VideoPlayerForm())`: 运行主窗体

### 2. AxJBNVOCX.cs - ActiveX 控件包装类

这个类是关键，它将 COM ActiveX 控件包装成 .NET 可用的类：

```csharp
[ComImport]
[Guid("97197A3A-091E-488D-B5BA-58EAD9819B4C")]
public interface IJBNVOCX
{
    // 定义控件的方法
    [DispId(2)]
    bool OpenServer(string strIp, int nPort, string strUserName, string strPassword);
    
    [DispId(3)]
    bool OpenChannel(int nChannel, int hVideoWnd);
    
    // ... 其他方法
}

public class AxJBNVOCX : AxHost
{
    private IJBNVOCX ocx;

    public AxJBNVOCX() : base("97197A3A-091E-488D-B5BA-58EAD9819B4C")
    {
    }

    // 封装的方法
    public bool OpenServer(string ip, int port, string username, string password)
    {
        if (ocx == null) return false;
        try
        {
            return ocx.OpenServer(ip, port, username, password);
        }
        catch (Exception ex)
        {
            MessageBox.Show("连接服务器失败: " + ex.Message);
            return false;
        }
    }
    
    // ... 其他封装方法
}
```

**关键点**:
- `[ComImport]` 和 `[Guid]`: 标识 COM 组件
- `AxHost`: WinForms 中用于托管 ActiveX 控件的基类
- 方法封装提供了错误处理和类型安全

### 3. VideoPlayerForm.cs - 主窗体

主窗体包含用户界面和业务逻辑：

#### 3.1 界面控件

```csharp
private AxJBNVOCX videoPlayer;      // 视频播放控件
private TextBox txtServerIp;         // 服务器 IP 输入框
private TextBox txtPort;             // 端口输入框
private TextBox txtUsername;         // 用户名输入框
private TextBox txtPassword;         // 密码输入框
private Button btnConnect;           // 连接按钮
private Button btnDisconnect;        // 断开按钮
private Button btnSnapshot;          // 截图按钮
private Label lblStatus;             // 状态标签
private Panel panelVideo;            // 视频显示面板
```

#### 3.2 连接服务器

```csharp
private void BtnConnect_Click(object sender, EventArgs e)
{
    // 1. 验证输入
    if (string.IsNullOrWhiteSpace(txtServerIp.Text))
    {
        MessageBox.Show("请输入服务器IP地址");
        return;
    }

    // 2. 连接到服务器
    bool success = videoPlayer.OpenServer(
        txtServerIp.Text,
        port,
        txtUsername.Text,
        txtPassword.Text
    );

    if (success)
    {
        // 3. 打开视频通道
        bool channelOpened = videoPlayer.OpenChannel(-1, 0);
        
        if (channelOpened)
        {
            lblStatus.Text = "状态: 已连接";
            lblStatus.ForeColor = Color.Green;
        }
    }
}
```

**参数说明**:
- `OpenServer`: 连接到视频服务器
  - `strIp`: 服务器 IP 地址
  - `nPort`: 服务器端口（通常是 34567）
  - `strUserName`: 用户名（通常是 "admin"）
  - `strPassword`: 密码

- `OpenChannel`: 打开视频通道
  - `nChannel`: 通道号（-1 表示自动选择第一个通道，0-N 表示具体通道）
  - `hVideoWnd`: 视频窗口句柄（0 表示在控件内部显示）

#### 3.3 截图功能

```csharp
private void BtnSnapshot_Click(object sender, EventArgs e)
{
    if (videoPlayer != null && videoPlayer.IsConnected())
    {
        bool success = videoPlayer.TakeSnapshot(-1);
        if (success)
        {
            MessageBox.Show("截图成功！");
        }
    }
}
```

#### 3.4 断开连接

```csharp
private void BtnDisconnect_Click(object sender, EventArgs e)
{
    if (videoPlayer != null)
    {
        videoPlayer.CloseChannel(-1);  // 关闭通道
        videoPlayer.CloseServer();     // 断开服务器
        lblStatus.Text = "状态: 已断开";
    }
}
```

#### 3.5 窗体关闭时清理

```csharp
protected override void OnFormClosing(FormClosingEventArgs e)
{
    if (videoPlayer != null && videoPlayer.IsConnected())
    {
        videoPlayer.CloseChannel(-1);
        videoPlayer.CloseServer();
    }
    base.OnFormClosing(e);
}
```

---

## 编译和运行

### 编译项目

1. 在 Visual Studio 中打开项目
2. 选择 "生成" → "生成解决方案" (或按 Ctrl+Shift+B)
3. 确保没有编译错误

### 部署应用程序

编译成功后，您需要部署以下文件：

```
YourApp/
├── VideoPlayerDemo.exe              # 您的应用程序
└── (将 bin 目录中的所有 DLL 文件复制到这里)
    ├── JBNVOCX.ocx
    ├── JBNVSDK.dll
    ├── avcodec-58.dll
    ├── avutil-56.dll
    ├── HW_H265dec_Win32D.dll
    ├── hi_h264dec_w.dll
    ├── msvcp120.dll
    ├── msvcr120.dll
    └── ... (其他 DLL)
```

### 运行应用程序

1. 确保 JBNVOCX.ocx 已注册（参见前面的注册步骤）
2. 双击 `VideoPlayerDemo.exe` 运行
3. 输入服务器信息：
   - 服务器 IP: 您的视频服务器或摄像头的 IP 地址
   - 端口: 通常是 34567
   - 用户名: 通常是 admin
   - 密码: 您设备的密码
4. 点击"连接并播放"按钮

---

## 常见问题

### Q1: 提示"无法加载 JBNVOCX 控件"

**原因**: ActiveX 控件未正确注册

**解决方案**:
1. 以管理员身份打开命令提示符
2. 切换到包含 JBNVOCX.ocx 的目录
3. 运行: `regsvr32 JBNVOCX.ocx`

### Q2: 编译时出现"平台不匹配"错误

**原因**: 项目平台设置不正确

**解决方案**:
1. 右键项目 → 属性 → 生成
2. 将"平台目标"设置为 **x86**
3. 重新生成项目

### Q3: 连接服务器失败

**可能原因**:
1. IP 地址或端口不正确
2. 用户名或密码错误
3. 网络连接问题
4. 服务器未开机或不可达

**解决方案**:
1. 检查 IP 地址和端口是否正确
2. 确认用户名和密码
3. 使用 ping 命令测试网络连接: `ping 192.168.1.100`
4. 检查防火墙设置

### Q4: 视频黑屏或无法显示

**可能原因**:
1. 通道号不正确
2. 视频流类型不支持
3. 解码库文件缺失

**解决方案**:
1. 尝试不同的通道号（0, 1, 2...）
2. 确保所有 DLL 文件都在应用程序目录中
3. 检查设备是否支持 H.264/H.265 编码

### Q5: 运行时提示缺少 DLL 文件

**原因**: 依赖的 DLL 文件未找到

**解决方案**:
将 JBNVSDK 的 bin 目录中的所有 DLL 文件复制到应用程序的运行目录

### Q6: 如何获取服务器的 IP 地址？

对于网络摄像头或 DVR/NVR 设备：
1. 查看设备的配置界面（通常可以通过显示器直接连接查看）
2. 使用设备制造商提供的搜索工具
3. 登录路由器查看 DHCP 分配的 IP 地址
4. 使用本项目中的搜索功能（参考 `TestC#` 项目中的 `JBNV_SearchServer` 方法）

---

## 扩展功能

### 添加多画面显示

使用 `SetWindowMode` 方法可以设置多画面显示：

```csharp
// 单画面
videoPlayer.SetWindowMode(1);

// 四画面
videoPlayer.SetWindowMode(4);

// 九画面
videoPlayer.SetWindowMode(9);
```

### 添加录像功能

```csharp
// 开始录像
videoPlayer.StartRecording(-1, @"C:\Videos");

// 停止录像
videoPlayer.StopRecording(-1);
```

### 添加云台控制

如果您的设备支持 PTZ（云台）控制，可以使用 SendPTZCommand 方法（需要在 AxJBNVOCX 类中添加）。

---

## 开发建议

1. **错误处理**: 始终使用 try-catch 块处理可能的异常
2. **资源释放**: 在窗体关闭时正确释放资源
3. **用户反馈**: 提供清晰的状态信息和错误提示
4. **配置保存**: 考虑保存用户的服务器配置信息
5. **日志记录**: 添加日志功能便于调试和问题追踪

---

## 总结

通过本教程，您应该能够：

1. ✅ 理解如何注册和使用 ActiveX 控件
2. ✅ 创建基本的 WinForms 应用程序
3. ✅ 使用 JBNVOCX 控件播放网络视频
4. ✅ 处理连接、断开、截图等基本操作
5. ✅ 解决常见的开发和运行问题

完整的示例代码在 `VideoPlayerDemo` 目录中，您可以直接使用或作为参考。

---

## 参考资源

- JBNVSDK 帮助文档: `JBNVSDK 帮助文档.pdf`
- C++ 示例: `JBSDKDemo` 项目
- C# 测试示例: `TestC#` 目录

---

## 技术支持

如有问题，请参考：
- SDK 帮助文档
- 现有的 C++ 和 C# 示例代码
- 设备厂商的技术支持

---

**祝您开发顺利！**
