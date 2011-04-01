
// Note: if you set the error string, you HAVE to return null not Py_none, otherwise python gets in a weird state!

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Scintilla.h"
//~ #include "Accessor.h"
#include "Extender.h"

#include "SString.h"
#include "SciTEKeys.h"
#include "IFaceTable.h"

#include "PythonExtension.h"

#include "Platform.h"

#ifdef _MSC_VER
	#pragma warning(disable: 4100) // unreferenced formal parameter
	#pragma warning(disable: 4996) // unsafe calls (deprecated stdio)
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

static const char* c_szExtensionModName = "scite_extend"; //looks for the file scite_extend.py
static bool fPythonInitialized = false;
static inline bool FInitialized() { return fPythonInitialized; }
static ExtensionAPI *_host = NULL;

void PythonExtension::InitializePython()
{
	if (!fPythonInitialized)
	{
		Py_NoSiteFlag = 1; //prevents from trying to call 'import site', when there isn't a site.py
		Py_Initialize();
		SetupPythonNamespace();
		fPythonInitialized = true;
	}
}

PythonExtension::PythonExtension() {}
PythonExtension::~PythonExtension() {}
void traceOut(const char *szText1, const char *szText2=NULL, int n=-99)
{
	if (!_host) return;
	_host->Trace(szText1); if (szText2) _host->Trace(szText2); 
	if (n==-99) return;
	char buf[256] = {0};
	snprintf(buf, sizeof(buf), "%d", n);
	_host->Trace(buf);
}
void PythonExtension::displayText(const char *szText) { traceOut(szText, "\n"); }
bool PythonExtension::displayError(const char *szError) { traceOut(">Python Error:", szError); traceOut("\n"); return true; }
bool PythonExtension::displayError(const char *szError, const char *szError2)
{
	traceOut(">Python Error:", szError);  traceOut(" ", szError2); traceOut("\n"); return true;
}

PythonExtension &PythonExtension::Instance() {
	static PythonExtension singleton;
	return singleton;
}


bool PythonExtension::Initialise(ExtensionAPI *host)
{
	_host = host;
	displayText("log:PythonExtension::Initialise");
	
	char* szDelayLoad = _host->Property("ext.python.delayload");
	if (!(szDelayLoad && szDelayLoad[0]!='\0' && (szDelayLoad[0]!='0'||strlen(szDelayLoad)>1)))
	{
		InitializePython();
		_runCallback("OnStart", 0, NULL);
	}
	
	return true;
}

bool PythonExtension::OnExecute(const char *s)
{
	InitializePython();
	int nResult = PyRun_SimpleString(s);
	if (nResult == 0) { return true; }
	else { PyErr_Print(); return false; }
}

bool PythonExtension::Finalise()
{
	/* by this point _host is already invalid */
	_host = NULL;
	return false;
}

bool PythonExtension::Clear()
{
	displayText("log:PythonExtension::Clear");
	return false;
}

bool PythonExtension::Load(const char *fileName)
{
	FILE* f = fopen(fileName, "r");
	if (!f) { _host->Trace(">Python: could not open file.\n"); return false; }
	int nResult = PyRun_SimpleFileEx(f, fileName, 1); //Python will close file handle.
	if (nResult == 0) { return true; }
	else { PyErr_Print(); return false; }
}

bool PythonExtension::InitBuffer(int index)
{
	displayText("log:PythonExtension::InitBuffer");
	
	
	return false;
}

bool PythonExtension::ActivateBuffer(int index)
{
	displayText("log:PythonExtension::Activatebuffer");
	
	
	return false;
}

bool PythonExtension::RemoveBuffer(int index)
{
	displayText("log:PythonExtension::removebuffer");
	
	
	return false;
}



// callbacks //////////////////

bool PythonExtension::OnOpen(const char *fileName)
{
	if (!FInitialized()) return false;
	return _runCallback("OnOpen", 1, fileName);
}
bool PythonExtension::OnClose(const char *fileName)
{
	if (!FInitialized()) return false;
	return _runCallback("OnClose", 1, fileName);
}
bool PythonExtension::OnSwitchFile(const char *fileName)
{
	if (!FInitialized()) return false;
	return _runCallback("OnSwitchFile", 1, fileName);
}
bool PythonExtension::OnBeforeSave(const char *fileName)
{
	if (!FInitialized()) return false;
	return _runCallback("OnBeforeSave", 1, fileName);
}
bool PythonExtension::OnSave(const char *fileName)
{
	if (!FInitialized()) return false;
	return _runCallback("OnSave", 1, fileName);
}
bool PythonExtension::OnSavePointReached()
{
	if (!FInitialized()) return false;
	return _runCallback("OnSavePointReached", 0, NULL);
}
bool PythonExtension::OnSavePointLeft()
{
	if (!FInitialized()) return false;
	return _runCallback("OnSavePointLeft", 0, NULL);
}

