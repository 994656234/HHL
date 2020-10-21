#ifndef VEHICLESETAIRCONDITIONPAGE_H
#define VEHICLESETAIRCONDITIONPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qdebug.h"
#include "QTimer"
#include "qlabel.h"

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
    int timerID1,timerID2;
    QList<bool *> modeSignal,temSignal;
    int flag,m_modeNum,m_temNum,m_setTemp,m_setTempFlag;
    QList<QLabel*> xinFenglbl,huiFenglbl;
    QList<unsigned char> xinFengStatus,huiFengStatus;
    void setXinFengStatus(QList<QLabel*> lbl,QList<unsigned char> status);
    void setHuiFengStatus(QList<QLabel*> lbl,QList<unsigned char> status);

private slots:
    void on_BTN_comfirm1_pressed();
    void on_BTN_confirm_pressed();
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
    void metroBTNPressEvent();
    void modeBTNPressEvent();
    void temBTNPressEvent();

    void on_BTN_newwind_open_pressed();
};

#endif // VEHICLESETAIRCONDITIONPAGE_H
