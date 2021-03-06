#include "prgpfade.h"

prgpfade::prgpfade()
{
    Dir_dlgbilder         = "dlgbilder";
    Dir_wkzbilder         = "wkzbilder";
    Inifile               = "konfiguration.ini";
    Inifile_postprozessor_V2 = "postprozessor.ini";
    Inifile_postprozessor_V3 = "einstellungen.ini";
    Inifile_wkz           = "wkz.ini";
    Ini_letzteDateien     = "letzte_dateien.ini";
    Ini_cadMaschine       = "maschine_cad.ini";
}

//--------------------------------------Programmordner:
QString prgpfade::path_prg()
{
    QString tmp;

    QString win = "C:\\Program Files";
    QDir win_dir(win);
    if(win_dir.exists())//Programm läuft wuf Windows
    {
        tmp = "C:\\Program Files\\iwop";
    }else
    {
        tmp = QDir::homePath();
        tmp += QDir::separator();
        tmp += ".iwop_prg";
    }
    return tmp;
}
QString prgpfade::path_dlgbilder()
{
    QString tmp;
    tmp = path_prg();
    tmp += QDir::separator();
    tmp += Dir_dlgbilder;
    return tmp;
}
QString prgpfade::path_dlgbilder_()
{
    QString tmp;
    tmp = path_dlgbilder();
    tmp += QDir::separator();
    return tmp;
}

//--------------------------------------Nutzerordner:
QString prgpfade::path_user()
{
    QString tmp;
    tmp = QDir::homePath();
    tmp += QDir::separator();

    QString win = "C:\\Program Files";
    QDir win_dir(win);
    if(win_dir.exists())//Programm läuft wuf Windows
    {
        tmp += ".iwop";
    }else
    {
        tmp += ".iwop_user";
    }
    return tmp;
}
QString prgpfade::path_user_postprozessor()
{
    QString tmp;
    tmp = QDir::homePath();
    tmp += QDir::separator();
    tmp += ".postprozessor";
    return tmp;
}
QString prgpfade::path_wkzbilder()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += Dir_wkzbilder;
    return tmp;
}
QString prgpfade::path_wkzbilder_()
{
    QString tmp;
    tmp = path_wkzbilder();
    tmp += QDir::separator();
    return tmp;
}
QString prgpfade::path_inifile()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += Inifile;
    return tmp;
}
QString prgpfade::path_inifile_postprozessor_V2()
{
    QString tmp;
    tmp = path_user_postprozessor();
    tmp += QDir::separator();
    tmp += Inifile_postprozessor_V2;
    return tmp;
}
QString prgpfade::path_inifile_postprozessor_V3()
{
    QString tmp;
    tmp = path_user_postprozessor();
    tmp += QDir::separator();
    tmp += Inifile_postprozessor_V3;
    return tmp;
}
QString prgpfade::path_inifile_wkz()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += Inifile_wkz;
    return tmp;
}
QString prgpfade::path_iniLetzteDateien()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += Ini_letzteDateien;
    return tmp;
}
QString prgpfade::path_iniCadMaschine()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += Ini_cadMaschine;
    return tmp;
}

//--------------------------------------






