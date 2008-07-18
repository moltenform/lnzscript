// Scite_msg.cpp : Defines the entry point for the console application.

// Not using precompiled headers
// Note, intentionally not compiling as Unicode.

#include <iostream>
#include <tchar.h>
#include "Scite_msg.h"

const char* documentation = 
"Scite_msg.exe {hwnd} {command}\n"
"Sends command to Scite.\n"
"\n"
"Example:Scite_msg.exe 15342 \"insert:hello\\040world\\0\"\n"
"Send hwnd as decimal number.\n"
"Commands include:\n"
"askfilename:\n"
"askproperty:\n"
"close:\n"
"currentmacro:\n"
"cwd:\n"
"enumproperties:\n"
"exportashtml:\n"
"exportasrtf:\n"
"exportaspdf:\n"
"exportaslatex:\n"
"exportasxml:\n"
"find:\n"
"goto:\n"
"loadsession:\n"
"macrocommand:\n"
"macroenable:\n"
"macrolist:\n"
"menucommand:\n"
"open:\n"
"output:\n"
"property:\n"
"reloadproperties:\n"
"quit:\n"
"replaceall:\n"
"saveas:\n"
"savesession:\n"
"extender:\n"
"focus:";
// See SciTEBase::PerformOne in SciTEBase.cxx

/*
This doesn't really work too well yet.
When sending text, it must end with the literal "\0",
in other words, typing 
>Scite_msg.exe 1245722 "insert:hello_no_spaces\0"
>Scite_msg.exe 1245722 "insert:hello\040world\0"
Otherwise, gibberish is also inserted.

Also, apparently anything with spaces cannot be sent. For some reason it thinks these
are different commands and gets messed up.

But I guess it is ok for now.

Steps to send:
replace \ with \\
replace newline with \n
replace space with \040
replace bell with \a, b with \b, return with \r, v with \v
end with \0

*/

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 3)
	{
		puts(documentation);
		return 1;
	}
	const char* strHwnd = argv[1];
	const char* strAction = argv[2];
	
	char *arg = strchr(strAction, ':');
	if (! arg)
	{
		puts("Invalid command. Should be in form close: or insert:hello");
		return 1;
	}

	// NOTE: not 64-bit safe. Is there a 64bit atoi?
	long nHwnd = atol(strHwnd);
	if (nHwnd==0 || nHwnd==LONG_MAX || nHwnd==LONG_MIN)
	{
		puts("Invalid hwnd. Should be in decimal");
		return 1;
	}
	HWND hwnd = (HWND) nHwnd;

	char * strFormattedAction = new char[strlen(strAction)+5];
	strFormattedAction[0] = '-';
	strcpy(strFormattedAction + 1, strAction);
	strFormattedAction[1+strlen(strAction)] = '\0';
	strFormattedAction[1+strlen(strAction)+1] = '\0';


puts(strFormattedAction);

	SendToHandle(hwnd, strFormattedAction);
	delete [] strFormattedAction;

	return 0;
}

void SendToHandle(HWND hwnd, const char *Message)
{
	COPYDATASTRUCT cds;
	if (strlen(Message)>INT_MAX) return;
	int size = (int) strlen(Message);
	cds.dwData = 0;	
	cds.lpData = (void *)Message;
	cds.cbData = size;
	SendMessage(hwnd, WM_COPYDATA,(WPARAM)NULL,(LPARAM)&cds);
}

