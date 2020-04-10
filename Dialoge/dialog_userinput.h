#ifndef DIALOG_USERINPUT_H
#define DIALOG_USERINPUT_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Dialog_userinput;
}

class Dialog_userinput : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_userinput(QWidget *parent = nullptr);
    ~Dialog_userinput();
    void set_default(QString d);

signals:
    void send_input(QString input);

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::Dialog_userinput *ui;
};

#endif // DIALOG_USERINPUT_H
