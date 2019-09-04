#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Defaultwerte:
    //kopierterEintrag_t              = NICHT_DEFINIERT;
    //kopiertesWerkzeug               = NICHT_DEFINIERT;
    vorlage_pkopf                   = NICHT_DEFINIERT;
    settings_anz_undo_t             = "10";
    //speichern_unter_flag            = false;
    tt.clear();
    anz_neue_dateien                = 0;//Zählung neuer Dateien mit 0 beginnen und dann raufzählen
    pfad_oefne_fmc                  = QDir::homePath() + "/Dokumente/CNC-Programme";

    vorschaufenster.setParent(ui->tab_Programmliste);

    QDir dir(QDir::homePath() + PFAD_ZUM_PROGRAMMORDNER);
    if(!dir.exists())
    {
        QString nachricht;
        nachricht = "Programmpfad nicht gefunden. Pfad \"";
        nachricht += QDir::homePath() + PFAD_ZUM_PROGRAMMORDNER;
        nachricht += "\" wird angelegt";
        QMessageBox mb;
        mb.setText(nachricht);
        mb.exec();
        dir.mkdir(QDir::homePath() + PFAD_ZUM_PROGRAMMORDNER);
        //dir.mkdir(QDir::homePath() + PFAD_ZU_DEN_WERKZEUGBILDERN);
/*
        QFile file(QDir::homePath() + WKZ_FILE);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) //Wenn es nicht möglich ist die Datei zu öffnen oder neu anzulegen
        {
            QMessageBox mb;
            mb.setText("Fehler beim Datei-Zugriff");
            mb.exec();
        }else
        {

            file.write(werkzeug_dialog.getDefault().toUtf8());
            QMessageBox mb;
            mb.setText("Neue, Werkzeugdatei wurde erzeugt.");
            mb.exec();
        }
        file.close();
*/
    }
    QString msg = this->loadConfig();
    if(msg != "OK")
    {
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
    }
    if(konfiguration_ini_ist_vorhanden == false)
    {
        //Sicherheitsabfrage:
        QMessageBox mb;
        mb.setWindowTitle("Konnte Konfiguratiosdatei nicht finden!");
        mb.setText("Die Konfigurationsdatei ist nicht vorhanden oder konnte nicht gelesen werden.Soll eine neue Konfigurationsdatei erstellt werden?");
        mb.setStandardButtons(QMessageBox::Yes);
        mb.addButton(QMessageBox::No);
        mb.setDefaultButton(QMessageBox::No);
        if(mb.exec() == QMessageBox::Yes)
        {
            saveConfig();
            loadConfig();
        }else
        {
            QMessageBox mb2;
            mb2.setText("Konfiguration wurde nicht angelegt.");
            mb2.exec();
        }
    }

    //on_pushButton_WKZ_Laden_clicked();
    //ladeWerkzeugnamen();
    //loadConfig_letzte_Dateien();

    //connect:
    connect(&prgkopf, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));

    connect(&prgkopf, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));

    connect(&prgkopf, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));

    connect(&vorschaufenster, SIGNAL(sende_maus_pos(QPoint)), this, SLOT(slot_maus_pos(QPoint)));

    update_gui();
    this->setWindowState(Qt::WindowMaximized);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QRect rect_main =  this->geometry();
    int hoehe = rect_main.height();
    int breite = rect_main.width();
    int hoehe_widget = hoehe-20;
    if (hoehe_widget <1)
    {
        hoehe_widget = 1;
    }
    int breite_widget = breite-20;
    if (breite_widget <1)
    {
        breite_widget = 1;
    }
    ui->tabWidget->setFixedSize(breite_widget, hoehe_widget);
    QRect rect_tabWidget =  ui->tabWidget->geometry();
    hoehe = rect_tabWidget.height();
    breite = rect_tabWidget.width();
    hoehe_widget = hoehe-55;
    if (hoehe_widget <1)
    {
        hoehe_widget = 1;
    }
    breite_widget = breite-20;
    if (breite_widget <1)
    {
        breite_widget = 1;
    }
    ui->listWidget_Werkzeug->setFixedSize(breite_widget, hoehe_widget);

    vorschaufenster.move(ui->tab_Programmliste->width()/3+5,10);
    vorschaufenster.setFixedWidth(ui->tab_Programmliste->width()-ui->tab_Programmliste->width()/3-10);
    vorschaufenster.setFixedHeight(ui->tab_Programmliste->height()-70);
    ui->listWidget_Programmliste->setFixedWidth(ui->tab_Programmliste->width()/3-10);
    ui->listWidget_Programmliste->setFixedHeight(ui->tab_Programmliste->height()-30);

    QMainWindow::resizeEvent(event);
}

