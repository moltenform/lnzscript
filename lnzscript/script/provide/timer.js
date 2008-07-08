
// Intended use:
// var timer = Timer.createTimer()
// (some code)
// timer.check()

Time.createTimer = function() 
{
	return new _Timer();
}
function _Timer() //intended to be constructed with new.
{
	this.dt = new Date();
}
_Timer.prototype.check = function()
{
	var n = new Date();
	var nDiff = n.getTime() - this.dt.getTime();
	return nDiff;
}

