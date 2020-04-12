#ifndef DEFINE_FAUF_H
#define DEFINE_FAUF_H

//#define DLG_FAUF                "[KAFRAE40]"

//--------------------------------Parameternahmen in der fmc-Datei
#define FAUF_WKZ       "WKZID=" //Name des WKZ z.B: IMA601
#define FAUF_X         "X="
#define FAUF_Y         "Y="
#define FAUF_Z         "Z="
#define FAUF_ERG       "EBG=" //Ecken runden global
#define FAUF_KADI      "KD="
#define FAUF_KOR       "TRKOR="
#define FAUF_ANTYP     "TYPAN="
#define FAUF_ABTYP     "TYPAB="
#define FAUF_EINTYP    "TYPEIN="
#define FAUF_ANWEG     "LGEAN="
#define FAUF_ABWEG     "LGEAB="
#define FAUF_ANVO      "FAN="
#define FAUF_VO        "F="
#define FAUF_DREHZ     "N="
#define FAUF_EVERS     "EVS=" //Ecken verschleifen
#define FAUF_WKZAKT    "WKZAKTUELL="
#define FAUF_BEZ       "BEZB="
#define FAUF_AFB       "AFB="
#define FAUF_AUSGEBL   "@@@/=1"

//--------------------------------Parameternahmen der Variablen
//Variabelnnahmen müssen immer mit "[" beginnen und mit "]" enden
#define VAR_FAUF_X         "[KAX]"
#define VAR_FAUF_Y         "[KAY]"
#define VAR_FAUF_Z         "[AZ]"
#define VAR_FAUF_ERG       "[EBG]" //Ecken runden global
#define VAR_FAUF_KADI      "[KD]"
#define VAR_FAUF_KOR       "[KB]"
#define VAR_FAUF_ANTYP     "[AT]"
#define VAR_FAUF_ABTYP     "[ABT]"
#define VAR_FAUF_EINTYP    "[ZTYP]"
#define VAR_FAUF_ANWEG     "[AW]"
#define VAR_FAUF_ABWEG     "[ABW]"
#define VAR_FAUF_ANVO      "[AV]"
#define VAR_FAUF_VO        "[V]"
#define VAR_FAUF_DREHZ     "[N]"
#define VAR_FAUF_EVERS     "[EVS]" //Ecken verschleifen


#endif // DEFINE_FAUF_H
