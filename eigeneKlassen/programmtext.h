#ifndef PROGRAMMTEXT_H
#define PROGRAMMTEXT_H

#include <QString>
#include <math.h>
#include "../myDefines.h"
#include "../eigeneDefines/define_prgkopf.h"
#include "../eigeneFunktionen/myfunktion.h"
#include "text_zeilenweise.h"
#include "wenndannsonst.h"
#include "rechtecktasche.h"
#include "geometrietext.h"
#include "tabelle_tz3.h"
//#include "../Dialoge/dialog_variable.h"
#include "eigeneDefines/define_prgkopf.h"
#include "eigeneDefines/define_prgende.h"
#include "eigeneDefines/defines_kom.h"
#include "eigeneDefines/defines_halt.h"
#include "eigeneDefines/define_bo.h"
#include "eigeneDefines/define_boY.h"
#include "eigeneDefines/define_boX.h"
#include "eigeneDefines/define_loreiae.h"
#include "eigeneDefines/define_loreima.h"
#include "eigeneDefines/define_topf.h"
#include "eigeneDefines/define_hbexp.h"
#include "eigeneDefines/define_hbexm.h"
#include "eigeneDefines/define_hbeyp.h"
#include "eigeneDefines/define_hbeym.h"
#include "eigeneDefines/define_nut.h"
#include "eigeneDefines/define_kta.h"
#include "eigeneDefines/define_rta.h"
#include "eigeneDefines/define_spiegeln.h"
#include "eigeneDefines/define_lage_aendern.h"
#include "eigeneDefines/define_var.h"
#include "eigeneDefines/define_var10.h"
#include "eigeneDefines/define_allegm_var.h"
#include "eigeneDefines/define_fauf.h"
#include "eigeneDefines/define_fabf.h"
#include "eigeneDefines/define_fgerade.h"
#include "eigeneDefines/define_fgerawi.h"
#include "eigeneDefines/define_fbouzs.h"
#include "eigeneDefines/define_fboguzs.h"
#include "werkzeug.h"


class programmtext
{
public:
    programmtext();
            void                set_text(QString neuer_Text);
//            void                set_wkz(werkzeug wkz);
            void                set_maschinengeometrie(text_zeilenweise tz);
    inline  void    set_wkz(werkzeug w)
    {
        wkz = w;
    }
            void                clear();
    inline  void                warnungen_einschalten(bool einschalten)
    {
        warnungen_sind_eingeschaltet = einschalten;
    }
    inline  void                nurlesend(bool einschalten)
    {
        readonly = einschalten;
    }
    inline bool                 get_nurlesend()
    {
        return readonly;
    }
    inline  QString             get_text()
    {
        return text.get_text();
    }
    inline  text_zeilenweise    get_text_zeilenweise()
    {
        return text;
    }
            QString             get_klartext();
    inline  text_zeilenweise    get_klartext_zeilenweise()
    {
        return klartext;
    }
            QString             get_variablen();
    inline  text_zeilenweise    get_variablen_zeilenweise()
    {
        return var;
    }
    inline  QString             get_anzeigetext()
    {
        return anzeigetext.get_text();
    }
    inline  text_zeilenweise    get_anzeigetext_zeilenweise()
    {
        return anzeigetext;
    }
    inline  QString             get_anzeigetext_zeile(uint zeilennummer)
    {
        return anzeigetext.zeile(zeilennummer);
    }

    inline  geometrietext       get_geo()
    {
        return geo;
    }
    inline  geometrietext       get_fkon()
    {
        return fkon;
    }
    inline  geometrietext       get_maschinengeo()
    {
        return maschinengeo;
    }
    inline  geometrietext       get_fraeserdarst()
    {
        return fraeserdarst;
    }

    inline  double   get_werkstuecklaenge()
    {
        return werkstuecklaenge;
    }
    inline  double   get_werkstueckbreite()
    {
        return werkstueckbreite;
    }
    inline  double   get_werkstueckdicke()
    {
        return werkstueckdicke;
    }
    inline  double   get_sicherheitsabstand()
    {
        return sicherheitsabstand;
    }
    inline  float   get_min_x()
    {
        return min_x;
    }
    inline  float   get_max_x()
    {
        return max_x;
    }
    inline  float   get_min_y()
    {
        return min_y;
    }
    inline  float   get_max_y()
    {
        return max_y;
    }

    inline  double   get_ax()
    {
        return versatz_x;
    }
    inline  double   get_ay()
    {
        return versatz_y;
    }
    inline  double   get_az()
    {
        return versatz_z;
    }
    inline  QString   get_ax_qstring()
    {
        return double_to_qstring(versatz_x);
    }
    inline  QString   get_ay_qstring()
    {
        return double_to_qstring(versatz_y);
    }
    inline  QString   get_az_qstring()
    {
        return double_to_qstring(versatz_z);
    }

    QString     zeile(uint zeilennummer);
    QString     zeilen(uint zeilennummer_beginn, uint zeilenmenge);
    int         zeile_loeschen(uint zeilennummer);
    int         zeilen_loeschen(uint zeilennummer_beginn, uint zeilenmenge);
    int         zeile_einfuegen(uint zeilennummer_vor_neuer_zeile, \
                                QString zeilentext);
    int         zeilen_einfuegen(uint zeilennummer_vor_neuer_zeile, \
                                 QString zeilentext);
    void        zeile_anhaengen(QString zeilentext);
    int         zeile_ersaetzen(uint zeilennummer, QString neuer_zeilentext);

    inline  void aktualisieren_ein_aus(bool einschalten)
    {
        if(einschalten)
        {
            aktualisieren_eingeschaltet = true;
            aktualisieren();
        }else
        {
            aktualisieren_eingeschaltet = false;
        }
    }

