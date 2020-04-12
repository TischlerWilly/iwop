#ifndef TEXT_ZEILENWEISE_H
#define TEXT_ZEILENWEISE_H


#include <QString>
#include <QStringList>


class text_zeilenweise
{
public:
    text_zeilenweise();

    //---------------------------------------------set_xy:
    void    set_text(QString neuer_text);
    void    set_text(QStringList liste);
    void    set_trennzeichen(char neues_Trennzeichen);

    //---------------------------------------------get_xy:
    QString     zeile(uint zeilennummer);
    QString     zeilen(uint zeilennummer_beginn, uint zeilenmenge);
    uint        finde_Zeile(QString zeilentext);

    inline  QString     text()
    {
        return Text;
    }
    inline  char        trennzeichen()
    {
        return Trenner;
    }
    inline  uint        zeilenanzahl()
    {
        return Anzahl_der_zeilen;
    }

    //---------------------------------------------Manipulationen:
    void    clear();
    void    zeile_vorwegsetzen(QString zeilentext);
    void    zeile_anhaengen(QString zeilentext);
    void    zeilen_anhaengen(QString zeilentext);
    int     zeile_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext);
    int     zeilen_einfuegen(uint zeilennummer_vor_neuer_zeile, QString zeilentext);
    int     zeile_ersaetzen(uint zeilennummer, QString neuer_zeilentext);
    int     zeile_loeschen(uint zeilennummer);
    int     zeilen_loeschen(uint zeilennummer_beginn, uint zeilenmenge);

    //---------------------------------------------

private:
    QString     Text;
    uint        Anzahl_der_zeilen;
    char        Trenner;           //Zeichen, dass die Zeilen trennt

    void    zeilen_zaehlen();
    QString textzeile_ohne_Zeilenvorschuebe(QString zeilentext);

};

#endif // TEXT_ZEILENWEISE_H
