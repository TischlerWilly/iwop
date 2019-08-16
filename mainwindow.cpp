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
    settings_anz_undo_t             = "10";
    //settings_anz_undo_w             = "30";
    //speichern_unter_flag            = false;
    tt.clear();
    anz_neue_dateien                = 0;//Zählung neuer Dateien mit 0 beginnen und dann raufzählen

    vorschaufenster.setParent(ui->tab_Programmliste);
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
    vorschaufenster.setFixedHeight(ui->tab_Programmliste->height()-35);
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

//---------------------------------------------------Sichtbarkeiten
void MainWindow::hideElemets_noFileIsOpen()
{
    ui->listWidget_Programmliste->hide();
    //Menü Datei:
    //ui->actionDateiSpeichern->setDisabled(true);
    //ui->actionDateiSpeichern_unter->setDisabled(true);
    //ui->actionDateiSchliessen->setDisabled(true);
    //Menü Bearbeiten:
    //if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        //ui->actionAendern->setDisabled(true);
        //ui->actionEinfuegen->setDisabled(true);
        //ui->actionKopieren->setDisabled(true);
        //ui->actionAusschneiden->setDisabled(true);
        //ui->actionEntfernen->setDisabled(true);
    }
    //ui->actionEin_Ausblenden->setDisabled(true);
    //ui->actionAuswahl_Einblenden->setDisabled(true);
    //ui->actionAuswahl_Ausblenden->setDisabled(true);
    //Menü CAM:
    //ui->actionMakeProgrammkopf->setDisabled(true);
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
    //if(ui->tabWidget->currentIndex() == INDEX_PROGRAMMLISTE)
    {
        //ui->actionAendern->setEnabled(true);
        //ui->actionEinfuegen->setEnabled(true);
        //ui->actionKopieren->setEnabled(true);
        //ui->actionAusschneiden->setEnabled(true);
        //ui->actionEntfernen->setEnabled(true);
    }
    //ui->actionEin_Ausblenden->setEnabled(true);
    //ui->actionAuswahl_Einblenden->setEnabled(true);
    //ui->actionAuswahl_Ausblenden->setEnabled(true);
    //Menü CAM:
    //ui->actionMakeProgrammkopf->setEnabled(true);
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

//---------------------------------------------------Menüs:

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

//---------------------------------------------------Vorschaufenster

void MainWindow::vorschauAktualisieren()
{
    connect(this, SIGNAL(sendVorschauAktualisieren(programmtext,int)), &vorschaufenster, SLOT(slot_aktualisieren(programmtext,int)));
    emit sendVorschauAktualisieren(*tt.get_prgtext(), ui->listWidget_Programmliste->currentRow()+1);
}

//---------------------------------------------------Dialoge:
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
