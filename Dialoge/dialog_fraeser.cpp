#include "dialog_fraeser.h"
#include "ui_dialog_fraeser.h"

Dialog_fraeser::Dialog_fraeser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fraeser)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);
    clear();
}

Dialog_fraeser::~Dialog_fraeser()
{
    delete ui;
}

void Dialog_fraeser::clear()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_nr->clear();
    ui->lineEdit_dm->clear();
    ui->lineEdit_nutzl->clear();
    ui->lineEdit_zustma->clear();
    ui->comboBox_ausrichtung->clear();
    ui->comboBox_ausrichtung->addItem("vertikel");  //Index 0
    ui->comboBox_ausrichtung->addItem("horizontal");//Index 1
    ui->comboBox_drehricht->clear();
    ui->comboBox_drehricht->addItem("rechts");      //Index 0
    ui->comboBox_drehricht->addItem("links");       //Index 1
    loadwkzbild();
}

void Dialog_fraeser::on_pushButton_ok_clicked()
{
    if(ui->lineEdit_nr->text().isEmpty())
    {
        QMessageBox mb;
        mb.setText("Bitte zuerst eine Werkzeugnummer eingeben!");
        mb.exec();
        return;
    }
    QString msg = dialogDataToString();
    this->hide();
    if(openToModifyData)
    {
        openToModifyData = false;
        emit sendDialogDataModifyed(msg);
    } else
    {
        emit sendDialogData(msg);
    }
}

void Dialog_fraeser::on_pushButton_abbrechen_clicked()
{
    this->close();
}

void Dialog_fraeser::loadwkzbild()
{
    prgpfade pf;
    if(!ui->lineEdit_nr->text().isEmpty())
    {
        QString bild1;
        bild1  = pf.get_path_wkzbilder_();
        bild1 += ui->lineEdit_nr->text();
        bild1 += ".bmp";
        QFile file(bild1);
        if(file.exists())
        {
            QPixmap pix1(bild1);
            ui->label_bild->setPixmap(pix1);
        }else
        {
            bild1  = pf.get_path_dlgbilder_();
            bild1 += "fraeser_nopic.bmp";
            QPixmap pix1(bild1);
            ui->label_bild->setPixmap(pix1);
        }
        ui->label_bild->setScaledContents(true);//Bild skallieren
    }else
    {
        QString bild1;
        bild1  = pf.get_path_dlgbilder_();
        bild1 += "fraeser.bmp";
        QPixmap pix1(bild1);
        ui->label_bild->setPixmap(pix1);
        ui->label_bild->setScaledContents(true);//Bild skallieren
    }
}

QString Dialog_fraeser::dialogDataToString()
{
    wkz_fraeser wf;
    wf.set_name(ui->lineEdit_name->text());
    wf.set_nummer(ui->lineEdit_nr->text());
    wf.set_dm(ui->lineEdit_dm->text().replace(",","."));
    wf.set_nutzlaenge(ui->lineEdit_nutzl->text().replace(",","."));
    wf.set_zustellmas(ui->lineEdit_zustma->text().replace(",","."));
    QString tmp;
    tmp = ui->comboBox_ausrichtung->currentText();
    if(tmp == "vertikal")
    {
        wf.set_ausrichtung_vert(true);
    }else
    {
        wf.set_ausrichtung_hori(true);
    }
    tmp = ui->comboBox_drehricht->currentText();
    if(tmp == "rechts")
    {
        wf.set_drehrichtung_uzs(true);
    }else
    {
        wf.set_drehrichtung_uzs(false);
    }

    return wf.get_data();
}

void Dialog_fraeser::getDialogData(QString text, bool openToChangeData)
{
    clear();
    openToModifyData = openToChangeData;

    QString parname = FRAESER_NAME;
    if(text.contains(parname))
    {
        ui->lineEdit_name->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_NR;
    if(text.contains(parname))
    {
        ui->lineEdit_nr->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_DM;
    if(text.contains(parname))
    {
        ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    }
    parname = ENDPAR;
    parname += FRAESER_NUTZL;
    if(text.contains(parname))
    {
        ui->lineEdit_nutzl->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    }
    parname = ENDPAR;
    parname += FRAESER_ZUSTMAS;
    if(text.contains(parname))
    {
        ui->lineEdit_zustma->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    }
    parname = ENDPAR;
    parname += FRAESER_VERTIKAL;
    if(text.contains(parname))
    {
        QString tmp;
        tmp = selektiereEintrag(text, parname, ENDPAR);
        if(tmp == "1")
        {
            ui->comboBox_ausrichtung->setCurrentIndex(0);//vertikal
        }else
        {
            ui->comboBox_ausrichtung->setCurrentIndex(1);//horizontal
        }
    }
    parname = ENDPAR;
    parname += FRAESER_UZS;
    if(text.contains(parname))
    {
        QString tmp;
        tmp = selektiereEintrag(text, parname, ENDPAR);
        if(tmp == "1")
        {
            ui->comboBox_drehricht->setCurrentIndex(0);//rechts == im Uhrzeigersinn
        }else
        {
            ui->comboBox_drehricht->setCurrentIndex(1);//links == gegen den Uhrzeigersinn
        }
    }

    this->show();
}

void Dialog_fraeser::on_lineEdit_nr_textChanged()
{
    loadwkzbild();
}
