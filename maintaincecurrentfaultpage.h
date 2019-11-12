#ifndef MAINTAINCECURRENTFAULTPAGE_H
#define MAINTAINCECURRENTFAULTPAGE_H

#include <mybase.h>
#include "qlabel.h"
#include "qpushbutton.h"
namespace Ui {
    class MaintainceCurrentFaultPage;
}

class MaintainceCurrentFaultPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceCurrentFaultPage(QWidget *parent = 0);
    ~MaintainceCurrentFaultPage();
     void updatePage();
private:
    Ui::MaintainceCurrentFaultPage *ui;
    QString m_Detail;
    QList<QPushButton* >m_buttons;
    QList<QList<QLabel* > >m_labels;

    int m_currentPageIndex,m_totalPageIndex,m_totalFaultNum,m_currentPageFaultNum;
    int m_currentButtonsDown;

    void Localareaupdate(int index);
    void DrawFaults(int i);
private slots:
    void on_returnBtn_pressed();
    void on_BTN7_Pre_pressed();
    void on_BTN8_Next_pressed();
    void on_BTNHome_pressed();
    void on_confirmBtn_pressed();

    void ButtonsPressEvent();
};

#endif // MAINTAINCECURRENTFAULTPAGE_H
