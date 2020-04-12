#include "geofunktionen.h"

punkt drehen(punkt drehzentrum, punkt alter_punkt, \
             float drehwinkel, bool drehrichtung_im_uhrzeigersinn)
{
    if(drehwinkel == 0)
    {
        return alter_punkt;
    }else{
        punkt neuer_punkt;
        if(drehrichtung_im_uhrzeigersinn == true)
        {
            drehwinkel = -drehwinkel;
        }
        neuer_punkt.x = drehzentrum.x + (alter_punkt.x - drehzentrum.x)\
                *cos_d(drehwinkel) - (alter_punkt.y - drehzentrum.y)*sin_d(drehwinkel);
        neuer_punkt.y = drehzentrum.y + (alter_punkt.x - drehzentrum.x)\
                *sin_d(drehwinkel) + (alter_punkt.y - drehzentrum.y)*cos_d(drehwinkel);
        return neuer_punkt;
    }
}

punkt2d drehen(punkt2d drehzentrum, punkt2d alter_punkt, \
             float drehwinkel, bool drehrichtung_im_uhrzeigersinn)
{
    if(drehwinkel == 0)
    {
        return alter_punkt;
    }else{
        punkt2d neuer_punkt;
        if(drehrichtung_im_uhrzeigersinn == true)
        {
            drehwinkel = -drehwinkel;
        }
        neuer_punkt.set_x(\
                           drehzentrum.x() + (alter_punkt.x() - drehzentrum.x())\
                           *cos_d(drehwinkel) - (alter_punkt.y() - drehzentrum.y())\
                           *sin_d(drehwinkel)\
                           );
        neuer_punkt.set_y(\
                          drehzentrum.y() + (alter_punkt.x() - drehzentrum.x())\
                          *sin_d(drehwinkel) + (alter_punkt.y() - drehzentrum.y())\
                          *cos_d(drehwinkel)\
                          );
        return neuer_punkt;
    }
}

punkt3d drehen(punkt3d drehzentrum, punkt3d alter_punkt, \
             float drehwinkel, bool drehrichtung_im_uhrzeigersinn)
{
    if(drehwinkel == 0)
    {
        return alter_punkt;
    }else{
        punkt3d neuer_punkt;
        if(drehrichtung_im_uhrzeigersinn == true)
        {
            drehwinkel = -drehwinkel;
        }
        neuer_punkt.set_x(\
                           drehzentrum.x() + (alter_punkt.x() - drehzentrum.x())\
                           *cos_d(drehwinkel) - (alter_punkt.y() - drehzentrum.y())\
                           *sin_d(drehwinkel)\
                           );
        neuer_punkt.set_y(\
                          drehzentrum.y() + (alter_punkt.x() - drehzentrum.x())\
                          *sin_d(drehwinkel) + (alter_punkt.y() - drehzentrum.y())\
                          *cos_d(drehwinkel)\
                          );
        neuer_punkt.set_z(alter_punkt.z());
        return neuer_punkt;
    }
}
punkt drehen_ij(punkt drehzentrum, float drehwinkel, bool drehrichtung_im_uhrzeigersinn, \
                punkt bezugspunkt_ij, punkt punkt_ij)
{
    if(drehwinkel == 0)
    {
        return punkt_ij;
    }else{
        bezugspunkt_ij = drehen(drehzentrum, bezugspunkt_ij, \
                                drehwinkel, drehrichtung_im_uhrzeigersinn);
        punkt p;
        p.x = 0;
        p.y = 0;
        punkt_ij = drehen(p, punkt_ij, drehwinkel, drehrichtung_im_uhrzeigersinn);
        return punkt_ij;
    }
}

