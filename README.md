# JBNVSDK - 视频监控开发套件

## 简介

JBNVSDK 是一个用于视频监控应用开发的完整软件开发工具包（SDK）。它提供了用于连接网络摄像头、DVR/NVR 设备并进行视频播放、录像、截图等功能的接口。

## 目录结构

```
JBNVSDK/
├── bin/                          # SDK 核心文件和依赖库
│   ├── JBNVOCX.ocx              # ActiveX 视频播放控件
│   ├── JBNVSDK.dll              # SDK 核心库
│   └── ...                       # 其他依赖 DLL 文件
├── include/                      # C/C++ 头文件
├── lib/                          # C/C++ 库文件
├── JBSDKDemo/                    # C++ 完整示例项目
├── TestC#/                       # C# 基础测试项目
├── VideoPlayerDemo/              # 🆕 C# WinForms 视频播放器教程项目
└── JBNVSDK 帮助文档.pdf         # 详细 API 文档
```

## 快速开始

### 🎯 零基础 WinForms 视频播放器教程（新！）

**适合人群**: 想要从零开始学习如何用 C# WinForms 创建视频播放应用的开发者

📂 **位置**: `VideoPlayerDemo/`

**特点**:
- ✅ 完整的从零到一教程
- ✅ 详细的代码注释和说明
- ✅ 中英文文档
- ✅ 开箱即用的示例代码
- ✅ 涵盖连接、播放、截图等基本功能

**快速使用**:
1. 注册 ActiveX 控件（以管理员身份运行）:
   ```cmd
   cd bin
   regsvr32 JBNVOCX.ocx
   ```

2. 用 Visual Studio 打开 `VideoPlayerDemo/VideoPlayerDemo.sln`

3. 按 F5 编译运行

4. 输入设备 IP、端口、用户名、密码后点击"连接并播放"

**详细教程**: 
- [中文完整教程](VideoPlayerDemo/README_CN.md) 📖
- [English Tutorial](VideoPlayerDemo/README.md) 📖

---

### C++ 示例

**位置**: 根目录下的 C++ 项目文件

使用 Visual Studio 打开 `JBSDKDemo.sln` 查看完整的 C++ 示例，包含：
- 设备搜索
- 视频播放
- 云台控制
- 对讲功能
- 人脸识别
- 等等

### C# 基础示例

**位置**: `TestC#/TestC_.sln`

展示了如何在 C# 中：
- 调用 JBNVSDK.dll 的 DLL 函数
- 使用设备搜索功能
- 上传文件到设备

## 核心功能

- 🎥 **视频播放**: 支持 H.264/H.265 实时视频流
- 📷 **截图录像**: 视频截图和本地录像
- 🔍 **设备搜索**: 自动搜索局域网内的设备
- 🎮 **云台控制**: PTZ 控制（如果设备支持）
- 🎤 **对讲功能**: 双向语音对讲
- 👤 **人脸识别**: 人脸检测和识别功能
- 📺 **多画面**: 支持 1/4/9/16 画面同时显示

## 系统要求

- **操作系统**: Windows 7 或更高版本（32位或64位）
- **开发环境**: 
  - C++: Visual Studio 2012 或更高版本
  - C#: Visual Studio 2015 或更高版本，.NET Framework 4.6.1+
- **平台**: x86（32位）

> **注意**: JBNVOCX.ocx 是 32 位 ActiveX 控件，C# 项目必须设置为 x86 平台目标

## 文档

- 📘 **API 参考手册**: `JBNVSDK 帮助文档.pdf`
- 📗 **WinForms 教程**: `VideoPlayerDemo/README_CN.md`
- 📙 **网络视频获取**: `互联网获取视频.docx`

## 常见问题

### 如何注册 ActiveX 控件？

以管理员身份运行命令提示符，然后执行：
```cmd
cd path\to\JBNVSDK\bin
regsvr32 JBNVOCX.ocx
```

### C# 项目编译出错？

确保项目平台目标设置为 **x86**，而不是 AnyCPU 或 x64。

### 如何找到我的设备 IP？

1. 使用设备制造商提供的搜索工具
2. 查看路由器的 DHCP 客户端列表
3. 使用本 SDK 的设备搜索功能（参考 TestC# 示例）

### 视频无法显示？

检查：
1. ActiveX 控件是否已正确注册
2. 所有 DLL 文件是否在应用程序目录中
3. IP 地址、端口、用户名、密码是否正确
4. 网络连接是否正常

## 开发指南

### 新手推荐学习路径

1. **第一步**: 阅读 `VideoPlayerDemo/README_CN.md` 教程
2. **第二步**: 运行 `VideoPlayerDemo` 项目体验基本功能
3. **第三步**: 阅读 API 文档了解更多功能
4. **第四步**: 参考 `JBSDKDemo` (C++) 或 `TestC#` 查看高级功能
5. **第五步**: 开始开发自己的应用

### 代码示例

#### 基本视频播放（C#）

```csharp
// 1. 创建控件
AxJBNVOCX videoPlayer = new AxJBNVOCX();

// 2. 连接服务器
bool connected = videoPlayer.OpenServer("192.168.1.100", 34567, "admin", "password");

// 3. 打开视频通道
if (connected)
{
    videoPlayer.OpenChannel(-1, 0); // -1 表示自动选择第一个通道
}

// 4. 断开连接
videoPlayer.CloseChannel(-1);
videoPlayer.CloseServer();
```

完整示例请参考 `VideoPlayerDemo` 项目。

## 技术支持

- 📖 查看帮助文档: `JBNVSDK 帮助文档.pdf`
- 💻 参考示例代码: `VideoPlayerDemo/`, `TestC#/`, `JBSDKDemo`
- 🔧 查看源代码注释

## 更新日志

### 2024-01-13
- ✨ 新增 `VideoPlayerDemo` - 完整的 C# WinForms 视频播放器教程项目
- 📚 添加详细的中英文开发教程
- 🎯 提供零基础入门指南

## 许可证

请查阅相关许可协议。

---

**开始您的第一个视频应用**: [VideoPlayerDemo 教程](VideoPlayerDemo/README_CN.md) 🚀
