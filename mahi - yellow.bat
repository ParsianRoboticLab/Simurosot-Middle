@echo off
tasklist /FI "IMAGENAME eq WorldModel.exe" 2>NUL | find /I /N "WorldModel.exe">NUL
if "%ERRORLEVEL%"=="0" TaskKill /F /IM WorldModel.exe
tasklist /FI "IMAGENAME eq ConsoleDebugger.exe" 2>NUL | find /I /N "ConsoleDebugger.exe">NUL
if "%ERRORLEVEL%"=="0" TaskKill /F /IM ConsoleDebugger.exe
Rem Move Parsian Simurosot dll auto
echo "Hello There"
COPY Release\Parsian.dll ..\Strategy4Yellow.dll
echo "Done"
START ..\Simurosot-master-1\ConsoleDebugger\Debug\ConsoleDebugger.exe
START ../WorldModel.exe