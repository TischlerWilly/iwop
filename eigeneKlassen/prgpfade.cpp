#include "prgpfade.h"

prgpfade::prgpfade()
{
    dir_dlgbilder         = "dlgbilder";
    dir_wkzbilder         = "wkzbilder";
    inifile               = "konfiguration.ini";
    inifile_postprozessor = "postprozessor.ini";
    inifile_wkz           = "wkz.ini";
    ini_letzteDateien     = "letzte_dateien.ini";
    ini_cadMaschine       = "maschine_cad.ini";
}

//--------------------------------------Programmordner:
QString prgpfade::get_path_prg()
{
    QString tmp;
    tmp = "C:\\Program Files\\iwop";
    return tmp;
}
QString prgpfade::get_path_dlgbilder()
{
    QString tmp;
    tmp = get_path_prg();
    tmp += QDir::separator();
    tmp += dir_dlgbilder;
    return tmp;
}
QString prgpfade::get_path_dlgbilder_()
{
    QString tmp;
    tmp = get_path_dlgbilder();
    tmp += QDir::separator();
    return tmp;
}

//--------------------------------------Nutzerordner:
QString prgpfade::get_path_user()
{
    QString tmp;
    tmp = QDir::homePath();
    tmp += QDir::separator();
    tmp += ".iwop";
    return tmp;
}
QString prgpfade::get_path_user_postprozessor()
{
    QString tmp;
    tmp = QDir::homePath();
    tmp += QDir::separator();
    tmp += ".postprozessor";
    return tmp;
}
QString prgpfade::get_path_wkzbilder()
{
    QString tmp;
    tmp = get_path_user();
    tmp += QDir::separator();
    tmp += dir_wkzbilder;
    return tmp;
}
QString prgpfade::get_path_wkzbilder_()
{
    QString tmp;
    tmp = get_path_wkzbilder();
    tmp += QDir::separator();
    return tmp;
}
QString prgpfade::get_path_inifile()
{
    QString tmp;
    tmp = get_path_user();
    tmp += QDir::separator();
    tmp += inifile;
    return tmp;
}
QString prgpfade::get_path_inifile_postprozessor()
{
    QString tmp;
    tmp = get_path_user_postprozessor();
    tmp += QDir::separator();
    tmp += inifile_postprozessor;
    return tmp;
}
QString prgpfade::get_path_inifile_wkz()
{
    QString tmp;
    tmp = get_path_user();
    tmp += QDir::separator();
    tmp += inifile_wkz;
    return tmp;
}
QString prgpfade::get_path_iniLetzteDateien()
{
    QString tmp;
    tmp = get_path_user();
    tmp += QDir::separator();
    tmp += ini_letzteDateien;
    return tmp;
}
QString prgpfade::get_path_iniCadMaschine()
{
    QString tmp;
    tmp = get_path_user();
    tmp += QDir::separator();
    tmp += ini_cadMaschine;
    return tmp;
}

//--------------------------------------