bool PythonExtension::OnChar(char ch)
{
	if (!FInitialized()) return false;
	CPyObjStrong pArgs = Py_BuildValue("(i)", (int) ch);
	return _runCallbackArgs("OnChar", pArgs);
}
bool PythonExtension::OnKey(int keycode, int modifiers)
{
	if (!FInitialized()) return false;
	int fShift = (SCMOD_SHIFT & modifiers) != 0 ? 1 : 0;
	int fCtrl = (SCMOD_CTRL & modifiers) != 0 ? 1 : 0;
	int fAlt = (SCMOD_ALT & modifiers) != 0 ? 1 : 0;
	CPyObjStrong pArgs = Py_BuildValue("(i,i,i,i)", (int) keycode, fShift, fCtrl, fAlt);
	return _runCallbackArgs("OnKey", pArgs);
}
bool PythonExtension::OnDoubleClick()
{
	if (!FInitialized()) return false;
	return _runCallback("OnDoubleClick", 0, NULL);
}
bool PythonExtension::OnMarginClick()
{
	if (!FInitialized()) return false;
	return _runCallback("OnMarginClick", 0, NULL);
}
bool PythonExtension::OnDwellStart(int pos, const char *word)
{
	if (!FInitialized()) return false;
	if (pos == 0 && word[0] == 0)
	{
		return _runCallback("OnTipEnd", 0, NULL);
	}
	else
	{
		CPyObjStrong pArgs = Py_BuildValue("(i,s)", pos, word);
		return _runCallbackArgs("OnTipStart", pArgs);
	}
}
bool PythonExtension::OnUserListSelection(int type, const char *selection)
{
	if (!FInitialized()) return false;
	CPyObjStrong pArgs = Py_BuildValue("(i,s)", type, selection);
	return _runCallbackArgs("OnUserListSelection", pArgs);
}

// implementation //////////////////

bool PythonExtension::_runCallback(const char* szNameOfFunction, int nArgs, const char* szArg1)
{
	if (nArgs == 0)
	{
		return _runCallbackArgs(szNameOfFunction, NULL);
	}
	else if (nArgs == 1)
	{
		CPyObjStrong pArgs = Py_BuildValue("(s)", szArg1);
		return _runCallbackArgs(szNameOfFunction, pArgs);
	}
	else
	{
		return displayError("Unexpected: calling _runCallback, only 0/1 args supported."); 
	}
}

bool PythonExtension::_runCallbackArgs(const char* szNameOfFunction, PyObject* pArgsBorrowed)
{
	//displayError("received evt", szNameOfFunction);
	
	CPyObjStrong pName = PyString_FromString(c_szExtensionModName);
	if (!pName) { return displayError("Unexpected error: could not form string."); }
	CPyObjStrong pModule = PyImport_Import(pName);
	if (!pModule) {
		displayError("Error importing module.");
		PyErr_Print();
		return false;
	}
	CPyObjWeak pDict = PyModule_GetDict(pModule);
	if (!pDict) { return displayError("Unexpected: could not get module dict."); }
	CPyObjWeak pFn = PyDict_GetItemString(pDict, szNameOfFunction);
	if (!pFn) { /* displayError("Module does not define that callback."); */ return false;	}
	if (!PyCallable_Check(pFn)) { return displayError("callback not a function", szNameOfFunction); }

	CPyObjStrong pResult = PyObject_CallObject(pFn, pArgsBorrowed);
	if (!pResult) {
		displayError("Error in callback ", szNameOfFunction);
		PyErr_Print();
		return false;
	}
	/* bubble event up by default, unless they explicitly return false. */
	if (PyBool_Check(pResult) && pResult == Py_False)
		return true; // do not bubble up
	else
		return false; // bubble up
}

////////python impls//////////////////


