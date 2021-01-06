#ifndef DIALOG_HBEXP_H
#define DIALOG_HBEXP_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/define_hbexp.h"

namespace Ui {
class Dialog_hbexp;
}

class Dialog_hbexp : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_hbexp(QWidget *parent = NULL);
    ~Dialog_hbexp();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_hbexp *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_HBEXP_H
