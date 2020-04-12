#include "dialog_fgerade.h"
#include "ui_dialog_fgerade.h"

Dialog_fgerade::Dialog_fgerade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fgerade)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.path_dlgbilder_();
    bild1 += "fgerade_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren
}

Dialog_fgerade::~Dialog_fgerade()
{
    delete ui;
}

void Dialog_fgerade::on_pushButton_ok_clicked()
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

void Dialog_fgerade::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_fgerade::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_fgerade::dialogDataToString()
{
    QString msg = DLG_FGERADE ;

    msg += FGERADE_X;
    msg += ui->lineEdit_x->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERADE_Y;
    msg += ui->lineEdit_y->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERADE_Z;
    msg += ui->lineEdit_z->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERADE_RAD;
    msg += ui->lineEdit_rad->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERADE_VO;
    msg += ui->lineEdit_vo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERADE_DREHBAR;
    msg += ui->lineEdit_drehbar->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERADE_OFFSET;
    msg += ui->lineEdit_offset->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERADE_FESTWI;
    msg += ui->lineEdit_festwi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FGERADE_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += FGERADE_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_fgerade::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString parname = FGERADE_X;
    ui->lineEdit_x->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERADE_Y;
    ui->lineEdit_y->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERADE_Z;
    ui->lineEdit_z->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERADE_RAD;
    ui->lineEdit_rad->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERADE_VO;
    ui->lineEdit_vo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERADE_DREHBAR;
    ui->lineEdit_drehbar->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERADE_OFFSET;
    ui->lineEdit_offset->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERADE_FESTWI;
    ui->lineEdit_festwi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FGERADE_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += FGERADE_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_fgerade::get_default()
{
    QString msg;

    msg += FGERADE_X;
    msg += "";
    msg += ENDPAR;

    msg += FGERADE_Y;
    msg += "";
    msg += ENDPAR;

    msg += FGERADE_Z;
    msg += "Z";
    msg += ENDPAR;

    msg += FGERADE_RAD;
    msg += "EBG";
    msg += ENDPAR;

    msg += FGERADE_VO;
    msg += "V";
    msg += ENDPAR;

    msg += FGERADE_DREHBAR;
    msg += "AGGDREHBAR";
    msg += ENDPAR;

    msg += FGERADE_OFFSET;
    msg += "AGGOFFSET";
    msg += ENDPAR;

    msg += FGERADE_FESTWI;
    msg += "AGGFWKL";
    msg += ENDPAR;

    msg += FGERADE_BEZ;
    msg += "Gerade";
    msg += ENDPAR;

    msg += FGERADE_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
