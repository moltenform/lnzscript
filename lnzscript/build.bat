@echo off
IF NOT EXIST Makefile GOTO notqmade 
@echo on

:: Run python scripts to generate c++
c:\python25\python .\provide_script\source\script_createcpp.py .\provide_script\source

:: Run python scripts to generate JavaScript lib
c:\python25\python .\provide_script\source\script_create_std_js.py .\provide_script\source .\release

:: run make
make

:notqmade
@echo off
echo No makefile. You probably need to run something like "qmake lnzconsole.pro"
echo Read "building.txt"for more information.
echo (Quitting)