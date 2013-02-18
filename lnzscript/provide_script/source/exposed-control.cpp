// todo: add dlgany?
///Function:Control.dialogClickButton
///Arguments:string strExecutableName, string strWindowTitle, string strButtonNameOrId
///Returns:
///Doc:Allows you to interact with standard dialog-boxes and message-boxes of Windows. Use "" for exe name, window to refer to current dialog. Button names include yes, no, ok, cancel, retry, ignore, close, help, or provide an ID. Won't always work for non-standard dialog-boxes.
///Implementation:c++_nircmd
///Example: Control.dialogSetText('explorer.exe','run',12298,'notepad'); /*type in notepad in run dialog*/ Control.dialogClickButton('explorer.exe','run','ok');//click ok
{
	CHECK_ARGS
	return R_Nircmd("dlg", strExecutableName, strWindowTitle, "click", strButtonNameOrId);
}
// todo: shouldn't take a string here, should take id as int.
///Function:Control.dialogSetText
///Arguments:string strExecutableName, string strWindowTitle, string strFieldId, string strText
///Returns:
///Doc:Allows you to enter text into standard dialog-boxes and message-boxes of Windows. Use "" for exe name, window to refer to current dialog. Won't always work for non-standard dialog-boxes.
///Implementation:c++_nircmd
///Example: Control.dialogSetText('explorer.exe','run',12298,'notepad.exe'); /*type in notepad in run dialog*/ Control.dialogClickButton('explorer.exe','run','ok');//click ok
{
	CHECK_ARGS
	return R_Nircmd("dlg", strExecutableName, strWindowTitle, "settext", strFieldId, strText);
}


///Function:Control.click
///Arguments:string window, string strControl, string strButton="left", int nClicks=1, int x=INTDEFAULT, int y=INTDEFAULT
///Returns:bool bSuccess
///Doc:Send simulated mouse click to control. Optionally specify button, number of clicks, or position of click (defaulting to center). Specify a control in one of three ways: ClassName (e.g. "Button", or "Button3" for the third Button control), Text (e.g. "OK" or "&Next" for a button with the text Next, with underlined N), or Control ID (e.g. 350, can be found with tools like Window Info Tool / spy). 
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_ControlClick(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl), QStrToCStr(strButton), nClicks, x, y);
	return util_LongToBool(res);
}


///Function:Control.exists
///Arguments:string window, string strControl
///Returns:bool bExists
///Doc:Determines if a control exists. Specify a control in one of three ways: ClassName (e.g. "Button", or "Button3" for the third Button control), Text (e.g. "OK" or "&Next" for a button with the text Next, with underlined N), or Control ID (e.g. 350, can be found with tools like Window Info Tool / spy). 
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[SMALLBUFSIZE];
	AU3_ControlCommand(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl), "IsVisible", "",buf, SMALLBUFSIZE);
	if (AU3_error()==0) return QScriptValue(eng, true);
	else return QScriptValue(eng, false);
}

///Function:Control.sendCommand
///Arguments:string window, string strControl, string strCommand, string strArgument=""
///Returns:string strResult
///Doc:Send command to a control. Result is returned as a string, unless the value is 0 in which case it is returned as the integer 0.  strArgument is an additional argument to send to the control. Common commands include: [[br]]"IsVisible" 	Returns 1 if visible, 0 otherwise [[br]]"IsEnabled" 	Returns 1 if enabled, 0 otherwise [[br]]"ShowDropDown" 	Drops a ComboBox [[br]]"HideDropDown" 	Undrops a ComboBox [[br]]"AddString", 'string' Adds a string to the end in a ListBox or ComboBox [[br]]"DelString", occurrence Deletes a string according to occurrence in a ListBox or ComboBox [[br]]"FindString", 'string' Returns occurrence ref of the exact string in a ListBox or ComboBox [[br]]"SetCurrentSelection", occurrence Sets selection to occurrence ref in a ListBox or ComboBox [[br]]"SelectString", 'string' Sets selection according to string in a ListBox or ComboBox [[br]]"IsChecked" 	Returns 1 if Button is checked, 0 otherwise [[br]]"Check" 	Checks radio or check Button [[br]]"UnCheck" 	Unchecks radio or check Button [[br]]"GetCurrentLine" 	Returns the line # where the caret is in an Edit [[br]]"GetCurrentCol" 	Returns the column # where the caret is in an Edit [[br]]"GetCurrentSelection" 	Returns name of the currently selected item in a ListBox or ComboBox [[br]]"GetLineCount" 	Returns # of lines in an Edit [[br]]"GetLine", line# Returns text at line # passed of an Edit [[br]]"GetSelected" 	Returns selected text of an Edit [[br]]"EditPaste", 'string' Pastes the 'string' at the Edit's caret position [[br]]"CurrentTab" 	Returns the current Tab shown of a SysTabControl32 [[br]]"TabRight" 	Moves to the next tab to the right of a SysTabControl32 [[br]]"TabLeft" 	Moves to the next tab to the left of a SysTabControl32.
///Example: if (Control.sendCommand("Untitled", "Button2", "IsChecked")) print ('it is checked'); print('contents of line 3 are:'+Control.sendCommand("Untitled","Edit1", "GetLine", "3"));
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[BUFSIZE];
	AU3_ControlCommand(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl), QStrToCStr(strCommand), QStrToCStr(strArgument),buf, BUFSIZE);
	if (AU3_error()!=0) return eng->nullValue(); //if error ocurred
	else if (strcmp(buf, "0")==0) return QScriptValue(eng, 0); //If result is "0", return 0. This way conditionals should make more sense.
	else return QScriptValue(eng, QString(buf));
}

