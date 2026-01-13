@echo off
echo ========================================
echo JBNVOCX ActiveX Control Registration
echo ========================================
echo.
echo This script will register the JBNVOCX.ocx ActiveX control.
echo Please make sure you run this script as Administrator.
echo.
pause

cd /d "%~dp0bin"

echo.
echo Registering JBNVOCX.ocx...
regsvr32 JBNVOCX.ocx

echo.
echo ========================================
echo Registration complete!
echo ========================================
echo.
echo You can now run the VideoPlayerDemo application.
echo.
pause
