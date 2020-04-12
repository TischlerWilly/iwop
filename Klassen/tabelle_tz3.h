#ifndef tabelle_tz3_H
#define tabelle_tz3_H

#include "text_zeilenweise.h"


class tabelle_tz3
{
public:
    tabelle_tz3();

    //--------------------------------------------------------set_xy:
    void set_trennzeichen_zeilen(char neues_Trennzeichen);
    void set_trennzeichen_spalten(char neues_Trennzeichen);
    void set_trennzeichen_eintraege(char neues_Trennzeichen);
    void set_text(QString neuer_text);

    //--------------------------------------------------------get_xy:
    QString zeile(uint zeilennummer);
    QString spalte(uint zeilennummer, uint spaltennummer);
    QString spalten();
    QString eintrag(uint zeilennummer, uint spaltennummer, uint eintragsnummer);
    uint    spaltenzahl(uint zeilennummer);
    QString folgespalte(uint zeile_aktuell, uint spalte_aktuell);
    QString vorherigespalte(uint zeile_aktuell, uint spalte_aktuell);

    inline QString text()
    {
        return Zeile.text();
    }

    //--------------------------------------------------------Manipulationen:
    bool zeile_ersaetzen(uint zeilennummer, QString neuer_text);
    bool spalte_ersatzen(uint zeilennummer, uint spaltennummer, QString neuer_text);
    bool vorherigespalte_ersaetzen(uint zeile_aktuell, uint spalte_aktuell, QString neuer_text);
    bool eintrag_ersatzen(uint zeilennummer, uint spaltennummer, uint eintragsnummer, QString neuer_text);
    void zeile_anhaengen(QString neuer_text);
    bool spalte_anhaengen(uint zeilennummer, QString neuer_text);
    bool eintrag_anhaengen(uint zeilennummer, uint spaltennummer, QString neuer_text);

    //--------------------------------------------------------

private:

    text_zeilenweise Zeile;
    text_zeilenweise Spalte;//ein Eintrag in einer Zeile
    text_zeilenweise Eintrag;



};

#endif // tabelle_tz3_H
