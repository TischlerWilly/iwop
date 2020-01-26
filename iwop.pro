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
        Dialoge/dialog_fraeser.cpp \
        Dialoge/dialog_halt.cpp \
        Dialoge/dialog_hbexm.cpp \
        Dialoge/dialog_hbexp.cpp \
        Dialoge/dialog_hbeym.cpp \
        Dialoge/dialog_hbeyp.cpp \
        Dialoge/dialog_kom.cpp \
        Dialoge/dialog_lage_aendern.cpp \
        Dialoge/dialog_loreiae.cpp \
        Dialoge/dialog_loreima.cpp \
        Dialoge/dialog_nut.cpp \
        Dialoge/dialog_prgende.cpp \
        Dialoge/dialog_prgkopf.cpp \
        Dialoge/dialog_programmlisten.cpp \
        Dialoge/dialog_saege.cpp \
        Dialoge/dialog_spiegeln.cpp \
        Dialoge/dialog_topf.cpp \
        eigeneFunktionen/geometrie.cpp \
        eigeneFunktionen/myfunktion.cpp \
        eigeneFunktionen/runden.cpp \
        eigeneFunktionen/text.cpp \
        eigeneFunktionen/umwandeln.cpp \
        eigeneKlassen/bogen.cpp \
        eigeneKlassen/darstellungsatribute.cpp \
        eigeneKlassen/formel.cpp \
        eigeneKlassen/geometrietext.cpp \
        eigeneKlassen/indexhisory.cpp \
        eigeneKlassen/kreis.cpp \
        eigeneKlassen/letzte_dateien.cpp \
        eigeneKlassen/prgpfade.cpp \
        eigeneKlassen/programmtext.cpp \
        eigeneKlassen/programmtexte.cpp \
        eigeneKlassen/punkt2d.cpp \
        eigeneKlassen/punkt3d.cpp \
        eigeneKlassen/rechteck.cpp \
        eigeneKlassen/rechteck3d.cpp \
        eigeneKlassen/rechtecktasche.cpp \
        eigeneKlassen/strecke.cpp \
        eigeneKlassen/tabelle_tz3.cpp \
        eigeneKlassen/text_zeilenweise.cpp \
        eigeneKlassen/undo_redo.cpp \
        eigeneKlassen/undo_redo_tz.cpp \
        eigeneKlassen/vorschau.cpp \
        eigeneKlassen/wenndannsonst.cpp \
        eigeneKlassen/werkzeug.cpp \
        eigeneKlassen/wkz_fraeser.cpp \
        eigeneKlassen/wkz_saege.cpp \
        eigeneKlassen/wuerfel.cpp \
        eigeneKlassen/zylinder.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        Dialoge/dialog_bohren.h \
        Dialoge/dialog_bohren_x.h \
        Dialoge/dialog_bohren_y.h \
        Dialoge/dialog_fraeser.h \
        Dialoge/dialog_halt.h \
        Dialoge/dialog_hbexm.h \
        Dialoge/dialog_hbexp.h \
        Dialoge/dialog_hbeym.h \
        Dialoge/dialog_hbeyp.h \
        Dialoge/dialog_kom.h \
        Dialoge/dialog_lage_aendern.h \
        Dialoge/dialog_loreiae.h \
        Dialoge/dialog_loreima.h \
        Dialoge/dialog_nut.h \
        Dialoge/dialog_prgende.h \
        Dialoge/dialog_prgkopf.h \
        Dialoge/dialog_programmlisten.h \
        Dialoge/dialog_saege.h \
        Dialoge/dialog_spiegeln.h \
        Dialoge/dialog_topf.h \
        eigeneDefines/define_bo.h \
        eigeneDefines/define_boX.h \
        eigeneDefines/define_boY.h \
        eigeneDefines/define_hbexm.h \
        eigeneDefines/define_hbexp.h \
        eigeneDefines/define_hbeym.h \
        eigeneDefines/define_hbeyp.h \
        eigeneDefines/define_lage_aendern.h \
        eigeneDefines/define_loreiae.h \
        eigeneDefines/define_loreima.h \
        eigeneDefines/define_nut.h \
        eigeneDefines/define_prgende.h \
        eigeneDefines/define_prgkopf.h \
        eigeneDefines/define_spiegeln.h \
        eigeneDefines/define_topf.h \
        eigeneDefines/define_wkz.h \
        eigeneDefines/define_wkz_fraeser.h \
        eigeneDefines/define_wkz_saege.h \
        eigeneDefines/defines_geometrie.h \
        eigeneDefines/defines_halt.h \
        eigeneDefines/defines_kom.h \
        eigeneFunktionen/geometrie.h \
        eigeneFunktionen/myfunktion.h \
        eigeneFunktionen/runden.h \
        eigeneFunktionen/text.h \
        eigeneFunktionen/umwandeln.h \
        eigeneKlassen/bogen.h \
        eigeneKlassen/darstellungsatribute.h \
        eigeneKlassen/formel.h \
        eigeneKlassen/geometrietext.h \
        eigeneKlassen/indexhisory.h \
        eigeneKlassen/kreis.h \
        eigeneKlassen/letzte_dateien.h \
        eigeneKlassen/prgpfade.h \
        eigeneKlassen/programmtext.h \
        eigeneKlassen/programmtexte.h \
        eigeneKlassen/punkt2d.h \
        eigeneKlassen/punkt3d.h \
        eigeneKlassen/rechteck.h \
        eigeneKlassen/rechteck3d.h \
        eigeneKlassen/rechtecktasche.h \
        eigeneKlassen/strecke.h \
        eigeneKlassen/tabelle_tz3.h \
        eigeneKlassen/text_zeilenweise.h \
        eigeneKlassen/undo_redo.h \
        eigeneKlassen/undo_redo_tz.h \
        eigeneKlassen/vorschau.h \
        eigeneKlassen/wenndannsonst.h \
        eigeneKlassen/werkzeug.h \
        eigeneKlassen/wkz_fraeser.h \
        eigeneKlassen/wkz_saege.h \
        eigeneKlassen/wuerfel.h \
        eigeneKlassen/zylinder.h \
        eigeneMakros/makro_geometrie.h \
        eigeneStruncts/punkt.h \
        mainwindow.h \
        myDefines.h \
        todo.h

FORMS += \
        Dialoge/dialog_bohren.ui \
        Dialoge/dialog_bohren_x.ui \
        Dialoge/dialog_bohren_y.ui \
        Dialoge/dialog_fraeser.ui \
        Dialoge/dialog_halt.ui \
        Dialoge/dialog_hbexm.ui \
        Dialoge/dialog_hbexp.ui \
        Dialoge/dialog_hbeym.ui \
        Dialoge/dialog_hbeyp.ui \
        Dialoge/dialog_kom.ui \
        Dialoge/dialog_lage_aendern.ui \
        Dialoge/dialog_loreiae.ui \
        Dialoge/dialog_loreima.ui \
        Dialoge/dialog_nut.ui \
        Dialoge/dialog_prgende.ui \
        Dialoge/dialog_prgkopf.ui \
        Dialoge/dialog_programmlisten.ui \
        Dialoge/dialog_saege.ui \
        Dialoge/dialog_spiegeln.ui \
        Dialoge/dialog_topf.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    eigeneMakros/makro_geometrie.h~ \
    eigeneStruncts/punkt.h~
