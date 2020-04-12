#ifndef RECHTECK3D_H
#define RECHTECK3D_H

#ifndef UNTEN_LINKS
#define UNTEN_LINKS     1
#endif
#ifndef UNTEN_RECHTS
#define UNTEN_RECHTS    2
#endif
#ifndef OBEN_RECHTS
#define OBEN_RECHTS     3
#endif
#ifndef OBEN_LINKS
#define OBEN_LINKS      4
#endif
#ifndef MITTE
#define MITTE           5
#endif
#ifndef LINKS
#define LINKS           6
#endif
#ifndef RECHTS
#define RECHTS          7
#endif
#ifndef OBEN
#define OBEN            8
#endif
#ifndef UNTEN
#define UNTEN           9
#endif

#include "darstellungsatribute.h"
#include "punkt3d.h"
#include "geofunktionen.h"

class rechteck3d : public darstellungsatribute
{
public:
    rechteck3d();
    rechteck3d(QString geotext);

    //--------------------------------------------------set_xy:
    void set_text(QString geotext);
    void set_mipu(double x, double y, double z);
    void set_mipu(punkt3d p);
    void set_z(double z);
    void set_laenge(double neue_laenge);
    void set_breite(double neue_breite);
    void set_rad(double neuer_radius);
    void set_drewi(double neuer_drehwinkel);

    inline  void    set_einfuegepunkt(punkt3d p)
    {
        Einfuegepunkt = p;
        //Lager der Punkte aktualisieren:
        set_laenge(l());
        set_breite(b());
    }
    inline  void    set_einfuegepunkt(double x, double y, double z)
    {
        Einfuegepunkt.set_x(x);
        Einfuegepunkt.set_y(y);
        Einfuegepunkt.set_z(z);
    }
    inline  void    set_einfuegepunkt(int x, int y)
    {
        Einfuegepunkt.set_x(x);
        Einfuegepunkt.set_y(y);
        Einfuegepunkt.set_z(0);
    }
    inline  void    set_bezugspunkt(int nummer_des_punktes)
    {
        Bezugspunkt = nummer_des_punktes;
    }
    inline  void    set_bezugspunkt(QString nummer_des_punktes)
    {
        Bezugspunkt = nummer_des_punktes.toInt();
    }      
    inline  void    set_laenge(QString neue_laenge)
    {
        set_laenge(neue_laenge.toDouble());
    }       
    inline  void    set_breite(QString neue_breite)
    {
        set_breite(neue_breite.toDouble());
    }       
    inline  void    set_rad(QString neuer_radius)
    {
        set_rad(neuer_radius.toDouble());
    }       
    inline  void    set_drewi(QString neuer_drehwinkel)
    {
        set_drewi(neuer_drehwinkel.toDouble());
    }

    //--------------------------------------------------get_xy:
            punkt3d bezpunkt();
    inline  int     bezpunkt_num()
    {
        return Bezugspunkt;
    }
    inline  QString bezpunkt_num_qstring()
    {
        return int_to_qstring(Bezugspunkt);
    }
    inline  punkt3d einfpunkt()
    {
        return Einfuegepunkt;
    }
    inline  double  l()
    {
        return Laenge;
    }
    inline  QString l_qstring()
    {
        return double_to_qstring(Laenge);
    }
    inline  double  b()
    {
        return Breite;
    }
    inline  QString b_qstring()
    {
        return double_to_qstring(Breite);
    }
    inline  punkt3d obl(bool ungedreht = true)
    {
        if(ungedreht)
        {
            return Obli;
        }else
        {
            return drehen(Mitte, Obli, Drehwinkel, true);
        }
    }
    inline  punkt3d ob(bool ungedreht = true)
    {
        if(ungedreht)
        {
            return Oben;
        }else
        {
            return drehen(Mitte, Oben, Drehwinkel, true);
        }
    }
    inline  punkt3d obr(bool ungedreht = true)
    {
        if(ungedreht)
        {
            return Obre;
        }else
        {
            return drehen(Mitte, Obre, Drehwinkel, true);
        }
    }
    inline  punkt3d li(bool ungedreht = true)
    {
        if(ungedreht)
        {
            return Links;
        }else
        {
            return drehen(Mitte, Links, Drehwinkel, true);
        }
    }
    inline  punkt3d mi()
    {
        return Mitte;
    }
    inline  punkt3d re(bool ungedreht = true)
    {
        if(ungedreht)
        {
            return Rechts;
        }else
        {
            return drehen(Mitte, Rechts, Drehwinkel, true);
        }
    }
    inline  punkt3d unl(bool ungedreht = true)
    {
        if(ungedreht)
        {
            return Unli;
        }else
        {
            return drehen(Mitte, Unli, Drehwinkel, true);
        }
    }
    inline  punkt3d un(bool ungedreht = true)
    {
        if(ungedreht)
        {
            return Unten;
        }else
        {
            return drehen(Mitte, Unten, Drehwinkel, true);
        }
    }
    inline  punkt3d unr(bool ungedreht = true)
    {
        if(ungedreht)
        {
            return Unre;
        }else
        {
            return drehen(Mitte, Unre, Drehwinkel, true);
        }
    }
    inline  double  rad()
    {
        return Radius;
    }
    inline  QString rad_qstring()
    {
        return double_to_qstring(Radius);
    }
    inline  double  drewi()
    {
        return Drehwinkel;
    }
    inline  QString drewi_qstring()
    {
        return double_to_qstring(Drehwinkel);
    }

    //--------------------------------------------------Manipulaionen:
    void    verschieben_um(double xversatz, double yversatz);


private:
    punkt3d Obli,   Oben,   Obre;
    punkt3d Links,  Mitte,  Rechts;
    punkt3d Unli,   Unten,  Unre;
    punkt3d Einfuegepunkt;
    int Bezugspunkt;
    double Laenge, Breite;
    double Radius;
    double Drehwinkel;



};

#endif // RECHTECK3D_H
