# WinForms Video Player Tutorial

## Introduction

This tutorial will guide you to create a simple desktop video player application using WinForms from scratch. The application uses the JBNVOCX ActiveX control provided by JBNVSDK to play video streams from network cameras or video servers.

[查看中文文档 (Chinese Documentation)](README_CN.md)

## Quick Start

### Prerequisites

- **Operating System**: Windows 7 or higher
- **Development Tool**: Visual Studio 2015 or higher (VS 2017/2019 recommended)
- **.NET Framework**: 4.6.1 or higher
- **JBNVSDK**: Included in the `bin` directory of this repository

### Required Files

From the `bin` directory, you need:

- `JBNVOCX.ocx` - ActiveX video player control
- `JBNVSDK.dll` - SDK core library
- `avcodec-58.dll` - Video decoding library
- `avutil-56.dll` - Video utility library
- `HW_H265dec_Win32D.dll` - H.265 decoder
- `hi_h264dec_w.dll` - H.264 decoder
- Other dependent DLL files

## Register ActiveX Control

Before using the JBNVOCX control, you must register it in the system.

### Registration Steps

1. **Open Command Prompt as Administrator**
   - Press `Win + X`
   - Select "Command Prompt (Admin)" or "Windows PowerShell (Admin)"

2. **Navigate to bin directory**
   ```cmd
   cd C:\path\to\JBNVSDK\bin
   ```

3. **Register OCX control**
   ```cmd
   regsvr32 JBNVOCX.ocx
   ```

4. **Verify successful registration**
   - You should see "DllRegisterServer in JBNVOCX.ocx succeeded"

## Using the Demo Project

### Method 1: Use the Provided Sample

1. Open `VideoPlayerDemo/VideoPlayerDemo.sln` with Visual Studio
2. Ensure all DLL files are in the bin directory
3. Press F5 to build and run

### Method 2: Create from Scratch

Follow the detailed tutorial in the Chinese documentation (README_CN.md) or refer to the source code.

## Project Structure

```
VideoPlayerDemo/
├── Program.cs                          # Application entry point
├── VideoPlayerForm.cs                  # Main form code
├── VideoPlayerForm.Designer.cs         # Form designer code
├── VideoPlayerForm.resx                # Form resource file
├── AxJBNVOCX.cs                       # ActiveX control wrapper class
├── App.config                          # Application configuration
├── VideoPlayerDemo.csproj              # Project file
└── Properties/
    ├── AssemblyInfo.cs                 # Assembly information
    ├── Resources.resx                  # Resource file
    ├── Resources.Designer.cs           # Resource designer code
    ├── Settings.settings               # Settings file
    └── Settings.Designer.cs            # Settings designer code
```

## Key Features

- **Simple UI**: Easy-to-use interface with connection parameters
- **Video Playback**: Real-time video streaming from network cameras
- **Snapshot**: Capture images from video stream
- **Error Handling**: Comprehensive error handling and user feedback
- **Resource Management**: Proper cleanup on exit

## Usage

1. Run the application
2. Enter server information:
   - Server IP: Your camera or video server IP address
   - Port: Usually 34567
   - Username: Usually "admin"
   - Password: Your device password
3. Click "Connect and Play" button
4. Video should start playing automatically

## Common Issues

### Cannot load JBNVOCX control

**Solution**: Register the ActiveX control using `regsvr32 JBNVOCX.ocx` as administrator

### Platform mismatch error during compilation

**Solution**: Set "Platform target" to **x86** in project properties

### Connection failed

**Check**:
1. IP address and port are correct
2. Username and password are correct
3. Network connectivity (use ping command)
4. Firewall settings

### Missing DLL files

**Solution**: Copy all DLL files from JBNVSDK bin directory to application directory

## Advanced Features

### Multi-screen Display

```csharp
// Single screen
videoPlayer.SetWindowMode(1);

// Four screens
videoPlayer.SetWindowMode(4);

// Nine screens
videoPlayer.SetWindowMode(9);
```

### Recording

```csharp
// Start recording
videoPlayer.StartRecording(-1, @"C:\Videos");

// Stop recording
videoPlayer.StopRecording(-1);
```

## Reference

- SDK Documentation: `JBNVSDK 帮助文档.pdf`
- C++ Sample: `JBSDKDemo` project
- C# Test Sample: `TestC#` directory

## License

Please refer to the main repository for license information.

---

**For detailed Chinese tutorial, see [README_CN.md](README_CN.md)**
