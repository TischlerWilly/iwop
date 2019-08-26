#include "programmtext.h"

//------------------------------------------------------------
//public:
programmtext::programmtext()
{
    clear();
    warnungen_einschalten(true);
    aktualisieren_ein_aus(true);
    aktualisieren_fkon_ein_aus(false);
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
        QString zeile = text.zeile(i);
        if(  (zeile.at(0) == '/')  &&  (zeile.at(1) == '/')  )
        {
            klartext.zeilen_anhaengen("");
            var.zeilen_anhaengen("");
            continue;//Ausgeblendete Zeile überspringen
        }
        if(zeile.contains(DLG_PKOPF))
        {

        }else
        {
            klartext.zeilen_anhaengen(" ");
            var.zeilen_anhaengen(" ");
        }
    }
}

void programmtext::aktualisiere_geo()
{

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
}









