//Some borrowed from Prototype library
//http://github.com/sstephenson/prototype/tree/master/src

// All of these are disabled. 
// Having these added to Array means that you can't write loops for(var index in arr) arr[index]...
// because of the other items...

/*Array.prototype.clone = function()
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
previously in exposed-global.cpp:
//~ ///Function:Array.clone
//~ ///Arguments:
//~ ///Returns:array copy
//~ ///Doc:Returns shallow copy of the array. Use include('<std>') to import this function.
//~ ///Implementation:Javascript
//~ ///InstanceMethod:true
//~ {}

//~ ///Function:Array.size
//~ ///Arguments:
//~ ///Returns:int nLength
//~ ///Doc:Returns length of the array. Use include('<std>') to import this function.
//~ ///Implementation:Javascript
//~ ///InstanceMethod:true
//~ {}
	
//~ ///Function:Array.last
//~ ///Arguments:
//~ ///Returns:elem value
//~ ///Doc:Retrieves last element of the array. Use include('<std>') to import this function.
//~ ///Implementation:Javascript
//~ ///InstanceMethod:true
//~ {}

//~ ///Function:Array.max
//~ ///Arguments:
//~ ///Returns:number max
//~ ///Doc:Finds and returns greatest numeric value in the array. Use include('<std>') to import this function.
//~ ///Implementation:Javascript
//~ ///InstanceMethod:true
//~ {}

//~ ///Function:Array.min
//~ ///Arguments:
//~ ///Returns:number min
//~ ///Doc:Finds and returns least numeric value in the array. Use include('<std>') to import this function.
//~ ///Implementation:Javascript
//~ ///InstanceMethod:true
//~ {}

*/

Math.shuffleArray = function(arr)
{
	// Fisher-yates, http://sedition.com/perl/javascript-fy.html
	var i = arr.length;
	if ( i == 0 ) return false;
	while ( --i ) {
	var j = Math.floor( Math.random() * ( i + 1 ) );
	var tempi = arr[i];
	var tempj = arr[j];
	arr[i] = tempj;
	arr[j] = tempi;
	}
	return arr;
}


