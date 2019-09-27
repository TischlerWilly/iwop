#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Defaultwerte:
    kopierterEintrag_t              = NICHT_DEFINIERT;
    //kopiertesWerkzeug               = NICHT_DEFINIERT;
    vorlage_pkopf                   = NICHT_DEFINIERT;
    settings_anz_undo_t             = "10";
    speichern_unter_flag            = false;
    tt.clear();
    anz_neue_dateien                = 0;//Zählung neuer Dateien mit 0 beginnen und dann raufzählen    
    QDir tmpdir("P:\\CNC");
    if(tmpdir.exists())
    {
        pfad_oefne_fmc = "P:\\CNC";
    }else
    {
        //pfad_oefne_fmc += "C:\\Users\\AV6\\Documents\\CNC-Programme";
        QString tmp;
        tmp  = QDir::homePath();
        tmp += QDir::separator();
        tmp += "Documents";
        tmp += QDir::separator();
        tmp += "CNC-Programme";

        QDir d(tmp);
        if(!d.exists())
        {
            d.mkpath(tmp);
        }

        pfad_oefne_fmc = tmp;
    }
    letzte_geoefnete_dateien.set_anz_eintreage(ANZAHL_LETZTER_DATEIEN);
    speichern_unter_flag            = false;

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
    loadConfig_letzte_Dateien();

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

    double breitePrgListe =ui->tab_Programmliste->width()/3;
    if(breitePrgListe > 250)
    {
        breitePrgListe =250;
    }

    vorschaufenster.move(breitePrgListe+5,10);
    vorschaufenster.setFixedWidth(ui->tab_Programmliste->width()-breitePrgListe-10);
    vorschaufenster.setFixedHeight(ui->tab_Programmliste->height()-70);
    ui->listWidget_Programmliste->setFixedWidth(breitePrgListe-10);
    ui->listWidget_Programmliste->setFixedHeight(ui->tab_Programmliste->height()-30);

    QMainWindow::resizeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *ce)
{
    while(tt.dateien_sind_offen() == true)
    {
        if(on_actionDateiSchliessen_triggered() == false)
        {
            break;
        }
    }
    if(tt.dateien_sind_offen() == true)
    {
        ce->ignore();
    }else
    {
        ce->accept();
    }
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
        ui->actionNaechste_offen_Datei->setEnabled(true);
        ui->actionLetzte_offene_Datei->setEnabled(true);
    }else
    {
        ui->actionNaechste_offen_Datei->setDisabled(true);
        ui->actionLetzte_offene_Datei->setDisabled(true);
    }
    aktualisiere_letzte_dateien_menu();
    aktualisiere_offene_dateien_menu();
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

void MainWindow::loadConfig_letzte_Dateien()
{
    QFile file(QDir::homePath() + PFAD_LETZTE_DATEIEN);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString tmp;
        while(!file.atEnd())
        {
            tmp += QString::fromUtf8(file.readLine());
        }
        file.close();
        text_zeilenweise tz;
        tz.set_text(tmp);
        QString liste;
        //Reihenfolge umdrehen:
        for(uint i=tz.zeilenanzahl(); i>0;i--)
        {
            liste += tz.zeile(i);
            liste += "\n";
        }
        liste = liste.left(liste.length() - 1);//letzets Zeichen löschen = "\n"
        letzte_geoefnete_dateien.set_text(liste);
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

void MainWindow::on_actionEin_Ausblenden_triggered()
{
    tt.get_prgtext()->warnungen_einschalten(false);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        if((ui->listWidget_Programmliste->currentIndex().isValid())  &&  \
                (ui->listWidget_Programmliste->currentItem()->isSelected()))
        {
            QList<QListWidgetItem*> items = ui->listWidget_Programmliste->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Programmliste->count() ;i++)
            {
                if(ui->listWidget_Programmliste->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }
            int row_letztes = row_erstes + items_menge-1;

            int menge_ausgeblendet = 0;
            int menge_eingeblendet = 0;
            for(int i=row_erstes ; i<=row_letztes ; i++)
            {
                QString zeilentext = tt.get_prgtext()->zeile(i+1);
                if(elementIstEingeblendet(zeilentext))
                {
                    menge_eingeblendet++;
                }else
                {
                    menge_ausgeblendet++;
                }
            }
            if(menge_eingeblendet == items_menge)
            {
                on_actionAuswahl_Ausblenden_triggered();
            }else if(menge_ausgeblendet == items_menge)
            {
                on_actionAuswahl_Einblenden_triggered();
            }
        } else
        {
            QMessageBox mb;
            mb.setText("Sie haben noch nichts ausgewaelt was ausgeblendet werden kann!");
            mb.exec();
        }
    }else
    {
        QMessageBox mb;
        mb.setText("Dieser Befehl kann nur im TAB Programmliste verwendet werden!");
        mb.exec();
    }
    tt.get_prgtext()->warnungen_einschalten(true);
    QApplication::restoreOverrideCursor();
}

