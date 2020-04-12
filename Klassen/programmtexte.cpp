#include "programmtexte.h"

programmtexte::programmtexte()
{
    clear();
}
void programmtexte::add(programmtext p, QString name, undo_redo ur)
{
    Vp.push_back(p);
    Vpname.push_back(name);
    Vur.push_back(ur);
    set_current_index(Vp.size()-1);
    Ih.add(Vp.size()-1);
}
void programmtexte::del()
{
    if(Vp.size() > 1)//immer eine Instanz behalten
    {        
        Vp.erase(Vp.begin() + Current_index);
        Vur.erase(Vur.begin() + Current_index);
        Vpname.erase(Vpname.begin() + Current_index);
        Ih.del(Current_index);
        set_current_index(Ih.get_current());
    }
    if(Vp.size() == 1)
    {
        clear();
    }
}
void programmtexte::del(uint index)
{
    if(index <= Vp.size()-1 && index > 1)//immer eine Instanz behalten
    {
        Vp.erase(Vp.begin() + index);
        Vur.erase(Vur.begin() + index);
        Vpname.erase(Vpname.begin() + index);
        Ih.del(index);
        set_current_index(Ih.get_current());
    }
}
void programmtexte::clear()
{
    Vp.clear();
    Vur.clear();
    Vpname.clear();
    Ih.clear();

    //immer eine Instanz behalten:
    programmtext t;
    Vp.push_back(t);
    QString name = NICHT_DEFINIERT;
    Vpname.push_back(name);
    undo_redo ur;
    Vur.push_back(ur);
    Current_index = 0;
}

//----------------------------------------------set_xy:
void programmtexte::set_current_index(int index)
{
    if(index <= Vp.size()-1)
    {
        Current_index = index;
        Ih.add(index);
    }
}
void programmtexte::set_current_index(QString pfad)
{
    for(int i=0; i<Vpname.size() ;i++)
    {
        if(Vpname.at(i) == pfad)
        {
            set_current_index(i);
            Ih.add(i);
        }
    }
}
void programmtexte::set_index_vor()
{
    set_current_index(Ih.index_vor());
}
void programmtexte::set_index_nach()
{
    set_current_index(Ih.index_nach());
}

//----------------------------------------------get_xy:
int programmtexte::size()
{
    int size = Vp.size();//gibt die Anzahl der Elemente wieder
    size = size-1;//-1 weil immer 1 Element vorhanden bleibt was jedoch nicht mitgezählt werden soll
    return size;
}
bool programmtexte::isopen(QString pfad)
{
    bool offen = false;
    for(int i=0; i<Vpname.size() ;i++)
    {
        if(Vpname.at(i) == pfad)
        {
            offen = true;
            break;
        }
    }
    return offen;
}
bool programmtexte::dateien_sind_offen()
{
    if(size() > 0)
    {
        return true;
    }else
    {
        return false;
    }
}
text_zeilenweise programmtexte::names()
{
    text_zeilenweise namen;
    for(int i = 1; i<Vpname.count() ; i++)//mit 1 beginnen statt mit 0 weil erstes Element ist "NICHT_DEFINIERT"
    {
        namen.zeile_anhaengen(Vpname.at(i));
    }
    return namen;
}

//----------------------------------------------Manipulationen:

//----------------------------------------------















