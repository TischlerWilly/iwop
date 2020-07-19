#include "dialog_schnellaenderung.h"
#include "ui_dialog_schnellaenderung.h"

Dialog_schnellaenderung::Dialog_schnellaenderung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_schnellaenderung)
{
    ui->setupUi(this);
    Startzeile = 0;
    Menge = 0;
    Param_alle.set_text("Ausführbedingung");
    Param_bohr = Param_alle;
    Param_bohr.zeile_anhaengen("Bohrgruppe");
    Param_bohr.zeile_anhaengen("Durchmesser");
    Param_bohr.zeile_anhaengen("Tiefe");
    Param_nut = Param_alle;
    Param_nut.zeile_anhaengen("Breite");
    Param_nut.zeile_anhaengen("Tiefe");
    Param_kta = Param_alle;
    Param_kta.zeile_anhaengen("Durchmesser");
    Param_kta.zeile_anhaengen("Tiefe");
    Param_rta = Param_alle;
    Param_rta.zeile_anhaengen("Länge");
    Param_rta.zeile_anhaengen("Breite");
    Param_rta.zeile_anhaengen("Tiefe");
    Param_fauf = Param_alle;
    Param_fauf.zeile_anhaengen("Kantendicke");
    Param_fauf.zeile_anhaengen("Anfahrtyp");
    Param_fauf.zeile_anhaengen("Abfahrtyp");
    Param_fauf.zeile_anhaengen("Anfahrwert");
    Param_fauf.zeile_anhaengen("Abfahrwert");
}

Dialog_schnellaenderung::~Dialog_schnellaenderung()
{
    delete ui;
}

void Dialog_schnellaenderung::on_pushButton_ok_clicked()
{
    this->hide();
    emit sendData(tz);
}

void Dialog_schnellaenderung::on_pushButton_abbrechen_clicked()
{
    this->close();
}

void Dialog_schnellaenderung::getData(text_zeilenweise t, uint start, uint menge)
{
    tz = t;
    Startzeile = start;
    Menge = menge;
    Dialoge.set_text("ALLE");


    for(uint i = start; i <= start+menge-1; i++)
    {
        QString programmzeile = t.zeile(i);
        if(programmzeile.contains(DLG_BO) || \
           programmzeile.contains(DLG_BOY) || \
           programmzeile.contains(DLG_BOX) || \
           programmzeile.contains(DLG_LOREIAE) || \
           programmzeile.contains(DLG_LOREIMA) || \
           programmzeile.contains(DLG_TOPF) || \
           programmzeile.contains(DLG_HBEXP) || \
           programmzeile.contains(DLG_HBEXM) || \
           programmzeile.contains(DLG_HBEYP) || \
           programmzeile.contains(DLG_HBEYM))
        {
            if(!Dialoge.text().contains("Bohrungen"))
            {
                Dialoge.zeile_anhaengen("Bohrungen");
            }
        }else if(programmzeile.contains(DLG_NUT))
        {
            if(!Dialoge.text().contains("Nuten"))
            {
                Dialoge.zeile_anhaengen("Nuten");
            }
        }else if(programmzeile.contains(DLG_KTA))
        {
            if(!Dialoge.text().contains("Kreistaschen"))
            {
                Dialoge.zeile_anhaengen("Kreistaschen");
            }
        }else if(programmzeile.contains(DLG_RTA))
        {
            if(!Dialoge.text().contains("Rechteckstaschen"))
            {
                Dialoge.zeile_anhaengen("Rechteckstaschen");
            }
        }else if(programmzeile.contains(DLG_FAUF))
        {
            if(!Dialoge.text().contains("Fräseraufrufe"))
            {
                Dialoge.zeile_anhaengen("Fräseraufrufe");
            }
        }
    }

    ui->comboBox_dlg->clear();
    for(uint i = 1; i <=Dialoge.zeilenanzahl() ;i++)
    {
        ui->comboBox_dlg->addItem(Dialoge.zeile(i));
    }

    this->show();
}

