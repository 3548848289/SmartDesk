#include "mainwindow.h"
#include <QApplication>

#include "ElaApplication.h"
#include "ElaWindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ElaApplication::getInstance()->init();
    MainWindow w;
    w.show();
    return a.exec();
}
