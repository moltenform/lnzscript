//Ecma script E262 edition 3
//http://www.mozilla.org/js/language/E262-3.pdf

///Function:(Global).eval
///Arguments:string strCode
///Returns:Object objResult
///Doc:Parse strCode and run it as a script. If the parse fails, generate a runtime error.
///Implementation:Javascript
{}
///Function:(Global).parseInt
///Arguments:string strDigits, int nBase
///Returns:int nResult
///Doc:The parseInt function turns a string representation of a number into an integer.
///Example: parseInt('135',10) == 135 //base 10
///Implementation:Javascript
{}
///Function:(Global).parseFloat
///Arguments:string strDigits
///Returns:double fResult
///Doc:The parseFloat function turns a string representation of a floating-point number into a number.
///Implementation:Javascript
{}
///Function:(Global).escape
///Arguments:string strInput
///Returns:string strOutput
///Doc:Replaces non-ascii characters in the string with hex escape sequences.
///Implementation:Javascript
{}
///Function:(Global).unescape
///Arguments:string strInput
///Returns:string strOutput
///Doc:Restores original string from escape() function
///Implementation:Javascript
{}
///Function:(Global).isNaN
///Arguments:number input
///Returns:bool isNotANumber
///Doc:Returns true if the input is the value NaN, and false otherwise.
///Implementation:Javascript
{}
///Function:(Global).isFinite
///Arguments:number input
///Returns:bool isFinite
///Doc:Returns false if the input is NaN, positive infinity, or negative infinity. Returns true otherwise.
///Implementation:Javascript
{}
//====================

///Function:Array.concat
///Arguments:array ar2
///Returns:array arCombined
///Doc:Returns an array consisting of the elements of the original array followed bt elements of the second arraty. (Combines two arrays).
///Implementation:Javascript
{}
///Function:Array.pop
///Arguments:
///Returns:value
///Doc:The last element of the array is removed from the array and returned.
///Implementation:Javascript
{}
///Function:Array.push
///Arguments:value
///Returns:int nLength
///Doc:A new element is appended onto the end of the array. The new length of the array is returned.
///Implementation:Javascript
{}
///Function:Array.shift
///Arguments:
///Returns:value
///Doc:The first element of the array is removed from the array and returned.
///Implementation:Javascript
{}
///Function:Array.unshift
///Arguments:value
///Returns:
///Doc:The value is prepended to the array, increasing the length by 1 and preserving the existing elements of the array.
///Implementation:Javascript
{}
///Function:Array.join
///Arguments:string seperator
///Returns:string strJoined
///Doc:Combines an array of strings into one long string, delimited by seperator.
///Implementation:Javascript
{}
///Function:Array.slice
///Arguments:int nStart, int nEnd
///Returns:array arSlice
///Doc:Returns a new array that has elements from the slice of array.
///Implementation:Javascript
///Example: var a =[1,2,3,4,5]; b = a.slice(0,3); //1 2 3
{}
///Function:Array.reverse
///Arguments:
///Returns:array arReversed
///Doc:Reverses order of items in array.
///Implementation:Javascript
{}
///Function:Array.sort
///Arguments:function fnCompare=null
///Returns:array arSorted
///Doc:Sorts elements of array. You can provide a custom comparison function. The comparison function should take 2 arguments, x,y, and return -1 if x<y, 0 if x==y, or 1 if x>y.
///Implementation:Javascript
{}
//================{}
///Function:String.fromCharCode
///Arguments:int nUnicode
///Returns:string strCharacter
///Doc:Returns a string value, converting arguments into characters.
///Example: var a = String.fromCharCode(97);
///Implementation:Javascript
{}
///Function:String.charAt
///Arguments:int nIndex
///Returns:string strCharacter
///Doc:Returns string containing character at position pos (where 0 refers to the first character).
///Example: var s = "hello"; var h = s.charAt(0);
///Implementation:Javascript
{}
///Function:String.charCodeAt
///Arguments:int nIndex
///Returns:int nUnicode
///Doc:Returns unicode or ascii value of character at position pos (where 0 refers to the first character).
///Implementation:Javascript
{}
///Function:String.indexOf
///Arguments:string strSearch, int nPosition=0
///Returns:int nIndex
///Doc:Searches for strSearch inside the string, and returns the index at which it is found. If the string is not found, -1 is returned. Provide a position to specify an index to start searching at.
///Example: var s = "what is the difference"; if (s.indexOf('the')!=-1) print('the sentence contained "the"');
///Implementation:Javascript
{}
///Function:String.lastIndexOf
///Arguments:string strSearch, int nPosition=nLength
///Returns:int nIndex
///Doc:Searches for strSearch backwards (from right to left) inside the string, and returns the index at which it is found. If the string is not found, -1 is returned. Provide a position to specify an index to start searching at.
///Implementation:Javascript
{}
///Function:String.split
///Arguments:string strSeperator
///Returns:array arSplit
///Doc:Splits input string into an array of substrings. Call .split('') to split into characters. A RegExp object can also be passed.
///Example: var s = "what is the difference"; var arWords = s.split(' '); //splits into array of words
///Implementation:Javascript
{}
///Function:String.substring
///Arguments:int nStart, int nEnd=nLength
///Returns:array arSplit
///Doc:Return substring of the input. If an end index is not provided, returns the string from the nth position to the end of the string.
///Example: var s = "abcdefg"; var sSlice = s.substring(0,3); //abc
///Implementation:Javascript
{}
///Function:String.toLowerCase
///Arguments:
///Returns:string strLower
///Doc:Convert string to lower case.
///Implementation:Javascript
{}
///Function:String.toUpperCase
///Arguments:
///Returns:string strUpper
///Doc:Convert string to upper case.
///Implementation:Javascript
{}
///Function:String.match
///Arguments:RegExp re
///Returns:string strFound
///Doc: Matches regular expression. Returns string matched if successful. If no match, returns null.
///Implementation:Javascript
///Example:var re=/(a)(b)/; print(s.replace(re, '$2$1')); //replaces ab with ba in the string.
{}
///Function:String.replace 
///Arguments:RegExp re, string strReplaceValue/function fnReplace
///Returns:string strResult
///Doc: Use regular expression to replace in string. If regular expression is global, such as /a/g, then replaces all instances. Replacement string can contain $0, referring to matched string, or $1, referring to first match group and so on. Replacement function, if given, will be passed string, and is expected to return a string.
///Implementation:Javascript
{}
///Function:String.search
///Arguments:RegExp re
///Returns:int nIndex
///Doc: Searches for regular expression in string. If found, returns position in string, otherwise returns -1.
///Implementation:Javascript
{}
///Function:String.slice
///Arguments:int nStart, int nEnd
///Returns:string strSlice
///Doc: Return substring from nStart to nEnd. If start is negative, it is treated as (sourceLength+start) where sourceLength is the length of the string. If end is negative, it is treated as (sourceLength+end) where sourceLength is the length of the string.
///Implementation:Javascript
{}
///Function:String.replace
///Arguments:string strFind, string strReplaceValue
///Returns:string strResult
///Doc: Replace one instance of strFind with strReplaceValue. Note that if a regular expression is passed, behavior is different.
///Implementation:Javascript
{}
//================

