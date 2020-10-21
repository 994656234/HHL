#ifndef VEHICLESTATUSAREA_H
#define VEHICLESTATUSAREA_H

#include <mybase.h>
#include "qpushbutton.h"
#include "qlabel.h"
#include "qtimer.h"
#include "QTime"
#include "emdialogpage.h"
#include "emdooropen.h"
namespace Ui {
    class VehicleStatusArea;
}

class VehicleStatusArea : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleStatusArea(QWidget *parent = 0);
    ~VehicleStatusArea();
    void setProgressBar(bool tract,bool brake, unsigned short value ,bool quickBrake);
    void timerEvent(QTimerEvent *e);
    void updatePage();
    void refreshAllButton();
    void hideLabel();
    void showEvent(QTimerEvent *e);
    bool fangyouFlag;
    int isDoorEmOpen();
    static int emDooropenflag;




private:
    Ui::VehicleStatusArea *ui;
    QList<QPushButton*> buttons;
    QList<QPushButton*> doorPushButton;

    unsigned short lifeSignal;


    QList<QLabel*> labels;
    QList<bool *> boorStatus;
    int time3s[4];
    QTimer *time2s;
    bool fireflag;
    EMDialogPage* emDialogPage;
    EmDoorOPen* emDoorOpen;



    void setLabelStatus(unsigned short int status,unsigned short int &t_status,QPushButton* btn,QString Faultstr,QString Warningstr,QString Normalstr);



    QList<QString> Btnstatus,Btnactions;
private slots:

    void changeTrainStatus();
    void firePushButtonEvent();




    void on_BTNEmergencyBrocast_pressed();
    void on_BTN_fangyou_pressed();
};

#endif // VEHICLESTATUSAREA_H
