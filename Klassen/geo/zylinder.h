#ifndef ZYLINDER_H
#define ZYLINDER_H

#include "kreis.h"

class zylinder : public kreis
{
public:
    zylinder();
    zylinder(QString geotext);
    inline  zylinder(punkt3d mittelpunkt, double radius, double zylinderhoehe)
    {
        set_mittelpunkt(mittelpunkt);
        set_radius(radius);
        set_hoehe(zylinderhoehe);
    }
    inline  void    set_hoehe(double neue_hoehe)
    {
        Hoehe = neue_hoehe;
    }
    inline  void    set_hoehe(QString neue_hoehe)
    {
        Hoehe = neue_hoehe.toDouble();
    }

    inline  double  hoehe()
    {
        return Hoehe;
    }
    inline  QString hoehe_qstring()
    {
        return double_to_qstring(Hoehe);
    }

private:
    double Hoehe;
};

#endif // ZYLINDER_H
