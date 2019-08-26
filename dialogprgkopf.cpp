#include "dialogprgkopf.h"
#include "ui_dialogprgkopf.h"

DialogPrgKopf::DialogPrgKopf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPrgKopf)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);
}

DialogPrgKopf::~DialogPrgKopf()
{
    delete ui;
}

void DialogPrgKopf::on_pushButton_ok_clicked()
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

void DialogPrgKopf::on_pushButton_esc_clicked()
{
    this->close();
}

void DialogPrgKopf::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString DialogPrgKopf::dialogDataToString()
{
    QString msg = DLG_PKOPF ;

    //... hier fehlt noch sehr viel

    msg += PKOPF_L;
    msg += buchstaben_alle_GROSS_schreiben(ui->lineEdit_l->text());
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void DialogPrgKopf::getDialogData(QString text, bool openToChangeData)
{

}
