#ifndef MAINTAINCERESETEXCISIONPAGE_H
#define MAINTAINCERESETEXCISIONPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qtimer.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class MaintainceResetExcisionPage;
}


class MaintainceResetExcisionPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceResetExcisionPage(QWidget *parent = 0);
    ~MaintainceResetExcisionPage();
    void timerEvent(QTimerEvent *e);
    void updatePage();

private:
    Ui::MaintainceResetExcisionPage *ui;
    QList<QPushButton *> CutButtons,ResetButtons;
    QList<bool* > CutSignals,ResetSignals;
    int timer2s[8];
    //void updatePage();
   // void setDCUStatus(QLabel* lbl,QList<bool> status);



private slots:
    void pushButtonPressedEvent();
    void CutButtonsPressEvent();
    void RstButtonsPressEvent();


};

#endif // MAINTAINCERESETEXCISIONPAGE_H
