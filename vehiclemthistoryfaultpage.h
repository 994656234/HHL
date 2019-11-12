#ifndef VEHICLEMTHISTORYFAULTPAGE_H
#define VEHICLEMTHISTORYFAULTPAGE_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class VehicleMTHistoryFaultPage;
}

class VehicleMTHistoryFaultPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleMTHistoryFaultPage(QWidget *parent = 0);
    ~VehicleMTHistoryFaultPage();

private:
    Ui::VehicleMTHistoryFaultPage *ui;
private slots:
    void pushButtonPressedEvent();
};

#endif // VEHICLEMTHISTORYFAULTPAGE_H
