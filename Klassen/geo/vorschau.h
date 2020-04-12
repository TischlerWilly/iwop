#ifndef VORSCHAU_H
#define VORSCHAU_H

#include <QWidget>
#include <QPainter>
#include <QMessageBox>
#include <QStatusBar>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMenu>
#include <math.h>
#include "geofunktionen.h"
#include "Klassen/programmtext.h"



class vorschau : public QWidget
{
    Q_OBJECT
public:
    explicit vorschau(QWidget *parent = 0);


protected:
    void paintEvent(QPaintEvent *);

private:
    void zeichneGeotext(QString geometrieElement, uint i);
    void zeichneFkon(QString geometrieElement, uint i);
    float sf();
    void set_sf(float neuer_faktor);
    void werkstueck_darstellung_berechnen();
    punkt drehen_arcTo(punkt oben_links, float laenge, float breite, \
                       float drehwinkel, punkt drehzentrum);
    punkt2d drehen_arcTo(punkt2d oben_links, double laenge, double breite, \
                         double drehwinkel, punkt2d drehzentrum);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void zoom(bool dichter);
    punkt2d mauspos_npwst();
    punkt2d mauspos_npanschlag();
    uint zeile_von_Mauspos();

    QColor set_farbe(QString farbe);
    Qt::PenStyle set_linienstil(QString stil);


    punkt       N;    //Nullpunkt
    punkt       Npv;  //Nullpunkt-Verschiebung(Nicht XY-Versatz, Verschiebung des sichtbaren Ausschnittes)
    rechteck3d  Wst;  //Werkstück
    rechteck3d  Wstd; //Dardestelltes Werkstück
    float       Sf;   //Skalierungsfaktor
    float       Zf;   //Zoomfaktor
    programmtext T;
    uint        Aktuelle_zeilennummer;
    int         Maus_pos_alt_x;
    int         Maus_pos_alt_y;
    uint        Zeile_von_maus_pos;//Zum Zwischenspeichern damit Ergebnis nicht verfälscht wird wenn Maus sich bewegt
    bool        Mrg;  //Mausrad gedrückt
    
signals:
    void anfrage_werkstueckmasse();
    void sende_maus_pos(QPoint p);
    void sende_zeilennummer(uint nr);

public slots:
    void slot_aktualisieren(programmtext t_neu, int aktive_zeile);
    void slot_aktives_Element_einfaerben(int zeilennummer);

private slots:
    void slot_zf_gleich_eins();
    void slot_tunix();
    void slot_sende_zeilennummer();

};

#endif // VORSCHAU_H
