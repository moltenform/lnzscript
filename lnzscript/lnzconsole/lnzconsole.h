
#include <iostream>

#include "provide_script/provide_script.h"


class LnzConsole
{
    
public:
	LnzConsole();
	void addArgv(int argc, char *argv[]);
	void beginInteractiveSession();
	void evaluateAndPrintResults(const char * strInput, const char * strName = 0);
	bool getConfirmationToRunScript();

private:
	ProvideScript provideScript; 
};
