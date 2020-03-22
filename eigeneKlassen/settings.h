#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <eigeneFunktionen/umwandeln.h>

class settings
{
public:
    settings();

    //Funkttionen set_xy:
    void set_anz_undo_prg(int anz);
    void set_anz_undo_prg(QString anz);
    void set_anz_undo_wkz(int anz);
    void set_anz_undo_wkz(QString anz);
    void set_option_path_opendialog(QString option);
    void set_option_path_opendialog_post();
    void set_option_path_opendialog_user();
    void set_userpath_opendialog(QString path);

    //Funkttionen get_xy:
    int anz_undo_prg_int();
    QString anz_undo_prg_qstring();
    int anz_undo_wkz_int();
    QString anz_undo_wkz_qstring();
    QString option_path_opendialog();
    QString userpath_opendialog();

private:
    int       anz_undo_prg;
    int       anz_undo_wkz;
    QString   stdpath_opdendialog_option;
    QString   stdpath_opdendialog_userpath;

};

#endif // SETTINGS_H
