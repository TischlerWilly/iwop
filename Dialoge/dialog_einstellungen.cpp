#include "dialog_einstellungen.h"
#include "ui_dialog_einstellungen.h"

Dialog_einstellungen::Dialog_einstellungen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_einstellungen)
{
    ui->setupUi(this);
}

Dialog_einstellungen::~Dialog_einstellungen()
{
    delete ui;
}

void Dialog_einstellungen::set_einstellungen(settings einstellungen)
{
    set = einstellungen;
    ui->spinBox_anz_ur_prg->setValue(set.anz_undo_prg_int());
    ui->spinBox_anz_ur_wkz->setValue(set.anz_undo_wkz_int());
    if(set.option_path_opendialog() == "post")
    {
        ui->radioButton_stdpath_opendialog_post->setChecked(true);
    }else
    {
        ui->radioButton_stdpath_opendialog_user->setChecked(true);
    }
    ui->lineEdit_userpath_opendialog->setText(set.userpath_opendialog());
}

settings Dialog_einstellungen::einstellungen()
{
    set.set_anz_undo_prg(ui->spinBox_anz_ur_prg->value());
    set.set_anz_undo_wkz(ui->spinBox_anz_ur_wkz->value());
    if(ui->radioButton_stdpath_opendialog_post->isChecked())
    {
        set.set_option_path_opendialog_post();
    }else
    {
        set.set_option_path_opendialog_user();
    }
    set.set_userpath_opendialog(ui->lineEdit_userpath_opendialog->text());

    return set;
}

void Dialog_einstellungen::on_pushButton_userpath_opendialog_clicked()
{
    if(set.userpath_opendialog().isEmpty())
    {
        set.set_userpath_opendialog("./");
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Standart-Order des Öffnen-Dialogs"), set.userpath_opendialog());
    if(!tmp.isEmpty())
    {
        set.set_userpath_opendialog(tmp);
        ui->lineEdit_userpath_opendialog->setText(tmp);
    }
}

void Dialog_einstellungen::on_pushButton_ok_clicked()
{
    this->close();
    emit signalSendEinsellungen(einstellungen());
}

void Dialog_einstellungen::on_pushButton_abbrechen_clicked()
{
    this->close();
}
