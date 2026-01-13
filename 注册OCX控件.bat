@echo off
chcp 65001 >nul
echo ========================================
echo JBNVOCX ActiveX 控件注册工具
echo ========================================
echo.
echo 此脚本将注册 JBNVOCX.ocx ActiveX 控件。
echo 请确保以管理员身份运行此脚本。
echo.
pause

cd /d "%~dp0bin"

echo.
echo 正在注册 JBNVOCX.ocx...
regsvr32 JBNVOCX.ocx

echo.
echo ========================================
echo 注册完成！
echo ========================================
echo.
echo 现在您可以运行 VideoPlayerDemo 应用程序了。
echo.
pause
