#ifndef KREIS_H
#define KREIS_H

#include "punkt3d.h"
#include "punkt2d.h"
#include "darstellungsatribute.h"
#include "defines_geometrie.h"
#include "Klassen/text_zeilenweise.h"

class kreis : public darstellungsatribute
{
public:
    kreis();
    kreis(QString geotext);
    inline  kreis(punkt3d mittelpunkt, double radius)
    {
        set_mittelpunkt(mittelpunkt);
        set_radius(radius);
    }

    void set_text(QString geotext);
    inline  void    set_mittelpunkt(punkt3d mittelpunkt)
    {
        Mittelp = mittelpunkt;
    }
    inline  void    set_mittelpunkt(double x, double y, double z)
    {
        Mittelp.set_x(x);
        Mittelp.set_y(y);
        Mittelp.set_z(z);
    }
    inline  void    set_radius(double radius)
    {
        Rad = radius;
    }
    inline  void    set_radius(QString radius)
    {
        Rad = radius.toDouble();
    }

    inline  punkt3d     mitte3d()
    {
        return Mittelp;
    }
    inline  punkt2d     mitte2d()
    {
        return punkt2d(Mittelp.x(), Mittelp.y());
    }
    inline  double      radius()
    {
        return Rad;
    }
    inline  QString     radius_QString()
    {
        return double_to_qstring(Rad);
    }

    void    verschieben_um(double xversatz, double yversatz);

    QString text();

private:
    punkt3d     Mittelp;
    double      Rad;

};

#endif // KREIS_H
