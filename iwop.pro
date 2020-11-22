#-------------------------------------------------
#
# Project created by QtCreator 2019-08-15T19:10:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iwop
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Dialoge/dialog_bohren.cpp \
        Dialoge/dialog_bohren_x.cpp \
        Dialoge/dialog_bohren_y.cpp \
        Dialoge/dialog_einstellungen.cpp \
        Dialoge/dialog_fabf.cpp \
        Dialoge/dialog_fauf.cpp \
        Dialoge/dialog_fboguzs.cpp \
        Dialoge/dialog_fbouzs.cpp \
        Dialoge/dialog_fgerade.cpp \
        Dialoge/dialog_fgerawi.cpp \
        Dialoge/dialog_fraeser.cpp \
        Dialoge/dialog_halt.cpp \
        Dialoge/dialog_hbexm.cpp \
        Dialoge/dialog_hbexp.cpp \
        Dialoge/dialog_hbeym.cpp \
        Dialoge/dialog_hbeyp.cpp \
        Dialoge/dialog_kom.cpp \
        Dialoge/dialog_kta.cpp \
        Dialoge/dialog_lage_aendern.cpp \
        Dialoge/dialog_loreiae.cpp \
        Dialoge/dialog_loreima.cpp \
        Dialoge/dialog_nut.cpp \
        Dialoge/dialog_prgende.cpp \
        Dialoge/dialog_prgkopf.cpp \
        Dialoge/dialog_programmlisten.cpp \
        Dialoge/dialog_rta.cpp \
        Dialoge/dialog_saege.cpp \
        Dialoge/dialog_schnellaenderung.cpp \
        Dialoge/dialog_spiegeln.cpp \
        Dialoge/dialog_topf.cpp \
        Dialoge/dialog_userinput.cpp \
        Dialoge/dialog_var.cpp \
        Dialoge/dialog_var10.cpp \
        Klassen/geo/geofunktionen.cpp \
        Funktionen/myfunktion.cpp \
        Funktionen/runden.cpp \
        Funktionen/text.cpp \
        Funktionen/umwandeln.cpp \
        Klassen/geo/bogen.cpp \
        Klassen/geo/darstellungsatribute.cpp \
        Klassen/formel.cpp \
        Klassen/geo/geometrietext.cpp \
        Klassen/indexhisory.cpp \
        Klassen/geo/kreis.cpp \
        Klassen/letzte_dateien.cpp \
        Klassen/prgpfade.cpp \
        Klassen/programmtext.cpp \
        Klassen/programmtexte.cpp \
        Klassen/geo/punkt2d.cpp \
        Klassen/geo/punkt3d.cpp \
        Klassen/geo/rechteck3d.cpp \
        Klassen/settings.cpp \
        Klassen/geo/strecke.cpp \
        Klassen/tabelle_tz3.cpp \
        Klassen/text_zeilenweise.cpp \
        Klassen/undo_redo.cpp \
        Klassen/undo_redo_tz.cpp \
        Klassen/userinput.cpp \
        Klassen/geo/vorschau.cpp \
        Klassen/wenndannsonst.cpp \
        Klassen/werkzeug.cpp \
        Klassen/wkz_fraeser.cpp \
        Klassen/wkz_saege.cpp \
        Klassen/geo/wuerfel.cpp \
        Klassen/geo/zylinder.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        Dialoge/dialog_bohren.h \
        Dialoge/dialog_bohren_x.h \
        Dialoge/dialog_bohren_y.h \
        Dialoge/dialog_einstellungen.h \
        Dialoge/dialog_fabf.h \
        Dialoge/dialog_fauf.h \
        Dialoge/dialog_fboguzs.h \
        Dialoge/dialog_fbouzs.h \
        Dialoge/dialog_fgerade.h \
        Dialoge/dialog_fgerawi.h \
        Dialoge/dialog_fraeser.h \
        Dialoge/dialog_halt.h \
        Dialoge/dialog_hbexm.h \
        Dialoge/dialog_hbexp.h \
        Dialoge/dialog_hbeym.h \
        Dialoge/dialog_hbeyp.h \
        Dialoge/dialog_kom.h \
        Dialoge/dialog_kta.h \
        Dialoge/dialog_lage_aendern.h \
        Dialoge/dialog_loreiae.h \
        Dialoge/dialog_loreima.h \
        Dialoge/dialog_nut.h \
        Dialoge/dialog_prgende.h \
        Dialoge/dialog_prgkopf.h \
        Dialoge/dialog_programmlisten.h \
        Dialoge/dialog_rta.h \
        Dialoge/dialog_saege.h \
        Dialoge/dialog_schnellaenderung.h \
        Dialoge/dialog_spiegeln.h \
        Dialoge/dialog_topf.h \
        Dialoge/dialog_userinput.h \
        Dialoge/dialog_var.h \
        Dialoge/dialog_var10.h \
        Defines/define_allegm_var.h \
        Defines/define_bo.h \
        Defines/define_boX.h \
        Defines/define_boY.h \
        Defines/define_fabf.h \
        Defines/define_fauf.h \
        Defines/define_fboguzs.h \
        Defines/define_fbouzs.h \
        Defines/define_fgerade.h \
        Defines/define_fgerawi.h \
        Defines/define_hbexm.h \
        Defines/define_hbexp.h \
        Defines/define_hbeym.h \
        Defines/define_hbeyp.h \
        Defines/define_kta.h \
        Defines/define_lage_aendern.h \
        Defines/define_loreiae.h \
        Defines/define_loreima.h \
        Defines/define_nut.h \
        Defines/define_prgende.h \
        Defines/define_prgkopf.h \
        Defines/define_rta.h \
        Defines/define_spiegeln.h \
        Defines/define_topf.h \
        Defines/define_var.h \
        Defines/define_var10.h \
        Defines/define_wkz.h \
        Defines/define_wkz_fraeser.h \
        Defines/define_wkz_saege.h \
        Klassen/geo/defines_geometrie.h \
        Defines/defines_halt.h \
        Defines/defines_kom.h \
        Klassen/geo/geofunktionen.h \
        Funktionen/myfunktion.h \
        Funktionen/runden.h \
        Funktionen/text.h \
        Funktionen/umwandeln.h \
        Klassen/geo/bogen.h \
        Klassen/geo/darstellungsatribute.h \
        Klassen/formel.h \
        Klassen/geo/geometrietext.h \
        Klassen/geo/makro_geometrie.h \
        Klassen/indexhisory.h \
        Klassen/geo/kreis.h \
        Klassen/letzte_dateien.h \
        Klassen/prgpfade.h \
        Klassen/programmtext.h \
        Klassen/programmtexte.h \
        Klassen/geo/punkt2d.h \
        Klassen/geo/punkt3d.h \
        Klassen/geo/rechteck3d.h \
        Klassen/settings.h \
        Klassen/geo/strecke.h \
        Klassen/tabelle_tz3.h \
        Klassen/text_zeilenweise.h \
        Klassen/undo_redo.h \
        Klassen/undo_redo_tz.h \
        Klassen/userinput.h \
        Klassen/geo/vorschau.h \
        Klassen/wenndannsonst.h \
        Klassen/werkzeug.h \
        Klassen/wkz_fraeser.h \
        Klassen/wkz_saege.h \
        Klassen/geo/wuerfel.h \
        Klassen/geo/zylinder.h \
        Struncts/punkt.h \
        mainwindow.h \
        myDefines.h \
        todo.h

