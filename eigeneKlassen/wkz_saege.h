#ifndef WKZ_SAEGE_H
#define WKZ_SAEGE_H

#include <QString>
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneFunktionen/text.h"
#include "eigeneDefines/define_wkz.h"
#include "eigeneDefines/define_wkz_saege.h"


class wkz_saege
{
public:
    wkz_saege();
    //--set_xy:
    void set_data(QString new_data);
    void set_name(QString neuer_name);
    void set_nummer(QString neue_nummer);
    void set_ausrichtung_vert(bool ist_vertikal);
    void set_ausrichtung_hori(bool ist_horizontal);
    void set_dm(double neuer_dm);
    void set_dm(QString neuer_dm);
    void set_breite(double neue_breite);
    void set_breite(QString neue_breite);

    //--get_xy:
    QString get_data();
    QString get_name();
    QString get_nummer();
    bool ist_vertikal();
    bool ist_horizontal();
    double get_dm();
    QString get_dm_qstring();
    double get_breite();
    QString get_breite_qstring();

private:
    QString name;
    QString nr;
    bool vertikal;
    double dm;
    double breite;

    void clear();
};

#endif // WKZ_SAEGE_H
