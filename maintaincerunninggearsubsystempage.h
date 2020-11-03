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
    void updateStatus(QList<QLabel*> lbl, unsigned char value, unsigned char flag);

private:
    Ui::MaintainceRunningGearSubsystemPage *ui;
    QList<QLabel*> column1,column2,column3,column4;
    unsigned char column1Value,column2Value,column3Value,column4Value,
                         column1Flag,column2Flag,column3Flag,column4Flag;

private slots:
    void on_BTNHome_pressed();
    void on_BTN1_pressed();
};

#endif // MAINTAINCERUNNINGGEARSUBSYSTEMPAGE_H