PyObject* pyfun_LogStdout(PyObject* self, PyObject* pArgs)
{
	char* szLogStr = NULL; /* we do NOT own this pointer, we cannot free it. */
	if (!PyArg_ParseTuple(pArgs, "s", &szLogStr)) return NULL;
	_host->Trace(szLogStr);
	Py_INCREF(Py_None);
	return Py_None;
}
PyObject* pyfun_MessageBox(PyObject* self, PyObject* pArgs)
{
	char* szLogStr = NULL; /* we do NOT own this pointer, we cannot free it. */
	if (!PyArg_ParseTuple(pArgs, "s", &szLogStr)) return NULL;
#ifdef _WIN32
	MessageBoxA(NULL, szLogStr, NULL , 0);
#endif
	Py_INCREF(Py_None);
	return Py_None;
}
PyObject* pyfun_SciteOpenFile(PyObject* self, PyObject* pArgs)
{
	
	char* szFilename = NULL; /* we do NOT own this pointer, we cannot free it. */
	if (!PyArg_ParseTuple(pArgs, "s", &szFilename)) return NULL;
	if (szFilename) {
		SString cmd = "open:";
		cmd += szFilename;
		cmd.substitute("\\", "\\\\");
		_host->Perform(cmd.c_str());
	}
	Py_INCREF(Py_None);
	return Py_None;
}
PyObject* pyfun_GetProperty(PyObject* self, PyObject* pArgs)
{
	char* szPropName = NULL; /* we do NOT own this pointer, we cannot free it. */
	if (!PyArg_ParseTuple(pArgs, "s", &szPropName)) return NULL;
	char *value = _host->Property(szPropName);
	if (value)
	{
		CPyObjWeak objRet = PyString_FromString(value); // weakref because we are giving ownership.
		delete[] value;
		return objRet;
	}
	else
	{
		Py_INCREF(Py_None);
		return Py_None;	
	}
}
// SetProperty(key, value).
PyObject* pyfun_SetProperty(PyObject* self, PyObject* pArgs) 
{
	char* szPropName = NULL; char* szPropValue = NULL; /* we do NOT own this pointer, we cannot free it. */
	if (!PyArg_ParseTuple(pArgs, "ss", &szPropName, &szPropValue)) return NULL;
	_host->SetProperty(szPropName, szPropValue); // it looks like SetProperty allocates, don't need key and val on the heap.
	Py_INCREF(Py_None);
	return Py_None;
}
PyObject* pyfun_UnsetProperty(PyObject* self, PyObject* pArgs)
{
	char* szPropName = NULL; /* we do NOT own this pointer, we cannot free it. */
	if (!PyArg_ParseTuple(pArgs, "s", &szPropName)) return NULL;
	_host->UnsetProperty(szPropName);
	Py_INCREF(Py_None);
	return Py_None;
}
inline bool GetPaneFromInt(int nPane, ExtensionAPI::Pane* outPane)
{
	if (nPane==0) *outPane = ExtensionAPI::paneEditor;
	else if (nPane==1) *outPane = ExtensionAPI::paneOutput;
	else return false;
	return true;
}
//pane functions. use a python wrapper to make this easier.
PyObject* pyfun_pane_Append(PyObject* self, PyObject* pArgs)
{
	char* szText = NULL; /* we do NOT own this pointer, we cannot free it. */
	int nPane = -1; ExtensionAPI::Pane pane;
	if (!PyArg_ParseTuple(pArgs, "is", &nPane, &szText)) return NULL;
	if (!GetPaneFromInt(nPane, &pane)) { PyErr_SetString(PyExc_RuntimeError,"Invalid pane, must be 0 or 1."); return NULL;}
	_host->Insert(pane, _host->Send(pane, SCI_GETLENGTH, 0, 0), szText);
	Py_INCREF(Py_None);
	return Py_None;
}

PyObject* pyfun_pane_Insert(PyObject* self, PyObject* pArgs)
{
	char* szText = NULL; /* we do NOT own this pointer, we cannot free it. */
	int nPane = -1, nPos=-1; ExtensionAPI::Pane pane;
	if (!PyArg_ParseTuple(pArgs, "iis", &nPane, &nPos, &szText)) return NULL;
	if (nPos<0) return NULL;
	if (!GetPaneFromInt(nPane, &pane)) { PyErr_SetString(PyExc_RuntimeError,"Invalid pane, must be 0 or 1."); return NULL;}
	_host->Insert(pane,nPos, szText);
	Py_INCREF(Py_None);
	return Py_None;
}
PyObject* pyfun_pane_Remove(PyObject* self, PyObject* pArgs)
{
	int nPane = -1, nPosStart=-1, nPosEnd=-1; ExtensionAPI::Pane pane;
	if (!PyArg_ParseTuple(pArgs, "iii", &nPane, &nPosStart, &nPosEnd)) return NULL;
	if (nPosStart<0 || nPosEnd<0) return NULL;
	if (!GetPaneFromInt(nPane, &pane)) { PyErr_SetString(PyExc_RuntimeError,"Invalid pane, must be 0 or 1."); return NULL;}
	_host->Remove(pane,nPosStart,nPosEnd);
	Py_INCREF(Py_None);
	return Py_None;
}
PyObject* pyfun_pane_TextRange(PyObject* self, PyObject* pArgs)
{
	int nPane = -1, nPosStart=-1, nPosEnd=-1; ExtensionAPI::Pane pane;
	if (!PyArg_ParseTuple(pArgs, "iii", &nPane, &nPosStart, &nPosEnd)) return NULL;
	if (nPosStart<0 || nPosEnd<0) return NULL;
	if (!GetPaneFromInt(nPane, &pane)) { PyErr_SetString(PyExc_RuntimeError,"Invalid pane, must be 0 or 1."); return NULL;}
	char *value = _host->Range(pane, nPosStart, nPosEnd);
	if (value)
	{
		CPyObjWeak objRet = PyString_FromString(value); // weakref because we are giving ownership.
		delete[] value;
		return objRet;
	}
	else
	{
		Py_INCREF(Py_None);
		return Py_None;	
	}
}
PyObject* pyfun_pane_FindText(PyObject* self, PyObject* pArgs) //returns a tuple
{
	char* szText = NULL; /* we do NOT own this pointer, we cannot free it. */
	int nPane = -1, nFlags=0, nPosStart=0, nPosEnd=-1; ExtensionAPI::Pane pane;
	if (!PyArg_ParseTuple(pArgs, "is|iii", &nPane, &szText, &nFlags, &nPosStart, &nPosEnd)) return NULL;
	if (!GetPaneFromInt(nPane, &pane)) { PyErr_SetString(PyExc_RuntimeError,"Invalid pane, must be 0 or 1."); return NULL;}
	if (nPosEnd==-1) nPosEnd= _host->Send(pane, SCI_GETLENGTH, 0, 0);
	if (nPosStart<0 || nPosEnd<0) return NULL;
	
	Sci_TextToFind ft = {{0, 0}, 0, {0, 0}};
	ft.lpstrText =szText; 
	ft.chrg.cpMin = nPosStart;
	ft.chrg.cpMax = nPosEnd;
	int result = _host->Send(pane, SCI_FINDTEXT, static_cast<uptr_t>(nFlags), reinterpret_cast<sptr_t>(&ft));
	
	if (result >= 0)
	{
		// build a tuple. // weakref because we are giving ownership.
		CPyObjWeak objRet = Py_BuildValue("(i,i)", ft.chrgText.cpMin, ft.chrgText.cpMax);
		return objRet;
	}
	else
	{
		Py_INCREF(Py_None);
		return Py_None;
	}
}

