include('<std>')
//ported from python's ntpath.py in the standard library


//~ # Split a path in a drive specification (a drive letter followed by a
//~ # colon) and the path specification.
//~ # It is always true that drivespec + pathspec == p
splitdrive = function(p)
{
	if (p.slice(1,2)==':')
		return [p.slice(0,2), p.slice(2)]
	return ['',p]
}

//~ # For DOS it is absolute if it starts with a slash or backslash (current
//~ # volume), or if a pathname after the volume letter and colon / UNC resource
//~ # starts with a slash or backslash.
isabs=function(s)
{
	s = splitdrive(s)[1]
	return (s != '' && '/\\'.contains(s.slice(0,1)) )
}

File.pathJoin = function(path,b)
{
	if (!path) return b
	if (!b) return path
	var b_wins=0
	if (path == "")
            b_wins = 1
	else if (isabs(b))
	{
		
		if (path.slice(1,2)!=':' || b.slice(1,2)==':')
			b_wins = 1
		else if (path.length>3 || (path.length==3&& !"/\\".contains(path[2])))
			b_wins = 1
	}
	
	if (b_wins)
		path=b
	else //# Join, and ensure there's a separator.
	{ 
		if (path.endsWith('/') || path.endsWith('\\')) {
			if ("/\\".contains(b[0]))
				path += b.slice(1)
			else
				path += b
		}
		else if (path.endsWith(':'))
			path +=b
		else {
			if ("/\\".contains(b[0]))
				path += b
			else
				path += '\\' + b
		}
	}
		
	return path
}

//~ """Split a pathname.
//~ Return tuple (head, tail) where tail is everything after the final slash.
//~ Either part may be empty."""
File.pathSplit=function(p) {
	var d = splitdrive(p)[0]
	var p = splitdrive(p)[1]
	var i=p.length
	while( i && !"/\\".contains(p[i-1]))
		i--;
	var head = p.slice(0,i)
	var tail = p.slice(i)
	var head2=head
	while(head2 && (head2.endsWith('/')||head2.endsWith('\\')))
		head2 = head2.slice(0,head2.length-1)
	if (head2)
		head=head2
	return [ d + head, tail]
}

/*function tests()
{
	//~ print(join('c:\\foo', 'bar'))
	//~ print(join('c:\\foo\\', 'bar'))
	//~ print(join('c:\\foo\\', '\\bar')) //replaces
	//~ print(join('c:\\foo\\', 'new\\bar')) //replaces
	//~ print(join('g:', '/a')) 
	//~ print(join('g:', '\\a')) 
	//~ print(join('g:/', '/a')) 
	//~ print(join('c:/a', '/b')) 
	//~ print(join('c:/', 'd:/')) 
	//~ print(join('c:', 'd:/')) 
	
	print(split('')) 
	print(split('c:')) 
	print(split('c:\\')) 
	print(split('c:/')) 
	print(split('c:\\foo')) 
	print(split('c:\\foo\\bar.txt')) 
	print(split('c:/foo/bar.txt')) 
	print(split('\\\\drive\\foo')) 
	print(split('\\\\drive')) 
	
}
tests()*/
