#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Defaultwerte:
    kopierterEintrag_t              = NICHT_DEFINIERT;
    kopierterEintrag_w              = NICHT_DEFINIERT;
    wkz.set_undo_redo_anz(settings_anz_undo_t.toUInt());
    vorlage_pkopf                   = prgkopf.get_default();
    vorlage_pende                   = prgende.get_default();
    vorlage_kom                     = kom.get_default();
    vorlage_halt                    = halt.get_default();
    vorlage_bo                      = dlgbo.get_default();
    vorlage_boy                     = dlgboy.get_default();
    vorlage_box                     = dlgbox.get_default();
    vorlage_loreiae                 = dlgloreiae.get_default();
    vorlage_loreima                 = dlgloreima.get_default();
    vorlage_topf                    = dlgtopf.get_default();
    vorlage_hbexp                   = dlghbexp.get_default();
    vorlage_hbexm                   = dlghbexm.get_default();
    vorlage_hbeyp                   = dlghbeyp.get_default();
    vorlage_hbeym                   = dlghbeym.get_default();
    vorlage_nut                     = dlgnut.get_default();
    vorlage_kta                     = dlgkta.get_default();
    vorlage_rta                     = dlgrta.get_default();
    vorlage_var                     = dlgvar.get_default();
    vorlage_fauf                    = dlgfauf.get_default();
    vorlage_fabf                    = dlgfabf.get_default();
    vorlage_fgerade                 = dlgfgerade.get_default();
    vorlage_var10                   = dlgvar10.get_default();
    vorlage_spiegeln                = dlgspiegeln.get_default();
    vorlage_lageaendern             = dlglageaendern.get_default();
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

    prgpfade pf;
    QDir dir(pf.get_path_prg());
    if(!dir.exists())
    {
        QString nachricht;
        nachricht = "Programmpfad nicht gefunden. Pfad \"";
        nachricht += pf.get_path_prg();
        nachricht += "\" wird angelegt";
        QMessageBox mb;
        mb.setText(nachricht);
        mb.exec();        
        dir.mkdir(pf.get_path_prg());
        dir.mkdir(pf.get_path_wkzbilder());
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
    loadWKZ();
    loadConfig_letzte_Dateien();

    //connect:
    connect(&prgkopf, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&prgende, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&kom, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&halt, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgbo, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgboy, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgbox, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgloreiae, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgloreima, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgtopf, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlghbexp, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlghbexm, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlghbeyp, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlghbeym, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgnut, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgkta, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgrta, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgvar, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgvar10, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgfauf, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgfabf, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgfgerade, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlgspiegeln, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));
    connect(&dlglageaendern, SIGNAL(signalSaveConfig(QString)), this, SLOT(slotSaveConfig(QString)));

    connect(&prgkopf, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&prgende, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&kom, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&halt, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgbo, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgboy, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgbox, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgloreiae, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgloreima, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgtopf, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlghbexp, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlghbexm, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlghbeyp, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlghbeym, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgnut, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgkta, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgrta, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgvar, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgvar10, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgfauf, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgfabf, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgfgerade, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgspiegeln, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlglageaendern, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgfraeser, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));
    connect(&dlgsaege, SIGNAL(sendDialogData(QString)), this, SLOT(getDialogData(QString)));

    connect(&prgkopf, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&prgende, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&kom, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&halt, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgbo, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgboy, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgbox, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgloreiae, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgloreima, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgtopf, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlghbexp, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlghbexm, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlghbeyp, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlghbeym, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgnut, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgkta, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgrta, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgvar, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgvar10, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgfauf, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgfabf, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgfgerade, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgspiegeln, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlglageaendern, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgfraeser, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));
    connect(&dlgsaege, SIGNAL(sendDialogDataModifyed(QString)), this, SLOT(getDialogDataModify(QString)));

    connect(&dlgnut, SIGNAL(signalNeedWKZ(QString)), this, SLOT(slotNeedWKZ(QString)));
    connect(&dlgkta, SIGNAL(signalNeedWKZ(QString)), this, SLOT(slotNeedWKZ(QString)));
    connect(&dlgrta, SIGNAL(signalNeedWKZ(QString)), this, SLOT(slotNeedWKZ(QString)));
    connect(&dlgfauf, SIGNAL(signalNeedWKZ(QString)), this, SLOT(slotNeedWKZ(QString)));

    connect(&vorschaufenster, SIGNAL(sende_maus_pos(QPoint)), this, SLOT(slot_maus_pos(QPoint)));

    update_gui();
    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_arg(int argc, char **argv)
{
    //argc = anzahl der Argumente
    //argv[0] bis argv[xy] sind die Elemente
    //erstes Element ist der Programmname
    //QString programmname = argv[0];
    //QString msg;
    //msg = "Anzahl der Argumente: ";
    //msg += int_to_qstring(argc);
    //msg += "\n";
    for(int i=1; i<argc ;i++)
    {
        //msg += argv[i];
        //msg += "\n";
        openFile(argv[i]);
    }
    //QMessageBox mb;
    //mb.setText(msg);
    //mb.exec();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //-------------------------------------------Tab-Widget:
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

    //-------------------------------------------Reiter Werkzeug:
    //---Buttons oben;
    ui->pushButton_MakeFraeser->move(5,15);
    ui->pushButton_MakeSaege->move(5+ui->pushButton_MakeFraeser->width()+5, 15);
    //---Liste:
    ui->listWidget_Werkzeug->move(5, 15+ui->pushButton_MakeFraeser->height()+15);
    int tmp;
    tmp = ui->tab_Werkzeug->width() - 10 ;
    if(tmp < 1)
    {
        tmp = 1;
    }
    ui->listWidget_Werkzeug->setFixedWidth(tmp);
    tmp = ui->tab_Werkzeug->height() - 15 - ui->pushButton_MakeFraeser->height() - 15 - ui->pushButton_wkz_speichern->height() - 15 -50;
    if(tmp < 1)
    {
        tmp = 1;
    }
    ui->listWidget_Werkzeug->setFixedHeight(tmp);
    //---Button unten:
    ui->pushButton_wkz_speichern->move(5, ui->listWidget_Werkzeug->pos().y() + ui->listWidget_Werkzeug->height() + 15 );
    //-------------------------------------------Reiter Programmliste:
    double breitePrgListe =ui->tab_Programmliste->width()/3;
    if(breitePrgListe > 250)
    {
        breitePrgListe =250;
    }

    vorschaufenster.move(breitePrgListe+5,10);
    vorschaufenster.setFixedWidth(ui->tab_Programmliste->width()-breitePrgListe-10);
    vorschaufenster.setFixedHeight(ui->tab_Programmliste->height()-60);
    ui->listWidget_Programmliste->setFixedWidth(breitePrgListe-10);
    ui->listWidget_Programmliste->setFixedHeight(ui->tab_Programmliste->height()-60);

    //-------------------------------------------
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    this->resize(this->width()-1 , this->height()-1);
    this->resize(this->width()+1 , this->height()+1);
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
            if(tt.get_prgtext()->get_nurlesend())
            {
                name += " [schreibgeschützt]";
            }
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

int MainWindow::aktualisiere_anzeigetext_wkz(bool undo_redo_on)
{
    int row;
    if(ui->listWidget_Werkzeug->currentIndex().isValid())
    {
        row = ui->listWidget_Werkzeug->currentRow();
    }else
    {
        row = 0;
    }
    ui->listWidget_Werkzeug->clear();
    text_zeilenweise tmp;
    tmp =wkz.get_anzeigetext();
    if(tmp.zeilenanzahl() == 0)
    {
        return -1;
    }
    for(uint i=1 ; i<=tmp.zeilenanzahl() ; i++)
    {
        ui->listWidget_Werkzeug->addItem(tmp.zeile(i));
    }
    for(int row = 0; row < ui->listWidget_Werkzeug->count(); row++)
    {
        QListWidgetItem *item = ui->listWidget_Werkzeug->item(row);
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
    ui->listWidget_Werkzeug->setCurrentRow(row);

    if(undo_redo_on == true)
    {
        wkz.undo_redo_neu();
    }
    return row;
}

//---------------------------------------------------Konfiguration

QString MainWindow::loadConfig()
{
    QString returnString = "OK";
    prgpfade pf;
    QFile file(pf.get_path_inifile());
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
                }else if(text.contains(DLG_PENDE))
                {
                    vorlage_pende = selektiereEintrag(text, DLG_PENDE, ENDE_ZEILE);
                }else if(text.contains(DLG_KOM))
                {
                    vorlage_kom = selektiereEintrag(text, DLG_KOM, ENDE_ZEILE);
                }else if(text.contains(DLG_HALT))
                {
                    vorlage_halt = selektiereEintrag(text, DLG_HALT, ENDE_ZEILE);
                }else if(text.contains(DLG_BO))
                {
                    vorlage_bo = selektiereEintrag(text, DLG_BO, ENDE_ZEILE);
                }else if(text.contains(DLG_BOY))
                {
                    vorlage_boy = selektiereEintrag(text, DLG_BOY, ENDE_ZEILE);
                }else if(text.contains(DLG_BOX))
                {
                    vorlage_box = selektiereEintrag(text, DLG_BOX, ENDE_ZEILE);
                }else if(text.contains(DLG_LOREIAE))
                {
                    vorlage_loreiae = selektiereEintrag(text, DLG_LOREIAE, ENDE_ZEILE);
                }else if(text.contains(DLG_LOREIMA))
                {
                    vorlage_loreima = selektiereEintrag(text, DLG_LOREIMA, ENDE_ZEILE);
                }else if(text.contains(DLG_TOPF))
                {
                    vorlage_topf = selektiereEintrag(text, DLG_TOPF, ENDE_ZEILE);
                }else if(text.contains(DLG_HBEXP))
                {
                    vorlage_hbexp = selektiereEintrag(text, DLG_HBEXP, ENDE_ZEILE);
                }else if(text.contains(DLG_HBEXM))
                {
                    vorlage_hbexm = selektiereEintrag(text, DLG_HBEXM, ENDE_ZEILE);
                }else if(text.contains(DLG_HBEYP))
                {
                    vorlage_hbeyp = selektiereEintrag(text, DLG_HBEYP, ENDE_ZEILE);
                }else if(text.contains(DLG_HBEYM))
                {
                    vorlage_hbeym = selektiereEintrag(text, DLG_HBEYM, ENDE_ZEILE);
                }else if(text.contains(DLG_NUT))
                {
                    vorlage_nut = selektiereEintrag(text, DLG_NUT, ENDE_ZEILE);
                }else if(text.contains(DLG_KTA))
                {
                    vorlage_kta = selektiereEintrag(text, DLG_KTA, ENDE_ZEILE);
                }else if(text.contains(DLG_RTA))
                {
                    vorlage_rta = selektiereEintrag(text, DLG_RTA, ENDE_ZEILE);
                }else if(text.contains(DLG_VAR))
                {
                    vorlage_var = selektiereEintrag(text, DLG_VAR, ENDE_ZEILE);
                }else if(text.contains(DLG_VAR10))
                {
                    vorlage_var10 = selektiereEintrag(text, DLG_VAR10, ENDE_ZEILE);
                }else if(text.contains(DLG_FAUF))
                {
                    vorlage_fauf = selektiereEintrag(text, DLG_FAUF, ENDE_ZEILE);
                }else if(text.contains(DLG_FABF))
                {
                    vorlage_fabf = selektiereEintrag(text, DLG_FABF, ENDE_ZEILE);
                }else if(text.contains(DLG_FGERADE))
                {
                    vorlage_fgerade = selektiereEintrag(text, DLG_FGERADE, ENDE_ZEILE);
                }else if(text.contains(DLG_SPIEGELN))
                {
                    vorlage_spiegeln = selektiereEintrag(text, DLG_SPIEGELN, ENDE_ZEILE);
                }else if(text.contains(DLG_LAGE_AENDERN))
                {
                    vorlage_lageaendern = selektiereEintrag(text, DLG_LAGE_AENDERN, ENDE_ZEILE);
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

    //-------------------------------------------
    inhaltVonKonfiguration +=       DLG_PKOPF;
    inhaltVonKonfiguration +=       vorlage_pkopf;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_PENDE;
    inhaltVonKonfiguration +=       vorlage_pende;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_KOM;
    inhaltVonKonfiguration +=       vorlage_kom;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_HALT;
    inhaltVonKonfiguration +=       vorlage_halt;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_BO;
    inhaltVonKonfiguration +=       vorlage_bo;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_BOY;
    inhaltVonKonfiguration +=       vorlage_boy;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_BOX;
    inhaltVonKonfiguration +=       vorlage_box;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_LOREIAE;
    inhaltVonKonfiguration +=       vorlage_loreiae;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_LOREIMA;
    inhaltVonKonfiguration +=       vorlage_loreima;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_TOPF;
    inhaltVonKonfiguration +=       vorlage_topf;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_HBEXP;
    inhaltVonKonfiguration +=       vorlage_hbexp;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_HBEXM;
    inhaltVonKonfiguration +=       vorlage_hbexm;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_HBEYP;
    inhaltVonKonfiguration +=       vorlage_hbeyp;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_HBEYM;
    inhaltVonKonfiguration +=       vorlage_hbeym;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_NUT;
    inhaltVonKonfiguration +=       vorlage_nut;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_KTA;
    inhaltVonKonfiguration +=       vorlage_kta;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_RTA;
    inhaltVonKonfiguration +=       vorlage_rta;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_VAR;
    inhaltVonKonfiguration +=       vorlage_var;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_VAR10;
    inhaltVonKonfiguration +=       vorlage_var10;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_FAUF;
    inhaltVonKonfiguration +=       vorlage_fauf;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_FABF;
    inhaltVonKonfiguration +=       vorlage_fabf;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_FGERADE;
    inhaltVonKonfiguration +=       vorlage_fgerade;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_SPIEGELN;
    inhaltVonKonfiguration +=       vorlage_spiegeln;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    inhaltVonKonfiguration +=       DLG_LAGE_AENDERN;
    inhaltVonKonfiguration +=       vorlage_lageaendern;
    inhaltVonKonfiguration +=       ENDE_ZEILE;
    inhaltVonKonfiguration +=       "\n";
    //-------------------------------------------
    inhaltVonKonfiguration +=       ENDE_DIALOGE;
    inhaltVonKonfiguration +=       "\n";
    //---------------------------------------------------------------------------------------------------------

    //Daten Speichern:
    prgpfade pf;
    QFile file(pf.get_path_inifile());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) //Wenn es nicht möglich ist die Datei zu öffnen oder neu anzulegen
    {
        QString msg;
        msg = "Fehler beim Zugriff auf die Datei \"";
        msg += pf.get_path_inifile();
        msg += "\"";
        QMessageBox mb;
        mb.setText(msg);
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
        }else if(text.contains(DLG_PENDE))
        {
            vorlage_pende = selektiereEintrag(text, DLG_PENDE, ENDE_ZEILE);
        }else if(text.contains(DLG_KOM))
        {
            vorlage_kom = selektiereEintrag(text, DLG_KOM, ENDE_ZEILE);
        }else if(text.contains(DLG_HALT))
        {
            vorlage_halt = selektiereEintrag(text, DLG_HALT, ENDE_ZEILE);
        }else if(text.contains(DLG_BO))
        {
            vorlage_bo = selektiereEintrag(text, DLG_BO, ENDE_ZEILE);
        }else if(text.contains(DLG_BOY))
        {
            vorlage_boy = selektiereEintrag(text, DLG_BOY, ENDE_ZEILE);
        }else if(text.contains(DLG_BOX))
        {
            vorlage_box = selektiereEintrag(text, DLG_BOX, ENDE_ZEILE);
        }else if(text.contains(DLG_LOREIAE))
        {
            vorlage_loreiae = selektiereEintrag(text, DLG_LOREIAE, ENDE_ZEILE);
        }else if(text.contains(DLG_LOREIMA))
        {
            vorlage_loreima = selektiereEintrag(text, DLG_LOREIMA, ENDE_ZEILE);
        }else if(text.contains(DLG_TOPF))
        {
            vorlage_topf = selektiereEintrag(text, DLG_TOPF, ENDE_ZEILE);
        }else if(text.contains(DLG_HBEXP))
        {
            vorlage_hbexp = selektiereEintrag(text, DLG_HBEXP, ENDE_ZEILE);
        }else if(text.contains(DLG_HBEXM))
        {
            vorlage_hbexm = selektiereEintrag(text, DLG_HBEXM, ENDE_ZEILE);
        }else if(text.contains(DLG_HBEYP))
        {
            vorlage_hbeyp = selektiereEintrag(text, DLG_HBEYP, ENDE_ZEILE);
        }else if(text.contains(DLG_HBEYM))
        {
            vorlage_hbeym = selektiereEintrag(text, DLG_HBEYM, ENDE_ZEILE);
        }else if(text.contains(DLG_NUT))
        {
            vorlage_nut = selektiereEintrag(text, DLG_NUT, ENDE_ZEILE);
        }else if(text.contains(DLG_KTA))
        {
            vorlage_kta = selektiereEintrag(text, DLG_KTA, ENDE_ZEILE);
        }else if(text.contains(DLG_RTA))
        {
            vorlage_rta = selektiereEintrag(text, DLG_RTA, ENDE_ZEILE);
        }else if(text.contains(DLG_VAR))
        {
            vorlage_var = selektiereEintrag(text, DLG_VAR, ENDE_ZEILE);
        }else if(text.contains(DLG_VAR10))
        {
            vorlage_var10 = selektiereEintrag(text, DLG_VAR10, ENDE_ZEILE);
        }else if(text.contains(DLG_FAUF))
        {
            vorlage_fauf = selektiereEintrag(text, DLG_FAUF, ENDE_ZEILE);
        }else if(text.contains(DLG_FABF))
        {
            vorlage_fabf = selektiereEintrag(text, DLG_FABF, ENDE_ZEILE);
        }else if(text.contains(DLG_FGERADE))
        {
            vorlage_fgerade = selektiereEintrag(text, DLG_FGERADE, ENDE_ZEILE);
        }else if(text.contains(DLG_SPIEGELN))
        {
            vorlage_spiegeln = selektiereEintrag(text, DLG_SPIEGELN, ENDE_ZEILE);
        }else if(text.contains(DLG_LAGE_AENDERN))
        {
            vorlage_lageaendern = selektiereEintrag(text, DLG_LAGE_AENDERN, ENDE_ZEILE);
        }

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
    //QFile file(QDir::homePath() + PFAD_LETZTE_DATEIEN);
    prgpfade pf;
    QFile file(pf.get_path_iniLetzteDateien());
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

void MainWindow::on_pushButton_wkz_speichern_clicked()
{
    //Sicherheitsabfrage:
    QMessageBox mb;
    mb.setWindowTitle("Werkzeug speichern");
    mb.setText("Sind Sie sicher, dass das Werkzeugmagazin gespeichert werden soll?");
    mb.setStandardButtons(QMessageBox::Yes);
    mb.addButton(QMessageBox::No);
    mb.setDefaultButton(QMessageBox::No);
    if(mb.exec() == QMessageBox::Yes)
    {
        saveWKZ();
    }else
    {
        QMessageBox mb2;
        mb2.setText("Werkzeugmagazin wurde nicht geaendert.");
        mb2.exec();
    }
}

void MainWindow::saveWKZ()
{
    //Daten Speichern:
    prgpfade pf;
    QFile file(pf.get_path_inifile_wkz());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) //Wenn es nicht möglich ist die Datei zu öffnen oder neu anzulegen
    {
        QString msg;
        msg = "Fehler beim Zugriff auf die Datei \"";
        msg += pf.get_path_inifile_wkz();
        msg += "\"";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
    } else
    {
        file.remove(); //lösche alte Datei wenn vorhanden
        file.close(); //beende Zugriff
        file.open(QIODevice::WriteOnly | QIODevice::Text); //lege Datei neu an
        file.write(wkz.get_text().toUtf8()); //fülle Datei mit Inhalt
        file.close(); //beende Zugriff
        QMessageBox mb;
        mb.setText("Werkzeugmagazin wurde erfolgreich gespeichert.");
        mb.exec();
    }
}

void MainWindow::loadWKZ()
{
    prgpfade pf;
    QFile file(pf.get_path_inifile_wkz());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //Keine Werkzeugdatei vorhanden
    } else
    {
        wkz.set_text(file.readAll());
        file.close();
    }
    aktualisiere_anzeigetext_wkz(true);
}

