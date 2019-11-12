#ifndef VEHICLESETINTENSITYCONTROLPAGE_H
#define VEHICLESETINTENSITYCONTROLPAGE_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class VehicleSetIntensityControlPage;
}

class VehicleSetIntensityControlPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleSetIntensityControlPage(QWidget *parent = 0);
    ~VehicleSetIntensityControlPage();

private:
    Ui::VehicleSetIntensityControlPage *ui;
    float m_BrightValuefactor;

private slots:
    void pushButtonPressedEvent();
};

#endif // VEHICLESETINTENSITYCONTROLPAGE_H