void MainWindow::on_actionAuswahl_Einblenden_triggered()
{
     tt.get_prgtext()->warnungen_einschalten(false);
     QApplication::setOverrideCursor(Qt::WaitCursor);
     if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
     {
         if((ui->listWidget_Programmliste->currentIndex().isValid())  &&  \
                 (ui->listWidget_Programmliste->currentItem()->isSelected()))
         {
             QList<QListWidgetItem*> items = ui->listWidget_Programmliste->selectedItems();
             int items_menge = items.count();
             int row_erstes = 0;//Nummer des ersten Elementes
             for(int i=0; i<ui->listWidget_Programmliste->count() ;i++)
             {
                 if(ui->listWidget_Programmliste->item(i)->isSelected())
                 {
                     row_erstes = i;
                     break;
                 }
             }
             int row_letztes = row_erstes + items_menge-1;

            tt.get_prgtext()->aktualisieren_ein_aus(false);
             for(int i=row_erstes ; i<=row_letztes ; i++)
             {
                 QString zeilentext =tt.get_prgtext()->zeile(i+1);
                 if(!elementIstEingeblendet(zeilentext))
                 {
                     int laenge = zeilentext.length();
                     zeilentext = zeilentext.right(laenge-2);
                    tt.get_prgtext()->zeile_ersaetzen(i+1, zeilentext);
                     QColor farbe(180,205,205);//grau
                     ui->listWidget_Programmliste->item(i)->setForeground(QBrush(farbe));
                 }
             }
            tt.get_prgtext()->aktualisieren_ein_aus(true);
             aktualisiere_anzeigetext();
             vorschauAktualisieren();
             for(int i=row_erstes ; i<=row_letztes ; i++)
             {
                 ui->listWidget_Programmliste->item(i)->setSelected(true);
             }
         } else
         {
             QMessageBox mb;
             mb.setText("Sie haben noch nichts ausgewaelt was ausgeblendet werden kann!");
             mb.exec();
         }
     }else
     {
         QMessageBox mb;
         mb.setText("Dieser Befehl kann nur im TAB Programmliste verwendet werden!");
         mb.exec();
     }
    tt.get_prgtext()->warnungen_einschalten(true);
     QApplication::restoreOverrideCursor();
}