void MainWindow::update_gui()
{
    if(tt.dateien_sind_offen())
    {
        showElements_aFileIsOpen();
        aktualisiere_anzeigetext();
        vorschauAktualisieren();
    }else
    {
        hideElemets_noFileIsOpen();
        vorschaufenster.hide();
    }
    if(tt.get_size() > 1)
    {
        //ui->actionNaechste_offen_Datei->setEnabled(true);
        //ui->actionLetzte_offene_Datei->setEnabled(true);
    }else
    {
        //ui->actionNaechste_offen_Datei->setDisabled(true);
        //ui->actionLetzte_offene_Datei->setDisabled(true);
    }
    //aktualisiere_letzte_dateien_menu();
    //aktualisiere_offene_dateien_menu();
    update_windowtitle();
}

void MainWindow::update_windowtitle()
{
    if(tt.dateien_sind_offen())
    {
        QString name = tt.get_prgname();
        if(name == NICHT_DEFINIERT)
        {
            name = "Neue Datei";
        }else
        {
            QFileInfo info = name;
            name = info.baseName();
        }
        if(tt.get_prgtext()->get_hat_ungesicherte_inhalte() == true)
        {
            name += "*";
        }
        QString fenstertitel = PROGRAMMNAME;
        fenstertitel += " ( " + name + " )";
        this->setWindowTitle(fenstertitel);
    }else
    {
        QString titel = PROGRAMMNAME;
        titel += " ";
        titel += PROGRAMMVERSION;
        this->setWindowTitle(titel);
    }
}

int MainWindow::aktualisiere_anzeigetext(bool undo_redo_on)
{
    int row;
    if(ui->listWidget_Programmliste->currentIndex().isValid())
    {
        row = ui->listWidget_Programmliste->currentRow();
    }else
    {
        row = 0;
    }
    ui->listWidget_Programmliste->clear();
    text_zeilenweise tmp;
    tmp =tt.get_prgtext()->get_anzeigetext_zeilenweise();
    if(tmp.zeilenanzahl() == 0)
    {
        return -1;
    }
    for(uint i=1 ; i<=tmp.zeilenanzahl() ; i++)
    {
        ui->listWidget_Programmliste->addItem(tmp.zeile(i));
    }
    for(int row = 0; row < ui->listWidget_Programmliste->count(); row++)
    {
        QListWidgetItem *item = ui->listWidget_Programmliste->item(row);
        if(elementIstEingeblendet(item))
        {
            elementEinblendenSichtbarMachen(item);
        }else
        {
            elementAusblendenSichtbarMachen(item);
        }
    }
    if(row >= (int)tmp.zeilenanzahl())
    {
        row = row-1;
    }
    ui->listWidget_Programmliste->setCurrentRow(row);

    if(undo_redo_on == true)
    {
        tt.get_prg_undo_redo()->neu(*tt.get_prgtext());
    }
    return row;
}

//---------------------------------------------------Konfiguration

QString MainWindow::loadConfig()
{
    QString returnString = "OK";

    QFile file(QDir::homePath() + INI_FILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        konfiguration_ini_ist_vorhanden = false;
        returnString = "Konnte Konfiguratiosdatei nicht finden!\nBitte ueberpruefen Sie die Einstellungen.";
    } else
    {
        konfiguration_ini_ist_vorhanden = true;
        while(!file.atEnd())
        {
            QString line = file.readLine();
            konfiguration_ini += line;
        }
        file.close();
        //Konfiguration Zeilenweise auswerten:
        for (QStringList::iterator it = konfiguration_ini.begin(); it != konfiguration_ini.end(); ++it)
            {
                QString text = *it;

                //-----------------------------------------------------Settings:
                if(text.contains(SETTINGS_ANZ_UNDO_T))
                {
                    settings_anz_undo_t = selektiereEintrag(text, SETTINGS_ANZ_UNDO_T, ENDE_ZEILE);
                }
                //-----------------------------------------------------Dialoge:
                if(text.contains(DLG_PKOPF))
                {
                    vorlage_pkopf = selektiereEintrag(text, DLG_PKOPF, ENDE_ZEILE);
                }
            }
    }

    return returnString;
}

