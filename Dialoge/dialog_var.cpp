#include "dialog_var.h"
#include "ui_dialog_var.h"

Dialog_var::Dialog_var(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_var)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);
}

Dialog_var::~Dialog_var()
{
    delete ui;
}

void Dialog_var::on_pushButton_ok_clicked()
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

void Dialog_var::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_var::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_var::dialogDataToString()
{
    QString msg = DLG_VAR ;

    msg += VAR_NAME;
    msg += ui->lineEdit_name->text().toUpper();
    msg += ENDPAR;

    msg += VAR_WERT;
    msg += ui->lineEdit_wert->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += VAR_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_var::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = VAR_NAME;
    ui->lineEdit_name->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += VAR_WERT;
    ui->lineEdit_wert->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += VAR_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_var::get_default()
{
    QString msg;

    msg += VAR_NAME;
    msg += "";
    msg += ENDPAR;

    msg += VAR_WERT;
    msg += "";
    msg += ENDPAR;

    msg += VAR_BEZ;
    msg += "Variable definieren";
    msg += ENDPAR;

    msg += VAR_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