// Not implemented in the dll!
// ///Function:Control.sendCommandTreeview
// ///Arguments:string window, string strControl, string strCommand, string strArgument=""
// ///Returns:string strResult
// ///Doc:Sends a command to a TreeView32 control. Use #0 or "nodename" to refer to a node. Commands include: [[br]]"Check", "item" 	Checks an item if supported. [[br]]"Collapse", "item" 	Collapses an item to hide its children. [[br]]"Exists", "item" 	Returns 1 if an item exists, otherwise 0. [[br]]"Expand", "item" 	Expands an item to show its children. [[br]]"GetItemCount", "item" 	Returns the number of children for a selected item. [[br]]"GetSelected" 	[, UseIndex] Returns the item reference of the current selection using the text reference of the item (or index reference if UseIndex is set to 1). [[br]]"GetText", "item" 	Returns the text of an item. [[br]]"IsChecked" 	Returns the state of an item. 1:checked, 0:unchecked, -1:not a checkbox. [[br]]"Select", "item" 	Selects an item. [[br]]"Uncheck", "item" 	Unchecks an item if supported. 
// ///Example: Control.sendCommandTreeview("MyFolder","TreeView321", "Expand", "#0"); //expands first child. Control.sendCommandTreeview("MyFolder","TreeView321", "Select", "abc|#2"); //Selects the third subnode of the node labeled "abc".
// {
// 	CHECK_ARGS
// 	char buf[BUFSIZE];
// 	//AU3_ControlTreeView(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl), QStrToCStr(strCommand),QStrToCStr(strArgument),"", buf, BUFSIZE);
// 	AU3_ControlListView(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl), QStrToCStr(strCommand),QStrToCStr(strArgument),"", buf, BUFSIZE);
// 	if (AU3_error()!=0) return eng->nullValue(); //if error ocurred
// 	else if (strcmp(buf, "0")==0) return QScriptValue(eng, 0); //If result is "0", return 0. This way conditionals should make more sense.
// 	else return QScriptValue(eng, QString(buf));
// }

///Function:Control.sendCommandListview
///Arguments:string window, string strControl, string strCommand, string strArgument="", string strArgument2=""
///Returns:string strResult
///Doc:Sends a command to a ListView32 control. All indices are 0 based (first item referenced by 0 and so on). Some commands take two arguments. In a "Details" view, the "item" is the "row" and the "subitem" is the "column". Commands include: [[br]]"DeSelect", From [, To] 	Deselects one or more items. [[br]]"FindItem", "string to find" [, SubItem] 	Returns the item index of the string. Returns -1 if the string is not found. [[br]]"GetItemCount" 	Returns the number of list items. [[br]]"GetSelected" [, option]	Returns a string containing the item index of selected items. If option=0 (default) only the first selected item is returned. If option=1 then all the selected items are returned delimited by |, e.g: "0|3|4|10". If no items are selected a blank "" string is returned. [[br]]"GetSelectedCount" 	Returns the number of items that are selected. [[br]]"GetSubItemCount" 	Returns the number of subitems. [[br]]"GetText", Item, SubItem 	Returns the text of a given item/subitem. [[br]]"IsSelected", Item 	Returns 1 if the item is selected, otherwise returns 0. [[br]]"Select", From [, To] 	Selects one or more items. [[br]]"SelectAll" 		Selects all items. [[br]]"SelectClear" 	Clears the selection of all items. [[br]]"SelectInvert" 	Inverts the current selection. [[br]]"ViewChange", "view" 	Changes the current view. Valid views are "list", "details", "smallicons", "largeicons".
///Example: Control.sendCommandListview("C:\\Program Files","SysListView321","Select", "2", "5");
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[BUFSIZE];
	AU3_ControlListView(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl), QStrToCStr(strCommand),QStrToCStr(strArgument), QStrToCStr(strArgument2),buf, BUFSIZE);
	if (AU3_error()!=0) return eng->nullValue(); //if error ocurred
	else if (strcmp(buf, "0")==0) return QScriptValue(eng, 0); //If result is "0", return 0. This way conditionals should make more sense.
	else return QScriptValue(eng, QString(buf));
}

