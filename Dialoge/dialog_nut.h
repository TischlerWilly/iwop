#ifndef DIALOG_NUT_H
#define DIALOG_NUT_H

#include <QDialog>
#include <QDir>
#include "eigeneKlassen/prgpfade.h"
#include "myDefines.h"
#include "eigeneFunktionen/text.h"
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneKlassen/text_zeilenweise.h"
#include "eigeneDefines/define_nut.h"

namespace Ui {
class Dialog_nut;
}

class Dialog_nut : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);
    void signalNeedWKZ(QString dlgtyp);

public:
    explicit Dialog_nut(QWidget *parent = nullptr);
    ~Dialog_nut();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);
    void getWKZlist(text_zeilenweise list);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_nut *ui;
    bool openToModifyData;
    text_zeilenweise wkzlist;
    QString dialogDataToString();
    void update_wkzlist();
    void update_comboboxWKZ();
};

#endif // DIALOG_NUT_H
