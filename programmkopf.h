#ifndef PROGRAMMKOPF_H
#define PROGRAMMKOPF_H

#include <QString>
#include "dialogprgkopf.h"

class programmkopf
{
public:
    programmkopf();
    void neu();

private:
    DialogPrgKopf dialog;

    QString kom1;               //Kommentar 1
    QString kom2;               //Kommentar 2
    QString l;                  //Länge
    QString b;                  //Breite
    QString d;                  //Dicke
    QString fuenfseiten;         //Fünf seiten (Darstellung Werkstückkante)
    QString spiegeln;           //Spiegeln
    QString mehrplatzbelegart;  //Mehrplatzbelegart
    QString xversatz;           //X-Versatz
    QString yversatz;           //Y-Versatz
    QString rol;                //Rohteillänge
    QString rob;                //Rohteilbreite
    QString loesen;             //automatisch lösen
    QString schabh;             //Schablonenhöhe
    QString siabst;             //Sicherheitsabstand
    QString parkpos;            //Parkposition
    QString bez;                //Bezeichnung
    QString afb;                //Ausführbedingung
    QString nachlb;             //Nachladebetrieb
    bool eingeblendet;          //1 == eingeblendet;  0 == ausgeblendet
};

#endif // PROGRAMMKOPF_H
