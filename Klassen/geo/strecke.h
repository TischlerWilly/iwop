#ifndef STRECKE_H
#define STRECKE_H

#include <QString>
#include <math.h>
#include <QMessageBox>
#include "punkt3d.h"
#include "punkt2d.h"
#include "darstellungsatribute.h"
#include "geofunktionen.h"
#include "Klassen/text_zeilenweise.h"
#include "defines_geometrie.h"

enum strecke_bezugspunkt{strecke_bezugspunkt_start, \
                         strecke_bezugspunkt_mitte, \
                         strecke_bezugspunkt_ende};

class strecke : public darstellungsatribute
{
public:
    strecke();
    strecke(QString geotext);

    //-----------------------------------------set_xy:
    void    set_text(QString geotext);
    void    set_start(punkt3d startpunkt);
    void    set_start(punkt2d startpunkt);
    void    set_ende(punkt3d endpunkt);
    void    set_ende(punkt2d endpunkt);

    //-----------------------------------------get_xy:
    inline punkt3d stapu()
    {
        return Stapu;
    }
    inline punkt3d endpu()
    {
        return Endpu;
    }
    punkt3d mitpu3d();
    punkt2d mitpu2d();
    punkt3d schnittp_zur_senkr_an_p(punkt3d p);

    inline double laenge3d()
    {
        return  laenge3d(Stapu, Endpu);
    }
    double laenge3d(punkt3d sp, punkt3d ep);
    inline double laenge2d()
    {
        return  laenge2d(Stapu, Endpu);
    }
    double laenge2d(punkt3d sp, punkt3d ep);
    inline QString laenge3d_QString()
    {
        return double_to_qstring(laenge3d());
    }
    inline QString laenge2d_QString()
    {
        return double_to_qstring(laenge2d());
    }
    double wink();
    double abst(punkt3d p);
    double abst(punkt2d p);
    bool auf_strecke(punkt3d p);

    QString text();

    //-----------------------------------------manipulationen:
    void    richtung_unkehren();
    void    drenen_um_startpunkt_2d(double drehwi, bool drehri_im_uzs);
    void    drenen_um_endpunkt_2d(double drehwi, bool drehri_im_uzs);
    void    drenen_um_mittelpunkt_2d(double drehwi, bool drehri_im_uzs);
    void    set_laenge_2d(double neue_laenge, \
               strecke_bezugspunkt bezugspunkt = strecke_bezugspunkt_mitte);
    void    verschieben_um(double xversatz, double yversatz);

    //-----------------------------------------

private:
    punkt3d Stapu, Endpu;

};

#endif // STRECKE_H
