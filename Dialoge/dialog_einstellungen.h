#ifndef DIALOG_EINSTELLUNGEN_H
#define DIALOG_EINSTELLUNGEN_H

#include <QDialog>
#include <QFileDialog>
#include "eigeneKlassen/settings.h"

namespace Ui {
class Dialog_einstellungen;
}

class Dialog_einstellungen : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_einstellungen(QWidget *parent = nullptr);
    ~Dialog_einstellungen();
    void set_einstellungen(settings einstellungen);
    settings einstellungen();

private slots:
    void on_pushButton_userpath_opendialog_clicked();
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

signals:
    void signalSendEinsellungen(settings s);

private:
    Ui::Dialog_einstellungen *ui;
    settings set;
};

#endif // DIALOG_EINSTELLUNGEN_H