//---------------------------------------------------Sichtbarkeiten
void MainWindow::hideElemets_noFileIsOpen()
{
    ui->listWidget_Programmliste->hide();
    //Menü Datei:
    ui->actionDateiSpeichern->setDisabled(true);
    ui->actionDateiSpeichern_unter->setDisabled(true);
    ui->actionDateiSchliessen->setDisabled(true);
    //Menü Bearbeiten:
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        //ui->action_aendern->setDisabled(true);
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
    ui->actionMakeProgrammende->setDisabled(true);
    ui->actionMakeKommentar->setDisabled(true);
    ui->actionMakeHalt->setDisabled(true);
    ui->actionMakeBohren_Durchmesser->setDisabled(true);
    ui->actionMakeBohren_in_Y->setDisabled(true);
    ui->actionMakeBohren_in_X->setDisabled(true);
    ui->actionMakeLochreihe_Anfang_Ende->setDisabled(true);
    ui->actionMakeLochreihe_Mitte_Anfang->setDisabled(true);
    ui->actionMakeTopfband->setDisabled(true);
    ui->actionMakeHBE_X_plus->setDisabled(true);
    ui->actionMakeHBE_X_minus->setDisabled(true);
    ui->actionMakeHBE_Y_plus->setDisabled(true);
    ui->actionMakeHBE_Y_minus->setDisabled(true);
    ui->actionMakeNut->setDisabled(true);
    ui->actionMakeKreistasche->setDisabled(true);
    ui->actionMakeRechtecktasche->setDisabled(true);
    ui->actionMakeVariable->setDisabled(true);
    ui->actionMakeVariablen10->setDisabled(true);
    ui->actionMakeFauf->setDisabled(true);
    ui->actionMakeAbfahren->setDisabled(true);
    ui->actionMakeFgerade->setDisabled(true);
    ui->actionMakeSpiegeln->setDisabled(true);
    ui->actionMakeLage_aendern->setDisabled(true);
    //Menü Extras:
    ui->actionProgrammliste_anzeigen->setDisabled(true);
    //anderes:
    vorschaufenster.hide();
}

void MainWindow::showElements_aFileIsOpen()
{
    ui->listWidget_Programmliste->show();
    //Menü Datei:
    ui->actionDateiSpeichern->setEnabled(true);
    ui->actionDateiSpeichern_unter->setEnabled(true);
    ui->actionDateiSchliessen->setEnabled(true);
    //Menü Bearbeiten:
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        //ui->action_aendern->setEnabled(true);
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
    ui->actionMakeProgrammende->setEnabled(true);
    ui->actionMakeKommentar->setEnabled(true);
    ui->actionMakeHalt->setEnabled(true);
    ui->actionMakeBohren_Durchmesser->setEnabled(true);
    ui->actionMakeBohren_in_Y->setEnabled(true);
    ui->actionMakeBohren_in_X->setEnabled(true);
    ui->actionMakeLochreihe_Anfang_Ende->setEnabled(true);
    ui->actionMakeLochreihe_Mitte_Anfang->setEnabled(true);
    ui->actionMakeTopfband->setEnabled(true);
    ui->actionMakeHBE_X_plus->setEnabled(true);
    ui->actionMakeHBE_X_minus->setEnabled(true);
    ui->actionMakeHBE_Y_plus->setEnabled(true);
    ui->actionMakeHBE_Y_minus->setEnabled(true);
    ui->actionMakeNut->setEnabled(true);
    ui->actionMakeKreistasche->setEnabled(true);
    ui->actionMakeRechtecktasche->setEnabled(true);
    ui->actionMakeVariable->setEnabled(true);
    ui->actionMakeVariablen10->setEnabled(true);
    ui->actionMakeFauf->setEnabled(true);
    ui->actionMakeAbfahren->setEnabled(true);
    ui->actionMakeFgerade->setEnabled(true);
    ui->actionMakeSpiegeln->setEnabled(true);
    ui->actionMakeLage_aendern->setEnabled(true);
    //Menü Extras:
    ui->actionProgrammliste_anzeigen->setEnabled(true);
    //anderes:
    vorschaufenster.show();
}

bool MainWindow::elementIstEingeblendet()
{
    QString tmp;
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        tmp = tt.get_prgtext()->zeile(ui->listWidget_Programmliste->currentRow()+1);
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {
        tmp = tt.get_prgtext()->zeile(ui->listWidget_Werkzeug->currentRow()+1);
    }
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
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
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
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {
        uint i = ui->listWidget_Werkzeug->currentRow()+1;
        QString tmp_t = wkz.zeile(i);
        int length_t = tmp_t.length();
        tmp_t = tmp_t.right(length_t-2);
        wkz.zeile_ersaetzen(i, tmp_t);
        QString tmp = ui->listWidget_Werkzeug->currentItem()->text();
        int length = tmp.length();
        tmp = tmp.right(length-2);
        ui->listWidget_Werkzeug->currentItem()->setText(tmp);
    }
    vorschauAktualisieren();
}

void MainWindow::elementAusblenden()
{
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        uint i = ui->listWidget_Programmliste->currentRow()+1;
        QString tmp_t = tt.get_prgtext()->zeile(i);
        tmp_t = "//" + tmp_t;
        tt.get_prgtext()->zeile_ersaetzen(i, tmp_t);

        QString tmp = ui->listWidget_Programmliste->currentItem()->text();
        QString newText = "//";
        newText += tmp;
        ui->listWidget_Programmliste->currentItem()->setText(newText);
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {
        uint i = ui->listWidget_Werkzeug->currentRow()+1;
        QString tmp_t = wkz.zeile(i);
        tmp_t = "//" + tmp_t;
        wkz.zeile_ersaetzen(i, tmp_t);

        QString tmp = ui->listWidget_Werkzeug->currentItem()->text();
        QString newText = "//";
        newText += tmp;
        ui->listWidget_Werkzeug->currentItem()->setText(newText);
    }
    vorschauAktualisieren();
}

void MainWindow::elementEinblendenSichtbarMachen()
{
    QColor farbe(0,0,0);//schwarz
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        ui->listWidget_Programmliste->currentItem()->setForeground(QBrush(farbe));
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {
        ui->listWidget_Werkzeug->currentItem()->setForeground(QBrush(farbe));
    }
}

void MainWindow::elementEinblendenSichtbarMachen(QListWidgetItem *item)
{
    QColor farbe(0,0,0);//schwarz
    item->setForeground(QBrush(farbe));
}

