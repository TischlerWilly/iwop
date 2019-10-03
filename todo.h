#ifndef TODO_H
#define TODO_H

#define PROGRAMMVERSION     "1.2019.09.26"

/*
->Dialog Halt
->Dialog Bohren











---------------------------------------------------------------------------
ToDo für neuen Dialoge anlegen:
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
    ->includes
        #include <QDir>
        #include "myDefines.h"
        #include "eigeneFunktionen/text.h"
        #include "eigeneFunktionen/umwandeln.h"
        #include "eigeneDefines/define_xyz.h"
    ->signals:
        void sendDialogData(QString text);
        void sendDialogDataModifyed(QString text);
        void signalSaveConfig(QString text);
    ->public:
        QString get_default()
    ->public slots:
        void getDialogData(QString text, bool openToChangeData);
    ->private:
        bool openToModifyData;
        QString dialogDataToString();
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
- programmtext.h
    ->include ergänzen
- programmtext.cpp
    ->aktualisiere_klartext_var()
    ->aktualisiere_geo()
    ->aktualisiere_anzeigetext()
---------------------------------------------------------------------------





*/
#endif // TODO_H
