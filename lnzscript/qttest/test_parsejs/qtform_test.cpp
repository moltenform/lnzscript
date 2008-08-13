
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

QString runTests()
{
	QFile file("parsetests.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	 return "Could not open file.";
	
	QString contents = file.readAll();
	file.close();
	QStringList astrTests = contents.split("~~");
	for (int t=0; t<astrTests.size(); t++)
	{
		QStringList astrTestParts = astrTests[t].split("~");
		if (astrTestParts.size() != 2) return "Malformed test " + IntToQStr(t) + " needs 2 parts: " + astrTests[t];
		QString strInput = astrTestParts[0].trimmed();
		QString strExpectedOutput = astrTestParts[1].trimmed();
		QString strActualOutput = parseLiteralStrings(strInput);
		if (strExpectedOutput != strActualOutput) 
			return "Test failed " + IntToQStr(t) + " \nExpected:\t" + strExpectedOutput + "\nGot:\t"+strActualOutput;
	}
	return "All " + IntToQStr(astrTests.size()) + " tests pass.";
}

