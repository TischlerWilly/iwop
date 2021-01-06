#ifndef DIALOG_LOREIMA_H
#define DIALOG_LOREIMA_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/define_loreima.h"

namespace Ui {
class Dialog_loreima;
}

class Dialog_loreima : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_loreima(QWidget *parent = NULL);
    ~Dialog_loreima();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_loreima *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_LOREIMA_H
