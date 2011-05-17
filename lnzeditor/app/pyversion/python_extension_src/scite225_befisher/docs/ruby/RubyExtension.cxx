
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Scintilla.h"
#include "Accessor.h"
#include "Extender.h"

#include "SString.h"
#include "SciTEKeys.h"
#include "IFaceTable.h"

#include "RubyExtension.h"

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

template<typename T> inline std::string stringFrom(const T& x)
{
	std::ostringstream out;
	out << x;
	return out.str();
}

template<typename T> inline T stringTo(const std::string& value)
{
	T result;
	if(!value.empty()) {
		std::stringstream ss(value);
		ss >> result;
	}
	return result;
}

class RubyException : public std::exception
{
public:
	typedef std::vector<std::string> Backtrace;
private:
	std::string _description;
	Backtrace _backtrace;
	std::string _what;
public:
	RubyException()
	{
		VALUE exception = rb_gv_get("$!");
		std::string type = RSTRING(rb_class_path(CLASS_OF(exception)))->ptr;
		
		std::stringstream description;
		if(type != "SyntaxError") {
			description << ruby_sourcefile << ":" << ruby_sourceline << ":";
			ID lastFunc = rb_frame_last_func();
			if(lastFunc)
				description << "in `" << rb_id2name(lastFunc) << "'";
			description << " ";
		}
		description << RSTRING(rb_obj_as_string(exception))->ptr;
		description << " (" << type << ")";
		
		_description = description.str();
		
		RArray *backtrace = RARRAY(rb_funcall(exception, rb_intern("backtrace"), 0));
		for(int i = 0; i < backtrace->len; ++i)
			_backtrace.push_back(RSTRING(backtrace->ptr[i])->ptr);
		
		std::stringstream what;
		what << _description << std::endl;
		for(Backtrace::const_iterator it = _backtrace.begin(); it != _backtrace.end(); ++it)
			what << "\tfrom " << *it << std::endl;
		_what = what.str();
	}
	virtual ~RubyException() throw() {}
	virtual const char *what() const throw()
	{
		return _what.c_str();
	}
	virtual const Backtrace& backtrace() const throw()
	{
		return _backtrace;
	}
};

const char *RubyExtension::PROP_STARTUP_SCRIPT = "ext.ruby.startup.script";
const char *RubyExtension::PROP_RELOAD         = "ext.ruby.reload";
const char *RubyExtension::PROP_LOAD_PATH      = "ext.ruby.load.path";

RubyExtension::RubyExtension()
	:running(false), startupScript(0)
{
	
}

RubyExtension::~RubyExtension()
{
	
}

RubyExtension &RubyExtension::Instance() {
	static RubyExtension singleton;
	return singleton;
}

bool RubyExtension::Initialise(ExtensionAPI *host)
{
	_host = host;
	
	startExtension();
	
	return false;
}

bool RubyExtension::Finalise()
{
	_host = NULL;
	
	return false;
}

bool RubyExtension::Clear()
{
	Events::triggerEvent("onClear", 0, NULL);
	return false;
}

bool RubyExtension::Load(const char *fileName)
{
	static VALUE args[] = { 0 };
	args[0] = rb_str_new2(fileName);
	Events::triggerEvent("onExtension", 1, args);
	return false;
}

bool RubyExtension::InitBuffer(int index)
{
	// std::stringstream ss;
	// ss << "InitBuffer(" << index << ")\n";
	// _host->Trace(ss.str().c_str());
	
	reloadStartupScript();
	
	return false;
}

bool RubyExtension::ActivateBuffer(int index)
{
	// std::stringstream ss;
	// ss << "ActivateBuffer(" << index << ")\n";
	// _host->Trace(ss.str().c_str());
	
	reloadStartupScript();
	
	return false;
}

bool RubyExtension::RemoveBuffer(int index)
{
	// std::stringstream ss;
	// ss << "RemoveBuffer(" << index << ")\n";
	// _host->Trace(ss.str().c_str());
	
	// reloadStartupScript();
	
	return false;
}

bool RubyExtension::OnExecute(const char *s)
{
	std::string code(s);
	if(code.substr(0, 5) == "ruby:") {
		try {
			runString(code.substr(5).c_str());
		} catch(const RubyException& ex) {
			std::stringstream msg;
			msg << "> Ruby: error running string commands ";
			msg << ex.what() << std::endl;
			_host->Trace(msg.str().c_str());
		}
	}
	return false;
}

