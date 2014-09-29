@echo off

start /wait .\ServerBuild.bat
if errorlevel 1 goto ERROR_Server
start /wait .\ClientBuild.bat
if errorlevel 1 goto ERROR_Client
start /wait .\copyDll.bat
if errorlevel 1 goto ERROR_COPY
goto END

:ERROR_Server
echo.
echo build server.exe has error!
pause
goto END

:ERROR_Client
echo.
echo build client.exe has error!
pause
goto END

:ERROR_COPY
echo.
echo copy dll has error!
pause
goto END

:END
exit