@echo off

cd .

g++ -g -o .\output\client.exe .\ClientSocket_test.cpp .\CheckInput.cpp -lwsock32 -lpthread -static -Wall
goto END

:END
pause
exit