
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
{
	CHECK_ARGS
	
	//QString strNircmdCommand = "info \""+ strTitle + "\" \""+strText+"\"";
	//return util_wincommondlg_runCmd(ctx, eng, strNircmdCommand);
	
	// Previous used nircmd:
	// QString strNircmdCommand = "infobox \""+ strText + "\" \""+strTitle+"\"";
	// return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
}

