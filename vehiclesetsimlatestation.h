#ifndef VEHICLESETSIMLATESTATION_H
#define VEHICLESETSIMLATESTATION_H
#include "mybase.h"
#include "stationchoicebox.h"
#include "qtimer.h"
#include "qbuttongroup.h"


#include <QWidget>

namespace Ui {
class VehicleSetSimlateStation;
}

class VehicleSetSimlateStation : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleSetSimlateStation(QWidget *parent = 0);
    ~VehicleSetSimlateStation();

private slots:
    void on_BTN1_pressed();
    void on_BTNHome_pressed();
    void on_PB_currentStation_pressed();

    void on_PB_nextStation_pressed();

    void on_PB_beginStation_pressed();

    void on_PB_terminalStation_pressed();

    void on_PB_jempStation_pressed();
    void timeoutEvent1();
    void timeoutEvent2();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_15_pressed();

    void on_pushButton_16_pressed();
    void radioButtonClick();

private:
    Ui::VehicleSetSimlateStation *ui;
    StationChoiceBox *stationChoiceBox;
    int currentStationId,nextStationId,beginStationId,terminalStationId;
    QString currentStationName,nextStationName,beginStationName,terminalStationName;
    QList<int> jumpStationId;
    void updatePage();
    int mode;
    QTimer *qTimer1,*qTimer2;
    QList<bool> jumpStatus;
    void allButtonsRelease();
    void allButtonsUnable();
    void allButtonsEnable();
    QButtonGroup *btnGroupLine;

};

#endif // VEHICLESETSIMLATESTATION_H
