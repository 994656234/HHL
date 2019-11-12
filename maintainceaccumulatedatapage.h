#ifndef MAINTAINCEACCUMULATEDATAPAGE_H
#define MAINTAINCEACCUMULATEDATAPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class MaintainceAccumulateDataPage;
}

class MaintainceAccumulateDataPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceAccumulateDataPage(QWidget *parent = 0);
    ~MaintainceAccumulateDataPage();
    void updatePage();

private:
    Ui::MaintainceAccumulateDataPage *ui;
    QList<QPushButton*>buttons;
    QList<unsigned char> signalTimeDatas,signalDatas;
    void SetTime(QLabel *lbl,QList<unsigned char> status);
    void SetStatus1(QLabel* lbl,unsigned char status);
    void SetStatus2(QLabel* lbl,QString status);
private slots:
    void NBpressEvent();
};

#endif // MAINTAINCEACCUMULATEDATAPAGE_H
