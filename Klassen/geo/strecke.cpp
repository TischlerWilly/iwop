#include "strecke.h"

strecke::strecke()
{
    punkt3d p;
    p.set_x(0);
    p.set_y(0);
    p.set_z(0);
    set_start(p);
    set_ende(p);
}

strecke::strecke(QString geotext)
{
    set_text(geotext);
}

//-----------------------------------------set_xy:
void strecke::set_text(QString geotext)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRZ_PA_);
    tz.set_text(geotext);
    punkt3d p;
    p.set_x(tz.zeile(2).toDouble());
    p.set_y(tz.zeile(3).toDouble());
    p.set_z(tz.zeile(4).toDouble());
    set_start(p);
    p.set_x(tz.zeile(5).toDouble());
    p.set_y(tz.zeile(6).toDouble());
    p.set_z(tz.zeile(7).toDouble());
    set_ende(p);
    set_farbe(tz.zeile(8));
    set_linienbreite(tz.zeile(9).toInt());
    set_stil(tz.zeile(10));
}
void strecke::set_start(punkt3d startpunkt)
{
    Stapu = startpunkt;
}
void strecke::set_start(punkt2d startpunkt)
{
    punkt3d p;
    p.set_x(startpunkt.x());
    p.set_y(startpunkt.y());
    Stapu = p;
}
void strecke::set_ende(punkt3d endpunkt)
{
    Endpu = endpunkt;
}
void strecke::set_ende(punkt2d endpunkt)
{
    punkt3d p;
    p.set_x(endpunkt.x());
    p.set_y(endpunkt.y());
    Endpu = p;
}

//-----------------------------------------get_xy:
punkt3d strecke::mitpu3d()
{
    return Stapu + ((Endpu-Stapu)/2);
}
punkt2d strecke::mitpu2d()
{
    punkt2d sta(Stapu);
    punkt2d end(Endpu);
    return sta + ((end-sta)/2);
}
punkt3d strecke::schnittp_zur_senkr_an_p(punkt3d p)
{
    //Die Strecke wird unendlich verlängert zu einer Geraden
    //es wird eine Senkrechte zur Gerade gezeichnet die durch den Punkt p verläuft
    //Diese Funktoin liefet den Schnittpunkt der Senkechten auf der Gerade zurück

    //Strecke in Vektorenform bringen:
    //Gerade = ortsvektor + (var * Richtungsvektor)
    //Gerade =     sp     + (var * (ep-sp))
    punkt3d ov; //Ortsvektor
    ov = stapu();
    punkt3d rv; //Richtungsvektor
    rv.set_x(  endpu().x() - stapu().x()  );
    rv.set_y(  endpu().y() - stapu().y()  );
    rv.set_z(  endpu().z() - stapu().z()  );
    // Gerade = ov   + (var * rv  )
    //          ov.x          rv.x   --> ov.x + (var * rv.x)
    //          ov.y + (var * rv.y)  --> ov.y + (var * rv.y)
    //          ov.z          rv.z   --> ov.z + (var * rv.z)

    //  rv   * (Gerade - p  ) = 0
    //  rv.x             p.x
    //  rv.y * (Gerade - p.y) = 0
    //  rv.z             p.z

    // Ausmultiplizienen
    //((rv.x * gerade.x) + (rv.y * gerade.y) + (rv.z * gerade.z)) - ( (rv.x * p.x) + (rv.y * p.y) + (rv.z * p.z) ) = 0
    //((rv.x * gerade.x) + (rv.y * gerade.y) + (rv.z * gerade.z)) - (                    hans                    ) = 0
    double hans = ( rv.x() * p.x() ) + (rv.y() * p.y() ) + (rv.z() * p.z() );

    //((rv.x * gerade.x) + (rv.y * gerade.y) + (rv.z * gerade.z)) - hans = 0
    //     Beispielzahlen:    3  * (  2  +   3 * s )
    //(rv.x * gerade.x) --> rv.x * (ov.x + rv.x*var)
    //                             6 +  9s
    //rv.x * ov.x + (rv.x*rv.x*var)
    //(rv.x * ov.x + (rv.x*rv.x*var)) + (rv.y * ov.y + (rv.y*rv.y*var)) + (rv.z * ov.z + (rv.z*rv.z*var)) - hans = 0
    //    a        + (rv.x*rv.x*var)) + (      b     + (rv.y*rv.y*var)) + (     c      + (rv.z*rv.z*var)) - hans = 0
    //    a        + (    d    *var)) + (      b     + (     e *  var)) + (     c      + (     f *  var)) - hans = 0
    //    a + (d * var) + b + (e *  var) + c + (f *  var) - hans = 0
    //    a + b + c - hans  + ((d+e+f)*var )  = 0
    //          g           +  (   h  *var )  = 0   /-g
    //                    h * var = -g              /:h
    //                        var = (-g)/h
    double a = rv.x() * ov.x();
    double b = rv.y() * ov.y();
    double c = rv.z() * ov.z();
    double d = rv.x() * rv.x();
    double e = rv.y() * rv.y();
    double f = rv.z() * rv.z();
    double g = a + b + c - hans;
    double h = d + e + f;
    double var = (-1 * g)/h;

    //var in gerade einsetzen
    // Gerade = ov   + (var * rv  )
    punkt3d pp; //Punkt auf der Geraden an dem die Senkrechte linie zum Punkt P beginnt
    pp.set_x(  ov.x() + (var * rv.x())  );
    pp.set_y(  ov.y() + (var * rv.y())  );
    pp.set_z(  ov.z() + (var * rv.z())  );

    return pp;
}