    inline  void aktualisieren_fkon_ein_aus(bool einschalten)
    {
        if(einschalten == true)
        {
            aktualisieren_fkon_eingeschaltet = true;
            aktualisieren();
        }else
        {
            aktualisieren_fkon_eingeschaltet = false;
            aktualisieren();
        }
    }
    inline bool get_aktualisieren_fkon_ein_aus()
    {
        return aktualisieren_fkon_eingeschaltet;
    }

    inline  bool ist_aktualisieren_fkon_ein()
    {
        return aktualisieren_fkon_eingeschaltet;
    }
    void aktualisieren();
    void wurde_gespeichert();
    bool get_hat_ungesicherte_inhalte();

    bool cagleich(punkt3d p1, punkt3d p2, double tolleranz);


private:
    text_zeilenweise    text;           //Programm-Rohtext (mit Formeln und Variablen)
    text_zeilenweise    text_kopie;     //Zum Vergleichen ob sich die Datei geändert wurde seit dem Speichern
    text_zeilenweise    klartext;       //Programm-Klartext (Formeln und Variablen sind nun Zahlen)
    text_zeilenweise    var;            //Variablen
    text_zeilenweise    anzeigetext;    //Programmliste
    geometrietext       geo;            //Geometrieen zur Darstellung
    geometrietext       fkon;           //Fräskonturen
    geometrietext       maschinengeo;   //Maschinengeometrie
    geometrietext       fraeserdarst;   //Darstellung des Fräsers

    double  werkstuecklaenge;
    double  werkstueckbreite;
    double  werkstueckdicke;
    double  sicherheitsabstand;
    double  versatz_x;
    double  versatz_y;
    double  versatz_z;
    bool    hat_programmkopf;
    bool    hat_programmende;
    float   min_x, min_y, max_x, max_y;
    uint    anz_faufr, anz_fabfa;
    bool    warnungen_sind_eingeschaltet;
    bool    warnung_frDial;
    bool    aktualisieren_eingeschaltet;
    bool    aktualisieren_fkon_eingeschaltet;
    bool    readonly;
    werkzeug wkz;

            void    clear_ausser_text();
    inline  void    set_werkstuecklaenge(double neue_laenge)
    {
        werkstuecklaenge = neue_laenge;
    }
    inline  void    set_werkstueckbreite(double neue_breite)
    {
        werkstueckbreite = neue_breite;
    }
    inline  void    set_werkstueckdicke(double neue_dicke)
    {
        werkstueckdicke = neue_dicke;
    }
    inline  void    set_versatz_x(double versatz)
    {
        versatz_x = versatz;
    }
    inline  void    set_versatz_y(double versatz)
    {
        versatz_y = versatz;
    }
    inline  void    set_versatz_z(double versatz)
    {
        versatz_z = versatz;
    }
            void    set_sicherheitsabstand(float neuer_Abstand);



            void    aktualisiere_klartext_var();
            QString param_to_klartext(QString prgzeile, QString parname, QString varname, QString &varlist, bool varmerken);
            QString param_to_klartext_orginal(QString prgzeile, QString parname);
            QString var_to_klartext(QString prgzeile, QString name, QString wert, QString &varlist);
            QString var_to_klartext(QString name, QString wert);
            void var_ergaenzen(QString &varlist, QString name, QString wert);
            void    aktualisiere_geo();
            void    aktualisiere_anzeigetext();
            void    aktualisiere_wkz();
            void    aktualisiere_fkon();
            void    aktualisiere_fraeserdarst();            
            void    aktualisiere_schleife_linear();
            void    aktualisiere_min_max();

            text_zeilenweise fkon_use_values(text_zeilenweise cam);

            kreis   spiegeln_kreis(kreis k, bool xbed, bool ybed, double xpos, double ypos);
            punkt3d spiegeln_punkt3d(punkt3d p, bool xbed, bool ybed, double xpos, double ypos);
            rechteck3d spiegeln_rechteck3d(rechteck3d r, bool xbed, bool ybed, double xpos, double ypos);
            strecke spiegeln_strecke(strecke s, bool xbed, bool ybed, double xpos, double ypos);
            bogen spiegeln_bogen(bogen bo, bool xbed, bool ybed, double xpos, double ypos);

            kreis   lageaendern_kreis(kreis k, bool afb,\
                                      double xalt, double yalt, double xneu, double yneu, \
                                      double wi, double geswi, bool kettenmas,\
                                      double xalt2, double yalt2, double xneu2, double yneu2, \
                                      double wi2, double geswi2);
            punkt3d lageaendern_punkt3d(punkt3d p, bool afb,\
                                        double xalt, double yalt, double xneu, double yneu, \
                                        double wi, double geswi, bool kettenmas,\
                                        double xalt2, double yalt2, double xneu2, double yneu2, \
                                        double wi2, double geswi2);
            rechteck3d lageaendern_rechteck3d(rechteck3d r, bool afb,\
                                              double xalt, double yalt, double xneu, double yneu, \
                                              double wi, double geswi, bool kettenmas,\
                                              double xalt2, double yalt2, double xneu2, double yneu2, \
                                              double wi2, double geswi2);
            strecke lageaendern_strecke(strecke s, bool afb,\
                                        double xalt, double yalt, double xneu, double yneu, \
                                        double wi, double geswi, bool kettenmas,\
                                        double xalt2, double yalt2, double xneu2, double yneu2, \
                                        double wi2, double geswi2);
            bogen lageaendern_bogen(bogen bo, bool afb,\
                                    double xalt, double yalt, double xneu, double yneu, \
                                    double wi, double geswi, bool kettenmas,\
                                    double xalt2, double yalt2, double xneu2, double yneu2, \
                                    double wi2, double geswi2);




};

#endif // PROGRAMMTEXT_H
