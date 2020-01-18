#include "werkzeug.h"

werkzeug::werkzeug()
{

}


//------------set_xy:
void werkzeug::set_text(QString neuer_Text)
{
    wkzlist.set_text(neuer_Text);
    QString tmp = wkzlist.get_text();
    if(!tmp.contains(LISTENENDE_WKZ))
    {
        wkzlist.zeile_anhaengen(LISTENENDE_WKZ);
    }
    //aktualisieren();
}
void werkzeug::zeile_anhaengen(QString wkz)
{
    if(wkzlist.zeilenanzahl() == 0)
    {
        set_text(wkz);
    }else
    {
        if(wkz == LISTENENDE_WKZ)
        {
            return;
        }
        wkzlist.zeile_anhaengen(wkz);
    }
}
int werkzeug::zeile_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext)
{
    if(zeilentext == LISTENENDE_WKZ)
    {
        return 0;
    }
    if(zeilennummer_vor_neuer_zeile > wkzlist.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    if(zeilennummer_vor_neuer_zeile == 0)
    {
        wkzlist.zeile_vorwegsetzen(zeilentext);
    }else
    {
        wkzlist.zeile_einfuegen(zeilennummer_vor_neuer_zeile, zeilentext);
    }
    //aktualisieren();
    return 0; //Keine Fehler
}
int werkzeug::zeilen_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext)
{
    if(zeilennummer_vor_neuer_zeile > wkzlist.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    text_zeilenweise tz;
    tz.set_text(zeilentext);
    for(uint i=1 ; i<=tz.zeilenanzahl() ;i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile == LISTENENDE_WKZ)
        {
            return 0;
        }
        if(  (zeilennummer_vor_neuer_zeile == 0)  &&  (i==1)  )
        {
            wkzlist.zeile_vorwegsetzen(zeile);
        }else
        {
            wkzlist.zeile_einfuegen(zeilennummer_vor_neuer_zeile+i-1, zeile);
        }
    }
    //aktualisieren();
    return 0; //Keine Fehler
}

//------------get_xy:
QString werkzeug::zeile(uint zeilennummer)
{
    if(zeilennummer > wkzlist.zeilenanzahl())
    {
        return "Fehler! Ungueltige Zeilennummer";
    }else
    {
        return wkzlist.zeile(zeilennummer);
    }
}
QString werkzeug::zeilen(uint zeilennummer_beginn, uint zeilenmenge)
{
    if(zeilennummer_beginn+zeilenmenge-1  > wkzlist.zeilenanzahl())
    {
        return "Fehler! Ungueltige Zeilennummer";
    }else
    {
        QString tmp;
        for(uint i=zeilennummer_beginn ; i<zeilennummer_beginn+zeilenmenge; i++)
        {
            if(!wkzlist.zeile(i).contains(LISTENENDE_WKZ))
            {
                if(i!=zeilennummer_beginn)
                {
                    tmp += "\n";
                }
                tmp += wkzlist.zeile(i);
            }
        }
        return tmp;
    }
}
int werkzeug::zeile_ersaetzen(uint zeilennummer, QString neuer_zeilentext)
{
    QString alter_text;
    alter_text = wkzlist.zeile(zeilennummer);
    if(alter_text == LISTENENDE_WKZ)
    {
        return 0;
    }
    QString zeilentext = wkzlist.zeile(zeilennummer);
    if(zeilentext.contains(LISTENENDE_WKZ))
    {
        return 0; //Listenende darf nicht gelöscht werden!
    }
    if(zeilennummer > wkzlist.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    if(zeilennummer == 0)
    {
        return 1; //Meldet Fehler in der Funktion
    }
    wkzlist.zeile_ersaetzen(zeilennummer, neuer_zeilentext);
    //aktualisieren();
    return 0; //Keine Fehler
}
int werkzeug::zeile_loeschen(uint zeilennummer)
{
    QString zeilentext = wkzlist.zeile(zeilennummer);
    if(zeilentext.contains(LISTENENDE_WKZ))
    {
        return 0; //Listenende darf nicht gelöscht werden!
    }
    if(zeilennummer > wkzlist.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    wkzlist.zeile_loeschen(zeilennummer);
    //aktualisieren();
    return 0; //Keine Fehler
}
int werkzeug::zeilen_loeschen(uint zeilennummer_beginn, uint zeilenmenge)
{
    if(zeilennummer_beginn+zeilenmenge-1 > wkzlist.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    for(uint i=zeilennummer_beginn+zeilenmenge-1; i>=zeilennummer_beginn ; i--)
    {
        QString tmp = wkzlist.zeile(i);
        if(!tmp.contains(LISTENENDE_WKZ))
        {
            wkzlist.zeile_loeschen(i);
        }
    }
    //aktualisieren();
    return 0; //Keine Fehler
}
text_zeilenweise werkzeug::get_anzeigetext()
{
    text_zeilenweise tz;

    //Dies später noch ändern:
    tz = wkzlist;

    return  tz;
}