///Function:Control.setEnabled
///Arguments:string window, string strControl, bool bEnabled
///Returns:bool bSuccess
///Doc:Set if a control is enabled or disabled, i.e. "grayed out".
///Implementation:c++_au3
{
	CHECK_ARGS
	long res;
	if (bEnabled) res = AU3_ControlEnable(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl));
	else res = AU3_ControlDisable(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl));
	return util_LongToBool(res);
}
///Function:Control.setVisible
///Arguments:string window, string strControl, bool bVisible
///Returns:bool bSuccess
///Doc:Set if a control is visible or hidden.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res;
	if (bVisible) res = AU3_ControlShow(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl));
	else res = AU3_ControlHide(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl));
	return util_LongToBool(res);
}

///Function:Control.setFocus
///Arguments:string window, string strControl
///Returns:bool bSuccess
///Doc:Sets focus to a given control on a window.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_ControlFocus(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl));
	return util_LongToBool(res);
}
//There is also ControlGetFocus, but I don't really know how to use it - seemed to return "" every time.

///Function:Control.getHandle
///Arguments:string window, string strControl
///Returns:string strHandle
///Doc:Get internal handle of a control. Result is returned as a string, or null if control is not found.
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[BUFSIZE];
	AU3_ControlGetHandle(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl),buf, BUFSIZE);
	if (AU3_error()!=0) return eng->nullValue(); //if error ocurred (maybe control not found)
	else return QScriptValue(eng, QString(buf));
}

///Function:Control.getPosition
///Arguments:string window, string strControl
///Returns:int x, int y
///Doc:Gets position of control on form.
///Implementation:c++_au3
{
	CHECK_ARGS
	QScriptValue arCoords = eng->newArray(2);
	arCoords.setProperty(0, QScriptValue(eng,(int)AU3_ControlGetPosX(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl))));
	arCoords.setProperty(1, QScriptValue(eng,(int)AU3_ControlGetPosY(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl))));
	if (AU3_error()==1) return eng->nullValue();
	else return arCoords;
}

///Function:Control.getDimensions
///Arguments:string window, string strControl
///Returns:int width, int height
///Doc:Gets dimensions of control on form.
///Implementation:c++_au3
{
	CHECK_ARGS
	QScriptValue arCoords = eng->newArray(2);
	arCoords.setProperty(0, QScriptValue(eng,(int)AU3_ControlGetPosWidth(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl))));
	arCoords.setProperty(1, QScriptValue(eng,(int)AU3_ControlGetPosHeight(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl))));
	if (AU3_error()==1) return eng->nullValue();
	else return arCoords;
}

///Function:Control.resize
///Arguments:string window, string strControl, int width, int height
///Returns:bool bSuccess
///Doc:Resizes a control.
///Implementation:c++_au3
{
	CHECK_ARGS
	long x = AU3_ControlGetPosX(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl));
	long y = AU3_ControlGetPosY(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl));
	long res = AU3_ControlMove(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl),x,y, width, height);
	return util_LongToBool(res);
}

///Function:Control.move
///Arguments:string window, string strControl, int x, int y, int width=-1, int height=-1
///Returns:bool bSuccess
///Doc:Moves a control. You can optionally provide a new width and height to move and resize in one step.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_ControlMove(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl), x, y, width, height);
	return util_LongToBool(res);
}

///Function:Control.sendText
///Arguments:string window, string strControl, string strKeySequence, bool bRaw
///Returns:bool bSuccess
///Doc:Send simulated keystrokes to a control (even if the window is not active). The string can include <Shift>, <Control>, <Ctrl>, <Alt>, as well as many others: {SPACE}, {ENTER}, {BACKSPACE}, {DELETE} (see Keyboard.send). <Alt> or <Win>, and other characters may not work equivalently to Keyboard.send.
///Implementation:c++_au3
{
	CHECK_ARGS
	
	strKeySequence = util_AU3KeyboardCommandsReplacement(strKeySequence);
	int nMode = (bRaw) ? 1 : 0;
	long res = AU3_ControlSend(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl), QStrToCStr(strKeySequence), nMode);
	return util_LongToBool(res);
}

///Function:Control.getText
///Arguments:string window, string strControl
///Returns:string strControlText
///Doc:Retrieves the text from a control. Up to 16K can be retrieved.
///Implementation:c++_au3
{
	CHECK_ARGS
	char buf[LARGEBUFSIZE];
	AU3_ControlGetText(QStrToCStr(window), QStrToCStr(strText), QStrToCStr(strControl), buf, LARGEBUFSIZE);
	if (AU3_error()!=0) return eng->nullValue();
	else return QScriptValue(eng, QString(buf));
}

///Function:Control.setText
///Arguments:string window, string strControl, string strControlText
///Returns:bool bSuccess
///Doc:Sets text of control.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_ControlSetText(QStrToCStr(window), QStrToCStr(strText),QStrToCStr(strControl), QStrToCStr(strControlText));
	return util_LongToBool(res);
}






