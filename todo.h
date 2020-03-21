#ifndef TODO_H
#define TODO_H

#define PROGRAMMVERSION     "1.2020.03.21"

/*







Zusatzwünsche:

- Schnelländerung Bohrgruppe
- HBE X umwandeln in HBE Y etc
- Fräsrichtung umkehren
- Fräsung mittig teilen (aus einer Fräsung 2 machen)
- Fräsgerade verlängern um / kürzen um
- Fräsbogenrichtung umkehren uzs/guzs

---------------------------------------------------------------------------In Arbeit:
---------------------------------------------------------------------------Fgerade
- programmtext.cpp
    ->aktualisiere_geo()
       >noch Ecken Verrunden umsetzen
---------------------------------------------------------------------------
---------------------------------------------------------------------------Fgerawi
- programmtext.cpp
    ->aktualisiere_geo()
        >noch Ecken Verrunden umsetzen
---------------------------------------------------------------------------
---------------------------------------------------------------------------FboUZS
- programmtext.cpp
    ->aktualisiere_geo()
       >noch Ecken Verrunden umsetzen
---------------------------------------------------------------------------
---------------------------------------------------------------------------FboGUZS
- programmtext.cpp
    ->aktualisiere_geo()
       >noch Ecken Verrunden umsetzen
---------------------------------------------------------------------------




---------------------------------------------------------------------------
ToDo für neue Dialoge anlegen:
- myDefines.h ->DLG_...
- define_xyz.h anlegen
- Qt-Designer-Formularklasse anlegen
- dialog_xyz.ui
    ->ui entwerfen
        -->WindowTitel
        -->modal true
        -->TAB-Reihenfolge
            ->slots anlegen
- dialog_xyz.h
- dialog_xyz.cpp
- mainwindow.h
    ->include
    ->DLG-Objekt anlegen (private:)
    ->vorlage_... anlegen(private: Variablen:)
- mainwindow.ui ->Menüeintrag erstellen
- Slot anlegen
- mainwindow.cpp
    ->Construktor ergänzen
        -->vorlage_xyz = xyz.get_defaut()
        -->Connect:
    ->loadConfig()
    ->saveConfig()
    ->slotSaveConfig(QString text)
    ->hideElemets_noFileIsOpen()
    ->showElements_aFileIsOpen()
    ->import_fmc(text_zeilenweise tz)
    ->export_fmc(text_zeilenweise tz)
    ->on_action_aendern_triggered()
    ->slotNeedWKZ(QString)
- programmtext.h
    ->include ergänzen
- programmtext.cpp
    ->aktualisiere_klartext_var()
    ->aktualisiere_geo()
    ->aktualisiere_anzeigetext()
---------------------------------------------------------------------------
---------------------------------------------------------------------------
ToDo für neue wkz-Dialoge anlegen:
- define_wkz ergänzen
- define_xyz.h anlegen
- Klasse wkz_xy schreiben
- Qt-Designer-Formularklasse anlegen
- dialog_xyz.ui
    ->ui entwerfen
        -->WindowTitel
        -->modal true
        -->TAB-Reihenfolge
            ->slots anlegen
- dialog_xyz.h
- dialog_xyz.cpp
- mainwindow.h
    ->include
    ->DLG-Objekt anlegen (private:)
- mainwindow.ui ->Button auf der Registerkarte wkz erstellen
- Slot anlegen
- mainwindow.cpp
    ->Construktor ergänzen
        -->Connect:
    ->on_action_aendern_triggered()
- werkzeug.cpp
    ->include ergänzen
- werkzeug.cpp
    ->werkzeug::get_anzeigetext()
---------------------------------------------------------------------------




*/
#endif // TODO_H
