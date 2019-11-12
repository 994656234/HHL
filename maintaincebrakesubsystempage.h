#ifndef MAINTAINCEBRAKESUBSYSTEMPAGE_H
#define MAINTAINCEBRAKESUBSYSTEMPAGE_H
#include "mybase.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class MaintainceBrakeSubsystemPage;
}

static int current_brake;

class MaintainceBrakeSubsystemPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceBrakeSubsystemPage(QWidget *parent = 0);
    ~MaintainceBrakeSubsystemPage();
    void updatePage();
    void updateStatus(QList<QLabel*> lbl, QList<QString> status);

private:
    Ui::MaintainceBrakeSubsystemPage *ui;
    QList<QLabel*> line1,line2,line3,line4,line5,line6,line7,line8,line9;
    QList<QString> line1Status,line2Status,line3Status,line4Status,line5Status,line6Status,line7Status,line8Status;


private slots:
    void on_BTN3_pressed();
    void on_BTN2_pressed();
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
};

#endif // MAINTAINCEBRAKESUBSYSTEMPAGE_H
