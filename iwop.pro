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
        Dialoge/dialog_prgkopf.cpp \
        Dialoge/dialog_programmlisten.cpp \
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
        eigeneKlassen/vorschau.cpp \
        eigeneKlassen/wenndannsonst.cpp \
        eigeneKlassen/wuerfel.cpp \
        eigeneKlassen/zylinder.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        Dialoge/dialog_prgkopf.h \
        Dialoge/dialog_programmlisten.h \
        eigeneDefines/define_prgkopf.h \
        eigeneDefines/defines_geometrie.h \
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
        eigeneKlassen/vorschau.h \
        eigeneKlassen/wenndannsonst.h \
        eigeneKlassen/wuerfel.h \
        eigeneKlassen/zylinder.h \
        eigeneMakros/makro_geometrie.h \
        eigeneStruncts/punkt.h \
        mainwindow.h \
        myDefines.h \
        todo.h

FORMS += \
        Dialoge/dialog_prgkopf.ui \
        Dialoge/dialog_programmlisten.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    eigeneMakros/makro_geometrie.h~ \
    eigeneStruncts/punkt.h~
