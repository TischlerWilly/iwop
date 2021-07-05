#ifndef PROGRAMMTEXT_H
#define PROGRAMMTEXT_H

#include <QString>
#include <math.h>
#include "../myDefines.h"
#include "Defines/define_prgkopf.h"
#include "Funktionen/myfunktion.h"
#include "text_zeilenweise.h"
#include "wenndannsonst.h"
#include "Klassen/geo/geometrietext.h"
#include "tabelle_tz3.h"
#include "Defines/define_prgkopf.h"
#include "Defines/define_prgende.h"
#include "Defines/defines_kom.h"
#include "Defines/defines_halt.h"
#include "Defines/define_bo.h"
#include "Defines/define_boY.h"
#include "Defines/define_boX.h"
#include "Defines/define_loreiae.h"
#include "Defines/define_loreima.h"
#include "Defines/define_topf.h"
#include "Defines/define_hbexp.h"
#include "Defines/define_hbexm.h"
#include "Defines/define_hbeyp.h"
#include "Defines/define_hbeym.h"
#include "Defines/define_nut.h"
#include "Defines/define_kta.h"
#include "Defines/define_rta.h"
#include "Defines/define_spiegeln.h"
#include "Defines/define_lage_aendern.h"
#include "Defines/define_var.h"
#include "Defines/define_var10.h"
#include "Defines/define_allegm_var.h"
#include "Defines/define_fauf.h"
#include "Defines/define_fabf.h"
#include "Defines/define_fgerade.h"
#include "Defines/define_fgerawi.h"
#include "Defines/define_fbouzs.h"
#include "Defines/define_fboguzs.h"
#include "Dialoge/dialog_stulp.h"
#include "werkzeug.h"


class programmtext
{
public:
    programmtext();

    //----------------------------------------------------------set_xy:
    void set_text(QString neuer_Text);
    void set_maschinengeometrie(text_zeilenweise tz);

    inline void set_wkz(werkzeug w)
    {
        Wkz = w;
    }
    inline void set_nurlesend(bool einschalten)
    {
        Readonly = einschalten;
    }
    inline void set_warnungen_ein_aus(bool einschalten)
    {
        Warnungen_sind_eingeschaltet = einschalten;
    }
    inline void set_aktualisieren_ein_aus(bool einschalten)
    {
        if(einschalten)
        {
            Aktualisieren_eingeschaltet = true;
            aktualisieren();
        }else
        {
            Aktualisieren_eingeschaltet = false;
        }
    }
    //inline void set_aktualisieren_fkon_ein_aus(bool einschalten)
    /*{
        if(einschalten == true)
        {
            Aktualisieren_fkon_eingeschaltet = true;
            aktualisieren();
        }else
        {
            Aktualisieren_fkon_eingeschaltet = false;
            aktualisieren();
        }
    }*/
    //----------------------------------------------------------get_xy:
    QString klartext();
    QString variablen();
    QString zeile(uint zeilennummer);
    QString zeilen(uint zeilennummer_beginn, uint zeilenmenge);
    bool hat_ungesicherte_inhalte();

    inline QString          text()
    {
        return Text.text();
    }
    inline text_zeilenweise text_zw()
    {
        return Text;
    }
    inline text_zeilenweise klartext_zw()
    {
        return Klartext;
    }
    inline text_zeilenweise variablen_zw()
    {
        return Var;
    }
    inline QString          anzeigetext()
    {
        return Anzeigetext.text();
    }
    inline text_zeilenweise anzeigetext_zw()
    {
        return Anzeigetext;
    }
    inline QString          anzeigetext_zeile(uint zeilennummer)
    {
        return Anzeigetext.zeile(zeilennummer);
    }
    inline geometrietext    geo()
    {
        return Geo;
    }
    inline geometrietext    fkon()
    {
        return Fkon;
    }
    inline geometrietext    maschinengeo()
    {
        return MaschinenGeo;
    }
    inline geometrietext    fraeserdarst()
    {
        return Fraeserdarst;
    }
    inline bool             nurlesend()
    {
        return Readonly;
    }
    inline double           werkstuecklaenge()
    {
        return Werkstuecklaenge;
    }
    inline double           werkstueckbreite()
    {
        return Werkstueckbreite;
    }
    inline double           werkstueckdicke()
    {
        return Werkstueckdicke;
    }
    inline double           sicherheitsabstand()
    {
        return Sicherheitsabstand;
    }
    inline float            min_x()
    {
        return Min_x;
    }
    inline float            max_x()
    {
        return Max_x;
    }
    inline float            min_y()
    {
        return Min_y;
    }
    inline float            max_y()
    {
        return Max_y;
    }
    inline double           ax()
    {
        return Versatz_x;
    }
    inline double           ay()
    {
        return Versatz_y;
    }
    inline double           az()
    {
        return Versatz_z;
    }
    inline QString          ax_QString()
    {
        return double_to_qstring(Versatz_x);
    }
    inline QString          ay_QString()
    {
        return double_to_qstring(Versatz_y);
    }
    inline QString          az_QString()
    {
        return double_to_qstring(Versatz_z);
    }
    inline bool             aktualisieren_ein_aus()
    {
        return Aktualisieren_eingeschaltet;
    }
    //----------------------------------------------------------Manipulationen:
    void    clear();
    int     zeile_loeschen(uint zeilennummer);
    int     zeilen_loeschen(uint zeilennummer_beginn, uint zeilenmenge);
    int     zeile_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext);
    int     zeilen_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext);
    void    zeile_anhaengen(QString zeilentext);
    int     zeile_ersaetzen(uint zeilennummer, QString neuer_zeilentext);
    void    aktualisieren();
    void    wurde_gespeichert();
    //----------------------------------------------------------

