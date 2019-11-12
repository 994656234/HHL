#ifndef MAINTAINCERUNNINGGEARSUBSYSTEMPAGE_H
#define MAINTAINCERUNNINGGEARSUBSYSTEMPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class MaintainceRunningGearSubsystemPage;
}

class MaintainceRunningGearSubsystemPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceRunningGearSubsystemPage(QWidget *parent = 0);
    ~MaintainceRunningGearSubsystemPage();
    void updatePage();
    void updateStatus(QList<QLabel*> lbl, QList<QString> status);

private:
    Ui::MaintainceRunningGearSubsystemPage *ui;
    QList<QLabel*> line1,line2,line3,line4,line5,line6,lbl_lifeSignal,lbl_signalValid;
    QList<QString> line1Status,line2Status,line3Status,line4Status,line5Status,line6Status,
            lifeSignalStatus,signalValidStatus;

private slots:
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
};

#endif // MAINTAINCERUNNINGGEARSUBSYSTEMPAGE_H
