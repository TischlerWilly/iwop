#include "bogen.h"

bogen::bogen()
{
    Fehler = true;
}

bogen::bogen(punkt3d startpunkt, punkt3d endpunkt)
{
    set_startpunkt(startpunkt);
    set_endpunkt(endpunkt);
}

bogen::bogen(QString geotext)
{
    set_text(geotext);
}

bogen::bogen(punkt3d startpunkt, punkt3d endpunkt, \
             float radiuswert, bool im_uhrzeigersinn)
{
    set_startpunkt(startpunkt);
    set_endpunkt(endpunkt);
    set_radius(radiuswert, im_uhrzeigersinn);
}

bogen::bogen(punkt2d mipu, double rad, double startwinkel, double endwinkel)
{
    Rad = rad;
    punkt3d p;
    p.set_x(mipu.x());
    p.set_y(mipu.y());
    strecke ssp;
    ssp.set_start(p);
    p.set_x(mipu.x()+rad);
    ssp.set_ende(p);
    strecke sep = ssp;
    ssp.drenen_um_startpunkt_2d(startwinkel, false);
    sep.drenen_um_startpunkt_2d(endwinkel, false);
    Stapu = ssp.endpu();
    Endpu = sep.endpu();
    Bogen_im_uzs = false;

}

void bogen::set_text(QString geotext)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRZ_PA_);
    tz.set_text(geotext);
    punkt3d start;
    start.set_x(tz.zeile(2).toDouble());
    start.set_y(tz.zeile(3).toDouble());
    start.set_z(tz.zeile(4).toDouble());
    punkt3d ende;
    ende.set_x(tz.zeile(5).toDouble());
    ende.set_y(tz.zeile(6).toDouble());
    ende.set_z(tz.zeile(7).toDouble());
    float rad =tz.zeile(8).toFloat();
    bool uzs;
    if(tz.zeile(9).contains("ja"))
    {
        uzs = true;
    }else
    {
        uzs = false;
    }
    set_startpunkt(start);
    set_endpunkt(ende);
    set_radius(rad, uzs);
    set_farbe(tz.zeile(12));
    set_linienbreite(tz.zeile(13).toInt());
    set_stil(tz.zeile(14));
}

void bogen::set_startpunkt(punkt3d startpunkt)
{
    Stapu = startpunkt;
}

void bogen::set_endpunkt(punkt3d endpunkt)
{
    Endpu = endpunkt;
}

void bogen::set_radius(float radiuswert, bool im_uhrzeigersinn)
{
    Rad = radiuswert;
    Bogen_im_uzs = im_uhrzeigersinn;
}

void bogen::set_radius(float radiuswert, punkt2d bogenrichtung)
{

    //Es muss geprüft werden, ob der Punkt links oder rechts von der Strecke liegt,
    //die vom Bogenstart- bis Bogenendpunkt geht

    /*
     * p = (px-x1)*(y1-y2) + (py-y1)*(x2-x1)
     * p = 0 : Punkt auf Linie
     * p < 0 : Punkt unter Linie
     * p > 0 : Punkt über Linie
    */

    double px = bogenrichtung.x();
    double py = bogenrichtung.y();
    double x1 = start().x();
    double x2 = ende().x();
    double y1 = start().y();
    double y2 = ende().y();

    double p = ((px-x1)*(y1-y2)) + ((py-y1)*(x2-x1));

    if(p<0)
    {
        set_radius(radiuswert, false);
    }else if(p>0)
    {
        set_radius(radiuswert, true);
    }else
    {
        //if(p=0)
        //-->der Punkt "Bogenrichtung" liegt auf der Linie
        Fehler = true;
        Fehlertext = "Bogenrichtung nicht bestimmbar!";
    }
}

QString bogen::text()
{
    QString msg = BOGEN;
    msg += TRZ_PA;
    msg += start().x_QString();
    msg += TRZ_PA;
    msg += start().y_QString();
    msg += TRZ_PA;
    msg += start().z_QString();
    msg += TRZ_PA;
    msg += ende().x_QString();
    msg += TRZ_PA;
    msg += ende().y_QString();
    msg += TRZ_PA;
    msg += ende().z_QString();
    msg += TRZ_PA;
    msg += rad_qString();
    msg += TRZ_PA;
    msg += im_uzs_QString();
    msg += TRZ_PA;
    msg += mitte().x_QString();
    msg += TRZ_PA;
    msg += mitte().y_QString();
    msg += TRZ_PA;
    msg += farbe();
    msg += TRZ_PA;
    msg += linienbreite_qstring();
    msg += TRZ_PA;
    msg += stil();

    return msg;
}

