#ifndef DARSTELLUNGSATRIBUTE_H
#define DARSTELLUNGSATRIBUTE_H

#include <QString>
#include "Funktionen/umwandeln.h"

class darstellungsatribute
{
public:
    darstellungsatribute();

    inline void set_farbe(QString neue_farbe)
    {
        Farbe = neue_farbe;
    }
    inline void set_farbe_fuellung(QString neue_farbe)
    {
        Farbe_fuellung = neue_farbe;
    }
    inline void set_stil(QString neuer_stil)
    {
        Stil = neuer_stil;
    }
    inline void set_linienbreite(int neue_breite)
    {
        Breite = neue_breite;
    }

    inline QString farbe()
    {
        return Farbe;
    }
    inline QString farbe_fuellung()
    {
        return Farbe_fuellung;
    }
    inline QString stil()
    {
        return Stil;
    }
    inline int linienbreite()
    {
        return Breite;
    }
    inline QString linienbreite_qstring()
    {
        return int_to_qstring(Breite);
    }

private:
    QString Farbe;
    QString Farbe_fuellung;
    QString Stil;
    int     Breite;
};

#define FARBE_KEINE       "keine"
#define FARBE_SCHWARZ     "schwarz"
#define FARBE_WEISS       "weiss"
#define FARBE_BLAU        "blau"
#define FARBE_HELLBLAU    "hellblau"
#define FARBE_ROT         "rot"
#define FARBE_ROSE        "rose"
#define FARBE_GRUEN       "gruen"
#define FARBE_GELB        "gelb"
#define FARBE_GRAU        "grau"
#define FARBE_DUNKELGRAU  "dunkelgrau"
#define FARBE_BRAUN       "braun"

#define STIL_TRANSPARENT    "transparent"
#define STIL_DURCHGEHEND    "durchgehend"
#define STIL_GESTRICHELT    "gestrichelt"
#define STIL_GEPUNKTET      "gepunktet"
#define STIL_STRICHP        "strichpunkt"
#define STIL_STRICHPP       "strichpp"


#endif // DARSTELLUNGSATRIBUTE_H
