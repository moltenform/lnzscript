
#include <QtScript>
#include "provide_script.h"
#include "print_function.h"
#include "util_au3.h"

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

StringResult ProvideScript::EvalString(QString contents)
{
	QScriptValue ret = engine.evaluate(contents);
	if (engine.hasUncaughtException())
	{
		int lineno = engine.uncaughtExceptionLineNumber();
		QString msg = ret.toString();
		QString readableError = msg.sprintf("%s, at %d", qPrintable(msg), lineno);
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
	
	QString strFilename = ctx->argument(0).toString();
	QString contents;
	try
	{
		QFile file(strFilename);
		if (!file.exists()) return ctx->throwError("Could not include file - file does not exist.");
		file.open(QIODevice::ReadOnly);
		contents = file.readAll();
		file.close();
	}
	catch (...)
	{
		return ctx->throwError("Could not include file.");
	}
	eng->evaluate(contents); //if this throws an exception, print it in a way that can be understood.
	if (eng->hasUncaughtException())
	{
		int lineno = engine.uncaughtExceptionLineNumber();
		QString msg = ret.toString();
		QString readableError = msg.sprintf("%s, at %d", qPrintable(msg), lineno);
		g_LnzScriptPrintCallback( &readableError); // print readable error
		
		// do not reset the exception, so that the script aborts.
	}
	
	return eng->nullValue();
}





