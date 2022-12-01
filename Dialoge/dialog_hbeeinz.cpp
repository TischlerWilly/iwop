#include "dialog_hbeeinz.h"
#include "ui_dialog_hbeeinz.h"

Dialog_hbeeinz::Dialog_hbeeinz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_hbeeinz)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.path_dlgbilder_();
    bild1 += "hbeeinz_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.path_dlgbilder_();
    bild2 += "hbeeinz_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_hbeeinz::~Dialog_hbeeinz()
{
    delete ui;
}

void Dialog_hbeeinz::on_pushButton_ok_clicked()
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

void Dialog_hbeeinz::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_hbeeinz::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_hbeeinz::dialogDataToString()
{
    QString msg = DLG_HBEEINZ ;

    msg += HBEEINZ_X;
    msg += ui->lineEdit_x->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_Y;
    msg += ui->lineEdit_y->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_WI;
    msg += ui->lineEdit_wi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_BOTI;
    msg += ui->lineEdit_boti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_Z;
    msg += ui->lineEdit_z->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_DM;
    msg += ui->lineEdit_dm->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_GRUPPE;
    msg += ui->lineEdit_grp->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_NWI;
    msg += ui->lineEdit_nwi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_MBZ;
    msg += ui->lineEdit_mbz->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_ANBOTI;
    msg += ui->lineEdit_anboti->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_ANBOVO;
    msg += ui->lineEdit_anbovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_BOVO;
    msg += ui->lineEdit_bovo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_DREHZ;
    msg += ui->lineEdit_n->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += HBEEINZ_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += HBEEINZ_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_hbeeinz::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = HBEEINZ_X;
    ui->lineEdit_x->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_Y;
    ui->lineEdit_y->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_WI;
    ui->lineEdit_wi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_BOTI;
    ui->lineEdit_boti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_Z;
    ui->lineEdit_z->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_DM;
    ui->lineEdit_dm->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_GRUPPE;
    ui->lineEdit_grp->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_NWI;
    ui->lineEdit_nwi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_MBZ;
    ui->lineEdit_mbz->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_ANBOTI;
    ui->lineEdit_anboti->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_ANBOVO;
    ui->lineEdit_anbovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_BOVO;
    ui->lineEdit_bovo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_DREHZ;
    ui->lineEdit_n->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += HBEEINZ_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += HBEEINZ_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_hbeeinz::get_default()
{
    QString msg;

    msg += HBEEINZ_X;
    msg += "0";
    msg += ENDPAR;

    msg += HBEEINZ_Y;
    msg += "50";
    msg += ENDPAR;

    msg += HBEEINZ_WI;
    msg += "0";
    msg += ENDPAR;

    msg += HBEEINZ_BOTI;
    msg += "18";
    msg += ENDPAR;

    msg += HBEEINZ_Z;
    msg += "D/2";
    msg += ENDPAR;

    msg += HBEEINZ_DM;
    msg += "8.2";
    msg += ENDPAR;

    msg += HBEEINZ_GRUPPE;
    msg += "1";
    msg += ENDPAR;

    msg += HBEEINZ_NWI;
    msg += "0";
    msg += ENDPAR;

    msg += HBEEINZ_MBZ;
    msg += "0";
    msg += ENDPAR;

    msg += HBEEINZ_ANBOTI;
    msg += "4";
    msg += ENDPAR;

    msg += HBEEINZ_ANBOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += HBEEINZ_BOVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += HBEEINZ_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += HBEEINZ_BEZ;
    msg += "HBE Einzeln";
    msg += ENDPAR;

    msg += HBEEINZ_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
