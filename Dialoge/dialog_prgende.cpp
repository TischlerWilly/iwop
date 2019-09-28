#include "dialog_prgende.h"
#include "ui_dialog_prgende.h"

Dialog_prgende::Dialog_prgende(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_prgende)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    QString bild1;
    bild1  = PFAD_DLGBILDER;
    bild1 += QDir::separator();
    bild1 += "pende_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren
}

Dialog_prgende::~Dialog_prgende()
{
    delete ui;
}

void Dialog_prgende::on_pushButton_ok_clicked()
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

void Dialog_prgende::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_prgende::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_prgende::dialogDataToString()
{
    QString msg = DLG_PENDE ;

    msg += PENDE_PAPO;
    msg += int_to_qstring(ui->spinBox_papo->value());
    msg += ENDPAR;

    msg += PENDE_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += PENDE_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_prgende::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    QString tmp;
    tmp = selektiereEintrag(text, PENDE_PAPO, ENDPAR);
    ui->spinBox_papo->setValue(tmp.toInt());
    ui->lineEdit_bez->setText(selektiereEintrag(text, PENDE_BEZ, ENDPAR));
    ui->lineEdit_afb->setText(selektiereEintrag(text, PENDE_AFB, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_prgende::get_default()
{
    QString msg = DLG_PKOPF ;

    msg += PENDE_PAPO;
    msg += "2";
    msg += ENDPAR;

    msg += PENDE_BEZ;
    msg += "Programmende";
    msg += ENDPAR;

    msg += PENDE_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}

