#ifndef UNDO_REDO_TZ_H
#define UNDO_REDO_TZ_H

#include <vector>
#include "eigeneKlassen/text_zeilenweise.h"




class undo_redo_tz
{
public:
    undo_redo_tz();
    void neu(text_zeilenweise t_neu);
    void set_groesse_max(uint maximale_anzahl_an_wiederrufenschritten);
    uint get_groesse_max();
    uint get_groesse();
    void clear();
    text_zeilenweise undo();
    text_zeilenweise redo();
    int get_erstes_aktives_element();
    int get_anz_aktive_elemente();


private:
    std::vector<text_zeilenweise> vector_t;
    std::vector<int> erstes_aktives_element_t;
    std::vector<int> anz_aktive_elemente_t;

    int aktuelle_position;
    uint max_anzahl;




};

#endif // UNDO_REDO_TZ_H
