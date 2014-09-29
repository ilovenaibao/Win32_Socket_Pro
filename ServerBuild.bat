@echo off

cd .
g++ -g -o .\output\server.exe .\ServerSocket_test.cpp .\CheckInput.cpp -lwsock32 -lpthread -static -Wall
goto END

:END
pause
exit