double winkel(double endpunkt_x, double endpunkt_y,\
              double mittelpunkt_x, double mittelpunkt_y)
{
    //berechnet wird immer der Winkel zur gedachten waagerechten Grundlinie
    //im Gegenuhrzeigersinn
    double wi, xdif, ydif;
    xdif = endpunkt_x - mittelpunkt_x;
    ydif = endpunkt_y - mittelpunkt_y;
    if(  (xdif > 0)  &&  (ydif == 0)  )
    {
        wi = 0;
    }else if(  (xdif < 0)  &&  (ydif == 0)  )
    {
        wi = 180;
    }else if(  (xdif == 0)  &&  (ydif > 0)  )
    {
        wi = 90;
    }else if(  (xdif == 0)  &&  (ydif < 0)  )
    {
        wi = 270;
    }else if(  (xdif > 0)  &&  (ydif > 0)  )
    {
        //tan(alpha) == Gegenkathete / Ankathete
        //tan(wi)    == ydif         / xdif
        wi = atan(ydif/xdif);
        wi = wi*180/M_PI;//Weil sonst Ergebnis in Bogenmaß;
    }else if(  (xdif < 0)  &&  (ydif > 0)  )
    {
        xdif = xdif * -1;
        wi = atan(ydif/xdif);
        wi = wi*180/M_PI;//Weil sonst Ergebnis in Bogenmaß;
        wi = 180 - wi;
    }else if(  (xdif < 0)  &&  (ydif < 0)  )
    {
        xdif = xdif * -1;
        ydif = ydif * -1;
        wi = atan(ydif/xdif);
        wi = wi*180/M_PI;//Weil sonst Ergebnis in Bogenmaß;
        wi = wi + 180;
    }else//(xdif > 0)  &&  (ydif < 0)
    {
        ydif = ydif * -1;
        wi = atan(ydif/xdif);
        wi = wi*180/M_PI;//Weil sonst Ergebnis in Bogenmaß;
        wi = 360 - wi;
    }
    return wi;
    /*
    punkt3d mipu;
    mipu.set_x(mittelpunkt_x);
    mipu.set_y(mittelpunkt_y);
    punkt3d enpu;
    enpu.set_x(endpunkt_x);
    enpu.set_y(endpunkt_y);
    strecke s;
    s.set_start(mipu);
    s.set_ende(enpu);

    double hypthenuse = s.laenge2dim();
    double gegenkathete = mittelpunkt_y - endpunkt_y;

    double wi =  asin(gegenkathete/hypthenuse)/M_PI*180*-1;//Weil sonst Ergebnis in Bogenmaß;

    if(endpunkt_x - mittelpunkt_x < 0   &&\
       wi > 0)
    {
        wi = 180-wi;
    }

    if(endpunkt_x - mittelpunkt_x < 0   &&\
       wi < 0)
    {
        wi = 180-wi;
    }else if(mittelpunkt_x - endpunkt_x < 0   &&\
             wi < 0)
    {
        wi = 360+wi;
    }else if(wi == 0)
    {
        if(mittelpunkt_x < endpunkt_x)
        {
            wi = 0;
        }else
        {
            wi = 180;
        }
    }
    if(wi == -90)
    {
        wi = 270;
    }
    */
}

double winkel(double endpunkt1_x, double endpunkt1_y,\
              double mittelpunkt_x, double mittelpunkt_y,\
              double endpunkt2_x, double endpunkt2_y)
{
    //sp, mipu, ep
    double w1 = winkel(endpunkt1_x, endpunkt1_y,\
                       mittelpunkt_x, mittelpunkt_y);

    double w2 = winkel(endpunkt2_x, endpunkt2_y,\
                       mittelpunkt_x, mittelpunkt_y);
    double wi;
    wi = w1 - w2;
    if(wi < 0)
    {
        wi = wi * -1;
    }
    if(w1 > w2)
    {
        wi = 360 - wi;
    }

    QString msg;
    msg += "Winkel 1: ";
    msg += double_to_qstring(w1);
    msg += "\n";
    msg += "Winkel 2: ";
    msg += double_to_qstring(w2);
    msg += "\n";
    msg += "Winkel: ";
    msg += double_to_qstring(wi);
    QMessageBox mb;
    mb.setText(msg);
    //mb.exec();

    return wi;
}

