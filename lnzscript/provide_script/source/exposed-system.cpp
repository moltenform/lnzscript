///Function:System.isAdmin
///Arguments:
///Returns:bool bIsAdmin
///Doc:Returns true if the current user has administrator privileges.
///Implementation:c++_au3
{
	CHECK_ARGS
	long nRes = AU3_IsAdmin();
	return util_LongToBool(nRes);
}

///Function:System.disableInput
///Arguments:
///Returns:
///Doc:Disables mouse and keyboard input from the user. The script can, however, still simulate most mouse and keyboard events. Note that this has different effects based on operating system. Pressing Ctrl+Alt+Del will re-enable input.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_BlockInput(1);
	return eng->nullValue();
}

///Function:System.enableInput
///Arguments:
///Returns:
///Doc:Enables mouse and keyboard input from the user after call to System.disableInput.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_BlockInput(0);
	return eng->nullValue();
}

///Function:System.windowsVersion
///Arguments:
///Returns:string strVersion
///Doc:Returns a string representing the windows version. '5.0'-Windows2000, '5.1'-WindowsXP,'6.0 Vista','5.2 Win server 2003' and so on. See msdn for more information.
///Implementation:c++_winext
{
	CHECK_ARGS
	return QScriptValue(eng, get_winapi_windows_version());
}

///Function:System.getenv
///Arguments:string strEnvironmentVariable
///Returns: string strValue
///Doc:Get environment variable, or false upon error.
///Implementation:c++_winext
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
///Implementation:c++_winext
{
	CHECK_ARGS
	return util_runExternalCommand( "rundll32.exe desk.cpl,InstallScreenSaver %l \""+strScreensaver+"\"" );
}

///Function:System.openEjectHardware
///Arguments:
///Returns:
///Doc: Opens "safely remove hardware" dialog.
///Implementation:c++_winext
{
	CHECK_ARGS
	return util_runExternalCommand( "RunDll32.exe shell32.dll,Control_RunDLL hotplug.dll");
}

///Function:System.openControlPanel
///Arguments:string strOption
///Returns:
///Doc: Opens a control panel. (To open the panel itself use File.openExplorerWindowSpecial). Options include: Keyboard[[br]]Mouse[[br]]Joystick[[br]]Multimedia[[br]]Internet Options[[br]]Add/Remove[[br]]Regional[[br]]Time[[br]]System[[br]]Display[[br]]Accessibility[[br]]Network[[br]]Power[[br]]Accounts[[br]]Security Center[[br]]Firewall[[br]]Wireless[[br]]Taskbar[[br]]Folder Options[[br]]Device Manager[[br]]Updates
///Implementation:c++_winext
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
	else return ctx->throwError("System.openControlPanel, unknown utilty. See doc.");
	
	return util_runExternalCommand( "rundll32.exe shell32.dll,Control_RunDLL "+cmd );
}

///Function:System.openUtility
///Arguments:string strOption
///Returns:
///Doc:Opens a system utility. Options include: [[br]]Disk Cleanup[[br]]Disk Management[[br]]Services[[br]]Computer Management[[br]]Administrative Tools[[br]]Event Viewer[[br]]
///Implementation:c++_qt
{
	CHECK_ARGS
	if (strOption=="Disk Cleanup") 
	{
		return util_runExternalCommand( "cleanmgr" ); 
	}
	
	// strangely enough, using cmd.exe /c services.msc seems to block. So instead use c:\windows\system32\mmc.exe c:\windows\system32\services.msc
	QString systemdir = get_winapi_special_folder_path("System");
	if (strOption=="Administrative Tools")
	{
		return util_runExternalCommand( systemdir + "\\control.exe admintools" ); // or, simply "control admintools" but control isn't in the path
	}
	
	// a problem with util_runExternalCommand? That uses au3 to run, which maybe is different than Qt's run.
	
	QString strMscFile;
	if (strOption=="Disk Management") strMscFile = "diskmgmt.msc";
	else if (strOption=="Services") strMscFile = "services.msc";
	else if (strOption=="Computer Management") strMscFile = "compmgmt.msc";
	else if (strOption=="Event Viewer") strMscFile = "eventvwr.msc"; // test on Vista. Should use wercon there instead? see previous revision
	else return ctx->throwError("System.openUtility, unknown utilty. See doc.");
	
	// return util_runExternalCommand( strMscFile ); these can't be run this way, probably because they aren't exe.
	// and for some reason, util_runExternalCommand given this will open a command console ? ?
	// so use Qt to run it, in the manner of Process.openFile
	QString realcmd = "cmd.exe /c start \"" + strMscFile + "\"";
	QProcess objProcess; objProcess.start(realcmd);
	bool bFileFound = (objProcess.error() != QProcess::FailedToStart);
	objProcess.waitForFinished(); //the cmd.exe should spawn off what we opened, so this won't actually block.
	
	return QScriptValue(eng, bFileFound);
}

//Function:System._hash
//Doc:(Exposed in String, by JavaScript).  Use Windows API to hash string. Intended for Ascii and not Unicode strings. Returns string in hexadecimal. (256 bytes = 512 characters)

// http://weseetips.com/2008/06/27/how-to-generate-the-hash-key-of-given-data/
// why I haven't done it - requires shapi lib, and there isn't a direct need for this.
// 
// Get file icon: http://weseetips.com/2008/06/03/how-to-get-the-icon-of-a-file/#comments
// Get program from extension: http://weseetips.com/2008/05/30/how-to-find-the-application-associated-with-particular-file-extension/
// 
// return string like 'a4b23a7c3d36b2452a2'
