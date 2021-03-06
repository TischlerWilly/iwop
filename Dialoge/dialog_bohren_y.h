#ifndef DIALOG_BOHREN_Y_H
#define DIALOG_BOHREN_Y_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/define_boY.h"

namespace Ui {
class Dialog_bohren_y;
}

class Dialog_bohren_y : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_bohren_y(QWidget *parent = NULL);
    ~Dialog_bohren_y();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_bohren_y *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_BOHREN_Y_H
