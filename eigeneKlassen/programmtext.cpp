#include "programmtext.h"

//------------------------------------------------------------
//public:
programmtext::programmtext()
{
    clear();
    warnungen_einschalten(true);
    aktualisieren_ein_aus(true);
    aktualisieren_fkon_ein_aus(false);
    nurlesend(false);
}

void programmtext::set_text(QString neuer_Text)
{
    text.set_text(neuer_Text);
    QString tmp = text.get_text();
    if(!tmp.contains(LISTENENDE))
    {
        text.zeile_anhaengen(LISTENENDE);
    }
    aktualisieren();
}

void programmtext::clear()
{
    text.clear();
    text_kopie.clear();
    clear_ausser_text();
}

void programmtext::clear_ausser_text()
{
    klartext.clear();
    var.clear();
    anzeigetext.clear();
    geo.clear();
    fkon.clear();
    werkstuecklaenge = 0;
    werkstueckbreite = 0;
    hat_programmkopf = false;
    hat_programmende = false;
    sicherheitsabstand = 5;
    min_x = 0;
    min_y = 0;
    max_x = 0;
    max_y = 0;
    anz_faufr = 0;
    anz_fabfa = 0;
    warnung_frDial = false;
    versatz_x = 0;
    versatz_y = 0;
    versatz_z = 0;
}

QString programmtext::get_klartext()
{
    QString returnstring;
    for(uint i=1 ; i<=klartext.zeilenanzahl() ; i++)
    {
        QString tmp = klartext.zeile(i);
        if(!tmp.isEmpty())
        {
            returnstring += tmp;
        }
    }
    return returnstring;
}

QString programmtext::get_variablen()
{
    QString returnstring;
    for(uint i=1 ; i<=var.zeilenanzahl() ; i++)
    {
        QString tmp = var.zeile(i);
        if(!tmp.isEmpty())
        {
            returnstring += tmp;
        }
    }
    return returnstring;
}

void programmtext::set_maschinengeometrie(text_zeilenweise tz)
{
    maschinengeo.clear();

    for(uint i=1; i<=tz.zeilenanzahl();i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile.contains(STRECKE))
        {
            strecke s(zeile);
            maschinengeo.add_strecke(s);
            maschinengeo.zeilenvorschub();
        }else if(zeile.contains(BOGEN))
        {
            bogen b(zeile);
            maschinengeo.add_bogen(b);
            maschinengeo.zeilenvorschub();
        }else if (zeile.contains(KREIS))
        {
            kreis k(zeile);
            maschinengeo.add_kreis(k);
            maschinengeo.zeilenvorschub();
        }
    }
}

//---------------------------------------
QString programmtext::zeile(uint zeilennummer)
{
    if(zeilennummer > text.zeilenanzahl())
    {
        return "Fehler! Ungueltige Zeilennummer";
    }else
    {
        return text.zeile(zeilennummer);
    }
}

QString programmtext::zeilen(uint zeilennummer_beginn, uint zeilenmenge)
{
    if(zeilennummer_beginn+zeilenmenge-1  > text.zeilenanzahl())
    {
        return "Fehler! Ungueltige Zeilennummer";
    }else
    {
        QString tmp;
        for(uint i=zeilennummer_beginn ; i<zeilennummer_beginn+zeilenmenge; i++)
        {
            if(!text.zeile(i).contains(LISTENENDE))
            {
                if(i!=zeilennummer_beginn)
                {
                    tmp += "\n";
                }
                tmp += text.zeile(i);
            }
        }
        return tmp;
    }
}

