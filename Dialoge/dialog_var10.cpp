#include "dialog_var10.h"
#include "ui_dialog_var10.h"

Dialog_var10::Dialog_var10(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_var10)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);
}

Dialog_var10::~Dialog_var10()
{
    delete ui;
}

void Dialog_var10::on_pushButton_ok_clicked()
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

void Dialog_var10::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_var10::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_var10::dialogDataToString()
{
    QString msg = DLG_VAR10;

    msg += VAR10_NAME1;
    msg += ui->lineEdit_name1->text().toUpper();
    msg += ENDPAR;

    msg += VAR10_NAME2;
    msg += ui->lineEdit_name2->text().toUpper();
    msg += ENDPAR;

    msg += VAR10_NAME3;
    msg += ui->lineEdit_name3->text().toUpper();
    msg += ENDPAR;

    msg += VAR10_NAME4;
    msg += ui->lineEdit_name4->text().toUpper();
    msg += ENDPAR;

    msg += VAR10_NAME5;
    msg += ui->lineEdit_name5->text().toUpper();
    msg += ENDPAR;

    msg += VAR10_NAME6;
    msg += ui->lineEdit_name6->text().toUpper();
    msg += ENDPAR;

    msg += VAR10_NAME7;
    msg += ui->lineEdit_name7->text().toUpper();
    msg += ENDPAR;

    msg += VAR10_NAME8;
    msg += ui->lineEdit_name8->text().toUpper();
    msg += ENDPAR;

    msg += VAR10_NAME9;
    msg += ui->lineEdit_name9->text().toUpper();
    msg += ENDPAR;

    msg += VAR10_NAME10;
    msg += ui->lineEdit_name10->text().toUpper();
    msg += ENDPAR;

    msg += VAR10_WERT1;
    msg += ui->lineEdit_wert1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR10_WERT2;
    msg += ui->lineEdit_wert2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR10_WERT3;
    msg += ui->lineEdit_wert3->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR10_WERT4;
    msg += ui->lineEdit_wert4->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR10_WERT5;
    msg += ui->lineEdit_wert5->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR10_WERT6;
    msg += ui->lineEdit_wert6->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR10_WERT7;
    msg += ui->lineEdit_wert7->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR10_WERT8;
    msg += ui->lineEdit_wert8->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR10_WERT9;
    msg += ui->lineEdit_wert9->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR10_WERT10;
    msg += ui->lineEdit_wert10->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += VAR10_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += VAR10_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_var10::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = VAR10_NAME1;
    ui->lineEdit_name1->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += VAR10_NAME2;
    ui->lineEdit_name2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_NAME3;
    ui->lineEdit_name3->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_NAME4;
    ui->lineEdit_name4->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_NAME5;
    ui->lineEdit_name5->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_NAME6;
    ui->lineEdit_name6->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_NAME7;
    ui->lineEdit_name7->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_NAME8;
    ui->lineEdit_name8->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_NAME9;
    ui->lineEdit_name9->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_NAME10;
    ui->lineEdit_name10->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_WERT1;
    ui->lineEdit_wert1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_WERT2;
    ui->lineEdit_wert2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_WERT3;
    ui->lineEdit_wert3->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_WERT4;
    ui->lineEdit_wert4->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_WERT5;
    ui->lineEdit_wert5->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_WERT6;
    ui->lineEdit_wert6->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_WERT7;
    ui->lineEdit_wert7->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_WERT8;
    ui->lineEdit_wert8->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_WERT9;
    ui->lineEdit_wert9->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_WERT10;
    ui->lineEdit_wert10->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += VAR10_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += VAR10_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_var10::get_default()
{
    QString msg;

    msg += VAR10_NAME1;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_NAME2;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_NAME3;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_NAME4;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_NAME5;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_NAME6;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_NAME7;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_NAME8;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_NAME9;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_NAME10;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_WERT1;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_WERT2;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_WERT3;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_WERT4;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_WERT5;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_WERT6;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_WERT7;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_WERT8;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_WERT9;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_WERT10;
    msg += "";
    msg += ENDPAR;

    msg += VAR10_BEZ;
    msg += "Variablen definieren";
    msg += ENDPAR;

    msg += VAR10_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
