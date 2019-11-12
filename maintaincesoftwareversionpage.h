#ifndef MAINTAINCESOFTWAREVERSIONPAGE_H
#define MAINTAINCESOFTWAREVERSIONPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "doorversioncontrol.h"
#include "qlabel.h"
#include "riomlcuversioncontrol.h"
#include "MainGetDefaultPara.h"

#include <QWidget>

enum CurrentVerison
{
    TCMS1=0,
    RIOM_LCU,
    EDCU,
    OTHERS

};


namespace Ui {
    class MaintainceSoftwareVersionPage;
}

class MaintainceSoftwareVersionPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceSoftwareVersionPage(QWidget *parent = 0);
    ~MaintainceSoftwareVersionPage();
    void updatePage();
    QList<QPushButton*> buttons;

private:
    Ui::MaintainceSoftwareVersionPage *ui;
    DoorVersionControl* doorVersion;
    RIOMLCUVersionControl* riomlcuVersion;
    CurrentVerison currentVersion;
    QList<QLabel*>  line;
    void updateTCMSStatus(QList<QString> status,QList<QLabel*> labels);
    QList<QString>   line1Status,line2Status,line3Status,line4Status,line5Status,line6Status,
    line7Status,line8Status,line9Status,line10Status,line11Status;
    QString turnNumberToQString(unsigned char status);
    QString turnNumberToQString2(unsigned char status);
    QString turnNumberToQStringDoor(unsigned char status1,unsigned char status2);
    QString turnNumberToQStringSIV(unsigned char status1,unsigned char status2,unsigned char status3,unsigned char status4 );
    QString turnNumberToQStringLCU(unsigned char status);
    QString turnNumberToQStringDCU(unsigned short int status);
    QList<QString> doorStatus,RIOM_LCUStatus,OtherStatus;
    QString turnNumberToQStringHVAC(unsigned char status1,unsigned char status2);
    MainGetDefaultPara *getParam;

private slots:
    void on_BTN4_pressed();
    void on_BTN3_pressed();
    void on_BTN2_pressed();
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
    void pushBottonPressedEvent();
};

#endif // MAINTAINCESOFTWAREVERSIONPAGE_H
