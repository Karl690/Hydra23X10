@echo off
net session >nul 2>&1
if %errorlevel% neq 0 (
	powershell -NoProfile -Command "Start-Process -FilePath '%~f0' -Verb RunAs"
	exit /b
)
"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -ExecutionPolicy Bypass -File "%~dp0install_name.ps1"
echo.
pause
