#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>


 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);

QString firstLabel = "One";
QString secondLabel = "Two";
	 
      QWidget *window = new QWidget;
     QPushButton *button1 = new QPushButton(firstLabel);
     QPushButton *button2 = new QPushButton(secondLabel);
     QPushButton *button3 = new QPushButton("Three");
     QPushButton *button4 = new QPushButton("Four");
     QPushButton *button5 = new QPushButton("Five");

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(button1);
     layout->addWidget(button2);
     layout->addWidget(button3);
     layout->addWidget(button4);
     layout->addWidget(button5);

     window->setLayout(layout);
     window->show();
	 
	 /*
     QPushButton hello("Hello world!");
     hello.resize(100, 30);	 
     hello.show();*/
     
     return app.exec();
 }

