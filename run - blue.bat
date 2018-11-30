@echo off
tasklist /FI "IMAGENAME eq WorldModel.exe" 2>NUL | find /I /N "WorldModel.exe">NUL
if "%ERRORLEVEL%"=="0" TaskKill /F /IM WorldModel.exe
Rem Move Parsian Simurosot dll auto
echo "Hello There"
COPY Release\Parsian.dll ..\Strategy4Blue.dll
echo "Done"
START ../WorldModel.exe