void MainWindow::elementAusblendenSichtbarMachen()
{
    QColor farbe(180,205,205);//grau
    if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        ui->listWidget_Programmliste->currentItem()->setForeground(QBrush(farbe));
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {
        ui->listWidget_Werkzeug->currentItem()->setForeground(QBrush(farbe));
    }
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
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {
        if((ui->listWidget_Werkzeug->currentIndex().isValid())  &&  \
                (ui->listWidget_Werkzeug->currentItem()->isSelected()))
        {
            QList<QListWidgetItem*> items = ui->listWidget_Werkzeug->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Werkzeug->count() ;i++)
            {
                if(ui->listWidget_Werkzeug->item(i)->isSelected())
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
                QString zeilentext =  wkz.zeile(i+1);
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
     }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
     {
         if((ui->listWidget_Werkzeug->currentIndex().isValid())  &&  \
                 (ui->listWidget_Werkzeug->currentItem()->isSelected()))
         {
             QList<QListWidgetItem*> items = ui->listWidget_Werkzeug->selectedItems();
             int items_menge = items.count();
             int row_erstes = 0;//Nummer des ersten Elementes
             for(int i=0; i<ui->listWidget_Werkzeug->count() ;i++)
             {
                 if(ui->listWidget_Werkzeug->item(i)->isSelected())
                 {
                     row_erstes = i;
                     break;
                 }
             }
             int row_letztes = row_erstes + items_menge-1;

             for(int i=row_erstes ; i<=row_letztes ; i++)
             {
                 QString zeilentext =wkz.zeile(i+1);
                 if(!elementIstEingeblendet(zeilentext))
                 {
                     int laenge = zeilentext.length();
                     zeilentext = zeilentext.right(laenge-2);
                     wkz.zeile_ersaetzen(i+1, zeilentext);
                     QColor farbe(180,205,205);//grau
                     ui->listWidget_Werkzeug->item(i)->setForeground(QBrush(farbe));
                 }
             }
             aktualisiere_anzeigetext_wkz();
             vorschauAktualisieren();
             for(int i=row_erstes ; i<=row_letztes ; i++)
             {
                 ui->listWidget_Werkzeug->item(i)->setSelected(true);
             }
         } else
         {
             QMessageBox mb;
             mb.setText("Sie haben noch nichts ausgewaelt was ausgeblendet werden kann!");
             mb.exec();
         }
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
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {
        if((ui->listWidget_Werkzeug->currentIndex().isValid())  &&  \
                (ui->listWidget_Werkzeug->currentItem()->isSelected()))
        {
            QList<QListWidgetItem*> items = ui->listWidget_Werkzeug->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Werkzeug->count() ;i++)
            {
                if(ui->listWidget_Werkzeug->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }
            int row_letztes = row_erstes + items_menge-1;

            for(int i=row_erstes ; i<=row_letztes ; i++)
            {
                QString zeilentext =wkz.zeile(i+1);
                if(elementIstEingeblendet(zeilentext))
                {
                    wkz.zeile_ersaetzen(i+1,"//"+zeilentext);
                    QColor farbe(180,205,205);//grau
                    ui->listWidget_Werkzeug->item(i)->setForeground(QBrush(farbe));
                }
            }
            aktualisiere_anzeigetext_wkz();
            vorschauAktualisieren();
            for(int i=row_erstes ; i<=row_letztes ; i++)
            {
                ui->listWidget_Werkzeug->item(i)->setSelected(true);
            }
        } else
        {
            QMessageBox mb;
            mb.setText("Sie haben noch nichts ausgewaelt was ausgeblendet werden kann!");
            mb.exec();
        }
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
    t.set_wkz(wkz);
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
        QStringList pfade = QFileDialog::getOpenFileNames(this, tr("Waehle WOP-Datei"), \
                                                    pfad_oefne_fmc, tr("fmc Dateien (*.fmc)"));
        text_zeilenweise tz;
        tz.set_text(pfade);
        for(uint i=1; i<=tz.zeilenanzahl();i++)
        {
            openFile(tz.zeile(i));
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
            QString quelle = QString::fromLatin1(file.readAll());
            programmtext t;
            bool readonly;
            t.set_text(import_fmc(quelle, readonly, pfad).get_text());
            t.nurlesend(readonly);
            t.aktualisieren_fkon_ein_aus(tt.get_aktualisieren_fkon_ein_aus());
            undo_redo tmpur;
            tmpur.set_groesse_max(settings_anz_undo_t.toInt());
            t.set_wkz(wkz);
            tt.add(t, pfad, tmpur);
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
    prgpfade pf;
    QFile inifile(pf.get_path_iniLetzteDateien());
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

text_zeilenweise MainWindow::import_fmc(QString quelle, bool &readonly, QString prgname)
{
    readonly = false;
    text_zeilenweise tz;
    tz.set_text(quelle);
    text_zeilenweise retz;
    bool msg_unbekannte_dlg = false;
    for(uint i=1; i<= tz.zeilenanzahl();i++)
    {
        QString zeile = tz.zeile(i);
        zeile.replace("'",".");

        if(zeile.contains(DLG_PKOPF))
        {
            QString prgzeile;
            prgzeile  = DLG_PKOPF;
            prgzeile += vorlage_pkopf;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(PKOPF_KOM1))
                {
                    prgzeile = replaceparam(PKOPF_KOM1, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_KOM2))
                {
                    prgzeile = replaceparam(PKOPF_KOM2, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_L))
                {
                    prgzeile = replaceparam(PKOPF_L, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_B))
                {
                    prgzeile = replaceparam(PKOPF_B, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_D))
                {
                    prgzeile = replaceparam(PKOPF_D, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_FUENFSEI))
                {
                    prgzeile = replaceparam(PKOPF_FUENFSEI, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_SPEIGELN))
                {
                    prgzeile = replaceparam(PKOPF_SPEIGELN, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_BELEGART))
                {
                    prgzeile = replaceparam(PKOPF_BELEGART, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_XVERS))
                {
                    prgzeile = replaceparam(PKOPF_XVERS, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_YVERS))
                {
                    prgzeile = replaceparam(PKOPF_YVERS, prgzeile, zeile);
                }else if (zeile.contains(PKOFP_RTL))
                {
                    prgzeile = replaceparam(PKOFP_RTL, prgzeile, zeile);
                }else if (zeile.contains(PKOFP_RTB))
                {
                    prgzeile = replaceparam(PKOFP_RTB, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_LOESEN))
                {
                    prgzeile = replaceparam(PKOPF_LOESEN, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_SCHABH))
                {
                    prgzeile = replaceparam(PKOPF_SCHABH, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_SIABST))
                {
                    prgzeile = replaceparam(PKOPF_SIABST, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_PAPO))
                {
                    prgzeile = replaceparam(PKOPF_PAPO, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_BEZ))
                {
                    prgzeile = replaceparam(PKOPF_BEZ, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_AFB))
                {
                    prgzeile = replaceparam(PKOPF_AFB, prgzeile, zeile);
                }else if (zeile.contains(PKOPF_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_PENDE))
        {
            QString prgzeile;
            prgzeile  = DLG_PENDE;
            prgzeile += vorlage_pende;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(PENDE_PAPO))
                {
                    prgzeile = replaceparam(PENDE_PAPO, prgzeile, zeile);
                }else if (zeile.contains(PENDE_BEZ))
                {
                    prgzeile = replaceparam(PENDE_BEZ, prgzeile, zeile);
                }else if (zeile.contains(PENDE_AFB))
                {
                   prgzeile = replaceparam(PENDE_AFB, prgzeile, zeile);
                }else if (zeile.contains(PENDE_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_KOM))
        {
            QString prgzeile;
            prgzeile  = DLG_KOM;
            prgzeile += vorlage_kom;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if (zeile.contains(KOM_BEZ))
                {
                    prgzeile = replaceparam(KOM_BEZ, prgzeile, zeile);
                }else if (zeile.contains(KOM_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_HALT))
        {
            QString prgzeile;
            prgzeile  = DLG_HALT;
            prgzeile += vorlage_halt;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(HALT_X))
                {
                    prgzeile = replaceparam(HALT_X, prgzeile, zeile);
                }else if(zeile.contains(HALT_Y))
                {
                    prgzeile = replaceparam(HALT_Y, prgzeile, zeile);
                }else if (zeile.contains(HALT_BEZ))
                {
                    prgzeile = replaceparam(HALT_BEZ, prgzeile, zeile);
                }else if (zeile.contains(HALT_AFB))
                {
                   prgzeile = replaceparam(HALT_AFB, prgzeile, zeile);
                }else if (zeile.contains(HALT_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_BO))
        {
            QString prgzeile;
            prgzeile  = DLG_BO;
            prgzeile += vorlage_bo;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(BO_X))
                {
                    prgzeile = replaceparam(BO_X, prgzeile, zeile);
                }else if(zeile.contains(BO_Y))
                {
                    prgzeile = replaceparam(BO_Y, prgzeile, zeile);
                }else if(zeile.contains(BO_BOTI))
                {
                    prgzeile = replaceparam(BO_BOTI, prgzeile, zeile);
                }else if(zeile.contains(BO_DM))
                {
                    prgzeile = replaceparam(BO_DM, prgzeile, zeile);
                }else if(zeile.contains(BO_GRUPPE))
                {
                    prgzeile = replaceparam(BO_GRUPPE, prgzeile, zeile);
                }else if(zeile.contains(BO_ANBOTI))
                {
                    prgzeile = replaceparam(BO_ANBOTI, prgzeile, zeile);
                }else if(zeile.contains(BO_ANBOVO))
                {
                    prgzeile = replaceparam(BO_ANBOVO, prgzeile, zeile);
                }else if(zeile.contains(BO_REBOMA))
                {
                    prgzeile = replaceparam(BO_REBOMA, prgzeile, zeile);
                }else if(zeile.contains(BO_BOVO))
                {
                    prgzeile = replaceparam(BO_BOVO, prgzeile, zeile);
                }else if(zeile.contains(BO_ZSM))
                {
                    prgzeile = replaceparam(BO_ZSM, prgzeile, zeile);
                }else if(zeile.contains(BO_DREHZ))
                {
                    prgzeile = replaceparam(BO_DREHZ, prgzeile, zeile);
                }else if(zeile.contains(BO_MESSEI))
                {
                    prgzeile = replaceparam(BO_MESSEI, prgzeile, zeile);
                }else if(zeile.contains(BO_TASATZ))
                {
                    prgzeile = replaceparam(BO_TASATZ, prgzeile, zeile);
                }else if(zeile.contains(BO_PLM))
                {
                    prgzeile = replaceparam(BO_PLM, prgzeile, zeile);
                }else if (zeile.contains(BO_BEZ))
                {
                    prgzeile = replaceparam(BO_BEZ, prgzeile, zeile);
                }else if (zeile.contains(BO_AFB))
                {
                   prgzeile = replaceparam(BO_AFB, prgzeile, zeile);
                }else if (zeile.contains(BO_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_BOY))
        {
            QString prgzeile;
            prgzeile  = DLG_BOY;
            prgzeile += vorlage_boy;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(BOY_X))
                {
                    prgzeile = replaceparam(BOY_X, prgzeile, zeile);
                }else if(zeile.contains(BOY_X2))
                {
                    prgzeile = replaceparam(BOY_X2, prgzeile, zeile);
                }else if(zeile.contains(BOY_Y1))
                {
                    prgzeile = replaceparam(BOY_Y1, prgzeile, zeile);
                }else if(zeile.contains(BOY_Y2))
                {
                    prgzeile = replaceparam(BOY_Y2, prgzeile, zeile);
                }else if(zeile.contains(BOY_Y3))
                {
                    prgzeile = replaceparam(BOY_Y3, prgzeile, zeile);
                }else if(zeile.contains(BOY_Y4))
                {
                    prgzeile = replaceparam(BOY_Y4, prgzeile, zeile);
                }else if(zeile.contains(BOY_Y5))
                {
                    prgzeile = replaceparam(BOY_Y5, prgzeile, zeile);
                }else if(zeile.contains(BOY_Y6))
                {
                    prgzeile = replaceparam(BOY_Y6, prgzeile, zeile);
                }else if(zeile.contains(BOY_BOTI))
                {
                    prgzeile = replaceparam(BOY_BOTI, prgzeile, zeile);
                }else if(zeile.contains(BOY_DM))
                {
                    prgzeile = replaceparam(BOY_DM, prgzeile, zeile);
                }else if(zeile.contains(BOY_KETTE))
                {
                    prgzeile = replaceparam(BOY_KETTE, prgzeile, zeile);
                }else if(zeile.contains(BOY_GRUPPE))
                {
                    prgzeile = replaceparam(BOY_GRUPPE, prgzeile, zeile);
                }else if(zeile.contains(BOY_ANBOTI))
                {
                    prgzeile = replaceparam(BOY_ANBOTI, prgzeile, zeile);
                }else if(zeile.contains(BOY_ANBOVO))
                {
                    prgzeile = replaceparam(BOY_ANBOVO, prgzeile, zeile);
                }else if(zeile.contains(BOY_REBOMA))
                {
                    prgzeile = replaceparam(BOY_REBOMA, prgzeile, zeile);
                }else if(zeile.contains(BOY_BOVO))
                {
                    prgzeile = replaceparam(BOY_BOVO, prgzeile, zeile);
                }else if(zeile.contains(BOY_ZSM))
                {
                    prgzeile = replaceparam(BOY_ZSM, prgzeile, zeile);
                }else if(zeile.contains(BOY_DREHZ))
                {
                    prgzeile = replaceparam(BOY_DREHZ, prgzeile, zeile);
                }else if(zeile.contains(BOY_MESSEI))
                {
                    prgzeile = replaceparam(BOY_MESSEI, prgzeile, zeile);
                }else if(zeile.contains(BOY_TASATZ))
                {
                    prgzeile = replaceparam(BOY_TASATZ, prgzeile, zeile);
                }else if(zeile.contains(BOY_PLM))
                {
                    prgzeile = replaceparam(BOY_PLM, prgzeile, zeile);
                }else if (zeile.contains(BOY_BEZ))
                {
                    prgzeile = replaceparam(BOY_BEZ, prgzeile, zeile);
                }else if (zeile.contains(BOY_AFB))
                {
                   prgzeile = replaceparam(BOY_AFB, prgzeile, zeile);
                }else if (zeile.contains(BOY_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_BOX))
        {
            QString prgzeile;
            prgzeile  = DLG_BOX;
            prgzeile += vorlage_box;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(BOX_Y))
                {
                    prgzeile = replaceparam(BOX_Y, prgzeile, zeile);
                }else if(zeile.contains(BOX_Y2))
                {
                    prgzeile = replaceparam(BOX_Y2, prgzeile, zeile);
                }else if(zeile.contains(BOX_X1))
                {
                    prgzeile = replaceparam(BOX_X1, prgzeile, zeile);
                }else if(zeile.contains(BOX_X2))
                {
                    prgzeile = replaceparam(BOX_X2, prgzeile, zeile);
                }else if(zeile.contains(BOX_X3))
                {
                    prgzeile = replaceparam(BOX_X3, prgzeile, zeile);
                }else if(zeile.contains(BOX_X4))
                {
                    prgzeile = replaceparam(BOX_X4, prgzeile, zeile);
                }else if(zeile.contains(BOX_X5))
                {
                    prgzeile = replaceparam(BOX_X5, prgzeile, zeile);
                }else if(zeile.contains(BOX_X6))
                {
                    prgzeile = replaceparam(BOX_X6, prgzeile, zeile);
                }else if(zeile.contains(BOX_BOTI))
                {
                    prgzeile = replaceparam(BOX_BOTI, prgzeile, zeile);
                }else if(zeile.contains(BOX_DM))
                {
                    prgzeile = replaceparam(BOX_DM, prgzeile, zeile);
                }else if(zeile.contains(BOX_KETTE))
                {
                    prgzeile = replaceparam(BOX_KETTE, prgzeile, zeile);
                }else if(zeile.contains(BOX_GRUPPE))
                {
                    prgzeile = replaceparam(BOX_GRUPPE, prgzeile, zeile);
                }else if(zeile.contains(BOX_ANBOTI))
                {
                    prgzeile = replaceparam(BOX_ANBOTI, prgzeile, zeile);
                }else if(zeile.contains(BOX_ANBOVO))
                {
                    prgzeile = replaceparam(BOX_ANBOVO, prgzeile, zeile);
                }else if(zeile.contains(BOX_REBOMA))
                {
                    prgzeile = replaceparam(BOX_REBOMA, prgzeile, zeile);
                }else if(zeile.contains(BOX_BOVO))
                {
                    prgzeile = replaceparam(BOX_BOVO, prgzeile, zeile);
                }else if(zeile.contains(BOX_ZSM))
                {
                    prgzeile = replaceparam(BOX_ZSM, prgzeile, zeile);
                }else if(zeile.contains(BOX_DREHZ))
                {
                    prgzeile = replaceparam(BOX_DREHZ, prgzeile, zeile);
                }else if(zeile.contains(BOX_MESSEI))
                {
                    prgzeile = replaceparam(BOX_MESSEI, prgzeile, zeile);
                }else if(zeile.contains(BOX_TASATZ))
                {
                    prgzeile = replaceparam(BOX_TASATZ, prgzeile, zeile);
                }else if(zeile.contains(BOX_PLM))
                {
                    prgzeile = replaceparam(BOX_PLM, prgzeile, zeile);
                }else if (zeile.contains(BOX_BEZ))
                {
                    prgzeile = replaceparam(BOX_BEZ, prgzeile, zeile);
                }else if (zeile.contains(BOX_AFB))
                {
                   prgzeile = replaceparam(BOX_AFB, prgzeile, zeile);
                }else if (zeile.contains(BOX_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_LOREIAE))
        {
            QString prgzeile;
            prgzeile  = DLG_LOREIAE;
            prgzeile += vorlage_loreiae;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(LOREIAE_XS))
                {
                    prgzeile = replaceparam(LOREIAE_XS, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_XE))
                {
                    prgzeile = replaceparam(LOREIAE_XE, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_Y1))
                {
                    prgzeile = replaceparam(LOREIAE_Y1, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_Y2))
                {
                    prgzeile = replaceparam(LOREIAE_Y2, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_YE))
                {
                    prgzeile = replaceparam(LOREIAE_YE, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_RASTER))
                {
                    prgzeile = replaceparam(LOREIAE_RASTER, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_BOTI))
                {
                    prgzeile = replaceparam(LOREIAE_BOTI, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_DM))
                {
                    prgzeile = replaceparam(LOREIAE_DM, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_GRUPPE))
                {
                    prgzeile = replaceparam(LOREIAE_GRUPPE, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_VERMIT))
                {
                    prgzeile = replaceparam(LOREIAE_VERMIT, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_ANBOTI))
                {
                    prgzeile = replaceparam(LOREIAE_ANBOTI, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_ANBOVO))
                {
                    prgzeile = replaceparam(LOREIAE_ANBOVO, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_REBOMA))
                {
                    prgzeile = replaceparam(LOREIAE_REBOMA, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_BOVO))
                {
                    prgzeile = replaceparam(LOREIAE_BOVO, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_ZSM))
                {
                    prgzeile = replaceparam(LOREIAE_ZSM, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_DREHZ))
                {
                    prgzeile = replaceparam(LOREIAE_DREHZ, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_MESSEI))
                {
                    prgzeile = replaceparam(LOREIAE_MESSEI, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_TASATZ))
                {
                    prgzeile = replaceparam(LOREIAE_TASATZ, prgzeile, zeile);
                }else if(zeile.contains(LOREIAE_PLM))
                {
                    prgzeile = replaceparam(LOREIAE_PLM, prgzeile, zeile);
                }else if (zeile.contains(LOREIAE_BEZ))
                {
                    prgzeile = replaceparam(LOREIAE_BEZ, prgzeile, zeile);
                }else if (zeile.contains(LOREIAE_AFB))
                {
                   prgzeile = replaceparam(LOREIAE_AFB, prgzeile, zeile);
                }else if (zeile.contains(LOREIAE_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_LOREIMA))
        {
            QString prgzeile;
            prgzeile  = DLG_LOREIMA;
            prgzeile += vorlage_loreima;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(LOREIMA_XS))
                {
                    prgzeile = replaceparam(LOREIMA_XS, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_XM))
                {
                    prgzeile = replaceparam(LOREIMA_XM, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_Y1))
                {
                    prgzeile = replaceparam(LOREIMA_Y1, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_Y2))
                {
                    prgzeile = replaceparam(LOREIMA_Y2, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_RASTER))
                {
                    prgzeile = replaceparam(LOREIMA_RASTER, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_BOTI))
                {
                    prgzeile = replaceparam(LOREIMA_BOTI, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_DM))
                {
                    prgzeile = replaceparam(LOREIMA_DM, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_GRUPPE))
                {
                    prgzeile = replaceparam(LOREIMA_GRUPPE, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_ANBOTI))
                {
                    prgzeile = replaceparam(LOREIMA_ANBOTI, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_ANBOVO))
                {
                    prgzeile = replaceparam(LOREIMA_ANBOVO, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_REBOMA))
                {
                    prgzeile = replaceparam(LOREIMA_REBOMA, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_BOVO))
                {
                    prgzeile = replaceparam(LOREIMA_BOVO, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_ZSM))
                {
                    prgzeile = replaceparam(LOREIMA_ZSM, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_DREHZ))
                {
                    prgzeile = replaceparam(LOREIMA_DREHZ, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_MESSEI))
                {
                    prgzeile = replaceparam(LOREIMA_MESSEI, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_TASATZ))
                {
                    prgzeile = replaceparam(LOREIMA_TASATZ, prgzeile, zeile);
                }else if(zeile.contains(LOREIMA_PLM))
                {
                    prgzeile = replaceparam(LOREIMA_PLM, prgzeile, zeile);
                }else if (zeile.contains(LOREIMA_BEZ))
                {
                    prgzeile = replaceparam(LOREIMA_BEZ, prgzeile, zeile);
                }else if (zeile.contains(LOREIMA_AFB))
                {
                   prgzeile = replaceparam(LOREIMA_AFB, prgzeile, zeile);
                }else if (zeile.contains(LOREIMA_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_TOPF))
        {
            QString prgzeile;
            prgzeile  = DLG_TOPF;
            prgzeile += vorlage_topf;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(TOPF_TA))
                {
                    prgzeile = replaceparam(TOPF_TA, prgzeile, zeile);
                }else if(zeile.contains(TOPF_A1))
                {
                    prgzeile = replaceparam(TOPF_A1, prgzeile, zeile);
                }else if(zeile.contains(TOPF_A2))
                {
                    prgzeile = replaceparam(TOPF_A2, prgzeile, zeile);
                }else if(zeile.contains(TOPF_A3))
                {
                    prgzeile = replaceparam(TOPF_A3, prgzeile, zeile);
                }else if(zeile.contains(TOPF_A4))
                {
                    prgzeile = replaceparam(TOPF_A4, prgzeile, zeile);
                }else if(zeile.contains(TOPF_A5))
                {
                    prgzeile = replaceparam(TOPF_A5, prgzeile, zeile);
                }else if(zeile.contains(TOPF_MA))
                {
                    prgzeile = replaceparam(TOPF_MA, prgzeile, zeile);
                }else if(zeile.contains(TOPF_MB))
                {
                    prgzeile = replaceparam(TOPF_MB, prgzeile, zeile);
                }else if(zeile.contains(TOPF_KETTE))
                {
                    prgzeile = replaceparam(TOPF_KETTE, prgzeile, zeile);
                }else if(zeile.contains(TOPF_GRUPPE))
                {
                    prgzeile = replaceparam(TOPF_GRUPPE, prgzeile, zeile);
                }else if(zeile.contains(TOPF_SEITE))
                {
                    prgzeile = replaceparam(TOPF_SEITE, prgzeile, zeile);
                }else if(zeile.contains(TOPF_MESSEI))
                {
                    prgzeile = replaceparam(TOPF_MESSEI, prgzeile, zeile);
                }else if(zeile.contains(TOPF_BODM))
                {
                    prgzeile = replaceparam(TOPF_BODM, prgzeile, zeile);
                }else if(zeile.contains(TOPF_TODM))
                {
                    prgzeile = replaceparam(TOPF_TODM, prgzeile, zeile);
                }else if(zeile.contains(TOPF_BOTI))
                {
                    prgzeile = replaceparam(TOPF_BOTI, prgzeile, zeile);
                }else if(zeile.contains(TOPF_WKZ))
                {
                    prgzeile = replaceparam(TOPF_WKZ, prgzeile, zeile);
                }else if(zeile.contains(TOPF_TOTI))
                {
                    prgzeile = replaceparam(TOPF_TOTI, prgzeile, zeile);
                }else if(zeile.contains(TOPF_ANBOTI))
                {
                    prgzeile = replaceparam(TOPF_ANBOTI, prgzeile, zeile);
                }else if(zeile.contains(TOPF_BOANBOVO))
                {
                    prgzeile = replaceparam(TOPF_BOANBOVO, prgzeile, zeile);
                }else if(zeile.contains(TOPF_TOANBOVO))
                {
                    prgzeile = replaceparam(TOPF_TOANBOVO, prgzeile, zeile);
                }else if(zeile.contains(TOPF_REBOMA))
                {
                    prgzeile = replaceparam(TOPF_REBOMA, prgzeile, zeile);
                }else if(zeile.contains(TOPF_BOBOVO))
                {
                    prgzeile = replaceparam(TOPF_BOBOVO, prgzeile, zeile);
                }else if(zeile.contains(TOPF_TOBOVO))
                {
                    prgzeile = replaceparam(TOPF_TOBOVO, prgzeile, zeile);
                }else if(zeile.contains(TOPF_BOZSM))
                {
                    prgzeile = replaceparam(TOPF_BOZSM, prgzeile, zeile);
                }else if(zeile.contains(TOPF_DREHZ))
                {
                    prgzeile = replaceparam(TOPF_DREHZ, prgzeile, zeile);
                }else if(zeile.contains(TOPF_PLM))
                {
                    prgzeile = replaceparam(TOPF_PLM, prgzeile, zeile);
                }else if (zeile.contains(TOPF_BEZ))
                {
                    prgzeile = replaceparam(TOPF_BEZ, prgzeile, zeile);
                }else if (zeile.contains(TOPF_AFB))
                {
                   prgzeile = replaceparam(TOPF_AFB, prgzeile, zeile);
                }else if (zeile.contains(TOPF_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_HBEXP))
        {
            QString prgzeile;
            prgzeile  = DLG_HBEXP;
            prgzeile += vorlage_hbexp;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(HBEXP_Y1))
                {
                    prgzeile = replaceparam(HBEXP_Y1, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_Y2))
                {
                    prgzeile = replaceparam(HBEXP_Y2, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_Y3))
                {
                    prgzeile = replaceparam(HBEXP_Y3, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_Y4))
                {
                    prgzeile = replaceparam(HBEXP_Y4, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_Y5))
                {
                    prgzeile = replaceparam(HBEXP_Y5, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_Y6))
                {
                    prgzeile = replaceparam(HBEXP_Y6, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_BOTI))
                {
                    prgzeile = replaceparam(HBEXP_BOTI, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_Z))
                {
                    prgzeile = replaceparam(HBEXP_Z, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_DM))
                {
                    prgzeile = replaceparam(HBEXP_DM, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_KETTE))
                {
                    prgzeile = replaceparam(HBEXP_KETTE, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_GRUPPE))
                {
                    prgzeile = replaceparam(HBEXP_GRUPPE, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_X2))
                {
                    prgzeile = replaceparam(HBEXP_X2, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_X1))
                {
                    prgzeile = replaceparam(HBEXP_X1, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_ANBOTI))
                {
                    prgzeile = replaceparam(HBEXP_ANBOTI, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_ANBOVO))
                {
                    prgzeile = replaceparam(HBEXP_ANBOVO, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_BOVO))
                {
                    prgzeile = replaceparam(HBEXP_BOVO, prgzeile, zeile);
                }else if(zeile.contains(HBEXP_DREHZ))
                {
                    prgzeile = replaceparam(HBEXP_DREHZ, prgzeile, zeile);
                }else if (zeile.contains(HBEXP_BEZ))
                {
                    prgzeile = replaceparam(HBEXP_BEZ, prgzeile, zeile);
                }else if (zeile.contains(HBEXP_AFB))
                {
                   prgzeile = replaceparam(HBEXP_AFB, prgzeile, zeile);
                }else if (zeile.contains(HBEXP_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_HBEXM))
        {
            QString prgzeile;
            prgzeile  = DLG_HBEXM;
            prgzeile += vorlage_hbexm;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(HBEXM_Y1))
                {
                    prgzeile = replaceparam(HBEXM_Y1, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_Y2))
                {
                    prgzeile = replaceparam(HBEXM_Y2, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_Y3))
                {
                    prgzeile = replaceparam(HBEXM_Y3, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_Y4))
                {
                    prgzeile = replaceparam(HBEXM_Y4, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_Y5))
                {
                    prgzeile = replaceparam(HBEXM_Y5, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_Y6))
                {
                    prgzeile = replaceparam(HBEXM_Y6, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_BOTI))
                {
                    prgzeile = replaceparam(HBEXM_BOTI, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_Z))
                {
                    prgzeile = replaceparam(HBEXM_Z, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_DM))
                {
                    prgzeile = replaceparam(HBEXM_DM, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_KETTE))
                {
                    prgzeile = replaceparam(HBEXM_KETTE, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_GRUPPE))
                {
                    prgzeile = replaceparam(HBEXM_GRUPPE, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_X2))
                {
                    prgzeile = replaceparam(HBEXM_X2, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_X1))
                {
                    prgzeile = replaceparam(HBEXM_X1, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_ANBOTI))
                {
                    prgzeile = replaceparam(HBEXM_ANBOTI, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_ANBOVO))
                {
                    prgzeile = replaceparam(HBEXM_ANBOVO, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_BOVO))
                {
                    prgzeile = replaceparam(HBEXM_BOVO, prgzeile, zeile);
                }else if(zeile.contains(HBEXM_DREHZ))
                {
                    prgzeile = replaceparam(HBEXM_DREHZ, prgzeile, zeile);
                }else if (zeile.contains(HBEXM_BEZ))
                {
                    prgzeile = replaceparam(HBEXM_BEZ, prgzeile, zeile);
                }else if (zeile.contains(HBEXM_AFB))
                {
                   prgzeile = replaceparam(HBEXM_AFB, prgzeile, zeile);
                }else if (zeile.contains(HBEXM_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_HBEYP))
        {
            QString prgzeile;
            prgzeile  = DLG_HBEYP;
            prgzeile += vorlage_hbeyp;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(HBEYP_X1))
                {
                    prgzeile = replaceparam(HBEYP_X1, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_X2))
                {
                    prgzeile = replaceparam(HBEYP_X2, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_X3))
                {
                    prgzeile = replaceparam(HBEYP_X3, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_X4))
                {
                    prgzeile = replaceparam(HBEYP_X4, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_X5))
                {
                    prgzeile = replaceparam(HBEYP_X5, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_X6))
                {
                    prgzeile = replaceparam(HBEYP_X6, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_BOTI))
                {
                    prgzeile = replaceparam(HBEYP_BOTI, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_Z))
                {
                    prgzeile = replaceparam(HBEYP_Z, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_DM))
                {
                    prgzeile = replaceparam(HBEYP_DM, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_KETTE))
                {
                    prgzeile = replaceparam(HBEYP_KETTE, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_GRUPPE))
                {
                    prgzeile = replaceparam(HBEYP_GRUPPE, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_Y2))
                {
                    prgzeile = replaceparam(HBEYP_Y2, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_Y1))
                {
                    prgzeile = replaceparam(HBEYP_Y1, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_ANBOTI))
                {
                    prgzeile = replaceparam(HBEYP_ANBOTI, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_ANBOVO))
                {
                    prgzeile = replaceparam(HBEYP_ANBOVO, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_BOVO))
                {
                    prgzeile = replaceparam(HBEYP_BOVO, prgzeile, zeile);
                }else if(zeile.contains(HBEYP_DREHZ))
                {
                    prgzeile = replaceparam(HBEYP_DREHZ, prgzeile, zeile);
                }else if (zeile.contains(HBEYP_BEZ))
                {
                    prgzeile = replaceparam(HBEYP_BEZ, prgzeile, zeile);
                }else if (zeile.contains(HBEYP_AFB))
                {
                   prgzeile = replaceparam(HBEYP_AFB, prgzeile, zeile);
                }else if (zeile.contains(HBEYP_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_HBEYM))
        {
            QString prgzeile;
            prgzeile  = DLG_HBEYM;
            prgzeile += vorlage_hbeym;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(HBEYM_X1))
                {
                    prgzeile = replaceparam(HBEYM_X1, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_X2))
                {
                    prgzeile = replaceparam(HBEYM_X2, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_X3))
                {
                    prgzeile = replaceparam(HBEYM_X3, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_X4))
                {
                    prgzeile = replaceparam(HBEYM_X4, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_X5))
                {
                    prgzeile = replaceparam(HBEYM_X5, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_X6))
                {
                    prgzeile = replaceparam(HBEYM_X6, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_BOTI))
                {
                    prgzeile = replaceparam(HBEYM_BOTI, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_Z))
                {
                    prgzeile = replaceparam(HBEYM_Z, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_DM))
                {
                    prgzeile = replaceparam(HBEYM_DM, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_KETTE))
                {
                    prgzeile = replaceparam(HBEYM_KETTE, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_GRUPPE))
                {
                    prgzeile = replaceparam(HBEYM_GRUPPE, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_Y2))
                {
                    prgzeile = replaceparam(HBEYM_Y2, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_Y1))
                {
                    prgzeile = replaceparam(HBEYM_Y1, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_ANBOTI))
                {
                    prgzeile = replaceparam(HBEYM_ANBOTI, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_ANBOVO))
                {
                    prgzeile = replaceparam(HBEYM_ANBOVO, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_BOVO))
                {
                    prgzeile = replaceparam(HBEYM_BOVO, prgzeile, zeile);
                }else if(zeile.contains(HBEYM_DREHZ))
                {
                    prgzeile = replaceparam(HBEYM_DREHZ, prgzeile, zeile);
                }else if (zeile.contains(HBEYM_BEZ))
                {
                    prgzeile = replaceparam(HBEYM_BEZ, prgzeile, zeile);
                }else if (zeile.contains(HBEYM_AFB))
                {
                   prgzeile = replaceparam(HBEYM_AFB, prgzeile, zeile);
                }else if (zeile.contains(HBEYM_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_NUT))
        {
            QString prgzeile;
            prgzeile  = DLG_NUT;
            prgzeile += vorlage_nut;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(NUT_WKZ))
                {
                    prgzeile = replaceparam(NUT_WKZ, prgzeile, zeile);
                }else if(zeile.contains(NUT_SX))
                {
                    prgzeile = replaceparam(NUT_SX, prgzeile, zeile);
                }else if(zeile.contains(NUT_SY))
                {
                    prgzeile = replaceparam(NUT_SY, prgzeile, zeile);
                }else if(zeile.contains(NUT_EX))
                {
                    prgzeile = replaceparam(NUT_EX, prgzeile, zeile);
                }else if(zeile.contains(NUT_EY))
                {
                    prgzeile = replaceparam(NUT_EY, prgzeile, zeile);
                }else if(zeile.contains(NUT_TI))
                {
                    prgzeile = replaceparam(NUT_TI, prgzeile, zeile);
                }else if(zeile.contains(NUT_B))
                {
                    prgzeile = replaceparam(NUT_B, prgzeile, zeile);
                }else if(zeile.contains(NUT_AUSLAUF))
                {
                    prgzeile = replaceparam(NUT_AUSLAUF, prgzeile, zeile);
                }else if(zeile.contains(NUT_KOR))
                {
                    prgzeile = replaceparam(NUT_KOR, prgzeile, zeile);
                }else if(zeile.contains(NUT_GEGENLAUF))
                {
                    prgzeile = replaceparam(NUT_GEGENLAUF, prgzeile, zeile);
                }else if(zeile.contains(NUT_NWI))
                {
                    prgzeile = replaceparam(NUT_NWI, prgzeile, zeile);
                }else if(zeile.contains(NUT_NTYP))
                {
                    prgzeile = replaceparam(NUT_NTYP, prgzeile, zeile);
                }else if(zeile.contains(NUT_NABST))
                {
                    prgzeile = replaceparam(NUT_NABST, prgzeile, zeile);
                }else if(zeile.contains(NUT_Z))
                {
                    prgzeile = replaceparam(NUT_Z, prgzeile, zeile);
                }else if(zeile.contains(NUT_EINVO))
                {
                    prgzeile = replaceparam(NUT_EINVO, prgzeile, zeile);
                }else if(zeile.contains(NUT_VO))
                {
                    prgzeile = replaceparam(NUT_VO, prgzeile, zeile);
                }else if(zeile.contains(NUT_DREHZ))
                {
                    prgzeile = replaceparam(NUT_DREHZ, prgzeile, zeile);
                }else if(zeile.contains(NUT_PLM))
                {
                    prgzeile = replaceparam(NUT_PLM, prgzeile, zeile);
                }else if(zeile.contains(NUT_WKZAKT))
                {
                    prgzeile = replaceparam(NUT_WKZAKT, prgzeile, zeile);
                }else if(zeile.contains(NUT_BEZ))
                {
                    prgzeile = replaceparam(NUT_BEZ, prgzeile, zeile);
                }else if(zeile.contains(NUT_AFB))
                {
                    prgzeile = replaceparam(NUT_AFB, prgzeile, zeile);
                }else if (zeile.contains(NUT_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_KTA))
        {
            QString prgzeile;
            prgzeile  = DLG_KTA;
            prgzeile += vorlage_kta;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(KTA_WKZ))
                {
                    prgzeile = replaceparam(KTA_WKZ, prgzeile, zeile);
                }else if(zeile.contains(KTA_X))
                {
                    prgzeile = replaceparam(KTA_X, prgzeile, zeile);
                }else if(zeile.contains(KTA_Y))
                {
                    prgzeile = replaceparam(KTA_Y, prgzeile, zeile);
                }else if(zeile.contains(KTA_DM))
                {
                    prgzeile = replaceparam(KTA_DM, prgzeile, zeile);
                }else if(zeile.contains(KTA_TI))
                {
                    prgzeile = replaceparam(KTA_TI, prgzeile, zeile);
                }else if(zeile.contains(KTA_ZUST))
                {
                    prgzeile = replaceparam(KTA_ZUST, prgzeile, zeile);
                }else if(zeile.contains(KTA_GEGENL))
                {
                    prgzeile = replaceparam(KTA_GEGENL, prgzeile, zeile);
                }else if(zeile.contains(KTA_AUSR))
                {
                    prgzeile = replaceparam(KTA_AUSR, prgzeile, zeile);
                }else if(zeile.contains(KTA_EINVO))
                {
                    prgzeile = replaceparam(KTA_EINVO, prgzeile, zeile);
                }else if(zeile.contains(KTA_VO))
                {
                    prgzeile = replaceparam(KTA_VO, prgzeile, zeile);
                }else if(zeile.contains(KTA_DREHZ))
                {
                    prgzeile = replaceparam(KTA_DREHZ, prgzeile, zeile);
                }else if(zeile.contains(KTA_PLM))
                {
                    prgzeile = replaceparam(KTA_PLM, prgzeile, zeile);
                }else if(zeile.contains(KTA_WKZAKT))
                {
                    prgzeile = replaceparam(KTA_WKZAKT, prgzeile, zeile);
                }else if(zeile.contains(KTA_BEZ))
                {
                    prgzeile = replaceparam(KTA_BEZ, prgzeile, zeile);
                }else if(zeile.contains(KTA_AFB))
                {
                    prgzeile = replaceparam(KTA_AFB, prgzeile, zeile);
                }else if (zeile.contains(KTA_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_RTA))
        {
            QString prgzeile;
            prgzeile  = DLG_RTA;
            prgzeile += vorlage_rta;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(RTA_WKZ))
                {
                    prgzeile = replaceparam(RTA_WKZ, prgzeile, zeile);
                }else if(zeile.contains(RTA_X))
                {
                    prgzeile = replaceparam(RTA_X, prgzeile, zeile);
                }else if(zeile.contains(RTA_Y))
                {
                    prgzeile = replaceparam(RTA_Y, prgzeile, zeile);
                }else if(zeile.contains(RTA_L))
                {
                    prgzeile = replaceparam(RTA_L, prgzeile, zeile);
                }else if(zeile.contains(RTA_B))
                {
                    prgzeile = replaceparam(RTA_B, prgzeile, zeile);
                }else if(zeile.contains(RTA_TI))
                {
                    prgzeile = replaceparam(RTA_TI, prgzeile, zeile);
                }else if(zeile.contains(RTA_RAD))
                {
                    prgzeile = replaceparam(RTA_RAD, prgzeile, zeile);
                }else if(zeile.contains(RTA_ZUST))
                {
                    prgzeile = replaceparam(RTA_ZUST, prgzeile, zeile);
                }else if(zeile.contains(RTA_GEGENL))
                {
                    prgzeile = replaceparam(RTA_GEGENL, prgzeile, zeile);
                }else if(zeile.contains(RTA_WI))
                {
                    prgzeile = replaceparam(RTA_WI, prgzeile, zeile);
                }else if(zeile.contains(RTA_AUSR))
                {
                    prgzeile = replaceparam(RTA_AUSR, prgzeile, zeile);
                }else if(zeile.contains(RTA_EINVO))
                {
                    prgzeile = replaceparam(RTA_EINVO, prgzeile, zeile);
                }else if(zeile.contains(RTA_VO))
                {
                    prgzeile = replaceparam(RTA_VO, prgzeile, zeile);
                }else if(zeile.contains(RTA_DREHZ))
                {
                    prgzeile = replaceparam(RTA_DREHZ, prgzeile, zeile);
                }else if(zeile.contains(RTA_PLM))
                {
                    prgzeile = replaceparam(RTA_PLM, prgzeile, zeile);
                }else if(zeile.contains(RTA_WKZAKT))
                {
                    prgzeile = replaceparam(RTA_WKZAKT, prgzeile, zeile);
                }else if(zeile.contains(RTA_BEZ))
                {
                    prgzeile = replaceparam(RTA_BEZ, prgzeile, zeile);
                }else if(zeile.contains(RTA_AFB))
                {
                    prgzeile = replaceparam(RTA_AFB, prgzeile, zeile);
                }else if (zeile.contains(RTA_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_VAR))
        {
            QString prgzeile;
            prgzeile  = DLG_VAR;
            prgzeile += vorlage_var;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(VAR_NAME))
                {
                    prgzeile = replaceparam(VAR_NAME, prgzeile, zeile);
                }else if(zeile.contains(VAR_WERT))
                {
                    prgzeile = replaceparam(VAR_WERT, prgzeile, zeile);
                }else if(zeile.contains(VAR_BEZ))
                {
                    prgzeile = replaceparam(VAR_BEZ, prgzeile, zeile);
                }else if(zeile.contains(VAR_AFB))
                {
                    prgzeile = replaceparam(VAR_AFB, prgzeile, zeile);
                }else if (zeile.contains(VAR_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_VAR10))
        {
            QString prgzeile;
            prgzeile  = DLG_VAR10;
            prgzeile += vorlage_var10;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(VAR10_NAME1))
                {
                    prgzeile = replaceparam(VAR10_NAME1, prgzeile, zeile);
                }else if(zeile.contains(VAR10_NAME2))
                {
                    prgzeile = replaceparam(VAR10_NAME2, prgzeile, zeile);
                }else if(zeile.contains(VAR10_NAME3))
                {
                    prgzeile = replaceparam(VAR10_NAME3, prgzeile, zeile);
                }else if(zeile.contains(VAR10_NAME4))
                {
                    prgzeile = replaceparam(VAR10_NAME4, prgzeile, zeile);
                }else if(zeile.contains(VAR10_NAME5))
                {
                    prgzeile = replaceparam(VAR10_NAME5, prgzeile, zeile);
                }else if(zeile.contains(VAR10_NAME6))
                {
                    prgzeile = replaceparam(VAR10_NAME6, prgzeile, zeile);
                }else if(zeile.contains(VAR10_NAME7))
                {
                    prgzeile = replaceparam(VAR10_NAME7, prgzeile, zeile);
                }else if(zeile.contains(VAR10_NAME8))
                {
                    prgzeile = replaceparam(VAR10_NAME8, prgzeile, zeile);
                }else if(zeile.contains(VAR10_NAME9))
                {
                    prgzeile = replaceparam(VAR10_NAME9, prgzeile, zeile);
                }else if(zeile.contains(VAR10_NAME10))
                {
                    prgzeile = replaceparam(VAR10_NAME10, prgzeile, zeile);
                }else if(zeile.contains(VAR10_WERT1))
                {
                    prgzeile = replaceparam(VAR10_WERT1, prgzeile, zeile);
                }else if(zeile.contains(VAR10_WERT2))
                {
                    prgzeile = replaceparam(VAR10_WERT2, prgzeile, zeile);
                }else if(zeile.contains(VAR10_WERT3))
                {
                    prgzeile = replaceparam(VAR10_WERT3, prgzeile, zeile);
                }else if(zeile.contains(VAR10_WERT4))
                {
                    prgzeile = replaceparam(VAR10_WERT4, prgzeile, zeile);
                }else if(zeile.contains(VAR10_WERT5))
                {
                    prgzeile = replaceparam(VAR10_WERT5, prgzeile, zeile);
                }else if(zeile.contains(VAR10_WERT6))
                {
                    prgzeile = replaceparam(VAR10_WERT6, prgzeile, zeile);
                }else if(zeile.contains(VAR10_WERT7))
                {
                    prgzeile = replaceparam(VAR10_WERT7, prgzeile, zeile);
                }else if(zeile.contains(VAR10_WERT8))
                {
                    prgzeile = replaceparam(VAR10_WERT8, prgzeile, zeile);
                }else if(zeile.contains(VAR10_WERT9))
                {
                    prgzeile = replaceparam(VAR10_WERT9, prgzeile, zeile);
                }else if(zeile.contains(VAR10_WERT10))
                {
                    prgzeile = replaceparam(VAR10_WERT10, prgzeile, zeile);
                }else if(zeile.contains(VAR10_BEZ))
                {
                    prgzeile = replaceparam(VAR10_BEZ, prgzeile, zeile);
                }else if(zeile.contains(VAR10_AFB))
                {
                    prgzeile = replaceparam(VAR10_AFB, prgzeile, zeile);
                }else if (zeile.contains(VAR10_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_FAUF))
        {
            QString prgzeile;
            prgzeile  = DLG_FAUF;
            prgzeile += vorlage_fauf;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(FAUF_WKZ))
                {
                    prgzeile = replaceparam(FAUF_WKZ, prgzeile, zeile);
                }else if(zeile.contains(FAUF_X))
                {
                    prgzeile = replaceparam(FAUF_X, prgzeile, zeile);
                }else if(zeile.contains(FAUF_Y))
                {
                    prgzeile = replaceparam(FAUF_Y, prgzeile, zeile);
                }else if(zeile.contains(FAUF_Z))
                {
                    prgzeile = replaceparam(FAUF_Z, prgzeile, zeile);
                }else if(zeile.contains(FAUF_ERG))
                {
                    prgzeile = replaceparam(FAUF_ERG, prgzeile, zeile);
                }else if(zeile.contains(FAUF_KADI))
                {
                    prgzeile = replaceparam(FAUF_KADI, prgzeile, zeile);
                }else if(zeile.contains(FAUF_KOR))
                {
                    prgzeile = replaceparam(FAUF_KOR, prgzeile, zeile);
                }else if(zeile.contains(FAUF_ANTYP))
                {
                    prgzeile = replaceparam(FAUF_ANTYP, prgzeile, zeile);
                }else if(zeile.contains(FAUF_ABTYP))
                {
                    prgzeile = replaceparam(FAUF_ABTYP, prgzeile, zeile);
                }else if(zeile.contains(FAUF_EINTYP))
                {
                    prgzeile = replaceparam(FAUF_EINTYP, prgzeile, zeile);
                }else if(zeile.contains(FAUF_ANWEG))
                {
                    prgzeile = replaceparam(FAUF_ANWEG, prgzeile, zeile);
                }else if(zeile.contains(FAUF_ABWEG))
                {
                    prgzeile = replaceparam(FAUF_ABWEG, prgzeile, zeile);
                }else if(zeile.contains(FAUF_ANVO))
                {
                    prgzeile = replaceparam(FAUF_ANVO, prgzeile, zeile);
                }else if(zeile.contains(FAUF_VO))
                {
                    prgzeile = replaceparam(FAUF_VO, prgzeile, zeile);
                }else if(zeile.contains(FAUF_DREHZ))
                {
                    prgzeile = replaceparam(FAUF_DREHZ, prgzeile, zeile);
                }else if(zeile.contains(FAUF_EVERS))
                {
                    prgzeile = replaceparam(FAUF_EVERS, prgzeile, zeile);
                }else if(zeile.contains(FAUF_WKZAKT))
                {
                    prgzeile = replaceparam(FAUF_WKZAKT, prgzeile, zeile);
                }else if(zeile.contains(FAUF_BEZ))
                {
                    prgzeile = replaceparam(FAUF_BEZ, prgzeile, zeile);
                }else if(zeile.contains(FAUF_AFB))
                {
                    prgzeile = replaceparam(FAUF_AFB, prgzeile, zeile);
                }else if (zeile.contains(FAUF_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_FABF))
        {
            QString prgzeile;
            prgzeile  = DLG_FABF;
            prgzeile += vorlage_fabf;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(FABF_DREHBAR))
                {
                    prgzeile = replaceparam(FABF_DREHBAR, prgzeile, zeile);
                }else if(zeile.contains(FABF_OFFSET))
                {
                    prgzeile = replaceparam(FABF_OFFSET, prgzeile, zeile);
                }else if(zeile.contains(FABF_FESTWI))
                {
                    prgzeile = replaceparam(FABF_FESTWI, prgzeile, zeile);
                }else if(zeile.contains(FABF_BEZ))
                {
                    prgzeile = replaceparam(FABF_BEZ, prgzeile, zeile);
                }else if(zeile.contains(FABF_AFB))
                {
                    prgzeile = replaceparam(FABF_AFB, prgzeile, zeile);
                }else if (zeile.contains(FABF_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_FGERADE))
        {
            QString prgzeile;
            prgzeile  = DLG_FGERADE;
            prgzeile += vorlage_fgerade;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(FGERADE_X))
                {
                    prgzeile = replaceparam(FGERADE_X, prgzeile, zeile);
                }else if(zeile.contains(FGERADE_Y))
                {
                    prgzeile = replaceparam(FGERADE_Y, prgzeile, zeile);
                }else if(zeile.contains(FGERADE_Z))
                {
                    prgzeile = replaceparam(FGERADE_Z, prgzeile, zeile);
                }else if(zeile.contains(FGERADE_RAD))
                {
                    prgzeile = replaceparam(FGERADE_RAD, prgzeile, zeile);
                }else if(zeile.contains(FGERADE_VO))
                {
                    prgzeile = replaceparam(FGERADE_VO, prgzeile, zeile);
                }else if(zeile.contains(FGERADE_DREHBAR))
                {
                    prgzeile = replaceparam(FGERADE_DREHBAR, prgzeile, zeile);
                }else if(zeile.contains(FGERADE_OFFSET))
                {
                    prgzeile = replaceparam(FGERADE_OFFSET, prgzeile, zeile);
                }else if(zeile.contains(FGERADE_FESTWI))
                {
                    prgzeile = replaceparam(FGERADE_FESTWI, prgzeile, zeile);
                }else if(zeile.contains(FGERADE_BEZ))
                {
                    prgzeile = replaceparam(FGERADE_BEZ, prgzeile, zeile);
                }else if(zeile.contains(FGERADE_AFB))
                {
                    prgzeile = replaceparam(FGERADE_AFB, prgzeile, zeile);
                }else if (zeile.contains(FGERADE_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_SPIEGELN))
        {
            QString prgzeile;
            prgzeile  = DLG_SPIEGELN;
            prgzeile += vorlage_spiegeln;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(SPIEGELN_XPOS))
                {
                    prgzeile = replaceparam(SPIEGELN_XPOS, prgzeile, zeile);
                }else if(zeile.contains(SPIEGELN_YPOS))
                {
                    prgzeile = replaceparam(SPIEGELN_YPOS, prgzeile, zeile);
                }else if(zeile.contains(SPIEGELN_XBED))
                {
                    prgzeile = replaceparam(SPIEGELN_XBED, prgzeile, zeile);
                }else if(zeile.contains(SPIEGELN_YBED))
                {
                    prgzeile = replaceparam(SPIEGELN_YBED, prgzeile, zeile);
                }else if (zeile.contains(SPIEGELN_BEZ))
                {
                    prgzeile = replaceparam(SPIEGELN_BEZ, prgzeile, zeile);
                }else if (zeile.contains(SPIEGELN_AFB))
                {
                   prgzeile = replaceparam(SPIEGELN_AFB, prgzeile, zeile);
                }else if (zeile.contains(SPIEGELN_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(zeile.contains(DLG_LAGE_AENDERN))
        {
            QString prgzeile;
            prgzeile  = DLG_LAGE_AENDERN;
            prgzeile += vorlage_lageaendern;
            prgzeile += ENDE_ZEILE;
            i++;
            zeile = tz.zeile(i);
            zeile.replace("'",".");
            while(!zeile.contains("[") && i<=tz.zeilenanzahl())
            {
                if(zeile.contains(LAGE_AENDERN_XALT))
                {
                    prgzeile = replaceparam(LAGE_AENDERN_XALT, prgzeile, zeile);
                }else if(zeile.contains(LAGE_AENDERN_YALT))
                {
                    prgzeile = replaceparam(LAGE_AENDERN_YALT, prgzeile, zeile);
                }else if(zeile.contains(LAGE_AENDERN_XNEU))
                {
                    prgzeile = replaceparam(LAGE_AENDERN_XNEU, prgzeile, zeile);
                }else if(zeile.contains(LAGE_AENDERN_YNEU))
                {
                    prgzeile = replaceparam(LAGE_AENDERN_YNEU, prgzeile, zeile);
                }else if (zeile.contains(LAGE_AENDERN_DREHWI))
                {
                    prgzeile = replaceparam(LAGE_AENDERN_DREHWI, prgzeile, zeile);
                }else if (zeile.contains(LAGE_AENDERN_KETTENMAS))
                {
                   prgzeile = replaceparam(LAGE_AENDERN_KETTENMAS, prgzeile, zeile);
                }else if (zeile.contains(LAGE_AENDERN_GESWI))
                {
                   prgzeile = replaceparam(LAGE_AENDERN_GESWI, prgzeile, zeile);
                }else if (zeile.contains(LAGE_AENDERN_BEZ))
                {
                   prgzeile = replaceparam(LAGE_AENDERN_BEZ, prgzeile, zeile);
                }else if (zeile.contains(LAGE_AENDERN_AFB))
                {
                   prgzeile = replaceparam(LAGE_AENDERN_AFB, prgzeile, zeile);
                }else if (zeile.contains(LAGE_AENDERN_AUSGEBL))
                {
                    QString tmp = "//";
                    prgzeile = tmp + prgzeile;
                }
                i++;
                zeile = tz.zeile(i);
                zeile.replace("'",".");
            }
            i--;
            retz.zeile_anhaengen(prgzeile);
        }else if(  zeile.contains("[DOCINFO]") || zeile.contains("[VARDEFAU]")  )
        {
            continue;
        }else if(  zeile.contains("[") && zeile.contains("]")  )
        {
            if(msg_unbekannte_dlg == false)
            {
                QString msg;
                msg = "Die Datei\n";
                msg += prgname;
                msg += "\nenthällt nicht programmierte Dialoge.\n";
                msg += "Die Originaldatei kann nur lesend geöffnet werden!\n";
                msg += "Bitte verwenden Sie \"Speichern unter\" wenn sie die Datei speichern möchten.";
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                readonly = true;
                msg_unbekannte_dlg = true;
            }
        }

    }
    return retz;
}

QString MainWindow::replaceparam(QString param, QString ziel, QString quelle)
{
    QString alterWert = text_mitte(ziel, param, ENDPAR);
    QString neuerWert = text_rechts(quelle, param);
    if(neuerWert == FMCNULL)
    {
        neuerWert = "";
    }
    ziel.replace(param+alterWert, param+neuerWert);
    return ziel;
}

QString MainWindow::exportparam(QString param, QString paramzeile)
{
    QString msg = param;
    QString wert;
    wert = selektiereEintrag(paramzeile, param, ENDPAR);
    if(wert.isEmpty())
    {
        wert = FMCNULL;
    }
    msg += wert;
    msg += "\n";
    return  msg;
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

            msg += exportparam(PKOPF_KOM1, zeile);
            msg += exportparam(PKOPF_KOM2, zeile);
            msg += exportparam(PKOPF_L, zeile);
            msg += exportparam(PKOPF_B, zeile);
            msg += exportparam(PKOPF_D, zeile);
            msg += exportparam(PKOPF_FUENFSEI, zeile);
            msg += exportparam(PKOPF_SPEIGELN, zeile);
            msg += exportparam(PKOPF_BELEGART, zeile);
            msg += exportparam(PKOPF_XVERS, zeile);
            msg += exportparam(PKOPF_YVERS, zeile);
            msg += exportparam(PKOFP_RTL, zeile);
            msg += exportparam(PKOFP_RTB, zeile);
            msg += exportparam(PKOPF_LOESEN, zeile);
            msg += exportparam(PKOPF_SCHABH, zeile);
            msg += exportparam(PKOPF_SIABST, zeile);
            msg += exportparam(PKOPF_PAPO, zeile);
            msg += exportparam(PKOPF_BEZ, zeile);
            msg += exportparam(PKOPF_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_PENDE))
        {
            msg += DLG_PENDE;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(PENDE_PAPO, zeile);
            msg += exportparam(PENDE_BEZ, zeile);
            msg += exportparam(PENDE_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_KOM))
        {
            msg += DLG_KOM;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(KOM_BEZ, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_HALT))
        {
            msg += DLG_HALT;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(HALT_X, zeile);
            msg += exportparam(HALT_Y, zeile);
            msg += exportparam(HALT_BEZ, zeile);
            msg += exportparam(HALT_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_BO))
        {
            msg += DLG_BO;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(BO_X, zeile);
            msg += exportparam(BO_Y, zeile);
            msg += exportparam(BO_BOTI, zeile);
            msg += exportparam(BO_DM, zeile);
            msg += exportparam(BO_GRUPPE, zeile);
            msg += exportparam(BO_ANBOTI, zeile);
            msg += exportparam(BO_ANBOVO, zeile);
            msg += exportparam(BO_REBOMA, zeile);
            msg += exportparam(BO_BOVO, zeile);
            msg += exportparam(BO_ZSM, zeile);
            msg += exportparam(BO_DREHZ, zeile);
            msg += exportparam(BO_MESSEI, zeile);
            msg += exportparam(BO_TASATZ, zeile);
            msg += exportparam(BO_PLM, zeile);
            msg += exportparam(BO_BEZ, zeile);
            msg += exportparam(BO_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_BOY))
        {
            msg += DLG_BOY;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(BOY_X, zeile);
            msg += exportparam(BOY_X2, zeile);
            msg += exportparam(BOY_Y1, zeile);
            msg += exportparam(BOY_Y2, zeile);
            msg += exportparam(BOY_Y3, zeile);
            msg += exportparam(BOY_Y4, zeile);
            msg += exportparam(BOY_Y5, zeile);
            msg += exportparam(BOY_Y6, zeile);
            msg += exportparam(BOY_BOTI, zeile);
            msg += exportparam(BOY_DM, zeile);
            msg += exportparam(BOY_KETTE, zeile);
            msg += exportparam(BOY_GRUPPE, zeile);
            msg += exportparam(BOY_ANBOTI, zeile);
            msg += exportparam(BOY_ANBOVO, zeile);
            msg += exportparam(BOY_REBOMA, zeile);
            msg += exportparam(BOY_BOVO, zeile);
            msg += exportparam(BOY_ZSM, zeile);
            msg += exportparam(BOY_DREHZ, zeile);
            msg += exportparam(BOY_MESSEI, zeile);
            msg += exportparam(BOY_TASATZ, zeile);
            msg += exportparam(BOY_PLM, zeile);
            msg += exportparam(BOY_BEZ, zeile);
            msg += exportparam(BOY_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_BOX))
        {
            msg += DLG_BOX;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(BOX_Y, zeile);
            msg += exportparam(BOX_Y2, zeile);
            msg += exportparam(BOX_X1, zeile);
            msg += exportparam(BOX_X2, zeile);
            msg += exportparam(BOX_X3, zeile);
            msg += exportparam(BOX_X4, zeile);
            msg += exportparam(BOX_X5, zeile);
            msg += exportparam(BOX_X6, zeile);
            msg += exportparam(BOX_BOTI, zeile);
            msg += exportparam(BOX_DM, zeile);
            msg += exportparam(BOX_KETTE, zeile);
            msg += exportparam(BOX_GRUPPE, zeile);
            msg += exportparam(BOX_ANBOTI, zeile);
            msg += exportparam(BOX_ANBOVO, zeile);
            msg += exportparam(BOX_REBOMA, zeile);
            msg += exportparam(BOX_BOVO, zeile);
            msg += exportparam(BOX_ZSM, zeile);
            msg += exportparam(BOX_DREHZ, zeile);
            msg += exportparam(BOX_MESSEI, zeile);
            msg += exportparam(BOX_TASATZ, zeile);
            msg += exportparam(BOX_PLM, zeile);
            msg += exportparam(BOX_BEZ, zeile);
            msg += exportparam(BOX_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_LOREIAE))
        {
            msg += DLG_LOREIAE;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(LOREIAE_XS, zeile);
            msg += exportparam(LOREIAE_XE, zeile);
            msg += exportparam(LOREIAE_Y1, zeile);
            msg += exportparam(LOREIAE_Y2, zeile);
            msg += exportparam(LOREIAE_YE, zeile);
            msg += exportparam(LOREIAE_RASTER, zeile);
            msg += exportparam(LOREIAE_BOTI, zeile);
            msg += exportparam(LOREIAE_DM, zeile);
            msg += exportparam(LOREIAE_GRUPPE, zeile);
            msg += exportparam(LOREIAE_VERMIT, zeile);
            msg += exportparam(LOREIAE_ANBOTI, zeile);
            msg += exportparam(LOREIAE_ANBOVO, zeile);
            msg += exportparam(LOREIAE_REBOMA, zeile);
            msg += exportparam(LOREIAE_BOVO, zeile);
            msg += exportparam(LOREIAE_ZSM, zeile);
            msg += exportparam(LOREIAE_DREHZ, zeile);
            msg += exportparam(LOREIAE_MESSEI, zeile);
            msg += exportparam(LOREIAE_TASATZ, zeile);
            msg += exportparam(LOREIAE_PLM, zeile);
            msg += exportparam(LOREIAE_BEZ, zeile);
            msg += exportparam(LOREIAE_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_LOREIMA))
        {
            msg += DLG_LOREIMA;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(LOREIMA_XS, zeile);
            msg += exportparam(LOREIMA_XM, zeile);
            msg += exportparam(LOREIMA_Y1, zeile);
            msg += exportparam(LOREIMA_Y2, zeile);
            msg += exportparam(LOREIMA_RASTER, zeile);
            msg += exportparam(LOREIMA_BOTI, zeile);
            msg += exportparam(LOREIMA_DM, zeile);
            msg += exportparam(LOREIMA_GRUPPE, zeile);
            msg += exportparam(LOREIMA_ANBOTI, zeile);
            msg += exportparam(LOREIMA_ANBOVO, zeile);
            msg += exportparam(LOREIMA_REBOMA, zeile);
            msg += exportparam(LOREIMA_BOVO, zeile);
            msg += exportparam(LOREIMA_ZSM, zeile);
            msg += exportparam(LOREIMA_DREHZ, zeile);
            msg += exportparam(LOREIMA_MESSEI, zeile);
            msg += exportparam(LOREIMA_TASATZ, zeile);
            msg += exportparam(LOREIMA_PLM, zeile);
            msg += exportparam(LOREIMA_BEZ, zeile);
            msg += exportparam(LOREIMA_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_TOPF))
        {
            msg += DLG_TOPF;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(TOPF_TA, zeile);
            msg += exportparam(TOPF_A1, zeile);
            msg += exportparam(TOPF_A2, zeile);
            msg += exportparam(TOPF_A3, zeile);
            msg += exportparam(TOPF_A4, zeile);
            msg += exportparam(TOPF_A5, zeile);
            msg += exportparam(TOPF_MA, zeile);
            msg += exportparam(TOPF_MB, zeile);
            msg += exportparam(TOPF_KETTE, zeile);
            msg += exportparam(TOPF_GRUPPE, zeile);
            msg += exportparam(TOPF_SEITE, zeile);
            msg += exportparam(TOPF_MESSEI, zeile);
            msg += exportparam(TOPF_BODM, zeile);
            msg += exportparam(TOPF_TODM, zeile);
            msg += exportparam(TOPF_BOTI, zeile);
            msg += exportparam(TOPF_WKZ, zeile);
            msg += exportparam(TOPF_TOTI, zeile);
            msg += exportparam(TOPF_ANBOTI, zeile);
            msg += exportparam(TOPF_BOANBOVO, zeile);
            msg += exportparam(TOPF_TOANBOVO, zeile);
            msg += exportparam(TOPF_REBOMA, zeile);
            msg += exportparam(TOPF_BOBOVO, zeile);
            msg += exportparam(TOPF_TOBOVO, zeile);
            msg += exportparam(TOPF_BOZSM, zeile);
            msg += exportparam(TOPF_DREHZ, zeile);
            msg += exportparam(TOPF_PLM, zeile);
            msg += exportparam(TOPF_BEZ, zeile);
            msg += exportparam(TOPF_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_HBEXP))
        {
            msg += DLG_HBEXP;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(HBEXP_Y1, zeile);
            msg += exportparam(HBEXP_Y2, zeile);
            msg += exportparam(HBEXP_Y3, zeile);
            msg += exportparam(HBEXP_Y4, zeile);
            msg += exportparam(HBEXP_Y5, zeile);
            msg += exportparam(HBEXP_Y6, zeile);
            msg += exportparam(HBEXP_BOTI, zeile);
            msg += exportparam(HBEXP_Z, zeile);
            msg += exportparam(HBEXP_DM, zeile);
            msg += exportparam(HBEXP_KETTE, zeile);
            msg += exportparam(HBEXP_GRUPPE, zeile);
            msg += exportparam(HBEXP_X2, zeile);
            msg += exportparam(HBEXP_X1, zeile);
            msg += exportparam(HBEXP_ANBOTI, zeile);
            msg += exportparam(HBEXP_ANBOVO, zeile);
            msg += exportparam(HBEXP_BOVO, zeile);
            msg += exportparam(HBEXP_DREHZ, zeile);
            msg += exportparam(HBEXP_BEZ, zeile);
            msg += exportparam(HBEXP_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_HBEXM))
        {
            msg += DLG_HBEXM;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(HBEXM_Y1, zeile);
            msg += exportparam(HBEXM_Y2, zeile);
            msg += exportparam(HBEXM_Y3, zeile);
            msg += exportparam(HBEXM_Y4, zeile);
            msg += exportparam(HBEXM_Y5, zeile);
            msg += exportparam(HBEXM_Y6, zeile);
            msg += exportparam(HBEXM_BOTI, zeile);
            msg += exportparam(HBEXM_Z, zeile);
            msg += exportparam(HBEXM_DM, zeile);
            msg += exportparam(HBEXM_KETTE, zeile);
            msg += exportparam(HBEXM_GRUPPE, zeile);
            msg += exportparam(HBEXM_X2, zeile);
            msg += exportparam(HBEXM_X1, zeile);
            msg += exportparam(HBEXM_ANBOTI, zeile);
            msg += exportparam(HBEXM_ANBOVO, zeile);
            msg += exportparam(HBEXM_BOVO, zeile);
            msg += exportparam(HBEXM_DREHZ, zeile);
            msg += exportparam(HBEXM_BEZ, zeile);
            msg += exportparam(HBEXM_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_HBEYP))
        {
            msg += DLG_HBEYP;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(HBEYP_X1, zeile);
            msg += exportparam(HBEYP_X2, zeile);
            msg += exportparam(HBEYP_X3, zeile);
            msg += exportparam(HBEYP_X4, zeile);
            msg += exportparam(HBEYP_X5, zeile);
            msg += exportparam(HBEYP_X6, zeile);
            msg += exportparam(HBEYP_BOTI, zeile);
            msg += exportparam(HBEYP_Z, zeile);
            msg += exportparam(HBEYP_DM, zeile);
            msg += exportparam(HBEYP_KETTE, zeile);
            msg += exportparam(HBEYP_GRUPPE, zeile);
            msg += exportparam(HBEYP_Y2, zeile);
            msg += exportparam(HBEYP_Y1, zeile);
            msg += exportparam(HBEYP_ANBOTI, zeile);
            msg += exportparam(HBEYP_ANBOVO, zeile);
            msg += exportparam(HBEYP_BOVO, zeile);
            msg += exportparam(HBEYP_DREHZ, zeile);
            msg += exportparam(HBEYP_BEZ, zeile);
            msg += exportparam(HBEYP_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_HBEYM))
        {
            msg += DLG_HBEYM;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(HBEYM_X1, zeile);
            msg += exportparam(HBEYM_X2, zeile);
            msg += exportparam(HBEYM_X3, zeile);
            msg += exportparam(HBEYM_X4, zeile);
            msg += exportparam(HBEYM_X5, zeile);
            msg += exportparam(HBEYM_X6, zeile);
            msg += exportparam(HBEYM_BOTI, zeile);
            msg += exportparam(HBEYM_Z, zeile);
            msg += exportparam(HBEYM_DM, zeile);
            msg += exportparam(HBEYM_KETTE, zeile);
            msg += exportparam(HBEYM_GRUPPE, zeile);
            msg += exportparam(HBEYM_Y2, zeile);
            msg += exportparam(HBEYM_Y1, zeile);
            msg += exportparam(HBEYM_ANBOTI, zeile);
            msg += exportparam(HBEYM_ANBOVO, zeile);
            msg += exportparam(HBEYM_BOVO, zeile);
            msg += exportparam(HBEYM_DREHZ, zeile);
            msg += exportparam(HBEYM_BEZ, zeile);
            msg += exportparam(HBEYM_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_NUT))
        {
            msg += DLG_NUT;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(NUT_WKZ, zeile);
            msg += exportparam(NUT_SX, zeile);
            msg += exportparam(NUT_SY, zeile);
            msg += exportparam(NUT_EX, zeile);
            msg += exportparam(NUT_EY, zeile);
            msg += exportparam(NUT_TI, zeile);
            msg += exportparam(NUT_B, zeile);
            msg += exportparam(NUT_AUSLAUF, zeile);
            msg += exportparam(NUT_KOR, zeile);
            msg += exportparam(NUT_GEGENLAUF, zeile);
            msg += exportparam(NUT_NWI, zeile);
            msg += exportparam(NUT_NTYP, zeile);
            msg += exportparam(NUT_NABST, zeile);
            msg += exportparam(NUT_Z, zeile);
            msg += exportparam(NUT_EINVO, zeile);
            msg += exportparam(NUT_VO, zeile);
            msg += exportparam(NUT_DREHZ, zeile);
            msg += exportparam(NUT_PLM, zeile);
            msg += exportparam(NUT_WKZAKT, zeile);
            msg += exportparam(NUT_BEZ, zeile);
            msg += exportparam(NUT_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_KTA))
        {
            msg += DLG_KTA;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(KTA_WKZ, zeile);
            msg += exportparam(KTA_X, zeile);
            msg += exportparam(KTA_Y, zeile);
            msg += exportparam(KTA_DM, zeile);
            msg += exportparam(KTA_TI, zeile);
            msg += exportparam(KTA_ZUST, zeile);
            msg += exportparam(KTA_GEGENL, zeile);
            msg += exportparam(KTA_AUSR, zeile);
            msg += exportparam(KTA_EINVO, zeile);
            msg += exportparam(KTA_VO, zeile);
            msg += exportparam(KTA_DREHZ, zeile);
            msg += exportparam(KTA_PLM, zeile);
            msg += exportparam(KTA_WKZAKT, zeile);
            msg += exportparam(KTA_BEZ, zeile);
            msg += exportparam(KTA_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_RTA))
        {
            msg += DLG_RTA;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(RTA_WKZ, zeile);
            msg += exportparam(RTA_X, zeile);
            msg += exportparam(RTA_Y, zeile);
            msg += exportparam(RTA_L, zeile);
            msg += exportparam(RTA_B, zeile);
            msg += exportparam(RTA_TI, zeile);
            msg += exportparam(RTA_RAD, zeile);
            msg += exportparam(RTA_ZUST, zeile);
            msg += exportparam(RTA_GEGENL, zeile);
            msg += exportparam(RTA_WI, zeile);
            msg += exportparam(RTA_AUSR, zeile);
            msg += exportparam(RTA_EINVO, zeile);
            msg += exportparam(RTA_VO, zeile);
            msg += exportparam(RTA_DREHZ, zeile);
            msg += exportparam(RTA_PLM, zeile);
            msg += exportparam(RTA_WKZAKT, zeile);
            msg += exportparam(RTA_BEZ, zeile);
            msg += exportparam(RTA_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_VAR))
        {
            msg += DLG_VAR;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(VAR_NAME, zeile);
            msg += exportparam(VAR_WERT, zeile);
            msg += exportparam(VAR_BEZ, zeile);
            msg += exportparam(VAR_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_VAR10))
        {
            msg += DLG_VAR10;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(VAR10_NAME1, zeile);
            msg += exportparam(VAR10_NAME2, zeile);
            msg += exportparam(VAR10_NAME3, zeile);
            msg += exportparam(VAR10_NAME4, zeile);
            msg += exportparam(VAR10_NAME5, zeile);
            msg += exportparam(VAR10_NAME6, zeile);
            msg += exportparam(VAR10_NAME7, zeile);
            msg += exportparam(VAR10_NAME8, zeile);
            msg += exportparam(VAR10_NAME9, zeile);
            msg += exportparam(VAR10_NAME10, zeile);
            msg += exportparam(VAR10_WERT1, zeile);
            msg += exportparam(VAR10_WERT2, zeile);
            msg += exportparam(VAR10_WERT3, zeile);
            msg += exportparam(VAR10_WERT4, zeile);
            msg += exportparam(VAR10_WERT5, zeile);
            msg += exportparam(VAR10_WERT6, zeile);
            msg += exportparam(VAR10_WERT7, zeile);
            msg += exportparam(VAR10_WERT8, zeile);
            msg += exportparam(VAR10_WERT9, zeile);
            msg += exportparam(VAR10_WERT10, zeile);
            msg += exportparam(VAR10_BEZ, zeile);
            msg += exportparam(VAR10_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_FAUF))
        {
            msg += DLG_FAUF;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(FAUF_WKZ, zeile);
            msg += exportparam(FAUF_X, zeile);
            msg += exportparam(FAUF_Y, zeile);
            msg += exportparam(FAUF_Z, zeile);
            msg += exportparam(FAUF_ERG, zeile);
            msg += exportparam(FAUF_KADI, zeile);
            msg += exportparam(FAUF_KOR, zeile);
            msg += exportparam(FAUF_ANTYP, zeile);
            msg += exportparam(FAUF_ABTYP, zeile);
            msg += exportparam(FAUF_EINTYP, zeile);
            msg += exportparam(FAUF_ANWEG, zeile);
            msg += exportparam(FAUF_ABWEG, zeile);
            msg += exportparam(FAUF_ANVO, zeile);
            msg += exportparam(FAUF_VO, zeile);
            msg += exportparam(FAUF_DREHZ, zeile);
            msg += exportparam(FAUF_EVERS, zeile);
            msg += exportparam(FAUF_WKZAKT, zeile);
            msg += exportparam(FAUF_BEZ, zeile);
            msg += exportparam(FAUF_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_FABF))
        {
            msg += DLG_FABF;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(FABF_DREHBAR, zeile);
            msg += exportparam(FABF_OFFSET, zeile);
            msg += exportparam(FABF_FESTWI, zeile);
            msg += exportparam(FABF_BEZ, zeile);
            msg += exportparam(FABF_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_FGERADE))
        {
            msg += DLG_FGERADE;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(FGERADE_X, zeile);
            msg += exportparam(FGERADE_Y, zeile);
            msg += exportparam(FGERADE_Z, zeile);
            msg += exportparam(FGERADE_RAD, zeile);
            msg += exportparam(FGERADE_VO, zeile);
            msg += exportparam(FGERADE_DREHBAR, zeile);
            msg += exportparam(FGERADE_OFFSET, zeile);
            msg += exportparam(FGERADE_FESTWI, zeile);
            msg += exportparam(FGERADE_BEZ, zeile);
            msg += exportparam(FGERADE_AFB, zeile);
            msg += "\n";
        }else if(zeile.contains(DLG_SPIEGELN))
        {
            msg += DLG_SPIEGELN;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(SPIEGELN_XPOS, zeile);
            msg += exportparam(SPIEGELN_YPOS, zeile);
            msg += exportparam(SPIEGELN_XBED, zeile);
            msg += exportparam(SPIEGELN_YBED, zeile);
            msg += exportparam(SPIEGELN_BEZ, zeile);
            msg += exportparam(SPIEGELN_AFB, zeile);msg += "\n";
        }else if(zeile.contains(DLG_LAGE_AENDERN))
        {
            msg += DLG_LAGE_AENDERN;
            msg += "\n";
            if(zeile.at(0)=="/" && zeile.at(1)=="/")
            {
                msg += FMCAUSGEBL;
                msg += "\n";
            }

            msg += exportparam(LAGE_AENDERN_XALT, zeile);
            msg += exportparam(LAGE_AENDERN_YALT, zeile);
            msg += exportparam(LAGE_AENDERN_XNEU, zeile);
            msg += exportparam(LAGE_AENDERN_YNEU, zeile);
            msg += exportparam(LAGE_AENDERN_DREHWI, zeile);
            msg += exportparam(LAGE_AENDERN_KETTENMAS, zeile);
            msg += exportparam(LAGE_AENDERN_GESWI, zeile);
            msg += exportparam(LAGE_AENDERN_BEZ, zeile);
            msg += exportparam(LAGE_AENDERN_AFB, zeile);
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
    if(  (tt.get_prgtext()->get_nurlesend() == true) && (speichern_unter_flag == false)  )
    {
        QMessageBox mb;
        mb.setText("Datei kann nicht gespeichert werden da sie nur lesend geöffnet ist.");
        mb.exec();
        return false;
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
            }else if(programmzeile.contains(DLG_PENDE))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &prgende, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_KOM))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &kom, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_HALT))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &halt, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_BO))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgbo, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_BOY))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgboy, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_BOX))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgbox, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_LOREIAE))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgloreiae, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_LOREIMA))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgloreima, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_TOPF))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgtopf, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_HBEXP))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlghbexp, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_HBEXM))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlghbexm, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_HBEYP))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlghbeyp, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_HBEYM))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlghbeym, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_NUT))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgnut, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_KTA))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgkta, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_RTA))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgrta, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_VAR))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgvar, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_VAR10))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgvar10, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_FAUF))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgfauf, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_FABF))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgfabf, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_FGERADE))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgfgerade, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_SPIEGELN))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgspiegeln, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(DLG_LAGE_AENDERN))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlglageaendern, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }
        }
    }else if(ui->tabWidget->currentIndex() == INDEX_WERKZEUGLISTE)
    {
        QList<QListWidgetItem*> items = ui->listWidget_Werkzeug->selectedItems();
        int items_menge = items.count();

        if(items_menge==1)
        {
            //text aus der aktiven Zeile in string speichern:
            QString programmzeile;
            if(ui->listWidget_Werkzeug->currentIndex().isValid()  &&  (ui->listWidget_Werkzeug->currentItem()->isSelected()))
            {
                programmzeile = wkz.zeile(ui->listWidget_Werkzeug->currentRow()+1);
            } else
            {
                QMessageBox mb;
                mb.setText("Sie haben noch nichts ausgewaelt was geaendert werden kann!");
                mb.exec();
                return;
            }
            //ermitteln an welches Unterfenster der string gehen soll und die Zeile Übergeben:
            if(programmzeile.contains(WKZ_FRAESER))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgfraeser, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }else if(programmzeile.contains(WKZ_SAEGE))
            {
                connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgsaege, SLOT(getDialogData(QString,bool)));
                emit sendDialogData(programmzeile, true);
            }
        }
    }
}

