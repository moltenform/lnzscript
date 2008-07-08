//Some borrowed from Prototype library
//http://github.com/sstephenson/prototype/tree/master/src

String.prototype.contains = function(s)
{
return (this.indexOf(s)!=-1);
}

String.prototype.startsWith = function(s)
{
return (this.indexOf(s)===0);
}

String.prototype.endsWith = function(s)
{
var d = this.length - s.length;
return d >= 0 && this.lastIndexOf(s) === d;
}

String.prototype.strip = function()
{
return this.replace(/^\s+/, '').replace(/\s+$/, '');
}