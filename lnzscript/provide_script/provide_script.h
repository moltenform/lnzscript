#ifndef PROVIDE_SCRIPT_H
#define PROVIDE_SCRIPT_H
#include <QtScript>

struct StringResult
{
public:
	QString str;
	int errnumber;
	StringResult(QString instr, int inerrno=0) : str(instr),errnumber(inerrno) {}
	// Errnumber:
	// NEGATIVE - information, not an error
	// 0		- normal
	// POSITIVE  - error or uncaught exception
};

// to reset, you will have to create a new instance of me.
class ProvideScript
{
public:
	ProvideScript();
	StringResult EvalScript(QString filename);
	StringResult EvalString(QString code, QString optionalFileName="");
	
	void addArgv(int argc, char *argv[]);

	
private:
	// QString processLiteralStrings(const QString& strInput)
	QScriptEngine engine;
};

QScriptValue g_ProvideScript_PrintFunction(QScriptContext *ctx, QScriptEngine *eng);
QScriptValue g_ProvideScript_IncludeFunction(QScriptContext *ctx, QScriptEngine *eng);

#endif

