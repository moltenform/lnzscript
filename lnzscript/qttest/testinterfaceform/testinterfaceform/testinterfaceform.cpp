
#include <QtGui>
#include "testinterfaceform.h"
#include "provide_script/print_function.h"

TestInterfaceForm::TestInterfaceForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	connect(ui.btnGo, SIGNAL(clicked()), this, SLOT(on_btn_go()));
	
	// Keep reference to pointer to the text edit, will be used for print context.
	g_LnzScriptPrintCallbackContext = (void *)ui.txtOutput;
}

void TestInterfaceForm::on_btn_go()
{
	QString strIn = ui.txtInput->toPlainText();
	
	StringResult strOut = provideScript.EvalString(strIn);
	
	// if the result is "null" or "undefined", don't print it.
	if (strOut.errnumber != -1)
		g_LnzScriptPrintCallback( &(strOut.str));
}



// data is passed through the "context" pointer.
void * g_LnzScriptPrintCallbackContext;
void g_LnzScriptPrintCallback(QString * str)
{
	QTextEdit* txtOutput = (QTextEdit *) g_LnzScriptPrintCallbackContext;
	static QString newline("\n");
	txtOutput->setPlainText(txtOutput->toPlainText() + newline + (*str));
	
}

