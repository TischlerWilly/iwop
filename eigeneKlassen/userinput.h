#ifndef USERINPUT_H
#define USERINPUT_H

#include "Dialoge/dialog_userinput.h"
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneKlassen/formel.h"
#include "eigeneFunktionen/text.h"
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
    Dialog_userinput dui;
    QString Def;    //Default
    QString Input;  //Nutzer-Eingabe
};

#endif // USERINPUT_H
