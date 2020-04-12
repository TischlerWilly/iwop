#include "dialog_loreima.h"
#include "ui_dialog_loreima.h"

Dialog_loreima::Dialog_loreima(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_loreima)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.path_dlgbilder_();
    bild1 += "loreima_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.path_dlgbilder_();
    bild2 += "loreima_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_loreima::~Dialog_loreima()
{
    delete ui;
}

void Dialog_loreima::on_pushButton_ok_clicked()
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

void Dialog_loreima::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_loreima::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_loreima::dialogDataToString()
{
    QString msg = DLG_LOREIMA ;

    msg += LOREIMA_XS;
    msg += ui->lineEdit_xs->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_XM;
    msg += ui->lineEdit_xm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_Y1;
    msg += ui->lineEdit_y1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_Y2;
    msg += ui->lineEdit_y2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_RASTER;
    msg += ui->lineEdit_raster->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_BOTI;
    msg += ui->lineEdit_boti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_DM;
    msg += ui->lineEdit_dm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_GRUPPE;
    msg += ui->lineEdit_grp->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_ANBOTI;
    msg += ui->lineEdit_anboti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_ANBOVO;
    msg += ui->lineEdit_anbovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_REBOMA;
    msg += ui->lineEdit_reboma->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_BOVO;
    msg += ui->lineEdit_bovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_ZSM;
    msg += ui->lineEdit_zsm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_DREHZ;
    msg += ui->lineEdit_n->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LOREIMA_MESSEI;
    msg += int_to_qstring(ui->spinBox_messei->value());
    msg += ENDPAR;

    msg += LOREIMA_TASATZ;
    msg += int_to_qstring(ui->spinBox_tasatz->value());
    msg += ENDPAR;

    msg += LOREIMA_PLM;
    msg += int_to_qstring(ui->spinBox_plm->value());
    msg += ENDPAR;

    msg += LOREIMA_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += LOREIMA_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_loreima::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = LOREIMA_XS;
    ui->lineEdit_xs->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_XM;
    ui->lineEdit_xm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_Y1;
    ui->lineEdit_y1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_Y2;
    ui->lineEdit_y2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_RASTER;
    ui->lineEdit_raster->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_BOTI;
    ui->lineEdit_boti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_DM;
    ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_GRUPPE;
    ui->lineEdit_grp->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_ANBOTI;
    ui->lineEdit_anboti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_ANBOVO;
    ui->lineEdit_anbovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_REBOMA;
    ui->lineEdit_reboma->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_BOVO;
    ui->lineEdit_bovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_ZSM;
    ui->lineEdit_zsm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_DREHZ;
    ui->lineEdit_n->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += LOREIMA_MESSEI;
    QString tmp;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_messei->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += LOREIMA_TASATZ;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_tasatz->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += LOREIMA_PLM;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_plm->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += LOREIMA_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += LOREIMA_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_loreima::get_default()
{
    QString msg;

    msg += LOREIMA_XS;
    msg += "";
    msg += ENDPAR;

    msg += LOREIMA_XM;
    msg += "";
    msg += ENDPAR;

    msg += LOREIMA_Y1;
    msg += "";
    msg += ENDPAR;

    msg += LOREIMA_Y2;
    msg += "";
    msg += ENDPAR;

    msg += LOREIMA_RASTER;
    msg += "32";
    msg += ENDPAR;

    msg += LOREIMA_BOTI;
    msg += "14";
    msg += ENDPAR;

    msg += LOREIMA_DM;
    msg += "5";
    msg += ENDPAR;

    msg += LOREIMA_GRUPPE;
    msg += "1";
    msg += ENDPAR;

    msg += LOREIMA_ANBOTI;
    msg += "4";
    msg += ENDPAR;

    msg += LOREIMA_ANBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += LOREIMA_REBOMA;
    msg += "4";
    msg += ENDPAR;

    msg += LOREIMA_BOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += LOREIMA_ZSM;
    msg += "5";
    msg += ENDPAR;

    msg += LOREIMA_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += LOREIMA_MESSEI;
    msg += "0";
    msg += ENDPAR;

    msg += LOREIMA_TASATZ;
    msg += "-1";
    msg += ENDPAR;

    msg += LOREIMA_PLM;
    msg += "0";
    msg += ENDPAR;

    msg += LOREIMA_BEZ;
    msg += "Lochreihe MA";
    msg += ENDPAR;

    msg += LOREIMA_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
