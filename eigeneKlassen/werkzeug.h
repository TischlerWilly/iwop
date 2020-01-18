#ifndef WERKZEUG_H
#define WERKZEUG_H

#include "eigeneDefines/define_wkz.h"
#include "eigeneKlassen/text_zeilenweise.h"

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
    QString zeile(uint zeilennummer);
    QString zeilen(uint zeilennummer_beginn, uint zeilenmenge);
    int zeile_ersaetzen(uint zeilennummer, QString neuer_zeilentext);
    int zeile_loeschen(uint zeilennummer);
    int zeilen_loeschen(uint zeilennummer_beginn, uint zeilenmenge);
    text_zeilenweise get_anzeigetext();

private:
    text_zeilenweise wkzlist;

};

#endif // WERKZEUG_H
