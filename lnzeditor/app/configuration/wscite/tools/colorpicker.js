function toHex(n)
{
	var s = n.toString(16);
	if (s.length == 1) s = '0'+s;
	return s;
}



var res = Dialog.askColor();
if (res)
{
	print('R: '+res[0] + ' G: '+res[1] + ' B: '+res[2]);
	print('#'+toHex(res[0]) + toHex(res[1]) + toHex(res[2]));
}
