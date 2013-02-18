
#include <QString.h>
#include <QStringList.h>
#include <QFile.h>
#include "parse_js.h"


// Transforms @'c:\directory' into 'c:\\directory'
// Pass in the string as const so that [ ] is faster.
QString processLiteralStrings(const QString& strInput)
{
	if (! strInput.contains(QString("@")))
		return strInput; //no @ in the string, so don't do anything
	
	QString strParsed;
	strParsed.reserve( strInput.length() + 5); //allocate as much as the input + 5. Just an estimate, doesn't matter if we are over/under
	int len = 0;
	
	
	enum states {NO_QUOTE, SINGLE_QUOTE, DOUBLE_QUOTE, SINGLE_TRANSFORM, LINE_COMMENT, MULTI_COMMENT};
	#define SQUOTE '\''
	#define DQUOTE '"'
	#define BSLASH '\\'
	int state = NO_QUOTE;
	int i;
	for (i=0;i<strInput.length()-1; i++ )
	{
		if (state==LINE_COMMENT || state==MULTI_COMMENT)
		{
			if (strInput[i]=='\n' && state==LINE_COMMENT) state = NO_QUOTE;
			else if (strInput[i]=='*' && strInput[i+1]=='/' && state==MULTI_COMMENT) state = NO_QUOTE;
			
			strParsed[len++] = strInput[i];
		}
		else
		{
			if (strInput[i]=='@' && strInput[i+1]==SQUOTE && state==NO_QUOTE)
			{
				state = SINGLE_TRANSFORM;
				strParsed[len++] = SQUOTE;
				i ++; // skip over the next char!
			}
			else if (strInput[i] == BSLASH && state == SINGLE_TRANSFORM)
			{
				// add two backslashes!
				strParsed[len++] = BSLASH;
				strParsed[len++] = BSLASH;
			}
			// 'this is \' one long string' , backslash escapes closing '
			else if (strInput[i] == BSLASH && strInput[i+1] == SQUOTE && (i-1>=0) && strInput[i-1] != BSLASH && state == SINGLE_QUOTE) 
			{
				//remain in the SINGLE_QUOTE state
				strParsed[len++] = strInput[i];
				i++; //skip to next char
				strParsed[len++] = strInput[i];
			}
			// "this is \" one long string" , backslash escapes closing "
			else if (strInput[i] == BSLASH && strInput[i+1] == DQUOTE && (i-1>=0) && strInput[i-1] != BSLASH && state == DOUBLE_QUOTE)
			{
				//remain in the DOUBLE_QUOTE state
				strParsed[len++] = strInput[i];
				i++; //skip to next char
				strParsed[len++] = strInput[i];
			}
			else if (strInput[i]==SQUOTE)
			{
				if (state==NO_QUOTE) state = SINGLE_QUOTE;
				else if (state==SINGLE_QUOTE) state = NO_QUOTE;
				else if (state==DOUBLE_QUOTE) state = DOUBLE_QUOTE; // no op
				else if (state==SINGLE_TRANSFORM) state = NO_QUOTE; // end the transform
				
				strParsed[len++] = SQUOTE; //regardless, write it over
			}
			else if (strInput[i]==DQUOTE)
			{
				if (state==NO_QUOTE) state = DOUBLE_QUOTE;
				else if (state==SINGLE_QUOTE) state = SINGLE_QUOTE; // no op
				else if (state==DOUBLE_QUOTE) state = NO_QUOTE; // end quote
				else if (state==SINGLE_TRANSFORM) state = SINGLE_TRANSFORM; // no op
				
				strParsed[len++] = DQUOTE; //regardless, write it over
			}
			else if (strInput[i] == '/' && strInput[i+1] == '/' && state == NO_QUOTE)
			{
				state = LINE_COMMENT;
				strParsed[len++] = strInput[i];
			}
			else if (strInput[i] == '/' && strInput[i+1] == '*' && state == NO_QUOTE)
			{
				state = MULTI_COMMENT;
				strParsed[len++] = strInput[i];
			}
			else
			{
				strParsed[len++] = strInput[i];
			}
		}
	}
	strParsed[len++] = strInput[i]; //we don't transform the last one, anyways.
	return strParsed;
}



/*
We need to take into account comments.
You might think, why is that important? What would be wrong about changing quotes inside a comment?
The following fails:

//  fakestring = @'
now /here/ is some \other\ code //gets messed up

It thinks that a string was starting.

*/
