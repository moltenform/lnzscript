
#include <QtGui>
#include "qtform_test.h"

#include "parse_js.h"

TestForm::TestForm(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);


	connect(ui.btnGo, SIGNAL(clicked()), this, SLOT(on_btn_go()));
	
	//run tests
	ui.txtOutput->setPlainText(runTests());
}

void TestForm::on_btn_go()
{
	QString strIn = ui.txtInput->toPlainText();
	
	QString strProcessed = parseLiteralStrings(strIn);
	ui.txtOutput->setPlainText(strProcessed);
}



