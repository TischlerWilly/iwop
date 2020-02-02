#include "dialog_kta.h"
#include "ui_dialog_kta.h"

Dialog_kta::Dialog_kta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_kta)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.get_path_dlgbilder_();
    bild1 += "kta_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.get_path_dlgbilder_();
    bild2 += "kta_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_kta::~Dialog_kta()
{
    delete ui;
}

void Dialog_kta::on_pushButton_ok_clicked()
{
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

void Dialog_kta::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_kta::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_kta::dialogDataToString()
{
    QString msg = DLG_KTA ;

    msg += KTA_WKZ;
    msg += ui->comboBox_wkz->currentText().replace("?", "");
    msg += ENDPAR;

    msg += KTA_X;
    msg += ui->lineEdit_x->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += KTA_Y;
    msg += ui->lineEdit_y->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += KTA_DM;
    msg += ui->lineEdit_dm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += KTA_TI;
    msg += ui->lineEdit_ti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += KTA_ZUST;
    msg += ui->lineEdit_zust->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += KTA_GEGENL;
    msg += ui->lineEdit_gegenlauf->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += KTA_AUSR;
    msg += ui->lineEdit_ausr->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += KTA_EINVO;
    msg += ui->lineEdit_einvo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += KTA_VO;
    msg += ui->lineEdit_vo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += KTA_DREHZ;
    msg += ui->lineEdit_drehz->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += KTA_PLM;
    msg += int_to_qstring(ui->spinBox_plm->value());
    msg += ENDPAR;

    msg += KTA_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += KTA_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_kta::update_wkzlist()
{
    emit signalNeedWKZ(DLG_KTA);
}

void Dialog_kta::getWKZlist(text_zeilenweise list)
{
    wkzlist = list;
    update_comboboxWKZ();
}

void Dialog_kta::update_comboboxWKZ()
{
    ui->comboBox_wkz->clear();
    for(uint i=1; i<= wkzlist.zeilenanzahl();i++)
    {
        ui->comboBox_wkz->addItem(wkzlist.zeile(i));
    }
}

void Dialog_kta::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    update_wkzlist();
    QString parname = KTA_WKZ;
    QString tmp;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    //Werkzeug einsetzen:
    uint wkzindex = 0;
    for(uint i=1; i<= wkzlist.zeilenanzahl();i++)
    {
        if(tmp == wkzlist.zeile(i))
        {
            wkzindex = i;
        }
    }
    if(wkzindex > 0)
    {
        ui->comboBox_wkz->setCurrentIndex(wkzindex-1);
    }else
    {
        update_comboboxWKZ();
        ui->comboBox_wkz->addItem(tmp + "???");
        ui->comboBox_wkz->setCurrentIndex(wkzlist.zeilenanzahl());
    }

    parname = ENDPAR;
    parname += KTA_X;
    ui->lineEdit_x->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += KTA_Y;
    ui->lineEdit_y->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += KTA_DM;
    ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += KTA_TI;
    ui->lineEdit_ti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += KTA_ZUST;
    ui->lineEdit_zust->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += KTA_GEGENL;
    ui->lineEdit_gegenlauf->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += KTA_AUSR;
    ui->lineEdit_ausr->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += KTA_EINVO;
    ui->lineEdit_einvo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += KTA_VO;
    ui->lineEdit_vo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += KTA_DREHZ;
    ui->lineEdit_drehz->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += KTA_PLM;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_plm->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += KTA_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += KTA_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_kta::get_default()
{
    QString msg;

    msg += KTA_WKZ;
    msg += "IMA 602";
    msg += ENDPAR;

    msg += KTA_X;
    msg += "";
    msg += ENDPAR;

    msg += KTA_Y;
    msg += "";
    msg += ENDPAR;

    msg += KTA_DM;
    msg += "50";
    msg += ENDPAR;

    msg += KTA_TI;
    msg += "5";
    msg += ENDPAR;

    msg += KTA_ZUST;
    msg += "0";
    msg += ENDPAR;

    msg += KTA_GEGENL;
    msg += "1";
    msg += ENDPAR;

    msg += KTA_AUSR;
    msg += "1";
    msg += ENDPAR;

    msg += KTA_EINVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += KTA_VO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += KTA_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += KTA_PLM;
    msg += "0";
    msg += ENDPAR;

    msg += KTA_BEZ;
    msg += "Kreistasche";
    msg += ENDPAR;

    msg += KTA_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
