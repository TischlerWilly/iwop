#include "rechteck3d.h"

rechteck3d::rechteck3d()
{
    set_bezugspunkt(MITTE);
    set_einfuegepunkt(0,0,0);
    set_laenge(0);
    set_breite(0);
    set_rad(0);
    set_drewi(0);
}
rechteck3d::rechteck3d(QString geotext)
{
    set_text(geotext);
}

//--------------------------------------------------set_xy:
void rechteck3d::set_text(QString geotext)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRZ_PA_);
    tz.set_text(geotext);
    set_bezugspunkt(tz.zeile(2).toInt());
    punkt3d p;
    p.set_x(tz.zeile(3).toDouble());
    p.set_y(tz.zeile(4).toDouble());
    p.set_z(tz.zeile(5).toDouble());
    set_einfuegepunkt(p);
    set_laenge(tz.zeile(6).toDouble());
    set_breite(tz.zeile(7).toDouble());
    set_rad(tz.zeile(8).toDouble());
    set_drewi(tz.zeile(9).toDouble());
    set_farbe(tz.zeile(10));
    set_farbe_fuellung(tz.zeile(11));
    set_linienbreite(tz.zeile(12).toInt());
    set_stil(tz.zeile(13));
}
void rechteck3d::set_mipu(double x, double y, double z=0)
{
    Unli.set_x(x - Laenge/2);
    Obli.set_x(x - Laenge/2);
    Links.set_x(x -Laenge/2);
    Unre.set_x(x + Laenge/2);
    Obre.set_x(x + Laenge/2);
    Rechts.set_x(x + Laenge/2);
    Mitte.set_x(x);
    Oben.set_x(x);
    Unten.set_x(x);

    Unli.set_y(y - Breite/2);
    Unre.set_y(y - Breite/2);
    Unten.set_y(y - Breite/2);
    Obre.set_y(y + Breite/2);
    Obli.set_y(y + Breite/2);
    Oben.set_y(y + Breite/2);
    Mitte.set_y(y);
    Links.set_y(y);
    Rechts.set_y(y);

    switch(Bezugspunkt)
    {
        case OBEN_LINKS:
            Einfuegepunkt = Obli;
            break;
        case OBEN:
            Einfuegepunkt = Oben;
            break;
        case OBEN_RECHTS:
            Einfuegepunkt = Obre;
            break;
        case LINKS:
            Einfuegepunkt = Links;
            break;
        case MITTE:
            Einfuegepunkt = Mitte;
            break;
        case RECHTS:
            Einfuegepunkt = Rechts;
            break;
        case UNTEN_LINKS:
            Einfuegepunkt = Unli;
            break;
        case UNTEN:
            Einfuegepunkt = Unten;
            break;
        case UNTEN_RECHTS:
            Einfuegepunkt = Unre;
            break;
    }
}
void rechteck3d::set_mipu(punkt3d p)
{
    set_mipu(p.x(), p.y(), p.z());
}
void rechteck3d::set_z(double z)
{
    Obli.set_z(z);
    Oben.set_z(z);
    Obre.set_z(z);
    Links.set_z(z);
    Mitte.set_z(z);
    Rechts.set_z(z);
    Unli.set_z(z);
    Unten.set_z(z);
    Unre.set_z(z);
}
void rechteck3d::set_laenge(double neue_laenge)
{
    Laenge = neue_laenge;
    switch(Bezugspunkt)
    {
        case LINKS:
        case UNTEN_LINKS:
        case OBEN_LINKS:
            Unli.set_x(Einfuegepunkt.x());
            Obli.set_x(Einfuegepunkt.x());
            Links.set_x(Einfuegepunkt.x());
            Unre.set_x(Einfuegepunkt.x() + neue_laenge);
            Obre.set_x(Einfuegepunkt.x() + neue_laenge);
            Rechts.set_x(Einfuegepunkt.x() + neue_laenge);
            Mitte.set_x(Einfuegepunkt.x() + neue_laenge/2);
            Oben.set_x(Einfuegepunkt.x() + neue_laenge/2);
            Unten.set_x(Einfuegepunkt.x() + neue_laenge/2);
            break;
        case RECHTS:
        case UNTEN_RECHTS:
        case OBEN_RECHTS:
            Unli.set_x(Einfuegepunkt.x() - neue_laenge);
            Obli.set_x(Einfuegepunkt.x() - neue_laenge);
            Links.set_x(Einfuegepunkt.x() - neue_laenge);
            Unre.set_x(Einfuegepunkt.x());
            Obre.set_x(Einfuegepunkt.x());
            Rechts.set_x(Einfuegepunkt.x());
            Mitte.set_x(Einfuegepunkt.x() - neue_laenge/2);
            Oben.set_x(Einfuegepunkt.x() - neue_laenge/2);
            Unten.set_x(Einfuegepunkt.x() - neue_laenge/2);
            break;
        case OBEN:
        case UNTEN:
        case MITTE:
            Unli.set_x(Einfuegepunkt.x() - neue_laenge/2);
            Obli.set_x(Einfuegepunkt.x() - neue_laenge/2);
            Links.set_x(Einfuegepunkt.x() - neue_laenge/2);
            Unre.set_x(Einfuegepunkt.x() + neue_laenge/2);
            Obre.set_x(Einfuegepunkt.x() + neue_laenge/2);
            Rechts.set_x(Einfuegepunkt.x() + neue_laenge/2);
            Mitte.set_x(Einfuegepunkt.x());
            Oben.set_x(Einfuegepunkt.x());
            Unten.set_x(Einfuegepunkt.x());
            break;
    }
}
void rechteck3d::set_breite(double neue_breite)
{
    Breite = neue_breite;
    switch(Bezugspunkt)
    {
        case UNTEN:
        case UNTEN_LINKS:
        case UNTEN_RECHTS:
            Unli.set_y(Einfuegepunkt.y());
            Unre.set_y(Einfuegepunkt.y());
            Unten.set_y(Einfuegepunkt.y());
            Obre.set_y(Einfuegepunkt.y() + neue_breite);
            Obli.set_y(Einfuegepunkt.y() + neue_breite);
            Oben.set_y(Einfuegepunkt.y() + neue_breite);
            Mitte.set_y(Einfuegepunkt.y() + neue_breite/2);
            Links.set_y(Einfuegepunkt.y() + neue_breite/2);
            Rechts.set_y(Einfuegepunkt.y() + neue_breite/2);
            break;
        case OBEN:
        case OBEN_LINKS:
        case OBEN_RECHTS:
            Unli.set_y(Einfuegepunkt.y() - neue_breite);
            Unre.set_y(Einfuegepunkt.y() - neue_breite);
            Unten.set_y(Einfuegepunkt.y() - neue_breite);
            Obre.set_y(Einfuegepunkt.y());
            Obli.set_y(Einfuegepunkt.y());
            Oben.set_y(Einfuegepunkt.y());
            Mitte.set_y(Einfuegepunkt.y() - neue_breite/2);
            Links.set_y(Einfuegepunkt.y() - neue_breite/2);
            Rechts.set_y(Einfuegepunkt.y() - neue_breite/2);
            break;
        case LINKS:
        case RECHTS:
        case MITTE:
            Unli.set_y(Einfuegepunkt.y() - neue_breite/2);
            Unre.set_y(Einfuegepunkt.y() - neue_breite/2);
            Unten.set_y(Einfuegepunkt.y() - neue_breite/2);
            Obre.set_y(Einfuegepunkt.y() + neue_breite/2);
            Obli.set_y(Einfuegepunkt.y() + neue_breite/2);
            Oben.set_y(Einfuegepunkt.y() + neue_breite/2);
            Mitte.set_y(Einfuegepunkt.y());
            Links.set_y(Einfuegepunkt.y());
            Rechts.set_y(Einfuegepunkt.y());
            break;
    }
}
void rechteck3d::set_rad(double neuer_radius)
{
    Radius = neuer_radius;
}
void rechteck3d::set_drewi(double neuer_drehwinkel)
{
    Drehwinkel = neuer_drehwinkel;
}