// send things to scintilla.
// now there is a 1-1 conversion between python and scintilla

// input is: pyfun_pane_SendScintilla( 1, "SCICUT", (46, 75))


bool pullPythonArgument(IFaceType type, CPyObjWeak pyObjNext, intptr_t* param)
{
	if (!pyObjNext) {  PyErr_SetString(PyExc_RuntimeError,"Unexpected: could not get next item."); return false; }

	switch(type) {
		case iface_void:
			break;
		case iface_int:
		case iface_length:
		case iface_position:
		case iface_colour:
		case iface_keymod:  //keymods: was going to make this in c++, but AssignCmdKey / ClearCmdKey only ones using this... see py's makeKeyMod
			if (!PyInt_Check((PyObject*) pyObjNext)) { PyErr_SetString(PyExc_RuntimeError,"Int expected."); return false; }
			*param = (intptr_t) PyInt_AsLong(pyObjNext);
			break;
		case iface_bool:
			if (!PyBool_Check(pyObjNext)) { PyErr_SetString(PyExc_RuntimeError,"Bool expected."); return false; }
			*param = (pyObjNext == Py_True) ? 1 : 0;
			break;
		case iface_string:
		case iface_cells:
			if (!PyString_Check(pyObjNext)) { PyErr_SetString(PyExc_RuntimeError,"String expected."); return false; }
			*param = (intptr_t) PyString_AsString(pyObjNext);
			break;
		case iface_textrange:
			PyErr_SetString(PyExc_RuntimeError,"raw textrange unsupported, but you can use CScite.Editor.Textrange(s,e)");  return false;
			break;
		default: {  PyErr_SetString(PyExc_RuntimeError,"Unexpected: receiving unknown scintilla type."); return false; }
	}
	return true;
}
bool pushPythonArgument(IFaceType type, intptr_t param, PyObject** pyValueOut /* caller must incref this! */)
{
	switch(type) {
		case iface_void:
			*pyValueOut = Py_None;
			break;
		case iface_int:
		case iface_length:
		case iface_position:
		case iface_colour:
			*pyValueOut = PyInt_FromLong((long) param);
			break;
		case iface_bool:
			*pyValueOut = param ? Py_True : Py_False;
			break;
		default: {  PyErr_SetString(PyExc_RuntimeError,"Unexpected: returning unknown scintilla type."); return false; }
	}
	return true;
}

PyObject* pyfun_pane_SendScintillaFn(PyObject* self, PyObject* pArgs)
{
	char* szCmd = NULL; /* we do NOT own this pointer, we cannot free it. */
	int nPane=-1; ExtensionAPI::Pane pane; 
	PyObject* pSciArgs; //borrowed reference, so ok.
	if (!PyArg_ParseTuple(pArgs, "isO", &nPane, &szCmd, &pSciArgs)) return NULL;
	if (!GetPaneFromInt(nPane, &pane)) { PyErr_SetString(PyExc_RuntimeError,"Invalid pane, must be 0 or 1."); return NULL;}
	if (!PyTuple_Check(pSciArgs)) { PyErr_SetString(PyExc_RuntimeError,"Third arg must be a tuple."); return NULL;}
	
	int nFnIndex = IFaceTable::FindFunction(szCmd);
	if (nFnIndex == -1) { PyErr_SetString(PyExc_RuntimeError,"Could not find fn."); return NULL; }
	
	intptr_t wParam = 0; //args to be passed to Scite
	intptr_t lParam = 0; //args to be passed to Scite
	IFaceFunction func = IFaceTable::functions[nFnIndex];
	bool isStringResult = func.returnType == iface_int && func.paramType[1] == iface_stringresult;
	size_t nArgCount = PyTuple_GET_SIZE((PyObject*) pSciArgs);
	size_t nArgsExpected = isStringResult ? ((func.paramType[0] != iface_void) ? 1 : 0) :
		((func.paramType[1] != iface_void) ? 2 : ((func.paramType[0] != iface_void) ? 1 : 0));
	if (nArgCount != nArgsExpected) { PyErr_SetString(PyExc_RuntimeError,"Wrong # of args"); return false; }
	
	if (func.paramType[0] != iface_void)
	{
		bool fResult = pullPythonArgument( func.paramType[0], PyTuple_GetItem(pSciArgs, 0), &wParam);
		if (!fResult)  {	return NULL; }
	}
	if (func.paramType[1] != iface_void && !isStringResult)
	{
		bool fResult = pullPythonArgument( func.paramType[1], PyTuple_GetItem(pSciArgs, 1), &lParam);
		if (!fResult)  {	return NULL; }
	}
	else if (isStringResult) { // allocate space for the result
		size_t spaceNeeded = _host->Send(pane, func.value, wParam, NULL);
		if (strcmp(szCmd, "GetCurLine")==0) // the first param of getCurLine is useless
			wParam = spaceNeeded;
		//traceOut("", "allocating", spaceNeeded);
		lParam = (intptr_t) new char[spaceNeeded+1];
		for (unsigned i=0; i<spaceNeeded+1; i++) ((char*)lParam)[i] = 0;
	}
	
	intptr_t result = _host->Send(pane, func.value, wParam, lParam);
	PyObject* pyObjReturn = NULL;
	if (!isStringResult)
	{
		bool fRet = pushPythonArgument(func.returnType, result, &pyObjReturn); // if returns void, it simply returns NONE, so we're good
		if (!fRet)  { return NULL; }
	}
	else
	{
		if (!lParam)  { /* Unexpected: returning null instead of string */ Py_INCREF(Py_None); return Py_None; }
		//pyObjReturn = PyString_FromString((char *) lParam); doesn't work
		//traceOut("got", "", (size_t) result);
		if (result == 0)
			pyObjReturn = PyString_FromString("");
		else
			pyObjReturn = PyString_FromStringAndSize((char *) lParam, (size_t) result-1);
		delete[] (char*) lParam;
	}
	Py_INCREF(pyObjReturn); //important to incref
	return pyObjReturn;
}

