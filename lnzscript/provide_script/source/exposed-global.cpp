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

///Function:Array.clone
///Arguments:
///Returns:array copy
///Doc:Returns shallow copy of the array. Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}

///Function:Array.size
///Arguments:
///Returns:int nLength
///Doc:Returns length of the array. Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}
	
///Function:Array.last
///Arguments:
///Returns:elem value
///Doc:Retrieves last element of the array. Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}

///Function:Array.max
///Arguments:
///Returns:number max
///Doc:Finds and returns greatest numeric value in the array. Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}

///Function:Array.min
///Arguments:
///Returns:number min
///Doc:Finds and returns least numeric value in the array. Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}

///Function:String.contains
///Arguments:string smallerString
///Returns:bool bContains
///Doc:Tests if string contains a certain substring. Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}

///Function:String.startsWith
///Arguments:string smallerString
///Returns:bool bStartsWith
///Doc:Tests if string starts with a certain substring. Use include('<std>') to import this function.
///Implementation:Javascript
///InstanceMethod:true
{}

///Function:String.endsWith
///Arguments:string smallerString
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
///Example:var timer = Time.createTimer(); for (var i=0; i<30000; i++); print('number of ms:'+timer.check());
///Implementation:Javascript
{}