QString MainWindow::saveConfig()
{
    QString returnString = "OK";

    //Daten in QString schreiben:
    QString inhaltVonKonfiguration;

    inhaltVonKonfiguration =        BEGIN_EINSTELLUNGEN;
    inhaltVonKonfiguration +=       "\n";
    //----------------------------------------------------Einstellungen:
    inhaltVonKonfiguration +=       SETTINGS_ANZ_UNDO_T;
    inhaltVonKonfiguration +=       settings_anz_undo_t;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    //----------------------------------------------------

    inhaltVonKonfiguration +=       ENDE_EINSTELLUNGEN;
    inhaltVonKonfiguration +=       "\n";


    inhaltVonKonfiguration +=       BEGIN_DIALOGE;
    inhaltVonKonfiguration +=       "\n";

    //----------------------------------------------------Dialog Programmkopf:
    inhaltVonKonfiguration +=       DLG_PKOPF;
    if(vorlage_pkopf == NICHT_DEFINIERT)
    {
        inhaltVonKonfiguration +=   prgkopf.get_default();
    }else
    {
        inhaltVonKonfiguration +=   vorlage_pkopf;
    }
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";

    //-------------------------------------------
    inhaltVonKonfiguration +=       ENDE_DIALOGE;
    inhaltVonKonfiguration +=       "\n";
    //---------------------------------------------------------------------------------------------------------

    //Daten Speichern:
    QFile file(QDir::homePath() + INI_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) //Wenn es nicht möglich ist die Datei zu öffnen oder neu anzulegen
    {
        QMessageBox mb;
        mb.setText("Fehler beim Zugriff auf die Datei \"konfiguration.ini\"");
        mb.exec();
    } else
    {
        file.remove(); //lösche alte Datei wenn vorhanden
        file.close(); //beende Zugriff
        file.open(QIODevice::WriteOnly | QIODevice::Text); //lege Datei neu an
        file.write(inhaltVonKonfiguration.toUtf8()); //fülle Datei mit Inhalt
        file.close(); //beende Zugriff
        QMessageBox mb;
        mb.setText("Konfiguration wurde erfolgreich geschrieben.");
        mb.exec();
    }
    return returnString;
}

void MainWindow::slotSaveConfig(QString text)
{
    //Sicherheitsabfrage:
    QMessageBox mb;
    mb.setWindowTitle("Konfiguration speichern");
    mb.setText("Sind Sie sicher, dass die Konfoguration gespeichert werden soll?");
    mb.setStandardButtons(QMessageBox::Yes);
    mb.addButton(QMessageBox::No);
    mb.setDefaultButton(QMessageBox::No);
    if(mb.exec() == QMessageBox::Yes)
    {
        //Daten vom Dialog in lokale Variabeln speichern:
        //------------------------------------------------Settings:
        if(text.contains(SETTINGS_ANZ_UNDO_T))
        {
            settings_anz_undo_t = selektiereEintrag(text, SETTINGS_ANZ_UNDO_T, ENDE_ZEILE);
        }
        if(text.contains(SETTINGS_FKON_BERECHNEN))
        {
            //fkon_berechnen = selektiereEintrag(text, SETTINGS_FKON_BERECHNEN, ENDE_ZEILE);
        }
        //------------------------------------------------Dialoge:
        if(text.contains(DLG_PKOPF))
        {
            vorlage_pkopf = selektiereEintrag(text, DLG_PKOPF, ENDE_ZEILE);
        }//else if....

        //Daten in Datei sichern:
        saveConfig();
        //Konfiguration neu laden:
        loadConfig();
        //Anzeige aktualisieren:
        tt.get_prgtext()->aktualisieren();
        vorschauAktualisieren();
    }else
    {
        QMessageBox mb2;
        mb2.setText("Konfiguration wurde nicht geaendert.");
        mb2.exec();
    }
}

