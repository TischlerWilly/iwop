#ifndef DIALOG_FRAESER_H
#define DIALOG_FRAESER_H

#include <QDialog>
#include <QDir>
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Defines/define_wkz.h"
#include "Defines/define_wkz_fraeser.h"
#include "Klassen/wkz_fraeser.h"

#include <QMessageBox>

namespace Ui {
class Dialog_fraeser;
}

class Dialog_fraeser : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);

public:
    explicit Dialog_fraeser(QWidget *parent = nullptr);
    ~Dialog_fraeser();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();
    void on_lineEdit_nr_textChanged();

private:
    Ui::Dialog_fraeser *ui;
    void clear();
    bool openToModifyData;
    QString dialogDataToString();
    void loadwkzbild();
};

#endif // DIALOG_FRAESER_H