// file events
bool RubyExtension::OnOpen(const char *fileName)
{
	static VALUE args[] = { 0 };
	args[0] = rb_str_new2(fileName);
	return Events::triggerEvent("onOpen", 1, args);
}
bool RubyExtension::OnClose(const char *fileName)
{
	static VALUE args[] = { 0 };
	args[0] = rb_str_new2(fileName);
	return Events::triggerEvent("onClose", 1, args);
}
bool RubyExtension::OnSwitchFile(const char *fileName)
{
	static VALUE args[] = { 0 };
	args[0] = rb_str_new2(fileName);
	return Events::triggerEvent("onSwitchFile", 1, args);
}
bool RubyExtension::OnBeforeSave(const char *fileName)
{
	static VALUE args[] = { 0 };
	args[0] = rb_str_new2(fileName);
	return Events::triggerEvent("onBeforeSave", 1, args);
}
bool RubyExtension::OnSave(const char *fileName)
{
	static VALUE args[] = { 0 };
	args[0] = rb_str_new2(fileName);
	return Events::triggerEvent("onSave", 1, args);
}
bool RubyExtension::OnSavePointReached()
{
	Events::triggerEvent("onSavePointReached", 0, NULL);
	return false;
}
bool RubyExtension::OnSavePointLeft()
{
	Events::triggerEvent("onSavePointLeft", 0, NULL);
	return false;
}

// input events
bool RubyExtension::OnChar(char ch)
{
	static VALUE args[] = { 0 };
	args[0] = CHR2FIX(ch);
	return Events::triggerEvent("onChar", 1, args);
}
bool RubyExtension::OnKey(int keycode, int modifiers)
{
	static VALUE args[] = { 0, 0 };
	args[0] = INT2FIX(keycode);
	args[1] = INT2FIX(modifiers);
	return Events::triggerEvent("onKey", 2, args);
}
bool RubyExtension::OnDoubleClick()
{
	return Events::triggerEvent("onDoubleClick", 0, NULL);
}
bool RubyExtension::OnMarginClick()
{
	return Events::triggerEvent("onMarginClick", 0, NULL);
}
bool RubyExtension::OnDwellStart(int pos, const char *word)
{
	static VALUE args[] = { 0, 0 };
	if(pos == 0 && word[0] == 0)
		return Events::triggerEvent("onTipEnd", 0, NULL);
	else {
		args[0] = INT2FIX(pos);
		args[1] = rb_str_new2(word);
		return Events::triggerEvent("onTipStart", 2, args);
	}
}

// misc events
bool RubyExtension::OnUserListSelection(int type, const char *selection)
{
	static VALUE args[] = { 0, 0 };
	args[0] = INT2FIX(type);
	args[1] = rb_str_new2(selection);
	return Events::triggerEvent("onListSelection", 2, args);
}

void RubyExtension::startExtension()
{
	if(running)
		shutdownExtension();
	
	/* init Ruby */ {
		ruby_init();
		
		// paths are from the SciTE directory
		ruby_incpush(".");
		ruby_incpush("./ruby");
		ruby_incpush("./ruby/lib");
		
		initInterface();
	}
	
	reloadStartupScript();
	
	running = true;
}

void RubyExtension::initInterface()
{
	_rModuleSciTE = rb_define_module("SciTE");
	initClasses();
}

void RubyExtension::shutdownExtension()
{
	if(!running)
		return;
	
	delete[] startupScript;
	ruby_finalize();
	
	running = false;
}

bool RubyExtension::checkStartupScript()
{
	if(startupScript != 0)
		delete[] startupScript;
	
	startupScript = _host->Property(PROP_STARTUP_SCRIPT);
	if(startupScript != 0 && startupScript[0] == '\0') { // not found
		delete[] startupScript;
		startupScript = 0;
	}
	
	return startupScript != 0;
}

void RubyExtension::runStartupScript()
{
	if(startupScript != 0) {
		try {
			runFile(startupScript);
		} catch(const RubyException& ex) {
			std::stringstream msg;
			msg << "> Ruby: error loading startup script ";
			msg << ex.what() << std::endl;
			_host->Trace(msg.str().c_str());
		}
	}
}

