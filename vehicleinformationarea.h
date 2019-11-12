#ifndef VEHICLEINFORMATIONAREA_H
#define VEHICLEINFORMATIONAREA_H

#include <mybase.h>

namespace Ui {
    class VehicleInformationArea;
}

class VehicleInformationArea : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleInformationArea(QWidget *parent = 0);
    ~VehicleInformationArea();
    void updatePage();

private:
    Ui::VehicleInformationArea *ui;
    int m_confirmfaultIndex,m_deletefaultIndex;

private slots:
    void on_BTNConfirmFault_released();
    void on_BTNConfirmFault_pressed();
};

#endif // VEHICLEINFORMATIONAREA_H
