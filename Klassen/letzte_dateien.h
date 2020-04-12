#ifndef LETZTE_DATEIEN_H
#define LETZTE_DATEIEN_H

#include "Klassen/text_zeilenweise.h"

class letzte_dateien
{
public:
    letzte_dateien();
    letzte_dateien(uint anzahl_der_eintraege);

    QString text();
    inline uint anz_eintreage()
    {
        return Anz_eintraege;
    }

    void set_text(QString liste);
    void set_anz_eintreage(uint neue_anz);
    void datei_merken(QString name);
    void datei_vergessen(QString name);



private:
    text_zeilenweise Dateinamen;
    uint Anz_eintraege;



};

#endif // LETZTE_DATEIEN_H