void MainWindow::on_actionAuswahl_Ausblenden_triggered()
{
    tt.get_prgtext()->warnungen_einschalten(false);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        if((ui->listWidget_Programmliste->currentIndex().isValid())  &&  \
                (ui->listWidget_Programmliste->currentItem()->isSelected()))
        {
            QList<QListWidgetItem*> items = ui->listWidget_Programmliste->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Programmliste->count() ;i++)
            {
                if(ui->listWidget_Programmliste->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }
            int row_letztes = row_erstes + items_menge-1;

            tt.get_prgtext()->aktualisieren_ein_aus(false);
            for(int i=row_erstes ; i<=row_letztes ; i++)
            {
                QString zeilentext =tt.get_prgtext()->zeile(i+1);
                if(elementIstEingeblendet(zeilentext))
                {
                   tt.get_prgtext()->zeile_ersaetzen(i+1,"//"+zeilentext);
                    QColor farbe(180,205,205);//grau
                    ui->listWidget_Programmliste->item(i)->setForeground(QBrush(farbe));
                }
            }
            tt.get_prgtext()->aktualisieren_ein_aus(true);
            aktualisiere_anzeigetext();
            vorschauAktualisieren();
            for(int i=row_erstes ; i<=row_letztes ; i++)
            {
                ui->listWidget_Programmliste->item(i)->setSelected(true);
            }
        } else
        {
            QMessageBox mb;
            mb.setText("Sie haben noch nichts ausgewaelt was ausgeblendet werden kann!");
            mb.exec();
        }
    }else
    {
        QMessageBox mb;
        mb.setText("Dieser Befehl kann nur im TAB Programmliste verwendet werden!");
        mb.exec();
    }
    tt.get_prgtext()->warnungen_einschalten(true);
    QApplication::restoreOverrideCursor();
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
            tz.set_text(QString::fromLatin1(file.readAll()));
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

            aktuelisiere_letzte_dateien_inifile();
            aktualisiere_letzte_dateien_menu();
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
            letzte_geoefnete_dateien.datei_vergessen(pfad);
            aktualisiere_letzte_dateien_menu();
            aktuelisiere_letzte_dateien_inifile();
        }
    }
}

void MainWindow::aktuelisiere_letzte_dateien_inifile()
{
    if(tt.dateien_sind_offen() == true)
    {
        letzte_geoefnete_dateien.datei_merken(tt.get_prgname());
    }
    //Daten Speichern:
    QFile inifile(QDir::homePath() + PFAD_LETZTE_DATEIEN);
    if (!inifile.open(QIODevice::WriteOnly | QIODevice::Text)) //Wenn es nicht möglich ist die Datei zu öffnen oder neu anzulegen
    {
        QMessageBox mb;
        mb.setText("Fehler beim Zugriff auf die Datei \"letzte_dateien.ini\"");
        mb.exec();
    } else
    {
        inifile.remove(); //lösche alte Datei wenn vorhanden
        inifile.close(); //beende Zugriff
        inifile.open(QIODevice::WriteOnly | QIODevice::Text); //lege Datei neu an
        inifile.write(letzte_geoefnete_dateien.get_text().toUtf8()); //fülle Datei mit Inhalt
        inifile.close(); //beende Zugriff
    }
}

void MainWindow::aktualisiere_letzte_dateien_menu()
{
    ui->menuLetzte_Dateien->clear();

    text_zeilenweise namen;
    namen.set_text(letzte_geoefnete_dateien.get_text());
    for(uint i=1; i<=namen.zeilenanzahl() ;i++)
    {
        oefneLetzteDateien[i-1] = new QAction(namen.zeile(i), this);
        ui->menuLetzte_Dateien->addAction(oefneLetzteDateien[i-1]);
        oefneLetzteDateien[i-1]->setData(namen.zeile(i));
        connect(oefneLetzteDateien[i-1], SIGNAL(triggered()), \
                this, SLOT(actionLetzteDateiOefnenTriggered()));
    }

}

void MainWindow::aktualisiere_offene_dateien_menu()
{
    ui->menuOffene_Dateien->clear();

    text_zeilenweise namen;
    namen = tt.get_names();
    for(uint i=1; i<=namen.zeilenanzahl() ;i++)
    {
        OffeneDateieFokus[i-1] = new QAction(namen.zeile(i), this);
        ui->menuOffene_Dateien->addAction(OffeneDateieFokus[i-1]);
        OffeneDateieFokus[i-1]->setData(namen.zeile(i));
        connect(OffeneDateieFokus[i-1], SIGNAL(triggered(bool)),        \
                this, SLOT(actionFokuswechselOffeneDateiTriggered())    );
    }
}

