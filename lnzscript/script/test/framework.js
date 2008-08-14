assertEq = function(v1, v2, strMsg)
{
	if (v1!=v2)
	{
		print('Assertion failed: '+v1+ ' != '+v2);
		print('Last test was: '+g_lastSeenMethod );
		abort('');
	}
}
assertNotEq = function(v1, v2, strMsg)
{
	if (v1==v2)
	{
		print('Assertion failed: '+v1+ ' == '+v2);
		print('Last test was: '+g_lastSeenMethod );
		abort('');
	}
}

assertFails = function(fn, strMsg)
{
	var bException = false;
	try { fn(); 	}
	catch(e) {bException = true;}
	if (!bException)
	{ 
		print('Assertion failed. Should have raised an exception. '+fn.toString());
		print('Last test was: '+g_lastSeenMethod );
		abort('');
	}
}

assertArrEq = function(a1, a2, strMsg)
{
	if (a1.length != a2.length) {print('Assertion failed. Arrays have different lengths. \nLast test was: '+g_lastSeenMethod ); abort('');}
	for(var i=0; i<a1.length;i++)
	{
		v1=a1[i]; v2=a2[i];
		if (v1!=v2)
		{
			print('Assertion failed: Array elements different. '+v1+ ' != '+v2);
			print('Last test was: '+g_lastSeenMethod );
			abort('');
		}
	}
	
}

assert = function(bExp)
{
	if (!bExp)
	{
		print('Last test was: '+g_lastSeenMethod );
		print('Assertion failed.');
		abort('');
	}
}

abort = function(s)
{
	if (s) print(s);
	throw(false);
}

testOpenWindow = function (fnPerform, strArgument, strExpectedWindowResult)
{
	if (Window.exists(strExpectedWindowResult)) Window.close(strExpectedWindowResult);
	
	fnPerform(strArgument); Time.sleep(800); Time.sleep(800);
	if (!Window.exists(strExpectedWindowResult)) {print('Window "'+strExpectedWindowResult+'" not found'); assert(false);}
	Window.close(strExpectedWindowResult);
}

print('Included: framework.js');