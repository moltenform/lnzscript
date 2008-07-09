#define WIN32_LEAN_AND_MEAN 1
#include "Windows.h"

#ifndef RGB
#define GetRValue(c) ((BYTE)(c))
#define GetGValue(c) ((BYTE)(((WORD)(c))>>8))
#define GetBValue(c) ((BYTE)((c)>>16))
#define RGB(r,g,b) ((COLORREF)((BYTE)(r)|((BYTE)(g) << 8)|((BYTE)(b) << 16)))
#endif

#include <QtScript>
namespace launchorz_functions
{
	//QScriptValue util_LongToBool(long n);
	// When returning a long, usually 1 means success, 0 means failure
	#define util_LongToBool(n)  ((n==0)?QScriptValue(eng, false) : QScriptValue(eng, true))
	
	void util_au3init();
	
	#define QStrToCStr(s) (s).toLatin1()
	//or toAscii() ?
	
	#define QStrToCStrPointer(s) ((const char *)(s).toLatin1())
	// hack for sprintf
	
	void util_SetAU3PixelRelativeCoords(bool bRelative);
	void util_SetAU3MouseRelativeCoords(bool bRelative);
	void util_SetAU3CaretRelativeCoords(bool bRelative);
	QString util_AU3KeyboardCommandsReplacement(QString strKeySequence);
	QScriptValue util_QListToScriptArray(QScriptEngine *eng, QList<QString>& results);
	QScriptValue util_ListDirectoryEntries(QScriptContext *ctx, QScriptEngine *eng, QDir objDir, QString strSortBy);
	QString util_Au3WindowGetTextParamFromObj(QScriptValue& val);
	QString util_Au3WindowParseAndSetMode(QScriptValue& val);
	
	// define this one from functions_au3.cpp
	void AddGlobalObjects(QScriptEngine *eng);
	
	
	#define G_Nircmd 1
	#define G_WinCommonDialog 2
	#define R_Nircmd(...) (util_externalCmd(G_Nircmd,ctx,eng,false,__VA_ARGS__))
	#define R_WinCommonDialog(...) (util_externalCmd(G_WinCommonDialog,ctx,eng,false,__VA_ARGS__))
	
	extern QString util_nircmd_directory, util_wincommondlg_directory; // implemented in util_au3.cpp. Declared extern to avoid "multiple definition of"
	void util_nircmd_init();
	QScriptValue util_externalCmd(int program, QScriptContext *ctx, QScriptEngine *eng, bool preFormatted, const QString& strCommand, const QString& arg1 =0, const QString& arg2=0, const QString& arg3=0, const QString& arg4=0,const QString& arg5=0,const QString& arg6=0);
}

