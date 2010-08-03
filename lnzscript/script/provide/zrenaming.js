

//the marker doesn't check files that might happen to be there, but that shouldn't come up.
//if another process is modifying this at the same time, no data will be lost. it is possible that file names are inconsistent.
var marker= '_!_lnzrename_!_';
errstring = function(s) { print(s); }
actuallyRenameFiles = function (inputFilenames, outputFilenames)
{
	//check lengths
	if (inputFilenames.length!=outputFilenames.length)
	{ errstring('Lengths do not match.'); return false; }
	//check for empty
	for (var i=0; i<inputFilenames.length;i++)
		if (!inputFilenames[i])
			{ errstring('Filenames cannot be empty.'); return false; }
	//check for duplicate names
	var tmp={}
	for (var i=0; i<outputFilenames.length;i++)
		if (tmp[outputFilenames[i]])
		{
			errstring('Duplicate names, '+outputFilenames[i]+' occurs twice.'); return false; 
		}
		else tmp[outputFilenames[i]]=1;
	//check for marker
	for (var i=0; i<inputFilenames.length;i++)
		if (inputFilenames[i].contains(marker))
		{ 
			errstring('In this tool, filenames cannot contain the string "'+marker+'".'); return false;
		}
	//we assume that files exist...
	//check that files can be renamed.
	for (var i=0; i<inputFilenames.length;i++)
		if (inputFilenames[i]!=outputFilenames[i])
		{
			var bRes = false;
			try
			{
				bRes=File.rename(inputFilenames[i], marker);
			}
			catch (err) {}
			if (!bRes) {errstring('The file '+inputFilenames[i]+' cannot be renamed.'); return false;}
			File.rename(marker, inputFilenames[i]);
		}
	
	//do not conflict with an existing file, not in the input list.
	tmp={}
	for (var i=0; i<inputFilenames.length;i++)
		tmp[inputFilenames[i]] = 1
	for (var i=0; i<outputFilenames.length;i++)
		if (!tmp[outputFilenames[i]] && File.exists(outputFilenames[i]))
			{errstring('The output name conflicts with an existing file :'+outputFilenames[i]); return false;}
	
	//the reason we do this, is that we can do conflicting overlap changes.
	//rename files to 0,1,2,3
	for (var i=0; i<inputFilenames.length;i++)
		File.rename( inputFilenames[i], marker+i.toString());
	//rename files to the output names
	for (var i=0; i<outputFilenames.length;i++)
		File.rename( marker+i.toString(), outputFilenames[i]);
	
	return true;
}

//must be in the current directory. originally allowed other dirs, but slightly complicated things
//note that replace is done -once-. not more than once. replace from right to left to catch file exts first?
//this is kind of fragile, if people want to change '.htm', they'll accidently hit '.html' and '.htm.tmp'
renameImpl = function(  sSearch, sReplace, bActuallyRename)
{
	var arFiles = File.dirListFiles(File.cd(), '*')
	var arSrc = []
	var arTargets = []
	for (var i=0; i<arFiles.length; i++)
	{
		var newFilename = arFiles[i].replace(sSearch, sReplace)
		if (newFilename && arFiles[i]!=newFilename)
		{
			arSrc.push(arFiles[i]);
			arTargets.push(newFilename);
			if (!bActuallyRename)
				print('"'+arFiles[i]+'" would be renamed to \t"'+newFilename+'"')
		}
		else if (!bActuallyRename)
				print('"'+arFiles[i]+'" would not be renamed.')
	}
	if (bActuallyRename)
		return actuallyRenameFiles(arSrc, arTargets); 
}

Rename.rename = function(sSearch, sReplace)
{
	return renameImpl(sSearch, sReplace, true);
}
Rename.renamePreview = function(sSearch, sReplace)
{
	return renameImpl(sSearch, sReplace, false);
}

renameFnImpl = function(  fn, sortOrder, bActuallyRename)
{
	var arFiles = File.dirListFiles(File.cd(), '*', sortOrder)
	var arSrc = []
	var arTargets = []
	for (var i=0; i<arFiles.length; i++)
	{
		var newFilename =fn(arFiles[i])
		if (newFilename && arFiles[i]!=newFilename)
		{
			arSrc.push(arFiles[i]);
			arTargets.push(newFilename);
			if (!bActuallyRename)
				print('"'+arFiles[i]+'" would be renamed to \t"'+newFilename+'"')
		}
		else if (!bActuallyRename)
				print('"'+arFiles[i]+'" would not be renamed.')
	}
	if (bActuallyRename)
		return actuallyRenameFiles(arSrc, arTargets); 
}

Rename.renameFn = function(fn, sortOrder)
{
	if (!sortOrder) sortOrder='Unsorted';
	return renameFnImpl(fn, sortOrder, true);
}
Rename.renameFnPreview = function(fn, sortOrder)
{
	if (!sortOrder) sortOrder='Unsorted';
	return renameFnImpl(fn, sortOrder, false);
}

