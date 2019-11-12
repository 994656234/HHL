#ifndef VEHICLERUNPAGE_H
#define VEHICLERUNPAGE_H

#include "basepage.h"
#include "ctrlspeedometer.h"
#include "QLabel"
namespace Ui {
    class VehicleRunPage;
}

class VehicleRunPage : public BasePage
{
    Q_OBJECT

public:
    explicit VehicleRunPage(QWidget *parent = 0);
    ~VehicleRunPage();
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);
    void updatePage();


private slots:

    void on_btn_VehicleRun_help_clicked();


    void on_BTNStationSet_pressed();

    void on_BTNCloseHelppage_pressed();


    void on_BTNBypass_pressed();

private:
    Ui::VehicleRunPage *ui;
    int count ;
    CtrlSpeedometer *Speedometer;

    void updateTrainStatus();
    void updateRunStatus();
    void setLowVoltageBarValue(int value1,int value2);
    void setTracBrakeBarValue(int value);

    void setDoorStatus(QLabel* lbl,QList<bool> signal);
    void setHVACStatus(QLabel* lbl,bool online,unsigned char signal);
    void setPISStatus(QLabel* lbl,QList<bool> signal);
    void setBCUStatus(QLabel* lbl,QList<bool> signal);
    void setTCUStatus(QLabel* lbl,QList<bool> signal);
    void setACUStatus(QLabel* lbl,QList<bool> signal);
    void setBCCUStatus(QLabel* lbl,QList<bool> signal);

    void setLableStatus(QLabel* lbl,bool value,QString styleTRUE,QString styleFALSE);
};

#endif // VEHICLERUNPAGE_H
