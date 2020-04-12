#include "userinput.h"

userinput::userinput()
{
    connect(&Dui, SIGNAL(send_input(QString)), this, SLOT(set_input(QString)));
}

void userinput::setWindowTitle(QString title)
{
    Dui.setWindowTitle(title);
}

void userinput::set_default(QString d)
{
    Dui.set_default(d);
}

void userinput::set_default(double d)
{
    Dui.set_default(double_to_qstring(d).replace(".",","));
}

void userinput::set_default(double d, int anz_nachkommastellen)
{
    QString def;
    QString tmp = double_to_qstring(d);
    if(anz_nachkommastellen == 0)
    {
        def = text_links(tmp, ".");
    }else
    {
        def = text_links(tmp, ".");
        def += ",";
        QString rechts = text_rechts(tmp, ".");
        for(int i=0; (i<anz_nachkommastellen)&&(i<rechts.count()) ;i++)
        {
            def += rechts.at(i);
        }
    }
    Dui.set_default(def);
}

void userinput::set_input(QString inp)
{
    Input = inp.replace(',','.');
}

QString userinput::input()
{
    return Input;
}

void userinput::eingabedlg()
{
    Dui.exec();
}

void userinput::formelauswertung()
{
    Formel f(Input);
    if(f.ist_fehlerhaft())
    {
        QMessageBox mb;
        mb.setText(f.bekomme_fehler_text());
        mb.exec();
    }else
    {
        Input = f.bekomme_Ergebnis_als_String();
    }
}
