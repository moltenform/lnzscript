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

assert = function(bExp)
{
	print('Last test was: '+g_lastSeenMethod );
	print('Assertion failed.');
	abort('');
}

abort = function(s)
{
	if (s) print(s);
	throw(false);
}

print('Included: framework.js');