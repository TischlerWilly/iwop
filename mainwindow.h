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
#include "Dialoge/dialog_prgende.h"
#include "eigeneKlassen/letzte_dateien.h"
#include "Dialoge/dialog_kom.h"
#include "Dialoge/dialog_halt.h"
#include "Dialoge/dialog_bohren.h"
#include "Dialoge/dialog_spiegeln.h"

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
    void slot_maus_pos(QPoint p);

signals:
    void sendVorschauAktualisieren(programmtext t_neu, int aktuelle_programmzeile);
    void send_an_programmlisten(QString prgtext, QString klartext, \
                        QString variabel, QString geotext, QString fkon);
    void sendDialogData(QString text, bool openToChangeData);
    void sendAktiveProgrammzeile(int zeilennummer);

private:
    Ui::MainWindow *ui;

    //Objekte:
    vorschau vorschaufenster;
    programmtexte   tt;
    letzte_dateien  letzte_geoefnete_dateien;
    QAction         *oefneLetzteDateien[ANZAHL_LETZTER_DATEIEN];
    QAction         *OffeneDateieFokus[ANZAHL_OFFENER_DATEIEN];
    Dialog_Programmlisten programmlisten;
    DialogPrgKopf    prgkopf;
    Dialog_prgende   prgende;
    Dialog_kom       kom;
    Dialog_halt      halt;
    Dialog_Bohren    dlgbo;
    Dialog_spiegeln  dlgspiegeln;

    //Variablen:
    QStringList     konfiguration_ini;
    bool            konfiguration_ini_ist_vorhanden;
    uint            anz_neue_dateien;
    QString         settings_anz_undo_t;
    QString         vorlage_pkopf;
    QString         vorlage_pende;
    QString         vorlage_kom;
    QString         vorlage_halt;
    QString         vorlage_bo;
    QString         vorlage_spiegeln;
    QString         pfad_oefne_fmc;
    QString         kopierterEintrag_t;
    bool            speichern_unter_flag;

    //Funktionen:
    QString loadConfig();
    QString saveConfig();
    void loadConfig_letzte_Dateien();
    void update_gui();
    void update_windowtitle();
    int aktualisiere_anzeigetext(bool undo_redo_on = true);
    void vorschauAktualisieren();
    void openFile(QString pfad);
    text_zeilenweise import_fmc(QString quelle, bool &readonly);
    QString replaceparam(QString param, QString ziel, QString quelle);
    QString          export_fmc(text_zeilenweise tz);
    void aktuelisiere_letzte_dateien_inifile();
    void aktualisiere_letzte_dateien_menu();
    void aktualisiere_offene_dateien_menu();    
    void closeEvent(QCloseEvent *ce);

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
    void on_action_aendern_triggered();
    void on_listWidget_Programmliste_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_Programmliste_currentRowChanged(int currentRow);
    void on_actionOffnen_triggered();
    void on_actionEin_Ausblenden_triggered();
    void on_actionAuswahl_Einblenden_triggered();
    void on_actionAuswahl_Ausblenden_triggered();
    void on_actionRueckgaengig_triggered();
    void on_actionWiederholen_triggered();
    void on_actionEinfuegen_triggered();
    void on_actionKopieren_triggered();
    void on_actionAusschneiden_triggered();
    void on_actionEntfernen_triggered();
    void on_actionNaechste_offen_Datei_triggered();
    void on_actionLetzte_offene_Datei_triggered();
    bool on_actionDateiSpeichern_triggered();
    void on_actionDateiSpeichern_unter_triggered();
    bool on_actionDateiSchliessen_triggered();
    void actionFokuswechselOffeneDateiTriggered();
    void actionLetzteDateiOefnenTriggered();
    void on_actionMakeProgrammkopf_triggered();
    void on_actionMakeProgrammende_triggered();
    void on_actionMakeKommentar_triggered();
    void on_actionMakeHalt_triggered();
    void on_actionMakeBohren_Durchmesser_triggered();
    void on_actionMakeSpiegeln_triggered();
};

#endif // MAINWINDOW_H
