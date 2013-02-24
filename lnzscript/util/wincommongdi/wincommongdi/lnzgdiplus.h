

// adapted from msdn
// http://msdn.microsoft.com/en-us/library/windows/desktop/ms533837%28v=vs.85%29.aspx
int ConvertImageFromOneFormatToAnother(const WCHAR* infile, const WCHAR* outfile)
{
	if (!DoesFileExist(infile)) { showerr("input file not found"); return 1; }
	if (DoesFileExist(outfile)) { showerr("file already exists"); return 1; }
	const WCHAR* strMimetype = getmimetypefromextension(outfile);
	if (!strMimetype) { showerr("did not recognize output image type"); return 1; }
	try {
		// Get the CLSID of the encoder.
		CLSID encoderClsid={0};
		int ret = GetEncoderClsid(strMimetype, &encoderClsid);
		if (ret<0) {  showerr("could failed to load encoder"); return 1; }

		Image image(infile);
		Status stat = image.Save(outfile, &encoderClsid, NULL);
		if (stat != Ok)
		{
			showerr("save failed with code stat = %d\n", stat);
			return 1;
		}
	} catch (...) { showerr("Exception occurred."); return 1; }
	return 0;
}

int SaveHBitmapToFile(HBITMAP hbitmap, const WCHAR* outfile)
{
	if (DoesFileExist(outfile)) { showerr("file already exists"); return 1; }
	const WCHAR* strMimetype = getmimetypefromextension(outfile);
	if (!strMimetype) { showerr("did not recognize output image type"); return 1; }
	try
	{
		// Get the CLSID of the encoder.
		CLSID encoderClsid={0};
		int ret = GetEncoderClsid(strMimetype, &encoderClsid);
		if (ret<0) {  showerr("could failed to load encoder"); return 1; }

		Bitmap* bmp = Bitmap::FromHBITMAP(hbitmap, NULL /*pallete*/);
		Status stat = bmp->Save(outfile, &encoderClsid, NULL);
		delete bmp;
		if (stat != Ok)
		{
			showerr("save failed with code stat = %d\n", stat);
			return 1;
		}
	} catch (...) { showerr("Exception occurred."); return 1; }
	return 0;
}

class ClipboardCloser { public: ~ClipboardCloser() { CloseClipboard(); } };

// reference: http://www.codeproject.com/Articles/42/All-you-ever-wanted-to-know-about-the-Clipboard#readwritebmp
int SaveClipboardToDisk(const WCHAR* outfile)
{
	if (DoesFileExist(outfile)) { showerr("file already exists"); return 1; }
	try
	{
		if (OpenClipboard(NULL /*new owner*/))
		{
			ClipboardCloser closer;
			HBITMAP handle = (HBITMAP)GetClipboardData(CF_BITMAP);
			if (handle)
			{
				return SaveHBitmapToFile(handle, outfile);
			}
			else
			{
				showerr("clipboard not in bitmap format"); 
				return 1;
			}
		}
		else
		{
			showerr("could not open clipboard"); return 1;
		}
	} catch(...) { showerr("Exception occurred."); return 1; }
	return 0;
}


void PressAltPrintscreen(bool bFullScreen)
{
	if (bFullScreen)
	{
		::keybd_event(VK_SNAPSHOT, 0, 0, 0);
		::Sleep(100);
		::keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0);
	}
	else
	{
		::keybd_event(VK_MENU, 0, 0, 0);
		::keybd_event(VK_SNAPSHOT, 0, 0, 0);
		::Sleep(100);
		::keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0);
		::keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	}
	::Sleep(100);
}

