#ifndef WKZ_FRAESER_H
#define WKZ_FRAESER_H

#include <QString>
#include "Funktionen/umwandeln.h"
#include "Funktionen/text.h"
#include "Defines/define_wkz.h"
#include "Defines/define_wkz_fraeser.h"

class wkz_fraeser
{
public:
    wkz_fraeser();
    //--set_xy:
    void set_text(QString new_data);
    void set_name(QString neuer_name);
    void set_nummer(QString neue_nummer);
    void set_ausrichtung_vert(bool ist_vertikal);
    void set_ausrichtung_hori(bool ist_horizontal);
    void set_dm(double neuer_dm);
    void set_dm(QString neuer_dm);
    void set_nutzlaenge(double neue_nutzl);
    void set_nutzlaenge(QString neue_nutzl);
    void set_zustellmas(double neues_zustma);
    void set_zustellmas(QString neuer_zustma);
    void set_drehrichtung_uzs(bool im_uhrzeigersinn);
    void set_spiegelwkznr(QString nr);
    inline void set_use_for(QString msg)
    {
        Use_for = msg;
    }
    inline void set_not_use_for(QString msg)
    {
        Not_use_for = msg;
    }
    inline void set_besonderheiten(QString msg)
    {
        Besonderheiten = msg;
    }
    inline void set_schneidenanz(int anz)
    {
        Schneidenanz = anz;
    }
    inline void set_schneidenanz(QString anz)
    {
        Schneidenanz = anz.toInt();
    }
    inline void set_klingenform(QString form)
    {
        Klingenform = form;
    }
    inline void set_klingenart(QString art)
    {
        Klingenart = art;
    }
    inline void set_vorschub(int f)
    {
        Vorschub = f;
    }
    inline void set_vorschub(QString f)
    {
        Vorschub = f.toInt();
    }
    inline void set_anfahrvorschub(int fan)
    {
        Anfahrvorschub = fan;
    }
    inline void set_anfahrvorschub(QString fan)
    {
        Anfahrvorschub = fan.toInt();
    }
    inline void set_drehzahl(int n)
    {
        Drehzahl = n;
    }
    inline void set_drehzahl(QString n)
    {
        Drehzahl = n.toInt();
    }

    //--get_xy:
    QString text();
    QString name();
    QString nummer();
    bool ist_vertikal();
    bool ist_horizontal();
    double dm();
    QString dm_qstring();
    double nutzlaenge();
    QString nutzlaenge_qstring();
    double zustellmas();
    QString zustellmas_qstring();
    bool dreht_im_uzs();
    QString spiegelwkznr();
    inline QString use_for()
    {
        return Use_for;
    }
    inline QString not_use_for()
    {
        return Not_use_for;
    }
    inline QString besonderheiten()
    {
        return Besonderheiten;
    }
    inline int schneidenanz()
    {
        return Schneidenanz;
    }
    inline QString schneidenanz_QString()
    {
        return int_to_qstring(Schneidenanz);
    }
    inline QString klingenform()
    {
        return Klingenform;
    }
    inline QString klingenart()
    {
        return Klingenart;
    }
    inline int vorschub()
    {
        return Vorschub;
    }
    inline QString vorschub_QString()
    {
        return int_to_qstring(Vorschub);
    }
    inline int anfahrvorschub()
    {
        return Anfahrvorschub;
    }
    inline QString anfahrvorschub_QString()
    {
        return int_to_qstring(Anfahrvorschub);
    }
    inline int drehzahl()
    {
        return Drehzahl;
    }
    inline QString drehzahl_QString()
    {
        return int_to_qstring(Drehzahl);
    }


private:
    QString Name;
    QString Nr;
    bool Vertikal;
    double Dm;
    double Nutzl;
    double Zustma;
    bool Drehri_uzs;
    QString SpiegelWKZ_nr;
    QString Use_for;
    QString Not_use_for;
    QString Besonderheiten;
    int Schneidenanz;
    QString Klingenform;
    QString Klingenart;
    int Vorschub;
    int Anfahrvorschub;
    int Drehzahl;

    void clear();
};

#endif // WKZ_FRAESER_H
