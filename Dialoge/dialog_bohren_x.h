#ifndef DIALOG_BOHREN_X_H
#define DIALOG_BOHREN_X_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/define_boX.h"

namespace Ui {
class Dialog_bohren_x;
}

class Dialog_bohren_x : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_bohren_x(QWidget *parent = NULL);
    ~Dialog_bohren_x();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_bohren_x *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_BOHREN_X_H
