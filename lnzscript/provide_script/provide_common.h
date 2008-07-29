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
	
	#define QStrToCStr(s) ((s).toLatin1())
	//or toAscii() ?
	#define IntToQStr(n) (QString("%1").arg(n))
	// note that QString(34) probably gives "34", but QString(0) gives "" and not "0"
	
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
	
	#define R_Nircmd(...) (util_externalCmdDefault(G_Nircmd,ctx,eng,__VA_ARGS__))
	#define R_WinCommonDialog(...) (util_externalCmdDefault(G_WinCommonDialog,ctx,eng,__VA_ARGS__))
	
	//util_runExternalCommand still uses old method of util_external_escape, and Au3_run. Probably should move to QProcess sometime.
	// Better to use QProcess QStringList args than this.
	#define util_external_escape(s) (QString(s).replace("\"","\\\"",Qt::CaseInsensitive))
	
	
	extern QString util_nircmd_location, util_wincommondlg_location; // implemented in provide_common.cpp. Declared extern to avoid "multiple definition of"
	QString get_base_directory();
	void util_nircmd_init();
	QScriptValue util_externalCmdDefault(unsigned int program, QScriptContext *ctx, QScriptEngine *eng,  const QString& strCommand, const QString& arg1=0, const QString& arg2=0, const QString& arg3 =0, const QString& arg4 =0, const QString& arg5 =0, const QString& arg6 =0);
	QScriptValue util_externalCmdDefault(unsigned int program, QScriptContext *ctx, QScriptEngine *eng, const QStringList& astrArgs);
	QString util_externalCmdStdout(unsigned int program, const QStringList& astrArgs);


	QScriptValue g_ExceptionWrongNumberArgs(QScriptContext *ctx, const char* functionName, int nArgument);
	QScriptValue g_ExceptionNotEnoughArgs(QScriptContext *ctx, const char* functionName, int nArguments);
	QScriptValue g_ExceptionTooManyArgs(QScriptContext *ctx, const char* functionName, int nArguments);
	QScriptValue g_ExceptionWrongTypeArg(QScriptContext *ctx, const char* functionName, int nArgument, const char* expectedType);

	extern const char* LNZTYPE_bool;
	extern const char* LNZTYPE_int;
	extern const char* LNZTYPE_string;
}

