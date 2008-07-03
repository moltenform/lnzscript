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

