#include "tabelle_tz3.h"

tabelle_tz3::tabelle_tz3()
{
    set_trennzeichen_zeilen('\n');
    set_trennzeichen_spalten(';');
    set_trennzeichen_eintraege('/');
}

//--------------------------------------------------------set_xy:
void tabelle_tz3::set_trennzeichen_zeilen(char neues_Trennzeichen)
{
    Zeile.set_trennzeichen(neues_Trennzeichen);
}
void tabelle_tz3::set_trennzeichen_spalten(char neues_Trennzeichen)
{
    Spalte.set_trennzeichen(neues_Trennzeichen);
}
void tabelle_tz3::set_trennzeichen_eintraege(char neues_Trennzeichen)
{
    Eintrag.set_trennzeichen(neues_Trennzeichen);
}
void tabelle_tz3::set_text(QString neuer_text)
{
    Zeile.set_text(neuer_text);
}

//--------------------------------------------------------get_xy:
QString tabelle_tz3::zeile(uint zeilennummer)
{
    QString tmp = Zeile.zeile(zeilennummer);
    if (tmp == "Zeilennummer ist groesser als Anzahl der Zeilen!!!")
    {
        tmp = "";
    }else if(tmp == "Zeilennummer ist Null!!!")
    {
        tmp = "";
    }
    return tmp;
}
QString tabelle_tz3::spalte(uint zeilennummer, uint spaltennummer)
{
    Spalte.set_text(zeile(zeilennummer));

    QString tmp = Spalte.zeile(spaltennummer);
    if (tmp == "Zeilennummer ist groesser als Anzahl der Zeilen!!!")
    {
        tmp = "";
    }else if(tmp == "Zeilennummer ist Null!!!")
    {
        tmp = "";
    }
    return tmp;
}
QString tabelle_tz3::spalten()
{
    text_zeilenweise tz;

    for(uint i=1 ; i<=Zeile.zeilenanzahl() ; i++)
    {
        Spalte.set_text(Zeile.zeile(i));
        for(uint ii=1 ; ii<=Spalte.zeilenanzahl(); ii++)
        {
            QString tmp = Spalte.zeile(ii);
            if(!tmp.isEmpty() &&  tmp!=" ")
            {
                tz.zeilen_anhaengen(tmp);
            }
        }
    }

    return tz.text();
}
QString tabelle_tz3::eintrag(uint zeilennummer, uint spaltennummer, uint eintragsnummer)
{
    Eintrag.set_text(spalte(zeilennummer, spaltennummer));

    QString tmp = Eintrag.zeile(eintragsnummer);
    if (tmp == "Zeilennummer ist groesser als Anzahl der Zeilen!!!")
    {
        tmp = "";
    }else if(tmp == "Zeilennummer ist Null!!!")
    {
        tmp = "";
    }
    return tmp;
}
uint tabelle_tz3::spaltenzahl(uint zeilennummer)
{
    Spalte.set_text(Zeile.zeile(zeilennummer));
    return Spalte.zeilenanzahl();
}
QString tabelle_tz3::folgespalte(uint zeile_aktuell, uint spalte_aktuell)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(Spalte.trennzeichen());
    uint pos = 0;

    for(uint i=1 ; i<=Zeile.zeilenanzahl() ; i++)
    {
        Spalte.set_text(Zeile.zeile(i));
        for(uint ii=1 ; ii<=Spalte.zeilenanzahl(); ii++)
        {
            QString tmp = Spalte.zeile(ii);
            if(!tmp.isEmpty() &&  tmp!=" ")
            {
                tz.zeilen_anhaengen(tmp);
            }
            if(i==zeile_aktuell  &&  ii==spalte_aktuell)
            {
                pos = tz.zeilenanzahl();
            }
        }
    }

    if(pos < tz.zeilenanzahl()  &&  pos>0)
    {
        return tz.zeile(pos+1);
    }else
    {
        return "";
    }
}
QString tabelle_tz3::vorherigespalte(uint zeile_aktuell, uint spalte_aktuell)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(Spalte.trennzeichen());
    uint pos = 0;

    for(uint i=1 ; i<=Zeile.zeilenanzahl() ; i++)
    {
        Spalte.set_text(Zeile.zeile(i));
        for(uint ii=1 ; ii<=Spalte.zeilenanzahl(); ii++)
        {
            QString tmp = Spalte.zeile(ii);
            if(!tmp.isEmpty() &&  tmp!=" ")
            {
                tz.zeilen_anhaengen(tmp);
            }
            if(i==zeile_aktuell  &&  ii==spalte_aktuell)
            {
                pos = tz.zeilenanzahl();
            }
        }
    }

    if(pos <= tz.zeilenanzahl()  &&  pos>0)
    {
        return tz.zeile(pos-1);
    }else
    {
        return "";
    }
}

