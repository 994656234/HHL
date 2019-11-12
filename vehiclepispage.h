#ifndef VEHICLEPISPAGE_H
#define VEHICLEPISPAGE_H
#include "mybase.h"

#include <QWidget>

namespace Ui {
    class VehiclePISPage;
}

class VehiclePISPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehiclePISPage(QWidget *parent = 0);
    ~VehiclePISPage();
    void updatePage();

private:
    Ui::VehiclePISPage *ui;
};

#endif // VEHICLEPISPAGE_H
