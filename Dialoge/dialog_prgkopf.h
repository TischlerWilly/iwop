#ifndef DIALOGPRGKOPF_H
#define DIALOGPRGKOPF_H

#include <QDialog>
#include <QDir>
#include "Klassen/prgpfade.h"
#include "myDefines.h"
#include "Funktionen/text.h"
#include "Funktionen/umwandeln.h"
#include "Defines/define_prgkopf.h"

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
    explicit DialogPrgKopf(QWidget *parent = NULL);
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