PyObject* pyfun_pane_SendScintillaGet(PyObject* self, PyObject* pArgs)
{
	char* szProp = NULL; /* we do NOT own this pointer, we cannot free it. */
	int nPane=-1; ExtensionAPI::Pane pane; PyObject* pyObjParam=NULL;
	if (!PyArg_ParseTuple(pArgs, "is|O", &nPane, &szProp, &pyObjParam)) return NULL;
	if (!GetPaneFromInt(nPane, &pane)) { PyErr_SetString(PyExc_RuntimeError,"Invalid pane, must be 0 or 1."); return NULL;}
	
	int nFnIndex = IFaceTable::FindProperty(szProp);
	if (nFnIndex == -1) { PyErr_SetString(PyExc_RuntimeError,"Could not find prop."); return NULL; }
	IFaceProperty prop =  IFaceTable::properties[nFnIndex];
	if (prop.getter == 0) { PyErr_SetString(PyExc_RuntimeError,"prop can't be get."); return NULL; }
	intptr_t wParam = 0; //args to be passed to Scite
	intptr_t lParam = 0; //args to be passed to Scite
	
	if (prop.paramType != iface_void)
	{
		if (pyObjParam==NULL || pyObjParam == Py_None) { PyErr_SetString(PyExc_RuntimeError,"prop needs param."); return NULL; }
		bool fResult = pullPythonArgument( prop.paramType, pyObjParam, &wParam);
		if (!fResult)  {	return NULL; }
	}	
	if (prop.valueType == iface_string) {  // allocate space for the result
		size_t spaceNeeded = _host->Send(pane, prop.getter, wParam, NULL);
		lParam = (intptr_t) new char[spaceNeeded ]; //note: no null term !!!
		for (unsigned int i=0; i<spaceNeeded; i++) ((char*)lParam)[i] = 0;
	}
	intptr_t result = _host->Send(pane, prop.getter, wParam, lParam);
	
	PyObject* pyObjReturn = NULL;
	if (prop.valueType != iface_string)
	{
		bool fRet = pushPythonArgument(prop.valueType, result, &pyObjReturn); // if returns void, it simply returns NONE, so we're good
		if (!fRet)  { return NULL; }
	}
	else
	{
		if (!lParam)  { /* Unexpected: returning null instead of string */ Py_INCREF(Py_None); return Py_None; }
		if (result == 0)
			pyObjReturn = PyString_FromString("");
		else
			pyObjReturn = PyString_FromStringAndSize((char *) lParam, (size_t) result-1);
		delete[] (char*) lParam;
	}
	Py_INCREF(pyObjReturn); //important to incref
	return pyObjReturn;
}

