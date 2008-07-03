

#include "testinterfaceconsole.h"
#include <iostream>

int main(int argc, char *argv[])
{
	TestInterfaceConsole console;
	
	char doc[] = "LnzScript Console\n\tRun with /r, read from stdin until EOF\n\tRun with /e, and text for arg 2, execute the text and quit\n\tRun with no arguments, interactive mode.";

	if (argc == 3 && strcmp(argv[1], "/e")==0)
	{
		console.evaluateAndPrintResults( argv[2] );
	}
	else if (argc == 2 && strcmp(argv[1], "/r")==0)
	{
		// read from stdin until EOF
		// Send "Ctrl+Z" to exit.
		
		std::string strOut;
		getline(std::cin, strOut, '\0');
		console.evaluateAndPrintResults( strOut.c_str() );
		
		// Before, tried this, but "a b c" would go through 3 iterations, seemed less efficient.
		/*
		std::string strLine;
		std::string strLine;
		while (std::cin >> strLine)
		{
		   std::cout << "::"+strLine;
			strOut += strLine;
		}*/
	}
	else if (argc == 1) //run with no arguments
	{
		std::cout << doc << std::endl;
		console.beginInteractiveSession();
	}
	else
	{
		std::cout << doc << std::endl << "Invalid parameters.";
	}
	
}
