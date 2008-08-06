
#include <QApplication>

#include "testinterfaceform.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TestInterfaceForm form;
    form.show();
    return app.exec();
}
