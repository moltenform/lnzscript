
///Function:Process.open
///Arguments:string strExecutable, string strWorkingDirectory="", int nFlag=1
///Returns:int nPID
///Doc:Opens external program. After running the requested program the script continues (this is asynchronous). To pause execution of the script until the spawned program has finished use Process.runAndWait. Optionally pass a flag such as Window.HIDE, Window.SHOW, Window.MINIMIZE, Window.MAXIMIZE, or Window.RESTORE. Returns the PID of process or null upon failure.
///Implementation:c++_au3
{
	// Seems analogous to QProcess::start 
	CHECK_ARGS
	long nRes = AU3_Run(QStrToCStr(strExecutable), QStrToCStr(strWorkingDirectory),nFlag);
	if (AU3_error()!=1)
		return QScriptValue(eng, (int) nRes);
	else
		return eng->nullValue();
}


///Function:Process.openFile
///Arguments:string strFileOrUrlOrProgram, string strWorkingDirectory=""
///Returns:
///Doc:Opens file, URL, or program with Windows shell (usually opens file in the default editor). After running the requested program the script continues (this is asynchronous).
///Implementation:c++_qt
{
	CHECK_ARGS
	QProcess objProcess;
	if (strWorkingDirectory != "") objProcess.setWorkingDirectory(strWorkingDirectory);
	
	QString strExecutable = "cmd.exe /c start \"" + strFileOrUrlOrProgram + "\"";
	objProcess.start(strExecutable);
	objProcess.waitForFinished(); //the cmd.exe should spawn off what we opened.
	return eng->nullValue();
}

///Function:Process.runAndWait
///Arguments:string strExecutable, string strWorkingDirectory="", int nFlag=1
///Returns:int nExitCode
///Doc:Opens external program. The script pauses until the program has closed. Optionally pass a flag such as Window.HIDE, Window.MINIMIZE, or Window.MAXIMIZE. Returns the exit code, or null upon failure.
///Implementation:c++_au3
{
	// Seems analogous to QProcess::execute 
	CHECK_ARGS
	long nRes = AU3_RunWait(QStrToCStr(strExecutable), QStrToCStr(strWorkingDirectory),nFlag);
	if (AU3_error()!=1)
		return QScriptValue(eng, (int) nRes);
	else
		return eng->nullValue();
}

///Function:Process.runAndRead
///Arguments:string strExecutable, string strWorkingDirectory="", int nTimeoutMilliseconds=30000
///Returns:string strOutput
///Doc:Opens external program and reads its output from stdout. The script pauses until the program has closed. Throws exception if program cannot be found, and if process times out. 
///Implementation:c++_qt
{
	// to run shell, use Process.runAndRead('cmd.exe /c dir')
	CHECK_ARGS
	QProcess objProcess;
	if (strWorkingDirectory != "") objProcess.setWorkingDirectory(strWorkingDirectory);
	objProcess.start(strExecutable);
	
	int nError = objProcess.error();
	if (nError ==0) return ctx->throwError("Process.runAndRead(): process failed to start. Either the invoked program is missing, or you may have insufficient permissions.");
	// error of 5 seems to mean ok. Other values at http://doc.trolltech.com/4.4/qprocess.html#ProcessError-enum
	
	bool bTimeout = objProcess.waitForFinished(nTimeoutMilliseconds);
	if (!bTimeout) return ctx->throwError("Process.runAndRead(): process timed out.");
	QString strOutput( objProcess.readAllStandardOutput());
	return QScriptValue(eng, strOutput);
}
///Function:Process.runCmdLine
///Arguments:string strCommandLineCommand, string strWorkingDirectory=""
///Returns:
///Doc:Execute command line command, in the style of the command prompt cmd.exe. As in the command prompt, you must use quotes if a file or directory has spaces in the name.
///Example: Process.runCmdLine('mkdir "c:\\program files\\myfolder"');
///Implementation:c++_qt
{
	CHECK_ARGS
	QProcess objProcess;
	if (strWorkingDirectory != "") objProcess.setWorkingDirectory(strWorkingDirectory);
	
	QString strExecutable = "cmd.exe /c " + strCommandLineCommand;
	objProcess.start(strExecutable);
	objProcess.waitForFinished(); //the cmd.exe should spawn off what we opened.
	return eng->nullValue();
}

// see also: nircmd closeprocess , killprocess

