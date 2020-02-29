#include "dialog_fabf.h"
#include "ui_dialog_fabf.h"

Dialog_fabf::Dialog_fabf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fabf)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);
}

Dialog_fabf::~Dialog_fabf()
{
    delete ui;
}

void Dialog_fabf::on_pushButton_ok_clicked()
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

void Dialog_fabf::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_fabf::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_fabf::dialogDataToString()
{
    QString msg = DLG_FABF ;

    msg += FABF_DREHBAR;
    msg += ui->lineEdit_drehbar->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FABF_OFFSET;
    msg += ui->lineEdit_offset->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FABF_FESTWI;
    msg += ui->lineEdit_festwi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FABF_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += FABF_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_fabf::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = FABF_DREHBAR;
    ui->lineEdit_drehbar->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FABF_OFFSET;
    ui->lineEdit_offset->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FABF_FESTWI;
    ui->lineEdit_festwi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FABF_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += FABF_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_fabf::get_default()
{
    QString msg;

    msg += FABF_DREHBAR;
    msg += "AGGDREHBAR";
    msg += ENDPAR;

    msg += FABF_OFFSET;
    msg += "AGGOFFSET";
    msg += ENDPAR;

    msg += FABF_FESTWI;
    msg += "AGGFWKL";
    msg += ENDPAR;

    msg += FABF_BEZ;
    msg += "Abfahren";
    msg += ENDPAR;

    msg += FABF_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
