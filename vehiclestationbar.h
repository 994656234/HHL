#ifndef VEHICLESTATIONBAR_H
#define VEHICLESTATIONBAR_H
#include "qhash.h"
#include <mybase.h>

namespace Ui {
    class VehicleStationBar;
}

class VehicleStationBar : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleStationBar(QWidget *parent = 0);
    ~VehicleStationBar();
    void updatePage();

private:
    Ui::VehicleStationBar *ui;
    QHash<int, QString> m_StationIDHash;
    QHash<int, QString> m_StationID;

    void SetAutoStation();
    void SetSemiAutoStation();
};

#endif // VEHICLESTATIONBAR_H
