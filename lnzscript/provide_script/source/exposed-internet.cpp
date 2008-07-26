

///Function:Internet.ieClearTemporary
///Arguments:string strOption
///Returns:
///Doc:Clear Internet Explorer temporary files or settings. Options are "Files" (to delete temporary internet files), "Cookies" (to clear cookies), "History" (to clear history), "Forms", "Passwords", and "All"
///Implementation:c++_qt
{
	CHECK_ARGS
	QString flag;
	
	if (strOption=="Files") flag="8";
	else if (strOption=="Cookies") flag="2";
	else if (strOption=="History") flag="1";
	else if (strOption=="Forms") flag="16";
	else if (strOption=="Passwords") flag="32";
	else if (strOption=="All") flag="255";
	else return ctx->throwError("Internet.ieClearTemporary(). Unrecognized option. See documentation.");
	
	return util_runExternalCommand("RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess "+flag);
}

///Function:Internet.ieFavorites
///Arguments:
///Returns:
///Doc:Opens Internet Explorer organize favorites dialog
///Implementation:c++_qt
{
	CHECK_ARGS
	return util_runExternalCommand("RUNDLL32.EXE shdocvw.dll,DoOrganizeFavDlg");
}

// this shouldn't be in JavaScript, but it is. Right now it is just an alias of Process.openFile

///Function:Internet.openUrl
///Arguments:string strUrl
///Returns:
///Doc:Use include('<std>') to import this function. Opens URL in the default browser.
///Implementation:Javascript
{}

