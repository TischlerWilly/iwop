#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include <vector>
#include "programmtext.h"




class undo_redo
{
public:
    undo_redo();
    void neu(programmtext t_neu);

    //----------------------------------set_xy:
    void set_groesse_max(uint maximale_anzahl_an_wiederrufenschritten);

    //----------------------------------get_xy:
    uint groesse_max();
    uint groesse();
    int  erstes_aktives_element();
    int  anz_aktive_elemente();

    //----------------------------------Manipulationen:
    void         clear();
    programmtext undo();
    programmtext redo();

    //----------------------------------

private:
    std::vector<programmtext>   Vector_t;
    std::vector<int>            Erstes_aktives_element_t;
    std::vector<int>            Anz_aktive_elemente_t;

    int     Aktuelle_position;
    uint    Max_anzahl;

};

#endif // UNDO_REDO_H
