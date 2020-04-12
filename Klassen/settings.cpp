#include "settings.h"

settings::settings()
{
    //Default-Werte:
    Anz_undo_prg = 10;
    Anz_undo_wkz = 10;
    Stdpath_opdendialog_option = "user";
    Stdpath_opdendialog_userpath = "";
    Entwicklermodus = false;
}

//------------------------------Funkttionen set_xy:
void settings::set_anz_undo_prg(int anz)
{
    Anz_undo_prg = anz;
}
void settings::set_anz_undo_prg(QString anz)
{
    set_anz_undo_prg(anz.toInt());
}
void settings::set_anz_undo_wkz(int anz)
{
    Anz_undo_wkz = anz;
}
void settings::set_anz_undo_wkz(QString anz)
{
    set_anz_undo_wkz(anz.toInt());
}
void settings::set_option_path_opendialog(QString option)
{
    Stdpath_opdendialog_option = option;
    //optionen:
    //post  --> Pfad des Postprozessors
    //user  --> Benutzerdefinierter Pfad
}
void settings::set_option_path_opendialog_post()
{
    set_option_path_opendialog("post");
}
void settings::set_option_path_opendialog_user()
{
    set_option_path_opendialog("user");
}
void settings::set_userpath_opendialog(QString path)
{
    Stdpath_opdendialog_userpath = path;
}
void settings::set_entwickermod(bool mod)
{
    Entwicklermodus = mod;
}

//------------------------------Funkttionen get_xy:
int settings::anz_undo_prg_int()
{
    return Anz_undo_prg;
}
QString settings::anz_undo_prg_qstring()
{
    return int_to_qstring(Anz_undo_prg);
}
int settings::anz_undo_wkz_int()
{
    return Anz_undo_wkz;
}
QString settings::anz_undo_wkz_qstring()
{
    return int_to_qstring(Anz_undo_wkz);
}
QString settings::option_path_opendialog()
{
    return Stdpath_opdendialog_option;
}
QString settings::userpath_opendialog()
{
    return Stdpath_opdendialog_userpath;
}
bool settings::entwicklermod()
{
    return Entwicklermodus;
}














