
///Function:Dialog.toolTip
///Arguments:string strText, int x=AU3_INTDEFAULT, int y=AU3_INTDEFAULT
///Returns:
///Doc:Creates a tooltip anywhere on the screen. If the x and y coordinates are omitted, the tip is placed near the mouse cursor. If the coords would cause the tooltip to run off screen, it is repositioned to visible. Tooltip appears until it is cleared, until script terminates, or sometimes until it is clicked upon. You may use a linefeed character to create multi-line tooltips.
///Example: Dialog.toolTip("That's cool"); Time.sleep(500); Dialog.toolTip("");
{
	CHECK_ARGS
	
	AU3_ToolTip(QStrToCStr(strText), x, y);
	return eng->nullValue();
}

// The reason why I don't use Qt for these is that it would create a dependency on QtGui.dll, which is pretty heavy.
// So, I wrote WinCommonDialog, which wraps Windows MessageBox.

///Function:Dialog.alert
///Arguments:string strTitle, string strText
///Returns:
///Doc:Display simple message box on the screen.
///Implementation:c++_nircmd
///Example:Dialog.alert("Information","Hello, world");
{
	CHECK_ARGS
	
	return R_WinCommonDialog("info", strTitle, strText);
	// Previously used nircmd:
	// return R_Nircmd("infobox", strText, strTitle);
}

///Function:Dialog.warning
///Arguments:string strTitle, string strText
///Returns:
///Doc:Display simple message box on the screen, warning icon.
///Implementation:c++_nircmd
{
	CHECK_ARGS
	return R_WinCommonDialog("warning", strTitle, strText);
}
///Function:Dialog.error
///Arguments:string strTitle, string strText
///Returns:
///Doc:Display simple message box on the screen, error icon.
///Implementation:c++_nircmd
{
	CHECK_ARGS
	return R_WinCommonDialog("error", strTitle, strText);
}
///Function:Dialog.askYesNo
///Arguments:string strTitle, string strText
///Returns:Dialog.YES or Dialog.NO
///Doc:Display simple message box on the screen, with options for yes and no.
///Implementation:c++_nircmd
///Example:var res = Dialog.askYesNo("Status","Continue?"); if (res==Dialog.YES) doSomething(); else doSomethingElse();
{
	CHECK_ARGS
	return R_WinCommonDialog("yesno", strTitle, strText);
}
///Function:Dialog.askYesNoCancel
///Arguments:string strTitle, string strText
///Returns:Dialog.YES, Dialog.NO, Dialog.CANCEL
///Doc:Display simple message box on the screen, with options for yes, no, cancel.
///Implementation:c++_nircmd
///Example:var res = Dialog.askYesNoCancel("Warning","Replace existing file?"); if (res==Dialog.YES) doSomething(); else if (res==Dialog.NO) doSomethingElse(); else doCancel();
{
	CHECK_ARGS
	return R_WinCommonDialog("yesnocancel", strTitle, strText);
}

///Function:Dialog.askOkCancel
///Arguments:string strTitle, string strText
///Returns:Dialog.OK or Dialog.CANCEL
///Doc:Display simple message box on the screen, with options for ok and cancel.
///Implementation:c++_nircmd
///Example:var res = Dialog.askOkCancel("Status","Continue?"); if (res==Dialog.OK) doSomething(); else doSomethingElse();
{
	CHECK_ARGS
	return R_WinCommonDialog("okcancel", strTitle, strText);
}