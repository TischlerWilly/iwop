#include "dialog_nut.h"
#include "ui_dialog_nut.h"

Dialog_nut::Dialog_nut(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_nut)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.get_path_dlgbilder_();
    bild1 += "nut_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.get_path_dlgbilder_();
    bild2 += "nut_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_nut::~Dialog_nut()
{
    delete ui;
}

void Dialog_nut::on_pushButton_ok_clicked()
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

void Dialog_nut::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_nut::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_nut::dialogDataToString()
{
    QString msg = DLG_NUT ;

    msg += NUT_WKZ;
    msg += ui->comboBox_wkz->currentText().replace("?", "");
    msg += ENDPAR;

    msg += NUT_SX;
    msg += ui->lineEdit_sx->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_SY;
    msg += ui->lineEdit_sy->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_EX;
    msg += ui->lineEdit_ex->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_EY;
    msg += ui->lineEdit_ey->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_TI;
    msg += ui->lineEdit_ti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_B;
    msg += ui->lineEdit_b->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_AUSLAUF;
    msg += ui->lineEdit_auslauf->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_KOR;
    msg += int_to_qstring(ui->spinBox_kor->value());
    msg += ENDPAR;

    msg += NUT_GEGENLAUF;
    msg += ui->lineEdit_gegenlauf->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_NWI;
    msg += ui->lineEdit_nwi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_NTYP;
    msg += int_to_qstring(ui->spinBox_ntyp->value());
    msg += ENDPAR;

    msg += NUT_NABST;
    msg += ui->lineEdit_nabst->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_Z;
    msg += ui->lineEdit_z->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_EINVO;
    msg += ui->lineEdit_einvo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_VO;
    msg += ui->lineEdit_vo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_DREHZ;
    msg += ui->lineEdit_drehz->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += NUT_PLM;
    msg += int_to_qstring(ui->spinBox_plm->value());
    msg += ENDPAR;

    msg += NUT_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += NUT_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_nut::update_wkzlist()
{
    emit signalNeedWKZ(DLG_NUT);
}

void Dialog_nut::getWKZlist(text_zeilenweise list)
{
    wkzlist = list;
    update_comboboxWKZ();
}

void Dialog_nut::update_comboboxWKZ()
{
    ui->comboBox_wkz->clear();
    for(uint i=1; i<= wkzlist.zeilenanzahl();i++)
    {
        ui->comboBox_wkz->addItem(wkzlist.zeile(i));
    }
}

void Dialog_nut::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    update_wkzlist();
    QString parname = NUT_WKZ;
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
    parname += NUT_SX;
    ui->lineEdit_sx->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_SY;
    ui->lineEdit_sy->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_EX;
    ui->lineEdit_ex->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_EY;
    ui->lineEdit_ey->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_TI;
    ui->lineEdit_ti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_B;
    ui->lineEdit_b->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_AUSLAUF;
    ui->lineEdit_auslauf->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_KOR;
    ui->spinBox_kor->setValue(selektiereEintrag(text, parname, ENDPAR).toInt());
    parname = ENDPAR;
    parname += NUT_GEGENLAUF;
    ui->lineEdit_gegenlauf->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_NWI;
    ui->lineEdit_nwi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_NTYP;
    ui->spinBox_ntyp->setValue(selektiereEintrag(text, parname, ENDPAR).toInt());
    parname = ENDPAR;
    parname += NUT_NABST;
    ui->lineEdit_nabst->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_Z;
    ui->lineEdit_z->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_EINVO;
    ui->lineEdit_einvo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_VO;
    ui->lineEdit_vo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_DREHZ;
    ui->lineEdit_drehz->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += NUT_PLM;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_plm->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += NUT_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += NUT_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_nut::get_default()
{
    QString msg;

    msg += NUT_WKZ;
    msg += "Saege- 425";
    msg += ENDPAR;

    msg += NUT_SX;
    msg += "L+50";
    msg += ENDPAR;

    msg += NUT_SY;
    msg += "50";
    msg += ENDPAR;

    msg += NUT_EX;
    msg += "-50";
    msg += ENDPAR;

    msg += NUT_EY;
    msg += "50";
    msg += ENDPAR;

    msg += NUT_TI;
    msg += "6.5";
    msg += ENDPAR;

    msg += NUT_B;
    msg += "8.5";
    msg += ENDPAR;

    msg += NUT_AUSLAUF;
    msg += "0";
    msg += ENDPAR;

    msg += NUT_KOR;
    msg += "0";
    msg += ENDPAR;

    msg += NUT_GEGENLAUF;
    msg += "0";
    msg += ENDPAR;

    msg += NUT_NWI;
    msg += "0";
    msg += ENDPAR;

    msg += NUT_NTYP;
    msg += "1";
    msg += ENDPAR;

    msg += NUT_NABST;
    msg += "10";
    msg += ENDPAR;

    msg += NUT_Z;
    msg += "D/2";
    msg += ENDPAR;

    msg += NUT_EINVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += NUT_VO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += NUT_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += NUT_PLM;
    msg += "0";
    msg += ENDPAR;

    msg += NUT_BEZ;
    msg += "Nut";
    msg += ENDPAR;

    msg += NUT_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