FORMS += \
        Dialoge/dialog_bohren.ui \
        Dialoge/dialog_bohren_x.ui \
        Dialoge/dialog_bohren_y.ui \
        Dialoge/dialog_einstellungen.ui \
        Dialoge/dialog_fabf.ui \
        Dialoge/dialog_fauf.ui \
        Dialoge/dialog_fboguzs.ui \
        Dialoge/dialog_fbouzs.ui \
        Dialoge/dialog_fgerade.ui \
        Dialoge/dialog_fgerawi.ui \
        Dialoge/dialog_fraeser.ui \
        Dialoge/dialog_halt.ui \
        Dialoge/dialog_hbexm.ui \
        Dialoge/dialog_hbexp.ui \
        Dialoge/dialog_hbeym.ui \
        Dialoge/dialog_hbeyp.ui \
        Dialoge/dialog_kom.ui \
        Dialoge/dialog_kta.ui \
        Dialoge/dialog_lage_aendern.ui \
        Dialoge/dialog_loreiae.ui \
        Dialoge/dialog_loreima.ui \
        Dialoge/dialog_nut.ui \
        Dialoge/dialog_prgende.ui \
        Dialoge/dialog_prgkopf.ui \
        Dialoge/dialog_programmlisten.ui \
        Dialoge/dialog_rta.ui \
        Dialoge/dialog_saege.ui \
        Dialoge/dialog_schnellaenderung.ui \
        Dialoge/dialog_spiegeln.ui \
        Dialoge/dialog_topf.ui \
        Dialoge/dialog_userinput.ui \
        Dialoge/dialog_var.ui \
        Dialoge/dialog_var10.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Klassen/geo/makro_geometrie.h~ \
    Makros/makro_geometrie.h~ \
    Struncts/punkt.h~ \
    iwop.ico

RC_ICONS = iwop.ico

RESOURCES += \
    toolbaricons.qrc
