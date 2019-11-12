#ifndef VEHICLETRAINAREA_H
#define VEHICLETRAINAREA_H
#include "qlabel.h"

#include <mybase.h>

namespace Ui {
    class VehicleTrainArea;
}

class VehicleTrainArea : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleTrainArea(QWidget *parent = 0);
    ~VehicleTrainArea();
    void updatePage();

private:
    Ui::VehicleTrainArea *ui;
    void setDoorStatus(QLabel *label,QList<bool> status);
    QList<bool> DOORstatus;
    void setPantoStatus(QLabel* label,unsigned char status);
};

#endif // VEHICLETRAINAREA_H
