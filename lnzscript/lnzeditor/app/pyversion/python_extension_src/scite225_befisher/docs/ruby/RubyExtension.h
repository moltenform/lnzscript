
#include <ruby.h>
#undef Sleep
#undef write
#undef read
#undef send
#undef recv

#include "IFaceTable.h"

#include <string>
#include <vector>
#include <map>

class RubyExtension : public Extension
{
public:
	static const char *PROP_STARTUP_SCRIPT;
	static const char *PROP_RELOAD;
	static const char *PROP_LOAD_PATH;
private:
	struct Arguments {
		VALUE recv;
		ID id;
		int argc;
		VALUE *argv;
		Arguments(VALUE recv, ID id, int argc, VALUE *argv)
			:recv(recv), id(id), argc(argc), argv(argv) {}
	};
	static VALUE callFunctionWrap(VALUE args);

	RubyExtension(); // Singleton
	RubyExtension(const RubyExtension &);
	void operator=(const RubyExtension &);

	ExtensionAPI *_host;
public:
	static RubyExtension &Instance();

	virtual ~RubyExtension();

	virtual bool Initialise(ExtensionAPI *host);
	virtual bool Finalise();
	virtual bool Clear();
	virtual bool Load(const char *fileName);

	virtual bool InitBuffer(int index);
	virtual bool ActivateBuffer(int index);
	virtual bool RemoveBuffer(int index);

	virtual bool OnExecute(const char *s); // eg. code from menu commands
	// virtual bool OnStyle(unsigned int startPos, int lengthDoc, int initStyle, Accessor *styler); // ???

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
	// virtual bool OnUpdateUI();
	virtual bool OnUserListSelection(int type, const char *selection);
	
	// call safely a ruby function
	static VALUE callFunction(VALUE recv, ID id, int argc, VALUE *argv);
private:
	bool running;
	char *startupScript;
	VALUE stack;
	
	void startExtension();
	void initInterface();
	void shutdownExtension();
	
	bool checkStartupScript();
	void runStartupScript();
	void reloadStartupScript();
	
	void runString(const char *code);
	void runFile(const char *fileName);
	
	void initClasses();
	typedef VALUE (*HOOK)(...); // for exporting functions to Ruby
	VALUE _rModuleSciTE; // main module
	
	class Main // functions inside main module (SciTE)
	{
	private:
		static ExtensionAPI *_host;
	public:
		static void create(ExtensionAPI *host, VALUE parent);
		
		static VALUE menuCommand(VALUE self, VALUE id);
		static VALUE perform(VALUE self, VALUE actions);
		static VALUE shutDown(VALUE self);
		static VALUE updateStatusBar(VALUE self, VALUE slowData);
		static VALUE constantName(VALUE self, VALUE number);
	};
	
	class IO // replaces $stdout, $defout, $stderr to redirect output to SciTE
	{
	private:
		static ExtensionAPI *_host;
		static VALUE _def;
	public:
		static void create(ExtensionAPI *host, VALUE parent);
		static VALUE def() { return _def; }
		static VALUE instance() { return rb_class_new_instance(0, 0, _def); }
		
		static VALUE write(VALUE self, VALUE str);
	};
	
	class Events // singleton, receives all the OnSomething of the interface
	{
	public:
		typedef std::vector<VALUE> Procs;
		typedef std::map<std::string, Procs> Callbacks;
	private:
		static ExtensionAPI *_host;
		static VALUE _def;
		static VALUE _instance;
		static Callbacks _callbacks;
	public:
		static void create(ExtensionAPI *host, VALUE parent);
		static void reset();
		static VALUE def() { return _def; }
		static VALUE instance() { return _instance; }
		
		static VALUE onEvent(VALUE self);
		static bool triggerEvent(const std::string& name, int argc, VALUE *args);
	};
	
	class Properties // singleton, get/set properties
	{
	private:
		static ExtensionAPI *_host;
		static VALUE _def;
		static VALUE _instance;
	public:
		static void create(ExtensionAPI *host, VALUE parent);
		static VALUE def() { return _def; }
		static VALUE instance() { return _instance; }
		
		static VALUE get(VALUE self, VALUE key);
		static VALUE set(VALUE self, VALUE key, VALUE value);
	};
	
	class Pane // editor pane, output pane
	{
	private:
		typedef struct IFaceFunction IFaceFunction;
		typedef struct IFaceProperty IFaceProperty;
		typedef std::map<std::string, IFaceFunction> IFunctions;
		typedef std::map<std::string, IFaceProperty> IProperties;
		
		static ExtensionAPI *_host;
		static VALUE _def;
		
		static IFunctions _functions;
		static IProperties _properties;
	public:
		static void create(ExtensionAPI *host, VALUE parent);
		static VALUE def() { return _def; }
		static VALUE instance(ExtensionAPI::Pane pane);
		static ExtensionAPI::Pane pane(VALUE self);
		static sptr_t send(VALUE self, unsigned int msg, uptr_t wParam = 0, sptr_t lParam = 0);
		
		// utils
		static uptr_t createType(VALUE self, IFaceType type, VALUE arg);
		static void destroyType(IFaceType type, uptr_t obj);
		static VALUE convertResult(IFaceType type, sptr_t result);
		
		static VALUE initialize(VALUE self, VALUE pane); // enum Pane { paneEditor=1, paneOutput=2, paneFindOutput=3 };
		static VALUE function(int argc, VALUE *argv, VALUE self);
		static VALUE property(int argc, VALUE *argv, VALUE self);
		static VALUE range(VALUE self, VALUE range);
		
		class Property // Pane property with parameter, exported as [], []= operators
		{
		private:
			static ExtensionAPI *_host;
			static VALUE _def;
		public:
			static void create(ExtensionAPI *host, VALUE parent);
			static VALUE def() { return _def; }
			static VALUE instance(VALUE pane, const char *name);
			
			static VALUE initialize(VALUE self, VALUE pane, VALUE name);
			static VALUE get(VALUE self, VALUE key);
			static VALUE set(VALUE self, VALUE key, VALUE value);
		};
	};
};
