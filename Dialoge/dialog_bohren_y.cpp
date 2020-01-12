#include "dialog_bohren_y.h"
#include "ui_dialog_bohren_y.h"

Dialog_bohren_y::Dialog_bohren_y(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bohren_y)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.get_path_dlgbilder_();
    bild1 += "boY_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.get_path_dlgbilder_();
    bild2 += "boY_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_bohren_y::~Dialog_bohren_y()
{
    delete ui;
}

void Dialog_bohren_y::on_pushButton_ok_clicked()
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

void Dialog_bohren_y::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_bohren_y::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_bohren_y::dialogDataToString()
{
    QString msg = DLG_BOY ;

    msg += BOY_X;
    msg += ui->lineEdit_x1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_X2;
    msg += ui->lineEdit_x2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_Y1;
    msg += ui->lineEdit_y1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_Y2;
    msg += ui->lineEdit_y2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_Y3;
    msg += ui->lineEdit_y3->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_Y4;
    msg += ui->lineEdit_y4->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_Y5;
    msg += ui->lineEdit_y5->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_Y6;
    msg += ui->lineEdit_y6->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_BOTI;
    msg += ui->lineEdit_boti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_DM;
    msg += ui->lineEdit_dm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_KETTE;
    msg += ui->lineEdit_kette->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_GRUPPE;
    msg += ui->lineEdit_grp->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_ANBOTI;
    msg += ui->lineEdit_anboti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_ANBOVO;
    msg += ui->lineEdit_anbovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_REBOMA;
    msg += ui->lineEdit_reboma->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_BOVO;
    msg += ui->lineEdit_bovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_ZSM;
    msg += ui->lineEdit_zsm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_DREHZ;
    msg += ui->lineEdit_n->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOY_MESSEI;
    msg += int_to_qstring(ui->spinBox_messei->value());
    msg += ENDPAR;

    msg += BOY_TASATZ;
    msg += int_to_qstring(ui->spinBox_tasatz->value());
    msg += ENDPAR;

    msg += BOY_PLM;
    msg += int_to_qstring(ui->spinBox_plm->value());
    msg += ENDPAR;

    msg += BOY_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += BOY_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_bohren_y::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = BOY_X;
    ui->lineEdit_x1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_X2;
    ui->lineEdit_x2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_Y1;
    ui->lineEdit_y1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_Y2;
    ui->lineEdit_y2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_Y3;
    ui->lineEdit_y3->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_Y4;
    ui->lineEdit_y4->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_Y5;
    ui->lineEdit_y5->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_Y6;
    ui->lineEdit_y6->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_BOTI;
    ui->lineEdit_boti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_DM;
    ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_KETTE;
    ui->lineEdit_kette->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_GRUPPE;
    ui->lineEdit_grp->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_ANBOTI;
    ui->lineEdit_anboti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_ANBOVO;
    ui->lineEdit_anbovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_REBOMA;
    ui->lineEdit_reboma->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_BOVO;
    ui->lineEdit_bovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_ZSM;
    ui->lineEdit_zsm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOY_DREHZ;
    ui->lineEdit_n->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    QString tmp;
    parname = ENDPAR;
    parname += BOY_MESSEI;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_messei->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += BOY_TASATZ;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_tasatz->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += BOY_PLM;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_plm->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += BOY_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += BOY_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_bohren_y::get_default()
{
    QString msg;

    msg += BOY_X;
    msg += "0";
    msg += ENDPAR;

    msg += BOY_X2;
    msg += "-1";
    msg += ENDPAR;

    msg += BOY_Y1;
    msg += "0";
    msg += ENDPAR;

    msg += BOY_Y2;
    msg += "";
    msg += ENDPAR;

    msg += BOY_Y3;
    msg += "";
    msg += ENDPAR;

    msg += BOY_Y4;
    msg += "";
    msg += ENDPAR;

    msg += BOY_Y5;
    msg += "";
    msg += ENDPAR;

    msg += BOY_Y6;
    msg += "";
    msg += ENDPAR;

    msg += BOY_BOTI;
    msg += "2";
    msg += ENDPAR;

    msg += BOY_DM;
    msg += "5";
    msg += ENDPAR;

    msg += BOY_KETTE;
    msg += "0";
    msg += ENDPAR;

    msg += BOY_GRUPPE;
    msg += "1";
    msg += ENDPAR;

    msg += BOY_ANBOTI;
    msg += "4";
    msg += ENDPAR;

    msg += BOY_ANBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += BOY_REBOMA;
    msg += "4";
    msg += ENDPAR;

    msg += BOY_BOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += BOY_ZSM;
    msg += "5";
    msg += ENDPAR;

    msg += BOY_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += BOY_MESSEI;
    msg += "0";
    msg += ENDPAR;

    msg += BOY_TASATZ;
    msg += "-1";
    msg += ENDPAR;

    msg += BOY_PLM;
    msg += "0";
    msg += ENDPAR;

    msg += BOY_BEZ;
    msg += "Bohren in Y";
    msg += ENDPAR;

    msg += BOY_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
