#ifndef MAINTAINCEBATTERYSUBSYSTEMPAGE_H
#define MAINTAINCEBATTERYSUBSYSTEMPAGE_H

#include <QWidget>
#include "mybase.h"
#include "qlabel.h"

namespace Ui {
class MaintainceBatterySubsystemPage;
}

class MaintainceBatterySubsystemPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceBatterySubsystemPage(QWidget *parent = 0);
    ~MaintainceBatterySubsystemPage();
    void updatePage();
    void updateStatus(QList<QLabel*> lbl, QList<short> status, QString str);
    void updateStatus(QList<QLabel*> lbl, QList<unsigned short> status, QString str);

private slots:
    void on_BTN1_pressed();

    void on_BTN2_pressed();

    void on_BTN3_pressed();

    void on_BTNHome_pressed();

private:
    Ui::MaintainceBatterySubsystemPage *ui;
    QList<QLabel*> line1,line2,line3,line4,line5;
    QList<short>line2Status,line3Status,line4Status;
    QList<unsigned short>line1Status,line5Status;
};

#endif // MAINTAINCEBATTERYSUBSYSTEMPAGE_H
