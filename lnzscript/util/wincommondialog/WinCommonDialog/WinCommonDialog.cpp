// WinCommonDialog.cpp : Defines the entry point for the console application
// See http://msdn.microsoft.com/en-us/library/ms645505(VS.85).aspx



#include "stdafx.h"
//#define UNICODE
// I would have had to convert the _TCHAR to the right format.

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"

const char * documentation = 
"WinCommonDialog.exe, Ben Fisher 2008, GPL\n"
"A wrapper over simple Windows dialogs, using return code to pass result.\n"
"Part of Launchorz, http://code.google.com/p/launchorz/\n"
"\n"
"Syntax:\n"
"WinCommonDialog {type} {title} {text}\n"
"\n"
"Types:\n"
"yesno\treturns 2 if yes, 1 if no.\n"
"okcancel\treturns 2 if OK, 0 if cancel.\n"
"yesnocancel\treturns 2 if yes, 1 if no, 0 if cancel\n"
"info\n"
"error\n"
"warning\n"
;


#define ErrorResult 99;
int _tmain(int argc, _TCHAR* argv[])
{
	if (argc<3) { puts(documentation); puts("\nNot enough arguments"); return ErrorResult; }
	_TCHAR* type = argv[1];
	_TCHAR* title = argv[2];
	_TCHAR* text = argv[3];
	int result;

	if (strcmp(type,"yesno")==0)
	{
		result = MessageBox(NULL, text, title,  MB_YESNO | MB_ICONQUESTION);
		if (result==IDYES) return 2;
		else if (result==IDNO) return 1;
		else return ErrorResult;
	}
	else if (strcmp(type,"okcancel")==0)
	{
		result = MessageBox(NULL, text, title,  MB_OKCANCEL | MB_ICONQUESTION);
		if (result==IDOK) return 2;
		else if (result==IDCANCEL) return 0;
		else return ErrorResult;
	}
	else if (strcmp(type,"yesnocancel")==0)
	{
		result = MessageBox(NULL, text, title,  MB_YESNOCANCEL | MB_ICONQUESTION);
		if (result==IDYES) return 2;
		else if (result==IDNO) return 1;
		else if (result==IDCANCEL) return 0;
		else return ErrorResult;
	}
	else if (strcmp(type,"info")==0)
	{
		result = MessageBox(NULL, text, title,  MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	else if (strcmp(type,"error")==0)
	{
		result = MessageBox(NULL, text, title,  MB_OK | MB_ICONERROR);
		return 0;
	}
	else if (strcmp(type,"warning")==0)
	{
		result = MessageBox(NULL, text, title,  MB_OK | MB_ICONWARNING);
		return 0;
	}
	else
	{
		puts("Dialog type was not recognized. Run with no arguments to see doc.");
		return ErrorResult;
	}

	return 0;
}