int programmtext::zeile_loeschen(uint zeilennummer)
{
    QString zeilentext = text.zeile(zeilennummer);
    if(zeilentext.contains(LISTENENDE))
    {
        return 0; //Listenende darf nicht gelöscht werden!
    }
    if(zeilennummer > text.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    text.zeile_loeschen(zeilennummer);
    aktualisieren();
    return 0; //Keine Fehler
}

int programmtext::zeilen_loeschen(uint zeilennummer_beginn, uint zeilenmenge)
{
    if(zeilennummer_beginn+zeilenmenge-1 > text.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    for(uint i=zeilennummer_beginn+zeilenmenge-1; i>=zeilennummer_beginn ; i--)
    {
        QString tmp = text.zeile(i);
        if(!tmp.contains(LISTENENDE))
        {
            text.zeile_loeschen(i);
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
    if(zeilennummer_vor_neuer_zeile > text.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    if(zeilennummer_vor_neuer_zeile == 0)
    {
        text.zeile_vorwegsetzen(zeilentext);
    }else
    {
        text.zeile_einfuegen(zeilennummer_vor_neuer_zeile, zeilentext);
    }
    aktualisieren();
    return 0; //Keine Fehler
}

int programmtext::zeilen_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext)
{
    if(zeilennummer_vor_neuer_zeile > text.zeilenanzahl())
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
            text.zeile_vorwegsetzen(zeile);
        }else
        {
            text.zeile_einfuegen(zeilennummer_vor_neuer_zeile+i-1, zeile);
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
    text.zeilen_anhaengen(zeilentext);
    aktualisieren();
}

int programmtext::zeile_ersaetzen(uint zeilennummer, QString neuer_zeilentext)
{
    QString alter_text;
    alter_text = text.zeile(zeilennummer);
    if(alter_text == LISTENENDE)
    {
        return 0;
    }
    QString zeilentext = text.zeile(zeilennummer);
    if(zeilentext.contains(LISTENENDE))
    {
        return 0; //Listenende darf nicht gelöscht werden!
    }
    if(zeilennummer > text.zeilenanzahl())
    {
        return 1; //Meldet Fehler in der Funktion
    }
    if(zeilennummer == 0)
    {
        return 1; //Meldet Fehler in der Funktion
    }
    text.zeile_ersaetzen(zeilennummer, neuer_zeilentext);
    aktualisieren();
    return 0; //Keine Fehler
}

//------------------------------------------------------------
//private:
bool programmtext::cagleich(punkt3d p1, punkt3d p2, double tolleranz = 0.1)
{
    if(  (  (p1.x() == p2.x()) || ((p1.x() - tolleranz <= p2.x()) && (p1.x() + tolleranz >= p2.x()))  )  && \
         (  (p1.y() == p2.y()) || ((p1.y() - tolleranz <= p2.y()) && (p1.y() + tolleranz >= p2.y()))  )  && \
         (  (p1.z() == p2.z()) || ((p1.z() - tolleranz <= p2.z()) && (p1.z() + tolleranz >= p2.z()))  )     )
    {
        return true;
    }else
    {
        return false;
    }
}

bool programmtext::get_hat_ungesicherte_inhalte()
{
    if(text.get_text().isEmpty())//Hat gar keine Inhalte
    {
        return false;
    }
    if(text_kopie.get_text() == text.get_text())//Inhalt wurde seit dem Speichern noch nicht verändert
    {
        return false;
    }else
    {
        return true;
    }
}

void programmtext::wurde_gespeichert()
{
    text_kopie = text;
}

void programmtext::aktualisieren()
{
    aktualisiere_klartext_var();
    aktualisiere_geo();
    aktualisiere_fraeserdarst();
    aktualisiere_fkon();
    aktualisiere_anzeigetext();
    aktualisiere_schleife_linear();
    aktualisiere_min_max();
}

void programmtext::aktualisiere_klartext_var()
{
    if(!aktualisieren_eingeschaltet)
    {
        return;
    }

    clear_ausser_text();
    QString variablen;
    for(uint i=1 ; i<=text.zeilenanzahl() ; i++)
    {
        QString zeile;
        zeile = text.zeile(i);

        if(  (zeile.at(0) == '/')  &&  (zeile.at(1) == '/')  )
        {
            klartext.zeilen_anhaengen(" ");
            var.zeilen_anhaengen(" ");
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
                if(  (hat_programmkopf == true)  &&  (warnungen_sind_eingeschaltet == true)  )
                {
                    QMessageBox mb;
                    mb.setText("Achtung!\nProgrammkopf mehrfach vorhanden!");
                    mb.exec();
                }
                hat_programmkopf = true;
                QString zeile_klartext;
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
            }
        }else if(zeile.contains(DLG_KOM))
        {
            QString zeile_klartext;
            zeile_klartext += DLG_KOM;
            zeile_klartext += text_mitte(zeile, KOM_BEZ, ENDPAR);

            klartext.zeilen_anhaengen(zeile_klartext);
            var.zeile_anhaengen(variablen);
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
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

                klartext.zeilen_anhaengen(zeile_klartext);
                var.zeile_anhaengen(variablen);
            }else
            {//Wenn AFB == 0;
                klartext.zeilen_anhaengen(" ");//leere Zeile
                var.zeile_anhaengen(variablen);
            }
        }else
        {
            klartext.zeilen_anhaengen(" ");//leere Zeile
            var.zeile_anhaengen(variablen);
        }
    }
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
    parwert = text_mitte(prgzeile, parname, ENDPAR);              //Parameter-Wert selektieren
    parwert = variablen_durch_werte_ersetzten(varlist, parwert);  //Variablen durch Werte ersetzen
    parwert = ausdruck_auswerten(parwert);                        //Ergebnis der Berechnung bekommen

    QString kt = parname;
    kt += parwert;
    kt += ENDPAR;

    if(varmerken == true)
    {
        if(!varlist.contains(varname))
        {
            varlist += varname;
            varlist += parwert;
            varlist += ENDPAR;
        }else
        {
            QString alterWert = text_mitte(varlist, varname, ENDPAR);
            varlist.replace(varname+alterWert, varname+parwert);
        }
    }

    return  kt;
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

    if(!aktualisieren_eingeschaltet)
    {
        return;
    }
    //Die Funktion "aktualisiere_klartext_var()" muss jeweils vorab aufgerufen worden sein!

    //CAD-Parameter ergänzen:
    if(warnung_frDial == false)
    {
        //QString abtyp = NICHT_DEFINIERT; //brauchen wir an dieser Stelle, damit der Wert später
                                         //beim Fräser-Abfahren verfügbar ist
        //float fdm=0;                     //Fräser-Durchmesser
        bool kantenansicht = false;

        for(uint i=1 ; i<=klartext.zeilenanzahl() ; i++)
        {
            QString zeile = klartext.zeile(i), tmp;

            if(zeile.isEmpty())
            {
                geo.zeilenvorschub();
            }else if(zeile.contains(DLG_PKOPF))
            {
                punkt3d nullpunkt(0,0,0);
                nullpunkt.set_linienbreite(15);
                geo.add_punkt(nullpunkt);

                rechteck3d rec;
                rec.set_bezugspunkt(UNTEN_LINKS);
                rec.set_einfuegepunkt(versatz_x,versatz_y,0);
                rec.set_laenge(get_werkstuecklaenge());
                rec.set_breite(get_werkstueckbreite());
                rec.set_farbe_fuellung(FARBE_GRAU);
                geo.add_rechteck(rec);

                //WST-Kanten anzeigen lassen:
                QString fuenfseiten = text_mitte(zeile, PKOPF_FUENFSEI, ENDPAR);
                if(fuenfseiten == "1")
                {
                    kantenansicht = true;
                    float abst = 20;
                    //Kante unten:
                    rec.set_einfuegepunkt(versatz_x,versatz_y-abst-get_werkstueckdicke(),0);
                    rec.set_breite(get_werkstueckdicke());
                    geo.add_rechteck(rec);

                    //Kante oben:
                    rec.set_einfuegepunkt(versatz_x,versatz_y+abst+get_werkstueckbreite(),0);
                    geo.add_rechteck(rec);

                    //Kante_links:
                    rec.set_einfuegepunkt(versatz_x-abst-get_werkstueckdicke(),versatz_y,0);
                    rec.set_laenge(get_werkstueckdicke());
                    rec.set_breite(get_werkstueckbreite());
                    geo.add_rechteck(rec);

                    //Kante_rechts:
                    rec.set_einfuegepunkt(versatz_x+abst+get_werkstuecklaenge(),versatz_y,0);
                    geo.add_rechteck(rec);
                }

                geo.zeilenvorschub();
            }else if(zeile.contains(DLG_PENDE))
            {
                geo.zeilenvorschub();
            }else if(zeile.contains(DLG_KOM))
            {
                geo.zeilenvorschub();
            }else if(zeile.contains(DLG_HALT))
            {
                geo.zeilenvorschub();
            }else if(zeile.contains(DLG_SPIEGELN))
            {
                geo.zeilenvorschub();
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
                geo.zeilenvorschub();

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
                if(boti<=0 || boti > get_werkstueckdicke())
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
                geo.add_kreis(k);
                geo.zeilenvorschub();
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
                if(boti<=0 || boti > get_werkstueckdicke())
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
                geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                        geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                        geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                        geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                        geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                        geo.add_kreis(k);
                    }
                }

                geo.zeilenvorschub();
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
                if(boti<=0 || boti > get_werkstueckdicke())
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
                geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                        geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                        geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                        geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                        geo.add_kreis(k);
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
                    geo.add_kreis(k);
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
                        geo.add_kreis(k);
                    }
                }

                geo.zeilenvorschub();
            }else if(zeile.contains(DLG_LOREIAE))
            {
                //...
                //...
                //...
                //...
                //...
                //...
                geo.zeilenvorschub();
            }else if(zeile.contains(DLG_LOREIMA))
            {
                double xs = text_mitte(zeile, LOREIMA_XS, ENDPAR).toDouble();
                double xm = text_mitte(zeile, LOREIMA_XM, ENDPAR).toDouble();
                double y1 = text_mitte(zeile, LOREIMA_Y1, ENDPAR).toDouble();
                double y2 = text_mitte(zeile, LOREIMA_Y2, ENDPAR).toDouble();
                double raster = text_mitte(zeile, LOREIMA_RASTER, ENDPAR).toDouble();
                float boti = text_mitte(zeile, LOREIMA_BOTI, ENDPAR).toFloat();
                kreis k;
                k.set_farbe(FARBE_SCHWARZ);
                if(boti<=0 || boti > get_werkstueckdicke())
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
                    k.set_radius(text_mitte(zeile, LOREIMA_DM, ENDPAR).toDouble()/2);

                    k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                    k = lageaendern_kreis(k, lageaendern_afb,\
                                          lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                          lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                          lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                          lageaendern_wi_alt, lageaendern_geswi_alt);
                    geo.add_kreis(k);

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
                        geo.add_kreis(k);
                    }
                }
                geo.zeilenvorschub();
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
                double to = text_mitte(zeile, TOPF_TODM, ENDPAR).toDouble();
                float boti = text_mitte(zeile, TOPF_BOTI, ENDPAR).toFloat();
                float toti = text_mitte(zeile, TOPF_TOTI, ENDPAR).toFloat();
                kreis kbo;
                kbo.set_farbe(FARBE_SCHWARZ);
                if(boti<=0 || boti > get_werkstueckdicke())
                {
                    kbo.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    kbo.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                kbo.set_stil(STIL_DURCHGEHEND);
                kreis kto;
                kto.set_farbe(FARBE_SCHWARZ);
                if(toti<=0 || toti > get_werkstueckdicke())
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

                }else if(seite == 2)//rechts
                {

                }else if(seite == 3)//oben
                {

                }else if(seite == 4)//links
                {

                }

                /*
                punkt3d mipu;
                mipu.set_x(text_mitte(zeile, TOPF_X, ENDPAR));
                mipu.set_y(text_mitte(zeile, TOPF_Y, ENDPAR));




                k.set_mittelpunkt(mipu);
                k.set_radius(text_mitte(zeile, TOPF_DM, ENDPAR).toDouble()/2);

                k = spiegeln_kreis(k, spiegeln_xbed, spiegeln_ybed, spiegeln_xpos, spiegeln_ypos);
                k = lageaendern_kreis(k, lageaendern_afb,\
                                      lageaendern_xalt, lageaendern_yalt, lageaendern_xneu, lageaendern_yneu,\
                                      lageaendern_wi, lageaendern_geswi, lageaendern_kettenmas,\
                                      lageaendern_xalt_alt, lageaendern_yalt_alt, lageaendern_xneu_alt, lageaendern_yneu_alt,\
                                      lageaendern_wi_alt, lageaendern_geswi_alt);
                geo.add_kreis(k);

                */



                geo.zeilenvorschub();
            }
        }
    }
}

