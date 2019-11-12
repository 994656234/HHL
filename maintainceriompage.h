#ifndef MAINTAINCERIOMPAGE_H
#define MAINTAINCERIOMPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "dicontrol.h"
#include "docontrol.h"
#include "axcontrol.h"
#include "tcdicontrol.h"
#include "tcdocontrol.h"

#include <QWidget>

enum CurrentForm
{
    TC_DI1 = 0,
    TC_DI2,
    TC_DI3,
    TC_DI4,
    TC_DI5,
    TC_DO,
    TC_AIM,
    MP_DI,
    MP_DO,
    M_DI,
    M_DO
};

namespace Ui {
    class MaintainceRIOMPage;
}

class MaintainceRIOMPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceRIOMPage(QWidget *parent = 0);
    ~MaintainceRIOMPage();
    void updatePage();
    void refreshAllButtons();

private:
    Ui::MaintainceRIOMPage *ui;
    QList<QPushButton *> buttons;
    DIControl *di1;
    DoControl *do1;
    AXControl *ax1;
    AXControl *ax2;

    TCDIControl *tcdi1;
    TCDOControl *tcdo1;
    TCDOControl *tcdo2;

    CurrentForm currentform;

    QList <QString> TC1AXData,TC2AXData;
    void setDataType();


private slots:
    void on_BTN1_pressed();
    void on_BTNHome_pressed();
    void buttonsPressEvent();
};

#endif // MAINTAINCERIOMPAGE_H