void MainWindow::on_listWidget_Programmliste_itemDoubleClicked(QListWidgetItem *item)
{
    emit on_action_aendern_triggered();
}

void MainWindow::on_listWidget_Werkzeug_itemDoubleClicked(QListWidgetItem *item)
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
        wkz.undo();
        aktualisiere_anzeigetext_wkz(false);
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
        wkz.redo();
        aktualisiere_anzeigetext_wkz(false);
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
        if(kopierterEintrag_w != NICHT_DEFINIERT)
        {
            QList<QListWidgetItem*> items = ui->listWidget_Werkzeug->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Werkzeug->count() ;i++)
            {
                if(ui->listWidget_Werkzeug->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }

            //Einfügen über ausgewähltem Eintrag:
            text_zeilenweise tmp_tz;
            tmp_tz.set_text(kopierterEintrag_w);
            if(tmp_tz.zeilenanzahl()==1)
            {
                wkz.zeile_einfuegen(ui->listWidget_Werkzeug->currentRow()-items_menge+1 \
                                                 , kopierterEintrag_w);
                int row = aktualisiere_anzeigetext_wkz()-items_menge+2 ;
                ui->listWidget_Werkzeug->setCurrentRow(row);
            }else
            {
                wkz.zeilen_einfuegen(row_erstes, kopierterEintrag_w);
                int row = aktualisiere_anzeigetext_wkz()-items_menge+2+tmp_tz.zeilenanzahl()-1 ;
                ui->listWidget_Werkzeug->setCurrentRow(row);
            }
        }else
        {
            QMessageBox mb;
            mb.setText("Sie haben noch nichts kopiert!");
            mb.exec();
        }
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
        if((ui->listWidget_Werkzeug->currentIndex().isValid())  &&  (ui->listWidget_Werkzeug->currentItem()->isSelected()))
        {
            QList<QListWidgetItem*> items = ui->listWidget_Werkzeug->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Werkzeug->count() ;i++)
            {
                if(ui->listWidget_Werkzeug->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }

            if(items_menge==1)
            {
                QString tmp = wkz.zeile(ui->listWidget_Werkzeug->currentRow()+1);
                if(tmp == LISTENENDE)
                {
                    return;
                }
                kopierterEintrag_w = tmp;
            }else
            {
                QString tmp = wkz.zeilen(row_erstes+1, items_menge);
                kopierterEintrag_w = tmp;
            }
        } else
        {
            QMessageBox mb;
            mb.setText("Sie haben noch nichts ausgewaelt was kopiert werden kann!");
            mb.exec();
        }
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
        if((ui->listWidget_Werkzeug->currentIndex().isValid())  &&  (ui->listWidget_Werkzeug->currentItem()->isSelected()))
        {
            QList<QListWidgetItem*> items = ui->listWidget_Werkzeug->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Werkzeug->count() ;i++)
            {
                if(ui->listWidget_Werkzeug->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }

            if(items_menge==1)
            {
                QString tmp = wkz.zeile(ui->listWidget_Werkzeug->currentRow()+1);
                if(tmp == LISTENENDE)
                {
                    return;
                }
                kopierterEintrag_w = wkz.zeile(ui->listWidget_Werkzeug->currentRow()+1);
                wkz.zeile_loeschen(ui->listWidget_Werkzeug->currentRow()+1);
                aktualisiere_anzeigetext_wkz();
            }else
            {
                //Zeilen kopieren:
                QString tmp = wkz.zeilen(row_erstes+1, items_menge);
                kopierterEintrag_w = tmp;
                //Zeilen löschen:
                wkz.zeilen_loeschen(row_erstes+1, items_menge);
                aktualisiere_anzeigetext_wkz();
                ui->listWidget_Werkzeug->setCurrentRow(row_erstes);
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
        if((ui->listWidget_Werkzeug->currentIndex().isValid())  &&  \
                (ui->listWidget_Werkzeug->currentItem()->isSelected()))
        {
            QList<QListWidgetItem*> items = ui->listWidget_Werkzeug->selectedItems();
            int items_menge = items.count();
            int row_erstes = 0;//Nummer des ersten Elementes
            for(int i=0; i<ui->listWidget_Werkzeug->count() ;i++)
            {
                if(ui->listWidget_Werkzeug->item(i)->isSelected())
                {
                    row_erstes = i;
                    break;
                }
            }

            if(items_menge == 1)
            {
                QString tmp = wkz.zeile(ui->listWidget_Werkzeug->currentRow()+1);
                if(tmp == LISTENENDE)
                {
                    return;
                }
                wkz.zeile_loeschen(ui->listWidget_Werkzeug->currentRow()+1);
                aktualisiere_anzeigetext_wkz();
            }else
            {
                wkz.zeilen_loeschen(row_erstes+1, items_menge);
                aktualisiere_anzeigetext_wkz();
                ui->listWidget_Werkzeug->setCurrentRow(row_erstes);
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

//---------------------------------------------------Dialoge WOP:

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
        text_zeilenweise at = wkz.get_anzeigetext();
        if(at.zeilenanzahl() == 0)
        {
            wkz.zeile_anhaengen(text);
            aktualisiere_anzeigetext_wkz();
        }else
        {
            //Zeile über aktiver Zeile einfügen:
            wkz.zeile_einfuegen(ui->listWidget_Werkzeug->currentRow(), text);
            //aktualisieren und Element darunter aktivieren:
            int row = aktualisiere_anzeigetext_wkz() + 1;
            ui->listWidget_Werkzeug->setCurrentRow(row);
        }
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
        QString text_alt = wkz.zeile(ui->listWidget_Werkzeug->currentRow()+1);
        if(text != text_alt)
        {
            if(elementIstEingeblendet())
            {
                wkz.zeile_ersaetzen(ui->listWidget_Werkzeug->currentRow()+1, text);
                aktualisiere_anzeigetext_wkz();
            }else
            {
                wkz.zeile_ersaetzen(ui->listWidget_Werkzeug->currentRow()+1, "//"+text);
                aktualisiere_anzeigetext_wkz();
            }
        }
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

void MainWindow::on_actionMakeProgrammende_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &prgende, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_pende;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeKommentar_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &kom, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_kom;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeHalt_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &halt, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_halt;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeBohren_Durchmesser_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgbo, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_bo;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeBohren_in_Y_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgboy, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_boy;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeBohren_in_X_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgbox, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_box;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeLochreihe_Anfang_Ende_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgloreiae, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_loreiae;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeLochreihe_Mitte_Anfang_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgloreima, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_loreima;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeTopfband_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgtopf, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_topf;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeHBE_X_plus_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlghbexp, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_hbexp;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeHBE_X_minus_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlghbexm, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_hbexm;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeHBE_Y_plus_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlghbeyp, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_hbeyp;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeHBE_Y_minus_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlghbeym, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_hbeym;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeNut_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgnut, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_nut;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeKreistasche_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgkta, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_kta;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeRechtecktasche_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgrta, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_rta;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeVariable_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgvar, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_var;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeVariablen10_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgvar10, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_var10;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeFauf_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgfauf, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_fauf;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeAbfahren_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgfabf, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_fabf;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeFgerade_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgfgerade, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_fgerade;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeSpiegeln_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgspiegeln, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_spiegeln;
        emit sendDialogData(msg, false);
    }
}

void MainWindow::on_actionMakeLage_aendern_triggered()
{
    if(ui->tabWidget->currentIndex() != INDEX_PROGRAMMLISTE)
    {
        QMessageBox mb;
        mb.setText("Bitte wechseln Sie zuerst in den TAB Programme!");
        mb.exec();
    }else
    {
        disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
        connect(this, SIGNAL(sendDialogData(QString,bool)), &dlglageaendern, SLOT(getDialogData(QString,bool)));
        QString msg = vorlage_lageaendern;
        emit sendDialogData(msg, false);
    }
}
//---------------------------------------------------Dialoge wkz
void MainWindow::on_pushButton_MakeFraeser_clicked()
{
    disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
    connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgfraeser, SLOT(getDialogData(QString,bool)));
    emit sendDialogData("clear", false);
}

void MainWindow::on_pushButton_MakeSaege_clicked()
{
    disconnect(this, SIGNAL(sendDialogData(QString, bool)), 0, 0);
    connect(this, SIGNAL(sendDialogData(QString,bool)), &dlgsaege, SLOT(getDialogData(QString,bool)));
    emit sendDialogData("clear", false);
}

//---------------------------------------------------WKZ:
void MainWindow::slotNeedWKZ(QString dlgtyp)
{
    disconnect(this, SIGNAL(sendWKZlist(text_zeilenweise)), 0, 0);
    if(dlgtyp == DLG_NUT)
    {
        connect(this, SIGNAL(sendWKZlist(text_zeilenweise)), &dlgnut, SLOT(getWKZlist(text_zeilenweise)));
        emit sendWKZlist(wkz.get_wkzlist(WKZ_SAEGE, SAEGE_NAME));
    }else if(dlgtyp == DLG_KTA)
    {
        connect(this, SIGNAL(sendWKZlist(text_zeilenweise)), &dlgkta, SLOT(getWKZlist(text_zeilenweise)));
        emit sendWKZlist(wkz.get_wkzlist(WKZ_FRAESER, FRAESER_NAME));
    }else if(dlgtyp == DLG_RTA)
    {
        connect(this, SIGNAL(sendWKZlist(text_zeilenweise)), &dlgrta, SLOT(getWKZlist(text_zeilenweise)));
        emit sendWKZlist(wkz.get_wkzlist(WKZ_FRAESER, FRAESER_NAME));
    }else if(dlgtyp == DLG_FAUF)
    {
        connect(this, SIGNAL(sendWKZlist(text_zeilenweise)), &dlgfauf, SLOT(getWKZlist(text_zeilenweise)));
        emit sendWKZlist(wkz.get_wkzlist(WKZ_FRAESER, FRAESER_NAME));
    }
}


//---------------------------------------------------


































