void MainWindow::actionFokuswechselOffeneDateiTriggered()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
    {
        QString msg = action->data().toString();
        tt.set_current_index(msg);
        update_gui();
    }
}

void MainWindow::actionLetzteDateiOefnenTriggered()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
    {
        QString msg = action->data().toString();
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
            openFile(msg);
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
            zeile.replace("'",".");
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
                    QString param = PKOPF_SPEIGELN;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_BELEGART))
                {
                    QString param = PKOPF_BELEGART;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
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
                    QString param = PKOPF_LOESEN;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
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
                    QString param = PKOPF_PAPO;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
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
                    QString param = PKOPF_AFB;
                    QString alterWert = text_mitte(prgzeile, param, ENDPAR);
                    QString neuerWert = text_rechts(zeile, param);
                    if(neuerWert == FMCNULL)
                    {
                        neuerWert = "";
                    }
                    prgzeile.replace(param+alterWert, param+neuerWert);
                }else if (zeile.contains(PKOPF_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            retz.zeile_anhaengen(prgzeile);
        }
    }

    return retz;
}

QString MainWindow::export_fmc(text_zeilenweise tz)
{
    QString msg;
    QString tmp;
    for(uint i=1; i<=tz.zeilenanzahl();i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile.contains(DLG_PKOPF))
        {
            msg += DLG_PKOPF;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += PKOPF_KOM1;
            tmp = selektiereEintrag(zeile, PKOPF_KOM1, ENDPAR);
            if(tmp.isEmpty())
            {
                msg += FMCNULL;
            }else
            {
                msg += tmp;
            }
            msg += "\n";
            msg += PKOPF_KOM2;
            tmp = selektiereEintrag(zeile, PKOPF_KOM2, ENDPAR);
            if(tmp.isEmpty())
            {
                msg += FMCNULL;
            }else
            {
                msg += tmp;
            }
            msg += "\n";
            msg += PKOPF_L;
            msg += selektiereEintrag(zeile, PKOPF_L, ENDPAR);
            msg += "\n";
            msg += PKOPF_B;
            msg += selektiereEintrag(zeile, PKOPF_B, ENDPAR);
            msg += "\n";
            msg += PKOPF_D;
            msg += selektiereEintrag(zeile, PKOPF_D, ENDPAR);
            msg += "\n";
            msg += PKOPF_FUENFSEI;
            msg += selektiereEintrag(zeile, PKOPF_FUENFSEI, ENDPAR);
            msg += "\n";
            msg += PKOPF_SPEIGELN;
            msg += selektiereEintrag(zeile, PKOPF_SPEIGELN, ENDPAR);
            msg += "\n";
            msg += PKOPF_BELEGART;
            msg += selektiereEintrag(zeile, PKOPF_BELEGART, ENDPAR);
            msg += "\n";
            msg += PKOPF_XVERS;
            msg += selektiereEintrag(zeile, PKOPF_XVERS, ENDPAR);
            msg += "\n";
            msg += PKOPF_YVERS;
            msg += selektiereEintrag(zeile, PKOPF_YVERS, ENDPAR);
            msg += "\n";
            msg += PKOFP_RTL;
            msg += selektiereEintrag(zeile, PKOFP_RTL, ENDPAR);
            msg += "\n";
            msg += PKOFP_RTB;
            msg += selektiereEintrag(zeile, PKOFP_RTB, ENDPAR);
            msg += "\n";
            msg += PKOPF_LOESEN;
            msg += selektiereEintrag(zeile, PKOPF_LOESEN, ENDPAR);
            msg += "\n";
            msg += PKOPF_SCHABH;
            msg += selektiereEintrag(zeile, PKOPF_SCHABH, ENDPAR);
            msg += "\n";
            msg += PKOPF_SIABST;
            msg += selektiereEintrag(zeile, PKOPF_SIABST, ENDPAR);
            msg += "\n";
            msg += PKOPF_PAPO;
            msg += selektiereEintrag(zeile, PKOPF_PAPO, ENDPAR);
            msg += "\n";
            msg += PKOPF_BEZ;
            msg += selektiereEintrag(zeile, PKOPF_BEZ, ENDPAR);
            msg += "\n";
            msg += PKOPF_AFB;
            msg += selektiereEintrag(zeile, PKOPF_AFB, ENDPAR);
            msg += "\n";

            msg += "\n";
        }
    }
    return msg;
}