double winkel(punkt2d ep1, punkt2d mipu, punkt2d ep2)
{
    return winkel(ep1.x(), ep1.y(), mipu.x(), mipu.y(), ep2.x(), ep2.y());
}

double winkel(punkt3d ep1, punkt3d mipu, punkt3d ep2)
{
    return winkel(ep1.x(), ep1.y(), mipu.x(), mipu.y(), ep2.x(), ep2.y());
}

double winkel(punkt3d ep1, punkt2d mipu, punkt3d ep2)
{
    return winkel(ep1.x(), ep1.y(), mipu.x(), mipu.y(), ep2.x(), ep2.y());
}

void trimmen(QString *geo1, QString *geo2)
{
    QString text_a = *geo1;
    QString text_b = *geo2;
    if(text_a.contains(STRECKE) && text_b.contains(STRECKE))
    {
        strecke s1(text_a);
        strecke s2(text_b);

        if(s1.endpu() == s2.stapu())
        {
            return;
        }

        punkt3d schnittpunkt;
        schnittpunkt.set_z(s1.endpu().z());
        //Schnittpunkt der beiden Geraden berechnen:
        if(s1.stapu().x()!=s1.endpu().x()  &&  s2.stapu().x()!=s2.endpu().x())//sonst div/0 möglich
        {
            //Geradengleichungen aufstellen y = m*x + t:
            //m = (y2-y1):(x2-x1)
            double m1 = (  s1.endpu().y()-s1.stapu().y()  )  /  (  s1.endpu().x()-s1.stapu().x()  );
            double m2 = (  s2.endpu().y()-s2.stapu().y()  )  /  (  s2.endpu().x()-s2.stapu().x()  );
            //t = y1 - (m1*x1)
            double t1 = s1.stapu().y()  -  (m1*s1.stapu().x());
            double t2 = s2.stapu().y()  -  (m2*s2.stapu().x());
            //Geradengleichungen gleichsetzen:
            //m1*x+t1 = m2*x+t2     /-m2*x
            //(m1-m2)*x+t1 = t2     /-t1
            //(m1-m2)*x = t2-t1     / :(m1-m2)
            //x = (t2-t1):(m1-m2)
            double x = (t2-t1)/(m1-m2);
            //x in eine der beiden Gleichungen einsetzen:
            double y = m1*x+t1;

            schnittpunkt.set_x(x);
            schnittpunkt.set_y(y);
            s1.set_ende(schnittpunkt);
            s2.set_start(schnittpunkt);
        }else
        {
            if(s1.stapu().x()==s1.endpu().x()  &&  s2.stapu().x()!=s2.endpu().x())//s1 ist senkrecht
            {
                //heißt x von s1 ist bekannt
                //Geradengleichungen aufstellen für s2     y = m*x + t:
                double m = (  s2.endpu().y()-s2.stapu().y()  )  /  (  s2.endpu().x()-s2.stapu().x()  );
                //t = y1 - (m*x)
                double t = s2.stapu().y()  -  (m*s2.stapu().x());
                double x = s1.stapu().x();
                //x in die Gleichung einsetzen:
                double y = m*x+t;

                schnittpunkt.set_x(x);
                schnittpunkt.set_y(y);
                s1.set_ende(schnittpunkt);
                s2.set_start(schnittpunkt);
            }else if(s1.stapu().x()!=s1.endpu().x()  &&  s2.stapu().x()==s2.endpu().x())//s2 ist senkrecht
            {
                //heißt x von s2 ist bekannt
                //Geradengleichungen aufstellen für s1     y = m*x + t:
                double m = (  s1.endpu().y()-s1.stapu().y()  )  /  (  s1.endpu().x()-s1.stapu().x()  );
                //t = y - (m*x)
                double t = s1.stapu().y()  -  (m*s1.stapu().x());
                double x = s2.stapu().x();
                //x in die Gleichung einsetzen:
                double y = m*x+t;

                schnittpunkt.set_x(x);
                schnittpunkt.set_y(y);
                s1.set_ende(schnittpunkt);
                s2.set_start(schnittpunkt);
            }else
            {
                //beide geraden sind senkrecht
                //soetwas sollte nicht an die Funktion übergeben werden
            }
        }

        //Werte zurück in die geo-QStrings schreiben:
        *geo1 = s1.text();
        *geo2 = s2.text();

        //QMessageBox mb;
        //mb.setText("m1: " + double_to_qstring(m1) + "\nm2: " + double_to_qstring(m2));
        //mb.exec();
    }else if(text_a.contains(STRECKE) && text_b.contains(BOGEN))
    {
        strecke s(text_a);
        bogen b(text_b);

        if(s.endpu() == b.start())
        {
            return;
        }

        //Kreisformel aufstellen:
        //  mx = Kreismittelpunkt X-Wert
        //  my = Kreismittelpunkt Y-Wert
        //  r  = Kreisradius
        //  (x-mx)²+(y-my)²=r²
        double mx = b.mitte().x();
        double my = b.mitte().y();
        double r  = b.rad();

        //Geradenformel aufstellen:
        //  a*x + b*y = c
        //    x1 = X-Wert der vom Startpunkt der Strecke
        //    x2 = X-Wert der vom Endpunkt der Strecke
        //    y1 = Y-Wert der vom Startpunkt der Strecke
        //    y2 = Y-Wert der vom Endpunkt der Strecke
        double x1= s.stapu().x();
        double x2= s.endpu().x();
        double y1= s.stapu().y();
        double y2= s.endpu().y();
        // a = y1-y2
        // b = x2-x1
        // c = x2*y1 - x1*y2
        double var_a = y1-y2;
        double var_b = x2-x1;
        double var_c = x2*y1 - x1*y2;
        // d = c-a*mx-b*my
        double var_d = var_c-var_a*mx-var_b*my;
        // e = r²*(a²+b²)-d²
        double var_e = r*r * (var_a*var_a + var_b*var_b) - var_d*var_d;

        //QMessageBox mb;
        //mb.setText("e= " + double_to_qstring(var_e));
        //mb.exec();

        if(var_e == 0)
        {
            //Es gibt genau eine Lösung
            // x = mx+ a*d / (a²+b²)
            double var_x = mx+ var_a*var_d / (var_a*var_a + var_b*var_b);

            // y = my+ b*d / (a²+b²)
            double var_y = my+ var_b*var_d / (var_a*var_a + var_b*var_b);

            punkt3d p3d = s.endpu();
            p3d.set_x(var_x);
            p3d.set_y(var_y);
            s.set_ende(p3d);
            b.set_startpunkt(p3d);

        }else if(var_e > 0)
        {
            //Es gibt zwei Lösungen
            // x1 = mx+ (a*d + b* wurzel(e)) /  (a²+b²)
            // x2 = mx+ (a*d - b* wurzel(e)) /  (a²+b²)
            double var_x1 = mx+ (var_a*var_d + var_b*sqrt(var_e)) / (var_a*var_a + var_b*var_b);
            double var_x2 = mx+ (var_a*var_d - var_b*sqrt(var_e)) / (var_a*var_a + var_b*var_b);

            // y1 = my+ (b*d - a* wurzel(e)) /  (a²+b²)
            // y2 = my+ (b*d + a* wurzel(e)) /  (a²+b²)
            double var_y1 = my+ (var_b*var_d - var_a*sqrt(var_e)) / (var_a*var_a + var_b*var_b);
            double var_y2 = my+ (var_b*var_d + var_a*sqrt(var_e)) / (var_a*var_a + var_b*var_b);

            punkt3d p3d1 = s.endpu();
            punkt3d p3d2 = s.endpu();

            p3d1.set_x(var_x1);
            p3d1.set_y(var_y1);
            p3d2.set_x(var_x2);
            p3d2.set_y(var_y2);

            //entscheiden ob p3d1 oder p3d2 richtig sind
            double winkel_orgi = winkel(b.start().x(),b.start().y(),\
                                        b.ende().x(),b.ende().y(),\
                                        b.mitte().x(),b.mitte().y());
            double winkep_p3d1 = winkel(p3d1.x(),p3d1.y(),\
                                        b.ende().x(),b.ende().y(),\
                                        b.mitte().x(),b.mitte().y());
            double winkep_p3d2 = winkel(p3d2.x(),p3d2.y(),\
                                        b.ende().x(),b.ende().y(),\
                                        b.mitte().x(),b.mitte().y());
            double diff_1 = winkel_orgi - winkep_p3d1;
            if(diff_1 < 0)
            {
                diff_1 = -diff_1;
            }
            double diff_2 = winkel_orgi - winkep_p3d2;
            if(diff_2 < 0)
            {
                diff_2 = -diff_2;
            }
            if(diff_1 < diff_2)
            {
                s.set_ende(p3d1);
                b.set_startpunkt(p3d1);
            }else
            {
                s.set_ende(p3d2);
                b.set_startpunkt(p3d2);
            }
        }


        //Werte zurück in die geo-QStrings schreiben:
        *geo1 = s.text();
        *geo2 = b.text();

    }else if(text_a.contains(BOGEN) && text_b.contains(STRECKE))
    {
        bogen b(text_a);
        strecke s(text_b);

        if(b.ende() == s.stapu())
        {
            return;
        }

        //Kreisformel aufstellen:
        //  mx = Kreismittelpunkt X-Wert
        //  my = Kreismittelpunkt Y-Wert
        //  r  = Kreisradius
        //  (x-mx)²+(y-my)²=r²
        double mx = b.mitte().x();
        double my = b.mitte().y();
        double r  = b.rad();

        //Geradenformel aufstellen:
        //  a*x + b*y = c
        //    x1 = X-Wert der vom Startpunkt der Strecke
        //    x2 = X-Wert der vom Endpunkt der Strecke
        //    y1 = Y-Wert der vom Startpunkt der Strecke
        //    y2 = Y-Wert der vom Endpunkt der Strecke
        double x2= s.stapu().x();
        double x1= s.endpu().x();
        double y2= s.stapu().y();
        double y1= s.endpu().y();
        // a = y1-y2
        // b = x2-x1
        // c = x2*y1 - x1*y2
        double var_a = y1-y2;
        double var_b = x2-x1;
        double var_c = x2*y1 - x1*y2;
        // d = c-a*mx-b*my
        double var_d = var_c-var_a*mx-var_b*my;
        // e = r²*(a²+b²)-d²
        double var_e = r*r * (var_a*var_a + var_b*var_b) - var_d*var_d;

        //QMessageBox mb;
        //mb.setText("e= " + double_to_qstring(var_e));
        //mb.exec();

        if(var_e == 0)
        {
            //Es gibt genau eine Lösung
            // x = mx+ a*d / (a²+b²)
            double var_x = mx+ var_a*var_d / (var_a*var_a + var_b*var_b);

            // y = my+ b*d / (a²+b²)
            double var_y = my+ var_b*var_d / (var_a*var_a + var_b*var_b);

            punkt3d p3d = s.stapu();
            p3d.set_x(var_x);
            p3d.set_y(var_y);
            s.set_start(p3d);
            b.set_endpunkt(p3d);

        }else if(var_e > 0)
        {
            //Es gibt zwei Lösungen
            // x1 = mx+ (a*d + b* wurzel(e)) /  (a²+b²)
            // x2 = mx+ (a*d - b* wurzel(e)) /  (a²+b²)
            double var_x1 = mx+ (var_a*var_d + var_b*sqrt(var_e)) / (var_a*var_a + var_b*var_b);
            double var_x2 = mx+ (var_a*var_d - var_b*sqrt(var_e)) / (var_a*var_a + var_b*var_b);

            // y1 = my+ (b*d - a* wurzel(e)) /  (a²+b²)
            // y2 = my+ (b*d + a* wurzel(e)) /  (a²+b²)
            double var_y1 = my+ (var_b*var_d - var_a*sqrt(var_e)) / (var_a*var_a + var_b*var_b);
            double var_y2 = my+ (var_b*var_d + var_a*sqrt(var_e)) / (var_a*var_a + var_b*var_b);

            punkt3d p3d1 = s.stapu();
            punkt3d p3d2 = s.stapu();

            p3d1.set_x(var_x1);
            p3d1.set_y(var_y1);
            p3d2.set_x(var_x2);
            p3d2.set_y(var_y2);

            //entscheiden ob p3d1 oder p3d2 richtig sind
            double winkel_orgi = winkel(b.start().x(),b.start().y(),\
                                        b.ende().x(),b.ende().y(),\
                                        b.mitte().x(),b.mitte().y());
            double winkep_p3d1 = winkel(b.start().x(),b.start().y(),\
                                        p3d1.x(),p3d1.y(),\
                                        b.mitte().x(),b.mitte().y());
            double winkep_p3d2 = winkel(b.start().x(),b.start().y(),\
                                        p3d2.x(),p3d2.y(),\
                                        b.mitte().x(),b.mitte().y());
            double diff_1 = winkel_orgi - winkep_p3d1;
            if(diff_1 < 0)
            {
                diff_1 = -diff_1;
            }
            double diff_2 = winkel_orgi - winkep_p3d2;
            if(diff_2 < 0)
            {
                diff_2 = -diff_2;
            }
            if(diff_1 < diff_2)
            {
                s.set_start(p3d1);
                b.set_endpunkt(p3d1);
            }else
            {
                s.set_start(p3d2);
                b.set_endpunkt(p3d2);
            }
        }


        //Werte zurück in die geo-QStrings schreiben:
        *geo2 = s.text();
        *geo1 = b.text();
    }else if(text_a.contains(BOGEN) && text_b.contains(BOGEN))
    {
        bogen b1(text_a);
        bogen b2(text_b);

        if(b1.ende() == b2.start())
        {
            return;
        }

        //Kreisformel aufstellen:
        //  mx = Kreismittelpunkt X-Wert
        //  my = Kreismittelpunkt Y-Wert
        //  r  = Kreisradius
        //  (x-mx)²+(y-my)²=r²
        double mx1 = b1.mitte().x();
        double my1 = b1.mitte().y();
        double r1  = b1.rad();

        double mx2 = b2.mitte().x();
        double my2 = b2.mitte().y();
        double r2  = b2.rad();

        //Prüfen, wie weit die Kreise auseinander liegen
        strecke s;
        punkt3d tmp;
        tmp.set_x(b1.mitte().x());
        tmp.set_y(b1.mitte().y());
        s.set_start(tmp);
        tmp.set_x(b2.mitte().x());
        tmp.set_y(b2.mitte().y());
        s.set_ende(tmp);
        double abst = s.laenge2d();

        if(abst > r1+r2)//Kreise liegen zu weit auseinander
        {
            return;
        }else if(abst == r1+r2)//Kreise berühren sich in genau einem Punkt
        {
            strecke_bezugspunkt sb = strecke_bezugspunkt_start;
            s.set_laenge_2d(r1, sb);
            b1.set_endpunkt(s.endpu());
            b1.set_startpunkt(s.endpu());
        }else//Kreise schneiden sich in 2 Punkten
        {
            //http://walter.bislins.ch/blog/index.asp?page=Schnittpunkte+zweier+Kreise+berechnen+%28JavaScript%29

            double var_x = (r1*r1 + abst*abst - r2*r2) / (2*abst);
            double var_y = r1*r1 - var_x*var_x;
            if(var_y > 0)
            {
                var_y = sqrt(var_y);
            }
            double AB0 = mx2-mx1;
            double AB1 = my2-my1;
            double ex0 = AB0/abst;
            double ex1 = AB1/abst;
            double ey0 = -ex1;
            double ey1 =  ex0;
            double Q1x = mx1 + var_x * ex0;
            double Q1y = my1 + var_x * ex1;
            double Q2x = Q1x - var_y * ey0;
            double Q2y = Q1y - var_y * ey1;
            Q1x += var_y * ey0;
            Q1y += var_y * ey1;

            punkt3d p3d1 = b1.ende();
            punkt3d p3d2 = p3d1;
            p3d1.set_x(Q1x);
            p3d1.set_y(Q1y);
            p3d2.set_x(Q2x);
            p3d2.set_y(Q2y);

            //entscheiden ob p3d1 oder p3d2 richtig sind
            double winkel_orgi = winkel(b1.start().x(),b1.start().y(),\
                                        b1.ende().x(),b1.ende().y(),\
                                        b1.mitte().x(),b1.mitte().y());
            double winkep_p3d1 = winkel(b1.start().x(),b1.start().y(),\
                                        p3d1.x(),p3d1.y(),\
                                        b1.mitte().x(),b1.mitte().y());
            double winkep_p3d2 = winkel(b1.start().x(),b1.start().y(),\
                                        p3d2.x(),p3d2.y(),\
                                        b1.mitte().x(),b1.mitte().y());
            double diff_1 = winkel_orgi - winkep_p3d1;
            if(diff_1 < 0)
            {
                diff_1 = -diff_1;
            }
            double diff_2 = winkel_orgi - winkep_p3d2;
            if(diff_2 < 0)
            {
                diff_2 = -diff_2;
            }
            if(diff_1 < diff_2)
            {
                b1.set_endpunkt(p3d1);
                b2.set_startpunkt(p3d1);
            }else
            {
                b1.set_endpunkt(p3d2);
                b2.set_startpunkt(p3d2);
            }

        }


        //Werte zurück in die geo-QStrings schreiben:
        *geo1 = b1.text();
        *geo2 = b2.text();

    }
}

