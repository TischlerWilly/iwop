#ifndef WKZ_FRAESER_H
#define WKZ_FRAESER_H

#include <QString>
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneFunktionen/text.h"
#include "eigeneDefines/define_wkz.h"
#include "eigeneDefines/define_wkz_fraeser.h"

class wkz_fraeser
{
public:
    wkz_fraeser();
    //--set_xy:
    void set_data(QString new_data);
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

private:
    QString Name;
    QString Nr;
    bool Vertikal;
    double Dm;
    double Nutzl;
    double Zustma;
    bool Drehri_uzs;
    QString SpiegelWKZ_nr;

    void clear();
};

#endif // WKZ_FRAESER_H
