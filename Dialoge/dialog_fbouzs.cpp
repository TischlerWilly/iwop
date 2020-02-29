#include "dialog_fbouzs.h"
#include "ui_dialog_fbouzs.h"

Dialog_fbouzs::Dialog_fbouzs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fbouzs)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.get_path_dlgbilder_();
    bild1 += "fbouzs_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren
}

Dialog_fbouzs::~Dialog_fbouzs()
{
    delete ui;
}

void Dialog_fbouzs::on_pushButton_ok_clicked()
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

void Dialog_fbouzs::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_fbouzs::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_fbouzs::dialogDataToString()
{
    QString msg = DLG_FBOUZS ;

    msg += FBOUZS_XE;
    msg += ui->lineEdit_xe->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_YE;
    msg += ui->lineEdit_ye->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_ZE;
    msg += ui->lineEdit_ze->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_XMI;
    msg += ui->lineEdit_xmi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_YMI;
    msg += ui->lineEdit_ymi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_RADBO;
    msg += ui->lineEdit_radbo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_RADECKE;
    msg += ui->lineEdit_radecke->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_VO;
    msg += ui->lineEdit_vo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_DREHBAR;
    msg += ui->lineEdit_drehbar->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_OFFSET;
    msg += ui->lineEdit_offset->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_FESTWI;
    msg += ui->lineEdit_festwi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOUZS_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += FBOUZS_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_fbouzs::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = FBOUZS_XE;
    ui->lineEdit_xe->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_YE;
    ui->lineEdit_ye->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_ZE;
    ui->lineEdit_ze->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_XMI;
    ui->lineEdit_xmi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_YMI;
    ui->lineEdit_ymi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_RADBO;
    ui->lineEdit_radbo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_RADECKE;
    ui->lineEdit_radecke->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_VO;
    ui->lineEdit_vo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_DREHBAR;
    ui->lineEdit_drehbar->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_OFFSET;
    ui->lineEdit_offset->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_FESTWI;
    ui->lineEdit_festwi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOUZS_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += FBOUZS_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_fbouzs::get_default()
{
    QString msg;

    msg += FBOUZS_XE;
    msg += "X";
    msg += ENDPAR;

    msg += FBOUZS_YE;
    msg += "Y";
    msg += ENDPAR;

    msg += FBOUZS_ZE;
    msg += "Z";
    msg += ENDPAR;

    msg += FBOUZS_XMI;
    msg += "X";
    msg += ENDPAR;

    msg += FBOUZS_YMI;
    msg += "Y";
    msg += ENDPAR;

    msg += FBOUZS_RADBO;
    msg += "0";
    msg += ENDPAR;

    msg += FBOUZS_RADECKE;
    msg += "EBG";
    msg += ENDPAR;

    msg += FBOUZS_VO;
    msg += "V";
    msg += ENDPAR;

    msg += FBOUZS_DREHBAR;
    msg += "AGGDREHBAR";
    msg += ENDPAR;

    msg += FBOUZS_OFFSET;
    msg += "AGGOFFSET";
    msg += ENDPAR;

    msg += FBOUZS_FESTWI;
    msg += "AGGFWKL";
    msg += ENDPAR;

    msg += FBOUZS_BEZ;
    msg += "Kreis IUZ";
    msg += ENDPAR;

    msg += FBOUZS_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