void MainWindow::on_actionNaechste_offen_Datei_triggered()
{
    tt.set_index_nach();
    update_gui();
}

void MainWindow::on_actionLetzte_offene_Datei_triggered()
{
    tt.set_index_vor();
    update_gui();
}

bool MainWindow::on_actionDateiSpeichern_triggered()
{
    if(tt.dateien_sind_offen() == false)
    {
        return true;//Funktion erfolgreich beendet
    }
    QString fileName;
    if((tt.get_prgname().contains("Unbekannt ") && tt.get_prgname().length() <= 13)  ||  speichern_unter_flag == true)
    {
        //Dialog öffnen zum Wählen des Speicherortes und des Namens:
        fileName = QFileDialog::getSaveFileName(this, tr("Datei Speichern"), \
                                                pfad_oefne_fmc, tr("fmc Dateien (*.fmc)"));
        if(!fileName.isEmpty())
        {
            QFileInfo info = fileName;
            pfad_oefne_fmc = info.path();
            if(!fileName.contains(DATEIENDUNG_EIGENE))
            {
                fileName += DATEIENDUNG_EIGENE;
            }
            if(fileName == DATEIENDUNG_EIGENE)//Wenn der Speichen-Dialog abgebrochen wurde
            {
                return false;//Funktion nicht erfolgreich beendet
            }else
            {
                tt.set_prgname(fileName);
            }
        }else //Speichen-Dialog wurde abgebrochen
        {
            return false;//Funktion nicht erfolgreich beendet
        }
    }else
    {
        //Namen der offenen Datei verwenden:

        fileName = tt.get_prgname();
        if(!fileName.contains(DATEIENDUNG_EIGENE))
        {
            fileName += DATEIENDUNG_EIGENE;
        }
    }

    //Programmliste in String schreiben
    QString dateiInhalt = export_fmc(tt.get_prgtext()->get_text_zeilenweise());

    //Datei füllen und speichern
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) //Wenn es nicht möglich ist die Datei zu öffnen oder neu anzulegen
        {
            QMessageBox mb;
            mb.setText("Fehler beim Dateizugriff");
            mb.exec();
            return false;//Funktion nicht erfolgreich beendet
        } else
        {
            file.remove(); //lösche alte Datei wenn vorhanden
            file.close(); //beende Zugriff
            file.open(QIODevice::WriteOnly | QIODevice::Text); //lege Datei neu an
            file.write(dateiInhalt.toLatin1()); //fülle Datei mit Inhalt
            file.close(); //beende Zugriff
            QFileInfo info = tt.get_prgname();
            QString tmp = PROGRAMMNAME;
            tmp += " ( " + info.baseName() + " )";
            this->setWindowTitle(tmp);
            tt.get_prgtext()->wurde_gespeichert();
            aktuelisiere_letzte_dateien_inifile();
            aktualisiere_letzte_dateien_menu();
            aktualisiere_offene_dateien_menu();
        }
    }
    return true;//Funktion erfolgreich beendet
}

void MainWindow::on_actionDateiSpeichern_unter_triggered()
{
    speichern_unter_flag = true;
    on_actionDateiSpeichern_triggered();
    speichern_unter_flag = false;
    QFileInfo info = tt.get_prgname();
    QString tmp = PROGRAMMNAME;
    tmp += " ( " + info.baseName() + " )";
    this->setWindowTitle(tmp);
}

