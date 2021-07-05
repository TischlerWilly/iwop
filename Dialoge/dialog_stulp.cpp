#include "dialog_stulp.h"
#include "ui_dialog_stulp.h"

Dialog_stulp::Dialog_stulp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_stulp)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.path_dlgbilder_();
    bild1 += "stulp_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.path_dlgbilder_();
    bild2 += "stulp_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_stulp::~Dialog_stulp()
{
    delete ui;
}

void Dialog_stulp::on_pushButton_ok_clicked()
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

void Dialog_stulp::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_stulp::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_stulp::dialogDataToString()
{
    QString msg = DLG_STULP ;

    msg += STULP_WKZ;
    msg += ui->comboBox_wkz->currentText().replace("?", "");
    msg += ENDPAR;

    msg += STULP_X;
    msg += ui->lineEdit_x->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_Y;
    msg += ui->lineEdit_y->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_Z;
    msg += ui->lineEdit_z->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_L;
    msg += ui->lineEdit_l->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_B;
    msg += ui->lineEdit_b->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_TI;
    msg += ui->lineEdit_ti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_RAD;
    msg += ui->lineEdit_rad->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_FALZVERSATZ;
    msg += ui->lineEdit_falzversatz->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_ZUST;
    msg += ui->lineEdit_zust->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_GEGENL;
    msg += ui->lineEdit_gegenl->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_SEITE;
    msg += int_to_qstring(ui->spinBox_seite->value());
    msg += ENDPAR;

    msg += STULP_EINVO;
    msg += ui->lineEdit_einvo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_VO;
    msg += ui->lineEdit_vo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_DREHZ;
    msg += ui->lineEdit_drehz->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += STULP_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += STULP_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_stulp::update_wkzlist()
{
    emit signalNeedWKZ(DLG_STULP);
}

void Dialog_stulp::getWKZlist(text_zeilenweise list)
{
    wkzlist = list;
    update_comboboxWKZ();
}

void Dialog_stulp::update_comboboxWKZ()
{
    ui->comboBox_wkz->clear();
    for(uint i=1; i<= wkzlist.zeilenanzahl();i++)
    {
        ui->comboBox_wkz->addItem(wkzlist.zeile(i));
    }
}

void Dialog_stulp::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    update_wkzlist();
    QString parname = STULP_WKZ;
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
    parname += STULP_X;
    ui->lineEdit_x->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_Y;
    ui->lineEdit_y->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_Z;
    ui->lineEdit_z->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_L;
    ui->lineEdit_l->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_B;
    ui->lineEdit_b->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_TI;
    ui->lineEdit_ti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_RAD;
    ui->lineEdit_rad->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_FALZVERSATZ;
    ui->lineEdit_falzversatz->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_ZUST;
    ui->lineEdit_zust->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_GEGENL;
    ui->lineEdit_gegenl->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_SEITE;
    ui->spinBox_seite->setValue(selektiereEintrag(text, parname, ENDPAR).toInt());
    parname = ENDPAR;
    parname += STULP_EINVO;
    ui->lineEdit_einvo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_VO;
    ui->lineEdit_vo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_DREHZ;
    ui->lineEdit_drehz->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += STULP_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += STULP_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_stulp::get_default()
{
    QString msg;

    msg += STULP_WKZ;
    msg += "IMA 4354";
    msg += ENDPAR;

    msg += STULP_X;
    msg += "";
    msg += ENDPAR;

    msg += STULP_Y;
    msg += "";
    msg += ENDPAR;

    msg += STULP_Z;
    msg += "";
    msg += ENDPAR;

    msg += STULP_L;
    msg += "";
    msg += ENDPAR;

    msg += STULP_B;
    msg += "";
    msg += ENDPAR;

    msg += STULP_TI;
    msg += "5";
    msg += ENDPAR;

    msg += STULP_RAD;
    msg += "0";
    msg += ENDPAR;

    msg += STULP_FALZVERSATZ;
    msg += "0";
    msg += ENDPAR;

    msg += STULP_ZUST;
    msg += "0";
    msg += ENDPAR;

    msg += STULP_GEGENL;
    msg += "1";
    msg += ENDPAR;

    msg += STULP_SEITE;
    msg += "1";
    msg += ENDPAR;

    msg += STULP_EINVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += STULP_VO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += STULP_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += STULP_BEZ;
    msg += "Stulp";
    msg += ENDPAR;

    msg += STULP_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}









