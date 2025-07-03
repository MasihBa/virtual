#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w1;
    MainWindow w2;
    MainWindow w3;
    MainWindow w4;
    w1.show();
    w2.show();
    w3.show();
   w4.show();
    return a.exec();
}
