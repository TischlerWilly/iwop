#ifndef DIALOG_STULP_H
#define DIALOG_STULP_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Klassen/text_zeilenweise.h"
#include "Defines/define_stulp.h"

namespace Ui {
class Dialog_stulp;
}

class Dialog_stulp : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);
    void signalNeedWKZ(QString dlgtyp);

public:
    explicit Dialog_stulp(QWidget *parent = nullptr);
    ~Dialog_stulp();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);
    void getWKZlist(text_zeilenweise list);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_stulp *ui;
    bool openToModifyData;
    text_zeilenweise wkzlist;
    QString dialogDataToString();
    void update_wkzlist();
    void update_comboboxWKZ();
};

#endif // DIALOG_STULP_H
