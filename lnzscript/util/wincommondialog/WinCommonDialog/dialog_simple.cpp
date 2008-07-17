#include "WinCommonDialog.h"
#include "dialog_simple.h"


const char* documentationSimple =
"WinCommonDialog simple {type} {title} {text}\n"
"(Returns result through exit code.)\n"
"\n"
"Types:\n"
"yesno\treturns 2 if yes, 1 if no.\n"
"okcancel\treturns 2 if ok, 0 if cancel.\n"
"yesnocancel\treturns 2 if yes, 1 if no, 0 if cancel\n"
"info\n"
"error\n"
"warning\n";


int dialog_simple(int argc, _TCHAR* argv[])
{
	if (argc <= 1 || wcscmp(argv[1],_T("/?"))==0) { puts(documentationSimple); return ErrorResult; }

	int result;
	_TCHAR* type = get_argument(1, argc, argv);
	_TCHAR* title = get_argument(2, argc, argv);
	_TCHAR* text = get_argument(3, argc, argv);

	if (wcscmp(type,_T("yesno"))==0)
	{
		result = MessageBox(NULL, text, title,  MB_YESNO | MB_ICONQUESTION);
		if (result==IDYES) return 2;
		else if (result==IDNO) return 1;
		else return ErrorResult;
	}
	else if (wcscmp(type,_T("okcancel"))==0)
	{
		result = MessageBox(NULL, text, title,  MB_OKCANCEL | MB_ICONQUESTION);
		if (result==IDOK) return 2;
		else if (result==IDCANCEL) return 0;
		else return ErrorResult;
	}
	else if (wcscmp(type,_T("yesnocancel"))==0)
	{
		result = MessageBox(NULL, text, title,  MB_YESNOCANCEL | MB_ICONQUESTION);
		if (result==IDYES) return 2;
		else if (result==IDNO) return 1;
		else if (result==IDCANCEL) return 0;
		else return ErrorResult;
	}
	else if (wcscmp(type,_T("info"))==0)
	{
		result = MessageBox(NULL, text, title,  MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	else if (wcscmp(type,_T("error"))==0)
	{
		result = MessageBox(NULL, text, title,  MB_OK | MB_ICONERROR);
		return 0;
	}
	else if (wcscmp(type,_T("warning"))==0)
	{
		result = MessageBox(NULL, text, title,  MB_OK | MB_ICONWARNING);
		return 0;
	}
	else
	{
		puts("Dialog type was not recognized. Run with no arguments to see doc.");
		return ErrorResult;
	}
}