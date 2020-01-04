#ifndef DIALOG_LOREIAE_H
#define DIALOG_LOREIAE_H

#include <QDialog>
#include <QDir>
#include "myDefines.h"
#include "eigeneFunktionen/text.h"
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneDefines/define_loreiae.h"

namespace Ui {
class Dialog_loreiae;
}

class Dialog_loreiae : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_loreiae(QWidget *parent = nullptr);
    ~Dialog_loreiae();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_loreiae *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_LOREIAE_H
