#ifndef VEHICLESETBRAKEPARAMPAGE_H
#define VEHICLESETBRAKEPARAMPAGE_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class VehicleSetBrakeParamPage;
}

class VehicleSetBrakeParamPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleSetBrakeParamPage(QWidget *parent = 0);
    ~VehicleSetBrakeParamPage();

private:
    Ui::VehicleSetBrakeParamPage *ui;
private slots:
    void pushButtonPressedEvent();
};

#endif // VEHICLESETBRAKEPARAMPAGE_H
