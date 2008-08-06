#include <QtScript>
#include "lnzconsole.h"
#include "provide_script/print_function.h"
#include <iostream>

TestInterfaceConsole::TestInterfaceConsole()
{
	// ProvideScript object is created implicitly.
}
void TestInterfaceConsole::addArgv(int argc, char *argv[])
{
	// ProvideScript object is created implicitly.

	// add command line arguments
	provideScript.addArgv(argc, argv);
}

void TestInterfaceConsole::beginInteractiveSession()
{
	std::cout << std::endl << "LnzScript Interactive session, enter q or exit to quit." << std::endl;
	std::string strLineInput;
	while (true)
	{
		std::cout << std::endl << ">";
		//void* res = (std::cin >> strLineInput);
		getline( std::cin, strLineInput);
		if (strLineInput=="q" || strLineInput=="exit")
			return;
		evaluateAndPrintResults(strLineInput.c_str());
	}
}


void TestInterfaceConsole::evaluateAndPrintResults(const char * c_strInput)
{
	QString strIn(c_strInput);
	
	StringResult strOut = provideScript.EvalString(strIn);
	
	// if the result is "null" or "undefined", don't print it.
	if (strOut.errnumber != -1)
		g_LnzScriptPrintCallback( &(strOut.str));
	
}

void g_LnzScriptPrintCallback(QString * str)
{
	const char * s = str->toAscii();
	std::cout << "\n" << s;
}

bool TestInterfaceConsole::getConfirmationToRunScript()
{
	// this is gross. we shouldn't have to do this.
	StringResult res = provideScript.EvalString("(confirm('Are you sure you want to run this script?')) ? 1:0");
	int nResult = res.str.toInt();
	return (nResult) ? true : false;
}

