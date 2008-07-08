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