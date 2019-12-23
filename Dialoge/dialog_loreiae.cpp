#include "dialog_loreiae.h"
#include "ui_dialog_loreiae.h"

Dialog_loreiae::Dialog_loreiae(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_loreiae)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    QString bild1;
    bild1  = PFAD_DLGBILDER;
    bild1 += QDir::separator();
    bild1 += "loreiae_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2;
    bild2  = PFAD_DLGBILDER;
    bild2 += QDir::separator();
    bild2 += "loreiae_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_loreiae::~Dialog_loreiae()
{
    delete ui;
}

void Dialog_loreiae::on_pushButton_ok_clicked()
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

void Dialog_loreiae::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_loreiae::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_loreiae::dialogDataToString()
{
    QString msg = DLG_LOREIAE ;

    msg += LOREIAE_XS;
    msg += ui->lineEdit_xs->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_XE;
    msg += ui->lineEdit_xe->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_Y1;
    msg += ui->lineEdit_y1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_Y2;
    msg += ui->lineEdit_y2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_YE;
    msg += ui->lineEdit_ye->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_RASTER;
    msg += ui->lineEdit_raster->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_BOTI;
    msg += ui->lineEdit_boti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_DM;
    msg += ui->lineEdit_dm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_GRUPPE;
    msg += ui->lineEdit_grp->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_VERMIT;
    msg += int_to_qstring(ui->spinBox_vermit->value());
    msg += ENDPAR;

    msg += LOREIAE_ANBOTI;
    msg += ui->lineEdit_anboti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_ANBOVO;
    msg += ui->lineEdit_anbovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_REBOMA;
    msg += ui->lineEdit_reboma->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_BOVO;
    msg += ui->lineEdit_bovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_ZSM;
    msg += ui->lineEdit_zsm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_DREHZ;
    msg += ui->lineEdit_n->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIAE_MESSEI;
    msg += int_to_qstring(ui->spinBox_messei->value());
    msg += ENDPAR;

    msg += LOREIAE_TASATZ;
    msg += int_to_qstring(ui->spinBox_tasatz->value());
    msg += ENDPAR;

    msg += LOREIAE_PLM;
    msg += int_to_qstring(ui->spinBox_plm->value());
    msg += ENDPAR;

    msg += LOREIAE_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += LOREIAE_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_loreiae::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = LOREIAE_XS;
    ui->lineEdit_xs->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_XE;
    ui->lineEdit_xe->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_Y1;
    ui->lineEdit_y1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_Y2;
    ui->lineEdit_y2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_YE;
    ui->lineEdit_ye->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_RASTER;
    ui->lineEdit_raster->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_BOTI;
    ui->lineEdit_boti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_DM;
    ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_GRUPPE;
    ui->lineEdit_grp->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_VERMIT;
    QString tmp;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_vermit->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += LOREIAE_ANBOTI;
    ui->lineEdit_anboti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_ANBOVO;
    ui->lineEdit_anbovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_REBOMA;
    ui->lineEdit_reboma->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_BOVO;
    ui->lineEdit_bovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_ZSM;
    ui->lineEdit_zsm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_DREHZ;
    ui->lineEdit_n->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIAE_MESSEI;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_messei->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += LOREIAE_TASATZ;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_tasatz->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += LOREIAE_PLM;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_plm->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += LOREIAE_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += LOREIAE_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_loreiae::get_default()
{
    QString msg;

    msg += LOREIAE_XS;
    msg += "";
    msg += ENDPAR;

    msg += LOREIAE_XE;
    msg += "";
    msg += ENDPAR;

    msg += LOREIAE_Y1;
    msg += "";
    msg += ENDPAR;

    msg += LOREIAE_Y2;
    msg += "";
    msg += ENDPAR;

    msg += LOREIAE_YE;
    msg += "Y1";
    msg += ENDPAR;

    msg += LOREIAE_RASTER;
    msg += "32";
    msg += ENDPAR;

    msg += LOREIAE_BOTI;
    msg += "14";
    msg += ENDPAR;

    msg += LOREIAE_DM;
    msg += "5";
    msg += ENDPAR;

    msg += LOREIAE_GRUPPE;
    msg += "1";
    msg += ENDPAR;

    msg += LOREIAE_VERMIT;
    msg += "0";
    msg += ENDPAR;

    msg += LOREIAE_ANBOTI;
    msg += "4";
    msg += ENDPAR;

    msg += LOREIAE_ANBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += LOREIAE_REBOMA;
    msg += "4";
    msg += ENDPAR;

    msg += LOREIAE_BOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += LOREIAE_ZSM;
    msg += "5";
    msg += ENDPAR;

    msg += LOREIAE_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += LOREIAE_MESSEI;
    msg += "0";
    msg += ENDPAR;

    msg += LOREIAE_TASATZ;
    msg += "-1";
    msg += ENDPAR;

    msg += LOREIAE_PLM;
    msg += "0";
    msg += ENDPAR;

    msg += LOREIAE_BEZ;
    msg += "Lochreihe AE";
    msg += ENDPAR;

    msg += LOREIAE_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
