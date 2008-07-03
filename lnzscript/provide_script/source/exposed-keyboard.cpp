
///Function:Keyboard.send
///Arguments:string strKeySequence
///Returns:
///Doc:Sends simulated keystrokes to the active window. The string can include <Alt>, <Control> or <Cntrl>, <Shift>, and <Win> as well as many others: {SPACE}, {ENTER}, {BACKSPACE}, {DELETE}, {UP}, {DOWN}, {LEFT}, {RIGHT}, {HOME}, {END}, {ESCAPE}, {INSERT}, {PGUP}, {PGDN}, {F1}-{F12}, {TAB}, {PRINTSCREEN}, {LWIN}, {RWIN}, {NUMLOCK on}, {CAPSLOCK off}, {SCROLLLOCK toggle}, {BREAK}, {PAUSE}, {NUMPAD0}, {NUMPADMULT}, {NUMPADADD}, {NUMPADSUB}, {NUMPADDIV}, {NUMPADDOT}, {NUMPADENTER}, {APPSKEY}, {LALT}, {RALT}, {LCTRL}, {RCTRL}, {LSHIFT}, {RSHIFT}, {SLEEP}, {ALTDOWN}, {SHIFTDOWN}, {CTRLDOWN}, {LWINDOWN}, {RWINDOWN}, {ASC nnnn}, {BROWSER_BACK}, {BROWSER_FORWARD}, {BROWSER_REFRESH}, {BROWSER_STOP}, {BROWSER_SEARCH}, {BROWSER_FAVORITES}, {BROWSER_HOME}, {VOLUME_MUTE}, {VOLUME_DOWN}, {VOLUME_UP}. Send {{} or {}} to send literal brace characters.
///Example:Process.open('notepad.exe'); Keyboard.send('hello'); Keyboard.send('<Control>s'); Keyboard.send('{UP}{DOWN}{TAB}{ENTER}'); Keyboard.send('<Control><Shift>f');
{
	CHECK_ARGS
	strKeySequence = util_AU3KeyboardCommandsReplacement(strKeySequence);
	AU3_Send(QStrToCStr(strKeySequence), 0); //do not send raw.
	return eng->nullValue();
}

///Function:Keyboard.sendRaw
///Arguments:string strKeySequence
///Returns:
///Doc:Sends simulated keystrokes to the active window. 
///Example:Keyboard.sendRaw('<html>');
{
	CHECK_ARGS
	AU3_Send(QStrToCStr(strKeySequence), 1); //send raw.
	return eng->nullValue();
}

///Function:Keyboard.sendAscii
///Arguments:int nAsciiCode
///Returns:
///Doc:Sends ascii value to active window.
{
	CHECK_ARGS
	QString strKeySequence;
	strKeySequence.sprintf("{ASC %03d}", nAsciiCode); // must be 3 digits, pad with 0
	AU3_Send(QStrToCStr(strKeySequence), 0);
	return eng->nullValue();
}

///Function:Keyboard.sendUnicode
///Arguments:int nUnicode
///Returns:
///Doc:Sends unicode value to active window.
{
	CHECK_ARGS
	QString strKeySequence;
	strKeySequence.sprintf("{ASC %04d}", nUnicode); // must be 4 digits, pad with 0
	AU3_Send(QStrToCStr(strKeySequence), 0);
	return eng->nullValue();
}

///Function:Keyboard.setKeyDelay
///Arguments:int keyDelay
///Returns:
///Doc:Alters the the length of the brief pause in between sent keystrokes. Time in milliseconds to pause (default=5). Sometimes a value of 0 does not work; use 1 instead.
{
	CHECK_ARGS
	AU3_AutoItSetOption("SendKeyDelay", keyDelay);
	return eng->nullValue();
}

///Function:Keyboard.setKeyDownDuration
///Arguments:int keyDownDuration
///Returns:
///Doc:Alters the length of time a key is held down before released during a keystroke. For applications that take a while to register keypresses (and many games) you may need to raise this value from the default. Time in milliseconds to pause (default=1).
{
	CHECK_ARGS
	AU3_AutoItSetOption("SendKeyDownDelay", keyDownDuration);
	return eng->nullValue();
}

