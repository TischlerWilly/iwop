#include "indexhisory.h"

indexhisory::indexhisory()
{

}

void indexhisory::add(int index)
{
    del(index);
    QString tmp = int_to_qstring(index);
    History.zeile_vorwegsetzen(tmp);
}

void indexhisory::del(int index)
{
    QString tmp = int_to_qstring(index);
    uint gefunden = 0;
    for(uint i=1; i<=History.zeilenanzahl() ;i++)
    {
        if(History.zeile(i) == tmp)
        {
            gefunden = i;
            break;
        }
    }
    if(gefunden !=0)
    {
        History.zeile_loeschen(gefunden);
    }
}

int indexhisory::get_current()
{
    if(History.get_text().isEmpty())
    {
        return 0;
    }else
    {
        return History.zeile(1).toInt();
    }
}

void indexhisory::clear()
{
    History.clear();
}

int indexhisory::index_vor()
{
    if(History.zeilenanzahl() > 1)
    {
        QString tmp = History.zeile(1);
        History.zeile_loeschen(1);
        History.zeile_anhaengen(tmp);
    }
    return get_current();
}

int indexhisory::index_nach()
{
    if(History.zeilenanzahl() > 1)
    {
        QString tmp = History.zeile(History.zeilenanzahl());
        History.zeile_loeschen(History.zeilenanzahl());
        History.zeile_vorwegsetzen(tmp);
    }
    return get_current();
}