void Dialog_schnellaenderung::on_comboBox_dlg_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_param->clear();
    if(arg1 == "ALLE")
    {
        for(uint i = 1; i <=Param_alle.zeilenanzahl() ;i++)
        {
            ui->comboBox_param->addItem(Param_alle.zeile(i));
        }
    }else if(arg1 == "Bohrungen")
    {
        for(uint i = 1; i <=Param_bohr.zeilenanzahl() ;i++)
        {
            ui->comboBox_param->addItem(Param_bohr.zeile(i));
        }
    }else if(arg1 == "Nuten")
    {
        for(uint i = 1; i <=Param_nut.zeilenanzahl() ;i++)
        {
            ui->comboBox_param->addItem(Param_nut.zeile(i));
        }
    }else if(arg1 == "Kreistaschen")
    {
        for(uint i = 1; i <=Param_kta.zeilenanzahl() ;i++)
        {
            ui->comboBox_param->addItem(Param_kta.zeile(i));
        }
    }else if(arg1 == "Rechteckstaschen")
    {
        for(uint i = 1; i <=Param_rta.zeilenanzahl() ;i++)
        {
            ui->comboBox_param->addItem(Param_rta.zeile(i));
        }
    }else if(arg1 == "Fräseraufrufe")
    {
        for(uint i = 1; i <=Param_fauf.zeilenanzahl() ;i++)
        {
            ui->comboBox_param->addItem(Param_fauf.zeile(i));
        }
    }
}

void Dialog_schnellaenderung::on_comboBox_param_currentIndexChanged()
{
    werte_ermitteln();
}

void Dialog_schnellaenderung::on_comboBox_alt_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "ALLE")
    {
        ui->lineEdit_neu->clear();
    }else
    {
        ui->lineEdit_neu->setText(arg1);
    }

}

