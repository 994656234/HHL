#ifndef VEHICLESETSTATIONPAGE_H
#define VEHICLESETSTATIONPAGE_H
#include "mybase.h"
#include "qhash.h"
#include "qpushbutton.h"

#include <QWidget>


namespace Ui {
    class VehicleSetStationPage;
}

class VehicleSetStationPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleSetStationPage(QWidget *parent = 0);
    ~VehicleSetStationPage();
    static QString flag;

private:
    Ui::VehicleSetStationPage *ui;
    QList<QPushButton*> buttons;
    QHash<QString,int> station;


private slots:
    void on_BTNChangeOrigin_Terminal_pressed();
    void on_BTNTerminal_pressed();
    void on_BTNOriginStation_pressed();
    void on_BTN9_pressed();
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
    void buttonPushEvent();
};

#endif // VEHICLESETSTATIONPAGE_H
