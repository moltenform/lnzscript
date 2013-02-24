// defined in provide_script.cpp, available to all scripts:

///Function:(Global).print
///Arguments:string strCode
///Returns:
///Doc:Print string or any object to the screen.
///Implementation:Javascript
{}

///Function:(Global).include
///Arguments:string strScriptFilename
///Returns:
///Doc:Include a LnzScript file and execute it as if its contents were included directly. Use include('<std>') to include standard JavaScript code.
///Implementation:Javascript
{}

// defined in provide_script.cpp, by using code like engine.evaluate("alert=function()..."):

///Function:(Global).alert
///Arguments:string strMessage
///Returns:
///Doc:Open a dialog box displaying message. See Dialog.alert, which can also specify a title.
///Implementation:Javascript
{}

///Function:(Global).confirm
///Arguments:string strMessage
///Returns:bool bResponse
///Doc:Open a dialog box displaying message, with options for yes and no. Returns true if yes, and false if no. See also Dialog.askYesNo, which has more options.
///Implementation:Javascript
{}

///Function:(Global).prompt
///Arguments:string strPrompt
///Returns:string strResult
///Doc:Open a dialog box in which the user can enter text. Returns "" if the user presses cancel. See also Dialog.input, which has more options.
///Implementation:Javascript
{}

//-----------------------------------
// imported from <std> : (i.e., std.js)
	
///Function:(Global).printarr
///Arguments:array ar
///Returns:
///Doc:Prints array, with indices. Use include('<std>') to import this function.
///Implementation:Javascript
{}

///Function:(Global).printobj
///Arguments:object obj
///Returns:
///Doc:Prints object, with keys. Use include('<std>') to import this function.
///Implementation:Javascript
{}

///Function:(Global).isFunction
///Arguments:object obj
///Returns:
///Doc:Returns true if the object is a function. Use include('<std>') to import this function.
///Implementation:Javascript
{}

///Function:(Global).isArray
///Arguments:object obj
///Returns:
///Doc:Returns true if the object is an array. Use include('<std>') to import this function.
///Implementation:Javascript
{}

///Function:(Global).isNumber
///Arguments:object obj
///Returns:
///Doc:Returns true if the object is a number or can be used as a number. Use include('<std>') to import this function.
///Implementation:Javascript
{}

///Function:Math.shuffleArray
///Arguments:array arr
///Returns:
///Doc:Shuffles (randomizes) order of elements in array. Use include('<std>') to import this function. Fisher-Yates algorithm. Note that apparently, initial random seed of lnzScript is the same, which is due to Qt library used. 
///Implementation:Javascript
///InstanceMethod:true
{}



///Function:String.contains
///Arguments:string strSmallerString
///Returns:bool bContains
///Doc:Tests if string contains a certain substring. Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}

///Function:String.startsWith
///Arguments:string strSmallerString
///Returns:bool bStartsWith
///Doc:Tests if string starts with a certain substring. Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}

///Function:String.endsWith
///Arguments:string strSmallerString
///Returns:bool bEndsWith
///Doc:Tests if string ends with a certain substring. Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}

///Function:String.strip
///Arguments:
///Returns:string strStripped
///Doc:Removes whitespace from beginning and end of string, similarly to the traditional strip() or trim(). Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}

///Function:Time.createTimer
///Arguments:
///Returns:timer objTimer
///Doc:Use include('<std>') to import this function. Creates a timer object that can be used for timing a script. Call the check() method on the timer to see how many milliseconds have passed after the object was created.
///Example:include('<std>'); [[br]]var timer = Time.createTimer();[[br]] for (var i=0; i<30000; i++); print('number of ms:'+timer.check());
///Implementation:Javascript
{}


///Function:Rename.rename
///Arguments:string strSearch, string strReplace
///Returns:bool bSuccess
///Doc:Rename strings in filenames. Use include('<std>') to import this. Rename does the following: for each file in the current directory (File.cd()), replace in the filename. Doesn't rename subdirectories. If a file cannot be renamed, throws an exception and leaves other filenames unchanged.
///Example:include('<std>'); [[br]]File.cd(@'c:\mydir'); [[br]]Rename.rename('.htm', '.html');
///Implementation:Javascript
{}

///Function:Rename.renamePreview
///Arguments:string strSearch, string strReplace
///Returns:bool bSuccess
///Doc:Preview before rename strings in filenames. Use include('<std>') to import this. Prints the results of what Rename.rename would do, without actually renaming the files. Useful for testing.
///Implementation:Javascript
{}

///Function:Rename.renameFn
///Arguments:function fnRename, string strSorted='name'
///Returns:bool bSuccess
///Doc:Rename filenames. Use include('<std>') to import this. Provide a function that accepts a string and returns a string, the new name. Doesn't rename subdirectories. You can specify a sort order, which is useful when your function has state; this could be used to rename a set of files to 001, 002, 003... based on modification date. If a file cannot be renamed, throws an exception and leaves other filenames unchanged.
///Example:include('<std>'); [[br]]File.cd(@'c:\mydir');[[br]] function myRename(s) {return 'new'+s;}[[br]] Rename.rename(myRename);
///Implementation:Javascript
{}

///Function:Rename.renameFnPreview
///Arguments:function fnRename, string strSorted='name'
///Returns:bool bSuccess
///Doc:Rename filenames. Use include('<std>') to import this. Prints the results of what Rename.renameFn would do, without actually renaming the files. Useful for testing.
///Implementation:Javascript
{}



