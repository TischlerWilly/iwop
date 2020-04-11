#ifndef PROGRAMMTEXTE_H
#define PROGRAMMTEXTE_H


#include <QString>
#include <qvector.h>
#include "../eigeneFunktionen/umwandeln.h"
#include "programmtext.h"
#include "undo_redo.h"
#include "indexhisory.h"


class programmtexte
{
public:
    programmtexte();
    void add(programmtext p, QString name, undo_redo ur);
    void del();
    void del(uint index);
    void clear();

    //----------------------------------------------set_xy:
    void set_current_index(int index);
    void set_current_index(QString pfad);
    void set_index_vor();
    void set_index_nach();

    inline void set_prgname(QString name)
    {
        Vpname.replace(Current_index, name);
    }
    inline void set_prgname(QString name, uint index)
    {
        Vpname.replace(index, name);
    }

    //----------------------------------------------get_xy:
    int                 size();
    bool                isopen(QString pfad);
    bool                dateien_sind_offen();
    text_zeilenweise    names();

    inline  programmtext   *prgtext()
    {
        return &Vp[Current_index];
    }
    inline  programmtext   *prgtext(uint index)
    {
        return &Vp[index];
    }
    inline  undo_redo      *prg_undo_redo()
    {
        return &Vur[Current_index];
    }
    inline  undo_redo      *prg_undo_redo(uint index)
    {
        return &Vur[index];
    }
    inline  QString         prgname()
    {
        return Vpname.at(Current_index);
    }
    inline  QString         prgname(uint index)
    {
        return Vpname.at(index);
    }
    inline  uint            current_index()
    {
        return Current_index;
    }

    //----------------------------------------------Manipulationen:

    //----------------------------------------------

private:
    QVector<programmtext> Vp;    //Vector enthällt Programmtexte
    QVector<undo_redo>    Vur;   //Vector enthällt Wiederrufenschritte
    QVector<QString>      Vpname;//Vektor enthällt Dateinahmen (Pfade)

    uint        Current_index;
    indexhisory Ih;
};

#endif // PROGRAMMTEXTE_H
