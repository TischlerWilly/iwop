#ifndef PRGPFADE_H
#define PRGPFADE_H

#include <QString>
#include <QDir>

class prgpfade
{
public:
    prgpfade();
    QString get_path_prg();
    QString get_path_user();
    QString get_path_dlgbilder();
    QString get_path_dlgbilder_();
    QString get_path_wkzbilder();
    QString get_path_wkzbilder_();
    QString get_path_inifile();
    QString get_path_iniLetzteDateien();
    QString get_path_iniCadMaschine();

private:
    //Ordner:
    QString dir_wkzbilder;
    QString dir_dlgbilder;

    //ini-Dateien:
    QString inifile;
    QString ini_letzteDateien;
    QString ini_cadMaschine;
};

#endif // PRGPFADE_H