# Microsoft Developer Studio Project File - Name="JBSDKDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=JBSDKDemo - Win32 UDebug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JBSDKDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JBSDKDemo.mak" CFG="JBSDKDemo - Win32 UDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JBSDKDemo - Win32 UDebug" (based on "Win32 (x86) Application")
!MESSAGE "JBSDKDemo - Win32 URelease" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "JBSDKDemo - Win32 UDebug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "JBSDKDemo___Win32_UDebug"
# PROP BASE Intermediate_Dir "JBSDKDemo___Win32_UDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "UDebug"
# PROP Intermediate_Dir "UDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /D "_UNICODE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../Debug/JBSDKDemo.exe" /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"../Debug/JBSDKDemo.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "JBSDKDemo - Win32 URelease"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "JBSDKDemo___Win32_URelease"
# PROP BASE Intermediate_Dir "JBSDKDemo___Win32_URelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "URelease"
# PROP Intermediate_Dir "URelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "_UNICODE" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"../Release/JBSDKDemo.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"Bin/JBSDKDemo.exe"

!ENDIF 

# Begin Target

# Name "JBSDKDemo - Win32 UDebug"
# Name "JBSDKDemo - Win32 URelease"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DialogAudio.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogBackConnect.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogFaceManager.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogFaceModify.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogLogon.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogOcxTest.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogPlayerRemote.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogTalkback.cpp
# End Source File
# Begin Source File

SOURCE=.\jbnvocx.cpp
# End Source File
# Begin Source File

SOURCE=.\JBSDKDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\JBSDKDemo.rc
# End Source File
# Begin Source File

SOURCE=.\JBSDKDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DialogBackConnect.h
# End Source File
# Begin Source File

SOURCE=.\DialogFaceManager.h
# End Source File
# Begin Source File

SOURCE=.\DialogFaceModify.h
# End Source File
# Begin Source File

SOURCE=.\DialogLogon.h
# End Source File
# Begin Source File

SOURCE=.\DialogOcxTest.h
# End Source File
# Begin Source File

SOURCE=.\DialogPlayer.h
# End Source File
# Begin Source File

SOURCE=.\DialogPlayerRemote.h
# End Source File
# Begin Source File

SOURCE=.\DialogTalkback.h
# End Source File
# Begin Source File

SOURCE=.\jbnvocx.h
# End Source File
# Begin Source File

SOURCE=.\JBSDKDemo.h
# End Source File
# Begin Source File

SOURCE=.\JBSDKDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\Picture.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\JBSDKDemo.ico
# End Source File
# Begin Source File

SOURCE=.\JBSDKDemo.rc2
# End Source File
# End Group
# End Target
# End Project
# Section JBSDKDemo : {AAC69E14-2712-4273-8D1F-2A7AD7EC300E}
# 	2:5:Class:CJBNVOCX1
# 	2:10:HeaderFile:jbnvocx1.h
# 	2:8:ImplFile:jbnvocx1.cpp
# End Section
# Section JBSDKDemo : {97197A3A-091E-488D-B5BA-58EAD9819B4C}
# 	2:21:DefaultSinkHeaderFile:jbnvocx.h
# 	2:16:DefaultSinkClass:CJBNVOCX
# End Section
# Section JBSDKDemo : {830DF3DB-C895-42AB-B2D0-918F4D772861}
# 	2:21:DefaultSinkHeaderFile:jbnvocx.h
# 	2:16:DefaultSinkClass:CJBNVOCX
# End Section
# Section JBSDKDemo : {0A2DB877-A6BB-4BD2-A9F4-FBE4A2A8756A}
# 	2:5:Class:CJBNVOCX
# 	2:10:HeaderFile:jbnvocx.h
# 	2:8:ImplFile:jbnvocx.cpp
# End Section
