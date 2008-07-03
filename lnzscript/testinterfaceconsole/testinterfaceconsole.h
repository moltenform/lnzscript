
#include <iostream>

#include "provide_script/provide_script.h"


class TestInterfaceConsole
{
    
public:
	TestInterfaceConsole();
	void beginInteractiveSession();
	void evaluateAndPrintResults(const char * strInput);

private:
	ProvideScript provideScript; 
};
