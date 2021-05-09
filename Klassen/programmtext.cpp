#include "programmtext.h"

//##################################################################################
//public:
//##################################################################################
programmtext::programmtext()
{
    clear();
    set_warnungen_ein_aus(true);
    set_aktualisieren_ein_aus(true);
    set_nurlesend(false);
}

//------------------------------------------------------------set_xy:
void programmtext::set_text(QString neuer_Text)
{
    Text.set_text(neuer_Text);
    QString tmp = Text.text();
    if(!tmp.contains(LISTENENDE))
    {
        Text.zeile_anhaengen(LISTENENDE);
    }
    aktualisieren();
}
void programmtext::set_maschinengeometrie(text_zeilenweise tz)
{
    MaschinenGeo.clear();

    for(uint i=1; i<=tz.zeilenanzahl();i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile.contains(STRECKE))
        {
            strecke s(zeile);
            MaschinenGeo.add_strecke(s);
            MaschinenGeo.zeilenvorschub();
        }else if(zeile.contains(BOGEN))
        {
            bogen b(zeile);
            MaschinenGeo.add_bogen(b);
            MaschinenGeo.zeilenvorschub();
        }else if (zeile.contains(KREIS))
        {
            kreis k(zeile);
            MaschinenGeo.add_kreis(k);
            MaschinenGeo.zeilenvorschub();
        }
    }
}

//------------------------------------------------------------get_xy:
QString programmtext::klartext()
{
    QString returnstring;
    for(uint i=1 ; i<=Klartext.zeilenanzahl() ; i++)
    {
        QString tmp = Klartext.zeile(i);
        if(!tmp.isEmpty())
        {
            returnstring += tmp;
        }
    }
    return returnstring;
}
QString programmtext::variablen()
{
    QString returnstring;
    for(uint i=1 ; i<=Var.zeilenanzahl() ; i++)
    {
        QString tmp = Var.zeile(i);
        if(!tmp.isEmpty())
        {
            returnstring += tmp;
        }
    }
    return returnstring;
}
QString programmtext::zeile(uint zeilennummer)
{
    if(zeilennummer > Text.zeilenanzahl())
    {
        return "Fehler! Ungueltige Zeilennummer";
    }else
    {
        return Text.zeile(zeilennummer);
    }
}
QString programmtext::zeilen(uint zeilennummer_beginn, uint zeilenmenge)
{
    if(zeilennummer_beginn+zeilenmenge-1  > Text.zeilenanzahl())
    {
        return "Fehler! Ungueltige Zeilennummer";
    }else
    {
        QString tmp;
        for(uint i=zeilennummer_beginn ; i<zeilennummer_beginn+zeilenmenge; i++)
        {
            if(!Text.zeile(i).contains(LISTENENDE))
            {
                if(i!=zeilennummer_beginn)
                {
                    tmp += "\n";
                }
                tmp += Text.zeile(i);
            }
        }
        return tmp;
    }
}
bool programmtext::hat_ungesicherte_inhalte()
{
    if(Text.text().isEmpty())//Hat gar keine Inhalte
    {
        return false;
    }
    if(Text_kopie.text() == Text.text())//Inhalt wurde seit dem Speichern noch nicht verändert
    {
        return false;
    }else
    {
        return true;
    }
}

