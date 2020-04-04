#ifndef STRECKE_H
#define STRECKE_H

#include <QString>
#include <math.h>
#include <QMessageBox>
#include "punkt3d.h"
#include "punkt2d.h"
#include "darstellungsatribute.h"
#include "../eigeneFunktionen/geometrie.h"
#include "text_zeilenweise.h"
#include "../eigeneDefines/defines_geometrie.h"

enum strecke_bezugspunkt{strecke_bezugspunkt_start, \
                         strecke_bezugspunkt_mitte, \
                         strecke_bezugspunkt_ende};

class strecke : public darstellungsatribute
{
public:
    strecke();
    strecke(QString geotext);
            void    set_start(punkt3d startpunkt);
            void    set_start(punkt2d startpunkt);
            void    set_ende(punkt3d endpunkt);
            void    set_ende(punkt2d endpunkt);
            void    richtung_unkehren();
            void    drenen_um_startpunkt_2d(double drehwinkel, \
                                             bool drehrichtung_im_uhrzeigersinn);
            void    drenen_um_endpunkt_2d(double drehwinkel, \
                                             bool drehrichtung_im_uhrzeigersinn);
            void    drenen_um_mittelpunkt_2d(double drehwinkel, \
                                             bool drehrichtung_im_uhrzeigersinn);
            void    set_laenge_2d(double neue_laenge, \
                       strecke_bezugspunkt bezugspunkt = strecke_bezugspunkt_mitte);
            void    verschieben_um(double xversatz, double yversatz);


    inline punkt3d startp()
    {
        return start;
    }
    inline punkt3d endp()
    {
        return ende;
    }  
    inline double laenge3dim()
    {
        return  laenge_3d(start, ende);
    }
    inline double laenge2dim()
    {
        return  laenge_2d(start, ende);
    }
    inline QString laenge3dim_QString()
    {
        return double_to_qstring(laenge3dim());
    }
    inline QString laenge2dim_QString()
    {
        return double_to_qstring(laenge2dim());
    }

    punkt3d get_mittelpunkt3d();
    punkt2d get_mittelpunkt2d();

    double get_winkel();
    double get_abst(punkt3d p);
    double get_abst(punkt2d p);

    QString get_text();

private:
    punkt3d start, ende;

    double laenge_2d(punkt3d sp, punkt3d ep);
    double laenge_3d(punkt3d sp, punkt3d ep);
    double get_abst_gerade(punkt3d p);



};

#endif // STRECKE_H
