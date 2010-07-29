

#include "lnzconsole.h"
#include <QtScript>
#include <qapplication.h>
#include <iostream>

int runScriptFile(LnzConsole* console, const char* scriptFile, int argc, char *argv[])
{
	// read from file and run it
	QString contents;
	QFile file(scriptFile);
	if (!file.exists()) {std::cerr << "Could not open file."; return 1; }
	try
	{
		file.open(QIODevice::ReadOnly);
		contents = file.readAll();
		file.close();
	} catch (...) { std::cerr << "Could not open file."; return 1; }
	
	if (contents.isEmpty()) return 0; // string was empty
	
	// set the current directory to the directory of the script. More intuitive for the user.
	// (we've already recorded the previous directory before)
	QFileInfo fileInfo(scriptFile);
	QDir::setCurrent(fileInfo.absolutePath());
	
	// add argv
	console->addArgv(argc, argv);
	
	console->evaluateAndPrintResults( contents.toLatin1(), scriptFile );
	std::cout << std::endl; //ending with newline looks nicer in editor
	return 0;
}

int main(int argc, char *argv[])
{
	QCoreApplication unusedApp(argc,argv);
	// One must have a QApplication instance before running QtScripts.
	// http://www.developingprogrammers.com/index.php/2006/04/19/console-applications-in-qt/ has a basic qt console app.
	
	LnzConsole console;
	
	char doc[] = "LnzScript Console\n\tRun with name of script to run that script.\n\tRun with /r, read from stdin until EOF\n\tRun with /f, and file name for arg 2, load script and run it\n\tRun with /fconfirm, same as /f but ask for confirmation.\n\tRun with /e, and code in arg 2, execute the text and quit\n\tRun with no parameters, interactive mode.";
	
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
		return runScriptFile(&console, argv[2], argc, argv);
	}
	else if (argc == 2 && strcmp(argv[1], "/r")==0)
	{
		// read from stdin until EOF
		// Send "Ctrl+Z" to exit.
		
		std::string strOut;
		getline(std::cin, strOut, '\0');
		console.evaluateAndPrintResults( strOut.c_str() );

	}
	else if (argc == 2 && (strcmp(argv[1], "/?")==0||strcmp(argv[1], "-?")==0))
	{
		std::cout << doc << std::endl;
	}
	else if (argc == 2) //running a file, as in lnzscript.exe foo.jsz
	{
		return runScriptFile(&console, argv[1], argc, argv);
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
	return 0;
}
