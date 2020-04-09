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
#include "eigeneKlassen/prgpfade.h"
#include "Dialoge/dialog_programmlisten.h"
#include "Dialoge/dialog_prgkopf.h"
#include "Dialoge/dialog_prgende.h"
#include "eigeneKlassen/letzte_dateien.h"
#include "Dialoge/dialog_kom.h"
#include "Dialoge/dialog_halt.h"
#include "Dialoge/dialog_bohren.h"
#include "Dialoge/dialog_bohren_y.h"
#include "Dialoge/dialog_bohren_x.h"
#include "Dialoge/dialog_loreiae.h"
#include "Dialoge/dialog_loreima.h"
#include "Dialoge/dialog_topf.h"
#include "Dialoge/dialog_hbexp.h"
#include "Dialoge/dialog_hbexm.h"
#include "Dialoge/dialog_hbeyp.h"
#include "Dialoge/dialog_hbeym.h"
#include "Dialoge/dialog_spiegeln.h"
#include "Dialoge/dialog_lage_aendern.h"
#include "eigeneKlassen/werkzeug.h"
#include "Dialoge/dialog_fraeser.h"
#include "Dialoge/dialog_saege.h"
#include "Dialoge/dialog_nut.h"
#include "Dialoge/dialog_kta.h"
#include "Dialoge/dialog_rta.h"
#include "Dialoge/dialog_var.h"
#include "Dialoge/dialog_var10.h"
#include "Dialoge/dialog_fauf.h"
#include "Dialoge/dialog_fabf.h"
#include "Dialoge/dialog_fgerade.h"
#include "Dialoge/dialog_fgerawi.h"
#include "Dialoge/dialog_fbouzs.h"
#include "Dialoge/dialog_fboguzs.h"
#include "Dialoge/dialog_einstellungen.h"
#include "eigeneKlassen/settings.h"

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
    void set_arg(int argc, char *argv[]);

public slots:
    void getDialogData(QString text);
    void getDialogDataModify(QString text);
    void getDialogDataModify(QString text, uint zeilennummer);
    void slotSaveConfig(QString text);
    void slot_maus_pos(QPoint p);
    void slotNeedWKZ(QString dlgtyp);
    void slotGetEinstellungen(settings s);
    void slotGetZeilennummer(uint nr);

signals:
    void sendVorschauAktualisieren(programmtext t_neu, int aktuelle_programmzeile);
    void send_an_programmlisten(QString prgtext, QString klartext, \
                        QString variabel, QString geotext, QString fkon);
    void sendDialogData(QString text, bool openToChangeData);
    void sendAktiveProgrammzeile(int zeilennummer);
    void sendWKZlist(text_zeilenweise list);

