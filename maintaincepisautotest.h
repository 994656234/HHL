#ifndef MAINTAINCEPISAUTOTEST_H
#define MAINTAINCEPISAUTOTEST_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>

namespace Ui {
    class MaintaincePISAutoTest;
}

class MaintaincePISAutoTest : public MyBase
{
    Q_OBJECT

public:
    explicit MaintaincePISAutoTest(QWidget *parent = 0);
    ~MaintaincePISAutoTest();
    void timerEvent(QTimerEvent *e);

private:
    Ui::MaintaincePISAutoTest *ui;
    QList<QPushButton*>buttons,TestButtons;
    QList<bool* > Signals;
    int timer2s[2];
private slots:
    void NBpressEvent();
    void TestButtonsPressEvent();
};

#endif // MAINTAINCEPISAUTOTEST_H