private:
    text_zeilenweise    Text;           //Programm-Rohtext (mit Formeln und Variablen)
    text_zeilenweise    Text_kopie;     //Zum Vergleichen ob sich die Datei geändert wurde seit dem Speichern
    text_zeilenweise    Klartext;       //Programm-Klartext (Formeln und Variablen sind nun Zahlen)
    text_zeilenweise    Var;            //Variablen
    text_zeilenweise    Anzeigetext;    //Programmliste
    geometrietext       Geo;            //Geometrieen zur Darstellung
    geometrietext       Fkon;           //Fräskonturen
    geometrietext       MaschinenGeo;   //Maschinengeometrie
    geometrietext       Fraeserdarst;   //Darstellung des Fräsers

    double  Werkstuecklaenge;
    double  Werkstueckbreite;
    double  Werkstueckdicke;
    double  Sicherheitsabstand;
    double  Versatz_x;
    double  Versatz_y;
    double  Versatz_z;
    bool    Hat_programmkopf;
    bool    Hat_programmende;
    float   Min_x, Min_y, Max_x, Max_y;
    uint    Anz_faufr, Anz_fabfa;
    bool    Warnungen_sind_eingeschaltet;
    bool    Warnung_frDial;
    bool    Aktualisieren_eingeschaltet;
    bool    Readonly;
    werkzeug Wkz;

    //----------------------------------------------------------set_xy:

    inline  void    set_werkstuecklaenge(double neue_laenge)
    {
        Werkstuecklaenge = neue_laenge;
    }
    inline  void    set_werkstueckbreite(double neue_breite)
    {
        Werkstueckbreite = neue_breite;
    }
    inline  void    set_werkstueckdicke(double neue_dicke)
    {
        Werkstueckdicke = neue_dicke;
    }
    inline  void    set_versatz_x(double versatz)
    {
        Versatz_x = versatz;
    }
    inline  void    set_versatz_y(double versatz)
    {
        Versatz_y = versatz;
    }
    inline  void    set_versatz_z(double versatz)
    {
        Versatz_z = versatz;
    }

    //----------------------------------------------------------get_xy:

    //----------------------------------------------------------Manipulationen:
    void    clear_ausser_text();
    QString param_to_klartext(QString prgzeile, QString parname, QString varname, QString &varlist, bool varmerken);
    QString param_to_klartext_orginal(QString prgzeile, QString parname);
    QString var_to_klartext(QString prgzeile, QString name, QString wert, QString &varlist);
    QString var_to_klartext(QString name, QString wert);
    void    var_ergaenzen(QString &varlist, QString name, QString wert);
    void    aktualisiere_klartext_var();
    void    aktualisiere_geo();
    void    aktualisiere_anzeigetext();
    void    aktualisiere_min_max();
    //-------------
    kreis       spiegeln_kreis(kreis k, bool xbed, bool ybed, double xpos, double ypos);
    punkt3d     spiegeln_punkt3d(punkt3d p, bool xbed, bool ybed, double xpos, double ypos);
    rechteck3d  spiegeln_rechteck3d(rechteck3d r, bool xbed, bool ybed, double xpos, double ypos);
    strecke     spiegeln_strecke(strecke s, bool xbed, bool ybed, double xpos, double ypos);
    bogen       spiegeln_bogen(bogen bo, bool xbed, bool ybed, double xpos, double ypos);
    //-------------
    kreis       lageaendern_kreis(kreis k, bool afb,\
                                  double xalt, double yalt, double xneu, double yneu, \
                                  double wi, double geswi, bool kettenmas,\
                                  double xalt2, double yalt2, double xneu2, double yneu2, \
                                  double wi2, double geswi2);
    punkt3d     lageaendern_punkt3d(punkt3d p, bool afb,\
                                    double xalt, double yalt, double xneu, double yneu, \
                                    double wi, double geswi, bool kettenmas,\
                                    double xalt2, double yalt2, double xneu2, double yneu2, \
                                    double wi2, double geswi2);
    rechteck3d  lageaendern_rechteck3d(rechteck3d r, bool afb,\
                                       double xalt, double yalt, double xneu, double yneu, \
                                       double wi, double geswi, bool kettenmas,\
                                       double xalt2, double yalt2, double xneu2, double yneu2, \
                                       double wi2, double geswi2);
    strecke     lageaendern_strecke(strecke s, bool afb,\
                                    double xalt, double yalt, double xneu, double yneu, \
                                    double wi, double geswi, bool kettenmas,\
                                    double xalt2, double yalt2, double xneu2, double yneu2, \
                                    double wi2, double geswi2);
    bogen       lageaendern_bogen(bogen bo, bool afb,\
                                  double xalt, double yalt, double xneu, double yneu, \
                                  double wi, double geswi, bool kettenmas,\
                                  double xalt2, double yalt2, double xneu2, double yneu2, \
                                  double wi2, double geswi2);
    //----------------------------------------------------------

};

#endif // PROGRAMMTEXT_H
