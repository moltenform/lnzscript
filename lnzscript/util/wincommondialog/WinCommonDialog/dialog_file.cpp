#include "WinCommonDialog.h"
#include "dialog_file.h"

#include <string>

const char* documentationFile =
"WinCommonDialog file {dialog} {filetype=*}\n"
"(Returns result through stdout.)\n"
"\n"
"Displays dialog where user can choose file.\n"
"Dialog should be one of:\n"
"open\n"
"openmult\n"
"save\n"
"\n"
"filetype, if present, should be in the format \"bmp\" (not \"*.bmp\")\n"
"Otherwise, defaults to All files *.*\n"
"Returns \"<cancel>\" if user cancels.\n"
"Exit code non-zero on error.\n";

int dialog_file(int argc, _TCHAR* argv[])
{
	if (argc <= 1 || wcscmp(argv[1],_T("/?"))==0) { puts(documentationFile); return ErrorResult; }

	_TCHAR* dlgtype = get_argument(1, argc, argv);
	_TCHAR* filetype = NULL;
	if (argc >= 3) filetype = get_argument(2, argc, argv);

	OPENFILENAME ofn;       // common dialog box structure
	WCHAR szFile[16384];     // buffer for file name. Big because of "select multiple files" option

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;

	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0'; // Set lpstrFile[0] to '\0' so that GetOpenFileName does not use the contents of szFile to initialize itself.
	ofn.nMaxFile = sizeof(szFile);
	WCHAR typeBuffer[128];
	// The 3rd argument can be "*", meaning all files, or "bmp", which means *.bmp files. Pass "bmp" and NOT "*.bmp" or ".bmp"
	// Multiple types are not supported currently.
	if (filetype==NULL || wcscmp(filetype,_T("*"))==0)
		ofn.lpstrFilter = L"All Files\0*.*\0"; //note, ends with \0\0
	else
	{
		if (wcslen(filetype) > 10) return ErrorResult;
		
		_snwprintf(typeBuffer, sizeof(typeBuffer), L"%s Files\0*.%s\0\0", filetype, filetype); 
		ofn.lpstrFilter = typeBuffer;
	}
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE) 
	{
		// the result, ofn.lpstrFile, is a Wide (Unicode) string, so convert to Ascii
		char * psz = new char[wcslen(ofn.lpstrFile)+1];
		wsprintfA(psz, "%S", ofn.lpstrFile);
        fputs(psz, stdout);
		delete[] psz;
	}
	else fputs("<cancel>", stdout);
	return 0;
}
