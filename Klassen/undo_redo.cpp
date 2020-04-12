#include "undo_redo.h"


undo_redo::undo_redo()
{
    set_groesse_max(20);
    clear();
}
void undo_redo::neu(programmtext t_neu)
{
    if((uint)Aktuelle_position+1 == Vector_t.size())
    {
        if(Vector_t.size() < Max_anzahl)
        {
            Vector_t.push_back(t_neu);
            Aktuelle_position++;
        }else
        {
            Vector_t.erase(Vector_t.begin());
            Vector_t.push_back(t_neu);
        }
    }else
    {
        Vector_t.erase(Vector_t.begin()+Aktuelle_position+1, Vector_t.end());
        Vector_t.push_back(t_neu);
        Aktuelle_position = Vector_t.size()-1;
    }
}

//----------------------------------set_xy:
void undo_redo::set_groesse_max(uint maximale_anzahl_an_wiederrufenschritten)
{
    if(maximale_anzahl_an_wiederrufenschritten > Vector_t.size())
    {
        Max_anzahl = maximale_anzahl_an_wiederrufenschritten;
    }
    if(maximale_anzahl_an_wiederrufenschritten < Vector_t.size())
    {
        Vector_t.clear();
        Max_anzahl = maximale_anzahl_an_wiederrufenschritten;
    }

}

//----------------------------------get_xy:
uint undo_redo::groesse_max()
{
    return Max_anzahl;
}
uint undo_redo::groesse()
{
    return Vector_t.size();
}
int undo_redo::erstes_aktives_element()
{
    return Erstes_aktives_element_t.at(Aktuelle_position);
}
int undo_redo::anz_aktive_elemente()
{
    return Anz_aktive_elemente_t.at(Aktuelle_position);
}

//----------------------------------Manipulationen:
void undo_redo::clear()
{
    Aktuelle_position = -1;
    Vector_t.clear();
}
programmtext undo_redo::undo()
{
    if(Aktuelle_position > 0)
    {
        Aktuelle_position--;
        return Vector_t.at(Aktuelle_position);
    }else
    {
        return Vector_t.at(0);
    }
}
programmtext undo_redo::redo()
{
    if((uint)Aktuelle_position+1 < Vector_t.size())
    {
        Aktuelle_position++;
        return Vector_t.at(Aktuelle_position);
    }else
    {
        return Vector_t.at(Aktuelle_position);
    }
}

//----------------------------------





