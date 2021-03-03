#ifndef MAINTAINCERUNNINGGEARSUBSYSTEMPAGE_H
#define MAINTAINCERUNNINGGEARSUBSYSTEMPAGE_H
#include "mybase.h"
#include "qlabel.h"
#include "qpushbutton.h"

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
    void updateStatus(QList<QLabel*> lbl, int value[4][20], int index);

private:
    Ui::MaintainceRunningGearSubsystemPage *ui;
    QList<QLabel*> line;
    unsigned char line1Value,line2Value,line3Value,line4Value,
                         line1Flag,line2Flag,line3Flag,line4Flag;
    QList<QPushButton*> metroButtons;
    int metroNum;
private slots:
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
    void metroBTNPressEvent();

};

#endif // MAINTAINCERUNNINGGEARSUBSYSTEMPAGE_H
