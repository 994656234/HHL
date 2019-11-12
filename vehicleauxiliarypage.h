#ifndef VEHICLEAUXILIARYPAGE_H
#define VEHICLEAUXILIARYPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class VehicleAuxiliaryPage;
}

class VehicleAuxiliaryPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleAuxiliaryPage(QWidget *parent = 0);
    ~VehicleAuxiliaryPage();
    void updatePage();

private:
    Ui::VehicleAuxiliaryPage *ui;
    QList<bool> BCMStatus;
    void setSIVStatus(QLabel *label,bool unknow,bool status);
    void setBCMStatus(QLabel *label,QList<bool> status);
};

#endif // VEHICLEAUXILIARYPAGE_H
