#ifndef DIALOG_VAR10_H
#define DIALOG_VAR10_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/define_var10.h"

namespace Ui {
class Dialog_var10;
}

class Dialog_var10 : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_var10(QWidget *parent = NULL);
    ~Dialog_var10();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_var10 *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_VAR10_H
