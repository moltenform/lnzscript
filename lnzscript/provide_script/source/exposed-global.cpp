///Function:(Global).print
///Arguments:string strCode
///Returns:
///Doc:Print string or any object to the screen.
///Implementation:Javascript
{}

///Function:(Global).include
///Arguments:string strScriptFilename
///Returns:
///Doc:Include a LnzScript file and execute it as if its contents were included directly.
///Implementation:Javascript
{}

// note that these are defined in provide_script.cpp, by using code like engine.evaluate("javascript code");
	
///Function:(Global).alert
///Arguments:string strMessage
///Returns:
///Doc:Open a dialog box displaying message. See Dialog.alert, which can also specify a title.
///Implementation:Javascript
{}

///Function:(Global).confirm
///Arguments:string strMessage
///Returns:
///Doc:Open a dialog box displaying message, with options for yes and no. Returns true if yes, and false if no. See also Dialog.askYesNo, which has more options.
///Implementation:Javascript
{}
	
// also document extensions like "startswith", "endswith" and the stuff in <std> here. Maybe Timer.createTimer should go in time.cpp though

