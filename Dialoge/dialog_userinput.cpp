#include "dialog_userinput.h"
#include "ui_dialog_userinput.h"

Dialog_userinput::Dialog_userinput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_userinput)
{
    ui->setupUi(this);
}

Dialog_userinput::~Dialog_userinput()
{
    delete ui;
}

void Dialog_userinput::on_pushButton_ok_clicked()
{
    QString msg = ui->lineEdit->text();
    emit send_input(msg);
    this->close();
}

void Dialog_userinput::set_default(QString d)
{
    ui->lineEdit->setText(d);
}


