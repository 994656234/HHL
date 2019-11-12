#ifndef MAINTAINCEQUERYFAULTPAGE_H
#define MAINTAINCEQUERYFAULTPAGE_H

#include <mybase.h>
#include "qpushbutton.h"

namespace Ui {
    class MaintainceQueryFaultPage;
}

class MaintainceQueryFaultPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceQueryFaultPage(QWidget *parent = 0);
    ~MaintainceQueryFaultPage();

private:
    Ui::MaintainceQueryFaultPage *ui;
    void updatePage();
    void setBtnsStyle(QPushButton* btn,int cnt);
    QString m_TrainSelect,m_SysSelect,m_CodeInput;

private slots:
    void on_returnBtn_pressed();
    void on_BTNHome_pressed();

    void TrainSelectEvent();
    void SystemSelectEvent();
    void NumPressEvent();

};

#endif // MAINTAINCEQUERYFAULTPAGE_H