//---------------------------------------------------Sichtbarkeiten
void MainWindow::hideElemets_noFileIsOpen()
{
    ui->listWidget_Programmliste->hide();
    //Menü Datei:
    //ui->actionDateiSpeichern->setDisabled(true);
    //ui->actionDateiSpeichern_unter->setDisabled(true);
    //ui->actionDateiSchliessen->setDisabled(true);
    //Menü Bearbeiten:
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        ui->action_aendern->setDisabled(true);
        //ui->actionEinfuegen->setDisabled(true);
        //ui->actionKopieren->setDisabled(true);
        //ui->actionAusschneiden->setDisabled(true);
        //ui->actionEntfernen->setDisabled(true);
    }
    //ui->actionEin_Ausblenden->setDisabled(true);
    //ui->actionAuswahl_Einblenden->setDisabled(true);
    //ui->actionAuswahl_Ausblenden->setDisabled(true);
    //Menü CAM:
    ui->actionMakeProgrammkopf->setDisabled(true);
    //Menü Extras:
    ui->actionProgrammliste_anzeigen->setDisabled(true);
    //anderes:
    vorschaufenster.hide();
}

void MainWindow::showElements_aFileIsOpen()
{
    ui->listWidget_Programmliste->show();
    //Menü Datei:
    //ui->actionDateiSpeichern->setEnabled(true);
    //ui->actionDateiSpeichern_unter->setEnabled(true);
    //ui->actionDateiSchliessen->setEnabled(true);
    //Menü Bearbeiten:
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        ui->action_aendern->setEnabled(true);
        //ui->actionEinfuegen->setEnabled(true);
        //ui->actionKopieren->setEnabled(true);
        //ui->actionAusschneiden->setEnabled(true);
        //ui->actionEntfernen->setEnabled(true);
    }
    //ui->actionEin_Ausblenden->setEnabled(true);
    //ui->actionAuswahl_Einblenden->setEnabled(true);
    //ui->actionAuswahl_Ausblenden->setEnabled(true);
    //Menü CAM:
    ui->actionMakeProgrammkopf->setEnabled(true);
    //Menü Extras:
    ui->actionProgrammliste_anzeigen->setEnabled(true);
    //anderes:
    vorschaufenster.show();
}

bool MainWindow::elementIstEingeblendet()
{
    QString tmp = tt.get_prgtext()->zeile(ui->listWidget_Programmliste->currentRow()+1);
    if(tmp.left(2) == "//")
    {
        return false;
    }else
    {
        return true;
    }
}

bool MainWindow::elementIstEingeblendet(QString zeilentext)
{
    if(zeilentext.left(2) == "//")
    {
        return false;
    }else
    {
        return true;
    }
}

bool MainWindow::elementIstEingeblendet(QListWidgetItem *item)
{
    QString tmp = item->text();
    if(tmp.left(2) == "//")
    {
        return false;
    }else
    {
        return true;
    }
}

void MainWindow::elementEinblenden()
{
    uint i = ui->listWidget_Programmliste->currentRow()+1;
    QString tmp_t = tt.get_prgtext()->zeile(i);
    int length_t = tmp_t.length();
    tmp_t = tmp_t.right(length_t-2);
    tt.get_prgtext()->zeile_ersaetzen(i, tmp_t);

    QString tmp = ui->listWidget_Programmliste->currentItem()->text();
    int length = tmp.length();
    tmp = tmp.right(length-2);
    ui->listWidget_Programmliste->currentItem()->setText(tmp);

    vorschauAktualisieren();
}

void MainWindow::elementAusblenden()
{
    uint i = ui->listWidget_Programmliste->currentRow()+1;
    QString tmp_t = tt.get_prgtext()->zeile(i);
    tmp_t = "//" + tmp_t;
    tt.get_prgtext()->zeile_ersaetzen(i, tmp_t);

    QString tmp = ui->listWidget_Programmliste->currentItem()->text();
    QString newText = "//";
    newText += tmp;
    ui->listWidget_Programmliste->currentItem()->setText(newText);

    vorschauAktualisieren();
}

void MainWindow::elementEinblendenSichtbarMachen()
{
    QColor farbe(0,0,0);//schwarz
    ui->listWidget_Programmliste->currentItem()->setForeground(QBrush(farbe));
}

void MainWindow::elementEinblendenSichtbarMachen(QListWidgetItem *item)
{
    QColor farbe(0,0,0);//schwarz
    item->setForeground(QBrush(farbe));
}

void MainWindow::elementAusblendenSichtbarMachen()
{
    QColor farbe(180,205,205);//grau
    ui->listWidget_Programmliste->currentItem()->setForeground(QBrush(farbe));
}

void MainWindow::elementAusblendenSichtbarMachen(QListWidgetItem *item)
{
    QColor farbe(180,205,205);//grau
    item->setForeground(QBrush(farbe));
}

