#include "dialog_bohren.h"
#include "ui_dialog_bohren.h"

Dialog_Bohren::Dialog_Bohren(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Bohren)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    QString bild1;
    bild1  = PFAD_DLGBILDER;
    bild1 += QDir::separator();
    bild1 += "bo_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2;
    bild2  = PFAD_DLGBILDER;
    bild2 += QDir::separator();
    bild2 += "bo_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_Bohren::~Dialog_Bohren()
{
    delete ui;
}

void Dialog_Bohren::on_pushButton_ok_clicked()
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

void Dialog_Bohren::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_Bohren::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_Bohren::dialogDataToString()
{
    QString msg = DLG_BO ;

    msg += BO_X;
    msg += ui->lineEdit_x1->text();
    msg += ENDPAR;

    msg += BO_Y;
    msg += ui->lineEdit_y1->text();
    msg += ENDPAR;

    msg += BO_BOTI;
    msg += ui->lineEdit_boti->text();
    msg += ENDPAR;

    msg += BO_DM;
    msg += ui->lineEdit_dm->text();
    msg += ENDPAR;

    msg += BO_GRUPPE;
    msg += ui->lineEdit_grp->text();
    msg += ENDPAR;

    msg += BO_ANBOTI;
    msg += ui->lineEdit_anboti->text();
    msg += ENDPAR;

    msg += BO_ANBOVO;
    msg += ui->lineEdit_anbovo->text();
    msg += ENDPAR;

    msg += BO_REBOMA;
    msg += ui->lineEdit_reboma->text();
    msg += ENDPAR;

    msg += BO_BOVO;
    msg += ui->lineEdit_bovo->text();
    msg += ENDPAR;

    msg += BO_ZSM;
    msg += ui->lineEdit_zsm->text();
    msg += ENDPAR;

    msg += BO_DREHZ;
    msg += ui->lineEdit_n->text();
    msg += ENDPAR;

    msg += BO_MESSEI;
    msg += int_to_qstring(ui->spinBox_messei->value());
    msg += ENDPAR;

    msg += BO_TASATZ;
    msg += int_to_qstring(ui->spinBox_tasatz->value());
    msg += ENDPAR;

    msg += BO_PLM;
    msg += int_to_qstring(ui->spinBox_plm->value());
    msg += ENDPAR;

    msg += BO_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += BO_AFB;
    msg += ui->lineEdit_afb->text();
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_Bohren::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    ui->lineEdit_x1->setText(selektiereEintrag(text, BO_X, ENDPAR).replace(".",","));
    ui->lineEdit_y1->setText(selektiereEintrag(text, BO_Y, ENDPAR).replace(".",","));
    ui->lineEdit_boti->setText(selektiereEintrag(text, BO_BOTI, ENDPAR).replace(".",","));
    ui->lineEdit_dm->setText(selektiereEintrag(text, BO_DM, ENDPAR).replace(".",","));
    ui->lineEdit_grp->setText(selektiereEintrag(text, BO_GRUPPE, ENDPAR).replace(".",","));
    ui->lineEdit_anboti->setText(selektiereEintrag(text, BO_ANBOTI, ENDPAR).replace(".",","));
    ui->lineEdit_anbovo->setText(selektiereEintrag(text, BO_ANBOVO, ENDPAR).replace(".",","));
    ui->lineEdit_reboma->setText(selektiereEintrag(text, BO_REBOMA, ENDPAR).replace(".",","));
    ui->lineEdit_bovo->setText(selektiereEintrag(text, BO_BOVO, ENDPAR).replace(".",","));
    ui->lineEdit_zsm->setText(selektiereEintrag(text, BO_ZSM, ENDPAR).replace(".",","));
    ui->lineEdit_n->setText(selektiereEintrag(text, BO_DREHZ, ENDPAR).replace(".",","));
    QString tmp;
    tmp = selektiereEintrag(text, BO_MESSEI, ENDPAR);
    ui->spinBox_messei->setValue(tmp.toInt());
    tmp = selektiereEintrag(text, BO_TASATZ, ENDPAR);
    ui->spinBox_tasatz->setValue(tmp.toInt());
    tmp = selektiereEintrag(text, BO_PLM, ENDPAR);
    ui->spinBox_plm->setValue(tmp.toInt());
    ui->lineEdit_bez->setText(selektiereEintrag(text, BO_BEZ, ENDPAR));
    ui->lineEdit_afb->setText(selektiereEintrag(text, BO_AFB, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_Bohren::get_default()
{
    QString msg;

    msg += BO_X;
    msg += "0";
    msg += ENDPAR;

    msg += BO_Y;
    msg += "0";
    msg += ENDPAR;

    msg += BO_BOTI;
    msg += "2";
    msg += ENDPAR;

    msg += BO_DM;
    msg += "5";
    msg += ENDPAR;

    msg += BO_GRUPPE;
    msg += "1";
    msg += ENDPAR;

    msg += BO_ANBOTI;
    msg += "4";
    msg += ENDPAR;

    msg += BO_ANBOVO;
    msg += "2000";
    msg += ENDPAR;

    msg += BO_REBOMA;
    msg += "4";
    msg += ENDPAR;

    msg += BO_BOVO;
    msg += "8000";
    msg += ENDPAR;

    msg += BO_ZSM;
    msg += "5";
    msg += ENDPAR;

    msg += BO_DREHZ;
    msg += "9000";
    msg += ENDPAR;

    msg += BO_MESSEI;
    msg += "0";
    msg += ENDPAR;

    msg += BO_TASATZ;
    msg += "-1";
    msg += ENDPAR;

    msg += BO_PLM;
    msg += "0";
    msg += ENDPAR;

    msg += BO_BEZ;
    msg += "Bohren Durchmesser";
    msg += ENDPAR;

    msg += BO_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
