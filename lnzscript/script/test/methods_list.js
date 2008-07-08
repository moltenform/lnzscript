// This file keeps track of methods that have been tested.
// The goal is for every method to have at least one test.


g_seenMethods = {}
g_lastSeenMethod = '';
function methods_list_init()
{
	if (!File.exists('methods_list.txt')) abort('methods_list.txt does not exist.');
	var strMethods = File.readFile('methods_list.txt');
	if (!strMethods) abort('Could not read methods list.');
	strMethods = strMethods.replace(/\r\n/g,'\n');
	var astrMethods = strMethods.split('\n');
	for (var i=0; i<astrMethods.length; i++)
	{
		var method = astrMethods[i];
		g_seenMethods[method] = -1; // as in it exists
	}
	return true;
}
methods_list_init();

registerTest = function(strMethod)
{
	if (!g_seenMethods[strMethod]) abort( 'I have not heard of method '+strMethod);
	if (g_seenMethods[strMethod] == 1) print('Warning: method '+strMethod+' is already registered.');
	g_seenMethods[strMethod] = 1;
	g_lastSeenMethod = strMethod;
}

methods_list_summary_namespace = function(strNamespace)
{
	print('Tests for namespace '+strNamespace+':');
	var strMissing = '';
	for(var key in g_seenMethods)
	{
		if (key.startsWith(strNamespace))
		{
			if (g_seenMethods[key]==-1) strMissing += key;
		}
	}
	if (strMissing) print('Missing: '+strMissing);
	else print('All pass');
}

methods_list_summary = function()
{
	var countSeen = 0;
	var countTotal = 0;
	for(var key in g_seenMethods)
	{
		countTotal++;
		if (g_seenMethods[key]!=-1)
			countSeen++;
	}
	print('Results: '+countSeen+' seen, '+countTotal+' total.');
}

print('Included: methods_list.js');