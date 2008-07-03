
///Function:Time.sleep
///Arguments:int nMilliseconds
///Returns:
///Doc:Pauses script for this amount of time.
{
	CHECK_ARGS
	AU3_Sleep(nMilliseconds);
	return eng->nullValue();
}

///Function:Time.createTimer
///Arguments:
///Returns:timer object
///Doc:Creates a timer object that can be used for timing a script. Call the check() method on the timer to see how many milliseconds have passed after the object was created.
///Example:var timer = Time.createTimer(); for (var i=0; i<30000; i++); print('number of ms:'+timer.check());
///Implementation:Javascript