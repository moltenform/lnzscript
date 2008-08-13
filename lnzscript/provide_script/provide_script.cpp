#include <QtScript>
#include "provide_script.h"
#include "print_function.h"
#include "provide_common.h"
#include "parse_js.h"

#include "functions_expose.h"

// The way things are now, you can create multiple ProvideScript objects, but they will share a single "print" function.

ProvideScript::ProvideScript()
{
	// constructor
	launchorz_functions::util_au3init();
	launchorz_functions::util_nircmd_init();
	
	// the engine was already created
	// create objects
	launchorz_functions::AddGlobalObjects(&engine);
	
	// add the print function to the engine
	QScriptValue fnScriptPrint = engine.newFunction(g_ProvideScript_PrintFunction);
	engine.globalObject().setProperty("print", fnScriptPrint);
	
	// add the include function to the engine
	QScriptValue fnScriptInclude = engine.newFunction(g_ProvideScript_IncludeFunction);
	engine.globalObject().setProperty("include", fnScriptInclude);
	
	// add the alert function and confirm function.
	engine.evaluate("alert = function(s){return Dialog.alert('LnzScript',s);}\n confirm = function(s){return Dialog.askYesNo('LnzScript',s)==Dialog.YES;}\n prompt=function(s){return Dialog.input('LnzScript',s)}\n");
	engine.evaluate("if (Process && Internet && Process.openFile) { Internet.openUrl = Process.openFile;}\n");
	
	// add flag saying that we have not yet included standard JavaScript libraries
	engine.globalObject().setProperty("__includedstd__", QScriptValue(&engine,false));
}


StringResult ProvideScript::EvalScript(QString filename)
{
	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	QString contents = file.readAll();
	file.close();
	
	if (contents.isEmpty()) // string was empty
		return StringResult("");
	
	return EvalString(contents);
}

// there should be something like this that returns a QScriptValue. This would be better.
// the problem is that there have to be two return values: What was the result? and Was there an exception?
StringResult ProvideScript::EvalString(QString contentsRaw, QString optionalFileName /*=0*/)
{
	QString contents = processLiteralStrings(contentsRaw);
	// Set "main" flag signalling that this file was not included
	QScriptValue ret = engine.evaluate("var __name__ = 'main';" + contents);
	if (engine.hasUncaughtException())
	{
		int lineno = engine.uncaughtExceptionLineNumber();
		QString msg = ret.toString();
		QString readableError = msg.sprintf("Script error occurred. \n%s:%d: %s", qPrintable(optionalFileName), lineno, qPrintable(msg));
		return StringResult(readableError, 1); // set error flag to 1
		// clear exception here?  engine.clearExceptions();
	}
	else
	{
		// When evaluating, print out "0" and "false" but don't print "null" or "undefined"
		if (! ret.toBoolean() && ret.toString()!="false" && !ret.isNumber())
			return StringResult(ret.toString(), -1);
		else
			return StringResult(ret.toString(), 0); 
	}
}


void ProvideScript::addArgv(int argc, char *argv[])
{
	// arg0 is lnzscript, arg1 is /f
	if (argc <= 2) return;
	int offset = 2; // how many arguments to ignore
	
	QScriptValue ar = engine.newArray(argc - offset);
	for (int i=offset; i<argc; i++)
		ar.setProperty(i-offset, QScriptValue(&engine, argv[i]));
	engine.globalObject().setProperty("argv", ar);
}

QScriptValue g_ProvideScript_PrintFunction(QScriptContext *ctx, QScriptEngine *eng)
{
	if (ctx->argumentCount()!=1) return ctx->throwError("print takes one argument(s).");
	// we don't check if it is a string, because .toString() on numbers will work just fine.
	
	QString str = ctx->argument(0).toString();
	g_LnzScriptPrintCallback( &str );
	return eng->nullValue();
}

QScriptValue g_ProvideScript_IncludeFunction(QScriptContext *ctx, QScriptEngine *eng)
{
	if (ctx->argumentCount()!=1) return ctx->throwError("include takes one argument(s).");
	if (!ctx->argument(0).isString()) return ctx->throwError(QScriptContext::TypeError,"include: argument 0 is not a string");

	// note there is nothing to stop a file from including itself. That would be bad; let's not do that.
	QString strFilename = ctx->argument(0).toString();
	
	if (strFilename == "<std>")
	{
		// check if they have already been included:
		if (eng->globalObject().property("__includedstd__", QScriptValue::ResolveLocal).toBoolean()) return eng->nullValue();
		
		strFilename = launchorz_functions::get_base_directory() + "std.js";
		eng->globalObject().setProperty("__includedstd__", QScriptValue(eng,true));
	}
	
	QString contentsRaw;
	try
	{
		QFile file(strFilename);
		if (!file.exists()) return ctx->throwError("Could not include file - file does not exist.");
		file.open(QIODevice::ReadOnly);
		contentsRaw = file.readAll();
		file.close();
	}
	catch (...)
	{
		return ctx->throwError("Could not include file.");
	}
	QString contents = processLiteralStrings(contentsRaw);
	// Set flag signalling that this WAS included. Because it is declared var, it should be private.
	QScriptValue ret = eng->evaluate("var __name__ = 'included';" + contents); //if this throws an exception, print it in a way that can be understood.
	if (eng->hasUncaughtException())
	{
		int lineno = eng->uncaughtExceptionLineNumber();
		QString msg = ret.toString();
		QString readableError = msg.sprintf("Script error occurred. \n%s:%d: %s", qPrintable(strFilename), lineno, qPrintable(msg));
		g_LnzScriptPrintCallback( &readableError); // print readable error
		
		// do not reset the exception, so that the script aborts.
	}
	
	return eng->nullValue();
}

