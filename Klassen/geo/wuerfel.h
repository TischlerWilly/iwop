#ifndef WUERFEL_H
#define WUERFEL_H

#include "rechteck3d.h"

class wuerfel : public rechteck3d
{
public:
    wuerfel();
    wuerfel(QString geotext);

    void set_text(QString geotext);
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

#endif // WUERFEL_H
