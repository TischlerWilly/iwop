#include "prgpfade.h"

prgpfade::prgpfade()
{
    Dir_dlgbilder         = "dlgbilder";
    Dir_wkzbilder         = "wkzbilder";
    Dir_toolbaricons      = "toolbaricons";
    Inifile               = "konfiguration.ini";
    Inifile_postprozessor = "postprozessor.ini";
    Inifile_wkz           = "wkz.ini";
    Ini_letzteDateien     = "letzte_dateien.ini";
    Ini_cadMaschine       = "maschine_cad.ini";
}

//--------------------------------------Programmordner:
QString prgpfade::path_prg()
{
    QString tmp;
    tmp = "C:\\Program Files\\iwop";
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
QString prgpfade::path_toolbaricons()
{
    QString tmp;
    tmp = path_prg();
    tmp += QDir::separator();
    tmp += Dir_toolbaricons;
    return tmp;
}
QString prgpfade::path_toolbaricons_()
{
    QString tmp;
    tmp = path_toolbaricons();
    tmp += QDir::separator();
    return tmp;
}

//--------------------------------------Nutzerordner:
QString prgpfade::path_user()
{
    QString tmp;
    tmp = QDir::homePath();
    tmp += QDir::separator();
    tmp += ".iwop";
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
QString prgpfade::path_inifile_postprozessor()
{
    QString tmp;
    tmp = path_user_postprozessor();
    tmp += QDir::separator();
    tmp += Inifile_postprozessor;
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






