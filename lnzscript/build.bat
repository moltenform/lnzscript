@echo off
IF NOT EXIST Makefile GOTO notqmade 
@echo on

:: Run python scripts to generate c++
c:\python25\python .\provide_script\source\script_createcpp.py .\provide_script\source

:: run make
make

:notqmade
@echo off
echo No makefile. You probably need to run something like "qmake testinterfaceconsole.pro"
echo Read "building.txt"for more information.
echo (Quitting)