#ifndef DIALOG_SAEGE_H
#define DIALOG_SAEGE_H

#include <QDialog>
#include <QDir>
#include "eigeneFunktionen/text.h"
#include "eigeneFunktionen/umwandeln.h"
#include "eigeneKlassen/prgpfade.h"
#include "myDefines.h"
#include "eigeneDefines/define_wkz.h"
#include "eigeneDefines/define_wkz_saege.h"
#include "eigeneKlassen/wkz_saege.h"

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
    explicit Dialog_saege(QWidget *parent = nullptr);
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
