#ifndef DIALOG_LAGE_AENDERN_H
#define DIALOG_LAGE_AENDERN_H

#include <QDialog>
#include <QDir>
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/define_lage_aendern.h"
#include <QMessageBox>

namespace Ui {
class Dialog_lage_aendern;
}

class Dialog_lage_aendern : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit Dialog_lage_aendern(QWidget *parent = nullptr);
    ~Dialog_lage_aendern();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_lage_aendern *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOG_LAGE_AENDERN_H
