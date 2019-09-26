#include "dialog_prgkopf.h"
#include "ui_dialog_prgkopf.h"

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

    msg += PKOPF_KOM1;
    msg += ui->lineEdit_kom1->text();
    msg += ENDPAR;

    msg += PKOPF_KOM2;
    msg += ui->lineEdit_kom2->text();
    msg += ENDPAR;

    msg += PKOPF_L;
    msg += ui->lineEdit_l->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += PKOPF_B;
    msg += ui->lineEdit_b->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += PKOPF_D;
    msg += ui->lineEdit_d->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += PKOPF_FUENFSEI;
    if(ui->checkBox_fuenfseiten->isChecked())
    {
        msg += "1";
    }else
    {
        msg += "0";
    }
    msg += ENDPAR;

    msg += PKOPF_SPEIGELN;
    if(ui->checkBox_spiegeln->isChecked())
    {
        msg += "1";
    }else
    {
        msg += "0";
    }
    msg += ENDPAR;

    msg += PKOPF_BELEGART;
    msg += ui->lineEdit_belegart->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += PKOPF_XVERS;
    msg += ui->lineEdit_ax->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += PKOPF_YVERS;
    msg += ui->lineEdit_ay->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += PKOFP_RTL;
    msg += ui->lineEdit_rl->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += PKOFP_RTB;
    msg += ui->lineEdit_rb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += PKOPF_LOESEN;
    if(ui->checkBox_loesen->isChecked())
    {
        msg += "1";
    }else
    {
        msg += "0";
    }
    msg += ENDPAR;

    msg += PKOPF_SCHABH;
    msg += ui->lineEdit_schabh->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += PKOPF_SIABST;
    msg += ui->lineEdit_siabst->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += PKOPF_PAPO;
    msg += int_to_qstring(ui->spinBox_pura->value());
    msg += ENDPAR;

    msg += PKOPF_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += PKOPF_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void DialogPrgKopf::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    ui->lineEdit_kom1->setText(selektiereEintrag(text, PKOPF_KOM1, ENDPAR));
    ui->lineEdit_kom2->setText(selektiereEintrag(text, PKOPF_KOM2, ENDPAR));
    ui->lineEdit_l->setText(selektiereEintrag(text, PKOPF_L, ENDPAR).replace(".",","));
    ui->lineEdit_b->setText(selektiereEintrag(text, PKOPF_B, ENDPAR).replace(".",","));
    ui->lineEdit_d->setText(selektiereEintrag(text, PKOPF_D, ENDPAR).replace(".",","));
    QString tmp;
    tmp = selektiereEintrag(text, PKOPF_FUENFSEI, ENDPAR);
    if(tmp == "1")
    {
        ui->checkBox_fuenfseiten->setChecked(true);
    }else
    {
        ui->checkBox_fuenfseiten->setChecked(false);
    }
    tmp = selektiereEintrag(text, PKOPF_SPEIGELN, ENDPAR);
    if(tmp == "1")
    {
        ui->checkBox_spiegeln->setChecked(true);
    }else
    {
        ui->checkBox_spiegeln->setChecked(false);
    }
    ui->lineEdit_belegart->setText(selektiereEintrag(text, PKOPF_BELEGART, ENDPAR).replace(".",","));
    ui->lineEdit_ax->setText(selektiereEintrag(text, PKOPF_XVERS, ENDPAR).replace(".",","));
    ui->lineEdit_ay->setText(selektiereEintrag(text, PKOPF_YVERS, ENDPAR).replace(".",","));
    ui->lineEdit_rl->setText(selektiereEintrag(text, PKOFP_RTL, ENDPAR).replace(".",","));
    ui->lineEdit_rb->setText(selektiereEintrag(text, PKOFP_RTB, ENDPAR).replace(".",","));
    tmp = selektiereEintrag(text, PKOPF_LOESEN, ENDPAR);
    if(tmp == "1")
    {
        ui->checkBox_loesen->setChecked(true);
    }else
    {
        ui->checkBox_loesen->setChecked(false);
    }
    ui->lineEdit_schabh->setText(selektiereEintrag(text, PKOPF_SCHABH, ENDPAR).replace(".",","));
    ui->lineEdit_siabst->setText(selektiereEintrag(text, PKOPF_SIABST, ENDPAR).replace(".",","));
    tmp = selektiereEintrag(text, PKOPF_PAPO, ENDPAR);
    ui->spinBox_pura->setValue(tmp.toInt());
    ui->lineEdit_bez->setText(selektiereEintrag(text, PKOPF_BEZ, ENDPAR));
    ui->lineEdit_afb->setText(selektiereEintrag(text, PKOPF_AFB, ENDPAR).replace(".",","));
    this->show();
}

QString DialogPrgKopf::get_default()
{
    QString msg = DLG_PKOPF ;

    msg += PKOPF_KOM1;
    msg += "";
    msg += ENDPAR;

    msg += PKOPF_KOM2;
    msg += "";
    msg += ENDPAR;

    msg += PKOPF_L;
    msg += "500";
    msg += ENDPAR;

    msg += PKOPF_B;
    msg += "300";
    msg += ENDPAR;

    msg += PKOPF_D;
    msg += "19";
    msg += ENDPAR;

    msg += PKOPF_FUENFSEI;
    msg += "0";
    msg += ENDPAR;

    msg += PKOPF_SPEIGELN;
    msg += "0";
    msg += ENDPAR;

    msg += PKOPF_BELEGART;
    msg += "0";
    msg += ENDPAR;

    msg += PKOPF_XVERS;
    msg += "0";
    msg += ENDPAR;

    msg += PKOPF_YVERS;
    msg += "0";
    msg += ENDPAR;

    msg += PKOFP_RTL;
    msg += "500";
    msg += ENDPAR;

    msg += PKOFP_RTB;
    msg += "300";
    msg += ENDPAR;

    msg += PKOPF_LOESEN;
    msg += "1";
    msg += ENDPAR;

    msg += PKOPF_SCHABH;
    msg += "0";
    msg += ENDPAR;

    msg += PKOPF_SIABST;
    msg += "20";
    msg += ENDPAR;

    msg += PKOPF_PAPO;
    msg += "2";
    msg += ENDPAR;

    msg += PKOPF_BEZ;
    msg += "Programmkopf";
    msg += ENDPAR;

    msg += PKOPF_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
