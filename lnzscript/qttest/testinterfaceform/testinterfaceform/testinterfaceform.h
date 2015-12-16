#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include "ui_testinterfaceform.h"
#include "provide_script/provide_script.h"

class TestInterfaceForm : public QWidget
{
	Q_OBJECT

public:
	TestInterfaceForm(QWidget *parent = 0);

public slots:
	void on_btn_go();


private:
	Ui::TestInterfaceForm ui;
	ProvideScript provideScript; 
};

// note defined as extern to avoid "multiple definition" error.
// apparently include guards only work per .cpp file.
extern void * g_LnzScriptPrintCallbackContext;

#endif

