#include "dialog_fboguzs.h"
#include "ui_dialog_fboguzs.h"

Dialog_fboguzs::Dialog_fboguzs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fboguzs)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.path_dlgbilder_();
    bild1 += "fboguzs_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren
}

Dialog_fboguzs::~Dialog_fboguzs()
{
    delete ui;
}

void Dialog_fboguzs::on_pushButton_ok_clicked()
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

void Dialog_fboguzs::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_fboguzs::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_fboguzs::dialogDataToString()
{
    QString msg = DLG_FBOGUZS ;

    msg += FBOGUZS_XE;
    msg += ui->lineEdit_xe->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_YE;
    msg += ui->lineEdit_ye->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_ZE;
    msg += ui->lineEdit_ze->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_XMI;
    msg += ui->lineEdit_xmi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_YMI;
    msg += ui->lineEdit_ymi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_RADBO;
    msg += ui->lineEdit_radbo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_RADECKE;
    msg += ui->lineEdit_radecke->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_VO;
    msg += ui->lineEdit_vo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_DREHBAR;
    msg += ui->lineEdit_drehbar->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_OFFSET;
    msg += ui->lineEdit_offset->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_FESTWI;
    msg += ui->lineEdit_festwi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FBOGUZS_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += FBOGUZS_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_fboguzs::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = FBOGUZS_XE;
    ui->lineEdit_xe->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_YE;
    ui->lineEdit_ye->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_ZE;
    ui->lineEdit_ze->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_XMI;
    ui->lineEdit_xmi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_YMI;
    ui->lineEdit_ymi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_RADBO;
    ui->lineEdit_radbo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_RADECKE;
    ui->lineEdit_radecke->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_VO;
    ui->lineEdit_vo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_DREHBAR;
    ui->lineEdit_drehbar->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_OFFSET;
    ui->lineEdit_offset->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_FESTWI;
    ui->lineEdit_festwi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FBOGUZS_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += FBOGUZS_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_fboguzs::get_default()
{
    QString msg;

    msg += FBOGUZS_XE;
    msg += "X";
    msg += ENDPAR;

    msg += FBOGUZS_YE;
    msg += "Y";
    msg += ENDPAR;

    msg += FBOGUZS_ZE;
    msg += "Z";
    msg += ENDPAR;

    msg += FBOGUZS_XMI;
    msg += "X";
    msg += ENDPAR;

    msg += FBOGUZS_YMI;
    msg += "Y";
    msg += ENDPAR;

    msg += FBOGUZS_RADBO;
    msg += "0";
    msg += ENDPAR;

    msg += FBOGUZS_RADECKE;
    msg += "EBG";
    msg += ENDPAR;

    msg += FBOGUZS_VO;
    msg += "V";
    msg += ENDPAR;

    msg += FBOGUZS_DREHBAR;
    msg += "AGGDREHBAR";
    msg += ENDPAR;

    msg += FBOGUZS_OFFSET;
    msg += "AGGOFFSET";
    msg += ENDPAR;

    msg += FBOGUZS_FESTWI;
    msg += "AGGFWKL";
    msg += ENDPAR;

    msg += FBOGUZS_BEZ;
    msg += "Kreis GUZ";
    msg += ENDPAR;

    msg += FBOGUZS_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
