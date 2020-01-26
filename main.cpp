#include "mainwindow.h"
#include <QApplication>
//#include "eigeneKlassen/text_zeilenweise.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    QCoreApplication app(argc, argv);
    QStringList arglst = app.arguments();
    text_zeilenweise tz;
    for (int i=0; i<arglst.size(); ++i) {
        tz.zeile_anhaengen(arglst.at(i));
    }
    QMessageBox mb;
    mb.setText(tz.get_text());
    mb.exec();
*/
    MainWindow w;
    w.show();

    return a.exec();
}
