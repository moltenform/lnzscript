//Note that "string window" is not necessarily a string. It can also be an object. In CHECK_ARGS, string window is handled separately.
// By typing in "string window" this automatically creates the variables QString window and QString strText !

// See also: nircmd win 

///Function:Window.activate
///Arguments:string window
///Returns:bool bSucess
///Doc:Activates (gives focus to) a window.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_WinActivate(QStrToCStr(window), QStrToCStr(strText));
	return eng->nullValue();
}

///Function:Window.isActive
///Arguments:string window
///Returns:bool bSucess
///Doc:Checks to see if a specified window exists and is currently active.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinActive(QStrToCStr(window), QStrToCStr(strText));
	return util_LongToBool(res);
}

///Function:Window.exists
///Arguments:string window
///Returns:bool bSucess
///Doc:Checks to see if a specified window exists.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinExists(QStrToCStr(window), QStrToCStr(strText));
	return util_LongToBool(res);
}

///Function:Window.getWindowsHandle
///Arguments:string window
///Returns:string strHandleId
///Doc:Retrieves the internal handle of a window (as a string, use parseInt to convert it to a number).
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[SMALLBUFSIZE];
	AU3_WinGetHandle(QStrToCStr(window), QStrToCStr(strText), buf, SMALLBUFSIZE);
	if (AU3_error()==1) return eng->nullValue();
	else return QScriptValue(eng, QString(buf));
}
///Function:Window.getProcessId
///Arguments:string window
///Returns:string strPID
///Doc:Retrieves the process ID of a window (as a string, use parseInt to convert it to a number).
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[SMALLBUFSIZE];
	AU3_WinGetProcess(QStrToCStr(window), QStrToCStr(strText), buf, SMALLBUFSIZE);
	if (strcmp(buf,"")==0) return eng->nullValue();
	else return QScriptValue(eng, QString(buf));
}


///Function:Window.getCaretPosition
///Arguments:bool bRelativeCoords=false
///Returns:int x, int y
///Doc:Returns the coordinates of the caret in the foreground window
///Implementation:c++_au3
{
	CHECK_ARGS
	util_SetAU3CaretRelativeCoords(bRelativeCoords);
	
	QScriptValue arCoords = eng->newArray(2);
	arCoords.setProperty(0, QScriptValue(eng,(int)AU3_WinGetCaretPosX()));
	arCoords.setProperty(1, QScriptValue(eng,(int)AU3_WinGetCaretPosY()));
	if (AU3_error()==1) return eng->nullValue();
	else return arCoords;
}

///Function:Window.getPosition
///Arguments:string window
///Returns:int x, int y
///Doc:Returns the coordinates of a window. Returns negative numbers such as -32000 for minimized windows.
///Implementation:c++_au3
{
	CHECK_ARGS
	
	QScriptValue arCoords = eng->newArray(2);
	arCoords.setProperty(0, QScriptValue(eng,(int)AU3_WinGetPosX(QStrToCStr(window), QStrToCStr(strText))));
	arCoords.setProperty(1, QScriptValue(eng,(int)AU3_WinGetPosY(QStrToCStr(window), QStrToCStr(strText))));
	if (AU3_error()==1) return eng->nullValue();
	else return arCoords;
}


///Function:Window.getDimensions
///Arguments:string window, bool bOnlyClientArea=false
///Returns:int width, int height
///Doc:Returns the coordinates of the caret in the foreground window
///Example: var desktopSize = Window.getDimensions('Program Manager'); //size of desktop
///Implementation:c++_au3
{
	CHECK_ARGS
	
	QScriptValue arCoords = eng->newArray(2);
	if (bOnlyClientArea)
	{
		arCoords.setProperty(0, QScriptValue(eng,(int)AU3_WinGetClientSizeWidth(QStrToCStr(window), QStrToCStr(strText))));
		arCoords.setProperty(1, QScriptValue(eng,(int)AU3_WinGetClientSizeHeight(QStrToCStr(window), QStrToCStr(strText))));
	} else {
		arCoords.setProperty(0, QScriptValue(eng,(int)AU3_WinGetPosWidth(QStrToCStr(window), QStrToCStr(strText))));
		arCoords.setProperty(1, QScriptValue(eng,(int)AU3_WinGetPosHeight(QStrToCStr(window), QStrToCStr(strText))));
	}
	if (AU3_error()==1) return eng->nullValue();
	else return arCoords;
}

///Function:Window.close
///Arguments:string window, bool bForce=false
///Returns:bool bSucess
///Doc:Closes a window. This function sends a close message to a window, the result depends on the window (it may ask to save data, etc.). To force a window to close, specify true (be warned that this will forcibly terminate the window if it doesn't close quickly enough, so a user might not have time to respond to dialogs prompting the user to save data). If multiple windows match the criteria, the window that was most recently active is closed.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res;
	if (bForce)
		res = AU3_WinKill(QStrToCStr(window), QStrToCStr(strText));
	else
		res = AU3_WinClose(QStrToCStr(window), QStrToCStr(strText));
	return util_LongToBool(res);
}

