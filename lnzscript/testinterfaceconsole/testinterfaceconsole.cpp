#include <QtScript>
#include "testinterfaceconsole.h"
#include "provide_script/print_function.h"
#include <iostream>

TestInterfaceConsole::TestInterfaceConsole()
{
	// create provide script object, and so on.
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
	
	//std::cout << "Processing, and the results are !" << c_strInput;
}

void g_LnzScriptPrintCallback(QString * str)
{
	const char * s = str->toAscii();
	std::cout << "\n" << s;
}

bool TestInterfaceConsole::getConfirmationToRunScript()
{
	QScriptValue res = provideScript.EvalString("Dialog.askYesNo('Confirmation','Are you sure you want to run this script?') == Dialog.YES");
	return res.toBoolean();
}