bool MainWindow::on_actionDateiSchliessen_triggered()
{
    //Sicherheitsabfrage:
    if(tt.get_prgtext()->get_hat_ungesicherte_inhalte() == true)
    {
        QFileInfo info;
        info = tt.get_prgname();
        QString dateiname = info.baseName();
        QString msg;

        if(dateiname == NICHT_DEFINIERT)
        {
            msg = "Soll die neue Datei vor dem Schliessen gespeichert werden?";
        }else
        {
            msg = "Soll die Datei \"";
            msg += dateiname;
            msg += "\" vor dem Schliessen gespeichert werden?";
        }
        QMessageBox mb;
        mb.setWindowTitle("Datei schliessen");
        mb.setText(msg);
        mb.setStandardButtons(QMessageBox::Yes);
        mb.addButton(QMessageBox::No);
        mb.addButton(QMessageBox::Abort);
        mb.setDefaultButton(QMessageBox::Abort);

        int mb_returnwert = mb.exec();
        if(mb_returnwert == QMessageBox::Yes)
        {
            if(on_actionDateiSpeichern_triggered() == false)//Speichern nicht erfolgreich abgeschlossen
            {
                return false;//Funktion nicht erfolgreich abgeschlossen
            }
        }else if(mb_returnwert == QMessageBox::No)
        {
            ;//nichts tun = nicht speichern
        }else if(mb_returnwert == QMessageBox::Abort)
        {
            return false;//Funktion nicht erfolgreich abgeschlossen
        }
    }
    //Datei schließen:
    tt.del();
    ui->listWidget_Programmliste->clear();
    aktualisiere_offene_dateien_menu();
    //GUI aktualisieren:
    update_gui();

    return true;//Funktion erfolgreich abgeschlossen
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

void MainWindow::on_actionRueckgaengig_triggered()
{
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        //t = ur.undo();
        *tt.get_prgtext() = tt.get_prg_undo_redo()->undo();
        aktualisiere_anzeigetext(false);
        vorschauAktualisieren();
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {
        //w = ur_wkz.undo();
        //aktualisiere_anzeigetext_wkz(false);
    }
}

void MainWindow::on_actionWiederholen_triggered()
{
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        //t = ur.redo();
        *tt.get_prgtext() = tt.get_prg_undo_redo()->redo();
        aktualisiere_anzeigetext(false);
        vorschauAktualisieren();
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {
        //w = ur_wkz.redo();
        //aktualisiere_anzeigetext_wkz(false);
    }
}

void MainWindow::on_actionEinfuegen_triggered()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        if(kopierterEintrag_t != NICHT_DEFINIERT)
        {
            QList<QListWidgetItem*> items = ui->listWidget_Programmliste->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Programmliste->count() ;i++)
            {
                if(ui->listWidget_Programmliste->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }

            //Einfügen über ausgewähltem Eintrag:
            text_zeilenweise tmp_tz;
            tmp_tz.set_text(kopierterEintrag_t);
            if(tmp_tz.zeilenanzahl()==1)
            {
                tt.get_prgtext()->zeile_einfuegen(ui->listWidget_Programmliste->currentRow()-items_menge+1 \
                                                 , kopierterEintrag_t);
                int row = aktualisiere_anzeigetext()-items_menge+2 ;
                ui->listWidget_Programmliste->setCurrentRow(row);
            }else
            {
                tt.get_prgtext()->zeilen_einfuegen(row_erstes, kopierterEintrag_t);
                int row = aktualisiere_anzeigetext()-items_menge+2+tmp_tz.zeilenanzahl()-1 ;
                ui->listWidget_Programmliste->setCurrentRow(row);
            }
        }else
        {
            QMessageBox mb;
            mb.setText("Sie haben noch nichts kopiert!");
            mb.exec();
        }
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {

    }
    vorschauAktualisieren();
    update_windowtitle();
    QApplication::restoreOverrideCursor();
}

