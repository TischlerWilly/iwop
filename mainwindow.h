#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QColor>
#include <QBrush>
#include <QListWidgetItem>
#include <QRect>
#include "eigeneKlassen/vorschau.h"
#include "eigeneKlassen/programmtexte.h"
#include "todo.h"
#include "Dialoge/dialog_programmlisten.h"
#include "Dialoge/dialog_prgkopf.h"

#define INDEX_PROGRAMMLISTE 0
#define INDEX_WERKZEUGLISTE 1

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void getDialogData(QString text);
    void getDialogDataModify(QString text);
    void slotSaveConfig(QString text);
    //void slot_maus_pos(QPoint p);

signals:
    void sendVorschauAktualisieren(programmtext t_neu, int aktuelle_programmzeile);
    void send_an_programmlisten(QString prgtext, QString klartext, \
                        QString variabel, QString geotext, QString fkon);
    void sendDialogData(QString text, bool openToChangeData);

private:
    Ui::MainWindow *ui;
    //Objekte:
    vorschau vorschaufenster;
    programmtexte   tt;
    Dialog_Programmlisten programmlisten;
    DialogPrgKopf    prgkopf;

    //Variablen:
    QStringList     konfiguration_ini;
    bool            konfiguration_ini_ist_vorhanden;
    uint            anz_neue_dateien;
    QString         settings_anz_undo_t;
    QString         vorlage_pkopf;

    //Funktionen:
    QString loadConfig();
    QString saveConfig();
    void update_gui();
    void update_windowtitle();
    int aktualisiere_anzeigetext(bool undo_redo_on = true);
    void vorschauAktualisieren();

    //Funktionen Sichtbarkeiten:
    void hideElemets_noFileIsOpen();
    void showElements_aFileIsOpen();
    bool elementIstEingeblendet();
    bool elementIstEingeblendet(QString zeilentext);
    bool elementIstEingeblendet(QListWidgetItem *item);
    void elementEinblendenSichtbarMachen();
    void elementEinblendenSichtbarMachen(QListWidgetItem *item);
    void elementAusblendenSichtbarMachen();
    void elementAusblendenSichtbarMachen(QListWidgetItem *item);
    void elementEinblenden();
    void elementAusblenden();

private slots:
    void resizeEvent(QResizeEvent *event);
    void on_actionNeu_triggered();
    void on_actionProgrammliste_anzeigen_triggered();
    void on_actionMakeProgrammkopf_triggered();
    void on_action_aendern_triggered();
    void on_listWidget_Programmliste_itemDoubleClicked(QListWidgetItem *item);
};

#endif // MAINWINDOW_H
