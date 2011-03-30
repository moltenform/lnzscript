
#include "..\python\include\python.h"

#include "IFaceTable.h"

#include <string>
#include <vector>
#include <map>

class CPyObjStrong
{
private:
	PyObject* m_pyo;
public:
	CPyObjStrong() { m_pyo = NULL; }
	CPyObjStrong(PyObject* pyo) { m_pyo = pyo; }
	void Attach(PyObject* pyo) { m_pyo = pyo; }
	~CPyObjStrong() { if (m_pyo) Py_DECREF(m_pyo); }
	operator PyObject*() { return m_pyo; }
	
	//~ CPyObjStrong & operator=(const MyClass &rhs) {  
		//~ if (this==&rhs) return *this; //~ rhis.
	//~ }
};
class CPyObjWeak //no real reason for this besides consistent code
{
private:
	PyObject* m_pyo;
public:
	CPyObjWeak(PyObject* pyo) { m_pyo = pyo; }
	~CPyObjWeak() { /* do not need to decref */ }
	operator PyObject*() { return m_pyo; }
};

int FindFriendlyNamedIDMConstant(const char *name);


class PythonExtension : public Extension
{

private:
	bool displayError(const char *wzError);
	bool displayError(const char *wzError, const char *wzError2);
	bool _runCallback(const char* szNameOfFunction, int nArgs, const char* szArg1);
	bool _runCallbackArgs(const char* szNameOfFunction, PyObject* pArgsBorrowed);
	void InitializePython();
	void SetupPythonNamespace();

public:
	void displayText(const char *szText);
	bool DoOpenFile(const char* sFilename);

private:
	PythonExtension(); // Singleton
	PythonExtension(const PythonExtension &); // Disable copy ctor
	void operator=(const PythonExtension &); // Disable operator=

	
public:
	static const IFaceConstant * const friendlyconstants;
	static const size_t lengthfriendlyconstants;
	static PythonExtension &Instance();

	virtual ~PythonExtension();

	virtual bool Initialise(ExtensionAPI *host);
	virtual bool Finalise();
	virtual bool Clear();
	virtual bool Load(const char *fileName);

	virtual bool InitBuffer(int index);
	virtual bool ActivateBuffer(int index);
	virtual bool RemoveBuffer(int index);

	virtual bool OnExecute(const char *s); // eg. code from menu commands

	// file events
	virtual bool OnOpen(const char *fileName);
	virtual bool OnClose(const char *filename);
	virtual bool OnSwitchFile(const char *fileName);
	virtual bool OnBeforeSave(const char *fileName);
	virtual bool OnSave(const char *fileName);
	virtual bool OnSavePointReached();
	virtual bool OnSavePointLeft();
	// input events
	virtual bool OnChar(char ch);
	virtual bool OnKey(int keycode, int modifiers);
	virtual bool OnDoubleClick();
	virtual bool OnMarginClick();
	virtual bool OnDwellStart(int pos, const char *word);
	// misc events
	virtual bool OnUserListSelection(int type, const char *selection);
	
};
