#ifndef VEHICLESETPAGE_H
#define VEHICLESETPAGE_H
#include "mybase.h"

#include <QWidget>

namespace Ui {
    class VehicleSetPage;
}

class VehicleSetPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleSetPage(QWidget *parent = 0);
    ~VehicleSetPage();

private:
    Ui::VehicleSetPage *ui;

private slots:
    void on_BTN_setCut_pressed();
    void on_BTN_setTime_pressed();
    void on_BTNHome_pressed();
    void on_BTN_setBrakeTest_pressed();
    void on_BTN_setLight_pressed();
    void on_BTN_setBrakeParam_pressed();
    void on_BTN_setAirCondition_pressed();
    void on_BTN_queryStation_pressed();
};

#endif // VEHICLESETPAGE_H
