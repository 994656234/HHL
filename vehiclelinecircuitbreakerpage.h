#ifndef VEHICLELINECIRCUITBREAKERPAGE_H
#define VEHICLELINECIRCUITBREAKERPAGE_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class VehicleLineCircuitBreakerPage;
}

class VehicleLineCircuitBreakerPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleLineCircuitBreakerPage(QWidget *parent = 0);
    ~VehicleLineCircuitBreakerPage();
    void updatePage();
    void timerEvent(QTimerEvent *e);

private:
    Ui::VehicleLineCircuitBreakerPage *ui;
    QList<QPushButton *> ResetButtons;
    QList<bool* > ResetSignals;
    int timer2s[8];
private slots:
    void RstButtonsPressEvent();
};

#endif // VEHICLELINECIRCUITBREAKERPAGE_H
