#ifndef DIALOG_SPIEGELN_H
#define DIALOG_SPIEGELN_H

#include <QDialog>
#include <QDir>
#include "myDefines.h"
#include "eigeneFunktionen/text.h"
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneDefines/define_spiegeln.h"

namespace Ui {
class Dialog_spiegeln;
}

class Dialog_spiegeln : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_spiegeln(QWidget *parent = nullptr);
    ~Dialog_spiegeln();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_spiegeln *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_SPIEGELN_H
