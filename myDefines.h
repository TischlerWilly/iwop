#ifndef MYDEFINES_H
#define MYDEFINES_H
                            //home/oliver +
#define PFAD_ZUM_PROGRAMMORDNER     "/.iwop"
#define INI_FILE                    "/.iwop/konfiguration.ini"
#define PFAD_LETZTE_DATEIEN         "/.iwop/letzte_dateien.ini"
#define CAD_Maschine                "/.iwop/maschine_cad.ini"

#define PFAD_DLGBILDER              "C:\\Program Files\\iwop\\dlgbilder"
//#define WKZ_FILE                    "/.iwop/werkzeug.ini"
//#define WKZ_BILDER_PFAD             "/.iwop/werkzeugbilder/"


#define DATEIENDUNG_EIGENE          ".fmc"
#define DATEIENDUNG_BACKUP          ".bak_"
#define PROGRAMMNAME                "IWOP"
#define ANZAHL_LETZTER_DATEIEN      15
#define ANZAHL_OFFENER_DATEIEN      20

//-------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------Einstellungen:
#define BEGIN_EINSTELLUNGEN "Einstellungen:"
#define ENDE_EINSTELLUNGEN  "---------------------------"

//Parameter:
#define SETTINGS_PFAD_WERKZEUGE             "[Pfad Werkzeugliste]"
#define SETTINGS_ANZ_UNDO_T                 "[Anzahl Wiederrufenschritte Programmliste]"
#define SETTINGS_ANZ_UNDO_W                 "[Anzahl Wiederrufenschritte Werkzeugliste]"
#define SETTINGS_DXF_KLASSE_WSTNP           "[Klasse Werkstuecknullpunkt]"
#define SETTINGS_DXF_KLASSE_GEO             "[Klasse Geometrieen]"
#define SETTINGS_DXF_KLASSE_GEO_BEACHTEN    "[Klasse der Geometrieen beachten]"
#define SETTINGS_FKON_BERECHNEN             "[Fraeskonturen grafisch darstellen]"
#define ENDE_ZEILE                          "#ENDE#"

//-------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------Dialoge:
#define BEGIN_DIALOGE       "Dialoge:"
#define ENDE_DIALOGE        "---------------------------"
#define DLG_PKOPF               "[PGKOPF40]"
#define DLG_PENDE               "[PGENDE40]"
#define DLG_KOM                 "[SWKOMT40]"
#define DLG_HALT                "[SNHALT40]"
#define DLG_BO                  "[VBDMES40]"
#define DLG_SPIEGELN            "[SWSPIE40]"
#define LISTENENDE              ">ENDE"

#define FMCNULL                 "(NULL)"
#define FMCAUSGEBL              "@@@/=1"

//Parameter:
//Parameter müssen immer zwischen [ und ] definiert sein
#define ENDPAR        ";"//Ende eines Parameters z.B. Werkstücklänge

#define FEHLER              "Fehler"
#define NICHT_DEFINIERT     "ist nicht definiert"





#endif // MYDEFINES_H
