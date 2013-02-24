
QMAKESPEC=win32-g++-32

#compile in 32 bit, not 64, which would be win32-g++-64

CONFIG += console

HEADERS     =  ./lnzconsole/lnzconsole.h ./provide_script/provide_script.h ./provide_script/provide_common.h ./provide_script/parse_js.h
SOURCES     = ./lnzconsole/main.cpp ./lnzconsole/lnzconsole.cpp  \
		./provide_script/parse_js.cpp \
		./provide_script/provide_script.cpp ./provide_script/provide_common.cpp ./provide_script/gen/functions_expose.cpp \
		./provide_script/gen/functions_au3.cpp \
		./provide_script/gen/functions_qt.cpp \
		./provide_script/gen/functions_winext.cpp


QT += script



win32-msvc {

#if compiling with msvc, needs Shell32.lib reference.
LIBS += ./provide_script/autoit/libautoitx3.a \
		Shell32.lib


} else {
LIBS += ./provide_script/autoit/libautoitx3.a

#later, you have to copy libgcc_s_dw2-1.dll into output dir (in qt\bin)
#the dll is needed, because qt itself was built with this dependency.
#see http://www.qtcentre.org/archive/index.php/t-26617.html
}

