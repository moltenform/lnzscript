
///Function:Process.open
///Arguments:string strExe, bool bPauseUntilItCloses=false, string strWorkingDir="", int nFlag=1
///Returns:int nPID
///Doc:Opens external program. Optionally pass a flag such as Window.HIDE, Window.SHOW, Window.MINIMIZE, Window.MAXIMIZE, or Window.RESTORE. Returns the PID of process or null upon failure.
///Implementation:c++_au3
{
	CHECK_ARGS
	if (bPauseUntilItCloses) 
	{
		// Seems analogous to QProcess::execute 
		long nRes = AU3_RunWait(QStrToCStr(strExe), QStrToCStr(strWorkingDir),nFlag);
		if (AU3_error()!=1)
			return QScriptValue(eng, (int) nRes);
		else
			return eng->nullValue();
	}
	else
	{
		// Seems analogous to QProcess::start
		long nRes = AU3_Run(QStrToCStr(strExe), QStrToCStr(strWorkingDir),nFlag);
		if (AU3_error()!=1)
			return QScriptValue(eng, (int) nRes);
		else
			return eng->nullValue();
	}
}


///Function:Process.openFile
///Arguments:string strFileOrUrlOrProgram, string strWorkingDir=""
///Returns:
///Doc:Opens file, URL, or program with Windows shell (usually opens file in the default editor). After running the requested program the script continues (this is asynchronous).
///Implementation:c++_qt
{
	CHECK_ARGS
	QProcess objProcess;
	if (strWorkingDir != "") objProcess.setWorkingDirectory(strWorkingDir);
	
	QString strExecutable = "cmd.exe /c start \"" + strFileOrUrlOrProgram + "\"";
	objProcess.start(strExecutable);
	objProcess.waitForFinished(); //the cmd.exe should spawn off what we opened, so this won't actually block.
	return eng->nullValue();
}

///Function:Process.runAndRead
///Arguments:string strExe, string strWorkingDir="", int nTimeoutMs=30000
///Returns:string strOutput
///Doc:Opens external program and reads its output from stdout. The script pauses until the program has closed. Throws exception if program cannot be found, and if process times out. 
///Implementation:c++_qt
{
	// to run shell, use Process.runAndRead('cmd.exe /c dir')
	CHECK_ARGS
	QProcess objProcess;
	if (strWorkingDir != "") objProcess.setWorkingDirectory(strWorkingDir);
	objProcess.start(strExe);
	
	int nError = objProcess.error();
	if (nError ==0) return ctx->throwError("Process.runAndRead(): process failed to start. Either the invoked program is missing, or you may have insufficient permissions.");
	// error of 5 seems to mean ok. Other values at http://doc.trolltech.com/4.4/qprocess.html#ProcessError-enum
	
	bool bTimeout = objProcess.waitForFinished(nTimeoutMs);
	if (!bTimeout) return ctx->throwError("Process.runAndRead(): process timed out.");
	QString strOutput( objProcess.readAllStandardOutput());
	return QScriptValue(eng, strOutput);
}
///Function:Process.runCmdLine
///Arguments:string strCommandLineCommand, string strWorkingDir=""
///Returns:
///Doc:Execute command line command, in the style of the command prompt cmd.exe. Waits until command completes. You must use quotes if a file or directory has spaces in the name.
///Example: Process.runCmdLine('mkdir "c:\\program files\\myfolder"');
///Implementation:c++_qt
{
	CHECK_ARGS
	QProcess objProcess;
	if (strWorkingDir != "") objProcess.setWorkingDirectory(strWorkingDir);
	
	QString strExecutable = "cmd.exe /c " + strCommandLineCommand;
	objProcess.start(strExecutable);
	objProcess.waitForFinished(); //the cmd.exe should spawn off what we opened.
	return eng->nullValue();
}


///Function:Process.close
///Arguments:string strExe
///Returns:
///Doc:Close a process. Names are executables without the full path, e.g., "notepad.exe". If multiple processes have the same name, the one closed is not necessarily the recently opened one.
///Example:Process.close('notepad.exe'); [[br]]Process.close('1356'); //close process id 1356
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_ProcessClose(QStrToCStr(strExe));
	return eng->nullValue();
}

///Function:Process.exists
///Arguments:string strExe
///Returns:int nPID
///Doc:Checks to see if a process is running e.g., "notepad.exe". Returns the PID of the process, or 0 if process does not exist.
///Implementation:c++_au3
{
	CHECK_ARGS
	long res = AU3_ProcessExists(QStrToCStr(strExe));
	return QScriptValue(eng, (int) res);	
}

