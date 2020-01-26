#include "dialog_topf.h"
#include "ui_dialog_topf.h"

Dialog_topf::Dialog_topf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_topf)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.get_path_dlgbilder_();
    bild1 += "topf_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.get_path_dlgbilder_();
    bild2 += "topf_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_topf::~Dialog_topf()
{
    delete ui;
}

void Dialog_topf::on_pushButton_ok_clicked()
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

void Dialog_topf::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_topf::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_topf::dialogDataToString()
{
    QString msg = DLG_TOPF ;

    msg += TOPF_TA;
    msg += ui->lineEdit_ta->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_A1;
    msg += ui->lineEdit_a1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_A2;
    msg += ui->lineEdit_a2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_A3;
    msg += ui->lineEdit_a3->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_A4;
    msg += ui->lineEdit_a4->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_A5;
    msg += ui->lineEdit_a5->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_MA;
    msg += ui->lineEdit_ma->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_MB;
    msg += ui->lineEdit_mb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_KETTE;
    msg += ui->lineEdit_kette->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_GRUPPE;
    msg += ui->lineEdit_grp->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_SEITE;
    msg += int_to_qstring(ui->spinBox_seite->value());
    msg += ENDPAR;

    msg += TOPF_MESSEI;
    msg += int_to_qstring(ui->spinBox_messei->value());
    msg += ENDPAR;

    msg += TOPF_BODM;
    msg += ui->lineEdit_bodm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_TODM;
    msg += ui->lineEdit_todm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_BOTI;
    msg += ui->lineEdit_boti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_WKZ;
    msg += ui->lineEdit_wkz->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_TOTI;
    msg += ui->lineEdit_toti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_ANBOTI;
    msg += ui->lineEdit_anboti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_BOANBOVO;
    msg += ui->lineEdit_boanbovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_TOANBOVO;
    msg += ui->lineEdit_toanbovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_REBOMA;
    msg += ui->lineEdit_reboma->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_BOBOVO;
    msg += ui->lineEdit_bobovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_TOBOVO;
    msg += ui->lineEdit_tobovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_BOZSM;
    msg += ui->lineEdit_bozsm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_DREHZ;
    msg += ui->lineEdit_n->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += TOPF_PLM;
    msg += int_to_qstring(ui->spinBox_plm->value());
    msg += ENDPAR;

    msg += TOPF_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += TOPF_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_topf::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = TOPF_TA;
    ui->lineEdit_ta->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_A1;
    ui->lineEdit_a1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_A2;
    ui->lineEdit_a2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_A3;
    ui->lineEdit_a3->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_A4;
    ui->lineEdit_a4->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_A5;
    ui->lineEdit_a5->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_MA;
    ui->lineEdit_ma->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_MB;
    ui->lineEdit_mb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_KETTE;
    ui->lineEdit_kette->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_GRUPPE;
    ui->lineEdit_grp->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    QString tmp;
    parname = ENDPAR;
    parname += TOPF_SEITE;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_seite->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += TOPF_MESSEI;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_messei->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += TOPF_BODM;
    ui->lineEdit_bodm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_TODM;
    ui->lineEdit_todm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_BOTI;
    ui->lineEdit_boti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_WKZ;
    ui->lineEdit_wkz->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_TOTI;
    ui->lineEdit_toti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_ANBOTI;
    ui->lineEdit_anboti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_BOANBOVO;
    ui->lineEdit_boanbovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_TOANBOVO;
    ui->lineEdit_toanbovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_REBOMA;
    ui->lineEdit_reboma->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_BOBOVO;
    ui->lineEdit_bobovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_TOBOVO;
    ui->lineEdit_tobovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_BOZSM;
    ui->lineEdit_bozsm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_DREHZ;
    ui->lineEdit_n->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += TOPF_PLM;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_plm->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += TOPF_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += TOPF_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_topf::get_default()
{
    QString msg;

    msg += TOPF_TA;
    msg += "";
    msg += ENDPAR;

    msg += TOPF_A1;
    msg += "100";
    msg += ENDPAR;

    msg += TOPF_A2;
    msg += "L-100";
    msg += ENDPAR;

    msg += TOPF_A3;
    msg += "";
    msg += ENDPAR;

    msg += TOPF_A4;
    msg += "";
    msg += ENDPAR;

    msg += TOPF_A5;
    msg += "";
    msg += ENDPAR;

    msg += TOPF_MA;
    msg += "";
    msg += ENDPAR;

    msg += TOPF_MB;
    msg += "";
    msg += ENDPAR;

    msg += TOPF_KETTE;
    msg += "0";
    msg += ENDPAR;

    msg += TOPF_GRUPPE;
    msg += "1";
    msg += ENDPAR;

    msg += TOPF_SEITE;
    msg += "1";
    msg += ENDPAR;

    msg += TOPF_MESSEI;
    msg += "0";
    msg += ENDPAR;

    msg += TOPF_BODM;
    msg += "5";
    msg += ENDPAR;

    msg += TOPF_TODM;
    msg += "35.3";
    msg += ENDPAR;

    msg += TOPF_BOTI;
    msg += "2";
    msg += ENDPAR;

    msg += TOPF_WKZ;
    msg += "602";
    msg += ENDPAR;

    msg += TOPF_TOTI;
    msg += "15";
    msg += ENDPAR;

    msg += TOPF_ANBOTI;
    msg += "4";
    msg += ENDPAR;

    msg += TOPF_BOANBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += TOPF_TOANBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += TOPF_REBOMA;
    msg += "4";
    msg += ENDPAR;

    msg += TOPF_BOBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += TOPF_TOBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += TOPF_BOZSM;
    msg += "5";
    msg += ENDPAR;

    msg += TOPF_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += TOPF_PLM;
    msg += "0";
    msg += ENDPAR;

    msg += TOPF_BEZ;
    msg += "Topfband";
    msg += ENDPAR;

    msg += TOPF_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