//--------------------------------------------------get_xy:
punkt3d rechteck3d::bezpunkt()
{
    switch(Bezugspunkt)
    {
        case UNTEN_LINKS:
            return Unli;
        case UNTEN_RECHTS:
            return Unre;
        case OBEN_RECHTS:
            return Obre;
        case OBEN_LINKS:
            return Obli;
        case MITTE:
            return Mitte;
        case LINKS:
            return Links;
        case RECHTS:
            return Rechts;
        case OBEN:
            return Oben;
        case UNTEN:
            return Unten;
        default:
            punkt3d p(0,0,0);
            return p;
    }
}

//--------------------------------------------------Manipulaionen:
void rechteck3d::verschieben_um(double xversatz, double yversatz)
{
    Obli.verschieben_um(xversatz, yversatz);
    Oben.verschieben_um(xversatz, yversatz);
    Obre.verschieben_um(xversatz, yversatz);
    Links.verschieben_um(xversatz, yversatz);
    Mitte.verschieben_um(xversatz, yversatz);
    Rechts.verschieben_um(xversatz, yversatz);
    Unli.verschieben_um(xversatz, yversatz);
    Unten.verschieben_um(xversatz, yversatz);
    Unre.verschieben_um(xversatz, yversatz);
    Einfuegepunkt.verschieben_um(xversatz, yversatz);
}

//--------------------------------------------------







