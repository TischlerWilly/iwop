#ifndef WKZ_SAEGE_H
#define WKZ_SAEGE_H

#include <QString>
#include "Funktionen/umwandeln.h"
#include "Funktionen/text.h"
#include "Defines/define_wkz.h"
#include "Defines/define_wkz_saege.h"


class wkz_saege
{
public:
    wkz_saege();
    //--set_xy:
    void set_text(QString new_data);
    void set_name(QString neuer_name);
    void set_nummer(QString neue_nummer);
    void set_ausrichtung_vert(bool ist_vertikal);
    void set_ausrichtung_hori(bool ist_horizontal);
    void set_dm(double neuer_dm);
    void set_dm(QString neuer_dm);
    void set_breite(double neue_breite);
    void set_breite(QString neue_breite);

    //--get_xy:
    QString text();
    QString name();
    QString nummer();
    bool ist_vertikal();
    bool ist_horizontal();
    double dm();
    QString dm_qstring();
    double breite();
    QString breite_qstring();

private:
    QString Name;
    QString Nr;
    bool Vertikal;
    double Dm;
    double Breite;

    void clear();
};

#endif // WKZ_SAEGE_H
