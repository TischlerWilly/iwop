#include "wkz_fraeser.h"

wkz_fraeser::wkz_fraeser()
{
    clear();
}
void wkz_fraeser::clear()
{
    Name        = "unbekannt";
    Nr          = "0";
    Vertikal    = true;
    Dm          = 1;
    Nutzl       = 1;
    Zustma      = 1;
    Drehri_uzs  = true;
    SpiegelWKZ_nr = "";
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
    tmp = text_mitte(new_data, FRAESER_SPIEGELNR, ENDPAR);
    set_spiegelwkznr(tmp);
}
void wkz_fraeser::set_name(QString neuer_name)
{
    Name = neuer_name;
}
void wkz_fraeser::set_nummer(QString neue_nummer)
{
    Nr = neue_nummer;
}
void wkz_fraeser::set_ausrichtung_vert(bool ist_vertikal)
{
    Vertikal = ist_vertikal;
}
void wkz_fraeser::set_ausrichtung_hori(bool ist_horizontal)
{
    if(ist_horizontal)
    {
        Vertikal = false;
    }else
    {
        Vertikal = true;
    }
}
void wkz_fraeser::set_dm(double neuer_dm)
{
    Dm = neuer_dm;
}
void wkz_fraeser::set_dm(QString neuer_dm)
{
    Dm = neuer_dm.toDouble();
}
void wkz_fraeser::set_nutzlaenge(double neue_nutzl)
{
    Nutzl = neue_nutzl;
}
void wkz_fraeser::set_nutzlaenge(QString neue_nutzl)
{
    Nutzl = neue_nutzl.toDouble();
}
void wkz_fraeser::set_zustellmas(double neues_zustma)
{
    Zustma = neues_zustma;
}
void wkz_fraeser::set_zustellmas(QString neuer_zustma)
{
    Zustma = neuer_zustma.toDouble();
}
void wkz_fraeser::set_drehrichtung_uzs(bool im_uhrzeigersinn)
{
    Drehri_uzs = im_uhrzeigersinn;
}
void wkz_fraeser::set_spiegelwkznr(QString nr)
{
    SpiegelWKZ_nr = nr;
}

//-----------------------get_xy:
QString wkz_fraeser::text()
{
    QString data = WKZ_FRAESER;
    data += FRAESER_NAME;
    data += name();
    data += ENDPAR;

    data += FRAESER_NR;
    data += nummer();
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
    data += dm_qstring();
    data += ENDPAR;

    data += FRAESER_NUTZL;
    data += nutzlaenge_qstring();
    data += ENDPAR;

    data += FRAESER_ZUSTMAS;
    data += zustellmas_qstring();
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

    data += FRAESER_SPIEGELNR;
    data += spiegelwkznr();
    data += ENDPAR;

    return data;
}
QString wkz_fraeser::name()
{
    return Name;
}
QString wkz_fraeser::nummer()
{
    return  Nr;
}
bool wkz_fraeser::ist_vertikal()
{
    return Vertikal;
}
bool wkz_fraeser::ist_horizontal()
{
    if(Vertikal == true)
    {
        return false;
    }else
    {
        return true;
    }
}
double wkz_fraeser::dm()
{
    return Dm;
}
QString wkz_fraeser::dm_qstring()
{
    return double_to_qstring(Dm);
}
double wkz_fraeser::nutzlaenge()
{
    return Nutzl;
}
QString wkz_fraeser::nutzlaenge_qstring()
{
    return  double_to_qstring(Nutzl);
}
double wkz_fraeser::zustellmas()
{
    return Zustma;
}
QString wkz_fraeser::zustellmas_qstring()
{
    return double_to_qstring(Zustma);
}
bool wkz_fraeser::dreht_im_uzs()
{
    return Drehri_uzs;
}
QString wkz_fraeser::spiegelwkznr()
{
    return SpiegelWKZ_nr;
}




















