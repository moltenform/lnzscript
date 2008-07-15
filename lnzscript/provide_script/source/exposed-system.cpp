///Function:System.isAdmin
///Arguments:
///Returns:bool bIsAdmin
///Doc:Returns true if the current user has administrator privileges.
{
	CHECK_ARGS
	long nRes = AU3_IsAdmin();
	return util_LongToBool(nRes);
}

///Function:System.disableInput
///Arguments:
///Returns:
///Doc:Disables mouse and keyboard input from the user. The script can, however, still simulate most mouse and keyboard events. Note that this has different effects based on operating system. Pressing Ctrl+Alt+Del will re-enable input.
{
	CHECK_ARGS
	AU3_BlockInput(1);
	return eng->nullValue();
}

///Function:System.enableInput
///Arguments:
///Returns:
///Doc:Enables mouse and keyboard input from the user after call to System.disableInput.
{
	CHECK_ARGS
	AU3_BlockInput(0);
	return eng->nullValue();
}

///Function:System.windowsVersion
///Arguments:
///Returns:string strVersion
///Doc:Returns a string representing the windows version. '5.0'-Windows2000, '5.1'-WindowsXP,'6.0 Vista','5.2 Win server 2003' and so on. See msdn for more information.
///Implementation:c++_qt
{
	CHECK_ARGS
	return QScriptValue(eng, get_winapi_windows_version());
}

///Function:System.getenv
///Arguments:string strEnvironmentVariable
///Returns: string strValue
///Doc:Get environment variable, or false upon error.
{
	CHECK_ARGS
	char * ptr;
	ptr = getenv( QStrToCStr(strEnvironmentVariable));
	if (!ptr) return QScriptValue(eng, false);
	else return QScriptValue(eng, QString(ptr));
}

///Function:System.installScreensaver
///Arguments:string strScreensaver
///Returns:
///Doc:Installs a screensaver. Tested on Windows XP.
///Implementation:c++_qt
{
	CHECK_ARGS
	return util_runExternalCommand( "rundll32.exe desk.cpl,InstallScreenSaver %l \""+strScreensaver+"\"" );
}

///Function:System.openEjectHardware
///Arguments:
///Returns:
///Doc: Opens "safely remove hardware" dialog.
///Implementation:c++_qt
{
	CHECK_ARGS
	return util_runExternalCommand( "RunDll32.exe shell32.dll,Control_RunDLL hotplug.dll");
}

///Function:System.openControlPanel
///Arguments:string strOption
///Returns:
///Doc: Opens a control panel. (To open the panel itself use File.openExplorerWindowSpecial). Options include: 
///Implementation:c++_qt
{
	CHECK_ARGS
	QString cmd;
	if (strOption=="Keyboard") cmd = "main.cpl @1";
	else if (strOption=="Mouse") cmd = "main.cpl @0";
	else if (strOption=="Joystick") cmd = "joy.cpl";
	else if (strOption=="Multimedia") cmd = "mmsys.cpl"; //mmsys.cpl,,0
	else if (strOption=="Internet Options") cmd = "inetcpl.cpl,,0";
	else if (strOption=="Add/Remove") cmd = "appwiz.cpl,,0";
	else if (strOption=="Regional") cmd = "intl.cpl,,0";
	else if (strOption=="Time") cmd = "timedate.cpl";
	else if (strOption=="System") cmd = "sysdm.cpl,,0";
	else if (strOption=="Display") cmd = "desk.cpl,,4"; //note opens to "settings"; I think that's most useful
	else if (strOption=="Accessibility") cmd = "access.cpl";
	else if (strOption=="Network") cmd = "ncpa.cpl";
	else if (strOption=="Power") cmd = "powercfg.cpl";
	else if (strOption=="Accounts") cmd = "nusrmgr.cpl";
	else if (strOption=="Security Center") cmd = "wscui.cpl";
	else if (strOption=="Firewall") cmd = "firewall.cpl";
	else if (strOption=="Wireless") cmd = "NetSetup.cpl,@0,WNSW";
	
	// unusual ones
	else if (strOption=="Taskbar")
		return util_runExternalCommand( "rundll32.exe shell32.dll,Options_RunDLL 1");
	else if (strOption=="Folder Options")
		return util_runExternalCommand( "rundll32.exe shell32.dll,Options_RunDLL 0");
	else if (strOption=="Device Manager")
		return util_runExternalCommand( "rundll32.exe devmgr.dll DeviceManager_Execute");
	else if (strOption == "Updates")
	{
		QString winver = get_winapi_windows_version();
		if (winver[0]=='5') 
			cmd = "wuaucpl.cpl"; //drops down...
		else if (winver[0]=='6')
			return util_runExternalCommand( "wuapp" );
		else 
			return ctx->throwError("System.openControlPanel, unknown windows version");
	}

	return util_runExternalCommand( "rundll32.exe shell32.dll,Control_RunDLL "+cmd );
}

///Function:System.openUtility
///Arguments:string strOption
///Returns:
///Doc:Opens a system utility. Options include: [[br]]Disk Cleanup[[br]]Disk Management[[br]]Services[[br]]Computer Management[[br]]Administrative Tools[[br]]Event Viewer[[br]]
///Implementation:c++_qt
{
	CHECK_ARGS
	QString cmd;
	if (strOption=="Disk Cleanup") cmd = "cleanmgr";
	else if (strOption=="Disk Management") cmd = "diskmgmt.msc";
	else if (strOption=="Services") cmd = "services.msc"; //need to start these with Process.openFile
	else if (strOption=="Computer Management") cmd = "compmgmt.msc";
	else if (strOption=="Administrative Tools") cmd = "control admintools";
	else if (strOption=="Event Viewer")
	{
		QString winver = get_winapi_windows_version();
		if (winver[0]=='5') cmd = "eventvwr.msc";
		else if (winver[0]=='6') cmd = "wercon";
		else return ctx->throwError("System.openUtility, unknown windows version");
	}
	return util_runExternalCommand( cmd );
}


