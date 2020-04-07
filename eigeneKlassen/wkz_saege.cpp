#include "wkz_saege.h"

wkz_saege::wkz_saege()
{
    clear();
}

void wkz_saege::clear()
{
    Name        = "unbekannt";
    Nr          = "0";
    Vertikal    = true;
    Dm          = 1;
    Breite      = 1;
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
    Name = neuer_name;
}
void wkz_saege::set_nummer(QString neue_nummer)
{
    Nr = neue_nummer;
}
void wkz_saege::set_ausrichtung_vert(bool ist_vertikal)
{
    Vertikal = ist_vertikal;
}
void wkz_saege::set_ausrichtung_hori(bool ist_horizontal)
{
    if(ist_horizontal)
    {
        Vertikal = false;
    }else
    {
        Vertikal = true;
    }
}
void wkz_saege::set_dm(double neuer_dm)
{
    Dm = neuer_dm;
}
void wkz_saege::set_dm(QString neuer_dm)
{
    Dm = neuer_dm.toDouble();
}
void wkz_saege::set_breite(double neue_breite)
{
    Breite = neue_breite;
}
void wkz_saege::set_breite(QString neue_breite)
{
    Breite = neue_breite.toDouble();
}

//-----------------------get_xy:
QString wkz_saege::text()
{
    QString data = WKZ_SAEGE;
    data += SAEGE_NAME;
    data += name();
    data += ENDPAR;

    data += SAEGE_NR;
    data += nummer();
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
    data += dm_qstring();
    data += ENDPAR;

    data += SAEGE_BREITE;
    data += breite_qstring();
    data += ENDPAR;

    return data;
}
QString wkz_saege::name()
{
    return Name;
}
QString wkz_saege::nummer()
{
    return  Nr;
}
bool wkz_saege::ist_vertikal()
{
    return Vertikal;
}
bool wkz_saege::ist_horizontal()
{
    if(Vertikal == true)
    {
        return false;
    }else
    {
        return true;
    }
}
double wkz_saege::dm()
{
    return Dm;
}
QString wkz_saege::dm_qstring()
{
    return double_to_qstring(Dm);
}
double wkz_saege::breite()
{
    return Breite;
}
QString wkz_saege::breite_qstring()
{
    return  double_to_qstring(Breite);
}


















