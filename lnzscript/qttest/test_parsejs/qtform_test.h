

#include <QWidget>
#include "ui_qtform_test_form.h"


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