double strecke::laenge3d(punkt3d sp, punkt3d ep)
{
    punkt3d p3 = ep - sp;
    return sqrt(p3.x()*p3.x() + p3.y()*p3.y() + p3.z()*p3.z());
                //Wurzel aus (a²+b²+c²)
}
double strecke::laenge2d(punkt3d sp, punkt3d ep)
{
    punkt2d spu(sp);
    punkt2d epu(ep);
    punkt2d p2 = epu-spu;
    return sqrt(p2.x()*p2.x() + p2.y()*p2.y()); //Wurzel aus (a²+b²)
}
double strecke::wink()
{
    double w = 0;
    if(stapu() == endpu())
    {
        w = 0;
    }else if(stapu().y() == endpu().y())
    {
        if(stapu().x() < endpu().x())
        {
            w = 0;
        }else
        {
            w = 180;
        }
    }else if(stapu().x() == endpu().x())
    {
        if(stapu().y() < endpu().y())
        {
            w = 90;
        }else
        {
            w = 270;
        }
    }else
    {
        w = winkel(endpu().x(), endpu().y(),\
                   stapu().x(), stapu().y());
    }

    return w;
}
double strecke::abst(punkt3d p)
{
    double abst = 999999;

    if(auf_strecke(p))
    {
        abst = 0;
    }else
    {
        punkt3d pp;
        pp = schnittp_zur_senkr_an_p(p);

        if(auf_strecke(pp))
        {
            abst = laenge3d(p, pp);
        }else
        {
            double abst_sp = laenge3d(stapu(),p);
            double abst_ep = laenge3d(endpu(),p);
            if(abst_sp < abst_ep)
            {
                abst = abst_sp;
            }else
            {
                abst = abst_ep;
            }
        }
    }
    return abst;
}
double strecke::abst(punkt2d p)
{
    punkt3d p3d;
    p3d.set_x(p.x());
    p3d.set_y(p.y());
    return  abst(p3d);
}
bool strecke::auf_strecke(punkt3d p)
{
    bool ergebnis;

    punkt3d ov; //Ortsvektor
    ov = stapu();
    punkt3d rv; //Richtungsvektor
    rv.set_x(  endpu().x() - stapu().x()  );
    rv.set_y(  endpu().y() - stapu().y()  );
    rv.set_z(  endpu().z() - stapu().z()  );

    // Gerade = ov   + (var * rv  )
    //Punkt = Gerade in die Gleichung setzen
    //   p    = ov   + (var * rv  )
    //   p.x  = ov.x          rv.x   --> p.x  = ov.x + (var * rv.x)
    //   p.y  = ov.y + (var * rv.y)  --> p.y  = ov.y + (var * rv.y)
    //   p.z  = ov.z          rv.z   --> p.z  = ov.z + (var * rv.z)

    //Der Punkt liegt auf der Gerade wenn alle 3 Gleichungen der gleiche Ergebnis haben
    //   p.x  = ov.x + (var * rv.x)  /-ov.x
    //   p.x - ov.x = var * rv.x     /:rv.x
    //   (p.x - ov.x):rv.x = var
    double var_x = (p.x() - ov.x()) / rv.x();
    double var_y = (p.y() - ov.y()) / rv.y();
    double var_z = (p.z() - ov.z()) / rv.z();

    if(var_x == var_y == var_z)
    {
        double var = var_x;
        if(  (0 <= var)  && (var <= 1)  )
        {
            ergebnis = true; //Punkt liegt auf der Strecke
        }else
        {
            ergebnis = false; //Punkt liegt zwar auf der Geraden, jedoch vor dem Start oder nach dem Endpunkt
        }
    }else
    {
        ergebnis = false; //Punkt liegt nicht auf der Geraden und somit auch nicht auf der Strecke
    }
    return ergebnis;
}

