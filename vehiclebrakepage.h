#ifndef VEHICLEBRAKEPAGE_H
#define VEHICLEBRAKEPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class VehicleBrakePage;
}

class VehicleBrakePage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleBrakePage(QWidget *parent = 0);
    ~VehicleBrakePage();
    void updatePage();

private:
    Ui::VehicleBrakePage *ui;
    QList<bool> status;
    void brakeStatus(QLabel * lable ,QList<bool> status);
    void stopBrakeStatus(QLabel *label,bool status);
};

#endif // VEHICLEBRAKEPAGE_H
