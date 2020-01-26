#include "wkz_fraeser.h"

wkz_fraeser::wkz_fraeser()
{
    clear();
}
void wkz_fraeser::clear()
{
    name        = "unbekannt";
    nr          = "0";
    vertikal    = true;
    dm          = 1;
    nutzl       = 1;
    zustma      = 1;
    drehri_uzs  = true;
}
//-----------------------set_xy:
void wkz_fraeser::set_data(QString new_data)
{
    QString tmp;
    tmp = text_mitte(new_data, FRAESER_NAME, ENDPAR);
    set_name(tmp);
    tmp = text_mitte(new_data, FRAESER_NR, ENDPAR);
    set_nummer(tmp);
    tmp = text_mitte(new_data, FRAESER_VERTIKAL, ENDPAR);
    if(tmp == "1")
    {
        set_ausrichtung_vert(true);
    }else
    {
        set_ausrichtung_vert(false);
    }
    tmp = text_mitte(new_data, FRAESER_DM, ENDPAR);
    set_dm(tmp);
    tmp = text_mitte(new_data, FRAESER_NUTZL, ENDPAR);
    set_nutzlaenge(tmp);
    tmp = text_mitte(new_data, FRAESER_ZUSTMAS, ENDPAR);
    set_zustellmas(tmp);
    tmp = text_mitte(new_data, FRAESER_UZS, ENDPAR);
    if(tmp == "1")
    {
        set_drehrichtung_uzs(true);
    }else
    {
        set_drehrichtung_uzs(false);
    }
}
void wkz_fraeser::set_name(QString neuer_name)
{
    name = neuer_name;
}
void wkz_fraeser::set_nummer(QString neue_nummer)
{
    nr = neue_nummer;
}
void wkz_fraeser::set_ausrichtung_vert(bool ist_vertikal)
{
    vertikal = ist_vertikal;
}
void wkz_fraeser::set_ausrichtung_hori(bool ist_horizontal)
{
    if(ist_horizontal)
    {
        vertikal = false;
    }else
    {
        vertikal = true;
    }
}
void wkz_fraeser::set_dm(double neuer_dm)
{
    dm = neuer_dm;
}
void wkz_fraeser::set_dm(QString neuer_dm)
{
    dm = neuer_dm.toDouble();
}
void wkz_fraeser::set_nutzlaenge(double neue_nutzl)
{
    nutzl = neue_nutzl;
}
void wkz_fraeser::set_nutzlaenge(QString neue_nutzl)
{
    nutzl = neue_nutzl.toDouble();
}
void wkz_fraeser::set_zustellmas(double neues_zustma)
{
    zustma = neues_zustma;
}
void wkz_fraeser::set_zustellmas(QString neuer_zustma)
{
    zustma = neuer_zustma.toDouble();
}
void wkz_fraeser::set_drehrichtung_uzs(bool im_uhrzeigersinn)
{
    drehri_uzs = im_uhrzeigersinn;
}

//-----------------------get_xy:
QString wkz_fraeser::get_data()
{
    QString data = WKZ_FRAESER;
    data += FRAESER_NAME;
    data += get_name();
    data += ENDPAR;

    data += FRAESER_NR;
    data += get_nummer();
    data += ENDPAR;

    data += FRAESER_VERTIKAL;
    if(ist_vertikal())
    {
        data += "1";
    }else
    {
        data += "0";
    }
    data += ENDPAR;

    data += FRAESER_DM;
    data += get_dm_qstring();
    data += ENDPAR;

    data += FRAESER_NUTZL;
    data += get_nutzlaenge_qstring();
    data += ENDPAR;

    data += FRAESER_ZUSTMAS;
    data += get_zustellmas_qstring();
    data += ENDPAR;

    data += FRAESER_UZS;
    if(dreht_im_uzs())
    {
        data += "1";
    }else
    {
        data += "0";
    }
    data += ENDPAR;

    return data;
}
QString wkz_fraeser::get_name()
{
    return name;
}
QString wkz_fraeser::get_nummer()
{
    return  nr;
}
bool wkz_fraeser::ist_vertikal()
{
    return vertikal;
}
bool wkz_fraeser::ist_horizontal()
{
    if(vertikal == true)
    {
        return false;
    }else
    {
        return true;
    }
}
double wkz_fraeser::get_dm()
{
    return dm;
}
QString wkz_fraeser::get_dm_qstring()
{
    return double_to_qstring(dm);
}
double wkz_fraeser::get_nutzlaenge()
{
    return nutzl;
}
QString wkz_fraeser::get_nutzlaenge_qstring()
{
    return  double_to_qstring(nutzl);
}
double wkz_fraeser::get_zustellmas()
{
    return zustma;
}
QString wkz_fraeser::get_zustellmas_qstring()
{
    return double_to_qstring(zustma);
}
bool wkz_fraeser::dreht_im_uzs()
{
    return drehri_uzs;
}





















