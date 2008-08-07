#include <iostream>
#include <QString>

// to build:
// open Qt command prompt
// run qmake qtconsole_hello.pro
// then run make.

int main(int argc, char *argv[])
{
	QString testing = "this is a qt string.";
	
	const char* cstr = testing.toLatin1();
	std::cout << cstr;
	
}
