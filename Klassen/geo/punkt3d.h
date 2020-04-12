#ifndef PUNKT3D_H
#define PUNKT3D_H

#include <QString>
#include "Funktionen/umwandeln.h"
#include "darstellungsatribute.h"
#include "Klassen/text_zeilenweise.h"
#include "defines_geometrie.h"

class punkt3d : public darstellungsatribute
{
public:
            punkt3d();
            punkt3d(QString geotext);
    inline  punkt3d(double x, double y, double z)
    {
        X_param = x;
        Y_param = y;
        Z_param = z;
    }

    void set_text(QString geotext);
    inline  void    set_x(double wert)
    {
        X_param = wert;
    }
    inline  void    set_y(double wert)
    {
        Y_param = wert;
    }
    inline  void    set_z(double wert)
    {
        Z_param = wert;
    }
    inline  void    set_x(QString wert)
    {
        X_param = wert.toDouble();
    }
    inline  void    set_y(QString wert)
    {
        Y_param = wert.toDouble();
    }
    inline  void    set_z(QString wert)
    {
        Z_param = wert.toDouble();
    }

    inline  double  x()
    {
        return X_param;
    }
    inline  double  y()
    {
        return Y_param;
    }
    inline  double  z()
    {
        return Z_param;
    }
    inline  QString x_QString()
    {
        return double_to_qstring(X_param);
    }
    inline  QString y_QString()
    {
        return double_to_qstring(Y_param);
    }
    inline  QString z_QString()
    {
        return double_to_qstring(Z_param);
    }

    void    verschieben_um(double xversatz, double yversatz);

private:
    double  X_param, Y_param, Z_param;
};

//-------------------Funktionen nicht innerhalb der Klasse:
punkt3d operator +(punkt3d p1, punkt3d p2);
punkt3d operator -(punkt3d p1, punkt3d p2);
punkt3d operator *(punkt3d p1, double faktor);
punkt3d operator *(double faktor, punkt3d p1);
punkt3d operator /(punkt3d p1, double divisor);
bool operator ==(punkt3d p1, punkt3d p2);
bool operator !=(punkt3d p1, punkt3d p2);

#endif // PUNKT3D_H
