#ifndef VEHICLEAIRCOMPRESSORPAGE_H
#define VEHICLEAIRCOMPRESSORPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class VehicleAirCompressorPage;
}

class VehicleAirCompressorPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleAirCompressorPage(QWidget *parent = 0);
    ~VehicleAirCompressorPage();
    void updatePage();
    void setACPStatus(QLabel *label,QList<bool> status);

private:
    Ui::VehicleAirCompressorPage *ui;
    QList<bool> ACPstatus;
};

#endif // VEHICLEAIRCOMPRESSORPAGE_H
