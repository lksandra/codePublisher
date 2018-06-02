@echo off

cd x64\Debug

Test_Executive.exe ..\..\ *.cpp *.h /r /f ..\..\XML_Results.xml

cd ..\..

Pause