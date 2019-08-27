#ifndef DIALOGPRGKOPF_H
#define DIALOGPRGKOPF_H

#include <QDialog>
#include "myDefines.h"
#include "eigeneFunktionen/text.h"
#include "eigeneDefines/define_prgkopf.h"

namespace Ui {
class DialogPrgKopf;
}

class DialogPrgKopf : public QDialog
{
    Q_OBJECT

signals:
    void sendDialogData(QString text);
    void sendDialogDataModifyed(QString text);
    void signalSaveConfig(QString text);

public:
    explicit DialogPrgKopf(QWidget *parent = nullptr);
    ~DialogPrgKopf();
    QString get_default();

public slots:
    void getDialogData(QString text, bool openToChangeData);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_esc_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::DialogPrgKopf *ui;
    bool openToModifyData;
    QString dialogDataToString();
};

#endif // DIALOGPRGKOPF_H
