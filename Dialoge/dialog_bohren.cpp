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
    msg += ui->lineEdit_x1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BO_Y;
    msg += ui->lineEdit_y1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BO_BOTI;
    msg += ui->lineEdit_boti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BO_DM;
    msg += ui->lineEdit_dm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BO_GRUPPE;
    msg += ui->lineEdit_grp->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BO_ANBOTI;
    msg += ui->lineEdit_anboti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BO_ANBOVO;
    msg += ui->lineEdit_anbovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BO_REBOMA;
    msg += ui->lineEdit_reboma->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BO_BOVO;
    msg += ui->lineEdit_bovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BO_ZSM;
    msg += ui->lineEdit_zsm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += BO_DREHZ;
    msg += ui->lineEdit_n->text().toUpper().replace(",",".");
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
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_Bohren::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = BO_X;
    ui->lineEdit_x1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BO_Y;
    ui->lineEdit_y1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BO_BOTI;
    ui->lineEdit_boti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BO_DM;
    ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BO_GRUPPE;
    ui->lineEdit_grp->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BO_ANBOTI;
    ui->lineEdit_anboti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BO_ANBOVO;
    ui->lineEdit_anbovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BO_REBOMA;
    ui->lineEdit_reboma->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BO_BOVO;
    ui->lineEdit_bovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BO_ZSM;
    ui->lineEdit_zsm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += BO_DREHZ;
    ui->lineEdit_n->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    QString tmp;
    parname = ENDPAR;
    parname += BO_MESSEI;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_messei->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += BO_TASATZ;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_tasatz->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += BO_PLM;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_plm->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += BO_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += BO_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
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
    msg += "AUTO";
    msg += ENDPAR;

    msg += BO_REBOMA;
    msg += "4";
    msg += ENDPAR;

    msg += BO_BOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += BO_ZSM;
    msg += "5";
    msg += ENDPAR;

    msg += BO_DREHZ;
    msg += "AUTO";
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
