#ifndef VEHICLEAIRCONDITIONERPAGE_H
#define VEHICLEAIRCONDITIONERPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class VehicleAirConditionerPage;
}

class VehicleAirConditionerPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleAirConditionerPage(QWidget *parent = 0);
    ~VehicleAirConditionerPage();
    void updatePage();
    void getAirConditionStatus(QLabel *label, unsigned char status, bool online);
    void getAirConditionDeload(QLabel *label, bool status, bool online);

private:
    Ui::VehicleAirConditionerPage *ui;
    QList<bool> HVACstatus;
};

#endif // VEHICLEAIRCONDITIONERPAGE_H
