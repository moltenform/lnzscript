#include "provide_common.h"

#include <QtScript>
#include "autoit/AutoIt3.h"




namespace launchorz_functions
{
	void util_au3init()
	{
		AU3_Init();
	}
	
	void util_SetAU3PixelRelativeCoords(bool bRelative)
	{
		if (bRelative) AU3_AutoItSetOption("PixelCoordMode",0);
		else AU3_AutoItSetOption("PixelCoordMode",1);
	}
	void util_SetAU3MouseRelativeCoords(bool bRelative)
	{
		if (bRelative) AU3_AutoItSetOption("MouseCoordMode",0);
		else AU3_AutoItSetOption("MouseCoordMode",1); //relative coords to the active window, not the client area 
	}
	void util_SetAU3CaretRelativeCoords(bool bRelative)
	{
		if (bRelative) AU3_AutoItSetOption("CaretCoordMode",0);
		else AU3_AutoItSetOption("CaretCoordMode",1); //relative coords to the active window, not the client area 
	}
	
	QString util_AU3KeyboardCommandsReplacement(QString strKeySequence)
	{
		strKeySequence.replace("+","{+}",Qt::CaseSensitive); strKeySequence.replace("!","{!}",Qt::CaseSensitive); strKeySequence.replace("#","{#}",Qt::CaseSensitive); strKeySequence.replace("^","{^}",Qt::CaseSensitive);
		strKeySequence.replace("<Alt>","!",Qt::CaseInsensitive); strKeySequence.replace("<Shift>","+",Qt::CaseInsensitive); strKeySequence.replace("<Control>","^",Qt::CaseInsensitive); strKeySequence.replace("<Cntrl>","^",Qt::CaseInsensitive); strKeySequence.replace("<Win>","#",Qt::CaseInsensitive);
		return strKeySequence;
	}
	QScriptValue util_QListToScriptArray(QScriptEngine *eng, QList<QString>& results)
	{
		QScriptValue ar = eng->newArray(results.count());
		for (int i=0; i<results.count(); i++)
			ar.setProperty(i, QScriptValue(eng, results[i]));
		return ar;
	}
	
	QScriptValue util_runExternalCommandWithEngine(QScriptEngine *eng, QString strCmd)
	{
		// consider using Au3 for this... not sure what is best.
		/* // this version is synchronous, probably not what people want.
		QProcess objProcess;
		objProcess.start(strCmd);
		objProcess.waitForFinished();*/
		
		// Note, asynchronous
		AU3_Run(QStrToCStr(strCmd), "",1); //returns pid, but not important
		return QScriptValue(eng, (AU3_error()==0) ? true : false);
	}
	
	

	// previous to calling this, use.setFilter to set a filter.
	QScriptValue util_ListDirectoryEntries(QScriptContext *ctx, QScriptEngine *eng, QDir objDir, QString strSortBy)
	{
		//get the sorting
		QString strSortKey = strSortBy.toLower(); //normalize by case
		QFlags<QDir::SortFlag> flags = 0;
		if (strSortKey=="unsorted") flags = QDir::Unsorted; 
		else if (strSortKey=="name") flags = QDir::Name; 
		else if (strSortKey=="time") flags = QDir::Time; 
		else if (strSortKey=="size") flags = QDir::Size | QDir::Reversed;  //by default, sorts from largest down. We reverse this to make it more consistent (imo)
		else if (strSortKey=="type") flags = QDir::Type; 
		else return ctx->throwError("File.dirListFiles(). Unsupported sort flag. Use one of unsorted/name/time/size/type");
		
		objDir.setSorting(flags);
		QFileInfoList list = objDir.entryInfoList();
		QScriptValue ar = eng->newArray(list.size());
		// It would be more efficient if we used the fileInfo object to also return the information, since it was computed here anyways...
		for (int i = 0; i < list.size(); i++)
		{
			QFileInfo fileInfo = list.at(i);
			ar.setProperty(i, QScriptValue(eng, fileInfo.fileName()));
		}
		return ar;
	}
	
	// Returns base directory (one containing the exe), with following backslash.
	QString get_base_directory()
	{
		// use windows api to get my path.
		TCHAR tbuffer[512];
		GetModuleFileName(NULL, tbuffer, 512);
		char buffer[512];
		wcstombs(buffer, tbuffer, 512);
		QString str(buffer);
		QFileInfo info(str); 
		QString strResult = info.absolutePath(); //get the dir from the path
		return (strResult.endsWith("\\")) ? strResult : strResult + "\\";
	}
	
