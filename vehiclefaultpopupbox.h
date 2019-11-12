#ifndef VEHICLEFAULTPOPUPBOX_H
#define VEHICLEFAULTPOPUPBOX_H
#include "mybase.h"

#include <QWidget>

namespace Ui {
    class VehicleFaultPopupBox;
}

class VehicleFaultPopupBox : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleFaultPopupBox(QWidget *parent = 0);
    ~VehicleFaultPopupBox();

private:
    Ui::VehicleFaultPopupBox *ui;
};

#endif // VEHICLEFAULTPOPUPBOX_H
