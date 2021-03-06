#ifndef USERINPUT_H
#define USERINPUT_H

#include "Dialoge/dialog_userinput.h"
#include "Funktionen/umwandeln.h"
#include "Klassen/formel.h"
#include "Funktionen/text.h"
#include <QMessageBox>

class userinput : public QObject
{
    Q_OBJECT

public:
    userinput();
    void setWindowTitle(QString title);
    void set_default(QString d);
    void set_default(double d);
    void set_default(double d, int anz_nachkommastellen);
    QString input();
    void eingabedlg();
    void formelauswertung();

public slots:
    void set_input(QString inp);

private:
    Dialog_userinput Dui;
    QString Def;    //Default
    QString Input;  //Nutzer-Eingabe
};

#endif // USERINPUT_H