	QString util_nircmd_directory, util_wincommondlg_directory;
	void util_nircmd_init()
	{
		QString strBaseDir = get_base_directory();
		util_nircmd_directory = strBaseDir + "nircmd.exe";
		util_wincommondlg_directory = strBaseDir + "WinCommonDialog.exe";
		if (! QFileInfo(util_nircmd_directory).exists()) { puts("Cannot find nircmd.exe."); abort(); }
		if (! QFileInfo(util_wincommondlg_directory).exists()) { puts("Cannot find WinCommonDialog.exe."); abort(); }
	}
	
	// kind of weird to have reference parameters having default arguments, but this apparently implicitly creates a QString of length 0, which can be tested with str==0.
	QScriptValue util_externalCmd(int program, QScriptContext *ctx, QScriptEngine *eng,  const QString& strCommand, const QString& arg1 /* =0*/, const QString& arg2, const QString& arg3, const QString& arg4, const QString& arg5, const QString& arg6)
	{
		if (util_nircmd_directory=="") return ctx->throwError("The file nircmd.exe could not be found. Place it in a location that can be found by LnzScript in order to use this function.");
		QString strExecutable;
		if (program == G_Nircmd) strExecutable = util_nircmd_directory + " ";
		else if (program == G_WinCommonDialog) strExecutable = util_wincommondlg_directory + " ";
		else return ctx->throwError("Internal error. Bad external command.");
		
		strExecutable += strCommand; // note unescaped! So, if everything is preformatted you can put it here - but make sure no unescaped quotes
		if (arg1!=0) strExecutable += " \""+util_external_escape(arg1)+"\""; //replace " with \", to escape quotes
		if (arg2!=0) strExecutable += " \""+util_external_escape(arg2)+"\"";
		if (arg3!=0) strExecutable += " \""+util_external_escape(arg3)+"\"";
		if (arg4!=0) strExecutable += " \""+util_external_escape(arg4)+"\"";
		if (arg5!=0) strExecutable += " \""+util_external_escape(arg5)+"\"";
		if (arg6!=0) strExecutable += " \""+util_external_escape(arg6)+"\"";
		
		// now do a "run and wait" (synchronous)
		long nStatus = AU3_RunWait(QStrToCStr(strExecutable), "",1); //default working directory, flag of 1
		if (program == G_Nircmd)
		{
			return (nStatus==0) ? QScriptValue(eng, true) : QScriptValue(eng, false); // "NirCmd now returns a non-zero value on error."
		}
		else if (program == G_WinCommonDialog)
		{
			return QScriptValue(eng, (int) nStatus); // What is nice is that WinCommonDialog actually returns its result through the return code. Nice.
		}
		else return ctx->throwError("Internal error. Bad external command.");
	}
	
	
/*
	There are 5 different ways to pass in a way to specify a window.
	'Untitled'			Match starting with Untitled

	'"Untitled - Notepad"'		Match exact string

	'%Untitled%'			Match windows with part of string

	''				Empty string - currently active window

	{'title':'hello', 'class':'Notepad', 'instance':1}		Set all of these parameters
	
	for a title starting and ending with quotes, use {'title':'"literal quotes"'}
*/
	QString util_Au3WindowGetTextParamFromObj(QScriptValue& val)
	{
		if (val.isObject() && !val.isFunction())
		{
			QScriptValueIterator iter(val);
			while (iter.hasNext())
			{
				iter.next();
				QString strName = iter.name();
				if (QString::compare(strName, "TEXT", Qt::CaseInsensitive)==0)
					return iter.value().toString();
			}
		}
		return QString("");
	}
	
