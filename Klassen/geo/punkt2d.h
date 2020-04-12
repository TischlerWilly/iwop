#ifndef PUNKT2D_H
#define PUNKT2D_H

#include <QString>
#include "Funktionen/umwandeln.h"
#include "punkt3d.h"
#include "darstellungsatribute.h"

class punkt2d : public darstellungsatribute
{
public:
    punkt2d();
    inline  punkt2d(double x, double y)
    {
        X_param = x;
        Y_param = y;
    }
            punkt2d(punkt3d p);

    inline  void    set_x(double wert)
    {
        X_param = wert;
    }
    inline  void    set_y(double wert)
    {
        Y_param = wert;
    }
    inline  void    set_x(QString wert)
    {
        X_param = wert.toDouble();
    }
    inline  void    set_y(QString wert)
    {
        Y_param = wert.toDouble();
    }

    inline  double  x()
    {
        return X_param;
    }
    inline  double  y()
    {
        return Y_param;
    }
    inline  QString x_QString()
    {
        return double_to_qstring(X_param);
    }
    inline  QString y_QString()
    {
        return double_to_qstring(Y_param);
    }

    void    verschieben_um(double xversatz, double yversatz);

private:
    double  X_param, Y_param;

};

//-------------------Funktionen nicht innerhalb der Klasse:
punkt2d operator +(punkt2d p1, punkt2d p2);
punkt2d operator -(punkt2d p1, punkt2d p2);
punkt2d operator *(punkt2d p1, double faktor);
punkt2d operator *(double faktor, punkt2d p1);
punkt2d operator /(punkt2d p1, double divisor);
bool operator ==(punkt2d p1, punkt2d p2);
bool operator !=(punkt2d p1, punkt2d p2);

#endif // PUNKT2D_H
