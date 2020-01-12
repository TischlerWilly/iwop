#include "dialog_hbexm.h"
#include "ui_dialog_hbexm.h"

Dialog_hbexm::Dialog_hbexm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_hbexm)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.get_path_dlgbilder_();
    bild1 += "hbexm_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.get_path_dlgbilder_();
    bild2 += "hbexm_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_hbexm::~Dialog_hbexm()
{
    delete ui;
}

void Dialog_hbexm::on_pushButton_ok_clicked()
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

void Dialog_hbexm::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_hbexm::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_hbexm::dialogDataToString()
{
    QString msg = DLG_HBEXM ;

    msg += HBEXM_Y1;
    msg += ui->lineEdit_y1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_Y2;
    msg += ui->lineEdit_y2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_Y3;
    msg += ui->lineEdit_y3->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_Y4;
    msg += ui->lineEdit_y4->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_Y5;
    msg += ui->lineEdit_y5->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_Y6;
    msg += ui->lineEdit_y6->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_BOTI;
    msg += ui->lineEdit_boti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_Z;
    msg += ui->lineEdit_z->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_DM;
    msg += ui->lineEdit_dm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_KETTE;
    msg += ui->lineEdit_kette->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_GRUPPE;
    msg += ui->lineEdit_grp->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_X2;
    msg += ui->lineEdit_x2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_X1;
    msg += ui->lineEdit_x1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_ANBOTI;
    msg += ui->lineEdit_anboti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_ANBOVO;
    msg += ui->lineEdit_anbovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_BOVO;
    msg += ui->lineEdit_bovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_DREHZ;
    msg += ui->lineEdit_n->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEXM_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += HBEXM_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_hbexm::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = HBEXM_Y1;
    ui->lineEdit_y1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_Y2;
    ui->lineEdit_y2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_Y3;
    ui->lineEdit_y3->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_Y4;
    ui->lineEdit_y4->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_Y5;
    ui->lineEdit_y5->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_Y6;
    ui->lineEdit_y6->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_BOTI;
    ui->lineEdit_boti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_Z;
    ui->lineEdit_z->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_DM;
    ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_KETTE;
    ui->lineEdit_kette->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_GRUPPE;
    ui->lineEdit_grp->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_X2;
    ui->lineEdit_x2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_X1;
    ui->lineEdit_x1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_ANBOTI;
    ui->lineEdit_anboti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_ANBOVO;
    ui->lineEdit_anbovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_BOVO;
    ui->lineEdit_bovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_DREHZ;
    ui->lineEdit_n->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEXM_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += HBEXM_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_hbexm::get_default()
{
    QString msg;

    msg += HBEXM_Y1;
    msg += "20";
    msg += ENDPAR;

    msg += HBEXM_Y2;
    msg += "96";
    msg += ENDPAR;

    msg += HBEXM_Y3;
    msg += "96";
    msg += ENDPAR;

    msg += HBEXM_Y4;
    msg += "96";
    msg += ENDPAR;

    msg += HBEXM_Y5;
    msg += "96";
    msg += ENDPAR;

    msg += HBEXM_Y6;
    msg += "96";
    msg += ENDPAR;

    msg += HBEXM_BOTI;
    msg += "18";
    msg += ENDPAR;

    msg += HBEXM_Z;
    msg += "D/2";
    msg += ENDPAR;

    msg += HBEXM_DM;
    msg += "8.2";
    msg += ENDPAR;

    msg += HBEXM_KETTE;
    msg += "1";
    msg += ENDPAR;

    msg += HBEXM_GRUPPE;
    msg += "1";
    msg += ENDPAR;

    msg += HBEXM_X2;
    msg += "-1";
    msg += ENDPAR;

    msg += HBEXM_X1;
    msg += "L";
    msg += ENDPAR;

    msg += HBEXM_ANBOTI;
    msg += "4";
    msg += ENDPAR;

    msg += HBEXM_ANBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += HBEXM_BOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += HBEXM_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += HBEXM_BEZ;
    msg += "HBE X minus";
    msg += ENDPAR;

    msg += HBEXM_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
