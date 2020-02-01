#ifndef WERKZEUG_H
#define WERKZEUG_H

#include "eigeneDefines/define_wkz.h"
#include "eigeneDefines/define_wkz_fraeser.h"
#include "eigeneDefines/define_wkz_saege.h"
#include "eigeneKlassen/text_zeilenweise.h"
#include "eigeneKlassen/undo_redo_tz.h"
#include "eigeneFunktionen/text.h"

class werkzeug
{
public:
    werkzeug();

    //------------set_xy:
    void set_text(QString neuer_Text);
    void zeile_anhaengen(QString wkz);
    int  zeile_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext);
    int  zeilen_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext);

    //------------get_xy:
    QString get_text();
    QString zeile(uint zeilennummer);
    QString zeilen(uint zeilennummer_beginn, uint zeilenmenge);
    int zeile_ersaetzen(uint zeilennummer, QString neuer_zeilentext);
    int zeile_loeschen(uint zeilennummer);
    int zeilen_loeschen(uint zeilennummer_beginn, uint zeilenmenge);
    text_zeilenweise get_anzeigetext();
    text_zeilenweise get_wkzlist(QString wkztyp, QString paramfilter = "");

    //------------
    //MainWindow::aktualisiere_anzeigetext_wkz(bool undo_redo_on = true);
    //MainWindow::Rückgängig/Wiederholen
    void undo_redo_neu();
    void undo();
    void redo();
    void set_undo_redo_anz(uint anz);

private:
    text_zeilenweise wkzlist;
    undo_redo_tz vur;      //enthällt Wiederrufenschritte

};

#endif // WERKZEUG_H
