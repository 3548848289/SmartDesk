#include "mainwindow.h"
#include <QApplication>

//准备重构

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
