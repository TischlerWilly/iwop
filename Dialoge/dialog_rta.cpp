#include "dialog_rta.h"
#include "ui_dialog_rta.h"

Dialog_rta::Dialog_rta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_rta)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.get_path_dlgbilder_();
    bild1 += "rta_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.get_path_dlgbilder_();
    bild2 += "rta_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_rta::~Dialog_rta()
{
    delete ui;
}

void Dialog_rta::on_pushButton_ok_clicked()
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

void Dialog_rta::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_rta::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_rta::dialogDataToString()
{
    QString msg = DLG_RTA ;

    msg += RTA_WKZ;
    msg += ui->comboBox_wkz->currentText().replace("?", "");
    msg += ENDPAR;

    msg += RTA_X;
    msg += ui->lineEdit_x->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_Y;
    msg += ui->lineEdit_y->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_L;
    msg += ui->lineEdit_l->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_B;
    msg += ui->lineEdit_b->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_TI;
    msg += ui->lineEdit_ti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_RAD;
    msg += ui->lineEdit_rad->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_ZUST;
    msg += ui->lineEdit_zust->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_GEGENL;
    msg += ui->lineEdit_gegenlauf->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_WI;
    msg += ui->lineEdit_wi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_AUSR;
    msg += ui->lineEdit_ausr->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_EINVO;
    msg += ui->lineEdit_einvo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_VO;
    msg += ui->lineEdit_vo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_DREHZ;
    msg += ui->lineEdit_drehz->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += RTA_PLM;
    msg += int_to_qstring(ui->spinBox_plm->value());
    msg += ENDPAR;

    msg += RTA_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += RTA_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_rta::update_wkzlist()
{
    emit signalNeedWKZ(DLG_RTA);
}

void Dialog_rta::getWKZlist(text_zeilenweise list)
{
    wkzlist = list;
    update_comboboxWKZ();
}

void Dialog_rta::update_comboboxWKZ()
{
    ui->comboBox_wkz->clear();
    for(uint i=1; i<= wkzlist.zeilenanzahl();i++)
    {
        ui->comboBox_wkz->addItem(wkzlist.zeile(i));
    }
}

void Dialog_rta::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    update_wkzlist();
    QString parname = RTA_WKZ;
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
    parname += RTA_X;
    ui->lineEdit_x->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_Y;
    ui->lineEdit_y->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_L;
    ui->lineEdit_l->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_B;
    ui->lineEdit_b->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_TI;
    ui->lineEdit_ti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_RAD;
    ui->lineEdit_rad->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_ZUST;
    ui->lineEdit_zust->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_GEGENL;
    ui->lineEdit_gegenlauf->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_WI;
    ui->lineEdit_wi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_AUSR;
    ui->lineEdit_ausr->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_EINVO;
    ui->lineEdit_einvo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_VO;
    ui->lineEdit_vo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_DREHZ;
    ui->lineEdit_drehz->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += RTA_PLM;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_plm->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += RTA_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += RTA_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_rta::get_default()
{
    QString msg;

    msg += RTA_WKZ;
    msg += "IMA602";
    msg += ENDPAR;

    msg += RTA_X;
    msg += "";
    msg += ENDPAR;

    msg += RTA_Y;
    msg += "";
    msg += ENDPAR;

    msg += RTA_L;
    msg += "";
    msg += ENDPAR;

    msg += RTA_B;
    msg += "";
    msg += ENDPAR;

    msg += RTA_TI;
    msg += "5";
    msg += ENDPAR;

    msg += RTA_RAD;
    msg += "0";
    msg += ENDPAR;

    msg += RTA_ZUST;
    msg += "0";
    msg += ENDPAR;

    msg += RTA_GEGENL;
    msg += "1";
    msg += ENDPAR;

    msg += RTA_WI;
    msg += "0";
    msg += ENDPAR;

    msg += RTA_AUSR;
    msg += "1";
    msg += ENDPAR;

    msg += RTA_EINVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += RTA_VO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += RTA_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += RTA_PLM;
    msg += "0";
    msg += ENDPAR;

    msg += RTA_BEZ;
    msg += "Rechtecktasche";
    msg += ENDPAR;

    msg += RTA_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}