PyObject* pyfun_pane_SendScintillaSet(PyObject* self, PyObject* pArgs)
{
	char* szProp = NULL; /* we do NOT own this pointer, we cannot free it. */
	int nPane=-1; ExtensionAPI::Pane pane; PyObject* pyObjValue=NULL; PyObject* pyObjParam=NULL;
	if (!PyArg_ParseTuple(pArgs, "isO|O", &nPane, &szProp, &pyObjValue, &pyObjParam)) return NULL;
	if (!GetPaneFromInt(nPane, &pane)) { PyErr_SetString(PyExc_RuntimeError,"Invalid pane, must be 0 or 1."); return NULL;}
	
	int nFnIndex = IFaceTable::FindProperty(szProp);
	if (nFnIndex == -1) { PyErr_SetString(PyExc_RuntimeError,"Could not find prop."); return NULL; }
	IFaceProperty prop =  IFaceTable::properties[nFnIndex];
	if (prop.setter == 0) { PyErr_SetString(PyExc_RuntimeError,"prop can't be set."); return NULL; }
	intptr_t wParam = 0; //args to be passed to Scite
	intptr_t lParam = 0; //args to be passed to Scite
	
	bool fResult = pullPythonArgument( prop.valueType, pyObjValue, &wParam);
	if (!fResult)  {	return NULL; }
	if (prop.paramType != iface_void)
	{
		if (pyObjParam==NULL || pyObjParam == Py_None) { PyErr_SetString(PyExc_RuntimeError,"prop needs param."); return NULL; }
		bool fResult = pullPythonArgument( prop.paramType, pyObjParam, &lParam);
		if (!fResult)  {	return NULL; }
	}
	intptr_t result = _host->Send(pane, prop.setter, wParam, lParam);
	result;
	Py_INCREF(Py_None);
	return Py_None;
}

