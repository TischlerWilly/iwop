#ifndef DIALOG_HBEEINZ_H
#define DIALOG_HBEEINZ_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/define_hbeeinzeln.h"

namespace Ui {
class Dialog_hbeeinz;
}

class Dialog_hbeeinz : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_hbeeinz(QWidget *parent = nullptr);
    ~Dialog_hbeeinz();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_hbeeinz *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_HBEEINZ_H
