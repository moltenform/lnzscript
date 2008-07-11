

#include "testinterfaceconsole.h"
#include <iostream>

int main(int argc, char *argv[])
{
	TestInterfaceConsole console;
	
	char doc[] = "LnzScript Console\n\tRun with /r, read from stdin until EOF\n\tRun with /f, and file name for arg 2, load .js script and run it\n\tRun with /fconfirm, same as /f but ask for confirmation.\n\tRun with /e, and text for arg 2, execute the text and quit\n\tRun with no arguments, interactive mode.";

	if (argc == 3 && strcmp(argv[1], "/e")==0)
	{
		console.evaluateAndPrintResults( argv[2] );
	}
	else if (argc >= 3 && (strcmp(argv[1], "/f")==0||strcmp(argv[1], "/fconfirm")==0))
	{
		if (strcmp(argv[1], "/fconfirm")==0)
		{
			// present dialog asking for confirmation
			bool bContinue = console.getConfirmationToRunScript();
			if (!bContinue) return 1;
		}
		
		// read from file and run it
		QString contents;
		try
		{
			QFile file(argv[2]);
			file.open(QIODevice::ReadOnly);
			contents = file.readAll();
			file.close();
		} catch (...) { std::cerr << "Error."; return 0; }
		
		if (contents.isEmpty()) return 0; // string was empty
		
		// set the current directory to the directory of the script. More intuitive for the user.
		// (we've already recorded the previous directory before)
		QFileInfo fileInfo(argv[2]);
		QDir::setCurrent(fileInfo.absolutePath());
		
		// add argv
		console.addArgv(argc, argv);
		
		console.evaluateAndPrintResults( contents.toLatin1() );
	}
	else if (argc == 2 && strcmp(argv[1], "/r")==0)
	{
		// read from stdin until EOF
		// Send "Ctrl+Z" to exit.
		
		std::string strOut;
		getline(std::cin, strOut, '\0');
		console.evaluateAndPrintResults( strOut.c_str() );

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
