
#include <QApplication>

#include "qtform_test.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	TestForm form;
	form.show();
	return app.exec();
}
