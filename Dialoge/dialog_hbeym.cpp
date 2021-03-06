#include "dialog_hbeym.h"
#include "ui_dialog_hbeym.h"

Dialog_hbeym::Dialog_hbeym(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_hbeym)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.path_dlgbilder_();
    bild1 += "hbeym_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.path_dlgbilder_();
    bild2 += "hbeym_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_hbeym::~Dialog_hbeym()
{
    delete ui;
}

void Dialog_hbeym::on_pushButton_ok_clicked()
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

void Dialog_hbeym::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_hbeym::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_hbeym::dialogDataToString()
{
    QString msg = DLG_HBEYM ;

    msg += HBEYM_X1;
    msg += ui->lineEdit_x1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_X2;
    msg += ui->lineEdit_x2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_X3;
    msg += ui->lineEdit_x3->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_X4;
    msg += ui->lineEdit_x4->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_X5;
    msg += ui->lineEdit_x5->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_X6;
    msg += ui->lineEdit_x6->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_BOTI;
    msg += ui->lineEdit_boti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_Z;
    msg += ui->lineEdit_z->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_DM;
    msg += ui->lineEdit_dm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_KETTE;
    msg += ui->lineEdit_kette->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_GRUPPE;
    msg += ui->lineEdit_grp->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_Y2;
    msg += ui->lineEdit_y2->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_Y1;
    msg += ui->lineEdit_y1->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_ANBOTI;
    msg += ui->lineEdit_anboti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_ANBOVO;
    msg += ui->lineEdit_anbovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_BOVO;
    msg += ui->lineEdit_bovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_DREHZ;
    msg += ui->lineEdit_n->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEYM_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += HBEYM_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_hbeym::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = HBEYM_X1;
    ui->lineEdit_x1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_X2;
    ui->lineEdit_x2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_X3;
    ui->lineEdit_x3->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_X4;
    ui->lineEdit_x4->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_X5;
    ui->lineEdit_x5->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_X6;
    ui->lineEdit_x6->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_BOTI;
    ui->lineEdit_boti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_Z;
    ui->lineEdit_z->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_DM;
    ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_KETTE;
    ui->lineEdit_kette->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_GRUPPE;
    ui->lineEdit_grp->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_Y2;
    ui->lineEdit_y2->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_Y1;
    ui->lineEdit_y1->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_ANBOTI;
    ui->lineEdit_anboti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_ANBOVO;
    ui->lineEdit_anbovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_BOVO;
    ui->lineEdit_bovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_DREHZ;
    ui->lineEdit_n->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEYM_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += HBEYM_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_hbeym::get_default()
{
    QString msg;

    msg += HBEYM_X1;
    msg += "20";
    msg += ENDPAR;

    msg += HBEYM_X2;
    msg += "96";
    msg += ENDPAR;

    msg += HBEYM_X3;
    msg += "96";
    msg += ENDPAR;

    msg += HBEYM_X4;
    msg += "96";
    msg += ENDPAR;

    msg += HBEYM_X5;
    msg += "96";
    msg += ENDPAR;

    msg += HBEYM_X6;
    msg += "96";
    msg += ENDPAR;

    msg += HBEYM_BOTI;
    msg += "18";
    msg += ENDPAR;

    msg += HBEYM_Z;
    msg += "D/2";
    msg += ENDPAR;

    msg += HBEYM_DM;
    msg += "8.2";
    msg += ENDPAR;

    msg += HBEYM_KETTE;
    msg += "1";
    msg += ENDPAR;

    msg += HBEYM_GRUPPE;
    msg += "1";
    msg += ENDPAR;

    msg += HBEYM_Y2;
    msg += "-1";
    msg += ENDPAR;

    msg += HBEYM_Y1;
    msg += "B";
    msg += ENDPAR;

    msg += HBEYM_ANBOTI;
    msg += "4";
    msg += ENDPAR;

    msg += HBEYM_ANBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += HBEYM_BOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += HBEYM_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += HBEYM_BEZ;
    msg += "HBE Y minus";
    msg += ENDPAR;

    msg += HBEYM_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}

