#ifndef DIALOG_FGERADE_H
#define DIALOG_FGERADE_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/define_fgerade.h"

namespace Ui {
class Dialog_fgerade;
}

class Dialog_fgerade : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_fgerade(QWidget *parent = NULL);
    ~Dialog_fgerade();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_fgerade *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_FGERADE_H
