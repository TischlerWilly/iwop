#ifndef DIALOG_TOPF_H
#define DIALOG_TOPF_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/define_topf.h"

namespace Ui {
class Dialog_topf;
}

class Dialog_topf : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_topf(QWidget *parent = NULL);
    ~Dialog_topf();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_topf *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_TOPF_H