//--------------------------------------------------------Manipulationen:
bool tabelle_tz3::zeile_ersaetzen(uint zeilennummer, QString neuer_text)
{
    if(Zeile.zeile_ersaetzen(zeilennummer, neuer_text))
    {
        return true;//Fehler ist aufgetreten
    }else
    {
        return false;//Kein Fehler ist aufgetreten
    }
}
bool tabelle_tz3::spalte_ersatzen(uint zeilennummer, uint spaltennummer, QString neuer_text)
{
    Spalte.set_text(Zeile.zeile(zeilennummer));

    if(Spalte.zeile_ersaetzen(spaltennummer, neuer_text))
    {
        return true;//Fehler ist aufgetreten
    }else
    {
        if(Zeile.zeile_ersaetzen(zeilennummer, Spalte.text()))
        {
            return true;//Fehler ist aufgetreten
        }else
        {
            return false;//Kein Fehler ist aufgetreten
        }
    }
}
bool tabelle_tz3::vorherigespalte_ersaetzen(uint zeile_aktuell, uint spalte_aktuell, QString neuer_text)
{
    //Pos der vorheriegen Spalte finden:
    //Die Funktion arbeitet ein bisschen quick&dirty, weil nur nach dem
    //ersten Vorkommen eines identischen Textes vor der aktuellen Position gesucht wird
    //und angenommen wird, dass es nur einen identischen Text gibt
    QString text_vorherige_spalte = vorherigespalte(zeile_aktuell, spalte_aktuell);
    uint zeilennummer = 0;
    uint spaltennummer = 0;

    for(uint i=1 ; i<=Zeile.zeilenanzahl() ; i++)
    {
        Spalte.set_text(Zeile.zeile(i));
        for(uint ii=1 ; ii<=Spalte.zeilenanzahl(); ii++)
        {
            QString tmp = Spalte.zeile(ii);
            if(tmp == text_vorherige_spalte   &&    \
                    i <= zeile_aktuell  &&          \
                    ii <= spalte_aktuell)
            {
                zeilennummer = i;
                spaltennummer = ii;
            }
        }
    }
    //Text ersetzen:
    return spalte_ersatzen(zeilennummer, spaltennummer, neuer_text);
}
bool tabelle_tz3::eintrag_ersatzen(uint zeilennummer, uint spaltennummer, uint eintragsnummer, QString neuer_text)
{
    Spalte.set_text(Zeile.zeile(zeilennummer));
    Eintrag.set_text(Spalte.zeile(spaltennummer));

    if(Eintrag.zeile_ersaetzen(eintragsnummer, neuer_text))
    {
        return true;//Fehler ist aufgetreten
    }else
    {
        if(Spalte.zeile_ersaetzen(spaltennummer, Eintrag.text()))
        {
            return true;//Fehler ist aufgetreten
        }else
        {
            if(Zeile.zeile_ersaetzen(zeilennummer, Spalte.text()))
            {
                return true;//Fehler ist aufgetreten
            }else
            {
                return false;//Kein Fehler ist aufgetreten
            }
        }
    }
}
void tabelle_tz3::zeile_anhaengen(QString neuer_text)
{
    Zeile.zeile_anhaengen(neuer_text);
}
bool tabelle_tz3::spalte_anhaengen(uint zeilennummer, QString neuer_text)
{
    if(Zeile.zeilenanzahl() < zeilennummer)
    {
        return true;//Fehler ist aufgetreten
    }else
    {
        Spalte.set_text(Zeile.zeile(zeilennummer));
        Spalte.zeile_anhaengen(neuer_text);
        Zeile.zeile_ersaetzen(zeilennummer, Spalte.text());
        return false;//Kein Fehler ist aufgetreten
    }
}
bool tabelle_tz3::eintrag_anhaengen(uint zeilennummer, uint spaltennummer, QString neuer_text)
{
    if(Zeile.zeilenanzahl() < zeilennummer)
    {
        return true;//Fehler ist aufgetreten
    }else
    {
        if(Spalte.zeilenanzahl() < spaltennummer)
        {
            return true;//Fehler ist aufgetreten
        }else
        {
            Spalte.set_text(Zeile.zeile(zeilennummer));
            Eintrag.set_text(Spalte.zeile(spaltennummer));
            Eintrag.zeile_anhaengen(neuer_text);
            Spalte.zeile_ersaetzen(spaltennummer, Eintrag.text());
            Zeile.zeile_ersaetzen(zeilennummer, Spalte.text());
            return false;//Kein Fehler ist aufgetreten
        }
    }
}

//--------------------------------------------------------






