#ifndef DIALOG_SAEGE_H
#define DIALOG_SAEGE_H

#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Defines/define_wkz.h"
#include "Defines/define_wkz_saege.h"
#include "Klassen/wkz_saege.h"

namespace Ui {
class Dialog_saege;
}

class Dialog_saege : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);

public:
    explicit Dialog_saege(QWidget *parent = NULL);
    ~Dialog_saege();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();
    void on_lineEdit_nr_textChanged();

private:
    Ui::Dialog_saege *ui;
    void clear();
    bool openToModifyData;
    QString dialogDataToString();
    void loadwkzbild();
};

#endif // DIALOG_SAEGE_H