//---------------------------------------------------Datei:

void MainWindow::on_actionNeu_triggered()
{
    int max = ANZAHL_OFFENER_DATEIEN;
    if(tt.get_size() >= max)
    {
        QString msg;
        msg += "Bitter zuerst eine Datei schliessen!\n";
        msg += "Es koennen maximal ";
        msg += int_to_qstring(max);
        msg += " Dateien gleichzeitig offen sein!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return;
    }
    programmtext t;
    t.set_text("");
    QString name = "Unbekannt ";
    anz_neue_dateien++;
    name += int_to_qstring(anz_neue_dateien);
    undo_redo tmpur;
    tmpur.set_groesse_max(settings_anz_undo_t.toInt());
    tt.add(t, name, tmpur);
    update_gui();
    ui->listWidget_Programmliste->item(0)->setSelected(true);
    ui->listWidget_Programmliste->setCurrentRow(0);
}

void MainWindow::on_actionOffnen_triggered()
{
    int max = ANZAHL_OFFENER_DATEIEN;
    if(tt.get_size() >= max)
    {
        QString msg;
        msg += "Bitter zuerst eine Datei schliessen!\n";
        msg += "Es koennen maximal ";
        msg += int_to_qstring(max);
        msg += " Dateien gleichzeitig offen sein!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return;
    }else
    {
        //Dialog öffnen zum Wählen der Datei:
        QString pfad = QFileDialog::getOpenFileName(this, tr("Waehle WOP-Datei"), \
                                                    pfad_oefne_fmc, tr("fmc Dateien (*.fmc)"));
        if(!pfad.isEmpty())
        {
            openFile(pfad);
        }
    }
}

void MainWindow::openFile(QString pfad)
{
    //Prüfen, ob Datei bereits geöffnet ist:
    if(tt.isopen(pfad))
    {
        tt.set_current_index(pfad);
        update_gui();
    }else
    {
        QFile file(pfad);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            //Programmdatei laden:
            QFileInfo info = pfad;
            pfad_oefne_fmc = info.path();
            QApplication::setOverrideCursor(Qt::WaitCursor);
            text_zeilenweise tz;
            while(!file.atEnd())
            {
                QString line = file.readLine();
                if(line.right(1) == "\n")
                {
                    line = line.left(line.length()-1);
                }
                if(tz.zeilenanzahl() == 0)
                {
                    tz.set_text(line);
                }else
                {
                    tz.zeilen_anhaengen(line);
                }
            }
            tz = kompatiblitaetspruefung(tz);
            tz = import_fmc(tz);
            programmtext t;
            t.set_text(tz.get_text());
            t.aktualisieren_fkon_ein_aus(tt.get_aktualisieren_fkon_ein_aus());
            undo_redo tmpur;
            tmpur.set_groesse_max(settings_anz_undo_t.toInt());
            tt.add(t, pfad, tmpur);
            tt.get_prgtext()->set_maschinengeometrie(tz);
            file.close();

            //aktuelisiere_letzte_dateien_inifile();
            //aktualisiere_letzte_dateien_menu();
            tt.get_prgtext()->wurde_gespeichert();
            update_gui();
            QApplication::restoreOverrideCursor();
        }else
        {
            if(!file.exists())
            {
                QMessageBox mb;
                mb.setText("Datei existiert nicht mehr oder wurde verschoben oder umbenannt!");
                mb.exec();
            }else
            {
                QMessageBox mb;
                mb.setText("Datei existiert, konnte jedoch nicht geoeffnet werden!");
                mb.exec();
            }
            //letzte_geoefnete_dateien.datei_vergessen(pfad);
            //aktualisiere_letzte_dateien_menu();
            //aktuelisiere_letzte_dateien_inifile();
        }
    }
}

text_zeilenweise MainWindow::kompatiblitaetspruefung(text_zeilenweise dateiinhalt)
{
    return dateiinhalt;
}

