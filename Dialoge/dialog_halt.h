#ifndef DIALOG_HALT_H
#define DIALOG_HALT_H

#include <QDialog>
#include <QDir>
#include "eigeneKlassen/prgpfade.h"
#include "myDefines.h"
#include "eigeneFunktionen/text.h"
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneDefines/defines_halt.h"

namespace Ui {
class Dialog_halt;
}

class Dialog_halt : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_halt(QWidget *parent = nullptr);
    ~Dialog_halt();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_halt *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_HALT_H
