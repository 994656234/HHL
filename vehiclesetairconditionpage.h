#ifndef VEHICLESETAIRCONDITIONPAGE_H
#define VEHICLESETAIRCONDITIONPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qdebug.h"
#include "QTimer"

#include <QWidget>

namespace Ui {
    class VehicleSetAirConditionPage;
}

class VehicleSetAirConditionPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleSetAirConditionPage(QWidget *parent = 0);
    ~VehicleSetAirConditionPage();
    void timerEvent(QTimerEvent *e);
    void updatePage();
    void hideEvent(QHideEvent *);

private:
    Ui::VehicleSetAirConditionPage *ui;
    QList<QPushButton*> metroButtons,modeButtons,temButtons;
    int timer_2s[2];
    QList<bool *> modeSignal,temSignal;
    float m_setTemp;
    int flag,m_modeNum,m_temNum,m_setTempFlag;

private slots:
    void on_BTN_comfirm1_pressed();
    void on_BTN_confirm_pressed();
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
    void metroBTNPressEvent();
    void modeBTNPressEvent();
    void temBTNPressEvent();

};

#endif // VEHICLESETAIRCONDITIONPAGE_H
