//Some borrowed from Prototype library
//http://github.com/sstephenson/prototype/tree/master/src

Array.prototype.clone = function()
{
return this.concat([]);
}

Array.prototype.size = function()
{
return this.length;
}

Array.prototype.last = function()
{
return this[this.length-1];
}

Array.prototype.max = function()
{
	var max = Number.MIN_VALUE;
	for (var i=0; i<this.length; i++)
	{
	if (this[i]>max) max=this[i];
	}
	return max;
}
Array.prototype.min = function()
{
	var min = Number.MAX_VALUE;
	for (var i=0; i<this.length; i++)
	{
	if (this[i]<min) min=this[i];
	}
	return min;
}

function artest()
{
	a = [1,2,-5,3,2,1];
	print(a.max());
	print(a.min());
}
