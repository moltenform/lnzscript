

CONFIG += console

HEADERS     =  ./testinterfaceconsole/testinterfaceconsole.h
SOURCES     = ./testinterfaceconsole/main.cpp ./testinterfaceconsole/testinterfaceconsole.cpp  \
		./provide_script/provide_script.cpp ./provide_script/provide_common.cpp ./provide_script/functions_expose.cpp \
		./provide_script/functions_au3.cpp \
		./provide_script/functions_nircmd.cpp \
		./provide_script/functions_qt.cpp


QT += script
LIBS += ./provide_script/autoit/libautoitx3.a