//------------------------------------------------------------Manipulationen:
void programmtext::clear()
{
    Text.clear();
    Text_kopie.clear();
    clear_ausser_text();
}
int programmtext::zeile_loeschen(uint zeilennummer)
{
    QString zeilentext = Text.zeile(zeilennummer);
    if(zeilentext.contains(LISTENENDE))
    {
        return 0; //Listenende darf nicht gelöscht werden!
    }
    if(zeilennummer > Text.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    Text.zeile_loeschen(zeilennummer);
    aktualisieren();
    return 0; //Keine Fehler
}
int programmtext::zeilen_loeschen(uint zeilennummer_beginn, uint zeilenmenge)
{
    if(zeilennummer_beginn+zeilenmenge-1 > Text.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    for(uint i=zeilennummer_beginn+zeilenmenge-1; i>=zeilennummer_beginn ; i--)
    {
        QString tmp = Text.zeile(i);
        if(!tmp.contains(LISTENENDE))
        {
            Text.zeile_loeschen(i);
        }
    }
    aktualisieren();
    return 0; //Keine Fehler
}
int programmtext::zeile_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext)
{
    if(zeilentext == LISTENENDE)
    {
        return 0;
    }
    if(zeilennummer_vor_neuer_zeile > Text.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    if(zeilennummer_vor_neuer_zeile == 0)
    {
        Text.zeile_vorwegsetzen(zeilentext);
    }else
    {
        Text.zeile_einfuegen(zeilennummer_vor_neuer_zeile, zeilentext);
    }
    aktualisieren();
    return 0; //Keine Fehler
}
int programmtext::zeilen_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext)
{
    if(zeilennummer_vor_neuer_zeile > Text.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    text_zeilenweise tz;
    tz.set_text(zeilentext);
    for(uint i=1 ; i<=tz.zeilenanzahl() ;i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile == LISTENENDE)
        {
            return 0;
        }
        if(  (zeilennummer_vor_neuer_zeile == 0)  &&  (i==1)  )
        {
            Text.zeile_vorwegsetzen(zeile);
        }else
        {
            Text.zeile_einfuegen(zeilennummer_vor_neuer_zeile+i-1, zeile);
        }
    }
    aktualisieren();
    return 0; //Keine Fehler
}
void programmtext::zeile_anhaengen(QString zeilentext)
{
    if(zeilentext == LISTENENDE)
    {
        return;
    }
    Text.zeilen_anhaengen(zeilentext);
    aktualisieren();
}
int programmtext::zeile_ersaetzen(uint zeilennummer, QString neuer_zeilentext)
{
    QString alter_text;
    alter_text = Text.zeile(zeilennummer);
    if(alter_text == LISTENENDE)
    {
        return 0;
    }
    QString zeilentext = Text.zeile(zeilennummer);
    if(zeilentext.contains(LISTENENDE))
    {
        return 0; //Listenende darf nicht gelöscht werden!
    }
    if(zeilennummer > Text.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    if(zeilennummer == 0)
    {
        return 1; //Meldet Fehler in der Funktion
    }
    Text.zeile_ersaetzen(zeilennummer, neuer_zeilentext);
    aktualisieren();
    return 0; //Keine Fehler
}
void programmtext::aktualisieren()
{
    aktualisiere_klartext_var();
    aktualisiere_geo();
    aktualisiere_anzeigetext();
    aktualisiere_min_max();
}
void programmtext::wurde_gespeichert()
{
    Text_kopie = Text;
}

//------------------------------------------------------------

//##################################################################################
//private:
//##################################################################################
//------------------------------------------------------------set_xy:

//------------------------------------------------------------get_xy:

//------------------------------------------------------------Manipulationen:
void programmtext::clear_ausser_text()
{
    Klartext.clear();
    Var.clear();
    Anzeigetext.clear();
    Geo.clear();
    Fkon.clear();
    Fraeserdarst.clear();
    Werkstuecklaenge = 0;
    Werkstueckbreite = 0;
    Hat_programmkopf = false;
    Hat_programmende = false;
    Sicherheitsabstand = 5;
    Min_x = 0;
    Min_y = 0;
    Max_x = 0;
    Max_y = 0;
    Anz_faufr = 0;
    Anz_fabfa = 0;
    Warnung_frDial = false;
    Versatz_x = 0;
    Versatz_y = 0;
    Versatz_z = 0;
}
QString programmtext::param_to_klartext(QString prgzeile, QString parname, QString varname, QString &varlist, bool varmerken)
{
    //prgzeile == ganze Programmzeile mit allen Parametern
    //param    == Parameter der in Klartext umgerechnet werden soll z.B. BO_X
    //varname  == Variablen-Name mit dem dieser Parameter über das GUI angesprochen werden kann
    //varlist  == liste aller Variablen die in dieser Programmzeile bekannt sind
    //varmerken
    //  0 ->Variable wird nicht zur varlist hinzugefügt
    //  1 ->sie wird hinzugefügt

    QString parwert;
    QString trennz = ";";
    if(prgzeile.contains(trennz+parname))
    {
        parwert = text_mitte(prgzeile, trennz+parname, ENDPAR);              //Parameter-Wert selektieren
    }else
    {
        parwert = text_mitte(prgzeile, parname, ENDPAR);              //Parameter-Wert selektieren
    }

    parwert = variablen_durch_werte_ersetzten(varlist, parwert);  //Variablen durch Werte ersetzen

    parwert = ausdruck_auswerten(parwert);                        //Ergebnis der Berechnung bekommen

    QString kt = parname;
    kt += parwert;
    kt += ENDPAR;

    if(varmerken == true)
    {
        var_ergaenzen(varlist, varname, parwert);
    }

    return  kt;
}
QString programmtext::param_to_klartext_orginal(QString prgzeile, QString parname)
{
    QString kt = parname;
    kt += text_mitte(prgzeile, parname, ENDPAR);
    kt += ENDPAR;
    return  kt;
}
QString programmtext::var_to_klartext(QString prgzeile, QString name, QString wert, QString &varlist)
{
    QString name_bez, name_wert, name_wert_var;
    QString wert_bez, wert_wert;
    name_bez = name;

    //name == Name der Variablen aus der FMC-Datei
    //wert == Name der Variablen aus dem Dialog == der über die Dialoge ansprechbare Name

    //name_bez == der Name von "name"                                  z.B: RTA_X == "MPX="
    //name_wert == der Wert von "name"                                 z.B: 50
    //name_wert_var == der Name von "wert" eingefasst in "[" und "]"   z.B: [MX]
    //wert_bez == der Name von "wert"                                  z.B: MX
    //wert_wert = der Wert von "wert"                                  z.B: 50

    QString trennz = ";";
    if(prgzeile.contains(trennz+name))
    {
        name_wert = text_mitte(prgzeile, trennz+name, ENDPAR);
    }else
    {
        name_wert = text_mitte(prgzeile, name, ENDPAR);
    }
    name_wert_var = "[";
    name_wert_var += name_wert;
    name_wert_var += "]";
    wert_bez = wert;
    wert_wert = text_mitte(prgzeile, wert, ENDPAR);
    wert_wert = variablen_durch_werte_ersetzten(varlist, wert_wert);
    wert_wert = ausdruck_auswerten(wert_wert);

    QString kt;
    kt += name_bez;
    kt += name_wert;
    kt += ENDPAR;
    kt += wert_bez;
    kt += wert_wert;
    kt += ENDPAR;

    if(!wert_wert.contains("AUTO"))
    {
        if(!varlist.contains(name_wert_var))
        {
            varlist += name_wert_var;
            varlist += wert_wert;
            varlist += ENDPAR;
        }else
        {
            QString alterWert = text_mitte(varlist, name_wert_var, ENDPAR);
            varlist.replace(name_wert_var+alterWert, name_wert_var+wert_wert);
        }
    }

    return  kt;
}
QString programmtext::var_to_klartext(QString name, QString wert)
{
    QString kt;
    kt = name;
    kt += wert;
    kt += ENDPAR;
    return kt;
}
void programmtext::var_ergaenzen(QString &varlist, QString name, QString wert)
{
    if(!varlist.contains(name))
    {
        varlist += name;
        varlist += wert;
        varlist += ENDPAR;
    }else
    {
        QString alterWert = text_mitte(varlist, name, ENDPAR);
        varlist.replace(name+alterWert, name+wert);
    }
}
void programmtext::aktualisiere_klartext_var()
{
    if(!Aktualisieren_eingeschaltet)
    {
        return;
    }

    clear_ausser_text();
    QString variablen;
    //wird für Zwischenspeicherung werte Fräsbahnen benötigt:
    QString x, y, z, wkzdm, wkzkor;
    wkzdm = 5; //Defaultwet falls Fräser unbekannt

    for(uint i=1 ; i<=Text.zeilenanzahl() ; i++)
    {
        QString zeile;
        zeile = Text.zeile(i);

        if(  (zeile.at(0) == '/')  &&  (zeile.at(1) == '/')  )
        {
            Klartext.zeilen_anhaengen(" ");
            Var.zeilen_anhaengen(" ");
            continue;//Ausgeblendete Zeile überspringen
        }

        if(zeile.contains(DLG_PKOPF))
        {
            QString tmp;
            tmp = text_mitte(zeile, PKOPF_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                if(  (Hat_programmkopf == true)  &&  (Warnungen_sind_eingeschaltet == true)  )
                {
                    QMessageBox mb;
                    mb.setText("Achtung!\nProgrammkopf mehrfach vorhanden!");
                    mb.exec();
                }
                Hat_programmkopf = true;
                QString zeile_klartext;
                QString tmp;
                zeile_klartext += DLG_PKOPF;
                //PKOPF_KOM1
                //PKOPF_KOM2
                zeile_klartext += param_to_klartext(zeile, PKOPF_L, VAR_PKOPF_L, variablen, true);
                zeile_klartext += param_to_klartext(zeile, PKOPF_B, VAR_PKOPF_B, variablen, true);
                zeile_klartext += param_to_klartext(zeile, PKOPF_D, VAR_PKOPF_D, variablen, true);
                zeile_klartext += param_to_klartext(zeile, PKOPF_FUENFSEI, "void", variablen, false);
                //PKOPF_SPEIGELN
                //PKOPF_BELEGART
                zeile_klartext += param_to_klartext(zeile, PKOPF_XVERS, VAR_PKOPF_XVERS, variablen, true);
                zeile_klartext += param_to_klartext(zeile, PKOPF_YVERS, VAR_PKOPF_YVERS, variablen, true);
                //PKOFP_RTL
                //PKOFP_RTB
                //PKOPF_LOESEN
                //PKOPF_SCHABH
                //PKOPF_SIABST
                //PKOPF_PAPO
                //PKOPF_BEZ

                set_werkstuecklaenge(text_mitte(variablen, VAR_PKOPF_L, ENDPAR).toFloat());
                set_werkstueckbreite(text_mitte(variablen, VAR_PKOPF_B, ENDPAR).toFloat());
                set_werkstueckdicke(text_mitte(variablen, VAR_PKOPF_D, ENDPAR).toFloat());
                set_versatz_x(text_mitte(variablen, VAR_PKOPF_XVERS, ENDPAR).toFloat());
                set_versatz_y(text_mitte(variablen, VAR_PKOPF_YVERS, ENDPAR).toFloat());

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_PENDE))
        {
            QString tmp;
            tmp = text_mitte(zeile, PENDE_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_PENDE;

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_KOM))
        {
            QString zeile_klartext;
            zeile_klartext += DLG_KOM;
            zeile_klartext += text_mitte(zeile, KOM_BEZ, ENDPAR);

            Klartext.zeilen_anhaengen(zeile_klartext);
            Var.zeile_anhaengen(variablen);
        }else if(zeile.contains(DLG_HALT))
        {
            QString tmp;
            tmp = text_mitte(zeile, HALT_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_HALT;
                zeile_klartext += param_to_klartext(zeile, HALT_X, "void", variablen, false);
                zeile_klartext += param_to_klartext(zeile, HALT_Y, "void", variablen, false);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_SPIEGELN))
        {
            QString tmp;
            tmp = text_mitte(zeile, SPIEGELN_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_SPIEGELN;
                zeile_klartext += param_to_klartext(zeile, SPIEGELN_XPOS, VAR_SPIEGELN_XPOS, variablen, true);
                zeile_klartext += param_to_klartext(zeile, SPIEGELN_YPOS, VAR_SPIEGELN_YPOS, variablen, true);
                zeile_klartext += param_to_klartext(zeile, SPIEGELN_XBED, "void", variablen, false);
                zeile_klartext += param_to_klartext(zeile, SPIEGELN_YBED, "void", variablen, false);
                zeile_klartext += param_to_klartext(zeile, SPIEGELN_BEZ, "void", variablen, false);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_LAGE_AENDERN))
        {
            QString tmp;
            tmp = text_mitte(zeile, LAGE_AENDERN_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_LAGE_AENDERN;
                zeile_klartext += param_to_klartext(zeile, LAGE_AENDERN_XALT, VAR_LAGE_AENDERN_XALT, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LAGE_AENDERN_YALT, VAR_LAGE_AENDERN_YALT, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LAGE_AENDERN_XNEU, VAR_LAGE_AENDERN_XNEU, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LAGE_AENDERN_YNEU, VAR_LAGE_AENDERN_YNEU, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LAGE_AENDERN_DREHWI, VAR_LAGE_AENDERN_DREHWI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LAGE_AENDERN_KETTENMAS, VAR_LAGE_AENDERN_KETTENMAS, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LAGE_AENDERN_GESWI, VAR_LAGE_AENDERN_GESWI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LAGE_AENDERN_BEZ, "void", variablen, false);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_BO))
        {
            QString tmp;
            tmp = text_mitte(zeile, BO_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_BO;
                zeile_klartext += param_to_klartext(zeile, BO_X, VAR_BO_X, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_Y, VAR_BO_Y, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_BOTI, VAR_BO_BOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_DM, VAR_BO_DM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_GRUPPE, VAR_BO_GRUPPE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_ANBOTI, VAR_BO_ANBOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_ANBOVO, VAR_BO_ANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_REBOMA, VAR_BO_REBOMA, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_BOVO, VAR_BO_BOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_ZSM, VAR_BO_ZSM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_DREHZ, VAR_BO_DREHZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_MESSEI, VAR_BO_MESSEI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_TASATZ, VAR_BO_TASATZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BO_PLM, VAR_BO_PLM, variablen, true);
                //BO_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_BOY))
        {
            QString tmp;
            tmp = text_mitte(zeile, BOY_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_BOY;
                zeile_klartext += param_to_klartext(zeile, BOY_X, VAR_BOY_X, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_X2, VAR_BOY_X2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_Y1, VAR_BOY_Y1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_Y2, VAR_BOY_Y2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_Y3, VAR_BOY_Y3, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_Y4, VAR_BOY_Y4, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_Y5, VAR_BOY_Y5, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_Y6, VAR_BOY_Y6, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_BOTI, VAR_BOY_BOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_DM, VAR_BOY_DM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_KETTE, VAR_BOY_KETTE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_GRUPPE, VAR_BOY_GRUPPE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_ANBOTI, VAR_BOY_ANBOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_ANBOVO, VAR_BOY_ANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_REBOMA, VAR_BOY_REBOMA, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_BOVO, VAR_BOY_BOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_ZSM, VAR_BOY_ZSM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_DREHZ, VAR_BOY_DREHZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_MESSEI, VAR_BOY_MESSEI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_TASATZ, VAR_BOY_TASATZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOY_PLM, VAR_BOY_PLM, variablen, true);
                //BO_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_BOX))
        {
            QString tmp;
            tmp = text_mitte(zeile, BOX_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_BOX;
                zeile_klartext += param_to_klartext(zeile, BOX_Y, VAR_BOX_Y, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_Y2, VAR_BOX_Y2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_X1, VAR_BOX_X1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_X2, VAR_BOX_X2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_X3, VAR_BOX_X3, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_X4, VAR_BOX_X4, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_X5, VAR_BOX_X5, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_X6, VAR_BOX_X6, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_BOTI, VAR_BOX_BOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_DM, VAR_BOX_DM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_KETTE, VAR_BOX_KETTE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_GRUPPE, VAR_BOX_GRUPPE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_ANBOTI, VAR_BOX_ANBOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_ANBOVO, VAR_BOX_ANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_REBOMA, VAR_BOX_REBOMA, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_BOVO, VAR_BOX_BOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_ZSM, VAR_BOX_ZSM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_DREHZ, VAR_BOX_DREHZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_MESSEI, VAR_BOX_MESSEI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_TASATZ, VAR_BOX_TASATZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, BOX_PLM, VAR_BOX_PLM, variablen, true);
                //BO_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_LOREIAE))
        {
            QString tmp;
            tmp = text_mitte(zeile, LOREIAE_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_LOREIAE;
                zeile_klartext += param_to_klartext(zeile, LOREIAE_XS, VAR_LOREIAE_XS, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_XE, VAR_LOREIAE_XE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_Y1, VAR_LOREIAE_Y1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_Y2, VAR_LOREIAE_Y2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_YE, VAR_LOREIAE_YE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_RASTER, VAR_LOREIAE_RASTER, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_BOTI, VAR_LOREIAE_BOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_DM, VAR_LOREIAE_DM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_GRUPPE, VAR_LOREIAE_GRUPPE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_VERMIT, VAR_LOREIAE_VERMIT, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_ANBOTI, VAR_LOREIAE_ANBOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_ANBOVO, VAR_LOREIAE_ANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_REBOMA, VAR_LOREIAE_REBOMA, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_BOVO, VAR_LOREIAE_BOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_ZSM, VAR_LOREIAE_ZSM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_DREHZ, VAR_LOREIAE_DREHZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_MESSEI, VAR_LOREIAE_MESSEI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_TASATZ, VAR_LOREIAE_TASATZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIAE_PLM, VAR_LOREIAE_PLM, variablen, true);
                //BO_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_LOREIMA))
        {
            QString tmp;
            tmp = text_mitte(zeile, LOREIMA_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_LOREIMA;
                zeile_klartext += param_to_klartext(zeile, LOREIMA_XM, VAR_LOREIMA_XM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_XS, VAR_LOREIMA_XS, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_Y1, VAR_LOREIMA_Y1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_Y2, VAR_LOREIMA_Y2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_RASTER, VAR_LOREIMA_RASTER, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_BOTI, VAR_LOREIMA_BOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_DM, VAR_LOREIMA_DM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_GRUPPE, VAR_LOREIMA_GRUPPE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_ANBOTI, VAR_LOREIMA_ANBOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_ANBOVO, VAR_LOREIMA_ANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_REBOMA, VAR_LOREIMA_REBOMA, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_BOVO, VAR_LOREIMA_BOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_ZSM, VAR_LOREIMA_ZSM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_DREHZ, VAR_LOREIMA_DREHZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_MESSEI, VAR_LOREIMA_MESSEI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_TASATZ, VAR_LOREIMA_TASATZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, LOREIMA_PLM, VAR_LOREIMA_PLM, variablen, true);
                //BO_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_TOPF))
        {
            QString tmp;
            tmp = text_mitte(zeile, TOPF_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_TOPF;
                zeile_klartext += param_to_klartext(zeile, TOPF_TA, VAR_TOPF_TA, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_A1, VAR_TOPF_A1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_A2, VAR_TOPF_A2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_A3, VAR_TOPF_A3, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_A4, VAR_TOPF_A4, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_A5, VAR_TOPF_A5, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_MA, VAR_TOPF_MA, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_MB, VAR_TOPF_MB, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_KETTE, VAR_TOPF_KETTE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_GRUPPE, VAR_TOPF_GRUPPE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_SEITE, VAR_TOPF_SEITE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_MESSEI, VAR_TOPF_MESSEI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_BODM, VAR_TOPF_BODM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_TODM, VAR_TOPF_TODM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_BOTI, VAR_TOPF_BOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_WKZ, VAR_TOPF_WKZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_TOTI, VAR_TOPF_TOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_ANBOTI, VAR_TOPF_ANBOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_BOANBOVO, VAR_TOPF_BOANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_TOANBOVO, VAR_TOPF_TOANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_REBOMA, VAR_TOPF_REBOMA, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_BOBOVO, VAR_TOPF_BOBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_TOBOVO, VAR_TOPF_TOBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_BOZSM, VAR_TOPF_BOZSM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_DREHZ, VAR_TOPF_DREHZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, TOPF_PLM, VAR_TOPF_PLM, variablen, true);
                //BO_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_HBEXP))
        {
            QString tmp;
            tmp = text_mitte(zeile, HBEXP_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_HBEXP;
                zeile_klartext += param_to_klartext(zeile, HBEXP_Y1, VAR_HBEXP_Y1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_Y2, VAR_HBEXP_Y2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_Y3, VAR_HBEXP_Y3, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_Y4, VAR_HBEXP_Y4, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_Y5, VAR_HBEXP_Y5, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_Y6, VAR_HBEXP_Y6, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_BOTI, VAR_HBEXP_BOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_Z, VAR_HBEXP_Z, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_DM, VAR_HBEXP_DM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_KETTE, VAR_HBEXP_KETTE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_GRUPPE, VAR_HBEXP_GRUPPE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_X2, VAR_HBEXP_X2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_X1, VAR_HBEXP_X1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_ANBOTI, VAR_HBEXP_ANBOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_ANBOVO, VAR_HBEXP_ANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_BOVO, VAR_HBEXP_BOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXP_DREHZ, VAR_HBEXP_DREHZ, variablen, true);
                //HBEXP_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_HBEXM))
        {
            QString tmp;
            tmp = text_mitte(zeile, HBEXM_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_HBEXM;
                zeile_klartext += param_to_klartext(zeile, HBEXM_Y1, VAR_HBEXM_Y1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_Y2, VAR_HBEXM_Y2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_Y3, VAR_HBEXM_Y3, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_Y4, VAR_HBEXM_Y4, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_Y5, VAR_HBEXM_Y5, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_Y6, VAR_HBEXM_Y6, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_BOTI, VAR_HBEXM_BOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_Z, VAR_HBEXM_Z, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_DM, VAR_HBEXM_DM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_KETTE, VAR_HBEXM_KETTE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_GRUPPE, VAR_HBEXM_GRUPPE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_X2, VAR_HBEXM_X2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_X1, VAR_HBEXM_X1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_ANBOTI, VAR_HBEXM_ANBOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_ANBOVO, VAR_HBEXM_ANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_BOVO, VAR_HBEXM_BOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEXM_DREHZ, VAR_HBEXM_DREHZ, variablen, true);
                //HBEXP_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_HBEYP))
        {
            QString tmp;
            tmp = text_mitte(zeile, HBEYP_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_HBEYP;
                zeile_klartext += param_to_klartext(zeile, HBEYP_X1, VAR_HBEYP_X1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_X2, VAR_HBEYP_X2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_X3, VAR_HBEYP_X3, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_X4, VAR_HBEYP_X4, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_X5, VAR_HBEYP_X5, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_X6, VAR_HBEYP_X6, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_BOTI, VAR_HBEYP_BOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_Z, VAR_HBEYP_Z, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_DM, VAR_HBEYP_DM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_KETTE, VAR_HBEYP_KETTE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_GRUPPE, VAR_HBEYP_GRUPPE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_Y2, VAR_HBEYP_Y2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_Y1, VAR_HBEYP_Y1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_ANBOTI, VAR_HBEYP_ANBOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_ANBOVO, VAR_HBEYP_ANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_BOVO, VAR_HBEYP_BOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYP_DREHZ, VAR_HBEYP_DREHZ, variablen, true);
                //HBEXP_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_HBEYM))
        {
            QString tmp;
            tmp = text_mitte(zeile, HBEYM_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_HBEYM;
                zeile_klartext += param_to_klartext(zeile, HBEYM_X1, VAR_HBEYM_X1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_X2, VAR_HBEYM_X2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_X3, VAR_HBEYM_X3, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_X4, VAR_HBEYM_X4, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_X5, VAR_HBEYM_X5, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_X6, VAR_HBEYM_X6, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_BOTI, VAR_HBEYM_BOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_Z, VAR_HBEYM_Z, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_DM, VAR_HBEYM_DM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_KETTE, VAR_HBEYM_KETTE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_GRUPPE, VAR_HBEYM_GRUPPE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_Y2, VAR_HBEYM_Y2, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_Y1, VAR_HBEYM_Y1, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_ANBOTI, VAR_HBEYM_ANBOTI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_ANBOVO, VAR_HBEYM_ANBOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_BOVO, VAR_HBEYM_BOVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, HBEYM_DREHZ, VAR_HBEYM_DREHZ, variablen, true);
                //HBEXP_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_NUT))
        {
            QString tmp;
            tmp = text_mitte(zeile, NUT_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_NUT;
                zeile_klartext += param_to_klartext(zeile, NUT_WKZ, "void", variablen, false);
                zeile_klartext += param_to_klartext(zeile, NUT_SX, VAR_NUT_SX, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_SY, VAR_NUT_SY, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_EX, VAR_NUT_EX, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_EY, VAR_NUT_EY, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_TI, VAR_NUT_TI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_B, VAR_NUT_B, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_AUSLAUF, VAR_NUT_AUSLAUF, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_KOR, VAR_NUT_KOR, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_GEGENLAUF, VAR_NUT_GEGENLAUF, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_NWI, VAR_NUT_NWI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_NTYP, VAR_NUT_NTYP, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_NABST, VAR_NUT_NABST, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_Z, VAR_NUT_Z, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_EINVO, VAR_NUT_EINVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_VO, VAR_NUT_VO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_DREHZ, VAR_NUT_DREHZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, NUT_PLM, VAR_NUT_PLM, variablen, true);
                //NUT_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_KTA))
        {
            QString tmp;
            tmp = text_mitte(zeile, KTA_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_KTA;
                zeile_klartext += param_to_klartext_orginal(zeile, KTA_WKZ);
                zeile_klartext += param_to_klartext(zeile, KTA_X, VAR_KTA_X, variablen, true);
                zeile_klartext += param_to_klartext(zeile, KTA_Y, VAR_KTA_Y, variablen, true);
                zeile_klartext += param_to_klartext(zeile, KTA_DM, VAR_KTA_DM, variablen, true);
                zeile_klartext += param_to_klartext(zeile, KTA_TI, VAR_KTA_TI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, KTA_ZUST, VAR_KTA_ZUST, variablen, true);
                zeile_klartext += param_to_klartext(zeile, KTA_GEGENL, VAR_KTA_GEGENL, variablen, true);
                zeile_klartext += param_to_klartext(zeile, KTA_AUSR, VAR_KTA_AUSR, variablen, true);
                zeile_klartext += param_to_klartext(zeile, KTA_EINVO, VAR_KTA_EINVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, KTA_VO, VAR_KTA_VO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, KTA_DREHZ, VAR_KTA_DREHZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, KTA_PLM, VAR_KTA_PLM, variablen, true);
                //NUT_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_RTA))
        {
            QString tmp;
            tmp = text_mitte(zeile, RTA_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_RTA;
                zeile_klartext += param_to_klartext_orginal(zeile, RTA_WKZ);
                zeile_klartext += param_to_klartext(zeile, RTA_X, VAR_RTA_X, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_Y, VAR_RTA_Y, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_L, VAR_RTA_L, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_B, VAR_RTA_B, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_TI, VAR_RTA_TI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_RAD, VAR_RTA_RAD, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_ZUST, VAR_RTA_ZUST, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_GEGENL, VAR_RTA_GEGENL, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_WI, VAR_RTA_WI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_AUSR, VAR_RTA_AUSR, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_EINVO, VAR_RTA_EINVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_VO, VAR_RTA_VO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_DREHZ, VAR_RTA_DREHZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, RTA_PLM, VAR_RTA_PLM, variablen, true);
                //NUT_BEZ

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_VAR))
        {
            QString tmp;
            tmp = text_mitte(zeile, VAR_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_VAR;
                zeile_klartext += var_to_klartext(zeile, VAR_NAME, VAR_WERT, variablen);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_VAR10))
        {
            QString tmp;
            tmp = text_mitte(zeile, VAR10_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_VAR10;
                zeile_klartext += var_to_klartext(zeile, VAR10_NAME1, VAR10_WERT1, variablen);
                zeile_klartext += var_to_klartext(zeile, VAR10_NAME2, VAR10_WERT2, variablen);
                zeile_klartext += var_to_klartext(zeile, VAR10_NAME3, VAR10_WERT3, variablen);
                zeile_klartext += var_to_klartext(zeile, VAR10_NAME4, VAR10_WERT4, variablen);
                zeile_klartext += var_to_klartext(zeile, VAR10_NAME5, VAR10_WERT5, variablen);
                zeile_klartext += var_to_klartext(zeile, VAR10_NAME6, VAR10_WERT6, variablen);
                zeile_klartext += var_to_klartext(zeile, VAR10_NAME7, VAR10_WERT7, variablen);
                zeile_klartext += var_to_klartext(zeile, VAR10_NAME8, VAR10_WERT8, variablen);
                zeile_klartext += var_to_klartext(zeile, VAR10_NAME9, VAR10_WERT9, variablen);
                zeile_klartext += var_to_klartext(zeile, VAR10_NAME10, VAR10_WERT10, variablen);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_FAUF))
        {
            QString tmp;
            tmp = text_mitte(zeile, FAUF_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);

            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_FAUF;
                zeile_klartext += param_to_klartext_orginal(zeile, FAUF_WKZ);
                //--------------------------------------------------------------------
                QString wkzname = text_mitte(zeile, FAUF_WKZ, ENDPAR);
                text_zeilenweise wtz;
                wtz = Wkz.wkzlist(WKZ_FRAESER);
                for(uint i=1; i<=wtz.zeilenanzahl() ;i++)
                {
                    QString aktname = text_mitte(wtz.zeile(i), FRAESER_NAME, ENDPAR);
                    if(aktname == wkzname)
                    {
                        wkzdm = text_mitte(wtz.zeile(i), FRAESER_DM, ENDPAR);
                    }
                }
                zeile_klartext += var_to_klartext(VAR_ALLGEM_WKZDM, wkzdm);
                //WKZR in Variablenliste ergänzen:
                var_ergaenzen(variablen, "[WKZR]", double_to_qstring(wkzdm.toDouble()/2));
                //--------------------------------------------------------------------
                             x = param_to_klartext(zeile, FAUF_X, VAR_FAUF_X, variablen, true);
                zeile_klartext += x;
                             x = text_mitte(x, FAUF_X, ENDPAR);
                             y = param_to_klartext(zeile, FAUF_Y, VAR_FAUF_Y, variablen, true);
                zeile_klartext += y;
                             y = text_mitte(y, FAUF_Y, ENDPAR);
                zeile_klartext += var_to_klartext(VAR_FGERADE_Y, y);
                             z = param_to_klartext(zeile, FAUF_Z, VAR_FAUF_Z, variablen, true);
                zeile_klartext += z;
                             z = text_mitte(z, FAUF_Z, ENDPAR);
                zeile_klartext += var_to_klartext(VAR_FGERADE_Z, z);
                zeile_klartext += param_to_klartext(zeile, FAUF_ERG, VAR_FAUF_ERG, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_KADI, VAR_FAUF_KADI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_KOR, VAR_FAUF_KOR, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_ANTYP, VAR_FAUF_ANTYP, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_ABTYP, VAR_FAUF_ABTYP, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_EINTYP, VAR_FAUF_EINTYP, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_ANWEG, VAR_FAUF_ANWEG, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_ABWEG, VAR_FAUF_ABWEG, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_ANVO, VAR_FAUF_ANVO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_VO, VAR_FAUF_VO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_DREHZ, VAR_FAUF_DREHZ, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FAUF_EVERS, VAR_FAUF_EVERS, variablen, true);


                wkzkor = text_mitte(zeile, FAUF_KOR, ENDPAR);

                var_ergaenzen(variablen, VAR_ALLGEM_X, x);
                var_ergaenzen(variablen, VAR_ALLGEM_Y, y);
                var_ergaenzen(variablen, VAR_ALLGEM_Z, z);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_FABF))
        {
            QString tmp;
            tmp = text_mitte(zeile, FABF_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString zeile_klartext;
                zeile_klartext += DLG_FABF;
                zeile_klartext += var_to_klartext(VAR_ALLGEM_XS, x);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_YS, y);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_ZS, z);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_WKZKOR, wkzkor);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_FGERADE))
        {
            QString tmp;
            tmp = text_mitte(zeile, FGERADE_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString xs = x;
                QString ys = y;
                QString zs = z;

                QString zeile_klartext;
                zeile_klartext += DLG_FGERADE;
                             x = param_to_klartext(zeile, FGERADE_X, VAR_FGERADE_X, variablen, true);
                zeile_klartext += x;
                             x = text_mitte(x, FGERADE_X, ENDPAR);
                             y = param_to_klartext(zeile, FGERADE_Y, VAR_FGERADE_Y, variablen, true);
                zeile_klartext += y;
                             y = text_mitte(y, FGERADE_Y, ENDPAR);
                             z = param_to_klartext(zeile, FGERADE_Z, VAR_FGERADE_Z, variablen, true);
                zeile_klartext += z;
                             z = text_mitte(z, FGERADE_Z, ENDPAR);
                zeile_klartext += param_to_klartext(zeile, FGERADE_RAD, VAR_FGERADE_RAD, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FGERADE_VO, VAR_FGERADE_VO, variablen, true);

                zeile_klartext += var_to_klartext(VAR_ALLGEM_XS, xs);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_YS, ys);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_ZS, zs);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_XE, x);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_YE, y);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_ZE, z);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_WKZDM, wkzdm);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_WKZKOR, wkzkor);
                var_ergaenzen(variablen, VAR_ALLGEM_X, x);
                var_ergaenzen(variablen, VAR_ALLGEM_Y, y);
                var_ergaenzen(variablen, VAR_ALLGEM_Z, z);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_FGERAWI))
        {
            QString tmp;
            tmp = text_mitte(zeile, FGERAWI_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString xs = x;
                QString ys = y;
                QString zs = z;
                QString l;
                QString wi;
                strecke s;
                punkt3d sp;
                sp.set_x(x);
                sp.set_y(y);
                sp.set_z(z);

                QString zeile_klartext;
                zeile_klartext += DLG_FGERAWI;
                             wi = param_to_klartext(zeile, FGERAWI_WI, VAR_FGERAWI_WI, variablen, true);
                zeile_klartext += wi;
                             wi = text_mitte(wi, FGERAWI_WI, ENDPAR);
                             l = param_to_klartext(zeile, FGERAWI_L, VAR_FGERAWI_L, variablen, true);
                zeile_klartext += l;
                             l = text_mitte(l, FGERAWI_L, ENDPAR);
                             z = param_to_klartext(zeile, FGERAWI_Z, VAR_FGERAWI_Z, variablen, true);
                zeile_klartext += z;
                             z = text_mitte(z, FGERAWI_Z, ENDPAR);
                zeile_klartext += param_to_klartext(zeile, FGERAWI_RAD, VAR_FGERAWI_RAD, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FGERAWI_VO, VAR_FGERAWI_VO, variablen, true);

                punkt3d ep;
                ep.set_x(x.toDouble() + l.toDouble());
                ep.set_y(y);
                ep.set_z(z);
                s.set_start(sp);
                s.set_ende(ep);
                s.drenen_um_startpunkt_2d(wi.toDouble(), false);

                x = s.endpu().x_QString();
                y = s.endpu().y_QString();

                zeile_klartext += var_to_klartext(VAR_ALLGEM_XS, xs);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_YS, ys);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_ZS, zs);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_XE, x);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_YE, y);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_ZE, z);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_WKZDM, wkzdm);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_WKZKOR, wkzkor);
                var_ergaenzen(variablen, VAR_ALLGEM_X, x);
                var_ergaenzen(variablen, VAR_ALLGEM_Y, y);
                var_ergaenzen(variablen, VAR_ALLGEM_Z, z);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_FBOUZS))
        {
            QString tmp;
            tmp = text_mitte(zeile, FBOUZS_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString xs = x;
                QString ys = y;
                QString zs = z;

                QString zeile_klartext;
                zeile_klartext += DLG_FBOUZS;
                             x = param_to_klartext(zeile, FBOUZS_XE, VAR_FBOUZS_XE, variablen, true);
                zeile_klartext += x;
                             x = text_mitte(x, FBOUZS_XE, ENDPAR);
                             y = param_to_klartext(zeile, FBOUZS_YE, VAR_FBOUZS_YE, variablen, true);
                zeile_klartext += y;
                             y = text_mitte(y, FBOUZS_YE, ENDPAR);
                             z = param_to_klartext(zeile, FBOUZS_ZE, VAR_FBOUZS_ZE, variablen, true);
                zeile_klartext += z;
                             z = text_mitte(z, FBOUZS_ZE, ENDPAR);
                zeile_klartext += param_to_klartext(zeile, FBOUZS_XMI, VAR_FBOUZS_XMI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FBOUZS_YMI, VAR_FBOUZS_YMI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FBOUZS_RADBO, VAR_FBOUZS_RADBO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FBOUZS_RADECKE, VAR_FBOUZS_RADECKE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FBOUZS_VO, VAR_FBOUZS_VO, variablen, true);

                zeile_klartext += var_to_klartext(VAR_ALLGEM_XS, xs);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_YS, ys);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_ZS, zs);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_XE, x);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_YE, y);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_ZE, z);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_WKZDM, wkzdm);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_WKZKOR, wkzkor);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_FBOGUZS))
        {
            QString tmp;
            tmp = text_mitte(zeile, FBOGUZS_AFB, ENDPAR);
            tmp = variablen_durch_werte_ersetzten(variablen, tmp);//Variablen durch Werte ersetzen
            tmp = ausdruck_auswerten(tmp);
            if(tmp.toFloat() == true)
            {
                QString xs = x;
                QString ys = y;
                QString zs = z;

                QString zeile_klartext;
                zeile_klartext += DLG_FBOGUZS;
                             x = param_to_klartext(zeile, FBOGUZS_XE, VAR_FBOGUZS_XE, variablen, true);
                zeile_klartext += x;
                             x = text_mitte(x, FBOGUZS_XE, ENDPAR);
                             y = param_to_klartext(zeile, FBOGUZS_YE, VAR_FBOGUZS_YE, variablen, true);
                zeile_klartext += y;
                             y = text_mitte(y, FBOGUZS_YE, ENDPAR);
                             z = param_to_klartext(zeile, FBOGUZS_ZE, VAR_FBOGUZS_ZE, variablen, true);
                zeile_klartext += z;
                             z = text_mitte(z, FBOGUZS_ZE, ENDPAR);
                zeile_klartext += param_to_klartext(zeile, FBOGUZS_XMI, VAR_FBOGUZS_XMI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FBOGUZS_YMI, VAR_FBOGUZS_YMI, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FBOGUZS_RADBO, VAR_FBOGUZS_RADBO, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FBOGUZS_RADECKE, VAR_FBOGUZS_RADECKE, variablen, true);
                zeile_klartext += param_to_klartext(zeile, FBOGUZS_VO, VAR_FBOGUZS_VO, variablen, true);

                zeile_klartext += var_to_klartext(VAR_ALLGEM_XS, xs);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_YS, ys);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_ZS, zs);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_XE, x);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_YE, y);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_ZE, z);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_WKZDM, wkzdm);
                zeile_klartext += var_to_klartext(VAR_ALLGEM_WKZKOR, wkzkor);

                Klartext.zeilen_anhaengen(zeile_klartext);
                Var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                Klartext.zeilen_anhaengen(" ");//leere Zeile
                Var.zeile_anhaengen(variablen);
            }
        }else
        {
            Klartext.zeilen_anhaengen(" ");//leere Zeile
            Var.zeile_anhaengen(variablen);
        }
    }
}
void programmtext::aktualisiere_geo()
{
    //Variablen für Spiegeln:
    bool spiegeln_xbed = false;
    bool spiegeln_ybed = false;
    double spiegeln_xpos = 0;
    double spiegeln_ypos = 0;
    //Variablen für Lage ändern:
    bool lageaendern_afb = false;
    double lageaendern_xalt = 0;
    double lageaendern_yalt = 0;
    double lageaendern_xneu = 0;
    double lageaendern_yneu = 0;
    double lageaendern_wi = 0;
    double lageaendern_geswi = 0;
    bool lageaendern_kettenmas = false;
    double lageaendern_xalt_alt = 0;
    double lageaendern_yalt_alt = 0;
    double lageaendern_xneu_alt = 0;
    double lageaendern_yneu_alt = 0;
    double lageaendern_wi_alt = 0;
    double lageaendern_geswi_alt = 0;
    //Variabeln für Kantendarstellung:
    punkt3d nullpunkt_ob;
    punkt3d nullpunkt_un;
    punkt3d nullpunkt_li;
    punkt3d nullpunkt_re;
    nullpunkt_ob.set_linienbreite(10);
    nullpunkt_un.set_linienbreite(10);
    nullpunkt_li.set_linienbreite(10);
    nullpunkt_re.set_linienbreite(10);
    punkt3d nullpunkt_wst;
    nullpunkt_wst.set_x(ax());
    nullpunkt_wst.set_y(ay());
    //Variabelen für Abfahren Fräser:
    QString abtyp;
    QString abwert;
    double wkzrad;
    QString radiuskor;

    if(!Aktualisieren_eingeschaltet)
    {
        return;
    }
    //Die Funktion "aktualisiere_klartext_var()" muss jeweils vorab aufgerufen worden sein!

    //CAD-Parameter ergänzen:
    if(Warnung_frDial == false)
    {
        //QString abtyp = NICHT_DEFINIERT; //brauchen wir an dieser Stelle, damit der Wert später
                                         //beim Fräser-Abfahren verfügbar ist
        //float fdm=0;                     //Fräser-Durchmesser
        bool kantenansicht = false;
        //float kantenabst = 20;

        for(uint i=1 ; i<=Klartext.zeilenanzahl() ; i++)
        {
            QString zeile = Klartext.zeile(i), tmp;

            if(zeile.isEmpty())
            {
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_PKOPF))
            {
                punkt3d nullpunkt(0,0,0);
                nullpunkt.set_linienbreite(15);
                Geo.add_punkt(nullpunkt);

                rechteck3d rec;
                rec.set_bezugspunkt(UNTEN_LINKS);
                rec.set_einfuegepunkt(Versatz_x,Versatz_y,0);
                rec.set_laenge(werkstuecklaenge());
                rec.set_breite(werkstueckbreite());
                rec.set_farbe_fuellung(FARBE_GRAU);
                Geo.add_rechteck(rec);

                //WST-Kanten anzeigen lassen:
                QString fuenfseiten = text_mitte(zeile, PKOPF_FUENFSEI, ENDPAR);
                if(fuenfseiten == "1")
                {
                    kantenansicht = true;
                    double abst = 20;
                    //Kante unten:
                    if(ay() >= 0)
                    {
                        nullpunkt_un.set_x(ax());
                        nullpunkt_un.set_y(0 - abst);
                    }else
                    {
                        nullpunkt_un.set_x(ax());
                        nullpunkt_un.set_y(0 - abst + ay());//+ay weil es ja dann +-ay ist
                    }
                    Geo.add_punkt(nullpunkt_un);
                    rec.set_bezugspunkt(OBEN_LINKS);
                    rec.set_einfuegepunkt(nullpunkt_un);
                    rec.set_breite(werkstueckdicke());
                    Geo.add_rechteck(rec);

                    //Kante oben:
                    if(ay() <= 0)
                    {
                        nullpunkt_ob.set_x(ax());
                        nullpunkt_ob.set_y(abst + werkstueckbreite());
                    }else
                    {
                        nullpunkt_ob.set_x(ax());
                        nullpunkt_ob.set_y(abst + werkstueckbreite() + Versatz_y);
                    }
                    Geo.add_punkt(nullpunkt_ob);
                    rec.set_bezugspunkt(UNTEN_LINKS);
                    rec.set_einfuegepunkt(nullpunkt_ob);
                    Geo.add_rechteck(rec);

                    //Kante_links:
                    if(ax() >= 0)
                    {
                        nullpunkt_li.set_x(0 - abst);
                        nullpunkt_li.set_y(ay());
                    }else
                    {
                        nullpunkt_li.set_x(0 - abst + ax());//+ax weil es ja dann +-ax ist
                        nullpunkt_li.set_y(ay());
                    }
                    Geo.add_punkt(nullpunkt_li);
                    rec.set_bezugspunkt(UNTEN_RECHTS);
                    rec.set_einfuegepunkt(nullpunkt_li);
                    rec.set_laenge(werkstueckdicke());
                    rec.set_breite(werkstueckbreite());
                    Geo.add_rechteck(rec);

                    //Kante_rechts:
                    if(ax() <=0)
                    {
                        nullpunkt_re.set_x(abst + werkstuecklaenge());
                        nullpunkt_re.set_y(ay());
                    }else
                    {
                        nullpunkt_re.set_x(abst + werkstuecklaenge() + ax());
                        nullpunkt_re.set_y(ay());
                    }
                    Geo.add_punkt(nullpunkt_re);
                    rec.set_bezugspunkt(UNTEN_LINKS);
                    rec.set_einfuegepunkt(nullpunkt_re);
                    Geo.add_rechteck(rec);
                }

                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_PENDE))
            {
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_KOM))
            {
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_HALT))
            {
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_SPIEGELN))
            {
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
                QString tmp;
                tmp = text_mitte(zeile, SPIEGELN_XBED, ENDPAR);
                if(tmp.toDouble() == 0)
                {
                    spiegeln_xbed = false;
                }else
                {
                    spiegeln_xbed = true;
                    spiegeln_xpos = text_mitte(zeile, SPIEGELN_XPOS, ENDPAR).toDouble();
                }
                tmp = text_mitte(zeile, SPIEGELN_YBED, ENDPAR);
                if(tmp.toDouble() == 0)
                {
                    spiegeln_ybed = false;
                }else
                {
                    spiegeln_ybed = true;
                    spiegeln_ypos = text_mitte(zeile, SPIEGELN_YPOS, ENDPAR).toDouble();
                }

            }else if(zeile.contains(DLG_LAGE_AENDERN))
            {
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();

                lageaendern_xalt_alt    = lageaendern_xalt;
                lageaendern_yalt_alt    = lageaendern_yalt;
                lageaendern_xneu_alt    = lageaendern_xneu;
                lageaendern_yneu_alt    = lageaendern_yneu;
                lageaendern_wi_alt      = lageaendern_wi;
                lageaendern_geswi_alt   = lageaendern_geswi;

                lageaendern_afb = true;
                lageaendern_xalt = text_mitte(zeile, LAGE_AENDERN_XALT, ENDPAR).toDouble();
                lageaendern_yalt = text_mitte(zeile, LAGE_AENDERN_YALT, ENDPAR).toDouble();
                lageaendern_xneu = text_mitte(zeile, LAGE_AENDERN_XNEU, ENDPAR).toDouble();
                lageaendern_yneu = text_mitte(zeile, LAGE_AENDERN_YNEU, ENDPAR).toDouble();
                lageaendern_wi = text_mitte(zeile, LAGE_AENDERN_DREHWI, ENDPAR).toDouble();
                lageaendern_geswi = text_mitte(zeile, LAGE_AENDERN_GESWI, ENDPAR).toDouble();
                QString tmp;
                tmp = text_mitte(zeile, LAGE_AENDERN_KETTENMAS, ENDPAR);
                if(tmp.toDouble() == 0)
                {
                    lageaendern_kettenmas = false;
                }else
                {
                    lageaendern_kettenmas = true;
                }

            }else if(zeile.contains(DLG_BO))
            {
                punkt3d mipu;
                mipu.set_x(text_mitte(zeile, BO_X, ENDPAR));
                mipu.set_y(text_mitte(zeile, BO_Y, ENDPAR));
                mipu.set_z(0);

                float boti = text_mitte(zeile, BO_BOTI, ENDPAR).toFloat();

                kreis k;
                k.set_farbe(FARBE_SCHWARZ);
                if(boti<=0 || boti > werkstueckdicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                k.set_stil(STIL_DURCHGEHEND);

                k.set_mittelpunkt(mipu);
                k.set_radius(text_mitte(zeile, BO_DM, ENDPAR).toDouble()/2);

                k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                k = lageaendern_kreis(k, lageaendern_afb,\
                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                Geo.add_kreis(k);
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_BOY))
            {
                kreis k;
                bool kette = false;
                if(text_mitte(zeile, BOY_KETTE, ENDPAR).toDouble() > 0)
                {
                    kette = true;
                }
                float boti = text_mitte(zeile, BOY_BOTI, ENDPAR).toFloat();
                k.set_radius(text_mitte(zeile, BOY_DM, ENDPAR).toDouble()/2);
                k.set_farbe(FARBE_SCHWARZ);
                if(boti<=0 || boti > werkstueckdicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_ROSE);
                }
                k.set_stil(STIL_DURCHGEHEND);

                double x1 = 0;
                double x2 = 0;
                double y1 = 0;
                double y2 = 0;
                double y3 = 0;
                double y4 = 0;
                double y5 = 0;
                double y6 = 0;
                x1 = text_mitte(zeile, BOY_X, ENDPAR).toDouble();
                x2 = text_mitte(zeile, BOY_X2, ENDPAR).toDouble();
                y1 = text_mitte(zeile, BOY_Y1, ENDPAR).toDouble();
                if(kette == true)
                {
                    y2 = y1 + text_mitte(zeile, BOY_Y2, ENDPAR).toDouble();
                    y3 = y2 + text_mitte(zeile, BOY_Y3, ENDPAR).toDouble();
                    y4 = y3 + text_mitte(zeile, BOY_Y4, ENDPAR).toDouble();
                    y5 = y4 + text_mitte(zeile, BOY_Y5, ENDPAR).toDouble();
                    y6 = y5 + text_mitte(zeile, BOY_Y6, ENDPAR).toDouble();
                }else
                {
                    y2 = text_mitte(zeile, BOY_Y2, ENDPAR).toDouble();
                    y3 = text_mitte(zeile, BOY_Y3, ENDPAR).toDouble();
                    y4 = text_mitte(zeile, BOY_Y4, ENDPAR).toDouble();
                    y5 = text_mitte(zeile, BOY_Y5, ENDPAR).toDouble();
                    y6 = text_mitte(zeile, BOY_Y6, ENDPAR).toDouble();
                }

                punkt3d p;

                p.set_x(x1);
                p.set_y(y1);
                k.set_mittelpunkt(p);
                k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                k = lageaendern_kreis(k, lageaendern_afb,\
                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                Geo.add_kreis(k);
                if(x2 > 0)
                {
                    p.set_x(x2);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                }
                if(y2 > 0)
                {
                    p.set_x(x1);
                    p.set_y(y2);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                    if(x2 >= 0)
                    {
                        p.set_x(x2);
                        k.set_mittelpunkt(p);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }
                if(y3 > 0)
                {
                    p.set_x(x1);
                    p.set_y(y3);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                    if(x2 >= 0)
                    {
                        p.set_x(x2);
                        k.set_mittelpunkt(p);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }
                if(y4 > 0)
                {
                    p.set_x(x1);
                    p.set_y(y4);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                    if(x2 >= 0)
                    {
                        p.set_x(x2);
                        k.set_mittelpunkt(p);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }
                if(y5 > 0)
                {
                    p.set_x(x1);
                    p.set_y(y5);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                    if(x2 >= 0)
                    {
                        p.set_x(x2);
                        k.set_mittelpunkt(p);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }
                if(y6 > 0)
                {
                    p.set_x(x1);
                    p.set_y(y6);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                    if(x2 >= 0)
                    {
                        p.set_x(x2);
                        k.set_mittelpunkt(p);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }

                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_BOX))
            {
                kreis k;
                bool kette = false;
                if(text_mitte(zeile, BOX_KETTE, ENDPAR).toDouble() > 0)
                {
                    kette = true;
                }
                float boti = text_mitte(zeile, BOX_BOTI, ENDPAR).toFloat();
                k.set_radius(text_mitte(zeile, BOX_DM, ENDPAR).toDouble()/2);
                k.set_farbe(FARBE_SCHWARZ);
                if(boti<=0 || boti > werkstueckdicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_ROSE);
                }
                k.set_stil(STIL_DURCHGEHEND);

                double y1 = 0;
                double y2 = 0;
                double x1 = 0;
                double x2 = 0;
                double x3 = 0;
                double x4 = 0;
                double x5 = 0;
                double x6 = 0;
                y1 = text_mitte(zeile, BOX_Y, ENDPAR).toDouble();
                y2 = text_mitte(zeile, BOX_Y2, ENDPAR).toDouble();
                x1 = text_mitte(zeile, BOX_X1, ENDPAR).toDouble();
                if(kette == true)
                {
                    x2 = x1 + text_mitte(zeile, BOX_X2, ENDPAR).toDouble();
                    x3 = x2 + text_mitte(zeile, BOX_X3, ENDPAR).toDouble();
                    x4 = x3 + text_mitte(zeile, BOX_X4, ENDPAR).toDouble();
                    x5 = x4 + text_mitte(zeile, BOX_X5, ENDPAR).toDouble();
                    x6 = x5 + text_mitte(zeile, BOX_X6, ENDPAR).toDouble();
                }else
                {
                    x2 = text_mitte(zeile, BOX_X2, ENDPAR).toDouble();
                    x3 = text_mitte(zeile, BOX_X3, ENDPAR).toDouble();
                    x4 = text_mitte(zeile, BOX_X4, ENDPAR).toDouble();
                    x5 = text_mitte(zeile, BOX_X5, ENDPAR).toDouble();
                    x6 = text_mitte(zeile, BOX_X6, ENDPAR).toDouble();
                }

                punkt3d p;

                p.set_y(y1);
                p.set_x(x1);
                k.set_mittelpunkt(p);
                k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                k = lageaendern_kreis(k, lageaendern_afb,\
                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                Geo.add_kreis(k);
                if(y2 > 0)
                {
                    p.set_y(y2);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                }
                if(x2 > 0)
                {
                    p.set_y(y1);
                    p.set_x(x2);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                    if(y2 >= 0)
                    {
                        p.set_y(y2);
                        k.set_mittelpunkt(p);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }
                if(x3 > 0)
                {
                    p.set_y(y1);
                    p.set_x(x3);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                    if(y2 >= 0)
                    {
                        p.set_y(y2);
                        k.set_mittelpunkt(p);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }
                if(x4 > 0)
                {
                    p.set_y(y1);
                    p.set_x(x4);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                    if(y2 >= 0)
                    {
                        p.set_y(y2);
                        k.set_mittelpunkt(p);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }
                if(x5 > 0)
                {
                    p.set_y(y1);
                    p.set_x(x5);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                    if(y2 >= 0)
                    {
                        p.set_y(y2);
                        k.set_mittelpunkt(p);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }
                if(x6 > 0)
                {
                    p.set_y(y1);
                    p.set_x(x6);
                    k.set_mittelpunkt(p);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);
                    if(y2 >= 0)
                    {
                        p.set_y(y2);
                        k.set_mittelpunkt(p);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }

                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_LOREIAE))
            {
                double xs = text_mitte(zeile, LOREIAE_XS, ENDPAR).toDouble();
                double xe = text_mitte(zeile, LOREIAE_XE, ENDPAR).toDouble();
                double y1 = text_mitte(zeile, LOREIAE_Y1, ENDPAR).toDouble();
                double y2 = text_mitte(zeile, LOREIAE_Y2, ENDPAR).toDouble();
                double ye = text_mitte(zeile, LOREIAE_YE, ENDPAR).toDouble();
                double raster = text_mitte(zeile, LOREIAE_RASTER, ENDPAR).toDouble();
                double boti = text_mitte(zeile, LOREIAE_BOTI, ENDPAR).toDouble();
                double vermit = text_mitte(zeile, LOREIAE_VERMIT, ENDPAR).toDouble();
                kreis k;
                k.set_radius(text_mitte(zeile, LOREIAE_DM, ENDPAR).toDouble()/2);
                k.set_farbe(FARBE_SCHWARZ);
                if(boti<=0 || boti > werkstueckdicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_GELB);
                }
                k.set_stil(STIL_DURCHGEHEND);
                double abst = xe-xs;
                int anz = (abst/raster);//Nachkommastellen werden abgeschnitten durch double zu int
                strecke s;
                punkt3d p;
                p.set_x(xs);
                p.set_y(y1);
                s.set_start(p);
                strecke_bezugspunkt sbezp;
                if(vermit > 0)//Option 1 oder 2(bewirkt das selbe scheinbar)
                {
                    sbezp = strecke_bezugspunkt_mitte;
                }else
                {
                    sbezp = strecke_bezugspunkt_start;
                }
                p.set_x(xe);
                p.set_y(ye);
                s.set_ende(p);
                s.set_laenge_2d(anz*raster ,sbezp);

                for(int i=0; i<=anz;i++)
                {
                    punkt3d mipu;
                    if(i==0)
                    {
                        mipu.set_x(s.stapu().x());
                        mipu.set_y(s.stapu().y());
                    }else
                    {
                        strecke stmp = s;
                        stmp.set_laenge_2d(i*raster, strecke_bezugspunkt_start);
                        mipu.set_x(stmp.endpu().x());
                        mipu.set_y(stmp.endpu().y());
                    }
                    k.set_mittelpunkt(mipu);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);

                    if(y2 > 0)
                    {
                        strecke slorei2 = s;
                        slorei2.verschieben_um(0, y2-y1);
                        if(i==0)
                        {
                            mipu.set_x(slorei2.stapu().x());
                            mipu.set_y(slorei2.stapu().y());
                        }else
                        {
                            strecke stmp = slorei2;
                            stmp.set_laenge_2d(i*raster, strecke_bezugspunkt_start);
                            mipu.set_x(stmp.endpu().x());
                            mipu.set_y(stmp.endpu().y());
                        }

                        k.set_mittelpunkt(mipu);
                        k.set_radius(text_mitte(zeile, LOREIMA_DM, ENDPAR).toDouble()/2);

                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_LOREIMA))
            {
                double xs = text_mitte(zeile, LOREIMA_XS, ENDPAR).toDouble();
                double xm = text_mitte(zeile, LOREIMA_XM, ENDPAR).toDouble();
                double y1 = text_mitte(zeile, LOREIMA_Y1, ENDPAR).toDouble();
                double y2 = text_mitte(zeile, LOREIMA_Y2, ENDPAR).toDouble();
                double raster = text_mitte(zeile, LOREIMA_RASTER, ENDPAR).toDouble();
                float boti = text_mitte(zeile, LOREIMA_BOTI, ENDPAR).toFloat();
                kreis k;
                k.set_radius(text_mitte(zeile, LOREIMA_DM, ENDPAR).toDouble()/2);
                k.set_farbe(FARBE_SCHWARZ);
                if(boti<=0 || boti > werkstueckdicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_GELB);
                }
                k.set_stil(STIL_DURCHGEHEND);
                double abst = xm-xs;
                int anz = (abst/raster)*2 + 1;//Nachkommastellen werden abgeschnitten durch double zu int

                for(int i=0; i<anz;i++)
                {
                    punkt3d mipu;
                    mipu.set_x(xm-((abst/raster)*raster)+(i*raster));
                    mipu.set_y(y1);
                    k.set_mittelpunkt(mipu);
                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                    Geo.add_kreis(k);

                    if(y2 >0)
                    {
                        mipu.set_x(xm-((abst/raster)*raster)+(i*raster));
                        mipu.set_y(y2);
                        k.set_mittelpunkt(mipu);
                        k.set_radius(text_mitte(zeile, LOREIMA_DM, ENDPAR).toDouble()/2);

                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);
                        Geo.add_kreis(k);
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_TOPF))
            {
                double ta = text_mitte(zeile, TOPF_TA, ENDPAR).toDouble();//Topfabstand von WST-Kante
                double a1 = text_mitte(zeile, TOPF_A1, ENDPAR).toDouble();
                double a2 = 0;
                double a3 = 0;
                double a4 = 0;
                double a5 = 0;
                double ma = text_mitte(zeile, TOPF_MA, ENDPAR).toDouble();//Abstand zischen den Bohrungen der Schrauben
                double mb = text_mitte(zeile, TOPF_MB, ENDPAR).toDouble();//Abstand zwischen BO und TO
                bool kette = false;
                if(text_mitte(zeile, TOPF_KETTE, ENDPAR).toDouble() > 0)
                {
                    kette = true;
                }
                int seite = text_mitte(zeile, TOPF_SEITE, ENDPAR).toInt();
                double bodm = text_mitte(zeile, TOPF_BODM, ENDPAR).toDouble();
                double todm = text_mitte(zeile, TOPF_TODM, ENDPAR).toDouble();
                float boti = text_mitte(zeile, TOPF_BOTI, ENDPAR).toFloat();
                float toti = text_mitte(zeile, TOPF_TOTI, ENDPAR).toFloat();
                kreis kbo1, kbo2;
                kbo1.set_radius(bodm/2);
                kbo1.set_farbe(FARBE_SCHWARZ);
                if(boti<=0 || boti > werkstueckdicke())
                {
                    kbo1.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    kbo1.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                kbo1.set_stil(STIL_DURCHGEHEND);
                kbo2 = kbo1;
                kreis kto;
                kto.set_radius(todm/2);
                kto.set_farbe(FARBE_SCHWARZ);
                if(toti<=0 || toti > werkstueckdicke())
                {
                    kto.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    kto.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                kto.set_stil(STIL_DURCHGEHEND);
                if(kette == true)
                {
                    a2 = a1 + text_mitte(zeile, TOPF_A2, ENDPAR).toDouble();
                    a3 = a2 + text_mitte(zeile, TOPF_A3, ENDPAR).toDouble();
                    a4 = a3 + text_mitte(zeile, TOPF_A4, ENDPAR).toDouble();
                    a5 = a4 + text_mitte(zeile, TOPF_A5, ENDPAR).toDouble();
                }else
                {
                    a2 = text_mitte(zeile, TOPF_A2, ENDPAR).toDouble();
                    a3 = text_mitte(zeile, TOPF_A3, ENDPAR).toDouble();
                    a4 = text_mitte(zeile, TOPF_A4, ENDPAR).toDouble();
                    a5 = text_mitte(zeile, TOPF_A5, ENDPAR).toDouble();
                }

                if(seite == 1)//unten
                {
                    punkt3d miputo, mipubo1, mipubo2;
                    miputo.set_y(ta);
                    mipubo1.set_y(ta+mb);
                    mipubo2.set_y(ta+mb);
                    for(uint i=1;i<=5;i++)
                    {
                        double abst = 0;
                        switch(i)
                        {
                            case 1:
                                abst = a1;
                                break;
                            case 2:
                                abst = a2;
                                break;
                            case 3:
                                abst = a3;
                                break;
                            case 4:
                                abst = a4;
                                break;
                            case 5:
                                abst = a5;
                                break;
                        }
                        if(abst == 0)
                        {
                            break;
                        }
                        miputo.set_x(abst);
                        mipubo1.set_x(abst-ma/2);
                        mipubo2.set_x(abst+ma/2);
                        kto.set_mittelpunkt(miputo);
                        kbo1.set_mittelpunkt(mipubo1);
                        kbo2.set_mittelpunkt(mipubo2);
                        kto = spiegeln_kreis(kto, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kbo1 = spiegeln_kreis(kbo1, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kbo2 = spiegeln_kreis(kbo2, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kto = lageaendern_kreis(kto, lageaendern_afb,\
                                                lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                lageaendern_wi_alt, lageaendern_geswi_alt);
                        kbo1 = lageaendern_kreis(kbo1, lageaendern_afb,\
                                                 lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                 lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                 lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                 lageaendern_wi_alt, lageaendern_geswi_alt);
                        kbo2 = lageaendern_kreis(kbo2, lageaendern_afb,\
                                                 lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                 lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                 lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                 lageaendern_wi_alt, lageaendern_geswi_alt);
                        kto.set_mittelpunkt(nullpunkt_wst.x() + kto.mitte3d().x(), nullpunkt_wst.y() + kto.mitte3d().y(),0);
                        kbo1.set_mittelpunkt(nullpunkt_wst.x() + kbo1.mitte3d().x(), nullpunkt_wst.y() + kbo1.mitte3d().y(),0);
                        kbo2.set_mittelpunkt(nullpunkt_wst.x() + kbo2.mitte3d().x(), nullpunkt_wst.y() + kbo2.mitte3d().y(),0);
                        Geo.add_kreis(kto);
                        Geo.add_kreis(kbo1);
                        Geo.add_kreis(kbo2);
                    }
                }else if(seite == 2)//rechts
                {
                    punkt3d miputo, mipubo1, mipubo2;
                    miputo.set_x(werkstuecklaenge() - ta);
                    mipubo1.set_x(werkstuecklaenge() - ta - mb);
                    mipubo2.set_x(werkstuecklaenge() - ta - mb);
                    for(uint i=1;i<=5;i++)
                    {
                        double abst = 0;
                        switch(i)
                        {
                            case 1:
                                abst = a1;
                                break;
                            case 2:
                                abst = a2;
                                break;
                            case 3:
                                abst = a3;
                                break;
                            case 4:
                                abst = a4;
                                break;
                            case 5:
                                abst = a5;
                                break;
                        }
                        if(abst == 0)
                        {
                            break;
                        }
                        miputo.set_y(abst);
                        mipubo1.set_y(abst-ma/2);
                        mipubo2.set_y(abst+ma/2);
                        kto.set_mittelpunkt(miputo);
                        kbo1.set_mittelpunkt(mipubo1);
                        kbo2.set_mittelpunkt(mipubo2);
                        kto = spiegeln_kreis(kto, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kbo1 = spiegeln_kreis(kbo1, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kbo2 = spiegeln_kreis(kbo2, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kto = lageaendern_kreis(kto, lageaendern_afb,\
                                                lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                lageaendern_wi_alt, lageaendern_geswi_alt);
                        kbo1 = lageaendern_kreis(kbo1, lageaendern_afb,\
                                                 lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                 lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                 lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                 lageaendern_wi_alt, lageaendern_geswi_alt);
                        kbo2 = lageaendern_kreis(kbo2, lageaendern_afb,\
                                                 lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                 lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                 lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                 lageaendern_wi_alt, lageaendern_geswi_alt);
                        kto.set_mittelpunkt(nullpunkt_wst.x() + kto.mitte3d().x(), nullpunkt_wst.y() + kto.mitte3d().y(),0);
                        kbo1.set_mittelpunkt(nullpunkt_wst.x() + kbo1.mitte3d().x(), nullpunkt_wst.y() + kbo1.mitte3d().y(),0);
                        kbo2.set_mittelpunkt(nullpunkt_wst.x() + kbo2.mitte3d().x(), nullpunkt_wst.y() + kbo2.mitte3d().y(),0);
                        Geo.add_kreis(kto);
                        Geo.add_kreis(kbo1);
                        Geo.add_kreis(kbo2);
                    }
                }else if(seite == 3)//oben
                {
                    punkt3d miputo, mipubo1, mipubo2;
                    miputo.set_y(werkstueckbreite() - ta);
                    mipubo1.set_y(werkstueckbreite() - ta - mb);
                    mipubo2.set_y(werkstueckbreite() - ta - mb);
                    for(uint i=1;i<=5;i++)
                    {
                        double abst = 0;
                        switch(i)
                        {
                            case 1:
                                abst = a1;
                                break;
                            case 2:
                                abst = a2;
                                break;
                            case 3:
                                abst = a3;
                                break;
                            case 4:
                                abst = a4;
                                break;
                            case 5:
                                abst = a5;
                                break;
                        }
                        if(abst == 0)
                        {
                            break;
                        }
                        miputo.set_x(abst);
                        mipubo1.set_x(abst-ma/2);
                        mipubo2.set_x(abst+ma/2);
                        kto.set_mittelpunkt(miputo);
                        kbo1.set_mittelpunkt(mipubo1);
                        kbo2.set_mittelpunkt(mipubo2);
                        kto = spiegeln_kreis(kto, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kbo1 = spiegeln_kreis(kbo1, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kbo2 = spiegeln_kreis(kbo2, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kto = lageaendern_kreis(kto, lageaendern_afb,\
                                                lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                lageaendern_wi_alt, lageaendern_geswi_alt);
                        kbo1 = lageaendern_kreis(kbo1, lageaendern_afb,\
                                                 lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                 lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                 lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                 lageaendern_wi_alt, lageaendern_geswi_alt);
                        kbo2 = lageaendern_kreis(kbo2, lageaendern_afb,\
                                                 lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                 lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                 lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                 lageaendern_wi_alt, lageaendern_geswi_alt);
                        kto.set_mittelpunkt(nullpunkt_wst.x() + kto.mitte3d().x(), nullpunkt_wst.y() + kto.mitte3d().y(),0);
                        kbo1.set_mittelpunkt(nullpunkt_wst.x() + kbo1.mitte3d().x(), nullpunkt_wst.y() + kbo1.mitte3d().y(),0);
                        kbo2.set_mittelpunkt(nullpunkt_wst.x() + kbo2.mitte3d().x(), nullpunkt_wst.y() + kbo2.mitte3d().y(),0);
                        Geo.add_kreis(kto);
                        Geo.add_kreis(kbo1);
                        Geo.add_kreis(kbo2);
                    }
                }else if(seite == 4)//links
                {
                    punkt3d miputo, mipubo1, mipubo2;
                    miputo.set_x(ta);
                    mipubo1.set_x(ta+mb);
                    mipubo2.set_x(ta+mb);
                    for(uint i=1;i<=5;i++)
                    {
                        double abst = 0;
                        switch(i)
                        {
                            case 1:
                                abst = a1;
                                break;
                            case 2:
                                abst = a2;
                                break;
                            case 3:
                                abst = a3;
                                break;
                            case 4:
                                abst = a4;
                                break;
                            case 5:
                                abst = a5;
                                break;
                        }
                        if(abst == 0)
                        {
                            break;
                        }
                        miputo.set_y(abst);
                        mipubo1.set_y(abst-ma/2);
                        mipubo2.set_y(abst+ma/2);
                        kto.set_mittelpunkt(miputo);
                        kbo1.set_mittelpunkt(mipubo1);
                        kbo2.set_mittelpunkt(mipubo2);
                        kto = spiegeln_kreis(kto, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kbo1 = spiegeln_kreis(kbo1, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kbo2 = spiegeln_kreis(kbo2, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        kto = lageaendern_kreis(kto, lageaendern_afb,\
                                                lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                lageaendern_wi_alt, lageaendern_geswi_alt);
                        kbo1 = lageaendern_kreis(kbo1, lageaendern_afb,\
                                                 lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                 lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                 lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                 lageaendern_wi_alt, lageaendern_geswi_alt);
                        kbo2 = lageaendern_kreis(kbo2, lageaendern_afb,\
                                                 lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                 lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                 lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                 lageaendern_wi_alt, lageaendern_geswi_alt);
                        kto.set_mittelpunkt(nullpunkt_wst.x() + kto.mitte3d().x(), nullpunkt_wst.y() + kto.mitte3d().y(),0);
                        kbo1.set_mittelpunkt(nullpunkt_wst.x() + kbo1.mitte3d().x(), nullpunkt_wst.y() + kbo1.mitte3d().y(),0);
                        kbo2.set_mittelpunkt(nullpunkt_wst.x() + kbo2.mitte3d().x(), nullpunkt_wst.y() + kbo2.mitte3d().y(),0);
                        Geo.add_kreis(kto);
                        Geo.add_kreis(kbo1);
                        Geo.add_kreis(kbo2);
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_HBEXP))
            {
                double y1 = text_mitte(zeile, HBEXP_Y1, ENDPAR).toDouble();
                double y2 = 0;
                double y3 = 0;
                double y4 = 0;
                double y5 = 0;
                double y6 = 0;
                double x2 = text_mitte(zeile, HBEXP_X2, ENDPAR).toDouble();
                double x1 = text_mitte(zeile, HBEXP_X1, ENDPAR).toDouble();
                double dm = text_mitte(zeile, HBEXP_DM, ENDPAR).toDouble();
                double ti = text_mitte(zeile, HBEXP_BOTI, ENDPAR).toDouble();
                double z = text_mitte(zeile, HBEXP_Z, ENDPAR).toDouble();
                bool kette = false;
                if(text_mitte(zeile, HBEXP_KETTE, ENDPAR).toDouble() > 0)
                {
                    kette = true;
                }
                if(kette == true)
                {
                    y2 = y1 + text_mitte(zeile, HBEXP_Y2, ENDPAR).toDouble();
                    y3 = y2 + text_mitte(zeile, HBEXP_Y3, ENDPAR).toDouble();
                    y4 = y3 + text_mitte(zeile, HBEXP_Y4, ENDPAR).toDouble();
                    y5 = y4 + text_mitte(zeile, HBEXP_Y5, ENDPAR).toDouble();
                    y6 = y5 + text_mitte(zeile, HBEXP_Y6, ENDPAR).toDouble();
                }else
                {
                    y2 = text_mitte(zeile, HBEXP_Y2, ENDPAR).toDouble();
                    y3 = text_mitte(zeile, HBEXP_Y3, ENDPAR).toDouble();
                    y4 = text_mitte(zeile, HBEXP_Y4, ENDPAR).toDouble();
                    y5 = text_mitte(zeile, HBEXP_Y5, ENDPAR).toDouble();
                    y6 = text_mitte(zeile, HBEXP_Y6, ENDPAR).toDouble();
                }
                rechteck3d r;
                r.set_stil(STIL_DURCHGEHEND);
                r.set_farbe(FARBE_SCHWARZ);
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_bezugspunkt(LINKS);
                r.set_laenge(ti);
                r.set_breite(dm);
                kreis k;
                k.set_stil(STIL_DURCHGEHEND);
                k.set_farbe(FARBE_SCHWARZ);
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(dm/2);
                for(uint i=1;i<=6;i++)
                {
                    double abst = 0;
                    switch(i)
                    {
                        case 1:
                            abst = y1;
                            break;
                        case 2:
                            abst = y2;
                            break;
                        case 3:
                            abst = y3;
                            break;
                        case 4:
                            abst = y4;
                            break;
                        case 5:
                            abst = y5;
                            break;
                        case 6:
                            abst = y6;
                            break;
                    }
                    if(abst == 0)
                    {
                        break;//for-Schleife
                    }
                    punkt3d p;
                    p.set_x(nullpunkt_wst.x() + x1);
                    p.set_y(nullpunkt_wst.y() + abst);
                    r.set_einfuegepunkt(p);
                    rechteck3d rgeo = r;
                    rgeo = spiegeln_rechteck3d(rgeo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    rgeo = lageaendern_rechteck3d(rgeo, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                    Geo.add_rechteck(rgeo);
                    if(kantenansicht == true)
                    {
                        punkt3d mipu;
                        mipu.set_x(nullpunkt_li.x() - z);
                        mipu.set_y(nullpunkt_li.y() + abst);
                        k.set_mittelpunkt(mipu);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        Geo.add_kreis(k);
                    }
                    if(x2 > 0)
                    {
                        rechteck3d r2 = r;
                        r2.set_bezugspunkt(RECHTS);
                        punkt3d p2 = p;
                        p2.set_x(nullpunkt_wst.x() + x2);
                        r2.set_einfuegepunkt(p2);
                        rechteck3d rgeo = r2;
                        rgeo = spiegeln_rechteck3d(rgeo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        rgeo = lageaendern_rechteck3d(rgeo, lageaendern_afb,\
                                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                        Geo.add_rechteck(rgeo);
                        if(kantenansicht == true)
                        {
                            punkt3d mipu;
                            mipu.set_x(nullpunkt_re.x() + z);
                            mipu.set_y(nullpunkt_li.y() + abst);
                            k.set_mittelpunkt(mipu);
                            k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            k = lageaendern_kreis(k, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                            Geo.add_kreis(k);
                        }
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_HBEXM))
            {
                double y1 = text_mitte(zeile, HBEXM_Y1, ENDPAR).toDouble();
                double y2 = 0;
                double y3 = 0;
                double y4 = 0;
                double y5 = 0;
                double y6 = 0;
                double x2 = text_mitte(zeile, HBEXM_X2, ENDPAR).toDouble();
                double x1 = text_mitte(zeile, HBEXM_X1, ENDPAR).toDouble();
                double dm = text_mitte(zeile, HBEXM_DM, ENDPAR).toDouble();
                double ti = text_mitte(zeile, HBEXM_BOTI, ENDPAR).toDouble();
                double z = text_mitte(zeile, HBEXM_Z, ENDPAR).toDouble();
                bool kette = false;
                if(text_mitte(zeile, HBEXM_KETTE, ENDPAR).toDouble() > 0)
                {
                    kette = true;
                }
                if(kette == true)
                {
                    y2 = y1 + text_mitte(zeile, HBEXM_Y2, ENDPAR).toDouble();
                    y3 = y2 + text_mitte(zeile, HBEXM_Y3, ENDPAR).toDouble();
                    y4 = y3 + text_mitte(zeile, HBEXM_Y4, ENDPAR).toDouble();
                    y5 = y4 + text_mitte(zeile, HBEXM_Y5, ENDPAR).toDouble();
                    y6 = y5 + text_mitte(zeile, HBEXM_Y6, ENDPAR).toDouble();
                }else
                {
                    y2 = text_mitte(zeile, HBEXM_Y2, ENDPAR).toDouble();
                    y3 = text_mitte(zeile, HBEXM_Y3, ENDPAR).toDouble();
                    y4 = text_mitte(zeile, HBEXM_Y4, ENDPAR).toDouble();
                    y5 = text_mitte(zeile, HBEXM_Y5, ENDPAR).toDouble();
                    y6 = text_mitte(zeile, HBEXM_Y6, ENDPAR).toDouble();
                }
                rechteck3d r;
                r.set_stil(STIL_DURCHGEHEND);
                r.set_farbe(FARBE_SCHWARZ);
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_bezugspunkt(RECHTS);
                r.set_laenge(ti);
                r.set_breite(dm);
                kreis k;
                k.set_stil(STIL_DURCHGEHEND);
                k.set_farbe(FARBE_SCHWARZ);
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(dm/2);
                for(uint i=1;i<=6;i++)
                {
                    double abst = 0;
                    switch(i)
                    {
                        case 1:
                            abst = y1;
                            break;
                        case 2:
                            abst = y2;
                            break;
                        case 3:
                            abst = y3;
                            break;
                        case 4:
                            abst = y4;
                            break;
                        case 5:
                            abst = y5;
                            break;
                        case 6:
                            abst = y6;
                            break;
                    }
                    if(abst == 0)
                    {
                        break;//for-Schleife
                    }
                    punkt3d p;
                    p.set_x(nullpunkt_wst.x() + x1);
                    p.set_y(nullpunkt_wst.y() + abst);
                    r.set_einfuegepunkt(p);
                    rechteck3d rgeo = r;
                    rgeo = spiegeln_rechteck3d(rgeo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    rgeo = lageaendern_rechteck3d(rgeo, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                    Geo.add_rechteck(rgeo);
                    if(kantenansicht == true)
                    {
                        punkt3d mipu;
                        mipu.set_x(nullpunkt_re.x() + z);
                        mipu.set_y(nullpunkt_li.y() + abst);
                        k.set_mittelpunkt(mipu);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        Geo.add_kreis(k);
                    }
                    if(x2 >= 0)
                    {
                        rechteck3d r2 = r;
                        r2.set_bezugspunkt(LINKS);
                        punkt3d p2 = p;
                        p2.set_x(nullpunkt_wst.x() + x2);
                        r2.set_einfuegepunkt(p2);
                        rechteck3d rgeo = r2;
                        rgeo = spiegeln_rechteck3d(rgeo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        rgeo = lageaendern_rechteck3d(rgeo, lageaendern_afb,\
                                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                        Geo.add_rechteck(rgeo);
                        if(kantenansicht == true)
                        {
                            punkt3d mipu;
                            mipu.set_x(nullpunkt_li.x() - z);
                            mipu.set_y(nullpunkt_li.y() + abst);
                            k.set_mittelpunkt(mipu);
                            k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            k = lageaendern_kreis(k, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                            Geo.add_kreis(k);
                        }
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_HBEYP))
            {
                double x1 = text_mitte(zeile, HBEYP_X1, ENDPAR).toDouble();
                double x2 = 0;
                double x3 = 0;
                double x4 = 0;
                double x5 = 0;
                double x6 = 0;
                double y2 = text_mitte(zeile, HBEYP_Y2, ENDPAR).toDouble();
                double y1 = text_mitte(zeile, HBEYP_Y1, ENDPAR).toDouble();
                double dm = text_mitte(zeile, HBEYP_DM, ENDPAR).toDouble();
                double ti = text_mitte(zeile, HBEYP_BOTI, ENDPAR).toDouble();
                double z = text_mitte(zeile, HBEYP_Z, ENDPAR).toDouble();
                bool kette = false;
                if(text_mitte(zeile, HBEYP_KETTE, ENDPAR).toDouble() > 0)
                {
                    kette = true;
                }
                if(kette == true)
                {
                    x2 = x1 + text_mitte(zeile, HBEYP_X2, ENDPAR).toDouble();
                    x3 = x2 + text_mitte(zeile, HBEYP_X3, ENDPAR).toDouble();
                    x4 = x3 + text_mitte(zeile, HBEYP_X4, ENDPAR).toDouble();
                    x5 = x4 + text_mitte(zeile, HBEYP_X5, ENDPAR).toDouble();
                    x6 = x5 + text_mitte(zeile, HBEYP_X6, ENDPAR).toDouble();
                }else
                {
                    x2 = text_mitte(zeile, HBEYP_X2, ENDPAR).toDouble();
                    x3 = text_mitte(zeile, HBEYP_X3, ENDPAR).toDouble();
                    x4 = text_mitte(zeile, HBEYP_X4, ENDPAR).toDouble();
                    x5 = text_mitte(zeile, HBEYP_X5, ENDPAR).toDouble();
                    x6 = text_mitte(zeile, HBEYP_X6, ENDPAR).toDouble();
                }
                rechteck3d r;
                r.set_stil(STIL_DURCHGEHEND);
                r.set_farbe(FARBE_SCHWARZ);
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_bezugspunkt(UNTEN);
                r.set_laenge(dm);
                r.set_breite(ti);
                kreis k;
                k.set_stil(STIL_DURCHGEHEND);
                k.set_farbe(FARBE_SCHWARZ);
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(dm/2);
                for(uint i=1;i<=6;i++)
                {
                    double abst = 0;
                    switch(i)
                    {
                        case 1:
                            abst = x1;
                            break;
                        case 2:
                            abst = x2;
                            break;
                        case 3:
                            abst = x3;
                            break;
                        case 4:
                            abst = x4;
                            break;
                        case 5:
                            abst = x5;
                            break;
                        case 6:
                            abst = x6;
                            break;
                    }
                    if(abst == 0)
                    {
                        break;//for-Schleife
                    }
                    punkt3d p;
                    p.set_y(nullpunkt_wst.y() + y1);
                    p.set_x(nullpunkt_wst.x() + abst);
                    r.set_einfuegepunkt(p);
                    rechteck3d rgeo = r;
                    rgeo = spiegeln_rechteck3d(rgeo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    rgeo = lageaendern_rechteck3d(rgeo, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                    Geo.add_rechteck(rgeo);
                    if(kantenansicht == true)
                    {
                        punkt3d mipu;
                        mipu.set_y(nullpunkt_un.y() - z);
                        mipu.set_x(nullpunkt_un.x() + abst);
                        k.set_mittelpunkt(mipu);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        Geo.add_kreis(k);
                    }
                    if(y2 > 0)
                    {
                        rechteck3d r2 = r;
                        r2.set_bezugspunkt(OBEN);
                        punkt3d p2 = p;
                        p2.set_y(nullpunkt_wst.y() + y2);
                        r2.set_einfuegepunkt(p2);
                        rechteck3d rgeo = r2;
                        rgeo = spiegeln_rechteck3d(rgeo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        rgeo = lageaendern_rechteck3d(rgeo, lageaendern_afb,\
                                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                        Geo.add_rechteck(rgeo);
                        if(kantenansicht == true)
                        {
                            punkt3d mipu;
                            mipu.set_y(nullpunkt_ob.y() + z);
                            mipu.set_x(nullpunkt_ob.x() + abst);
                            k.set_mittelpunkt(mipu);
                            k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            k = lageaendern_kreis(k, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                            Geo.add_kreis(k);
                        }
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_HBEYM))
            {
                double x1 = text_mitte(zeile, HBEYM_X1, ENDPAR).toDouble();
                double x2 = 0;
                double x3 = 0;
                double x4 = 0;
                double x5 = 0;
                double x6 = 0;
                double y2 = text_mitte(zeile, HBEYM_Y2, ENDPAR).toDouble();
                double y1 = text_mitte(zeile, HBEYM_Y1, ENDPAR).toDouble();
                double dm = text_mitte(zeile, HBEYM_DM, ENDPAR).toDouble();
                double ti = text_mitte(zeile, HBEYM_BOTI, ENDPAR).toDouble();
                double z = text_mitte(zeile, HBEYM_Z, ENDPAR).toDouble();
                bool kette = false;
                if(text_mitte(zeile, HBEYM_KETTE, ENDPAR).toDouble() > 0)
                {
                    kette = true;
                }
                if(kette == true)
                {
                    x2 = x1 + text_mitte(zeile, HBEYM_X2, ENDPAR).toDouble();
                    x3 = x2 + text_mitte(zeile, HBEYM_X3, ENDPAR).toDouble();
                    x4 = x3 + text_mitte(zeile, HBEYM_X4, ENDPAR).toDouble();
                    x5 = x4 + text_mitte(zeile, HBEYM_X5, ENDPAR).toDouble();
                    x6 = x5 + text_mitte(zeile, HBEYM_X6, ENDPAR).toDouble();
                }else
                {
                    x2 = text_mitte(zeile, HBEYM_X2, ENDPAR).toDouble();
                    x3 = text_mitte(zeile, HBEYM_X3, ENDPAR).toDouble();
                    x4 = text_mitte(zeile, HBEYM_X4, ENDPAR).toDouble();
                    x5 = text_mitte(zeile, HBEYM_X5, ENDPAR).toDouble();
                    x6 = text_mitte(zeile, HBEYM_X6, ENDPAR).toDouble();
                }
                rechteck3d r;
                r.set_stil(STIL_DURCHGEHEND);
                r.set_farbe(FARBE_SCHWARZ);
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_bezugspunkt(OBEN);
                r.set_laenge(dm);
                r.set_breite(ti);
                kreis k;
                k.set_stil(STIL_DURCHGEHEND);
                k.set_farbe(FARBE_SCHWARZ);
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(dm/2);
                for(uint i=1;i<=6;i++)
                {
                    double abst = 0;
                    switch(i)
                    {
                        case 1:
                            abst = x1;
                            break;
                        case 2:
                            abst = x2;
                            break;
                        case 3:
                            abst = x3;
                            break;
                        case 4:
                            abst = x4;
                            break;
                        case 5:
                            abst = x5;
                            break;
                        case 6:
                            abst = x6;
                            break;
                    }
                    if(abst == 0)
                    {
                        break;//for-Schleife
                    }
                    punkt3d p;
                    p.set_y(nullpunkt_wst.y() + y1);
                    p.set_x(nullpunkt_wst.x() + abst);
                    r.set_einfuegepunkt(p);
                    rechteck3d rgeo = r;
                    rgeo = spiegeln_rechteck3d(rgeo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    rgeo = lageaendern_rechteck3d(rgeo, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                    Geo.add_rechteck(rgeo);
                    if(kantenansicht == true)
                    {
                        punkt3d mipu;
                        mipu.set_y(nullpunkt_ob.y() + z);
                        mipu.set_x(nullpunkt_ob.x() + abst);
                        k.set_mittelpunkt(mipu);
                        k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        k = lageaendern_kreis(k, lageaendern_afb,\
                                              lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                              lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                              lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                              lageaendern_wi_alt, lageaendern_geswi_alt);
                        Geo.add_kreis(k);
                    }
                    if(y2 >= 0)
                    {
                        rechteck3d r2 = r;
                        r2.set_bezugspunkt(UNTEN);
                        punkt3d p2 = p;
                        p2.set_y(nullpunkt_wst.y() + y2);
                        r2.set_einfuegepunkt(p2);
                        rechteck3d rgeo = r2;
                        rgeo = spiegeln_rechteck3d(rgeo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        rgeo = lageaendern_rechteck3d(rgeo, lageaendern_afb,\
                                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                        Geo.add_rechteck(rgeo);
                        if(kantenansicht == true)
                        {
                            punkt3d mipu;
                            mipu.set_y(nullpunkt_un.y() - z);
                            mipu.set_x(nullpunkt_un.x() + abst);
                            k.set_mittelpunkt(mipu);
                            k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            k = lageaendern_kreis(k, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                            Geo.add_kreis(k);
                        }
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_NUT))
            {
                punkt3d sp;
                punkt3d ep;
                double b;
                double t;
                QString kor;
                rechteck3d r;
                r.set_bezugspunkt(MITTE);
                sp.set_x(text_mitte(zeile, NUT_SX, ENDPAR));
                sp.set_y(text_mitte(zeile, NUT_SY, ENDPAR));
                sp.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                ep.set_x(text_mitte(zeile, NUT_EX, ENDPAR));
                ep.set_y(text_mitte(zeile, NUT_EY, ENDPAR));
                ep.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                b = text_mitte(zeile, NUT_B, ENDPAR).toDouble();
                t = text_mitte(zeile, NUT_TI, ENDPAR).toDouble();
                kor = text_mitte(zeile, NUT_KOR, ENDPAR);
                strecke s;
                s.set_start(sp);
                s.set_ende(ep);
                r.set_laenge(s.laenge2d());
                r.set_breite(b);
                if(kor == "0")//mitte
                {
                    r.set_einfuegepunkt(s.mitpu3d());
                }else if(kor == "1")//links
                {
                    strecke s2 = s;
                    s2.set_laenge_2d(b);
                    s2.drenen_um_mittelpunkt_2d(90, true);
                    r.set_einfuegepunkt(s2.stapu());
                }else if(kor == "2")//rechts
                {
                    strecke s2 = s;
                    s2.set_laenge_2d(b);
                    s2.drenen_um_mittelpunkt_2d(90, false);
                    r.set_einfuegepunkt(s2.stapu());
                }

                r.set_drewi(s.wink());

                r.set_farbe_fuellung(FARBE_BLAU);
                sp.set_linienbreite(13);
                ep.set_linienbreite(8);

                sp = spiegeln_punkt3d(sp, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                ep = spiegeln_punkt3d(ep, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                sp = lageaendern_punkt3d(sp, lageaendern_afb,\
                                         lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                         lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                         lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                         lageaendern_wi_alt, lageaendern_geswi_alt);
                ep = lageaendern_punkt3d(ep, lageaendern_afb,\
                                         lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                         lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                         lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                         lageaendern_wi_alt, lageaendern_geswi_alt);
                r = spiegeln_rechteck3d(r, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                r = lageaendern_rechteck3d(r, lageaendern_afb,\
                                           lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                           lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                           lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                           lageaendern_wi_alt, lageaendern_geswi_alt);

                Geo.add_rechteck(r);
                Geo.add_punkt(sp);
                Geo.add_punkt(ep);
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_KTA))
            {
                punkt3d mipu;
                mipu.set_x(text_mitte(zeile, KTA_X, ENDPAR));
                mipu.set_y(text_mitte(zeile, KTA_Y, ENDPAR));
                mipu.set_z(0);

                double ti = text_mitte(zeile, KTA_TI, ENDPAR).toDouble();

                kreis k;
                k.set_farbe(FARBE_SCHWARZ);
                if(ti<=0 || ti > werkstueckdicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_DUNKELGRAU);
                }
                k.set_stil(STIL_DURCHGEHEND);

                k.set_mittelpunkt(mipu);
                k.set_radius(text_mitte(zeile, KTA_DM, ENDPAR).toDouble()/2);

                k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                k = lageaendern_kreis(k, lageaendern_afb,\
                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                k.set_mittelpunkt(nullpunkt_wst.x() + k.mitte3d().x(), nullpunkt_wst.y() + k.mitte3d().y(),0);//für ax und ay
                Geo.add_kreis(k);
                QString ausr = text_mitte(zeile, KTA_AUSR, ENDPAR);
                if(ausr == "0")
                {
                    double wkzdm = k.radius()/2;

                    QString wkzname = text_mitte(zeile, KTA_WKZ, ENDPAR);
                    text_zeilenweise wkzlist_name;
                    wkzlist_name = Wkz.wkzlist(WKZ_FRAESER, FRAESER_NAME);
                    text_zeilenweise wkzlist_dm;
                    wkzlist_dm = Wkz.wkzlist(WKZ_FRAESER, FRAESER_DM);

                    for(uint i=1; i<=wkzlist_name.zeilenanzahl() ;i++)
                    {
                        if(wkzlist_name.zeile(i) == wkzname)
                        {
                            if(wkzlist_dm.zeile(i).toDouble() > 0)
                            {
                                wkzdm = wkzlist_dm.zeile(i).toDouble();
                            }
                        }
                    }

                    if(wkzdm < k.radius())
                    {
                        k.set_farbe_fuellung(FARBE_GRAU);
                        k.set_radius(k.radius()-wkzdm);
                        Geo.add_kreis(k);
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_RTA))
            {
                punkt3d mipu;
                mipu.set_x(text_mitte(zeile, RTA_X, ENDPAR));
                mipu.set_y(text_mitte(zeile, RTA_Y, ENDPAR));
                mipu.set_z(0);

                double ti = text_mitte(zeile, RTA_TI, ENDPAR).toDouble();

                rechteck3d r;
                r.set_bezugspunkt(MITTE);
                r.set_farbe(FARBE_SCHWARZ);
                if(ti<=0 || ti > werkstueckdicke())
                {
                    r.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    r.set_farbe_fuellung(FARBE_DUNKELGRAU);
                }
                r.set_stil(STIL_DURCHGEHEND);

                r.set_einfuegepunkt(mipu);
                r.set_laenge(text_mitte(zeile, RTA_L, ENDPAR).toDouble());
                r.set_breite(text_mitte(zeile, RTA_B, ENDPAR).toDouble());
                r.set_drewi(text_mitte(zeile, RTA_WI, ENDPAR).toDouble());
                double min = r.l();
                if(r.b() < min)
                {
                    min = r.b();
                }
                double wkzdm = min/4;
                QString wkzname = text_mitte(zeile, RTA_WKZ, ENDPAR);
                text_zeilenweise wkzlist_name;
                wkzlist_name = Wkz.wkzlist(WKZ_FRAESER, FRAESER_NAME);
                text_zeilenweise wkzlist_dm;
                wkzlist_dm = Wkz.wkzlist(WKZ_FRAESER, FRAESER_DM);

                for(uint i=1; i<=wkzlist_name.zeilenanzahl() ;i++)
                {
                    if(wkzlist_name.zeile(i) == wkzname)
                    {
                        if(wkzlist_dm.zeile(i).toDouble() > 0)
                        {
                            wkzdm = wkzlist_dm.zeile(i).toDouble();
                        }
                    }
                }
                double rad = text_mitte(zeile, RTA_RAD, ENDPAR).toDouble();
                if(rad < wkzdm/2)
                {
                    rad = wkzdm/2;
                }
                if(rad > min/2)
                {
                    rad = min/2;
                }
                r.set_rad(rad);

                r = spiegeln_rechteck3d(r, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                r = lageaendern_rechteck3d(r, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                r.set_einfuegepunkt(nullpunkt_wst.x() + r.einfpunkt().x(), nullpunkt_wst.y() + r.einfpunkt().y(), 0);
                if(min < wkzdm)
                {
                    r.set_farbe_fuellung(FARBE_ROT);
                }
                Geo.add_rechteck(r);
                QString ausr = text_mitte(zeile, RTA_AUSR, ENDPAR);
                if(ausr == "0")
                {
                    if(wkzdm < min)
                    {
                        double lneu = r.l()-wkzdm*2;
                        double bneu = r.b()-wkzdm*2;
                        if(lneu > 0 && bneu > 0)
                        {
                            r.set_farbe_fuellung(FARBE_GRAU);
                            r.set_laenge(lneu);
                            r.set_breite(bneu);
                            double radneu = r.rad()-wkzdm;
                            if(radneu < 0)
                            {
                                radneu = 0;
                            }
                            r.set_rad(radneu);
                            Geo.add_rechteck(r);
                        }
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_VAR))
            {
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_VAR10))
            {
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_FAUF))
            {
                QString antyp;
                QString anwert;
                antyp = text_mitte(zeile, FAUF_ANTYP, ENDPAR);
                abtyp = text_mitte(zeile, FAUF_ABTYP, ENDPAR);
                anwert = text_mitte(zeile, FAUF_ANWEG, ENDPAR);
                abwert = text_mitte(zeile, FAUF_ABWEG, ENDPAR);
                strecke s;
                punkt3d sp, ep;
                bool wird_dargestellt = false;
                for(uint ii=i+1; ii<Klartext.zeilenanzahl();ii++)
                {
                    QString tmp = Klartext.zeile(ii);
                    if(tmp.contains(DLG_FABF) || tmp.contains(DLG_FAUF))
                    {
                        //wird_dargestellt = false;
                        break; //Anfahrweg und Abfahrweg kann nicht dargestellt werden da keine Fräskontur gefunden wurde
                    }else if(  tmp.contains(DLG_FGERADE)  ||  tmp.contains(DLG_FGERAWI)  )
                    {
                        sp.set_x(text_mitte(tmp, VAR_ALLGEM_XS, ENDPAR));
                        sp.set_y(text_mitte(tmp, VAR_ALLGEM_YS, ENDPAR));
                        ep.set_x(text_mitte(tmp, VAR_ALLGEM_XE, ENDPAR));
                        ep.set_y(text_mitte(tmp, VAR_ALLGEM_YE, ENDPAR));
                        wird_dargestellt = true;
                        break;
                    }else if(tmp.contains(DLG_FBOUZS))
                    {
                        sp.set_x(text_mitte(tmp, VAR_ALLGEM_XS, ENDPAR));
                        sp.set_y(text_mitte(tmp, VAR_ALLGEM_YS, ENDPAR));
                        punkt3d epbo;
                        epbo.set_x(text_mitte(tmp, VAR_ALLGEM_XE, ENDPAR));
                        epbo.set_y(text_mitte(tmp, VAR_ALLGEM_YE, ENDPAR));
                        double rad = text_mitte(tmp, FBOUZS_RADBO, ENDPAR).toDouble();
                        bogen bo;
                        bo.set_startpunkt(sp);
                        bo.set_endpunkt(epbo);
                        bo.set_radius(rad, true);
                        punkt3d mipu;
                        mipu.set_x(bo.mitte().x());
                        mipu.set_y(bo.mitte().y());
                        strecke stmp;
                        stmp.set_start(sp);
                        stmp.set_ende(mipu);
                        stmp.drenen_um_startpunkt_2d(90, false);
                        ep = stmp.endpu();
                        wird_dargestellt = true;
                        break;
                    }else if(tmp.contains(DLG_FBOGUZS))
                    {
                        sp.set_x(text_mitte(tmp, VAR_ALLGEM_XS, ENDPAR));
                        sp.set_y(text_mitte(tmp, VAR_ALLGEM_YS, ENDPAR));
                        punkt3d epbo;
                        epbo.set_x(text_mitte(tmp, VAR_ALLGEM_XE, ENDPAR));
                        epbo.set_y(text_mitte(tmp, VAR_ALLGEM_YE, ENDPAR));
                        double rad = text_mitte(tmp, FBOUZS_RADBO, ENDPAR).toDouble();
                        bogen bo;
                        bo.set_startpunkt(sp);
                        bo.set_endpunkt(epbo);
                        bo.set_radius(rad, false);
                        punkt3d mipu;
                        mipu.set_x(bo.mitte().x());
                        mipu.set_y(bo.mitte().y());
                        strecke stmp;
                        stmp.set_start(sp);
                        stmp.set_ende(mipu);
                        stmp.drenen_um_startpunkt_2d(90, true);
                        ep = stmp.endpu();
                        wird_dargestellt = true;
                        break;
                    }
                }
                if(wird_dargestellt == true)
                {
                    s.set_start(sp);
                    s.set_ende(ep);
                    s.set_laenge_2d(anwert.toDouble(), strecke_bezugspunkt_start);
                    s.drenen_um_startpunkt_2d(180, true);
                    QString kor = text_mitte(zeile, FAUF_KOR, ENDPAR);
                    radiuskor = kor;
                    wkzrad = text_mitte(zeile, VAR_ALLGEM_WKZDM, ENDPAR).toDouble()/2;
                    kreis k;
                    k.set_farbe(FARBE_BLAU);
                    k.set_farbe_fuellung(FARBE_SCHWARZ);
                    k.set_radius(wkzrad);

                    if(kor != "0")
                    {
                        if(spiegeln_xbed != spiegeln_ybed)
                        {
                            if(kor == "1")
                            {
                                kor = "2";
                            }else
                            {
                                kor = "1";
                            }
                        }
                    }

                    if(  (antyp == "0")  ||  (antyp == "1" && kor == "0")  )//Anfahrtyp Gerade
                    {
                        s.richtung_unkehren();
                        s.set_farbe(FARBE_BLAU);
                        s = spiegeln_strecke(s, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        s = lageaendern_strecke(s, lageaendern_afb,\
                                                lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                lageaendern_wi_alt, lageaendern_geswi_alt);
                        strecke sGeo = s;
                        sGeo.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                        Geo.add_strecke(sGeo);

                        if(kor == "0")//mitte == keine
                        {
                            k.set_mittelpunkt(s.mitpu3d());
                        }else if(kor == "1")//links
                        {
                            strecke stmp;
                            stmp.set_start(s.mitpu3d());
                            stmp.set_ende(s.endpu());
                            stmp.set_laenge_2d(k.radius(), strecke_bezugspunkt_start);
                            stmp.drenen_um_startpunkt_2d(90, false);
                            s.verschieben_um(stmp.endpu().x()-s.stapu().x(), stmp.endpu().y()-s.stapu().y());
                            k.set_mittelpunkt(s.stapu());
                        }else if(kor == "2")//rechts
                        {
                            strecke stmp;
                            stmp.set_start(s.mitpu3d());
                            stmp.set_ende(s.endpu());
                            stmp.set_laenge_2d(k.radius(), strecke_bezugspunkt_start);
                            stmp.drenen_um_startpunkt_2d(90, true);
                            s.verschieben_um(stmp.endpu().x()-s.stapu().x(), stmp.endpu().y()-s.stapu().y());
                            k.set_mittelpunkt(s.stapu());
                        }
                        k.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                        Fraeserdarst.add_kreis(k);
                    }else//Anfahrtyp Bogen
                    {
                        if(kor == "1")//links --> Bogen von links
                        {
                            s.drenen_um_endpunkt_2d(90, false);
                            bogen bo;
                            bo.set_startpunkt(s.stapu());
                            bo.set_endpunkt(sp);
                            bo.set_radius(anwert.toDouble(), false);
                            bo.set_farbe(FARBE_BLAU);
                            bo = spiegeln_bogen(bo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            bo = lageaendern_bogen(bo, lageaendern_afb,\
                                                   lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                   lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                   lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                   lageaendern_wi_alt, lageaendern_geswi_alt);
                            bogen boGeo = bo;
                            boGeo.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                            Geo.add_bogen(boGeo);
                            s.drenen_um_startpunkt_2d(90, false);
                            s.drenen_um_endpunkt_2d(45, false);
                            //-------------------------------------------------------------------
                            double laenge = anwert.toDouble();
                            laenge = laenge - k.radius();
                            s.set_laenge_2d(laenge, strecke_bezugspunkt_ende);
                            k.set_mittelpunkt(s.stapu());
                            //-------------------------------------------------------------------
                            k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            k = lageaendern_kreis(k, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                            k.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                            Fraeserdarst.add_kreis(k);
                        }else if(kor == "2")//rechts --> Bogen von rechts
                        {
                            s.drenen_um_endpunkt_2d(90, true);
                            bogen bo;
                            bo.set_startpunkt(s.stapu());
                            bo.set_endpunkt(sp);
                            bo.set_radius(anwert.toDouble(), true);
                            bo.set_farbe(FARBE_BLAU);
                            bo = spiegeln_bogen(bo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            bo = lageaendern_bogen(bo, lageaendern_afb,\
                                                   lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                   lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                   lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                   lageaendern_wi_alt, lageaendern_geswi_alt);
                            bogen boGeo = bo;
                            boGeo.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                            Geo.add_bogen(boGeo);
                            s.drenen_um_startpunkt_2d(90, true);
                            s.drenen_um_endpunkt_2d(45, true);
                            //-------------------------------------------------------------------
                            double laenge = anwert.toDouble();
                            laenge = laenge - k.radius();
                            s.set_laenge_2d(laenge, strecke_bezugspunkt_ende);
                            k.set_mittelpunkt(s.stapu());
                            //-------------------------------------------------------------------
                            k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            k = lageaendern_kreis(k, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                            k.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                            Fraeserdarst.add_kreis(k);
                        }
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_FABF))
            {
                strecke s;
                punkt3d sp, ep;
                bool wird_dargestellt = false;
                for(uint ii=i-1; ii>0 ;ii--)
                {
                    QString tmp = Klartext.zeile(ii);
                    if(tmp.contains(DLG_FABF) || tmp.contains(DLG_FAUF))
                    {
                        //wird_dargestellt = false;
                        break; //Anfahrweg und Abfahrweg kann nicht dargestellt werden da keine Fräskontur gefunden wurde
                    }else if(  tmp.contains(DLG_FGERADE)  ||  tmp.contains(DLG_FGERAWI)  )
                    {
                        sp.set_x(text_mitte(tmp, VAR_ALLGEM_XS, ENDPAR));
                        sp.set_y(text_mitte(tmp, VAR_ALLGEM_YS, ENDPAR));
                        ep.set_x(text_mitte(tmp, VAR_ALLGEM_XE, ENDPAR));
                        ep.set_y(text_mitte(tmp, VAR_ALLGEM_YE, ENDPAR));
                        wird_dargestellt = true;
                        break;
                    }else if(tmp.contains(DLG_FBOUZS))
                    {
                        ep.set_x(text_mitte(tmp, VAR_ALLGEM_XE, ENDPAR));
                        ep.set_y(text_mitte(tmp, VAR_ALLGEM_YE, ENDPAR));
                        punkt3d spbo;
                        spbo.set_x(text_mitte(tmp, VAR_ALLGEM_XS, ENDPAR));
                        spbo.set_y(text_mitte(tmp, VAR_ALLGEM_YS, ENDPAR));
                        double rad = text_mitte(tmp, FBOUZS_RADBO, ENDPAR).toDouble();
                        bogen bo;
                        bo.set_startpunkt(spbo);
                        bo.set_endpunkt(ep);
                        bo.set_radius(rad, true);
                        punkt3d mipu;
                        mipu.set_x(bo.mitte().x());
                        mipu.set_y(bo.mitte().y());
                        strecke stmp;
                        stmp.set_start(mipu);
                        stmp.set_ende(ep);
                        stmp.drenen_um_endpunkt_2d(90, true);
                        sp = stmp.stapu();
                        wird_dargestellt = true;
                        break;
                    }else if(tmp.contains(DLG_FBOGUZS))
                    {
                        ep.set_x(text_mitte(tmp, VAR_ALLGEM_XE, ENDPAR));
                        ep.set_y(text_mitte(tmp, VAR_ALLGEM_YE, ENDPAR));
                        punkt3d spbo;
                        spbo.set_x(text_mitte(tmp, VAR_ALLGEM_XS, ENDPAR));
                        spbo.set_y(text_mitte(tmp, VAR_ALLGEM_YS, ENDPAR));
                        double rad = text_mitte(tmp, FBOUZS_RADBO, ENDPAR).toDouble();
                        bogen bo;
                        bo.set_startpunkt(spbo);
                        bo.set_endpunkt(ep);
                        bo.set_radius(rad, false);
                        punkt3d mipu;
                        mipu.set_x(bo.mitte().x());
                        mipu.set_y(bo.mitte().y());
                        strecke stmp;
                        stmp.set_start(mipu);
                        stmp.set_ende(ep);
                        stmp.drenen_um_endpunkt_2d(90, false);
                        sp = stmp.stapu();
                        wird_dargestellt = true;
                        break;
                    }
                }
                if(wird_dargestellt == true)
                {
                    s.set_start(ep);
                    s.set_ende(sp);
                    s.set_laenge_2d(abwert.toDouble(), strecke_bezugspunkt_start);
                    s.drenen_um_startpunkt_2d(180, true);
                    QString kor = radiuskor;
                    kreis k;
                    k.set_farbe(FARBE_BLAU);
                    k.set_farbe_fuellung(FARBE_SCHWARZ);
                    k.set_radius(wkzrad);

                    if(kor != "0")
                    {
                        if(spiegeln_xbed != spiegeln_ybed)
                        {
                            if(kor == "1")
                            {
                                kor = "2";
                            }else
                            {
                                kor = "1";
                            }
                        }
                    }

                    if(  (abtyp == "0")  ||  (abtyp == "1" && kor == "0")  )//Anfahrtyp Gerade
                    {
                        s.richtung_unkehren();
                        s.set_farbe(FARBE_BLAU);
                        s = spiegeln_strecke(s, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                        s = lageaendern_strecke(s, lageaendern_afb,\
                                                lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                lageaendern_wi_alt, lageaendern_geswi_alt);
                        strecke sGeo = s;
                        sGeo.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                        Geo.add_strecke(sGeo);
                        if(kor == "0")//mitte == keine
                        {
                            k.set_mittelpunkt(s.mitpu3d());
                        }else if(kor == "1")//links
                        {
                            strecke stmp;
                            stmp.set_start(s.mitpu3d());
                            stmp.set_ende(s.endpu());
                            stmp.set_laenge_2d(k.radius(), strecke_bezugspunkt_start);
                            stmp.drenen_um_startpunkt_2d(90, true);
                            s.verschieben_um(stmp.endpu().x()-s.stapu().x(), stmp.endpu().y()-s.stapu().y());
                            k.set_mittelpunkt(s.stapu());
                        }else if(kor == "2")//rechts
                        {
                            strecke stmp;
                            stmp.set_start(s.mitpu3d());
                            stmp.set_ende(s.endpu());
                            stmp.set_laenge_2d(k.radius(), strecke_bezugspunkt_start);
                            stmp.drenen_um_startpunkt_2d(90, false);
                            s.verschieben_um(stmp.endpu().x()-s.stapu().x(), stmp.endpu().y()-s.stapu().y());
                            k.set_mittelpunkt(s.stapu());
                        }
                        k.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                        Fraeserdarst.add_kreis(k);
                    }else//Anfahrtyp Bogen
                    {
                        if(kor == "1")//links --> Bogen von links
                        {
                            bogen bo;
                            bo.set_startpunkt(s.stapu());
                            s.drenen_um_endpunkt_2d(90, true);
                            bo.set_endpunkt(s.stapu());
                            bo.set_radius(abwert.toDouble(), false);
                            bo.set_farbe(FARBE_BLAU);
                            bo = spiegeln_bogen(bo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            bo = lageaendern_bogen(bo, lageaendern_afb,\
                                                   lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                   lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                   lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                   lageaendern_wi_alt, lageaendern_geswi_alt);
                            bogen boGeo = bo;
                            boGeo.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                            Geo.add_bogen(boGeo);
                            s.drenen_um_startpunkt_2d(90, true);
                            s.drenen_um_endpunkt_2d(45, true);
                            //-------------------------------------------------------------------
                            double laenge = abwert.toDouble();
                            laenge = laenge - k.radius();
                            s.set_laenge_2d(laenge, strecke_bezugspunkt_ende);
                            k.set_mittelpunkt(s.stapu());
                            //-------------------------------------------------------------------
                            k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            k = lageaendern_kreis(k, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                            k.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                            Fraeserdarst.add_kreis(k);
                        }else if(kor == "2")//rechts --> Bogen von rechts
                        {
                            bogen bo;
                            bo.set_startpunkt(s.stapu());
                            s.drenen_um_endpunkt_2d(90, false);
                            bo.set_endpunkt(s.stapu());
                            bo.set_radius(abwert.toDouble(), true);
                            bo.set_farbe(FARBE_BLAU);
                            bo = spiegeln_bogen(bo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            bo = lageaendern_bogen(bo, lageaendern_afb,\
                                                   lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                   lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                   lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                   lageaendern_wi_alt, lageaendern_geswi_alt);
                            bogen boGeo = bo;
                            boGeo.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                            Geo.add_bogen(boGeo);
                            s.drenen_um_startpunkt_2d(90, false);
                            s.drenen_um_endpunkt_2d(45, false);
                            //-------------------------------------------------------------------
                            double laenge = abwert.toDouble();
                            laenge = laenge - k.radius();
                            s.set_laenge_2d(laenge, strecke_bezugspunkt_ende);
                            k.set_mittelpunkt(s.stapu());
                            //-------------------------------------------------------------------
                            k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                            k = lageaendern_kreis(k, lageaendern_afb,\
                                                  lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                                  lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                                  lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                                  lageaendern_wi_alt, lageaendern_geswi_alt);
                            k.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                            Fraeserdarst.add_kreis(k);
                        }
                    }
                }
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_FGERADE) ||  zeile.contains(DLG_FGERAWI))
            {
                punkt3d sp, ep;
                sp.set_x(text_mitte(zeile, VAR_ALLGEM_XS, ENDPAR));
                sp.set_y(text_mitte(zeile, VAR_ALLGEM_YS, ENDPAR));
                ep.set_x(text_mitte(zeile, VAR_ALLGEM_XE, ENDPAR));
                ep.set_y(text_mitte(zeile, VAR_ALLGEM_YE, ENDPAR));
                strecke s;
                s.set_start(sp);
                s.set_ende(ep);
                s.set_farbe(FARBE_BLAU);
                s = spiegeln_strecke(s, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                s = lageaendern_strecke(s, lageaendern_afb,\
                                        lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                        lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                        lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                        lageaendern_wi_alt, lageaendern_geswi_alt);
                s.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                Geo.add_strecke(s);

                kreis k;
                k.set_farbe(FARBE_BLAU);
                k.set_farbe_fuellung(FARBE_SCHWARZ);
                k.set_radius(text_mitte(zeile, VAR_ALLGEM_WKZDM, ENDPAR).toDouble()/2);

                QString kor = text_mitte(zeile, VAR_ALLGEM_WKZKOR, ENDPAR);
                if(kor == "0")//mitte == keine
                {
                    k.set_mittelpunkt(s.mitpu3d());
                }else if(kor == "1")//links
                {
                    strecke stmp = s;
                    stmp.set_laenge_2d(k.radius(), strecke_bezugspunkt_start);
                    if(  (spiegeln_xbed == true && spiegeln_ybed == true)  ||  (spiegeln_xbed == false && spiegeln_ybed == false)  )
                    {
                        stmp.drenen_um_startpunkt_2d(90, false);
                    }else
                    {
                        stmp.drenen_um_startpunkt_2d(90, true);
                    }
                    s.verschieben_um(stmp.endpu().x()-s.stapu().x(), stmp.endpu().y()-s.stapu().y());
                    k.set_mittelpunkt(s.mitpu3d());
                }else if(kor == "2")//rechts
                {
                    strecke stmp = s;
                    stmp.set_laenge_2d(k.radius(), strecke_bezugspunkt_start);
                    if(  (spiegeln_xbed == true && spiegeln_ybed == true)  ||  (spiegeln_xbed == false && spiegeln_ybed == false)  )
                    {
                        stmp.drenen_um_startpunkt_2d(90, true);
                    }else
                    {
                        stmp.drenen_um_startpunkt_2d(90, false);
                    }
                    s.verschieben_um(stmp.endpu().x()-s.stapu().x(), stmp.endpu().y()-s.stapu().y());
                    k.set_mittelpunkt(s.mitpu3d());
                }
                Fraeserdarst.add_kreis(k);
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_FBOUZS))
            {
                punkt3d sp, ep;
                sp.set_x(text_mitte(zeile, VAR_ALLGEM_XS, ENDPAR));
                sp.set_y(text_mitte(zeile, VAR_ALLGEM_YS, ENDPAR));
                ep.set_x(text_mitte(zeile, VAR_ALLGEM_XE, ENDPAR));
                ep.set_y(text_mitte(zeile, VAR_ALLGEM_YE, ENDPAR));
                bogen bo;
                bo.set_startpunkt(sp);
                bo.set_endpunkt(ep);
                double rad = text_mitte(zeile, FBOUZS_RADBO, ENDPAR).toDouble();
                if(rad < 0)
                {
                    rad = rad * -1;
                }
                bo.set_radius(rad, true);
                bo.set_farbe(FARBE_BLAU);
                bogen bo_orgi = bo;
                bo = spiegeln_bogen(bo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                bo = lageaendern_bogen(bo, lageaendern_afb,\
                                       lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                       lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                       lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                       lageaendern_wi_alt, lageaendern_geswi_alt);
                bo.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                Geo.add_bogen(bo);
                kreis k;
                k.set_farbe(FARBE_BLAU);
                k.set_farbe_fuellung(FARBE_SCHWARZ);
                k.set_radius(text_mitte(zeile, VAR_ALLGEM_WKZDM, ENDPAR).toDouble()/2);
                strecke s;
                punkt3d mipu;
                mipu.set_x(bo_orgi.mitte().x());
                mipu.set_y(bo_orgi.mitte().y());
                s.set_start(bo_orgi.start());
                s.set_ende(bo_orgi.ende());
                s.drenen_um_mittelpunkt_2d(90, false);
                s.set_start(mipu);
                //-------------------------------------------------------------------
                double laenge = 0;
                QString kor = text_mitte(zeile, VAR_ALLGEM_WKZKOR, ENDPAR);
                if(kor == "0")//mitte == keine
                {
                   laenge = rad;
                }else if(kor == "1")//links
                {
                   laenge = rad;
                   laenge = laenge + k.radius();
                }else if(kor == "2")//rechts
                {
                    laenge = rad;
                    laenge = laenge - k.radius();
                }
                s.set_laenge_2d(laenge, strecke_bezugspunkt_start);
                k.set_mittelpunkt(s.endpu());
                //-------------------------------------------------------------------
                k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                k = lageaendern_kreis(k, lageaendern_afb,\
                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                k.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                Fraeserdarst.add_kreis(k);
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else if(zeile.contains(DLG_FBOGUZS))
            {
                punkt3d sp, ep;
                sp.set_x(text_mitte(zeile, VAR_ALLGEM_XS, ENDPAR));
                sp.set_y(text_mitte(zeile, VAR_ALLGEM_YS, ENDPAR));
                ep.set_x(text_mitte(zeile, VAR_ALLGEM_XE, ENDPAR));
                ep.set_y(text_mitte(zeile, VAR_ALLGEM_YE, ENDPAR));
                bogen bo;
                bo.set_startpunkt(sp);
                bo.set_endpunkt(ep);
                double rad = text_mitte(zeile, FBOUZS_RADBO, ENDPAR).toDouble();
                if(rad < 0)
                {
                    rad = rad * -1;
                }
                bo.set_radius(rad, false);
                bo.set_farbe(FARBE_BLAU);
                bogen bo_orgi = bo;
                bo = spiegeln_bogen(bo, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                bo = lageaendern_bogen(bo, lageaendern_afb,\
                                       lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                       lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                       lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                       lageaendern_wi_alt, lageaendern_geswi_alt);
                bo.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                Geo.add_bogen(bo);
                kreis k;
                k.set_farbe(FARBE_BLAU);
                k.set_farbe_fuellung(FARBE_SCHWARZ);
                k.set_radius(text_mitte(zeile, VAR_ALLGEM_WKZDM, ENDPAR).toDouble()/2);
                strecke s;
                punkt3d mipu;
                mipu.set_x(bo_orgi.mitte().x());
                mipu.set_y(bo_orgi.mitte().y());
                s.set_start(bo_orgi.start());
                s.set_ende(bo_orgi.ende());
                s.drenen_um_mittelpunkt_2d(90, true);
                s.set_start(mipu);
                double laenge = 0;
                QString kor = text_mitte(zeile, VAR_ALLGEM_WKZKOR, ENDPAR);
                if(kor == "0")//mitte == keine
                {
                   laenge = rad;
                }else if(kor == "1")//links
                {
                   laenge = rad;
                   laenge = laenge - k.radius();
                }else if(kor == "2")//rechts
                {
                    laenge = rad;
                    laenge = laenge + k.radius();
                }
                s.set_laenge_2d(laenge, strecke_bezugspunkt_start);
                k.set_mittelpunkt(s.endpu());
                k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                k = lageaendern_kreis(k, lageaendern_afb,\
                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                k.verschieben_um(nullpunkt_wst.x(), nullpunkt_wst.y());
                Fraeserdarst.add_kreis(k);
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }else
            {
                Geo.zeilenvorschub();
                Fraeserdarst.zeilenvorschub();
            }
        }
    }
}
void programmtext::aktualisiere_anzeigetext()
{
    if(!Aktualisieren_eingeschaltet)
    {
        return;
    }

    Anzeigetext.clear();
    for(uint i=1 ; i<=Text.zeilenanzahl() ; i++)
    {
        QString zeile = Text.zeile(i);
        QString zeilekt = Klartext.zeile(i);
        QString tmp;
        tmp = QString::fromStdString(int_to_string(i));
        tmp += ": ";
        //-----------------------
        if(zeile.contains(DLG_PKOPF))
        {
            tmp += text_mitte(zeile, PKOPF_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_PENDE))
        {
            tmp += text_mitte(zeile, PENDE_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_KOM))
        {
            tmp += text_mitte(zeile, KOM_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_HALT))
        {
            tmp += text_mitte(zeile, HALT_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_SPIEGELN))
        {
            tmp += text_mitte(zeile, SPIEGELN_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_LAGE_AENDERN))
        {
            tmp += text_mitte(zeile, LAGE_AENDERN_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_BO))
        {
            tmp += text_mitte(zeile, BO_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_BOY))
        {
            tmp += text_mitte(zeile, BOY_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_BOX))
        {
            tmp += text_mitte(zeile, BOX_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_LOREIAE))
        {
            tmp += text_mitte(zeile, LOREIAE_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_LOREIMA))
        {
            tmp += text_mitte(zeile, LOREIMA_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_TOPF))
        {
            tmp += text_mitte(zeile, TOPF_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_HBEXP))
        {
            tmp += text_mitte(zeile, HBEXP_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_HBEXM))
        {
            tmp += text_mitte(zeile, HBEXM_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_HBEYP))
        {
            tmp += text_mitte(zeile, HBEYP_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_HBEYM))
        {
            tmp += text_mitte(zeile, HBEYM_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_NUT))
        {
            tmp += text_mitte(zeile, NUT_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_KTA))
        {
            tmp += text_mitte(zeile, KTA_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_RTA))
        {
            tmp += text_mitte(zeile, RTA_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_VAR))
        {
            tmp += text_mitte(zeile, VAR_BEZ, ENDPAR);
            tmp += " [";
            tmp += text_mitte(zeile, VAR_NAME, ENDPAR);
            tmp += " = ";
            tmp += text_mitte(zeilekt, VAR_WERT, ENDPAR);
            tmp += "]";
        }else if(zeile.contains(DLG_VAR10))
        {
            tmp += text_mitte(zeile, VAR10_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_FAUF))
        {
            tmp += text_mitte(zeile, FAUF_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_FABF))
        {
            tmp += text_mitte(zeile, FABF_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_FGERADE))
        {
            tmp += text_mitte(zeile, FGERADE_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_FGERAWI))
        {
            tmp += text_mitte(zeile, FGERAWI_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_FBOUZS))
        {
            tmp += text_mitte(zeile, FBOUZS_BEZ, ENDPAR);
        }else if(zeile.contains(DLG_FBOGUZS))
        {
            tmp += text_mitte(zeile, FBOGUZS_BEZ, ENDPAR);
        }else if(zeile.contains(LISTENENDE))
        {
            tmp += "...";
        }else
        {
            tmp += zeile;
        }
        //-----------------------
        if(  (zeile.at(0) == '/')  &&  (zeile.at(1) == '/')  )
        {
            tmp = "//" + tmp;
        }
        if(tmp.isEmpty())
        {
            tmp = " ";
        }
        if(i==1)
        {
            Anzeigetext.set_text(tmp);
        }else
        {
            Anzeigetext.zeile_anhaengen(tmp);
        }
    }
}
void programmtext::aktualisiere_min_max()
{
    Min_x = 0;
    Min_y = 0;
    Max_x = 0;
    Max_y = 0;
    //min und max berechnen:
    text_zeilenweise geotext = Geo.text_zw();
    for(uint i=1;i<=geotext.zeilenanzahl();i++)
    {
        text_zeilenweise spalten;
        spalten.set_trennzeichen(TRZ_EL_);
        spalten.set_text(geotext.zeile(i));

        for(uint ii=1;ii<=spalten.zeilenanzahl();ii++)
        {
            text_zeilenweise element;
            element.set_trennzeichen(TRZ_PA_);
            element.set_text(spalten.zeile(ii));

            if(element.text().contains(PUNKT))
            {
                double x = element.zeile(2).toDouble();
                double y = element.zeile(3).toDouble();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
            }else if(element.text().contains(STRECKE))
            {
                double x = element.zeile(2).toDouble();
                double y = element.zeile(3).toDouble();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
                x = element.zeile(5).toDouble();
                y = element.zeile(6).toDouble();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
            }else if(element.text().contains(BOGEN))
            {
                double x = element.zeile(2).toDouble();
                double y = element.zeile(3).toDouble();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
                x = element.zeile(5).toDouble();
                y = element.zeile(6).toDouble();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
            }else if(element.text().contains(KREIS))
            {
                double rad = element.zeile(5).toDouble();
                double x = element.zeile(2).toDouble()-rad;
                double y = element.zeile(3).toDouble()-rad;
                if(x < Min_x)
                {
                    Min_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }
                x = x+rad*2;
                y = y+rad*2;
                if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y > Max_y)
                {
                    Max_y = y;
                }
            }else if(element.text().contains(ZYLINDER))
            {
                double rad = element.zeile(5).toDouble();
                double x = element.zeile(2).toDouble()-rad;
                double y = element.zeile(3).toDouble()-rad;
                if(x < Min_x)
                {
                    Min_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }
                x = x+rad*2;
                y = y+rad*2;
                if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y > Max_y)
                {
                    Max_y = y;
                }
            }else if(element.text().contains(RECHTECK3D))
            {
                rechteck3d r;
                r.set_bezugspunkt(element.zeile(2).toInt());
                r.set_einfuegepunkt(element.zeile(3).toDouble(),\
                                    element.zeile(4).toDouble(),\
                                    element.zeile(5).toDouble());
                r.set_laenge(element.zeile(6).toDouble());
                r.set_breite(element.zeile(7).toDouble());
                r.set_rad(element.zeile(8).toDouble());
                r.set_drewi(element.zeile(9).toDouble());

                double x = r.unl(false).x();
                double y = r.unl(false).y();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
                x = r.unr(false).x();
                y = r.unr(false).y();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
                x = r.obl(false).x();
                y = r.obl(false).y();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
                x = r.obr(false).x();
                y = r.obr(false).y();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
            }else if(element.text().contains(WUERFEL))
            {
                rechteck3d r;
                r.set_bezugspunkt(element.zeile(2).toInt());
                r.set_einfuegepunkt(element.zeile(3).toDouble(),\
                                    element.zeile(4).toDouble(),\
                                    element.zeile(5).toDouble());
                r.set_laenge(element.zeile(6).toDouble());
                r.set_breite(element.zeile(7).toDouble());
                r.set_rad(element.zeile(8).toDouble());
                r.set_drewi(element.zeile(9).toDouble());

                double x = r.unl(false).x();
                double y = r.unl(false).y();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
                x = r.unr(false).x();
                y = r.unr(false).y();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
                x = r.obl(false).x();
                y = r.obl(false).y();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
                x = r.obr(false).x();
                y = r.obr(false).y();
                if(x < Min_x)
                {
                    Min_x = x;
                }else if(x > Max_x)
                {
                    Max_x = x;
                }
                if(y < Min_y)
                {
                    Min_y = y;
                }else if(y > Max_y)
                {
                    Max_y = y;
                }
            }
        }
    }
    Min_x -= 50;
    Min_y -= 50;
    Max_x += 50;
    Max_y += 50;
}
//-------------
kreis programmtext::spiegeln_kreis(kreis k, bool xbed, bool ybed, double xpos, double ypos)
{
    punkt3d mipu;
    mipu = k.mitte3d();
    if(xbed == true)
    {
        double x = mipu.x();
        double abstspiegelachse = xpos - x;
        x = x + (2*abstspiegelachse);
        mipu.set_x(x);
        k.set_mittelpunkt(mipu);
    }
    if(ybed == true)
    {
        double y = mipu.y();
        double abstspiegelachse = ypos - y;
        y = y + (2*abstspiegelachse);
        mipu.set_y(y);
        k.set_mittelpunkt(mipu);
    }
    return  k;
}
punkt3d programmtext::spiegeln_punkt3d(punkt3d p, bool xbed, bool ybed, double xpos, double ypos)
{
    if(xbed == true)
    {
        double x = p.x();
        double abstspiegelachse = xpos - x;
        x = x + (2*abstspiegelachse);
        p.set_x(x);
    }
    if(ybed == true)
    {
        double y = p.y();
        double abstspiegelachse = ypos - y;
        y = y + (2*abstspiegelachse);
        p.set_y(y);
    }
    return  p;
}
rechteck3d programmtext::spiegeln_rechteck3d(rechteck3d r, bool xbed, bool ybed, double xpos, double ypos)
{
    punkt3d mipu;
    mipu = r.mi();
    if(xbed == true)
    {
        double x = mipu.x();
        double abstspiegelachse = xpos - x;
        x = x + (2*abstspiegelachse);
        mipu.set_x(x);
        r.set_mipu(mipu);
        r.set_drewi(360-r.drewi());
    }
    if(ybed == true)
    {
        double y = mipu.y();
        double abstspiegelachse = ypos - y;
        y = y + (2*abstspiegelachse);
        mipu.set_y(y);
        r.set_mipu(mipu);
        r.set_drewi(360-r.drewi());
    }
    return  r;
}
strecke programmtext::spiegeln_strecke(strecke s, bool xbed, bool ybed, double xpos, double ypos)
{
    s.set_start(spiegeln_punkt3d(s.stapu(), xbed, ybed, xpos, ypos));
    s.set_ende(spiegeln_punkt3d(s.endpu(), xbed, ybed, xpos, ypos));
    return  s;
}
bogen programmtext::spiegeln_bogen(bogen bo, bool xbed, bool ybed, double xpos, double ypos)
{
    if(xbed == false && ybed == false)
    {
        return  bo;
    }
    double rad = bo.rad();
    punkt3d sp = spiegeln_punkt3d(bo.start(), xbed, ybed, xpos, ypos);
    punkt3d ep = spiegeln_punkt3d(bo.ende(), xbed, ybed, xpos, ypos);
    bo.set_startpunkt(ep);
    bo.set_endpunkt(sp);

    if(xbed == true && ybed == true)
    {
        bo.set_radius(rad, !bo.im_uzs());
    }else
    {
        bo.set_radius(rad, bo.im_uzs());
    }
    return  bo;
}
//-------------
kreis programmtext::lageaendern_kreis(kreis k, bool afb, \
                                      double xalt, double yalt, double xneu, double yneu, \
                                      double wi, double geswi, bool kettenmas, \
                                      double xalt2, double yalt2, double xneu2, double yneu2, \
                                      double wi2, double geswi2)
{
    if(afb == true)
    {
        punkt3d mipu;
        mipu = k.mitte3d();
        double x = mipu.x();
        double y = mipu.y();
        double ax = xneu - xalt;
        double ay = yneu - yalt;
        double w = wi + geswi;
        if(kettenmas == true)
        {
            double ax2 = xneu2 - xalt2;
            double ay2 = yneu2 - yalt2;
            double w2 = wi2 + geswi2;
            ax = ax + ax2;
            ay = ay + ay2;
            w = w + w2;
        }
        if(w != 0)
        {
            punkt3d sp, ep;
            sp.set_x(xalt);
            sp.set_y(yalt);
            ep.set_x(mipu.x());
            ep.set_y(mipu.y());
            strecke s;
            s.set_start(sp);
            s.set_ende(ep);
            s.drenen_um_startpunkt_2d(w, false);
            x = s.endpu().x();
            y = s.endpu().y();
        }
        x = x + ax;
        y = y + ay;
        mipu.set_x(x);
        mipu.set_y(y);
        k.set_mittelpunkt(mipu);
    }
    return  k;
}
punkt3d programmtext::lageaendern_punkt3d(punkt3d p, bool afb, \
                                          double xalt, double yalt, double xneu, double yneu, \
                                          double wi, double geswi, bool kettenmas, \
                                          double xalt2, double yalt2, double xneu2, double yneu2, \
                                          double wi2, double geswi2)
{
    if(afb == true)
    {
        double x = p.x();
        double y = p.y();
        double ax = xneu - xalt;
        double ay = yneu - yalt;
        double w = wi + geswi;
        if(kettenmas == true)
        {
            double ax2 = xneu2 - xalt2;
            double ay2 = yneu2 - yalt2;
            double w2 = wi2 + geswi2;
            ax = ax + ax2;
            ay = ay + ay2;
            w = w + w2;
        }
        if(w != 0)
        {
            punkt3d sp, ep;
            sp.set_x(xalt);
            sp.set_y(yalt);
            ep.set_x(p.x());
            ep.set_y(p.y());
            strecke s;
            s.set_start(sp);
            s.set_ende(ep);
            s.drenen_um_startpunkt_2d(w, false);
            x = s.endpu().x();
            y = s.endpu().y();
        }
        x = x + ax;
        y = y + ay;
        p.set_x(x);
        p.set_y(y);
    }
    return  p;
}
rechteck3d programmtext::lageaendern_rechteck3d(rechteck3d r, bool afb, \
                                                double xalt, double yalt, double xneu, \
                                                double yneu, double wi, double geswi, bool kettenmas, \
                                                double xalt2, double yalt2, double xneu2, double yneu2, \
                                                double wi2, double geswi2)
{
    if(afb == true)
    {
        punkt3d mipu;
        mipu = r.mi();
        double x = mipu.x();
        double y = mipu.y();
        double ax = xneu - xalt;
        double ay = yneu - yalt;
        double w = wi + geswi;
        if(kettenmas == true)
        {
            double ax2 = xneu2 - xalt2;
            double ay2 = yneu2 - yalt2;
            double w2 = wi2 + geswi2;
            ax = ax + ax2;
            ay = ay + ay2;
            w = w + w2;
        }
        if(w != 0)
        {
            punkt3d sp, ep;
            sp.set_x(xalt);
            sp.set_y(yalt);
            ep.set_x(mipu.x());
            ep.set_y(mipu.y());
            strecke s;
            s.set_start(sp);
            s.set_ende(ep);
            s.drenen_um_startpunkt_2d(w, false);
            x = s.endpu().x();
            y = s.endpu().y();
            r.set_drewi(r.drewi()+w);
        }
        x = x + ax;
        y = y + ay;
        mipu.set_x(x);
        mipu.set_y(y);
        r.set_mipu(mipu);
    }
    return  r;
}
strecke programmtext::lageaendern_strecke(strecke s, bool afb, \
                                          double xalt, double yalt, double xneu, \
                                          double yneu, double wi, double geswi, bool kettenmas, \
                                          double xalt2, double yalt2, double xneu2, double yneu2, \
                                          double wi2, double geswi2)
{
    s.set_start(lageaendern_punkt3d(s.stapu(), afb, xalt, yalt, xneu, yneu, wi, geswi, kettenmas, xalt2, yalt2, xneu2, yneu2, wi2, geswi2));
    s.set_ende(lageaendern_punkt3d(s.endpu(), afb, xalt, yalt, xneu, yneu, wi, geswi, kettenmas, xalt2, yalt2, xneu2, yneu2, wi2, geswi2));
    return s;
}
bogen programmtext::lageaendern_bogen(bogen bo, bool afb, \
                                      double xalt, double yalt, double xneu, \
                                      double yneu, double wi, double geswi, bool kettenmas, \
                                      double xalt2, double yalt2, double xneu2, double yneu2, \
                                      double wi2, double geswi2)
{
    punkt3d sp = lageaendern_punkt3d(bo.start(), afb, xalt, yalt, xneu, yneu, wi, geswi, kettenmas, xalt2, yalt2, xneu2, yneu2, wi2, geswi2);
    punkt3d ep = lageaendern_punkt3d(bo.ende(), afb, xalt, yalt, xneu, yneu, wi, geswi, kettenmas, xalt2, yalt2, xneu2, yneu2, wi2, geswi2);
    bo.set_startpunkt(sp);
    bo.set_endpunkt(ep);
    bo.set_radius(bo.rad(), bo.im_uzs());
    return bo;
}

//------------------------------------------------------------