///Function:Window.getClassList
///Arguments:string window
///Returns:string strClassList
///Doc:Retrieves the classes from a window, separated by \n (linefeed). 
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[BUFSIZE];
	AU3_WinGetClassList(QStrToCStr(window), QStrToCStr(strText), buf, BUFSIZE);
	if (AU3_error()==1) return eng->nullValue();
	else return QScriptValue(eng, QString(buf));
}

///Function:Window.isMinimized
///Arguments:string window
///Returns:bool bMinimized
///Doc:Is a given window minimized.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinGetState(QStrToCStr(window), QStrToCStr(strText));
	if (res & 16L) return QScriptValue(eng, true);
	else return QScriptValue(eng, false);
}
///Function:Window.isMaximized
///Arguments:string window
///Returns:bool bMaximized
///Doc:Is a given window maximized.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinGetState(QStrToCStr(window), QStrToCStr(strText));
	if (res & 32L) return QScriptValue(eng, true);
	else return QScriptValue(eng, false);
}

///Function:Window.getText
///Arguments:string window
///Returns:string strText
///Doc:Retrieves the text from a window. Up to 16K can be retrieved.
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[LARGEBUFSIZE];
	AU3_WinGetText(QStrToCStr(window), QStrToCStr(strText), buf, LARGEBUFSIZE);
	if (AU3_error()!=0) return eng->nullValue();
	else return QScriptValue(eng, QString(buf));
}
///Function:Window.getTitle
///Arguments:string window
///Returns:string strTitle
///Doc:Retrieves the title from a window.
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[BUFSIZE];
	AU3_WinGetTitle(QStrToCStr(window), QStrToCStr(strText), buf, BUFSIZE);
	if (AU3_error()==1) return eng->nullValue(); //test if this happens
	else return QScriptValue(eng, QString(buf));
}


///Function:Window.callMenuItem
///Arguments:string window, string strMenu, string strMenuItem, string strSubmenuItem=""
///Returns:bool bSucess
///Doc:Invokes a menu item of the window. Note that underlined menu items contain a & character to indicate the underlining. Thus, the menu item File would actually require the text "&File", and Convert would require "Con&vert". will only work on standard menus. Unfortunately, many menus in use today are actually custom written or toolbars "pretending" to be menus.
///Implementation:c++_au3
{
	CHECK_ARGS	
	long res = AU3_WinMenuSelectItem(QStrToCStr(window), QStrToCStr(strText), QStrToCStr(strMenu),QStrToCStr(strMenuItem), QStrToCStr(strSubmenuItem),"","","","","");
	return util_LongToBool(res);
}

///Function:Window.minimizeAll
///Arguments:
///Returns:
///Doc:Minimizes all windows. Use restoreAll to restore.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_WinMinimizeAll();
	return eng->nullValue();
}
///Function:Window.restoreAll
///Arguments:
///Returns:
///Doc:Restores all windows after a call to minimizeAll.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_WinMinimizeAllUndo();
	return eng->nullValue();
}


///Function:Window.resize
///Arguments:string window, int width, int height
///Returns:bool bSuccess
///Doc:Resizes a window. Has no effect on minimized windows, but works on hidden windows. If width and height are small (or negative), the window will go no smaller than 112 x 27 pixels. The window will go no larger than the size of the desktop.
///Implementation:c++_au3
{
	CHECK_ARGS
	long x = AU3_WinGetPosX(QStrToCStr(window), QStrToCStr(strText));
	long y = AU3_WinGetPosY(QStrToCStr(window), QStrToCStr(strText));
	long res = AU3_WinMove(QStrToCStr(window), QStrToCStr(strText),x,y, width, height);
	return util_LongToBool(res);
}

///Function:Window.move
///Arguments:string window, int x, int y, int width=-1, int height=-1
///Returns:bool bSuccess
///Doc:Moves a window. Negative values for x and y are allowed - you can move a window off screen. Has no effect on minimized windows. You can optionally provide a new width and height to move and resize in one step.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinMove(QStrToCStr(window), QStrToCStr(strText), x, y, width, height);
	return util_LongToBool(res);
}

///Function:Window.includeChildWindows
///Arguments:bool bInclude
///Returns:
///Doc:By default, only top-level windows are searched. Run Window.includeChildWindows(true) to be able to manipulate child windows as well.
///Implementation:c++_au3
{
	CHECK_ARGS
	if (bInclude) AU3_AutoItSetOption("WinSearchChildren",1);
	else AU3_AutoItSetOption("WinSearchChildren",0);
	return eng->nullValue();
}
///Function:Window.setAlwaysOnTop
///Arguments:string window, bool bOnTop=true
///Returns:bool bSucess
///Doc:Change a window's "Always On Top" attribute, so that it is above other windows.
///Implementation:c++_au3
{
	CHECK_ARGS	
	long res;
	if (bOnTop) res = AU3_WinSetOnTop(QStrToCStr(window), QStrToCStr(strText), 1);
	else res = AU3_WinSetOnTop(QStrToCStr(window), QStrToCStr(strText), 0);
	return util_LongToBool(res);
}