void Dialog_schnellaenderung::on_pushButton_werte_aendern_clicked()
{
    QString dlg = ui->comboBox_dlg->currentText();
    QString par = ui->comboBox_param->currentText();
    QString wert_alt = ui->comboBox_alt->currentText();
    QString wert_neu = ui->lineEdit_neu->text();

    if(!wert_neu.isEmpty())
    {
        if(dlg == "ALLE")
        {
            if(par == "Ausführbedingung")
            {
                wert_aendern("AFB=", wert_alt, wert_neu);
                werte_ermitteln();
            }
        }else if(dlg == "Bohrungen")
        {
            if(par == "Ausführbedingung")
            {
                wert_aendern("AFB=", wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Bohrgruppe")
            {
                wert_aendern("GRP=", wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Durchmesser")
            {
                wert_aendern("DM=", wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Tiefe")
            {
                wert_aendern("TI=", wert_alt, wert_neu);
                werte_ermitteln();
            }
        }else if(dlg == "Nuten")
        {
            if(par == "Ausführbedingung")
            {
                wert_aendern(NUT_AFB, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Breite")
            {
                wert_aendern(NUT_B, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Tiefe")
            {
                wert_aendern(NUT_TI, wert_alt, wert_neu);
                werte_ermitteln();
            }
        }else if(dlg == "Kreistaschen")
        {
            if(par == "Ausführbedingung")
            {
                wert_aendern(KTA_AFB, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Durchmesser")
            {
                wert_aendern(KTA_DM, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Tiefe")
            {
                wert_aendern(KTA_TI, wert_alt, wert_neu);
                werte_ermitteln();
            }
        }else if(dlg == "Rechteckstaschen")
        {
            if(par == "Ausführbedingung")
            {
                wert_aendern(RTA_AFB, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Länge")
            {
                wert_aendern(RTA_L, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Breite")
            {
                wert_aendern(RTA_B, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Tiefe")
            {
                wert_aendern(RTA_TI, wert_alt, wert_neu);
                werte_ermitteln();
            }
        }else if(dlg == "Fräseraufrufe")
        {
            if(par == "Ausführbedingung")
            {
                wert_aendern(FAUF_AFB, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Kantendicke")
            {
                wert_aendern(FAUF_KADI, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Anfahrtyp")
            {
                wert_aendern(FAUF_ANTYP, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Abfahrtyp")
            {
                wert_aendern(FAUF_ABTYP, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Anfahrwert")
            {
                wert_aendern(FAUF_ANWEG, wert_alt, wert_neu);
                werte_ermitteln();
            }else if(par == "Abfahrwert")
            {
                wert_aendern(FAUF_ABWEG, wert_alt, wert_neu);
                werte_ermitteln();
            }
        }
    }else
    {
        QString msg;
        msg = "Sie haben keinen neunen Wert definiert!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
    }

}

void Dialog_schnellaenderung::werte_ermitteln()
{
    ui->comboBox_alt->clear(); //Jetige Werte des Paramters
    QString dlg = ui->comboBox_dlg->currentText();
    QString par = ui->comboBox_param->currentText();
    text_zeilenweise werte_alt;
    werte_alt.set_text("ALLE");

    if(ui->comboBox_dlg->currentText() == "ALLE")
    {
        for(uint i = Startzeile; i <= Startzeile+Menge-1; i++)
        {
            QString programmzeile = tz.zeile(i);
            QString parname = "AFB=";
            QString wert = selektiereEintrag(programmzeile, parname, ENDPAR);
            bool vorhanden = false;
            for(uint ii=1; ii<=werte_alt.zeilenanzahl() ;ii++)
            {
                if(werte_alt.zeile(ii) == wert)
                {
                    vorhanden = true;
                    break; //for ii
                }
            }
            if(vorhanden == false && !wert.isEmpty())
            {
                werte_alt.zeile_anhaengen(wert);
            }
        }
    }else if(ui->comboBox_dlg->currentText() == "Bohrungen")
    {
        QString parname;
        if(par == "Ausführbedingung")
        {
            parname = "AFB=";
        }else if(par == "Bohrgruppe")
        {
            parname = "GRP=";
        }else if(par == "Durchmesser")
        {
            parname = "DM=";
        }else if(par == "Tiefe")
        {
            parname = "TI=";
        }
        for(uint i = Startzeile; i <= Startzeile+Menge-1; i++)
        {
            QString programmzeile = tz.zeile(i);
            if(programmzeile.contains(DLG_BO) || \
               programmzeile.contains(DLG_BOY) || \
               programmzeile.contains(DLG_BOX) || \
               programmzeile.contains(DLG_LOREIAE) || \
               programmzeile.contains(DLG_LOREIMA) || \
               programmzeile.contains(DLG_TOPF) || \
               programmzeile.contains(DLG_HBEXP) || \
               programmzeile.contains(DLG_HBEXM) || \
               programmzeile.contains(DLG_HBEYP) || \
               programmzeile.contains(DLG_HBEYM))
            {
                if(programmzeile.contains(parname))
                {
                    QString wert = selektiereEintrag(programmzeile, parname, ENDPAR);
                    bool vorhanden = false;
                    for(uint ii=1; ii<=werte_alt.zeilenanzahl() ;ii++)
                    {
                        if(werte_alt.zeile(ii) == wert)
                        {
                            vorhanden = true;
                            break; //for ii
                        }
                    }
                    if(vorhanden == false && !wert.isEmpty())
                    {
                        werte_alt.zeile_anhaengen(wert);
                    }
                }
            }
        }
    }else if(ui->comboBox_dlg->currentText() == "Nuten")
    {
        QString parname;
        if(par == "Ausführbedingung")
        {
            parname = NUT_AFB;
        }else if(par == "Breite")
        {
            parname = NUT_B;
        }else if(par == "Tiefe")
        {
            parname = NUT_TI;
        }
        for(uint i = Startzeile; i <= Startzeile+Menge-1; i++)
        {
            QString programmzeile = tz.zeile(i);
            if(programmzeile.contains(DLG_NUT))
            {
                if(programmzeile.contains(parname))
                {
                    QString wert = selektiereEintrag(programmzeile, parname, ENDPAR);
                    bool vorhanden = false;
                    for(uint ii=1; ii<=werte_alt.zeilenanzahl() ;ii++)
                    {
                        if(werte_alt.zeile(ii) == wert)
                        {
                            vorhanden = true;
                            break; //for ii
                        }
                    }
                    if(vorhanden == false && !wert.isEmpty())
                    {
                        werte_alt.zeile_anhaengen(wert);
                    }
                }
            }
        }
    }else if(ui->comboBox_dlg->currentText() == "Kreistaschen")
    {
        QString parname;
        if(par == "Ausführbedingung")
        {
            parname = KTA_AFB;
        }else if(par == "Durchmesser")
        {
            parname = KTA_DM;
        }else if(par == "Tiefe")
        {
            parname = KTA_TI;
        }
        for(uint i = Startzeile; i <= Startzeile+Menge-1; i++)
        {
            QString programmzeile = tz.zeile(i);
            if(programmzeile.contains(DLG_KTA))
            {
                if(programmzeile.contains(parname))
                {
                    QString wert = selektiereEintrag(programmzeile, parname, ENDPAR);
                    bool vorhanden = false;
                    for(uint ii=1; ii<=werte_alt.zeilenanzahl() ;ii++)
                    {
                        if(werte_alt.zeile(ii) == wert)
                        {
                            vorhanden = true;
                            break; //for ii
                        }
                    }
                    if(vorhanden == false && !wert.isEmpty())
                    {
                        werte_alt.zeile_anhaengen(wert);
                    }
                }
            }
        }
    }else if(ui->comboBox_dlg->currentText() == "Rechteckstaschen")
    {
        QString parname;
        if(par == "Ausführbedingung")
        {
            parname = RTA_AFB;
        }else if(par == "Länge")
        {
            parname = RTA_L;
        }else if(par == "Breite")
        {
            parname = RTA_B;
        }else if(par == "Tiefe")
        {
            parname = RTA_TI;
        }
        for(uint i = Startzeile; i <= Startzeile+Menge-1; i++)
        {
            QString programmzeile = tz.zeile(i);
            if(programmzeile.contains(DLG_RTA))
            {
                if(programmzeile.contains(parname))
                {
                    QString wert = selektiereEintrag(programmzeile, parname, ENDPAR);
                    bool vorhanden = false;
                    for(uint ii=1; ii<=werte_alt.zeilenanzahl() ;ii++)
                    {
                        if(werte_alt.zeile(ii) == wert)
                        {
                            vorhanden = true;
                            break; //for ii
                        }
                    }
                    if(vorhanden == false && !wert.isEmpty())
                    {
                        werte_alt.zeile_anhaengen(wert);
                    }
                }
            }
        }
    }else if(ui->comboBox_dlg->currentText() == "Fräseraufrufe")
    {
        QString parname;
        if(par == "Ausführbedingung")
        {
            parname = FAUF_AFB;
        }else if(par == "Kantendicke")
        {
            parname = FAUF_KADI;
        }else if(par == "Anfahrtyp")
        {
            parname = FAUF_ANTYP;
        }else if(par == "Abfahrtyp")
        {
            parname = FAUF_ABTYP;
        }else if(par == "Anfahrwert")
        {
            parname = FAUF_ANWEG;
        }else if(par == "Abfahrwert")
        {
            parname = FAUF_ABWEG;
        }
        for(uint i = Startzeile; i <= Startzeile+Menge-1; i++)
        {
            QString programmzeile = tz.zeile(i);
            if(programmzeile.contains(DLG_FAUF))
            {
                if(programmzeile.contains(parname))
                {
                    QString wert = selektiereEintrag(programmzeile, parname, ENDPAR);
                    bool vorhanden = false;
                    for(uint ii=1; ii<=werte_alt.zeilenanzahl() ;ii++)
                    {
                        if(werte_alt.zeile(ii) == wert)
                        {
                            vorhanden = true;
                            break; //for ii
                        }
                    }
                    if(vorhanden == false && !wert.isEmpty())
                    {
                        werte_alt.zeile_anhaengen(wert);
                    }
                }
            }
        }
    }

    ui->comboBox_alt->clear();
    for(uint i = 1; i <=werte_alt.zeilenanzahl() ;i++)
    {
        ui->comboBox_alt->addItem(werte_alt.zeile(i));
    }
}

void Dialog_schnellaenderung::wert_aendern(QString parname, QString wert_alt, QString wert_neu)
{
    for(uint i = Startzeile; i <= Startzeile+Menge-1; i++)
    {
        QString programmzeile = tz.zeile(i);
        QString wert = selektiereEintrag(programmzeile, parname, ENDPAR);
        QString vorher = parname + wert + ENDPAR;
        QString nachher = parname + wert_neu + ENDPAR;
        if(wert_alt == "ALLE")
        {
            programmzeile.replace(vorher, nachher);
        }else
        {
            if(wert == wert_alt)
            {
                programmzeile.replace(vorher, nachher);
            }
        }
        tz.zeile_ersaetzen(i, programmzeile);
    }
}
