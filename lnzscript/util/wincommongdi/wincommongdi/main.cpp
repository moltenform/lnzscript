
#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>
using namespace Gdiplus;

#include "util.h"
#include "lnzgdiplus.h"

const char * documentation = 
"WinCommonLnzImage.exe, Ben Fisher 2013, GPL\n"
"Provide image capability to lnzscript. Does not overwrite existing files.\n"
"Part of Launchorz, http://github.com/downpoured/lnzscript/\n"
"\n"
"WinCommonLnzImage convert infile.bmp outfile.png\n"
"WinCommonLnzImage screenshot outfile.png\n"
"WinCommonLnzImage screenshot outfile.png /fullscreen\n"
"WinCommonLnzImage clipboard out.png\n"
"\n";

int wmain(int argc, WCHAR* argv[])
{
	// Initialize GDI+.
	GdiScopeStarter start;	

	if (argc<=1 || StringAreEqual(argv[1], L"/?") || StringAreEqual(argv[1], L"-h"))
	{
		puts(documentation);
		return 0;
	}
	else if (argc>3 && StringAreEqual(argv[1], L"convert"))
	{
		return ConvertImageFromOneFormatToAnother(argv[2],argv[3]);
	}
	else if (argc>2 && StringAreEqual(argv[1], L"screenshot"))
	{
		bool bFull = (argc>3 && StringAreEqual(argv[3], L"/fullscreen"));
		PressAltPrintscreen(bFull);
		::Sleep(300);
		return SaveClipboardToDisk(argv[2]);
	}
	else if (argc>2 && StringAreEqual(argv[1], L"clipboard"))
	{
		return SaveClipboardToDisk(argv[2]);
	}
	
	puts("wrong number of options or unrecognized command\n");
	puts(documentation);
	return 1;
}