void bogen::richtung_unkehren()
{
    punkt3d tmp = Stapu;
    Stapu = Endpu;
    Endpu = tmp;

    if(Bogen_im_uzs == true)
    {
        Bogen_im_uzs = false;
    }else
    {
        Bogen_im_uzs = true;
    }
}

void bogen::verschieben_um(double xversatz, double yversatz)
{
    //if(hat_fehler() == false)
    //{
        Stapu.verschieben_um(xversatz, yversatz);
        Endpu.verschieben_um(xversatz, yversatz);
    //}
}

double bogen::bogenwinkel()
{
    return winkel(start(), mitte(), ende());
}

punkt2d bogen::mitte()
{
    punkt2d mittelp;
    punkt2d pstart(Stapu); //Z-Werte sollen hier ignoriert werden
    punkt2d pende(Endpu);    //Z-Werte sollen hier ignoriert werden
    strecke stre_spep;
    stre_spep.set_start(Stapu);
    stre_spep.set_ende(Endpu);
    double laenge = stre_spep.laenge2d();
    Fehler = false;
    if(  start() == ende()  )
    {
        Fehler = true;
        Fehlertext = "Fehler! Start und Endpunkt sind deckungsgleich!";
    }else if( rad() <= 0)
    {
        Fehler = true;
        Fehlertext = "Fehler! Radius <= 0!";
    }else if( rad() < laenge/2)
    {
        Fehler = true;
        Fehlertext = "Fehler! Radius zu klein für Punktabstand Start-Ende";
    }else if( rad() == laenge/2)
    {
        mittelp = stre_spep.mitpu2d();
    }else
    {
        double a = stre_spep.laenge2d()/2; //Hälfte des Abstandes von
                                             //Start und Endpunkt
        double r = rad();
        double x = sqrt(r*r - a*a)*2; //Länge der Mittelsenkrechtenn zu stre_spep

        strecke stre_tmp = stre_spep;
        stre_tmp.drenen_um_mittelpunkt_2d(90,true);
        stre_tmp.set_laenge_2d(x, strecke_bezugspunkt_mitte);

        if(im_uzs() == false)
        {
            mittelp.set_x(stre_tmp.stapu().x());
            mittelp.set_y(stre_tmp.stapu().y());
        }else
        {
            mittelp.set_x(stre_tmp.endpu().x());
            mittelp.set_y(stre_tmp.endpu().y());
        }
    }

    if(Fehler == false)
    {
        return mittelp;
    }else
    {
        punkt2d tmp;
        tmp.set_x(0);
        tmp.set_y(0);
        return tmp;
    }
}

void bogen::set_bogenwinkel(double wi, bogen_bezugspunkt bezug)
{
    if(Fehler == true)
    {
        return;
    }else
    {
        if(bezug == bogen_bezugspunkt_start)
        {
            strecke s;
            s.set_start(mitte());
            s.set_ende(start());
            s.drenen_um_startpunkt_2d(wi, im_uzs());
            set_endpunkt(s.endpu());
        }else if(bezug == bogen_bezugspunkt_ende)
        {
            strecke s;
            s.set_start(mitte());
            s.set_ende(ende());
            s.drenen_um_startpunkt_2d(wi, !im_uzs());
            set_startpunkt(s.endpu());
        }else
        {
            strecke s;
            s.set_start(start());
            s.set_ende(ende());
            s.set_ende(s.mitpu3d());
            s.set_start(mitte());
            s.set_laenge_2d(rad(), strecke_bezugspunkt_start);
            s.drenen_um_startpunkt_2d(wi/2, im_uzs());
            set_endpunkt(s.endpu());
            s.drenen_um_startpunkt_2d(wi, !im_uzs());
            set_startpunkt(s.endpu());
        }
    }
}

void bogen::mb()
{
    QString msg;
    msg = "Bogenwerte:\n\n";
    msg += "Mittelpunkt:\n";
    msg += "X= ";
    msg += mitte().x_QString();
    msg += "\nY= ";
    msg += mitte().y_QString();
    msg += "\n\nStartpunkt:\n";
    msg += "X= ";
    msg += start().x_QString();
    msg += "\nY= ";
    msg += start().y_QString();
    msg += "\n\nEntpunkt:\n";
    msg += "X= ";
    msg += ende().x_QString();
    msg += "\nY= ";
    msg += ende().y_QString();
    msg += "\n\nRadius:\n";
    msg += rad_qString();
    msg += "\n\nBogenwinkel:\n";
    msg += double_to_qstring(bogenwinkel());
    msg += "\n\nFehlermeldungen:\n";
    msg += Fehlertext;

    QMessageBox mb;
    mb.setText(msg);
    mb.exec();
}