///Function:Window.maximize
///Arguments:string window
///Returns:bool bSucess
///Doc:Maximize a window. For more operations, see window.setState.
///Implementation:c++_au3
{
	CHECK_ARGS	
	long res = AU3_WinSetState(QStrToCStr(window), QStrToCStr(strText), SW_MAXIMIZE); return util_LongToBool(res);
}
///Function:Window.minimize
///Arguments:string window
///Returns:bool bSucess
///Doc:Minimize a window. For more operations, see window.setState.
///Implementation:c++_au3
{
	CHECK_ARGS	
	long res = AU3_WinSetState(QStrToCStr(window), QStrToCStr(strText), SW_MINIMIZE); return util_LongToBool(res);
}
///Function:Window.restore
///Arguments:string window
///Returns:bool bSucess
///Doc:Restores a minimized or maximized window. For more operations, see window.setState.
///Implementation:c++_au3
{
	CHECK_ARGS	
	long res = AU3_WinSetState(QStrToCStr(window), QStrToCStr(strText), SW_RESTORE); return util_LongToBool(res);
}
///Function:Window.setState
///Arguments:string window, int nFlag
///Returns:bool bSucess
///Doc:Set state of a window (e.g. maximized, minimized). Pass a flag such as WindowStyle.hide, WindowStyle.show, WindowStyle.minimize, WindowStyle.maximize, or WindowStyle.restore.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinSetState(QStrToCStr(window), QStrToCStr(strText), nFlag); return util_LongToBool(res);
}
///Function:Window.setTitle
///Arguments:string window, string strTitle
///Returns:bool bSucess
///Doc:Set title of window.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinSetTitle(QStrToCStr(window), QStrToCStr(strText), QStrToCStr(strTitle)); 
	return util_LongToBool(res);
}
///Function:Window.setTransparency
///Arguments:string window, int nTransparency
///Returns:bool bSucess
///Doc:Set transparency, from 0 to 255. On Windows XP and later.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinSetTrans(QStrToCStr(window), QStrToCStr(strText), nTransparency); 
	return util_LongToBool(res);
}

///Function:Window.wait
///Arguments:string window, int nTimeout=0
///Returns:bool bBeforeTimeout
///Doc:Pauses execution of the script until a window exists. Returns false if timed out. Polls for a window match every 250 milliseconds or so.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinWait(QStrToCStr(window), QStrToCStr(strText), nTimeout); 
	return util_LongToBool(res);
}
///Function:Window.waitUntilActive
///Arguments:string window, int nTimeout=0
///Returns:bool bBeforeTimeout
///Doc:Pauses execution of the script until a window is the active window. Returns false if timed out. Polls for a window match every 250 milliseconds or so.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinWaitActive(QStrToCStr(window), QStrToCStr(strText), nTimeout); 
	return util_LongToBool(res);
}
///Function:Window.waitUntilClosed
///Arguments:string window, int nTimeout=0
///Returns:bool bBeforeTimeout
///Doc:Pauses execution of the script until a window is closed. Returns false if timed out. Polls for a window match every 250 milliseconds or so.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinWaitClose(QStrToCStr(window), QStrToCStr(strText), nTimeout); 
	return util_LongToBool(res);
}
///Function:Window.waitUntilNotActive
///Arguments:string window, int nTimeout=0
///Returns:bool bBeforeTimeout
///Doc:Pauses execution of the script until a window is not active. Returns false if timed out. Polls for a window match every 250 milliseconds or so.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_WinWaitNotActive(QStrToCStr(window), QStrToCStr(strText), nTimeout); 
	return util_LongToBool(res);
}


///Function:Window.setDelay
///Arguments:int nMillisecondsDelay
///Returns:
///Doc:By default, scripts pause for 250 ms after each successful window-related function. This delay can be changed.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_AutoItSetOption("WinWaitDelay",nMillisecondsDelay);
	return eng->nullValue();
}

///Function:Window.getStatusbarText
///Arguments:string window, int nPart=1
///Returns:string strStatusbarText
///Doc:Attempts to read the first standard status bar on a window (Microsoft common control: msctls_statusbar32). Some programs use their own status bars or special versions of the MS common control which StatusbarGetText cannot read. For example, StatusbarText does not work on the program TextPad, but Control.getText will work. Returns null upon failure.
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[BUFSIZE];
	AU3_StatusbarGetText(QStrToCStr(window), QStrToCStr(strText),nPart, buf, BUFSIZE);
	
	if (AU3_error()==0) return QScriptValue(eng, QString(buf));
	else return eng->nullValue();
}


///Function:Window._test
///Arguments:string window
///Returns:string strResult
///Doc:Testing
///Implementation:c++_au3
{
	CHECK_ARGS	
	QString strResult;
	strResult.append(window);
	strResult.append("|");
	strResult.append(strText);
	strResult.append("|");
	return QScriptValue(eng, strResult);
}

