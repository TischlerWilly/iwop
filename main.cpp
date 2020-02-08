#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.set_arg(argc, argv);
    w.show();

    return a.exec();
}
