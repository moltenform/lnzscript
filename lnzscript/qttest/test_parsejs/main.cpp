
#include <QApplication>

#include "qtform_test.h"

#ifdef LNZCONSOLEONLY
#include <stdio.h>
int main(int argc, char *argv[])
{
	(void) argc; (void) argv;
	const char* szTestResults = runTests().toAscii();
	printf("results of tests:%s\n", szTestResults);
	return 0;
}
#else

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	TestForm form;
	form.show();
	return app.exec();
}

#endif
