#ifndef VEHICLESTATUSAREA_H
#define VEHICLESTATUSAREA_H

#include <mybase.h>
#include "qpushbutton.h"
#include "qlabel.h"
#include "qtimer.h"
#include "QTime"
#include "emdialogpage.h"
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

    void setLabelStatus(unsigned short int status,unsigned short int &t_status,QPushButton* btn,QString Faultstr,QString Warningstr,QString Normalstr);



    QList<QString> Btnstatus,Btnactions;
private slots:

    void changeTrainStatus();
    void doorPushButtonEvent();



};

#endif // VEHICLESTATUSAREA_H