QString strecke::text()
{
    QString msg = STRECKE;
    msg += TRZ_PA;
    msg += stapu().x_QString();
    msg += TRZ_PA;
    msg += stapu().y_QString();
    msg += TRZ_PA;
    msg += stapu().z_QString();
    msg += TRZ_PA;
    msg += endpu().x_QString();
    msg += TRZ_PA;
    msg += endpu().y_QString();
    msg += TRZ_PA;
    msg += endpu().z_QString();
    msg += TRZ_PA;
    msg += farbe();
    msg += TRZ_PA;
    msg += linienbreite_qstring();
    msg += TRZ_PA;
    msg += stil();

    return msg;
}

//-----------------------------------------manipulationen:
void strecke::richtung_unkehren()
{
    punkt3d tmp = Stapu;
    Stapu = Endpu;
    Endpu = tmp;
}
void strecke::drenen_um_startpunkt_2d(double drehwi, bool drehri_im_uzs)
{
    punkt2d sp(Stapu);
    punkt2d ep(Endpu);
    ep = drehen(sp, ep, drehwi, drehri_im_uzs);
    punkt3d tmp;
    tmp.set_x(ep.x());
    tmp.set_y(ep.y());
    tmp.set_z(Endpu.z());
    set_ende(tmp);
}
void strecke::drenen_um_endpunkt_2d(double drehwi, bool drehri_im_uzs)
{
    punkt2d sp(Stapu);
    punkt2d ep(Endpu);
    sp = drehen(ep, sp, drehwi, drehri_im_uzs);
    punkt3d tmp;
    tmp.set_x(sp.x());
    tmp.set_y(sp.y());
    tmp.set_z(Stapu.z());
    set_start(tmp);
}
void strecke::drenen_um_mittelpunkt_2d(double drehwi, bool drehri_im_uzs)
{
    punkt2d sp(Stapu);
    punkt2d ep(Endpu);
    punkt2d mp = mitpu2d();
    sp = drehen(mp, sp, drehwi, drehri_im_uzs);
    ep = drehen(mp, ep, drehwi, drehri_im_uzs);
    punkt3d tmp;
    tmp.set_x(sp.x());
    tmp.set_y(sp.y());
    tmp.set_z(Stapu.z());
    set_start(tmp);
    tmp.set_x(ep.x());
    tmp.set_y(ep.y());
    tmp.set_z(Endpu.z());
    set_ende(tmp);
}
void strecke::set_laenge_2d(double neue_laenge, strecke_bezugspunkt bezugspunkt)
{
    double skalfakt = neue_laenge/laenge2d(stapu(), endpu());

    switch(bezugspunkt)
    {
    case strecke_bezugspunkt_start:
    {
        punkt2d sp(Stapu);
        punkt2d ep(Endpu);
        punkt2d p2;
        punkt3d p3;
        p2 = ep-sp;
        p2 = p2*skalfakt;
        ep = sp+p2;
        p3.set_x(ep.x());
        p3.set_y(ep.y());
        p3.set_z(Endpu.z());
        set_ende(p3);
    }
        break;
    case strecke_bezugspunkt_mitte:
    {
        punkt2d mp = mitpu2d();
        punkt2d sp(Stapu);
        punkt2d ep(Endpu);

        punkt2d p2e;//Endpunkt
        punkt3d p3e;//Endpunkt
        p2e = ep-mp;
        p2e = p2e*skalfakt;
        ep = mp+p2e;
        p3e.set_x(ep.x());
        p3e.set_y(ep.y());
        p3e.set_z(Endpu.z());
        set_ende(p3e);

        punkt2d p2s; //Startpunkt
        punkt3d p3s; //Startpunkt
        p2s = sp-mp;
        p2s = p2s*skalfakt;
        sp = mp+p2s;
        p3s.set_x(sp.x());
        p3s.set_y(sp.y());
        p3s.set_z(Stapu.z());
        set_start(p3s);
    }
        break;
    case strecke_bezugspunkt_ende:
    {
        punkt2d sp(Stapu);
        punkt2d ep(Endpu);
        punkt2d p2;
        punkt3d p3;
        p2 = sp-ep;
        p2 = p2*skalfakt;
        sp = ep+p2;
        p3.set_x(sp.x());
        p3.set_y(sp.y());
        p3.set_z(Stapu.z());
        set_start(p3);
    }
        break;
    }
}
void strecke::verschieben_um(double xversatz, double yversatz)
{
    Stapu.verschieben_um(xversatz, yversatz);
    Endpu.verschieben_um(xversatz, yversatz);
}


//-----------------------------------------















