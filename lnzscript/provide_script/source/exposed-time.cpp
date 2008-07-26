
///Function:Time.sleep
///Arguments:int nMilliseconds
///Returns:
///Doc:Pauses script for this amount of time.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_Sleep(nMilliseconds);
	return eng->nullValue();
}

// Time.createTimer is documented in exposed-global.cpp, because it is in <std>

