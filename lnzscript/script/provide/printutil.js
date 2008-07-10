
printarr = function(arr)
{
print('Array:');
for (var i=0; i<arr.length; i++)
	print('['+i+']\t'+arr[i]);
}

printobj = function(obj)
{
// Prototypes may have been added, so only include unique keys.
var dummy = new Object;
print('Object:');
for (var key in obj)
	if (dummy[key]===undefined)
		print('['+key+']\t'+obj[key]);

}

