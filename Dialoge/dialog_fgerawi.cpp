#include "dialog_fgerawi.h"
#include "ui_dialog_fgerawi.h"

Dialog_fgerawi::Dialog_fgerawi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fgerawi)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.get_path_dlgbilder_();
    bild1 += "fgerawi_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren
}

Dialog_fgerawi::~Dialog_fgerawi()
{
    delete ui;
}

void Dialog_fgerawi::on_pushButton_ok_clicked()
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

void Dialog_fgerawi::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_fgerawi::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_fgerawi::dialogDataToString()
{
    QString msg = DLG_FGERAWI ;

    msg += FGERAWI_WI;
    msg += ui->lineEdit_wi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERAWI_L;
    msg += ui->lineEdit_l->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERAWI_Z;
    msg += ui->lineEdit_z->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERAWI_RAD;
    msg += ui->lineEdit_rad->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERAWI_VO;
    msg += ui->lineEdit_vo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERAWI_DREHBAR;
    msg += ui->lineEdit_drehbar->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERAWI_OFFSET;
    msg += ui->lineEdit_offset->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERAWI_FESTWI;
    msg += ui->lineEdit_festwi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERAWI_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += FGERAWI_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_fgerawi::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = FGERAWI_WI;
    ui->lineEdit_wi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERAWI_L;
    ui->lineEdit_l->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERAWI_Z;
    ui->lineEdit_z->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERAWI_RAD;
    ui->lineEdit_rad->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERAWI_VO;
    ui->lineEdit_vo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERAWI_DREHBAR;
    ui->lineEdit_drehbar->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERAWI_OFFSET;
    ui->lineEdit_offset->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERAWI_FESTWI;
    ui->lineEdit_festwi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERAWI_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += FGERAWI_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_fgerawi::get_default()
{
    QString msg;

    msg += FGERAWI_WI;
    msg += "";
    msg += ENDPAR;

    msg += FGERAWI_L;
    msg += "";
    msg += ENDPAR;

    msg += FGERAWI_Z;
    msg += "Z";
    msg += ENDPAR;

    msg += FGERAWI_RAD;
    msg += "EBG";
    msg += ENDPAR;

    msg += FGERAWI_VO;
    msg += "V";
    msg += ENDPAR;

    msg += FGERAWI_DREHBAR;
    msg += "AGGDREHBAR";
    msg += ENDPAR;

    msg += FGERAWI_OFFSET;
    msg += "AGGOFFSET";
    msg += ENDPAR;

    msg += FGERAWI_FESTWI;
    msg += "AGGFWKL";
    msg += ENDPAR;

    msg += FGERAWI_BEZ;
    msg += "Gerade mit Winkel";
    msg += ENDPAR;

    msg += FGERAWI_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