///Function:Process.close
///Arguments:string strExecutableName
///Returns:
///Doc:Close a process. Names are executables without the full path, e.g., "notepad.exe" or "winword.exe". If multiple processes have the same name, the one with the highest PID is terminated--regardless of how recently the process was spawned. PID is the unique number which identifies a Process. A PID is returned by the ProcessExists or Run commands.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_ProcessClose(QStrToCStr(strExecutableName));
	return eng->nullValue();
}

///Function:Process.closePID
///Arguments:int nPID
///Returns:
///Doc:Close a process. PID is the unique number which identifies a Process. A PID is returned by the ProcessExists or Run commands.
///Implementation:c++_au3
{
	CHECK_ARGS
	// Kind of undocumented, but here goes...
	QString strPid;
	strPid.sprintf("%d", nPID);
	AU3_ProcessClose(QStrToCStr(strPid));
	return eng->nullValue();	
}

///Function:Process.exists
///Arguments:string strExecutableName
///Returns:int nPID
///Doc:Checks to see if a process is running. Names are executables without the full path, e.g., "notepad.exe" or "winword.exe". Returns the PID of the process, or 0 if process does not exist.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_ProcessExists(QStrToCStr(strExecutableName));
	return QScriptValue(eng, (int) res);	
}

///Function:Process.setPriority
///Arguments:string strExecutableName, int nPriorityLevel
///Returns:bool bSuccess
///Doc:Changes the priority of a process. 0=Idle/Low, 4=High, 5=Realtime (use with caution). Levels 1 and 3 not supported on Win95/98/ME.  Returns false upon failure. Names are executables without the full path, e.g., "notepad.exe" or "winword.exe". 
///Implementation:c++_au3
{
	CHECK_ARGS
	long nRes = AU3_ProcessSetPriority(QStrToCStr(strExecutableName),nPriorityLevel);
	return util_LongToBool(nRes);
}

///Function:Process.waitUntilOpen
///Arguments:string strExecutableName, int nTimeout=0
///Returns:bool bSuccess
///Doc:Wait until process is open. Optional parameter nTimeout specifies how long to wait (default is to wait indefinitely). Returns false if timed out. Names are executables without the full path, e.g., "notepad.exe" or "winword.exe". 
///Implementation:c++_au3
{
	CHECK_ARGS
	long nRes = AU3_ProcessWait(QStrToCStr(strExecutableName), nTimeout);
	return util_LongToBool(nRes);
}

///Function:Process.waitUntilClosed
///Arguments:string strExecutableName, int nTimeout=0
///Returns:bool bSuccess
///Doc:Wait until process is closed. Optional parameter nTimeout specifies how long to wait (default is to wait indefinitely). Returns false if timed out. Names are executables without the full path, e.g., "notepad.exe" or "winword.exe". 
///Implementation:c++_au3
{
	CHECK_ARGS
	long nRes = AU3_ProcessWaitClose(QStrToCStr(strExecutableName), nTimeout);
	return util_LongToBool(nRes);
}



///Function:Process.systemShutdown
///Arguments:bool bForce=false
///Returns:bool bSuccess
///Doc:Shuts down system. Optionally specify true to "force" shutdown, which may result in unsaved data being lost. Returns false upon failure.
///Implementation:c++_au3
{
	CHECK_ARGS
	long nFlag = bForce ? 1+4 : 1;
	long nRes = AU3_Shutdown(nFlag);
	return util_LongToBool(nRes);
}

// see also nircmd exitwin 

///Function:Process.systemLogoff
///Arguments:bool bForce=false
///Returns:bool bSuccess
///Doc:Log off current user. Optionally specify true to "force" logoff, which may result in unsaved data being lost. Returns false upon failure.
///Implementation:c++_au3
{
	CHECK_ARGS
	long nFlag = bForce ? 0+4 : 0;
	long nRes = AU3_Shutdown(nFlag);
	return util_LongToBool(nRes);
}

///Function:Process.systemRestart
///Arguments:bool bForce=false
///Returns:bool bSuccess
///Doc:Restart computer. Optionally specify true to "force" restart, which may result in unsaved data being lost. Returns false upon failure.
///Implementation:c++_au3
{
	CHECK_ARGS
	long nFlag = bForce ? 0+4 : 0;
	long nRes = AU3_Shutdown(nFlag);
	return util_LongToBool(nRes);
}

///Function:Process.systemLock
///Arguments:
///Returns:
///Doc:Lock computer.
///Implementation:c++_nircmd
{
	CHECK_ARGS
	// AU3_Send("#l", 0); // Send Windows - L, which by default locks computer. This works, but doesn't seem as robust.
	return R_Nircmd("lockws");
}

