#ifndef MAINTAINCEACCUMULATORSUBSYSTEMPAGE_H
#define MAINTAINCEACCUMULATORSUBSYSTEMPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class MaintainceAccumulatorSubsystemPage;
}

static int current_acc;

class MaintainceAccumulatorSubsystemPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceAccumulatorSubsystemPage(QWidget *parent = 0);
    ~MaintainceAccumulatorSubsystemPage();
    void updatePage();
    void timerEvent(QTimerEvent *e);



private:
    Ui::MaintainceAccumulatorSubsystemPage *ui;
    int timer2s[1];
    void hideEvent(QHideEvent *);

private slots:
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
    void on_BTNStartTest_pressed();
};

#endif // MAINTAINCEACCUMULATORSUBSYSTEMPAGE_H
