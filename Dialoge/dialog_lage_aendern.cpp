#include "dialog_lage_aendern.h"
#include "ui_dialog_lage_aendern.h"

Dialog_lage_aendern::Dialog_lage_aendern(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_lage_aendern)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);
}

Dialog_lage_aendern::~Dialog_lage_aendern()
{
    delete ui;
}

void Dialog_lage_aendern::on_pushButton_ok_clicked()
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

void Dialog_lage_aendern::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_lage_aendern::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_lage_aendern::dialogDataToString()
{
    QString msg = DLG_LAGE_AENDERN ;

    msg += LAGE_AENDERN_XALT;
    msg += ui->lineEdit_xalt->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LAGE_AENDERN_YALT;
    msg += ui->lineEdit_yalt->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LAGE_AENDERN_XNEU;
    msg += ui->lineEdit_xneu->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LAGE_AENDERN_YNEU;
    msg += ui->lineEdit_yneu->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LAGE_AENDERN_DREHWI;
    msg += ui->lineEdit_drehwi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LAGE_AENDERN_KETTENMAS;
    msg += ui->lineEdit_kettenmas->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LAGE_AENDERN_GESWI;
    msg += ui->lineEdit_geswi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += LAGE_AENDERN_BEZ;
    msg += ui->lineEdit_bez->text().toUpper();
    msg += ENDPAR;

    msg += LAGE_AENDERN_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_lage_aendern::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = LAGE_AENDERN_XALT;
    ui->lineEdit_xalt->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));

    parname = LAGE_AENDERN_YALT;
    ui->lineEdit_yalt->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));

    parname = LAGE_AENDERN_XNEU;
    ui->lineEdit_xneu->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));

    parname = LAGE_AENDERN_YNEU;
    ui->lineEdit_yneu->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));

    parname = LAGE_AENDERN_DREHWI;
    ui->lineEdit_xneu->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));

    parname = LAGE_AENDERN_KETTENMAS;
    ui->lineEdit_xneu->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));

    parname = LAGE_AENDERN_GESWI;
    ui->lineEdit_xneu->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));

    parname = LAGE_AENDERN_BEZ;
    ui->lineEdit_xneu->setText(selektiereEintrag(text, parname, ENDPAR));

    parname += LAGE_AENDERN_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_lage_aendern::get_default()
{
    QString msg;

    msg += LAGE_AENDERN_XALT;
    msg += "L/2";
    msg += ENDPAR;

    msg += LAGE_AENDERN_YALT;
    msg += "B/2";
    msg += ENDPAR;

    msg += LAGE_AENDERN_XNEU;
    msg += "L/2";
    msg += ENDPAR;

    msg += LAGE_AENDERN_YNEU;
    msg += "B/2";
    msg += ENDPAR;

    msg += LAGE_AENDERN_DREHWI;
    msg += "180";
    msg += ENDPAR;

    msg += LAGE_AENDERN_KETTENMAS;
    msg += "0";
    msg += ENDPAR;

    msg += LAGE_AENDERN_GESWI;
    msg += "0";
    msg += ENDPAR;

    msg += LAGE_AENDERN_BEZ;
    msg += "Lage ändern";
    msg += ENDPAR;

    msg += LAGE_AENDERN_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
