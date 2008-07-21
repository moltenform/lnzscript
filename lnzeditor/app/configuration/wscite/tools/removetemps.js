
// in case <std> isn't there for some reason.
if (!String.prototype.startsWith)
{
	String.prototype.startsWith = function(s)
	{
	return (this.indexOf(s)===0);
	}

	String.prototype.endsWith = function(s)
	{
	var d = this.length - s.length;
	return d >= 0 && this.lastIndexOf(s) === d;
	}
}

// removes temporary files in the tmp directory.

// The current directory is set to the location of the script.

var tmpdir = '..\\tmp\\';
var aFiles = File.dirListFiles( tmpdir);for(var i=0; i<aFiles.length;i++)
{
	if (aFiles[i].startsWith('lnz'))
	{
		if (aFiles[i].endsWith('.tmp') || aFiles[i].endsWith('.tmp.js'))
			File.removeFile(tmpdir + aFiles[i]);
	}

}


print('');