text_zeilenweise MainWindow::import_fmc(text_zeilenweise tz)
{
    text_zeilenweise retz;
    for(uint i=1; i<= tz.zeilenanzahl();i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile.contains(DLG_PKOPF))
        {
            QString prgzeile;
            prgzeile = DLG_PKOPF;
            prgzeile += vorlage_pkopf;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(PKOPF_KOM1))
                {
                    QString alterWert = text_mitte(prgzeile, PKOPF_KOM1, ENDPAR);
                    QString neuerWert = text_rechts(zeile, PKOPF_KOM1);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(PKOPF_KOM1+alterWert, PKOPF_KOM1+neuerWert);
                }else if (zeile.contains(PKOPF_KOM2))
                {
                    QString alterWert = text_mitte(prgzeile, PKOPF_KOM2, ENDPAR);
                    QString neuerWert = text_rechts(zeile, PKOPF_KOM2);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(PKOPF_KOM2+alterWert, PKOPF_KOM2+neuerWert);
                }else if (zeile.contains(PKOPF_L))
                {
                    QString param = PKOPF_L;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_B))
                {
                    QString param = PKOPF_B;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_D))
                {
                    QString param = PKOPF_D;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_FUENFSEI))
                {
                    QString param = PKOPF_FUENFSEI;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_SPEIGELN))
                {

                }else if (zeile.contains(PKOPF_BELEGART))
                {

                }else if (zeile.contains(PKOPF_XVERS))
                {
                    QString param = PKOPF_XVERS;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_YVERS))
                {
                    QString param = PKOPF_YVERS;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOFP_RTL))
                {
                    QString param = PKOFP_RTL;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOFP_RTB))
                {
                    QString param = PKOFP_RTB;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_LOESEN))
                {

                }else if (zeile.contains(PKOPF_SCHABH))
                {
                    QString param = PKOPF_SCHABH;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_SIABST))
                {
                    QString param = PKOPF_SIABST;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_PAPO))
                {

                }else if (zeile.contains(PKOPF_BEZ))
                {
                    QString param = PKOPF_BEZ;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_AFB))
                {

                }else if (zeile.contains(PKOPF_AUSGEBL))
                {

                }
                i++;
                zeile = tz.zeile(i);
            }
            retz.zeile_anhaengen(prgzeile);
        }
    }

    return retz;
}

//---------------------------------------------------Bearbeiten:

void MainWindow::on_action_aendern_triggered()
{
    disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
    disconnect(this, SIGNAL(sendDialogData(QString, bool, QStringList)), 0, 0);

    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        QList<QListWidgetItem*> items = ui->listWidget_Programmliste->selectedItems();
        int items_menge = items.count();

        if(items_menge==1)
        {
            //text aus der aktiven Zeile in string speichern:
            QString programmzeile;
            if(ui->listWidget_Programmliste->currentIndex().isValid()  &&  (ui->listWidget_Programmliste->currentItem()->isSelected()))
            {
                programmzeile = tt.get_prgtext()->zeile(ui->listWidget_Programmliste->currentRow()+1);
            } else
            {
                QMessageBox mb;
                mb.setText("Sie haben noch nichts ausgewaelt was geaendert werden kann!");
                mb.exec();
                return;
            }
            //ermitteln an welches Unterfenster der string gehen soll und die Zeile Übergeben:
            if(programmzeile.contains(DLG_PKOPF))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &prgkopf, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }//else if....
        }
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {

    }
}

void MainWindow::on_listWidget_Programmliste_itemDoubleClicked(QListWidgetItem *item)
{
    emit on_action_aendern_triggered();
}


//---------------------------------------------------Vorschaufenster

void MainWindow::vorschauAktualisieren()
{
    connect(this, SIGNAL(sendVorschauAktualisieren(programmtext,int)), &vorschaufenster, SLOT(slot_aktualisieren(programmtext,int)));
    emit sendVorschauAktualisieren(*tt.get_prgtext(), ui->listWidget_Programmliste->currentRow()+1);
}

void MainWindow::on_listWidget_Programmliste_currentRowChanged(int currentRow)
{
    connect(this, SIGNAL(sendAktiveProgrammzeile(int)), &vorschaufenster, SLOT(slot_aktives_Element_einfaerben(int)));
    emit sendAktiveProgrammzeile(currentRow+1);
}

void MainWindow::slot_maus_pos(QPoint p)
{
    int x = p.x();
    int y = p.y();
    QString x_ = QString::fromStdString(int_to_string(x));
    QString y_ = QString::fromStdString(int_to_string(y));
    ui->statusBar->showMessage("X:" + x_ + " / Y:" + y_);
}