///Function:Number.toString
///Arguments:int nBase=10
///Returns:string strNumber
///Doc: Convert number to string, in the given base.
///Implementation:Javascript
{}
///Function:Number.toFixed
///Arguments:int nDigits
///Returns:string strNumber
///Doc: Convert number to string, with given number of decimal digits.
///Implementation:Javascript
///Example: var n = 1.55555; print(n.toFixed(2));
{}
///Function:Number.toExponential
///Arguments:
///Returns:string strNumber
///Doc: Return number in exponential form (scientific notation).
///Implementation:Javascript
{}
///Function:Number.toPrecision
///Arguments:int nDigits
///Returns:string strNumber
///Doc: Return number with precision (uses rounding and scientific notation as necessary).
///Implementation:Javascript
{}

//================

///Function:Math.abs
///Arguments:number input
///Returns:number absInput
///Doc:Returns the absolute value of its argument (same magnitude but positive sign).
///Implementation:Javascript
{}
///Function:Math.acos
///Arguments:double input
///Returns:double arcCosine
///Doc:Compute arc cosine.
///Implementation:Javascript
{}
///Function:Math.asin
///Arguments:double input
///Returns:double arcSine
///Doc:Compute arc sine.
///Implementation:Javascript
{}
///Function:Math.atan
///Arguments:double input
///Returns:double arcTan
///Doc:Compute arc tangent.
///Implementation:Javascript
{}
///Function:Math.atan2
///Arguments:double y, double x
///Returns:double angleInRadians
///Doc:Computes the angle in radians from the origin to the point (x,y).
///Implementation:Javascript
{}
///Function:Math.ceil
///Arguments:double input
///Returns:int output
///Doc:Rounds double up to next integer.
///Implementation:Javascript
{}
///Function:Math.cos
///Arguments:double input
///Returns:double fcos
///Doc:Compute cosine.
///Implementation:Javascript
{}
///Function:Math.exp
///Arguments:double input
///Returns:double exp
///Doc:Compute e to the (argument) power.
///Implementation:Javascript
{}
///Function:Math.floor
///Arguments:double input
///Returns:int output
///Doc:Rounds double down to an integer.
///Implementation:Javascript
{}
///Function:Math.log
///Arguments:double input
///Returns:double naturalLog
///Doc:Compute natural (base e) logarithm. To use another base, use Math.log(x)/Math.log(base)
///Implementation:Javascript
{}
///Function:Math.max
///Arguments:double a, double b
///Returns:double max
///Doc:Returns larger of the arguments.
///Implementation:Javascript
{}
///Function:Math.min
///Arguments:double a, double b
///Returns:double min
///Doc:Returns smaller of the arguments.
///Implementation:Javascript
{}
///Function:Math.pow
///Arguments:double x, double power
///Returns:double result
///Doc:Returns x raised to a power.
///Implementation:Javascript
{}
///Function:Math.random
///Arguments:
///Returns:double fRandom
///Doc:Returns pseudo-random double between 0 and 1. The value is greater than or equal to 0 and less than 1.
///Implementation:Javascript
{}
///Function:Math.round
///Arguments:double input
///Returns:int output
///Doc:Rounds double to the closest integer. Also, if input is 3.5, rounds up to 4, and so on.
///Implementation:Javascript
{}
///Function:Math.sin
///Arguments:double input
///Returns:double fsin
///Doc:Compute sine.
///Implementation:Javascript
{}
///Function:Math.sqrt
///Arguments:double input
///Returns:double sqrt
///Doc:Compute square root.
///Implementation:Javascript
{}
///Function:Math.tan
///Arguments:double input
///Returns:double ftan
///Doc:Compute tangent.
///Implementation:Javascript
{}
//================{}
///Function:Date.(constructor)
///Arguments:int year, int month, [int date, [int hours, [int minutes, [int seconds]]]]
///Returns:date dateOutput
///Doc:Construct Date object
///Implementation:Javascript
{}
///Function:Date.parse
///Arguments:string strDate
///Returns:date dateOutput
///Doc:Construct Date object from string
///Example: var date = Date.parse('Janurary 7 1980');
///Implementation:Javascript
{}
///Function:Date.UTC
///Arguments:int year, int month, [int date, [int hours, [int minutes, [int seconds]]]]
///Returns:int nUtc
///Doc:Calculate utc (coordinated universal time)
///Implementation:Javascript
{}
///Function:Date.toString
///Arguments:
///Returns:string strDate
///Doc:Returns representation of date as a string. 
///Example: var date = Date.parse('Janurary 7 1980'); var s = date.toString();
///Implementation:Javascript
{}
///Function:Date.getTime
///Arguments:
///Returns:int nMilliseconds
///Doc:Returns time from Jan1,1970 in milliseconds. If time is before this date, can be negative.
///Implementation:Javascript
{}
///Function:Date.setTime
///Arguments:int nMilliseconds
///Returns:
///Doc:Set time from Jan1,1970 in milliseconds. If time is before this date, can be negative.
///Implementation:Javascript
{}
///Function:Date.getFullYear
///Arguments:
///Returns:year
///Doc:Returns year of date. See specification for more Date methods such as getMonth, getSeconds...
///Implementation:Javascript
{}
///Function:Date.setFullYear
///Arguments:int year
///Returns:
///Doc:Set year of date.  See specification for more Date methods such as setMonth, setSeconds...
///Implementation:Javascript
{}
///Function:Date.getMilliseconds
///Arguments:
///Returns:milliseconds
///Doc:Returns milliseconds. See specification for more Date methods such as getMonth, getSeconds...
///Implementation:Javascript
{}
///Function:Date.setMilliseconds
///Arguments:int ms
///Returns:
///Doc:Returns milliseconds. See specification for more Date methods such as getMonth, getSeconds...
///Implementation:Javascript
{}
//========================

///Function:RegExp.(constructor)
///Arguments:string strPattern, string strFlags=""
///Returns:RegExp re
///Doc:Creates RegExp object. Alternatively use the syntax /pattern/g instead of new RegExp('pattern','g'); Flags can include g (global), i (ignoreCase), m (multiline, anchors match at lines)
///Implementation:Javascript
{}
///Function:RegExp.exec
///Arguments:string strString
///Returns:array arResults
///Doc:Performs regex match on string, and returns an array of results. The first element of the array is the found string, and the remaining are captured subgroups.
///Implementation:Javascript
///Example:var re=/(\d+),(\d+)/; var a = re.exec('12-2456'); //item 1 is 12, item 2 is 2456
{}





