#ifndef VEHICLERUNSTATEPAGE_H
#define VEHICLERUNSTATEPAGE_H

#include <QWidget>
#include "mybase.h"

namespace Ui {
    class VehicleRunStatePage;
}

class VehicleRunStatePage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleRunStatePage(QWidget *parent = 0);
    ~VehicleRunStatePage();
    void updatePage();
    void showEvent(QShowEvent *);

private:
    Ui::VehicleRunStatePage *ui;
};

#endif // VEHICLERUNSTATEPAGE_H