///Function:Process.setPriority
///Arguments:string strExe, int nPriorityLevel
///Returns:bool bSuccess
///Doc:Changes the priority of a process. 0=Idle/Low, 4=High, 5=Realtime (use with caution). Levels 1 and 3 not supported on Win95/98/ME.  Returns false upon failure. Names are executables without the full path, e.g., "notepad.exe" or "winword.exe". 
///Implementation:c++_au3
{
	CHECK_ARGS
	long nRes = AU3_ProcessSetPriority(QStrToCStr(strExe),nPriorityLevel);
	return util_LongToBool(nRes);
}

///Function:Process.waitUntilOpen
///Arguments:string strExe, int nTimeout=0
///Returns:bool bSuccess
///Doc:Wait until process is open. Optional parameter nTimeout specifies how long to wait (default is to wait indefinitely). Returns false if timed out. Names are executables without the full path, e.g., "notepad.exe" or "winword.exe". 
///Implementation:c++_au3
{
	CHECK_ARGS
	long nRes = AU3_ProcessWait(QStrToCStr(strExe), nTimeout);
	return util_LongToBool(nRes);
}

///Function:Process.waitUntilClosed
///Arguments:string strExe, int nTimeout=0
///Returns:bool bSuccess
///Doc:Wait until process is closed. Optional parameter nTimeout specifies how long to wait (default is to wait indefinitely). Returns false if timed out. Names are executables without the full path, e.g., "notepad.exe" or "winword.exe". 
///Implementation:c++_au3
{
	CHECK_ARGS
	long nRes = AU3_ProcessWaitClose(QStrToCStr(strExe), nTimeout);
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
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_Send("#l", 0); // Send Windows - L, which by default locks computer.
	// used to use nir-cmd.
	return eng->nullValue();
}

//~ ///Function:nirdisabled_Process.systemMonitorOff
//~ ///Arguments:bool bMonitorState
//~ ///Returns:
//~ ///Doc:Turn monitor off or on. Process.systemMonitorOff(false) to turn off. Process.systemMonitorOff(true) to turn on.
//~ ///Implementation:c++_nir-cmd


//~ ///Function:nirdisabled_Process.systemScreensaver
//~ ///Arguments:
//~ ///Returns:
//~ ///Doc:Starts the default screen saver. 
//~ ///Implementation:c++_nir-cmd


//~ ///Function:nirdisabled_Process.systemStandby
//~ ///Arguments:bool bForce=false
//~ ///Returns:
//~ ///Doc:Puts computer in "stand by" mode. Optionally specify true to "force", which may result in unsaved data being lost. 
//~ ///Implementation:c++_nir-cmd


//~ ///Function:nirdisabled_Process.systemHibernate
//~ ///Arguments:bool bForce=false
//~ ///Returns:bool bStatus
//~ ///Doc:Puts computer in "hibernate" mode. Optionally specify true to "force", which may result in unsaved data being lost. 
//~ ///Implementation:c++_nir-cmd


//~ ///Function:nirdisabled_Process.systemRefresh
//~ ///Arguments:
//~ ///Returns:
//~ ///Doc:Initiate a general system refresh. You can use this command to refresh your system after changing your system settings in the Registry (e.g: changing desktop icons size, environment variables, and so on..)
//~ ///Implementation:c++_nirc-md


//~ ///Function:nirdisabled_Process.systemRefreshExplorer
//~ ///Arguments:
//~ ///Returns:
//~ ///Doc:Initiate a general refresh for Windows Explorer. This refresh command can be useful if you make a change in the Registry related to the shell file types (For example, if you change the icon of .gif extensio).
//~ ///Implementation:c++_nir-cmd


//~ ///Function:nirdisabled_Process.memoryDump
//~ ///Arguments:string strExe, string strOutputFilename, int nStartAddress=0x00010000, int nBytesToRead=0x00002000, int nBytesPerLine=32, bool bIncludeHex=true, bool bIncludeAscii=true
//~ ///Returns:bool bStatus
//~ ///Doc:Saves memory dump of process to a file. Reads memory from a process and formats it in plain text. (Probably won't work in 64-bit mode). By default reads around 8k. Names are executables without the full path, e.g., "notepad.exe" or "winword.exe".
//~ ///Implementation:c++_nir-cmd


//~ ///Function:nirdisabled_Process.setServiceStartup
//~ ///Arguments:string strServiceName, string strStartupType
//~ ///Returns:bool bStatus
//~ ///Doc:Change startup type of a service or driver. Options are "auto","manual", "disabled", "boot" (for drivers), "system" (for drivers)
//~ ///Implementation:c++_nir-cmd


//~ ///Function:nirdisabledwant_Process.setServiceStatus
//~ ///Arguments:string strServiceName, string strAction
//~ ///Returns:bool bStatus
//~ ///Doc:Start or stop a service or driver. Actions are "start","stop", "restart", "pause", "continue".
//~ ///Example:Process.setServiceStatus("MySql","restart"); //restart Mysql service
//~ ///Implementation:c++_nir-cmd
