#include "dialog_kom.h"
#include "ui_dialog_kom.h"

Dialog_kom::Dialog_kom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_kom)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);
}

Dialog_kom::~Dialog_kom()
{
    delete ui;
}

void Dialog_kom::on_pushButton_ok_clicked()
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

void Dialog_kom::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_kom::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_kom::dialogDataToString()
{
    QString msg = DLG_KOM ;

    msg += KOM_BEZ;
    msg += ui->lineEdit->text();
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_kom::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    ui->lineEdit->setText(selektiereEintrag(text, KOM_BEZ, ENDPAR));
    this->show();
}

QString Dialog_kom::get_default()
{
    QString msg;

    msg += KOM_BEZ;
    msg += "---------------";
    msg += ENDPAR;

    return msg;
}
