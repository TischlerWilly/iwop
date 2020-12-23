#ifndef DIALOG_SCHNELLAENDERUNG_H
#define DIALOG_SCHNELLAENDERUNG_H

#include <QDialog>
#include <QMessageBox>
#include "Klassen/text_zeilenweise.h"
#include "Funktionen/umwandeln.h"
#include "Funktionen/text.h"
#include "myDefines.h"
#include "Defines/define_nut.h"
#include "Defines/define_kta.h"
#include "Defines/define_rta.h"
#include "Defines/define_fauf.h"

namespace Ui {
class Dialog_schnellaenderung;
}

class Dialog_schnellaenderung : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_schnellaenderung(QWidget *parent = NULL);
    ~Dialog_schnellaenderung();

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();
    void on_comboBox_dlg_currentIndexChanged(const QString &arg1);
    void on_comboBox_param_currentIndexChanged();
    void on_comboBox_alt_currentIndexChanged(const QString &arg1);

    void on_pushButton_werte_aendern_clicked();

public slots:
    void getData(text_zeilenweise t, uint start, uint menge);

signals:
    void sendData(text_zeilenweise t);

private:
    Ui::Dialog_schnellaenderung *ui;
    text_zeilenweise tz;
    uint Startzeile;
    uint Menge;
    text_zeilenweise Dialoge;
    text_zeilenweise Param_alle;
    text_zeilenweise Param_bohr;
    text_zeilenweise Param_nut;
    text_zeilenweise Param_kta;
    text_zeilenweise Param_rta;
    text_zeilenweise Param_fauf;

    void werte_ermitteln();
    void wert_aendern(QString parname, QString wert_alt, QString wert_neu);
};

#endif // DIALOG_SCHNELLAENDERUNG_H