void RubyExtension::reloadStartupScript()
{
	bool reset = false;
	
	/* get property */ {
		char *propReset = _host->Property(PROP_RELOAD);
		if(propReset != NULL) {
			reset = stringTo<int>(std::string(propReset).empty() ? "0" : propReset) != 0;
			delete[] propReset;
		}
	}
	
	if(!running || reset) {
		if(checkStartupScript())
			runStartupScript();
	}
}

void RubyExtension::runString(const char *code)
{
	ruby_script("(eval)");
	int error;
	rb_eval_string_protect(code, &error);
	if(error)
		throw RubyException();
}

void RubyExtension::runFile(const char *fileName)
{
	ruby_script(fileName);
	int error;
	rb_load_protect(rb_str_new2(fileName), Qfalse, &error);
	if(error)
		throw RubyException();
}


VALUE RubyExtension::callFunctionWrap(VALUE args)
{
	Arguments &arguments = *reinterpret_cast<Arguments*>(args);
	return rb_funcall2(arguments.recv, arguments.id, arguments.argc, arguments.argv);
}

VALUE RubyExtension::callFunction(VALUE recv, ID id, int argc, VALUE *argv)
{
	Arguments args(recv, id, argc, argv);
	int error = 0;
	VALUE result = rb_protect(callFunctionWrap, reinterpret_cast<VALUE>(&args), &error);
	if(error)
		throw RubyException();
	return result;
}

void RubyExtension::initClasses()
{
	
	
	/* Constants */ {
		IFaceConstant constant = { NULL, 0 };
		for(int i = 0; i < IFaceTable::constantCount; ++i) {
			constant = IFaceTable::constants[i];
			rb_define_const(_rModuleSciTE, constant.name, INT2FIX(constant.value));
		}
	}
	
	/* Main */ {
		Main::create(_host, _rModuleSciTE);
	}
	
	/* IO */ {
		IO::create(_host, _rModuleSciTE);
		VALUE instance = IO::instance();
		rb_gv_set("$stdout", instance);
		// rb_gv_set("$defout", instance); // obsolete
		rb_gv_set("$stderr", instance);
	}
	
	/* Events */ {
		Events::create(_host, _rModuleSciTE);
	}
	
	/* Properties */ {
		Properties::create(_host, _rModuleSciTE);
	}
	
	/* Pane */ {
		Pane::create(_host, _rModuleSciTE);
	}
}

// Exposed functions

/* Main */
ExtensionAPI *RubyExtension::Main::_host = NULL;
void RubyExtension::Main::create(ExtensionAPI *host, VALUE parent)
{
	_host = host;
	
	rb_define_module_function(parent, "menuCommand", reinterpret_cast<HOOK>(&menuCommand), 1);
	rb_define_module_function(parent, "perform", reinterpret_cast<HOOK>(&perform), 1);
	rb_define_module_function(parent, "shutDown", reinterpret_cast<HOOK>(&shutDown), 0);
	rb_define_module_function(parent, "updateStatusBar", reinterpret_cast<HOOK>(&updateStatusBar), 1);
	rb_define_module_function(parent, "constantName", reinterpret_cast<HOOK>(&constantName), 1);
}

VALUE RubyExtension::Main::menuCommand(VALUE self, VALUE id)
{
	int menuID = FIX2INT(id);
	_host->DoMenuCommand(menuID);
	return Qnil;
}

VALUE RubyExtension::Main::perform(VALUE self, VALUE actions)
{
	const char *a = STR2CSTR(actions);
	_host->Perform(a);
	return Qnil;
}

VALUE RubyExtension::Main::shutDown(VALUE self)
{
	_host->ShutDown();
	return Qnil;
}

VALUE RubyExtension::Main::updateStatusBar(VALUE self, VALUE slowData)
{
	if(slowData == Qtrue || slowData == Qfalse)
		_host->UpdateStatusBar(slowData == Qtrue);
	else
		rb_raise(rb_eNoMethodError, "SciTE::updateStatusBar expects a boolean argument");
	return Qnil;
}

VALUE RubyExtension::Main::constantName(VALUE self, VALUE number)
{
	char buffer[64];
	IFaceTable::GetConstantName(NUM2INT(number), buffer, 64);
	return rb_str_new2(buffer);
}

