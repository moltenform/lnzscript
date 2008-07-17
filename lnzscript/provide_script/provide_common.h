#define WIN32_LEAN_AND_MEAN 1
#define _WIN32_WINNT    0x0500
#define _WIN32_IE        0x0500
#include "Windows.h"

#ifndef RGB
#define GetRValue(c) ((BYTE)(c))
#define GetGValue(c) ((BYTE)(((WORD)(c))>>8))
#define GetBValue(c) ((BYTE)((c)>>16))
#define RGB(r,g,b) ((COLORREF)((BYTE)(r)|((BYTE)(g) << 8)|((BYTE)(b) << 16)))
#endif

#define LARGEBUFSIZE 16384
#define BUFSIZE 1024
#define SMALLBUFSIZE 64

#include "Shlobj.h"
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
	
	#define util_runExternalCommand(s) (util_runExternalCommandWithEngine(eng,s))
	QScriptValue util_runExternalCommandWithEngine(QScriptEngine *eng, QString strCmd);
	QString get_winapi_special_folder_path(QString strName);
	QString get_winapi_windows_version();
	
	#define G_Nircmd 1
	#define G_WinCommonDialog 2
	#define R_Nircmd(...) (util_externalCmd(G_Nircmd,ctx,eng,__VA_ARGS__))
	#define R_WinCommonDialog(...) (util_externalCmd(G_WinCommonDialog,ctx,eng,__VA_ARGS__))
	
	// Use these to manually provide string. Be sure to escape quotes in input with util_external_escape
	#define R_NircmdPreformatted(s_pref) (util_externalCmd(G_Nircmd,ctx,eng,s_pref))
	#define R_WinCommonDialogPreformatted(s_pref) (util_externalCmd(G_WinCommonDialog,ctx,eng,s_pref))
	#define util_external_escape(s) (QString(s).replace("\"","\\\"",Qt::CaseInsensitive))
	
	extern QString util_nircmd_directory, util_wincommondlg_directory; // implemented in provide_common.cpp. Declared extern to avoid "multiple definition of"
	QString get_base_directory();
	void util_nircmd_init();
	QScriptValue util_externalCmd(int program, QScriptContext *ctx, QScriptEngine *eng, const QString& strCommand, const QString& arg1 =0, const QString& arg2=0, const QString& arg3=0, const QString& arg4=0,const QString& arg5=0,const QString& arg6=0);
}