PyObject* pyfun_app_GetConstant(PyObject* self, PyObject* pArgs)
{
	char* szProp = NULL; /* we do NOT own this pointer, we cannot free it. */
	if (!PyArg_ParseTuple(pArgs, "s",  &szProp)) return NULL;
	
	int nFnIndex = IFaceTable::FindConstant(szProp);
	if (nFnIndex == -1) { PyErr_SetString(PyExc_RuntimeError,"Could not find constant."); return NULL; }
	IFaceConstant faceConstant =  IFaceTable::constants[nFnIndex];
	PyObject* pyValueOut = PyInt_FromLong(faceConstant.value);
	Py_INCREF(pyValueOut);
	return pyValueOut;
}
PyObject* pyfun_app_SciteCommand(PyObject* self, PyObject* pArgs)
{
	char* szProp = NULL; /* we do NOT own this pointer, we cannot free it. */
	if (!PyArg_ParseTuple(pArgs, "s",  &szProp)) return NULL;
	
	int nFnIndex = FindFriendlyNamedIDMConstant(szProp);
	if (nFnIndex == -1) { PyErr_SetString(PyExc_RuntimeError,"Could not find command."); return NULL; }
	IFaceConstant faceConstant =  PythonExtension::friendlyconstants[nFnIndex];
	_host->DoMenuCommand(faceConstant.value);
	Py_INCREF(Py_None);
	return Py_None;
}
PyObject* pyfun_app_UpdateStatusBar(PyObject* self, PyObject* pArgs)
{
	PyObject * pyObjBoolUpdate = NULL;
	if (!PyArg_ParseTuple(pArgs, "|O",  &pyObjBoolUpdate)) return NULL;
	bool bUpdateSlowData = false;
	if (pyObjBoolUpdate == Py_True) bUpdateSlowData = true;
	_host->UpdateStatusBar(bUpdateSlowData);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef methods_LogStdout[] = {
	{"LogStdout", pyfun_LogStdout, METH_VARARGS, "Logs stdout"},
	{"app_Trace", pyfun_LogStdout, METH_VARARGS, "(for compat with scite-lua scripts)"},
	{"app_MsgBox", pyfun_MessageBox, METH_VARARGS, ""},
	{"app_OpenFile", pyfun_SciteOpenFile, METH_VARARGS, ""},
	{"app_GetProperty", pyfun_GetProperty, METH_VARARGS, "Get SciTE Property"},
	{"app_SetProperty", pyfun_SetProperty, METH_VARARGS, "Set SciTE Property"},
	{"app_UnsetProperty", pyfun_UnsetProperty, METH_VARARGS, "Unset SciTE Property"},
	{"app_UpdateStatusBar", pyfun_app_UpdateStatusBar, METH_VARARGS, ""},
	{"app_SciteCommand", pyfun_app_SciteCommand, METH_VARARGS, ""},
	{"app_GetConstant", pyfun_app_GetConstant, METH_VARARGS, ""},
	
	{"pane_Append", pyfun_pane_Append, METH_VARARGS, ""},
	{"pane_Insert", pyfun_pane_Insert, METH_VARARGS, ""},
	{"pane_Remove", pyfun_pane_Remove, METH_VARARGS, ""},
	{"pane_Textrange", pyfun_pane_TextRange, METH_VARARGS, ""},
	{"pane_FindText", pyfun_pane_FindText, METH_VARARGS, ""},
	{"pane_ScintillaFn", pyfun_pane_SendScintillaFn, METH_VARARGS, ""},
	{"pane_ScintillaGet", pyfun_pane_SendScintillaGet, METH_VARARGS, ""},
	{"pane_ScintillaSet", pyfun_pane_SendScintillaSet, METH_VARARGS, ""},
	// the match object, if needed, would be easier to write in Python.
	
	{NULL, NULL, 0, NULL}
};



void PythonExtension::SetupPythonNamespace()
{
	CPyObjWeak pInitMod = Py_InitModule("CScite", methods_LogStdout);
	// PyRun_SimpleString is evil. it swallows the error message, might leave python in a weird state.
	//~ CPyObjStrong pResult= PyRun_String(
	int ret = PyRun_SimpleString(
	"import CScite\n"
	"import sys\n"
	"class StdoutCatcher:\n"
	"    def write(self, str):\n"
	"        CScite.LogStdout(str)\n"
	"sys.stdout = StdoutCatcher()\n"
	"sys.stderr = StdoutCatcher()\n"
	);
	if (ret!=0)
	{
		displayError("Unexpected: error capturing stdout from Python. make sure python26.zip is present?");
		PyErr_Print(); //of course, if printing isn't set up, will not help, but at least will clear python's error bit
		return;
	}
	// now run setup script.
	//~ ret = PyRun_AnyFile(fp, "pythonsetup.py");
	CPyObjStrong pName = PyString_FromString("pythonsetup");
	if (!pName) { displayError("Unexpected error: could not form string pythonsetup."); }
	CPyObjStrong pModule = PyImport_Import(pName);
	if (!pModule) {
		displayError("Error importing pythonsetup module.");
		PyErr_Print();
	}
	//use Python's import. don't have to worry about current directory problems or file handles
}

int FindFriendlyNamedIDMConstant(const char *name) {
	int lo = 0;
	int hi = PythonExtension::lengthfriendlyconstants - 1;
	do {
		int idx = (lo+hi)/2;
		int cmp = strcmp(name, PythonExtension::friendlyconstants[idx].name);

		if (cmp > 0) {
			lo = idx + 1;
		} else if (cmp < 0) {
			hi = idx - 1;
		} else {
			return idx;
		}
	} while (lo <= hi);
	return -1;
}

#include "Scite.h"
static IFaceConstant rgFriendlyNamedIDMConstants[] = {
{"Abbrev",IDM_ABBREV},
{"About",IDM_ABOUT},
{"Activate",IDM_ACTIVATE},
{"BlockComment",IDM_BLOCK_COMMENT},
{"BookmarkClearall",IDM_BOOKMARK_CLEARALL},
{"BookmarkNext",IDM_BOOKMARK_NEXT},
{"BookmarkNextSelect",IDM_BOOKMARK_NEXT_SELECT},
{"BookmarkPrev",IDM_BOOKMARK_PREV},
{"BookmarkPrevSelect",IDM_BOOKMARK_PREV_SELECT},
{"BookmarkToggle",IDM_BOOKMARK_TOGGLE},
{"BoxComment",IDM_BOX_COMMENT},
{"Buffer",IDM_BUFFER},
{"Buffersep",IDM_BUFFERSEP},
{"Build",IDM_BUILD},
{"Clear",IDM_CLEAR},
{"ClearOutput",IDM_CLEAROUTPUT},
{"Close",IDM_CLOSE},
{"Closeall",IDM_CLOSEALL},
{"Compile",IDM_COMPILE},
{"Complete",IDM_COMPLETE},
{"CompleteWord",IDM_COMPLETEWORD},
{"Copy",IDM_COPY},
{"Copyasrtf",IDM_COPYASRTF},
{"Copypath",IDM_COPYPATH},
{"Cut",IDM_CUT},
{"DirectionDown",IDM_DIRECTIONDOWN},
{"DirectionUp",IDM_DIRECTIONUP},
{"Duplicate",IDM_DUPLICATE},
{"Encoding_default",IDM_ENCODING_DEFAULT},
{"Encoding_ucookie",IDM_ENCODING_UCOOKIE},
{"Encoding_ucs2be",IDM_ENCODING_UCS2BE},
{"Encoding_ucs2le",IDM_ENCODING_UCS2LE},
{"Encoding_utf8",IDM_ENCODING_UTF8},
{"EnterSelection",IDM_ENTERSELECTION},
{"Eol_convert",IDM_EOL_CONVERT},
{"Eol_cr",IDM_EOL_CR},
{"Eol_crlf",IDM_EOL_CRLF},
{"Eol_lf",IDM_EOL_LF},
{"Expand",IDM_EXPAND},
{"ExpandEnsurechildrenvisible",IDM_EXPAND_ENSURECHILDRENVISIBLE},
{"Filer",IDM_FILER},
{"Find",IDM_FIND},
{"FindInFiles",IDM_FINDINFILES},
{"FindNext",IDM_FINDNEXT},
{"FindNextBack",IDM_FINDNEXTBACK},
{"FindNextBackSel",IDM_FINDNEXTBACKSEL},
{"FindNextSel",IDM_FINDNEXTSEL},
{"FinishedExecute",IDM_FINISHEDEXECUTE},
{"FoldMargin",IDM_FOLDMARGIN},
{"Fullscreen",IDM_FULLSCREEN},
{"Go",IDM_GO},
{"Goto",IDM_GOTO},
{"Help",IDM_HELP},
{"Help_scite",IDM_HELP_SCITE},
{"Import",IDM_IMPORT},
{"Incsearch",IDM_INCSEARCH},
{"InsAbbrev",IDM_INS_ABBREV},
{"Join",IDM_JOIN},
{"Language",IDM_LANGUAGE},
{"LineNumberMargin",IDM_LINENUMBERMARGIN},
{"Loadsession",IDM_LOADSESSION},
{"Lwrcase",IDM_LWRCASE},
{"Macrolist",IDM_MACROLIST},
{"Macroplay",IDM_MACROPLAY},
{"Macrorecord",IDM_MACRORECORD},
{"Macrostoprecord",IDM_MACROSTOPRECORD},
{"Macro_sep",IDM_MACRO_SEP},
{"Matchbrace",IDM_MATCHBRACE},
{"Matchcase",IDM_MATCHCASE},
{"Monofont",IDM_MONOFONT},
{"Movetableft",IDM_MOVETABLEFT},
{"Movetabright",IDM_MOVETABRIGHT},
{"Mrufile",IDM_MRUFILE},
{"Mru_sep",IDM_MRU_SEP},
{"New",IDM_NEW},
{"Nextfile",IDM_NEXTFILE},
{"Nextfilestack",IDM_NEXTFILESTACK},
{"Nextmatchppc",IDM_NEXTMATCHPPC},
{"Nextmsg",IDM_NEXTMSG},
{"Ontop",IDM_ONTOP},
{"Open",IDM_OPEN},
{"Openabbrevproperties",IDM_OPENABBREVPROPERTIES},
{"Opendirectoryproperties",IDM_OPENDIRECTORYPROPERTIES},
{"Openfileshere",IDM_OPENFILESHERE},
{"Openglobalproperties",IDM_OPENGLOBALPROPERTIES},
{"Openlocalproperties",IDM_OPENLOCALPROPERTIES},
{"Openluaexternalfile",IDM_OPENLUAEXTERNALFILE},
{"Openselected",IDM_OPENSELECTED},
{"Openuserproperties",IDM_OPENUSERPROPERTIES},
{"Paste",IDM_PASTE},
{"Pasteanddown",IDM_PASTEANDDOWN},
{"Prevfile",IDM_PREVFILE},
{"Prevfilestack",IDM_PREVFILESTACK},
{"Prevmatchppc",IDM_PREVMATCHPPC},
{"Prevmsg",IDM_PREVMSG},
{"Print",IDM_PRINT},
{"PrintSetup",IDM_PRINTSETUP},
{"Quit",IDM_QUIT},
{"Readonly",IDM_READONLY},
{"Redo",IDM_REDO},
{"Regexp",IDM_REGEXP},
{"Replace",IDM_REPLACE},
{"Revert",IDM_REVERT},
{"Runwin",IDM_RUNWIN},
{"Save",IDM_SAVE},
{"Saveacopy",IDM_SAVEACOPY},
{"Saveall",IDM_SAVEALL},
{"Saveas",IDM_SAVEAS},
{"Saveashtml",IDM_SAVEASHTML},
{"Saveaspdf",IDM_SAVEASPDF},
{"Saveasrtf",IDM_SAVEASRTF},
{"Saveastex",IDM_SAVEASTEX},
{"Saveasxml",IDM_SAVEASXML},
{"SaveSession",IDM_SAVESESSION},
{"SelectAll",IDM_SELECTALL},
{"SelectToBrace",IDM_SELECTTOBRACE},
{"SelectToNextmatchppc",IDM_SELECTTONEXTMATCHPPC},
{"SelectToPrevmatchppc",IDM_SELECTTOPREVMATCHPPC},
{"SelMargin",IDM_SELMARGIN},
{"ShowCalltip",IDM_SHOWCALLTIP},
{"Split",IDM_SPLIT},
{"SplitVertical",IDM_SPLITVERTICAL},
{"SrcWin",IDM_SRCWIN},
{"StatusWin",IDM_STATUSWIN},
{"StopExecute",IDM_STOPEXECUTE},
{"StreamComment",IDM_STREAM_COMMENT},
{"Switchpane",IDM_SWITCHPANE},
{"Tabsize",IDM_TABSIZE},
{"Tabwin",IDM_TABWIN},
{"ToggleOutput",IDM_TOGGLEOUTPUT},
{"ToggleParameters",IDM_TOGGLEPARAMETERS},
{"ToggleFoldAll",IDM_TOGGLE_FOLDALL},
{"ToggleFoldRecursive",IDM_TOGGLE_FOLDRECURSIVE},
{"Tools",IDM_TOOLS},
{"Toolwin",IDM_TOOLWIN},
{"Undo",IDM_UNDO},
{"Unslash",IDM_UNSLASH},
{"Uprcase",IDM_UPRCASE},
{"ViewEol",IDM_VIEWEOL},
{"ViewGuides",IDM_VIEWGUIDES},
{"ViewSpace",IDM_VIEWSPACE},
{"ViewStatusbar",IDM_VIEWSTATUSBAR},
{"ViewTabbar",IDM_VIEWTABBAR},
{"ViewToolbar",IDM_VIEWTOOLBAR},
{"Wholeword",IDM_WHOLEWORD},
{"Wrap",IDM_WRAP},
{"Wraparound",IDM_WRAPAROUND},
{"Wrapoutput",IDM_WRAPOUTPUT},
};
const IFaceConstant * const PythonExtension::friendlyconstants = rgFriendlyNamedIDMConstants;
const size_t PythonExtension::lengthfriendlyconstants = _countof(rgFriendlyNamedIDMConstants);

