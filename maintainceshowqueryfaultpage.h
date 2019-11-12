#ifndef MAINTAINCESHOWQUERYFAULTPAGE_H
#define MAINTAINCESHOWQUERYFAULTPAGE_H

#include <mybase.h>
#include "qpushbutton.h"
namespace Ui {
    class MaintainceShowQueryFaultPage;
}

class MaintainceShowQueryFaultPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceShowQueryFaultPage(QWidget *parent = 0);
    ~MaintainceShowQueryFaultPage();
    void updatePage();
private:
    Ui::MaintainceShowQueryFaultPage *ui;
    QString m_Detail;
    QList<QPushButton* >m_buttons;
    int m_currentPageIndex,m_totalPageIndex,m_totalFaultNum,m_currentPageFaultNum;
    int m_currentButtonsDown;

    void Localareaupdate(int index);
    void DrawFaults(int i);

    void showEvent(QShowEvent *);
private slots:
    void on_BTNHome_pressed();
    void on_BTN8_Next_pressed();
    void on_BTN7_Pre_pressed();
    void on_returnBtn_pressed();
    void ButtonsPressEvent();
};

#endif // MAINTAINCESHOWQUERYFAULTPAGE_H
