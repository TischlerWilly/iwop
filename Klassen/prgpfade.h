#ifndef PRGPFADE_H
#define PRGPFADE_H

#include <QString>
#include <QDir>

class prgpfade
{
public:
    prgpfade();
    QString path_prg();
    QString path_user();
    QString path_user_postprozessor();
    QString path_dlgbilder();
    QString path_dlgbilder_();
    QString path_wkzbilder();
    QString path_wkzbilder_();
    QString path_inifile();
    QString path_inifile_postprozessor_V2();
    QString path_inifile_postprozessor_V3();
    QString path_inifile_wkz();
    QString path_iniLetzteDateien();
    QString path_iniCadMaschine();

private:
    //Ordner:
    QString Dir_wkzbilder;
    QString Dir_dlgbilder;

    //ini-Dateien:
    QString Inifile;
    QString Inifile_postprozessor_V2;
    QString Inifile_postprozessor_V3;
    QString Inifile_wkz;
    QString Ini_letzteDateien;
    QString Ini_cadMaschine;
};

#endif // PRGPFADE_H
