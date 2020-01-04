#ifndef DIALOG_HBEXM_H
#define DIALOG_HBEXM_H

#include <QDialog>
#include <QDir>
#include "myDefines.h"
#include "eigeneFunktionen/text.h"
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneDefines/define_hbexm.h"

namespace Ui {
class Dialog_hbexm;
}

class Dialog_hbexm : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_hbexm(QWidget *parent = nullptr);
    ~Dialog_hbexm();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_hbexm *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_HBEXM_H