void MainWindow::on_actionKopieren_triggered()
{
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        if((ui->listWidget_Programmliste->currentIndex().isValid())  &&  (ui->listWidget_Programmliste->currentItem()->isSelected()))
        {
            QList<QListWidgetItem*> items = ui->listWidget_Programmliste->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Programmliste->count() ;i++)
            {
                if(ui->listWidget_Programmliste->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }

            if(items_menge==1)
            {
                QString tmp = tt.get_prgtext()->zeile(ui->listWidget_Programmliste->currentRow()+1);
                if(tmp == LISTENENDE)
                {
                    return;
                }
                kopierterEintrag_t = tmp;
            }else
            {
                QString tmp = tt.get_prgtext()->zeilen(row_erstes+1, items_menge);
                kopierterEintrag_t = tmp;
            }
        } else
        {
            QMessageBox mb;
            mb.setText("Sie haben noch nichts ausgewaelt was kopiert werden kann!");
            mb.exec();
        }
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {

    }
}

void MainWindow::on_actionAusschneiden_triggered()
{
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        if((ui->listWidget_Programmliste->currentIndex().isValid())  &&  (ui->listWidget_Programmliste->currentItem()->isSelected()))
        {
            QList<QListWidgetItem*> items = ui->listWidget_Programmliste->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Programmliste->count() ;i++)
            {
                if(ui->listWidget_Programmliste->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }

            if(items_menge==1)
            {
                QString tmp = tt.get_prgtext()->zeile(ui->listWidget_Programmliste->currentRow()+1);
                if(tmp == LISTENENDE)
                {
                    return;
                }
                kopierterEintrag_t = tt.get_prgtext()->zeile(ui->listWidget_Programmliste->currentRow()+1);
                tt.get_prgtext()->zeile_loeschen(ui->listWidget_Programmliste->currentRow()+1);
                aktualisiere_anzeigetext();
            }else
            {
                //Zeilen kopieren:
                QString tmp = tt.get_prgtext()->zeilen(row_erstes+1, items_menge);
                kopierterEintrag_t = tmp;
                //Zeilen löschen:
                tt.get_prgtext()->zeilen_loeschen(row_erstes+1, items_menge);
                aktualisiere_anzeigetext();
                ui->listWidget_Programmliste->setCurrentRow(row_erstes);
            }
            QApplication::setOverrideCursor(Qt::WaitCursor);
            vorschauAktualisieren();
            update_windowtitle();
            QApplication::restoreOverrideCursor();
        } else
        {
            QMessageBox mb;
            mb.setText("Sie haben noch nichts ausgewaelt was ausgeschnitten werden kann!");
            mb.exec();
        }
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {

    }
}

void MainWindow::on_actionEntfernen_triggered()
{
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        if((ui->listWidget_Programmliste->currentIndex().isValid())  &&  \
                (ui->listWidget_Programmliste->currentItem()->isSelected()))
        {
            QList<QListWidgetItem*> items = ui->listWidget_Programmliste->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Programmliste->count() ;i++)
            {
                if(ui->listWidget_Programmliste->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }

            if(items_menge == 1)
            {
                QString tmp = tt.get_prgtext()->zeile(ui->listWidget_Programmliste->currentRow()+1);
                if(tmp == LISTENENDE)
                {
                    return;
                }
                tt.get_prgtext()->zeile_loeschen(ui->listWidget_Programmliste->currentRow()+1);
                aktualisiere_anzeigetext();
            }else
            {
                tt.get_prgtext()->zeilen_loeschen(row_erstes+1, items_menge);
                aktualisiere_anzeigetext();
                ui->listWidget_Programmliste->setCurrentRow(row_erstes);
            }
            QApplication::setOverrideCursor(Qt::WaitCursor);
            vorschauAktualisieren();
            update_windowtitle();
            QApplication::restoreOverrideCursor();
        } else
        {
            QMessageBox mb;
            mb.setText("Sie haben noch nichts ausgewaelt was geloescht werden kann!");
            mb.exec();
        }
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {

    }
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













