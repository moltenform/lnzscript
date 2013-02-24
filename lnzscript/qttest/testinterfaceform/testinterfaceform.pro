
FORMS       =  ./testinterfaceform/testinterfaceform.ui
HEADERS     =  ./testinterfaceform/testinterfaceform.h ./provide_script/print_function.h ./provide_script/provide_script.h

SOURCES     = ./testinterfaceform/main.cpp ./testinterfaceform/testinterfaceform.cpp  \
		./provide_script/provide_script.cpp ./provide_script/provide_common.cpp ./provide_script/gen/functions_expose.cpp \
		./provide_script/gen/functions_au3.cpp \
		./provide_script/gen/functions_qt.cpp \
		./provide_script/gen/functions_winext.cpp

QT += script
LIBS += ./provide_script/autoit/libautoitx3.a