//---------------------------------------------------Dialoge:
void MainWindow::getDialogData(QString text)
{
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        text_zeilenweise at = tt.get_prgtext()->get_anzeigetext_zeilenweise();
        if(at.zeilenanzahl() == 0)
        {
            tt.get_prgtext()->zeile_anhaengen(text);
            aktualisiere_anzeigetext();
            //pruefe_benutzereingaben(ui->listWidget_Programmliste->currentRow()+1);
        }else
        {
            //Zeile über aktiver Zeile einfügen:
            tt.get_prgtext()->zeile_einfuegen(ui->listWidget_Programmliste->currentRow(), text);
            //aktualisieren und Element darunter aktivieren:
            int row = aktualisiere_anzeigetext() + 1;
            ui->listWidget_Programmliste->setCurrentRow(row);
            //pruefe_benutzereingaben(ui->listWidget_Programmliste->currentRow());
        }
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {

    }
    vorschauAktualisieren();
    update_windowtitle();
}

void MainWindow::getDialogDataModify(QString text)
{
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        QString text_alt = tt.get_prgtext()->zeile(ui->listWidget_Programmliste->currentRow()+1);
        if(text != text_alt)
        {
            if(elementIstEingeblendet())
            {
                tt.get_prgtext()->zeile_ersaetzen(ui->listWidget_Programmliste->currentRow()+1, text);
                aktualisiere_anzeigetext();
                //pruefe_benutzereingaben(ui->listWidget_Programmliste->currentRow()+1);
            }else
            {
                tt.get_prgtext()->zeile_ersaetzen(ui->listWidget_Programmliste->currentRow()+1, "//"+text);
                aktualisiere_anzeigetext();
            }
        }
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {

    }
    vorschauAktualisieren();
    update_windowtitle();
}

void MainWindow::on_actionProgrammliste_anzeigen_triggered()
{
    QString tmp_text;
    tmp_text = "";
    text_zeilenweise te =tt.get_prgtext()->get_text_zeilenweise();
    for(uint i=1 ; i<=te.zeilenanzahl() ; i++)
    {
        tmp_text += QString::fromStdString(int_to_string(i));
        tmp_text += "--";
        tmp_text += te.zeile(i);
        tmp_text += "\n";
    }

    QString tmp_klartext;
    tmp_klartext = "";
    text_zeilenweise kl =tt.get_prgtext()->get_klartext_zeilenweise();
    for(uint i=1 ; i<=kl.zeilenanzahl() ; i++)
    {
        tmp_klartext += QString::fromStdString(int_to_string(i));
        tmp_klartext += "--";
        tmp_klartext += kl.zeile(i);
        tmp_klartext += "\n";
    }

    QString tmp_var;
    tmp_var += "";
    text_zeilenweise v =tt.get_prgtext()->get_variablen_zeilenweise();
    for(uint i=1 ; i<=v.zeilenanzahl() ; i++)
    {
        tmp_var += QString::fromStdString(int_to_string(i));
        tmp_var += "--";
        tmp_var += v.zeile(i);
        tmp_var += "\n";
    }

    QString tmp_geom;
    tmp_geom = "";
    text_zeilenweise g =tt.get_prgtext()->get_geo().get_text_zeilenweise();
    for(uint i=1 ; i<=g.zeilenanzahl() ; i++)
    {
        tmp_geom += QString::fromStdString(int_to_string(i));
        tmp_geom += "--";
        tmp_geom += g.zeile(i);
        tmp_geom += "\n";
    }

    QString tmp_fkon;
    tmp_fkon = "";
    text_zeilenweise fk =tt.get_prgtext()->get_fkon().get_text_zeilenweise();
    for(uint i=1 ; i<=fk.zeilenanzahl() ; i++)
    {
        tmp_fkon += QString::fromStdString(int_to_string(i));
        tmp_fkon += "--";
        tmp_fkon += fk.zeile(i);
        tmp_fkon += "\n";
    }

    connect( this, \
             SIGNAL(send_an_programmlisten(QString,QString,QString,QString,QString)),\
             &programmlisten,\
             SLOT(daten_anzeigen(QString,QString,QString,QString,QString)));
    emit send_an_programmlisten(tmp_text,\
                                tmp_klartext,\
                                tmp_var,\
                                tmp_geom,\
                                tmp_fkon);
}

void MainWindow::on_actionMakeProgrammkopf_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &prgkopf, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_pkopf;
        emit sendDialogData(msg, false);
    }
}

//---------------------------------------------------






