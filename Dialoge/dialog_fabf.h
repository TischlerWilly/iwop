#ifndef DIALOG_FABF_H
#define DIALOG_FABF_H

#include <QDialog>
#include <QDir>
#include "eigeneKlassen/prgpfade.h"
#include "myDefines.h"
#include "eigeneFunktionen/text.h"
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneDefines/define_fabf.h"

namespace Ui {
class Dialog_fabf;
}

class Dialog_fabf : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_fabf(QWidget *parent = nullptr);
    ~Dialog_fabf();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_fabf *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_FABF_H
