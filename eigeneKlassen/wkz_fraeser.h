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

    //--get_xy:
    QString get_data();
    QString get_name();
    QString get_nummer();
    bool ist_vertikal();
    bool ist_horizontal();
    double get_dm();
    QString get_dm_qstring();
    double get_nutzlaenge();
    QString get_nutzlaenge_qstring();
    double get_zustellmas();
    QString get_zustellmas_qstring();
    bool dreht_im_uzs();

private:
    QString name;
    QString nr;
    bool vertikal;
    double dm;
    double nutzl;
    double zustma;
    bool drehri_uzs;

    void clear();
};

#endif // WKZ_FRAESER_H
