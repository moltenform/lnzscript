
#include <QtGui>
#include "qtform_test.h"

TestForm::TestForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	connect(ui.btnGo, SIGNAL(clicked()), this, SLOT(on_btn_go()));
	
}

void TestForm::on_btn_go()
{
	QString strIn = ui.txtInput->toPlainText();
	
	ui.txtOutput->setPlainText(ui.txtOutput->toPlainText() + "\n" + strIn);
}