/* IO */
ExtensionAPI *RubyExtension::IO::_host = NULL;
VALUE RubyExtension::IO::_def = 0;

void RubyExtension::IO::create(ExtensionAPI *host, VALUE parent)
{
	_host = host;
	
	_def = rb_define_class_under(parent, "IO", rb_cObject);
	rb_define_method(_def, "write", reinterpret_cast<HOOK>(&write), 1);
}

VALUE RubyExtension::IO::write(VALUE self, VALUE str)
{
	if(TYPE(str) == T_STRING) {
		const char *s = STR2CSTR(str);
		_host->Trace(s);
	}
	return Qnil;
}

/* Events */
ExtensionAPI *RubyExtension::Events::_host = NULL;
VALUE RubyExtension::Events::_def = 0;
VALUE RubyExtension::Events::_instance = 0;
RubyExtension::Events::Callbacks RubyExtension::Events::_callbacks;

void RubyExtension::Events::create(ExtensionAPI *host, VALUE parent)
{
	_host = host;
	
	_def = rb_define_class_under(parent, "EventsSingleton", rb_cObject);
	
	_instance = rb_class_new_instance(0, 0, _def);
	rb_define_const(parent, "Events", _instance);
	
	// other events
	rb_define_singleton_method(_instance, "onClear", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onExtension", reinterpret_cast<HOOK>(&onEvent), 0);
	
	// file events
	rb_define_singleton_method(_instance, "onOpen", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onClose", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onSwitchFile", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onBeforeSave", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onSave", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onSavePointReached", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onSavePointLeft", reinterpret_cast<HOOK>(&onEvent), 0);
	
	// input events
	rb_define_singleton_method(_instance, "onChar", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onKey", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onDoubleClick", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onMarginClick", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onTipStart", reinterpret_cast<HOOK>(&onEvent), 0);
	rb_define_singleton_method(_instance, "onTipEnd", reinterpret_cast<HOOK>(&onEvent), 0);
	
	// misc events
	rb_define_singleton_method(_instance, "onListSelection", reinterpret_cast<HOOK>(&onEvent), 0);
}

void RubyExtension::Events::reset()
{
	_callbacks.clear();
}

VALUE RubyExtension::Events::onEvent(VALUE self)
{
	const char *name = rb_id2name(rb_frame_last_func());
	if(rb_block_given_p()) {
		VALUE block = rb_block_proc();
		_callbacks[std::string(name)].push_back(block);
	} else {
		std::stringstream msg;
		msg << "No block given for event handler '" << name << "'";
		rb_raise(rb_eScriptError, msg.str().c_str());
	}
	return Qnil;
}

bool RubyExtension::Events::triggerEvent(const std::string& name, int argc, VALUE *args)
{
	Procs procs = _callbacks[name];
	
	bool stopPropagation = false;
	for(Procs::const_iterator it = procs.begin(); it != procs.end(); ++it) {
		try {
			stopPropagation = stopPropagation ||
				(callFunction(*it, rb_intern("call"), argc, args) == Qfalse);
		} catch(const RubyException &ex) {
			std::stringstream msg;
			msg << "> Ruby: ";
			msg << ex.what() << std::endl;
			_host->Trace(msg.str().c_str());
		}
	}
	return stopPropagation;
}

/* Properties */
ExtensionAPI *RubyExtension::Properties::_host = NULL;
VALUE RubyExtension::Properties::_def = 0;
VALUE RubyExtension::Properties::_instance = 0;

void RubyExtension::Properties::create(ExtensionAPI *host, VALUE parent)
{
	_host = host;
	
	_def = rb_define_class_under(parent, "PropertiesSingleton", rb_cObject);
	
	_instance = rb_class_new_instance(0, 0, _def);
	rb_define_const(parent, "Properties", _instance);
	
	rb_define_singleton_method(_instance, "[]", reinterpret_cast<HOOK>(&get), 1);
	rb_define_singleton_method(_instance, "[]=", reinterpret_cast<HOOK>(&set), 2);
}

VALUE RubyExtension::Properties::get(VALUE self, VALUE key)
{
	char *property = _host->Property(STR2CSTR(key));
	if(property != NULL)
		return rb_str_new2(property);
	else
		return Qnil;
}

VALUE RubyExtension::Properties::set(VALUE self, VALUE key, VALUE value)
{
	Check_Type(key, T_STRING);
	
	if(NIL_P(value) != 0) {
		_host->UnsetProperty(STR2CSTR(key));
	} else {
		if(FIXNUM_P(value) != 0) {
			std::string ivalue = stringFrom(FIX2INT(value));
			_host->SetProperty(STR2CSTR(key), ivalue.c_str());
		} else {
			Check_Type(value, T_STRING);
			_host->SetProperty(STR2CSTR(key), STR2CSTR(value));
		}
	}
	
	return Qnil;
}

/* Pane */
ExtensionAPI *RubyExtension::Pane::_host = NULL;
VALUE RubyExtension::Pane::_def = 0;

RubyExtension::Pane::IFunctions RubyExtension::Pane::_functions;
RubyExtension::Pane::IProperties RubyExtension::Pane::_properties;

std::string toCamelCase(const std::string& str)
{
	std::string result(str);
	char& c = result[0];
	c = (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
	return result;
}

void RubyExtension::Pane::create(ExtensionAPI *host, VALUE parent)
{
	_host = host;
	
	_def = rb_define_class_under(parent, "Pane", rb_cObject);
	rb_define_method(_def, "initialize", reinterpret_cast<HOOK>(&initialize), 1);
	rb_define_method(_def, "range", reinterpret_cast<HOOK>(&range), 1);
	
	Pane::Property::create(_host, _def);
	
	VALUE pEditor = instance(ExtensionAPI::paneEditor);
	VALUE pOutput = instance(ExtensionAPI::paneOutput);
	VALUE pFindOutput = instance(ExtensionAPI::paneFindOutput);
	
	/* Functions */ {
		IFaceFunction func = { "", 0, iface_void, { iface_void, iface_void } };
		std::string ccName;
		for(int i = 0; i < IFaceTable::functionCount; ++i) {
			func = IFaceTable::functions[i];
			ccName = toCamelCase(func.name);
			
			_functions[ccName] = func;
			rb_define_method(_def, ccName.c_str(), reinterpret_cast<HOOK>(&function), -1);
		}
	}
	
	/* Properties */ {
		IFaceProperty prop = { "", 0, 0, iface_void, iface_void };
		std::string ccName;
		for(int i = 0; i < IFaceTable::propertyCount; ++i) {
			prop = IFaceTable::properties[i];
			ccName = toCamelCase(prop.name);
			
			_properties[ccName] = prop;
			
			if(prop.paramType == iface_void) {
				rb_define_method(_def, ccName.c_str(), reinterpret_cast<HOOK>(&property), -1);
				rb_define_method(_def, (ccName + "=").c_str(), reinterpret_cast<HOOK>(&property), -1);
			} else {
				ID id = rb_intern(ccName.c_str());
				rb_attr(_def, id, 1, 0, Qfalse);
				
				rb_iv_set(pEditor, ("@" + ccName).c_str(), Pane::Property::instance(pEditor, ccName.c_str()));
				rb_iv_set(pOutput, ("@" + ccName).c_str(), Pane::Property::instance(pOutput, ccName.c_str()));
				rb_iv_set(pFindOutput, ("@" + ccName).c_str(), Pane::Property::instance(pFindOutput, ccName.c_str()));
				
			}
		}
	}
	
	rb_define_const(parent, "Editor", pEditor);
	rb_define_const(parent, "Output", pOutput);
	rb_define_const(parent, "FindOutput", pFindOutput);
}

VALUE RubyExtension::Pane::instance(ExtensionAPI::Pane pane)
{
	int argc = 1;
	VALUE argv[] = { INT2FIX(pane) };
	
	return rb_class_new_instance(argc, argv, _def);
}

ExtensionAPI::Pane RubyExtension::Pane::pane(VALUE self)
{
	return static_cast<ExtensionAPI::Pane>(FIX2INT(rb_iv_get(self, "@pane")));
}

VALUE RubyExtension::Pane::initialize(VALUE self, VALUE pane)
{
	rb_iv_set(self, "@pane", pane);
	return self;
}

sptr_t RubyExtension::Pane::send(VALUE self, unsigned int msg, uptr_t wParam, sptr_t lParam)
{
	return _host->Send(pane(self), msg, wParam, lParam);
}

uptr_t RubyExtension::Pane::createType(VALUE self, IFaceType type, VALUE arg)
{
	switch(type) {
		case iface_void:
			{
				return 0;
			} break;
		case iface_int:
		case iface_length:
		case iface_position:
		case iface_colour:
		case iface_keymod:
			{
				return NUM2INT(arg);
			} break;
		case iface_bool:
			{
				return arg == Qtrue;
			} break;
		case iface_string:
		case iface_cells:
			{
				Check_Type(arg, T_STRING);
				return (uptr_t)STR2CSTR(arg);
			} break;
		case iface_textrange:
			{
				if(rb_class_of(arg) != rb_cRange)
					rb_raise(rb_eTypeError, "argument expected to be a range");
				
				int begin = FIX2INT(callFunction(arg, rb_intern("begin"), 0, NULL));
				int end   = FIX2INT(callFunction(arg, rb_intern("end"),   0, NULL));
				
				/* we need the length to allocate the string */
				if(end == -1)
					end = send(self, SCI_GETTEXTLENGTH);
				
				int len = end - begin;
				
				TextRange *range = new TextRange;
				range->chrg.cpMin = begin;
				range->chrg.cpMax = end;
				range->lpstrText = new char[len + 1];
				return (uptr_t)range;
			} break;
		default:{}
			
	}
	return 0;
}

void RubyExtension::Pane::destroyType(IFaceType type, uptr_t obj)
{
	if(type == iface_textrange) {
		TextRange *range = reinterpret_cast<TextRange*>(obj);
		delete[] range->lpstrText;
		delete range;
	}
}

VALUE RubyExtension::Pane::convertResult(IFaceType type, sptr_t result)
{
	VALUE ret = Qnil;
	switch(type) {
		case iface_int:
		case iface_length:
		case iface_position:
		case iface_colour:
		case iface_keymod:
			{
				ret = INT2NUM(result);
			} break;
		case iface_bool:
			{
				ret = result != 0 ? Qtrue : Qfalse;
			} break;
	}
	return ret;
}

VALUE RubyExtension::Pane::function(int argc, VALUE *argv, VALUE self)
{
	std::string funcName = rb_id2name(rb_frame_last_func());
	IFaceFunction func = _functions[funcName];
	
	uptr_t wParam = 0;
	sptr_t lParam = 0;
	
	if(argc == 1) {
		if(func.paramType[0] != iface_void)
			wParam = createType(self, func.paramType[0], argv[0]);
		else if(func.paramType[1] != iface_void)
			lParam = createType(self, func.paramType[1], argv[0]);
		else
			rb_raise(rb_eArgError, "method expects no argument");
	}
	if(argc == 2) {
		wParam = createType(self, func.paramType[0], argv[0]);
		lParam = createType(self, func.paramType[1], argv[1]);
	}
	if(argc > 2)
		rb_raise(rb_eNoMethodError, "no pane method takes more than 2 arguments");
	
	bool isSR = func.returnType == iface_int && func.paramType[1] == iface_stringresult;
	if(isSR) {
		int len = send(self, func.value, wParam, 0); // get length of result
		if(funcName == "getCurLine") // the first param of getCurLine is useless
			wParam = len;
		lParam = (sptr_t)new char[len];
	}
	
	sptr_t result = send(self, func.value, wParam, lParam);
	VALUE ret = convertResult(func.returnType, result);
	
	/* special cases */
	if(isSR) {
		// ret = rb_ary_new();
		// rb_ary_push(ret, rb_str_new2((char*)lParam));
		// rb_ary_push(ret, INT2FIX(result));
		ret = rb_str_new2((char*)lParam);
		delete[] (char*)lParam;
	}
	
	destroyType(func.paramType[0], wParam);
	destroyType(func.paramType[1], lParam);
	
	return ret;
}

VALUE RubyExtension::Pane::property(int argc, VALUE *argv, VALUE self)
{
	std::string propName = rb_id2name(rb_frame_last_func());
	// remove '=' of the setter
	if(propName[propName.length() - 1] == '=')
		propName.erase(propName.length() - 1);
	
	IFaceProperty prop = _properties[propName];
	
	VALUE ret = Qnil;
	
	uptr_t wParam = 0;
	sptr_t lParam = 0;
	
	if(argc == 0) { // get
		if(prop.getter == 0)
			rb_raise(rb_eNoMethodError, "you can't get this property");
		
		sptr_t result = send(self, prop.getter, wParam, lParam);
		ret = convertResult(prop.valueType, result);
		
	} else if(argc == 1) { // set
		if(prop.setter == 0)
			rb_raise(rb_eNoMethodError, "you can't set this property");
		
		switch(prop.valueType) {
			case iface_int:
			case iface_length:
			case iface_position:
			case iface_colour:
			case iface_keymod:
				{
					wParam = NUM2INT(argv[0]);
				} break;
			case iface_bool:
				{
					wParam = argv[0] == Qtrue;
				} break;
			case iface_string:
				{
					Check_Type(argv[0], T_STRING);
					lParam = (sptr_t)STR2CSTR(argv[0]);
				} break;
		}
		
		send(self, prop.setter, wParam, lParam);
		
	} else {
		rb_raise(rb_eArgError, "property misused");
	}
	
	return ret;
}

VALUE RubyExtension::Pane::range(VALUE self, VALUE range)
{
	if(rb_class_of(range) != rb_cRange)
		rb_raise(rb_eTypeError, "argument expected to be a range");
	
	int begin = FIX2INT(callFunction(range, rb_intern("begin"), 0, NULL));
	int end   = FIX2INT(callFunction(range, rb_intern("end"),   0, NULL));
	
	if(end == -1)
		end = send(self, SCI_GETTEXTLENGTH);
	
	char *text = _host->Range(pane(self), begin, end);
	VALUE result = rb_str_new2(text);
	delete[] text;
	
	return result;
}

/* Pane::Property */
ExtensionAPI *RubyExtension::Pane::Property::_host = NULL;
VALUE RubyExtension::Pane::Property::_def = 0;

void RubyExtension::Pane::Property::create(ExtensionAPI *host, VALUE parent)
{
	_host = host;
	
	_def = rb_define_class_under(parent, "Property", rb_cObject);
	rb_define_method(_def, "initialize", reinterpret_cast<HOOK>(&initialize), 2);
	rb_define_method(_def, "[]", reinterpret_cast<HOOK>(&get), 1);
	rb_define_method(_def, "[]=", reinterpret_cast<HOOK>(&set), 2);
}

VALUE RubyExtension::Pane::Property::instance(VALUE pane, const char *name)
{
	int argc = 2;
	VALUE argv[] = { pane, rb_str_new2(name) };
	
	return rb_class_new_instance(argc, argv, _def);
}

VALUE RubyExtension::Pane::Property::initialize(VALUE self, VALUE pane, VALUE name)
{
	rb_iv_set(self, "@pane", pane);
	rb_iv_set(self, "@name", name);
	return self;
}

VALUE RubyExtension::Pane::Property::get(VALUE self, VALUE key)
{
	std::string propName = STR2CSTR(rb_iv_get(self, "@name"));
	IFaceProperty prop = _properties[propName];
	
	if(prop.getter == 0)
		rb_raise(rb_eNoMethodError, "you can't get this property");
	
	VALUE pane = rb_iv_get(self, "@pane");
	
	uptr_t wParam = createType(pane, prop.paramType, key);
	sptr_t lParam = 0;
	
	if(prop.valueType == iface_string) { // special case
		sptr_t len = send(pane, prop.getter, wParam, 0);
		lParam = (sptr_t)new char[len];
	}
	
	sptr_t result = send(pane, prop.getter, wParam, lParam);
	
	VALUE ret = Qnil;
	
	if(prop.valueType == iface_string) {
		ret = rb_str_new((char*)lParam, result);
		delete[] (char*)lParam;
	} else {
		ret = convertResult(prop.valueType, result);
	}
	
	return ret;
}

VALUE RubyExtension::Pane::Property::set(VALUE self, VALUE key, VALUE value)
{
	std::string propName = STR2CSTR(rb_iv_get(self, "@name"));
	IFaceProperty prop = _properties[propName];
	
	if(prop.setter == 0)
		rb_raise(rb_eNoMethodError, "you can't set this property");
	
	VALUE pane = rb_iv_get(self, "@pane");
	
	uptr_t wParam = createType(pane, prop.paramType, key);
	sptr_t lParam = createType(pane, prop.valueType, value);
	
	send(pane, prop.setter, wParam, lParam);
	
	return Qnil;
}
