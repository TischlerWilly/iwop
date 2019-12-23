#include "dialog_bohren_x.h"
#include "ui_dialog_bohren_x.h"

Dialog_bohren_x::Dialog_bohren_x(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bohren_x)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    QString bild1;
    bild1  = PFAD_DLGBILDER;
    bild1 += QDir::separator();
    bild1 += "boX_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2;
    bild2  = PFAD_DLGBILDER;
    bild2 += QDir::separator();
    bild2 += "boX_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_bohren_x::~Dialog_bohren_x()
{
    delete ui;
}

void Dialog_bohren_x::on_pushButton_ok_clicked()
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

void Dialog_bohren_x::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_bohren_x::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_bohren_x::dialogDataToString()
{
    QString msg = DLG_BOX ;

    msg += BOX_Y;
    msg += ui->lineEdit_y1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_Y2;
    msg += ui->lineEdit_y2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_X1;
    msg += ui->lineEdit_x1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_X2;
    msg += ui->lineEdit_x2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_X3;
    msg += ui->lineEdit_x3->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_X4;
    msg += ui->lineEdit_x4->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_X5;
    msg += ui->lineEdit_x5->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_X6;
    msg += ui->lineEdit_x6->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_BOTI;
    msg += ui->lineEdit_boti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_DM;
    msg += ui->lineEdit_dm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_KETTE;
    msg += ui->lineEdit_kette->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_GRUPPE;
    msg += ui->lineEdit_grp->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_ANBOTI;
    msg += ui->lineEdit_anboti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_ANBOVO;
    msg += ui->lineEdit_anbovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_REBOMA;
    msg += ui->lineEdit_reboma->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_BOVO;
    msg += ui->lineEdit_bovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_ZSM;
    msg += ui->lineEdit_zsm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_DREHZ;
    msg += ui->lineEdit_n->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BOX_MESSEI;
    msg += int_to_qstring(ui->spinBox_messei->value());
    msg += ENDPAR;

    msg += BOX_TASATZ;
    msg += int_to_qstring(ui->spinBox_tasatz->value());
    msg += ENDPAR;

    msg += BOX_PLM;
    msg += int_to_qstring(ui->spinBox_plm->value());
    msg += ENDPAR;

    msg += BOX_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += BOX_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_bohren_x::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = BOX_Y;
    ui->lineEdit_y1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_Y2;
    ui->lineEdit_y2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_X1;
    ui->lineEdit_x1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_X2;
    ui->lineEdit_x2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_X3;
    ui->lineEdit_x3->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_X4;
    ui->lineEdit_x4->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_X5;
    ui->lineEdit_x5->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_X6;
    ui->lineEdit_x6->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_BOTI;
    ui->lineEdit_boti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_DM;
    ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_KETTE;
    ui->lineEdit_kette->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_GRUPPE;
    ui->lineEdit_grp->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_ANBOTI;
    ui->lineEdit_anboti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_ANBOVO;
    ui->lineEdit_anbovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_REBOMA;
    ui->lineEdit_reboma->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_BOVO;
    ui->lineEdit_bovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_ZSM;
    ui->lineEdit_zsm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BOX_DREHZ;
    ui->lineEdit_n->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    QString tmp;
    parname = ENDPAR;
    parname += BOX_MESSEI;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_messei->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += BOX_TASATZ;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_tasatz->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += BOX_PLM;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_plm->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += BOX_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += BOX_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_bohren_x::get_default()
{
    QString msg;

    msg += BOX_Y;
    msg += "0";
    msg += ENDPAR;

    msg += BOX_Y2;
    msg += "-1";
    msg += ENDPAR;

    msg += BOX_X1;
    msg += "0";
    msg += ENDPAR;

    msg += BOX_X2;
    msg += "";
    msg += ENDPAR;

    msg += BOX_X3;
    msg += "";
    msg += ENDPAR;

    msg += BOX_X4;
    msg += "";
    msg += ENDPAR;

    msg += BOX_X5;
    msg += "";
    msg += ENDPAR;

    msg += BOX_X6;
    msg += "";
    msg += ENDPAR;

    msg += BOX_BOTI;
    msg += "2";
    msg += ENDPAR;

    msg += BOX_DM;
    msg += "5";
    msg += ENDPAR;

    msg += BOX_KETTE;
    msg += "0";
    msg += ENDPAR;

    msg += BOX_GRUPPE;
    msg += "1";
    msg += ENDPAR;

    msg += BOX_ANBOTI;
    msg += "4";
    msg += ENDPAR;

    msg += BOX_ANBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += BOX_REBOMA;
    msg += "4";
    msg += ENDPAR;

    msg += BOX_BOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += BOX_ZSM;
    msg += "5";
    msg += ENDPAR;

    msg += BOX_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += BOX_MESSEI;
    msg += "0";
    msg += ENDPAR;

    msg += BOX_TASATZ;
    msg += "-1";
    msg += ENDPAR;

    msg += BOX_PLM;
    msg += "0";
    msg += ENDPAR;

    msg += BOX_BEZ;
    msg += "Bohren in X";
    msg += ENDPAR;

    msg += BOX_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
