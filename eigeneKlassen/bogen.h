#ifndef BOGEN_H
#define BOGEN_H

#include <math.h>
#include "punkt3d.h"
#include "punkt2d.h"
#include "strecke.h"
#include "darstellungsatribute.h"
#include "../eigeneFunktionen/myfunktion.h"

enum bogen_bezugspunkt{bogen_bezugspunkt_start, \
                       bogen_bezugspunkt_mitte, \
                       bogen_bezugspunkt_ende};

class bogen : public darstellungsatribute
{
public:
    bogen();
    bogen(QString geotext);
    bogen(punkt3d startpunkt, punkt3d endpunkt);
    bogen(punkt3d startpunkt, punkt3d endpunkt, float radiuswert, bool im_uhrzeigersinn);
    bogen(punkt2d mipu, double rad, double startwinkel, double endwinkel);

    //------------------------------------------------------Werte setzen:
    void set_startpunkt(punkt3d startpunkt);
    void set_endpunkt(punkt3d endpunkt);
    void set_radius(float radiuswert, bool im_uhrzeigersinn);
    inline void set_radius(QString radiuswert, bool im_uhrzeigersinn)
    {
        set_radius(radiuswert.toFloat(), im_uhrzeigersinn);
    }
    void set_radius(float radiuswert, punkt2d bogenrichtung);    
    void set_bogenwinkel(double wi, bogen_bezugspunkt bezug);

    //------------------------------------------------------Werte auslesen:
    inline punkt3d start()
    {
        return startp;
    }
    inline punkt3d ende()
    {
        return endp;
    }
    punkt2d mitte();
    inline punkt2d mittelpunkt()
    {
        return mitte();
    }
    inline double rad()
    {
        return radius;
    }
    inline QString rad_qString()
    {
        return double_to_qstring(radius);
    }
    inline bool im_uzs()
    {
        return bogen_im_uzs;
    }
    inline QString im_uzs_QString()
    {
        if(bogen_im_uzs == true)
        {
            return "ja";
        }else
        {
            return "nein";
        }
    }
    double bogenwinkel();

    inline bool hat_fehler()
    {
        return fehler;
    }
    inline QString  fehlermeldung()
    {
        return fehlertext;
    }
     QString get_text();
     void get_mb();

    //------------------------------------------------------Manipulationen:
    void    richtung_unkehren();
    void    verschieben_um(double xversatz, double yversatz);


private:
    punkt3d startp, endp;
    double radius;
    bool bogen_im_uzs; //Bogen im Uhrzeigersinn

    bool fehler;
    QString fehlertext;



};

#endif // BOGEN_H
