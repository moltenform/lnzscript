// finds a scite instance.
// original from "scite_other" by  Steve Donovan, 2004
// because the hwnd is passed in, we probably don't need this

BOOL CALLBACK EnumWindowsProc(HWND  hwnd, LPARAM  lParam)
{
  HWND* results = (HWND*)lParam;
  int idx = size_of_array(results);	
  char buff[256];
  GetClassName(hwnd,buff,sizeof(buff));	
  if (strcmp(buff,"DirectorExtension") == 0) {
	printf("found %x\n",hwnd);
	results[idx] = hwnd;
	results[idx+1] = NULL;
  }
  return TRUE;
}

// count until we reach a NULL
static int size_of_array(HWND* results)
{
  int idx = 0;
  // find our place in the output array	
  for (idx = 0; results[idx] != NULL; idx++) ;	
  return idx;
}

void findscite()
{
HWND results[100];
results[0] = 0;
  EnumWindows(EnumWindowsProc,(long)results);
  nmsg = size_of_array(results);

	
	
    SendToHandle(handle,command);	
  
	  
	
}


