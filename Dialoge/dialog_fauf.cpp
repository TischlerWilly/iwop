#include "dialog_fauf.h"
#include "ui_dialog_fauf.h"

Dialog_fauf::Dialog_fauf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fauf)
{
    ui->setupUi(this);
    openToModifyData = false;
    ui->pushButton_ok->setDefault(true);

    prgpfade pf;
    QString bild1 = pf.path_dlgbilder_();
    bild1 += "fauf_1.bmp";
    QPixmap pix1(bild1);
    ui->label_bild->setPixmap(pix1);
    ui->label_bild->setScaledContents(true);//Bild skallieren

    QString bild2 = pf.path_dlgbilder_();
    bild2 += "fauf_2.bmp";
    QPixmap pix2(bild2);
    ui->label_bild_2->setPixmap(pix2);
    ui->label_bild_2->setScaledContents(true);//Bild skallieren
}

Dialog_fauf::~Dialog_fauf()
{
    delete ui;
}

void Dialog_fauf::on_pushButton_ok_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    if(openToModifyData)
    {
        openToModifyData = false;
        emit sendDialogDataModifyed(msg);
    } else
    {
        emit sendDialogData(msg);
    }
}

void Dialog_fauf::on_pushButton_esc_clicked()
{
    this->close();
}

void Dialog_fauf::on_pushButton_save_clicked()
{
    QString msg = dialogDataToString();
    this->hide();
    emit signalSaveConfig(msg);
}

QString Dialog_fauf::dialogDataToString()
{
    QString msg = DLG_FAUF ;

    msg += FAUF_WKZ;
    msg += ui->comboBox_wkz->currentText().replace("?", "");
    msg += ENDPAR;

    msg += FAUF_X;
    msg += ui->lineEdit_x->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_Y;
    msg += ui->lineEdit_y->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_Z;
    msg += ui->lineEdit_z->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_ERG;
    msg += ui->lineEdit_erg->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_KADI;
    msg += ui->lineEdit_kadi->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_KOR;
    msg += int_to_qstring(ui->spinBox_kor->value());
    msg += ENDPAR;

    msg += FAUF_ANTYP;
    msg += int_to_qstring(ui->spinBox_antyp->value());
    msg += ENDPAR;

    msg += FAUF_ABTYP;
    msg += int_to_qstring(ui->spinBox_abtyp->value());
    msg += ENDPAR;

    msg += FAUF_EINTYP;
    msg += ui->lineEdit_eintyp->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_ANWEG;
    msg += ui->lineEdit_anweg->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_ABWEG;
    msg += ui->lineEdit_abweg->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_ANVO;
    msg += ui->lineEdit_anvo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_VO;
    msg += ui->lineEdit_vo->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_DREHZ;
    msg += ui->lineEdit_drehz->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_EVERS;
    msg += ui->lineEdit_evers->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += FAUF_BEZ;
    msg += ui->lineEdit_bez->text();
    msg += ENDPAR;

    msg += FAUF_AFB;
    msg += ui->lineEdit_afb->text().toUpper().replace(",",".");
    msg += ENDPAR;

    msg += ENDE_ZEILE;
    return msg;
}

void Dialog_fauf::update_wkzlist()
{
    emit signalNeedWKZ(DLG_FAUF);
}

void Dialog_fauf::getWKZlist(text_zeilenweise list)
{
    wkzlist = list;
    update_comboboxWKZ();
}

void Dialog_fauf::update_comboboxWKZ()
{
    ui->comboBox_wkz->clear();
    for(uint i=1; i<= wkzlist.zeilenanzahl();i++)
    {
        ui->comboBox_wkz->addItem(wkzlist.zeile(i));
    }
}

void Dialog_fauf::getDialogData(QString text, bool openToChangeData)
{
    openToModifyData = openToChangeData;
    update_wkzlist();
    QString parname = FAUF_WKZ;
    QString tmp;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    //Werkzeug einsetzen:
    uint wkzindex = 0;
    for(uint i=1; i<= wkzlist.zeilenanzahl();i++)
    {
        if(tmp == wkzlist.zeile(i))
        {
            wkzindex = i;
        }
    }
    if(wkzindex > 0)
    {
        ui->comboBox_wkz->setCurrentIndex(wkzindex-1);
    }else
    {
        update_comboboxWKZ();
        ui->comboBox_wkz->addItem(tmp + "???");
        ui->comboBox_wkz->setCurrentIndex(wkzlist.zeilenanzahl());
    }

    parname = ENDPAR;
    parname += FAUF_X;
    ui->lineEdit_x->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_Y;
    ui->lineEdit_y->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_Z;
    ui->lineEdit_z->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_ERG;
    ui->lineEdit_erg->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_KADI;
    ui->lineEdit_kadi->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_KOR;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_kor->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += FAUF_ANTYP;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_antyp->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += FAUF_ABTYP;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->spinBox_abtyp->setValue(tmp.toInt());
    parname = ENDPAR;
    parname += FAUF_EINTYP;
    tmp = selektiereEintrag(text, parname, ENDPAR);
    ui->lineEdit_eintyp->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_ANWEG;
    ui->lineEdit_anweg->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_ABWEG;
    ui->lineEdit_abweg->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_ANVO;
    ui->lineEdit_anvo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_VO;
    ui->lineEdit_vo->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_DREHZ;
    ui->lineEdit_drehz->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_EVERS;
    ui->lineEdit_evers->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    parname = ENDPAR;
    parname += FAUF_BEZ;
    ui->lineEdit_bez->setText(selektiereEintrag(text, parname, ENDPAR));
    parname = ENDPAR;
    parname += FAUF_AFB;
    ui->lineEdit_afb->setText(selektiereEintrag(text, parname, ENDPAR).replace(".",","));
    this->show();
}

QString Dialog_fauf::get_default()
{
    QString msg;

    msg += FAUF_WKZ;
    msg += "IMA602";
    msg += ENDPAR;

    msg += FAUF_X;
    msg += "";
    msg += ENDPAR;

    msg += FAUF_Y;
    msg += "";
    msg += ENDPAR;

    msg += FAUF_Z;
    msg += "-2";
    msg += ENDPAR;

    msg += FAUF_ERG;
    msg += "0";
    msg += ENDPAR;

    msg += FAUF_KADI;
    msg += "0";
    msg += ENDPAR;

    msg += FAUF_KOR;
    msg += "2";
    msg += ENDPAR;

    msg += FAUF_ANTYP;
    msg += "0";
    msg += ENDPAR;

    msg += FAUF_ABTYP;
    msg += "0";
    msg += ENDPAR;

    msg += FAUF_EINTYP;
    msg += "0";
    msg += ENDPAR;

    msg += FAUF_ANWEG;
    msg += "2*WKZR";
    msg += ENDPAR;

    msg += FAUF_ABWEG;
    msg += "2*WKZR";
    msg += ENDPAR;

    msg += FAUF_ANVO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += FAUF_VO;
    msg += "AUTO";
    msg += ENDPAR;

    msg += FAUF_DREHZ;
    msg += "AUTO";
    msg += ENDPAR;

    msg += FAUF_EVERS;
    msg += "0.05";
    msg += ENDPAR;

    msg += FAUF_WKZAKT;
    msg += "1";
    msg += ENDPAR;

    msg += FAUF_BEZ;
    msg += "Aufruf Fräser";
    msg += ENDPAR;

    msg += FAUF_AFB;
    msg += "1";
    msg += ENDPAR;

    return msg;
}
