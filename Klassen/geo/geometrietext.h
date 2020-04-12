#ifndef GEOMETRIETEXT_H
#define GEOMETRIETEXT_H

#include <QString>
#include <QMessageBox>
#include "Klassen/text_zeilenweise.h"
#include "Struncts/punkt.h"
#include "Funktionen/umwandeln.h"
#include "punkt3d.h"
#include "strecke.h"
#include "bogen.h"
#include "kreis.h"
#include "zylinder.h"
#include "rechteck3d.h"
#include "wuerfel.h"
#include "defines_geometrie.h"
#include "geofunktionen.h"


class geometrietext
{
public:
    geometrietext();
    void clear();
    void zeilenvorschub();
    void add_punkt(punkt3d p);
    void add_punkt(punkt3d p, uint zeile);
    void add_strecke(strecke s);
    void add_strecke(strecke s, uint zeile);
    void add_bogen(bogen b);
    void add_bogen(bogen b, uint zeile);
    void add_kreis(kreis k);
    void add_kreis(kreis k, uint zeile);
    void add_zylinder(zylinder z);
    void add_zylinder(zylinder z, uint zeile);
    void add_rechteck(rechteck3d rec);
    void add_rechteck(rechteck3d rec, uint zeile);
    void add_wuerfel(wuerfel w);
    void add_wuerfel(wuerfel w, uint zeile);

    void set_text(QString neuer_text);

    inline QString          text()
    {
        return Text.text();
    }
    inline text_zeilenweise text_zw()
    {
        return Text;
    }
    inline uint             akt_zeile()
    {
        return Aktuelle_zeile;
    }

private:
    uint                Aktuelle_zeile;
    text_zeilenweise    Text;

};

#endif // GEOMETRIETEXT_H
