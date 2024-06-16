#include "mainwindow.h"
#include "drawingwidget.h"
#include <QApplication>

int flag = 1;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
