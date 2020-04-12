#include "dialog_saege.h"
#include "ui_dialog_saege.h"

Dialog_saege::Dialog_saege(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_saege)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);
    clear();
}

Dialog_saege::~Dialog_saege()
{
    delete ui;
}

void Dialog_saege::clear()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_nr->clear();
    ui->lineEdit_dm->clear();
    ui->lineEdit_breite->clear();
    ui->comboBox_ausrichtung->clear();
    ui->comboBox_ausrichtung->addItem("vertikel");  //Index 0
    ui->comboBox_ausrichtung->addItem("horizontal");//Index 1
    loadwkzbild();
}

void Dialog_saege::on_pushButton_ok_clicked()
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

void Dialog_saege::on_pushButton_abbrechen_clicked()
{
    this->close();
}

void Dialog_saege::loadwkzbild()
{
    prgpfade pf;
    if(!ui->lineEdit_nr->text().isEmpty())
    {
        QString bild1;
        bild1  = pf.path_wkzbilder_();
        bild1 += ui->lineEdit_nr->text();
        bild1 += ".bmp";
        QFile file(bild1);
        if(file.exists())
        {
            QPixmap pix1(bild1);
            ui->label_bild->setPixmap(pix1);
        }else
        {
            bild1  = pf.path_dlgbilder_();
            bild1 += "saege_nopic.bmp";
            QPixmap pix1(bild1);
            ui->label_bild->setPixmap(pix1);
        }
        ui->label_bild->setScaledContents(true);//Bild skallieren
    }else
    {
        QString bild1;
        bild1  = pf.path_dlgbilder_();
        bild1 += "saege.bmp";
        QPixmap pix1(bild1);
        ui->label_bild->setPixmap(pix1);
        ui->label_bild->setScaledContents(true);//Bild skallieren
    }
}

void Dialog_saege::on_lineEdit_nr_textChanged()
{
    loadwkzbild();
}

QString Dialog_saege::dialogDataToString()
{
    wkz_saege ws;
    ws.set_name(ui->lineEdit_name->text());
    ws.set_nummer(ui->lineEdit_nr->text());
    ws.set_dm(ui->lineEdit_dm->text().replace(",","."));
    ws.set_breite(ui->lineEdit_breite->text().replace(",","."));
    QString tmp;
    tmp = ui->comboBox_ausrichtung->currentText();
    if(tmp == "vertikal")
    {
        ws.set_ausrichtung_vert(true);
    }else
    {
        ws.set_ausrichtung_hori(true);
    }

    return ws.text();
}

void Dialog_saege::getDialogData(QString text, bool openToChangeData)
{
    clear();
    openToModifyData = openToChangeData;

    QString parname = SAEGE_NAME;
    if(text.contains(parname))
    {
        ui->lineEdit_name->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += SAEGE_NR;
    if(text.contains(parname))
    {
        ui->lineEdit_nr->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += SAEGE_DM;
    if(text.contains(parname))
    {
        ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    }
    parname = ENDPAR;
    parname += SAEGE_BREITE;
    if(text.contains(parname))
    {
        ui->lineEdit_breite->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    }
    parname = ENDPAR;
    parname += SAEGE_VERTIKAL;
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
    this->show();
}
