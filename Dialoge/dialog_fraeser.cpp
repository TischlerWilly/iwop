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
    ui->comboBox_ausrichtung->addItem("vertikal");  //Index 0
    ui->comboBox_ausrichtung->addItem("horizontal");//Index 1
    ui->comboBox_drehricht->clear();
    ui->comboBox_drehricht->addItem("rechts");      //Index 0
    ui->comboBox_drehricht->addItem("links");       //Index 1
    ui->lineEdit_spiegelnr->clear();
    ui->lineEdit_use_for->clear();
    ui->lineEdit_not_use_for->clear();
    ui->lineEdit_besonderheiten->clear();
    ui->lineEdit_schneidenanz->clear();
    ui->lineEdit_kleingenform->clear();
    ui->lineEdit_klingenart->clear();
    ui->lineEdit_vo->clear();
    ui->lineEdit_anvo->clear();
    ui->lineEdit_drehz->clear();
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
            bild1 += "fraeser_nopic.bmp";
            QPixmap pix1(bild1);
            ui->label_bild->setPixmap(pix1);
        }
        ui->label_bild->setScaledContents(true);//Bild skallieren
    }else
    {
        QString bild1;
        bild1  = pf.path_dlgbilder_();
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
    wf.set_spiegelwkznr(ui->lineEdit_spiegelnr->text());
    wf.set_use_for(ui->lineEdit_use_for->text());
    wf.set_not_use_for(ui->lineEdit_not_use_for->text());
    wf.set_besonderheiten(ui->lineEdit_besonderheiten->text());
    wf.set_schneidenanz(ui->lineEdit_schneidenanz->text());
    wf.set_klingenform(ui->lineEdit_kleingenform->text());
    wf.set_klingenart(ui->lineEdit_klingenart->text());
    wf.set_vorschub(ui->lineEdit_vo->text());
    wf.set_anfahrvorschub(ui->lineEdit_anvo->text());
    wf.set_drehzahl(ui->lineEdit_drehz->text());

    return wf.text();
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
    parname = ENDPAR;
    parname += FRAESER_SPIEGELNR;
    if(text.contains(parname))
    {
        ui->lineEdit_spiegelnr->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_USE_FOR;
    if(text.contains(parname))
    {
        ui->lineEdit_use_for->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_NOT_USE_FOR;
    if(text.contains(parname))
    {
        ui->lineEdit_not_use_for->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_BESONDERH;
    if(text.contains(parname))
    {
        ui->lineEdit_besonderheiten->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_SCHNEIDENANZ;
    if(text.contains(parname))
    {
        ui->lineEdit_schneidenanz->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_KLINGENFORM;
    if(text.contains(parname))
    {
        ui->lineEdit_kleingenform->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_KLINGENART;
    if(text.contains(parname))
    {
        ui->lineEdit_klingenart->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_VO;
    if(text.contains(parname))
    {
        ui->lineEdit_vo->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_ANVO;
    if(text.contains(parname))
    {
        ui->lineEdit_anvo->setText(selektiereEintrag(text, parname, ENDPAR));
    }
    parname = ENDPAR;
    parname += FRAESER_DREHZ;
    if(text.contains(parname))
    {
        ui->lineEdit_drehz->setText(selektiereEintrag(text, parname, ENDPAR));
    }

    this->show();
}

void Dialog_fraeser::on_lineEdit_nr_textChanged()
{
    loadwkzbild();
}
