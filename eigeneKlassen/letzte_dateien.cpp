#include "letzte_dateien.h"

letzte_dateien::letzte_dateien()
{
    set_anz_eintreage(3);
}

letzte_dateien::letzte_dateien(uint anzahl_der_eintraege)
{
    set_anz_eintreage(anzahl_der_eintraege);
}

void letzte_dateien::set_anz_eintreage(uint neue_anz)
{
    //darf nicht verwendet werde, wenn bereits Daten eingelesen sind
    if(neue_anz > 1)
    {
        Dateinamen.clear();
        Anz_eintraege = neue_anz;
    }
}

void letzte_dateien::datei_merken(QString name)
{
    QString tmp = Dateinamen.get_text();
    if(tmp.contains(name))
    {
        uint pos=0;
        for(uint i = 1 ; i<=Dateinamen.zeilenanzahl() ; i++)
        {
            if(Dateinamen.zeile(i) == name)
            {
                pos = i;
                break;
            }
        }
        Dateinamen.zeilen_loeschen(pos,1);
        Dateinamen.zeile_anhaengen(name);
    }else if(Dateinamen.zeilenanzahl() < Anz_eintraege)
    {
        Dateinamen.zeile_anhaengen(name);
    }else
    {
        Dateinamen.zeilen_loeschen(1,1);
        Dateinamen.zeile_anhaengen(name);
    }
}

void letzte_dateien::datei_vergessen(QString name)
{
    for(uint i=1; i<=Dateinamen.zeilenanzahl() ;i++)
    {
        if(Dateinamen.zeile(i) == name)
        {
            Dateinamen.zeile_loeschen(i);
            break;
        }
    }
}

QString letzte_dateien::text()
{
    QString retstr;
    //Reihenfolge der Einträge umdrehen:
    for(uint i=Dateinamen.zeilenanzahl(); i>0;i--)
    {
        retstr += Dateinamen.zeile(i);
        retstr += "\n";
    }
    retstr = retstr.left(retstr.length() - 1);//letzets Zeichen löschen = "\n"
    return retstr;
}
void letzte_dateien::set_text(QString liste)
{
    text_zeilenweise tz;
    tz.set_text(liste);

    if(tz.zeilenanzahl() <= Anz_eintraege)
    {
        Dateinamen = tz;
    }
}
