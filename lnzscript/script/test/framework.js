assertEq = function(v1, v2, strMsg)
{
	if (v1!=v2)
	{
		print('Assertion failed: '+v1+ ' != '+v2);
		assert(false);
	}
}
assertNotEq = function(v1, v2, strMsg)
{
	if (v1==v2)
	{
		print('Assertion failed: '+v1+ ' == '+v2);
		assert(false);
	}
}


assert = function(bExp)
{
	
	print('Last test was: '+g_lastSeenMethod );
	throw('Assertion failed.');
}

print('Included: framework.js');