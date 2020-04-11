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
#include "../eigeneFunktionen/geometrie.h"
#include "programmtext.h"



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
    float get_sf();
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
    punkt2d get_mauspos_npwst();
    punkt2d get_mauspos_npanschlag();
    uint get_zeile_von_Mauspos();

    QColor set_farbe(QString farbe);
    Qt::PenStyle set_linienstil(QString stil);


    punkt n;//Nullpunkt
    punkt npv;//Nullpunkt-Verschiebung(Nicht XY-Versatz, Verschiebung des sichtbaren Ausschnittes)
    rechteck3d wst;//Werkstück
    rechteck3d wstd;//Dardestelltes Werkstück
    float sf;//Skalierungsfaktor
    float zf;//Zoomfaktor
    programmtext t;
    uint aktuelle_zeilennummer;
    int maus_pos_alt_x;
    int maus_pos_alt_y;
    uint zeile_von_maus_pos;//Zum Zwischenspeichern damit Ergebnis nicht verfälscht wird wenn Maus sich bewegt
    bool mrg; //Mausrad gedrückt
    
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
