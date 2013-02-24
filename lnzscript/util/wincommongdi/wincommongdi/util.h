#define null nullptr

inline bool StringEndsWith(const WCHAR* s1, const WCHAR*s2)
{
	size_t len1=wcslen(s1), len2=wcslen(s2);
	if (len2>len1) return false;
	return wcscmp(s1+len1-len2, s2)==0;
}
#define StringAreEqual(s1, s2) (wcscmp((s1),(s2))==0)
#define showerr printf

inline bool DoesFileExist(const WCHAR* s)
{
	DWORD dwAttrib = ::GetFileAttributes(s);
  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

class GdiScopeStarter {
private: GdiplusStartupInput gdiplusStartupInput; ULONG_PTR gdiplusToken;
public: GdiScopeStarter() { GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); }
		~GdiScopeStarter() { GdiplusShutdown(gdiplusToken); }
};

const WCHAR* getmimetypefromextension(const WCHAR* filename)
{
	if (StringEndsWith(filename, L".png")) return L"image/png";
	if (StringEndsWith(filename, L".PNG")) return L"image/png";
	if (StringEndsWith(filename, L".jpg")) return L"image/jpeg";
	if (StringEndsWith(filename, L".JPG")) return L"image/jpeg";
	if (StringEndsWith(filename, L".jpeg")) return L"image/jpeg";
	if (StringEndsWith(filename, L".JPEG")) return L"image/jpeg";
	if (StringEndsWith(filename, L".png")) return L"image/png";
	if (StringEndsWith(filename, L".bmp")) return L"image/bmp";
	if (StringEndsWith(filename, L".BMP")) return L"image/bmp";
	if (StringEndsWith(filename, L".gif")) return L"image/gif";
	if (StringEndsWith(filename, L".GIF")) return L"image/gif";
	if (StringEndsWith(filename, L".tif")) return L"image/tiff";
	if (StringEndsWith(filename, L".TIF")) return L"image/tiff";
	if (StringEndsWith(filename, L".tiff")) return L"image/tiff";
	if (StringEndsWith(filename, L".TIFF")) return L"image/tiff";
	return NULL;
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}
