#ifndef UNDO_REDO_TZ_H
#define UNDO_REDO_TZ_H

#include <vector>
#include "Klassen/text_zeilenweise.h"




class undo_redo_tz
{
public:
    undo_redo_tz();
    void neu(text_zeilenweise t_neu);

    //----------------------------------------set_xy:
    void set_groesse_max(uint maximale_anzahl_an_wiederrufenschritten);

    //----------------------------------------get_xy:
    uint groesse_max();
    uint groesse();
    int  erstes_aktives_element();
    int  anz_aktive_elemente();

    //----------------------------------------Manipulationen:
    void             clear();
    text_zeilenweise undo();
    text_zeilenweise redo();

    //----------------------------------------

private:
    std::vector<text_zeilenweise> Vector_t;
    std::vector<int>              Erstes_aktives_element_t;
    std::vector<int>              Anz_aktive_elemente_t;

    int  Aktuelle_position;
    uint Max_anzahl;




};

#endif // UNDO_REDO_TZ_H
