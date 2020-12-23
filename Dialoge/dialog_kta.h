#ifndef DIALOG_KTA_H
#define DIALOG_KTA_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Klassen/text_zeilenweise.h"
#include "Defines/define_kta.h"

namespace Ui {
class Dialog_kta;
}

class Dialog_kta : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);
    void signalNeedWKZ(QString dlgtyp);

public:
    explicit Dialog_kta(QWidget *parent = NULL);
    ~Dialog_kta();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);
    void getWKZlist(text_zeilenweise list);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_kta *ui;
    bool openToModifyData;
    text_zeilenweise wkzlist;
    QString dialogDataToString();
    void update_wkzlist();
    void update_comboboxWKZ();
};

#endif // DIALOG_KTA_H
