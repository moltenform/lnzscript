// This file keeps track of methods that have been tested.
// The goal is for every method to have at least one test.


g_seenMethods = {}
g_lastSeenMethod = '';
function methods_list_init()
{
	if (!File.exists('methods_list.txt')) {print('methods_list.txt does not exist.'); throw(false);}
	var strMethods = File.readFile('methods_list.txt');
	if (!strMethods) throw('Could not read methods list.');
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
	if (!g_seenMethods[strMethod]) throw 'I have not heard of method '+strMethod;
	g_seenMethods[strMethod] = 1;
	g_lastSeenMethod = strMethod;
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