bool cagleich(punkt3d p1, punkt3d p2, double tolleranz = 0.1)
{
    if(  (  (p1.x() == p2.x()) || ((p1.x() - tolleranz <= p2.x()) && (p1.x() + tolleranz >= p2.x()))  )  && \
         (  (p1.y() == p2.y()) || ((p1.y() - tolleranz <= p2.y()) && (p1.y() + tolleranz >= p2.y()))  )  && \
         (  (p1.z() == p2.z()) || ((p1.z() - tolleranz <= p2.z()) && (p1.z() + tolleranz >= p2.z()))  )     )
    {
        return true;
    }else
    {
        return false;
    }
}
bool cagleich(punkt2d p1, punkt2d p2, double tolleranz = 0.1)
{
    if(  (  (p1.x() == p2.x()) || ((p1.x() - tolleranz <= p2.x()) && (p1.x() + tolleranz >= p2.x()))  )  && \
         (  (p1.y() == p2.y()) || ((p1.y() - tolleranz <= p2.y()) && (p1.y() + tolleranz >= p2.y()))  )      )
    {
        return true;
    }else
    {
        return false;
    }
}
bool cagleich(double p1, double p2, double tolleranz = 0.1)
{
    if(    (p1 == p2) || ((p1 - tolleranz <= p2) && (p1 + tolleranz >= p2))  )
    {
        return true;
    }else
    {
        return false;
    }
}
