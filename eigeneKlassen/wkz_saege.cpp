#include "wkz_saege.h"

wkz_saege::wkz_saege()
{
    clear();
}

void wkz_saege::clear()
{
    name        = "unbekannt";
    nr          = "0";
    vertikal    = true;
    dm          = 1;
    breite      = 1;
}
//-----------------------set_xy:
void wkz_saege::set_data(QString new_data)
{
    QString tmp;
    tmp = text_mitte(new_data, SAEGE_NAME, ENDPAR);
    set_name(tmp);
    tmp = text_mitte(new_data, SAEGE_NR, ENDPAR);
    set_nummer(tmp);
    tmp = text_mitte(new_data, SAEGE_VERTIKAL, ENDPAR);
    if(tmp == "1")
    {
        set_ausrichtung_vert(true);
    }else
    {
        set_ausrichtung_vert(false);
    }
    tmp = text_mitte(new_data, SAEGE_DM, ENDPAR);
    set_dm(tmp);
    tmp = text_mitte(new_data, SAEGE_BREITE, ENDPAR);
    set_breite(tmp);
}
void wkz_saege::set_name(QString neuer_name)
{
    name = neuer_name;
}
void wkz_saege::set_nummer(QString neue_nummer)
{
    nr = neue_nummer;
}
void wkz_saege::set_ausrichtung_vert(bool ist_vertikal)
{
    vertikal = ist_vertikal;
}
void wkz_saege::set_ausrichtung_hori(bool ist_horizontal)
{
    if(ist_horizontal)
    {
        vertikal = false;
    }else
    {
        vertikal = true;
    }
}
void wkz_saege::set_dm(double neuer_dm)
{
    dm = neuer_dm;
}
void wkz_saege::set_dm(QString neuer_dm)
{
    dm = neuer_dm.toDouble();
}
void wkz_saege::set_breite(double neue_breite)
{
    breite = neue_breite;
}
void wkz_saege::set_breite(QString neue_breite)
{
    breite = neue_breite.toDouble();
}

//-----------------------get_xy:
QString wkz_saege::get_data()
{
    QString data = WKZ_SAEGE;
    data += SAEGE_NAME;
    data += get_name();
    data += ENDPAR;

    data += SAEGE_NR;
    data += get_nummer();
    data += ENDPAR;

    data += SAEGE_VERTIKAL;
    if(ist_vertikal())
    {
        data += "1";
    }else
    {
        data += "0";
    }
    data += ENDPAR;

    data += SAEGE_DM;
    data += get_dm_qstring();
    data += ENDPAR;

    data += SAEGE_BREITE;
    data += get_breite_qstring();
    data += ENDPAR;

    return data;
}
QString wkz_saege::get_name()
{
    return name;
}
QString wkz_saege::get_nummer()
{
    return  nr;
}
bool wkz_saege::ist_vertikal()
{
    return vertikal;
}
bool wkz_saege::ist_horizontal()
{
    if(vertikal == true)
    {
        return false;
    }else
    {
        return true;
    }
}
double wkz_saege::get_dm()
{
    return dm;
}
QString wkz_saege::get_dm_qstring()
{
    return double_to_qstring(dm);
}
double wkz_saege::get_breite()
{
    return breite;
}
QString wkz_saege::get_breite_qstring()
{
    return  double_to_qstring(breite);
}


















