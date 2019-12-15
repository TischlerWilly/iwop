#include "dialog_spiegeln.h"
#include "ui_dialog_spiegeln.h"

Dialog_spiegeln::Dialog_spiegeln(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_spiegeln)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);
}

Dialog_spiegeln::~Dialog_spiegeln()
{
    delete ui;
}

void Dialog_spiegeln::on_pushButton_ok_clicked()
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

void Dialog_spiegeln::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_spiegeln::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_spiegeln::dialogDataToString()
{
    QString msg = DLG_SPIEGELN ;

    msg += SPIEGELN_XPOS;
    msg += ui->lineEdit_xpos->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += SPIEGELN_YPOS;
    msg += ui->lineEdit_ypos->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += SPIEGELN_XBED;
    if(ui->checkBox_xbed->isChecked())
    {
        msg += "1";
    }else
    {
        msg += "0";
    }
    msg += ENDPAR;

    msg += SPIEGELN_YBED;
    if(ui->checkBox_ybed->isChecked())
    {
        msg += "1";
    }else
    {
        msg += "0";
    }
    msg += ENDPAR;

    msg += SPIEGELN_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += SPIEGELN_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_spiegeln::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = SPIEGELN_XPOS;
    ui->lineEdit_xpos->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname = SPIEGELN_YPOS;
    ui->lineEdit_ypos->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname = SPIEGELN_XBED;
    QString tmp = selektiereEintrag(text, parname, ENDPAR);
    if(tmp == "1")
    {
        ui->checkBox_xbed->setChecked(true);
    }else
    {
        ui->checkBox_xbed->setChecked(false);
    }
    parname = ENDPAR;
    parname = SPIEGELN_YBED;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    if(tmp == "1")
    {
        ui->checkBox_ybed->setChecked(true);
    }else
    {
        ui->checkBox_ybed->setChecked(false);
    }
    parname = ENDPAR;
    parname += SPIEGELN_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += SPIEGELN_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_spiegeln::get_default()
{
    QString msg;

    msg += SPIEGELN_XPOS;
    msg += "L/2";
    msg += ENDPAR;

    msg += SPIEGELN_YPOS;
    msg += "B/2";
    msg += ENDPAR;

    msg += SPIEGELN_XBED;
    msg += "0";
    msg += ENDPAR;

    msg += SPIEGELN_XBED;
    msg += "1";
    msg += ENDPAR;

    msg += SPIEGELN_BEZ;
    msg += "spiegeln";
    msg += ENDPAR;

    msg += SPIEGELN_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
