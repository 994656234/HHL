#ifndef VEHICLESETBRAKETESTPAGE_H
#define VEHICLESETBRAKETESTPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class VehicleSetBrakeTestPage;
}

class VehicleSetBrakeTestPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleSetBrakeTestPage(QWidget *parent = 0);
    ~VehicleSetBrakeTestPage();
    void timerEvent(QTimerEvent *e);
    void updatePage();

private:
    Ui::VehicleSetBrakeTestPage *ui;
    QList<QPushButton *> testButtons;
    QList<bool* > testSignals;
    int timer2s[2];
private slots:
    void pushButtonPressedEvent();
    void TestButtonsPressEvent();
};

#endif // VEHICLESETBRAKETESTPAGE_H
