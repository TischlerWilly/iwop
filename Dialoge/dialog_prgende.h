#ifndef DIALOG_PRGENDE_H
#define DIALOG_PRGENDE_H

#include <QDialog>
#include <QDir>
#include "myDefines.h"
#include "eigeneFunktionen/text.h"
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneDefines/define_prgende.h"

namespace Ui {
class Dialog_prgende;
}

class Dialog_prgende : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_prgende(QWidget *parent = nullptr);
    ~Dialog_prgende();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_prgende *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_PRGENDE_H