///Function:Process.systemMonitorOff
///Arguments:bool bMonitorState
///Returns:
///Doc:Turn monitor off or on. Process.systemMonitorOff(false) to turn off. Process.systemMonitorOff(true) to turn on.
///Implementation:c++_nircmd
{
	CHECK_ARGS
	return R_Nircmd("monitor", (bMonitorState) ? "on" : "off");
}

///Function:Process.systemScreensaver
///Arguments:
///Returns:
///Doc:Starts the default screen saver. 
///Implementation:c++_nircmd
{
	CHECK_ARGS
	return R_Nircmd("screensaver");
}

///Function:Process.systemStandby
///Arguments:bool bForce=false
///Returns:
///Doc:Puts computer in "stand by" mode. Optionally specify true to "force", which may result in unsaved data being lost. 
///Implementation:c++_nircmd
{
	CHECK_ARGS
	if (bForce) return R_Nircmd("standby","force");
	else return R_Nircmd("standby");
}
///Function:Process.systemHibernate
///Arguments:bool bForce=false
///Returns:bool bStatus
///Doc:Puts computer in "hibernate" mode. Optionally specify true to "force", which may result in unsaved data being lost. 
///Implementation:c++_nircmd
{
	CHECK_ARGS
	if (bForce) return R_Nircmd("hibernate","force");
	else return R_Nircmd("hibernate");
}

///Function:Process.systemRefresh
///Arguments:
///Returns:
///Doc:Initiate a general system refresh. You can use this command to refresh your system after changing your system settings in the Registry (e.g: changing desktop icons size, environment variables, and so on..)
///Implementation:c++_nircmd
{
	CHECK_ARGS
	return R_Nircmd("sysrefresh"); //also "environment" - for refreshing the environment variables, "policy" - for policy settings, "intl" for locale settings.
}
///Function:Process.systemRefreshExplorer
///Arguments:
///Returns:
///Doc:Initiate a general refersh for Windows Explorer. This refresh command can be useful if you make a change in the Registry related to the shell file types (For example, if you change the icon of .gif extensio).
///Implementation:c++_nircmd
{
	CHECK_ARGS
	return R_Nircmd("shellrefresh");
}

///Function:Process.memoryDump
///Arguments:string strExecutableName, string strOutputFilename, int nStartAddress=0x00010000, int nBytesToRead=0x00002000, int nBytesPerLine=32, bool bIncludeHex=true, bool bIncludeAscii=true
///Returns:bool bStatus
///Doc:Saves memory dump of process to a file. Reads memory from a process and formats it in plain text. (Probably won't work in 64-bit mode). By default reads around 8k. Names are executables without the full path, e.g., "notepad.exe" or "winword.exe".
///Implementation:c++_nircmd
{
	CHECK_ARGS
	QString strNircmdCommand;
	// Note that we escape quotes in the input (important)
	QStringList args;
	args << "memdump" << strExecutableName << strOutputFilename;
	args << IntToQStr(nBytesPerLine) <<  IntToQStr(nBytesToRead) << IntToQStr(nStartAddress);
	
	if (!bIncludeHex) args << "nohex";
	if (!bIncludeAscii) args << "noascii";
	
	return util_externalCmdDefault(G_Nircmd, ctx, eng, args);
}

///Function:Process.setServiceStartup
///Arguments:string strServiceName, string strStartupType
///Returns:bool bStatus
///Doc:Change startup type of a service or driver. Options are "auto","manual", "disabled", "boot" (for drivers), "system" (for drivers)
///Implementation:c++_nircmd
{
	CHECK_ARGS
	if (!(strStartupType == "auto" || strStartupType == "manual" || strStartupType == "disabled" || strStartupType == "boot" || strStartupType == "system"))
		return ctx->throwError("Process.setServiceStartup() Invalid parameter, choose one of \"auto\",\"manual\", \"disabled\", \"boot\" \"system\"");

	return R_Nircmd("service", strStartupType, strServiceName);
}
///Function:Process.setServiceStatus
///Arguments:string strServiceName, string strAction
///Returns:bool bStatus
///Doc:Start or stop a service or driver. Actions are "start","stop", "restart", "pause", "continue".
///Example:Process.setServiceStatus("MySql","restart"); //restart Mysql service
///Implementation:c++_nircmd
{
	CHECK_ARGS
	if (!(strAction == "start" || strAction == "stop" || strAction == "restart" || strAction == "pause" || strAction == "continue"))
		return ctx->throwError("Process.setServiceStatus() Invalid action, choose one of \"start\",\"stop\", \"restart\", \"pause\", \"continue\".");
	
	return R_Nircmd("service", strAction, strServiceName);
}
