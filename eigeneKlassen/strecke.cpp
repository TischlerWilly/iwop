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
    start = startpunkt;
}

void strecke::set_start(punkt2d startpunkt)
{
    punkt3d p;
    p.set_x(startpunkt.x());
    p.set_y(startpunkt.y());
    start = p;
}

void strecke::set_ende(punkt3d endpunkt)
{
    ende = endpunkt;
}

void strecke::set_ende(punkt2d endpunkt)
{
    punkt3d p;
    p.set_x(endpunkt.x());
    p.set_y(endpunkt.y());
    ende = p;
}

void strecke::richtung_unkehren()
{
    punkt3d tmp = start;
    start = ende;
    ende = tmp;
}

double strecke::laenge_3d(punkt3d sp, punkt3d ep)
{
    punkt3d p3 = ep - sp;
    return sqrt(p3.x()*p3.x() + p3.y()*p3.y() + p3.z()*p3.z());
                //Wurzel aus (a²+b²+c²)
}

double strecke::laenge_2d(punkt3d sp, punkt3d ep)
{
    punkt2d spu(sp);
    punkt2d epu(ep);
    punkt2d p2 = epu-spu;
    return sqrt(p2.x()*p2.x() + p2.y()*p2.y()); //Wurzel aus (a²+b²)
}

punkt3d strecke::get_mittelpunkt3d()
{
    return start + ((ende-start)/2);
}

punkt2d strecke::get_mittelpunkt2d()
{
    punkt2d sta(start);
    punkt2d end(ende);
    return sta + ((end-sta)/2);
}

void strecke::drenen_um_mittelpunkt_2d(double drehwinkel, \
                                    bool drehrichtung_im_uhrzeigersinn)
{
    punkt2d sp(start);
    punkt2d ep(ende);
    punkt2d mp = get_mittelpunkt2d();
    sp = drehen(mp, sp, drehwinkel, drehrichtung_im_uhrzeigersinn);
    ep = drehen(mp, ep, drehwinkel, drehrichtung_im_uhrzeigersinn);
    punkt3d tmp;
    tmp.set_x(sp.x());
    tmp.set_y(sp.y());
    tmp.set_z(start.z());
    set_start(tmp);
    tmp.set_x(ep.x());
    tmp.set_y(ep.y());
    tmp.set_z(ende.z());
    set_ende(tmp);
}

void strecke::drenen_um_startpunkt_2d(double drehwinkel, bool drehrichtung_im_uhrzeigersinn)
{
    punkt2d sp(start);
    punkt2d ep(ende);
    ep = drehen(sp, ep, drehwinkel, drehrichtung_im_uhrzeigersinn);
    punkt3d tmp;
    tmp.set_x(ep.x());
    tmp.set_y(ep.y());
    tmp.set_z(ende.z());
    set_ende(tmp);
}

void strecke::drenen_um_endpunkt_2d(double drehwinkel, bool drehrichtung_im_uhrzeigersinn)
{
    punkt2d sp(start);
    punkt2d ep(ende);
    sp = drehen(ep, sp, drehwinkel, drehrichtung_im_uhrzeigersinn);
    punkt3d tmp;
    tmp.set_x(sp.x());
    tmp.set_y(sp.y());
    tmp.set_z(start.z());
    set_start(tmp);
}

void strecke::set_laenge_2d(double neue_laenge, strecke_bezugspunkt bezugspunkt)
{
    double skalfakt = neue_laenge/laenge_2d(startp(), endp());

    switch(bezugspunkt)
    {
    case strecke_bezugspunkt_start:
    {
        punkt2d sp(start);
        punkt2d ep(ende);
        punkt2d p2;
        punkt3d p3;
        p2 = ep-sp;
        p2 = p2*skalfakt;
        ep = sp+p2;
        p3.set_x(ep.x());
        p3.set_y(ep.y());
        p3.set_z(ende.z());
        set_ende(p3);
    }
        break;
    case strecke_bezugspunkt_mitte:
    {
        punkt2d mp = get_mittelpunkt2d();
        punkt2d sp(start);
        punkt2d ep(ende);

        punkt2d p2e;//Endpunkt
        punkt3d p3e;//Endpunkt
        p2e = ep-mp;
        p2e = p2e*skalfakt;
        ep = mp+p2e;
        p3e.set_x(ep.x());
        p3e.set_y(ep.y());
        p3e.set_z(ende.z());
        set_ende(p3e);

        punkt2d p2s; //Startpunkt
        punkt3d p3s; //Startpunkt
        p2s = sp-mp;
        p2s = p2s*skalfakt;
        sp = mp+p2s;
        p3s.set_x(sp.x());
        p3s.set_y(sp.y());
        p3s.set_z(start.z());
        set_start(p3s);
    }
        break;
    case strecke_bezugspunkt_ende:
    {
        punkt2d sp(start);
        punkt2d ep(ende);
        punkt2d p2;
        punkt3d p3;
        p2 = sp-ep;
        p2 = p2*skalfakt;
        sp = ep+p2;
        p3.set_x(sp.x());
        p3.set_y(sp.y());
        p3.set_z(start.z());
        set_start(p3);
    }
        break;
    }
}

void strecke::verschieben_um(double xversatz, double yversatz)
{
    start.verschieben_um(xversatz, yversatz);
    ende.verschieben_um(xversatz, yversatz);
}

QString strecke::get_text()
{
    QString msg = STRECKE;
    msg += TRZ_PA;
    msg += startp().x_QString();
    msg += TRZ_PA;
    msg += startp().y_QString();
    msg += TRZ_PA;
    msg += startp().z_QString();
    msg += TRZ_PA;
    msg += endp().x_QString();
    msg += TRZ_PA;
    msg += endp().y_QString();
    msg += TRZ_PA;
    msg += endp().z_QString();
    msg += TRZ_PA;
    msg += get_farbe();
    msg += TRZ_PA;
    msg += get_linienbreite_qstring();
    msg += TRZ_PA;
    msg += get_stil();

    return msg;
}

double strecke::get_winkel()
{
    double w = 0;
    if(startp() == endp())
    {
        w = 0;
    }else if(startp().y() == endp().y())
    {
        if(startp().x() < endp().x())
        {
            w = 0;
        }else
        {
            w = 180;
        }
    }else if(startp().x() == endp().x())
    {
        if(startp().y() < endp().y())
        {
            w = 90;
        }else
        {
            w = 270;
        }
    }else
    {
        w = winkel(endp().x(), endp().y(),\
                   startp().x(), startp().y());
    }

    return w;
}

double strecke::get_abst_gerade(punkt3d p)
{
    //Strecke in Vektorenform bringen:
    //Gerade = ortsvektor + (var * Richtungsvektor)
    //Gerade =     sp     + (var * (ep-sp))
    punkt3d ov; //Ortsvektor
    ov = startp();
    punkt3d rv; //Richtungsvektor
    rv.set_x(  endp().x() - startp().x()  );
    rv.set_y(  endp().y() - startp().y()  );
    rv.set_z(  endp().z() - startp().z()  );
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
    //                        3  * (  2  +   3 * s )
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
    //  var = (-g)/h
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

    return laenge_3d(p, pp);
}

double strecke::get_abst(punkt3d p)
{
    return get_abst_gerade(p);
    //dies ist falsch wenn der Punkt nicht im Bereich zwischen sp und ep liegt, weil die Strecke dann verlänger wird
}

double strecke::get_abst(punkt2d p)
{
    punkt3d p3d;
    p3d.set_x(p.x());
    p3d.set_y(p.y());
    return  get_abst(p3d);
}












