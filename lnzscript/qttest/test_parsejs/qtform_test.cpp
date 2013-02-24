

#include "qtform_test.h"

#include "..\..\provide_script\parse_js.h"
#include "..\..\provide_script\parse_js.cpp"


#ifndef LNZCONSOLEONLY

#include <QtGui>

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
	
	QString strProcessed = processLiteralStrings(strIn);
	ui.txtOutput->setPlainText(strProcessed);
}

#endif

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
		QString strActualOutput = processLiteralStrings(strInput);
		strExpectedOutput.replace(" ","`"); strActualOutput.replace(" ","`");
		if (strExpectedOutput != strActualOutput) {
			strExpectedOutput.replace("\r","\\r"); strExpectedOutput.replace("\n","\\n"); strExpectedOutput.replace("\t","\\t");
			strActualOutput.replace("\r","\\r"); strActualOutput.replace("\n","\\n"); strActualOutput.replace("\t","\\t");
			return "Test failed " + IntToQStr(t) + " \nExpected-"+IntToQStr(strExpectedOutput.length())+":  " + strExpectedOutput + "\nGot-"+IntToQStr(strActualOutput.length())+"     :  "+strActualOutput;
		}
	}
	return "All " + IntToQStr(astrTests.size()) + " tests pass.";
}