	QString util_Au3WindowParseAndSetMode(QScriptValue& val)
	{
		if (val.isString())
		{
			QString str = val.toString();
			if (str == "")						// Match currently active window
			{
				AU3_AutoItSetOption("WinTitleMatchMode",4);
				return QString("[ACTIVE]");
			}
			else if (str.startsWith('"') && str.endsWith('"'))	// Match exact string
			{
				AU3_AutoItSetOption("WinTitleMatchMode",3);
				return str.mid(1, str.length()-2); //strip off "
			}
			else if (str.startsWith('%') && str.endsWith('%'))	// Match as substring
			{
				AU3_AutoItSetOption("WinTitleMatchMode",2);
				return str.mid(1, str.length()-2); //strip off %
			}
			else		//normal match - Matches partial titles from the start.
			{
				AU3_AutoItSetOption("WinTitleMatchMode",1);
				return str;
			}
		}
		else if (val.isObject() && !val.isFunction())
		{
			QScriptValueIterator iter(val);
			if (!(iter.hasNext()))
				return NULL; //empty object, {}, invalid
			
			QString strResult("[");
			while (iter.hasNext())
			{
				iter.next();
				
				QString strName = iter.name();
				if (QString::compare(strName, "TEXT", Qt::CaseInsensitive)==0) // This parameter will be handled by util_Au3WindowGetTextParamFromObj - don't include it here
					continue;
				
				else if (QString::compare(strName, "TITLE", Qt::CaseInsensitive)==0) strResult.append("TITLE");
				else if (QString::compare(strName, "CLASS", Qt::CaseInsensitive)==0) strResult.append("CLASS");
				else if (QString::compare(strName, "REGEXPTITLE", Qt::CaseInsensitive)==0) strResult.append("REGEXPTITLE");
				else if (QString::compare(strName, "REGEXPCLASS", Qt::CaseInsensitive)==0) strResult.append("REGEXPCLASS");
				else if (QString::compare(strName, "INSTANCE", Qt::CaseInsensitive)==0) strResult.append("INSTANCE");
				else if (QString::compare(strName, "HANDLE", Qt::CaseInsensitive)==0) strResult.append("HANDLE");
				//else return NULL;
				else strResult.append(strName); // be lenient, accept bad values
				
				strResult.append(":");
				strResult.append( iter.value().toString().replace(";",";;",Qt::CaseSensitive) );
				
				if (iter.hasNext())
					strResult.append(";");
			}
			strResult.append("]");
			
			// Set mode
			AU3_AutoItSetOption("WinTitleMatchMode",4);
			return strResult;
		}
		else return NULL;
	}
	
	QString get_winapi_windows_version()
	{
		OSVERSIONINFO osvi; ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osvi);
		
		QString ret; ret.sprintf("%d.%d", (int) osvi.dwMajorVersion , (int)osvi.dwMinorVersion);
		return ret;
	}
	
	// Returns special folder path.  Returns "" if not a special folder name.
	QString get_winapi_special_folder_path(QString strName)
	{
		int cslid;
		if (strName=="Application Data") cslid = CSIDL_APPDATA;
		else if (strName=="Application Data All Users") cslid = CSIDL_COMMON_APPDATA;
		else if (strName=="Cookies") cslid = CSIDL_COOKIES;
		else if (strName=="Desktop") cslid = CSIDL_DESKTOPDIRECTORY; //note DesktopDirectory not Desktop
		else if (strName=="Favorites") cslid = CSIDL_FAVORITES;
		else if (strName=="Application Data Local Settings") cslid = CSIDL_LOCAL_APPDATA;
		else if (strName=="My Documents") cslid = CSIDL_PERSONAL;
		//else if (strName=="My Music") cslid = CSIDL_MYMUSIC;
		else if (strName=="My Pictures") cslid = CSIDL_MYPICTURES;
		//else if (strName=="My Video") cslid = CSIDL_MYVIDEO;
		else if (strName=="Program Files") cslid = CSIDL_PROGRAM_FILES;
		else if (strName=="Program Files Common") cslid = CSIDL_PROGRAM_FILES_COMMON;
		else if (strName=="Recent Documents") cslid = CSIDL_RECENT;
		else if (strName=="Start Menu") cslid = CSIDL_STARTMENU;
		else if (strName=="Startup Items") cslid = CSIDL_STARTUP;
		else if (strName=="System") cslid = CSIDL_SYSTEM;
		else if (strName=="Windows") cslid = CSIDL_WINDOWS;
		else return "";
		
		// use windows api to get path.
		TCHAR tbuffer[512];
		SHGetSpecialFolderPath(NULL, tbuffer, cslid, false);
		char buffer[512];
		wcstombs(buffer, tbuffer, 512);
		
		return QString(buffer);
	}
}
