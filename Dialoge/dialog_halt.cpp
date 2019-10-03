#include "dialog_halt.h"
#include "ui_dialog_halt.h"

Dialog_halt::Dialog_halt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_halt)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    QString bild1;
    bild1  = PFAD_DLGBILDER;
    bild1 += QDir::separator();
    bild1 += "halt_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren
}

Dialog_halt::~Dialog_halt()
{
    delete ui;
}

void Dialog_halt::on_pushButton_ok_clicked()
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

void Dialog_halt::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_halt::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_halt::dialogDataToString()
{
    QString msg = DLG_HALT ;

    msg += HALT_X;
    msg += ui->lineEdit_x->text();
    msg += ENDPAR;

    msg += HALT_Y;
    msg += ui->lineEdit_y->text();
    msg += ENDPAR;

    msg += HALT_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += HALT_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_halt::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    ui->lineEdit_x->setText(selektiereEintrag(text, HALT_X, ENDPAR).replace(".",","));
    ui->lineEdit_y->setText(selektiereEintrag(text, HALT_Y, ENDPAR).replace(".",","));
    ui->lineEdit_bez->setText(selektiereEintrag(text, HALT_BEZ, ENDPAR));
    ui->lineEdit_afb->setText(selektiereEintrag(text, HALT_AFB, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_halt::get_default()
{
    QString msg;

    msg += HALT_X;
    msg += "L+700";
    msg += ENDPAR;

    msg += HALT_Y;
    msg += "0";
    msg += ENDPAR;

    msg += HALT_BEZ;
    msg += "Halt";
    msg += ENDPAR;

    msg += HALT_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