private:
    Ui::MainWindow *ui;

    //Objekte:
    settings        set;
    Dialog_einstellungen dlgsettings;
    vorschau vorschaufenster;
    programmtexte   tt;
    werkzeug        wkz;
    letzte_dateien  letzte_geoefnete_dateien;
    QAction         *oefneLetzteDateien[ANZAHL_LETZTER_DATEIEN];
    QAction         *OffeneDateieFokus[ANZAHL_OFFENER_DATEIEN];
    Dialog_Programmlisten programmlisten;
    DialogPrgKopf    prgkopf;
    Dialog_prgende   prgende;
    Dialog_kom       kom;
    Dialog_halt      halt;
    Dialog_Bohren    dlgbo;
    Dialog_bohren_y  dlgboy;
    Dialog_bohren_x  dlgbox;
    Dialog_loreiae   dlgloreiae;
    Dialog_loreima   dlgloreima;
    Dialog_topf      dlgtopf;
    Dialog_hbexp     dlghbexp;
    Dialog_hbexm     dlghbexm;
    Dialog_hbeyp     dlghbeyp;
    Dialog_hbeym     dlghbeym;
    Dialog_nut       dlgnut;
    Dialog_spiegeln  dlgspiegeln;
    Dialog_lage_aendern   dlglageaendern;
    Dialog_fraeser   dlgfraeser;
    Dialog_saege     dlgsaege;
    Dialog_kta       dlgkta;
    Dialog_rta       dlgrta;
    Dialog_var       dlgvar;
    Dialog_var10     dlgvar10;
    Dialog_fauf      dlgfauf;
    Dialog_fabf      dlgfabf;
    Dialog_fgerade   dlgfgerade;
    Dialog_fgerawi   dlgfgerawi;
    Dialog_fbouzs    dlgfbouzs;
    Dialog_fboguzs   dlgfboguzs;

    //Variablen:
    QStringList     konfiguration_ini;
    bool            konfiguration_ini_ist_vorhanden;
    uint            anz_neue_dateien;
    QString         vorlage_pkopf;
    QString         vorlage_pende;
    QString         vorlage_kom;
    QString         vorlage_halt;
    QString         vorlage_bo;
    QString         vorlage_boy;
    QString         vorlage_box;
    QString         vorlage_loreiae;
    QString         vorlage_loreima;
    QString         vorlage_topf;
    QString         vorlage_hbexp;
    QString         vorlage_hbexm;
    QString         vorlage_hbeyp;
    QString         vorlage_hbeym;
    QString         vorlage_nut;
    QString         vorlage_kta;
    QString         vorlage_rta;
    QString         vorlage_var;
    QString         vorlage_var10;
    QString         vorlage_fauf;
    QString         vorlage_fabf;
    QString         vorlage_fgerade;
    QString         vorlage_fgerawi;
    QString         vorlage_fbouzs;
    QString         vorlage_fboguzs;
    QString         vorlage_spiegeln;
    QString         vorlage_lageaendern;
    QString         pfad_oefne_fmc;
    QString         kopierterEintrag_t;
    QString         kopierterEintrag_w;
    bool            speichern_unter_flag;

    //Funktionen:
    QString loadConfig();
    void settings_umsetzen();
    QString saveConfig();
    void saveWKZ();
    void loadWKZ();
    void loadConfig_letzte_Dateien();
    void update_gui();
    void update_windowtitle();
    int aktualisiere_anzeigetext(bool undo_redo_on = true);
    int aktualisiere_anzeigetext_wkz(bool undo_redo_on = true);
    void vorschauAktualisieren();
    void openFile(QString pfad);
    text_zeilenweise import_fmc(QString quelle, bool &readonly, QString prgname);
    QString replaceparam(QString param, QString ziel, QString quelle);
    QString get_param(QString param, QString quelle);
    QString set_param(QString param, QString wert, QString zeile);
    QString exportparam(QString param, QString paramzeile);
    QString exportparam_direktwert(QString param, QString wert);
    QString          export_fmc(text_zeilenweise tz);
    void aktuelisiere_letzte_dateien_inifile();
    void aktualisiere_letzte_dateien_menu();
    void aktualisiere_offene_dateien_menu();    
    void closeEvent(QCloseEvent *ce);
    QString ausgabepfad_postprozessor();

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
    void on_actionMakeLage_aendern_triggered();
    void on_actionMakeBohren_in_Y_triggered();
    void on_actionMakeBohren_in_X_triggered();
    void on_actionMakeLochreihe_Anfang_Ende_triggered();
    void on_actionMakeLochreihe_Mitte_Anfang_triggered();
    void on_actionMakeTopfband_triggered();
    void on_actionMakeHBE_X_plus_triggered();
    void on_actionMakeHBE_X_minus_triggered();
    void on_actionMakeHBE_Y_plus_triggered();
    void on_actionMakeHBE_Y_minus_triggered();
    void on_tabWidget_currentChanged(int index);
    void on_pushButton_MakeFraeser_clicked();
    void on_pushButton_MakeSaege_clicked();
    void on_listWidget_Werkzeug_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_wkz_speichern_clicked();
    void on_actionMakeNut_triggered();
    void on_actionMakeKreistasche_triggered();
    void on_actionMakeRechtecktasche_triggered();
    void on_actionMakeVariable_triggered();
    void on_actionMakeVariablen10_triggered();
    void on_actionMakeFauf_triggered();
    void on_actionMakeAbfahren_triggered();
    void on_actionMakeFgerade_triggered();
    void on_actionMakeFbouzs_triggered();
    void on_actionMakeFboguzs_triggered();
    void on_actionMakeFgerawi_triggered();
    void on_actionEinstellungen_triggered();
    void on_actionTestfunktion_triggered();
    void on_actionBogenrichtung_umkehren_triggered();
    void on_actionFraesrichtung_umkehren_triggered();
    void on_listWidget_Werkzeug_currentRowChanged(int currentRow);
    void on_actionFraesbahn_teilen_in_akt_Zeile_triggered();
    void on_actionFraesbahn_teilen_vor_akt_Zeilen_triggered();
    void on_actionFraesbahn_verlaengern_Gerade_triggered();
};

#endif // MAINWINDOW_H