void programmtext::aktualisiere_fraeserdarst()
{

}

void programmtext::aktualisiere_fkon()
{

}

void programmtext::aktualisiere_anzeigetext()
{
    if(!aktualisieren_eingeschaltet)
    {
        return;
    }

    anzeigetext.clear();
    for(uint i=1 ; i<=text.zeilenanzahl() ; i++)
    {
        QString zeile = text.zeile(i);
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
            anzeigetext.set_text(tmp);
        }else
        {
            anzeigetext.zeile_anhaengen(tmp);
        }
    }
}

void programmtext::aktualisiere_schleife_linear()
{

}

void programmtext::aktualisiere_min_max()
{
    min_x = 0;
    min_y = 0;
    max_x = 0;
    max_y = 0;
    //min und max berechnen:
    text_zeilenweise geotext = geo.get_text_zeilenweise();
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

            if(element.get_text().contains(PUNKT))
            {
                double x = element.zeile(2).toDouble();
                double y = element.zeile(3).toDouble();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
            }else if(element.get_text().contains(STRECKE))
            {
                double x = element.zeile(2).toDouble();
                double y = element.zeile(3).toDouble();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
                x = element.zeile(5).toDouble();
                y = element.zeile(6).toDouble();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
            }else if(element.get_text().contains(BOGEN))
            {
                double x = element.zeile(2).toDouble();
                double y = element.zeile(3).toDouble();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
                x = element.zeile(5).toDouble();
                y = element.zeile(6).toDouble();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
            }else if(element.get_text().contains(KREIS))
            {
                double rad = element.zeile(5).toDouble();
                double x = element.zeile(2).toDouble()-rad;
                double y = element.zeile(3).toDouble()-rad;
                if(x < min_x)
                {
                    min_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }
                x = x+rad*2;
                y = y+rad*2;
                if(x > max_x)
                {
                    max_x = x;
                }
                if(y > max_y)
                {
                    max_y = y;
                }
            }else if(element.get_text().contains(ZYLINDER))
            {
                double rad = element.zeile(5).toDouble();
                double x = element.zeile(2).toDouble()-rad;
                double y = element.zeile(3).toDouble()-rad;
                if(x < min_x)
                {
                    min_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }
                x = x+rad*2;
                y = y+rad*2;
                if(x > max_x)
                {
                    max_x = x;
                }
                if(y > max_y)
                {
                    max_y = y;
                }
            }else if(element.get_text().contains(RECHTECK3D))
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
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
                x = r.unr(false).x();
                y = r.unr(false).y();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
                x = r.obl(false).x();
                y = r.obl(false).y();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
                x = r.obr(false).x();
                y = r.obr(false).y();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
            }else if(element.get_text().contains(WUERFEL))
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
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
                x = r.unr(false).x();
                y = r.unr(false).y();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
                x = r.obl(false).x();
                y = r.obl(false).y();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
                x = r.obr(false).x();
                y = r.obr(false).y();
                if(x < min_x)
                {
                    min_x = x;
                }else if(x > max_x)
                {
                    max_x = x;
                }
                if(y < min_y)
                {
                    min_y = y;
                }else if(y > max_y)
                {
                    max_y = y;
                }
            }
        }
    }
    min_x -= 50;
    min_y -= 50;
    max_x += 50;
    max_y += 50;
}

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
            x = s.endp().x();
            y = s.endp().y();
        }
        x = x + ax;
        y = y + ay;
        mipu.set_x(x);
        mipu.set_y(y);
        k.set_mittelpunkt(mipu);
    }
    return  k;
}






