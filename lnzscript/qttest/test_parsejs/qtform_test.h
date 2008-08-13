
#include <QWidget>
#include "ui_qtform_test_form.h"

#define IntToQStr(n) (QString("%1").arg(n))
QString runTests();

class TestForm : public QWidget
{
    Q_OBJECT

public:
    TestForm(QWidget *parent = 0);

public slots:
    void on_btn_go();

private:
    Ui::TestForm ui;

};


