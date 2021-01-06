#ifndef DIALOG_KOM_H
#define DIALOG_KOM_H

#include <QDialog>
#include <QDir>
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/defines_kom.h"

namespace Ui {
class Dialog_kom;
}

class Dialog_kom : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_kom(QWidget *parent = NULL);
    ~Dialog_kom();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_kom *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_KOM_H
