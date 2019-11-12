#ifndef MAINTAINCEHISTORYFAULTPAGE_H
#define MAINTAINCEHISTORYFAULTPAGE_H

#include <mybase.h>
#include "qpushbutton.h"
#include "qlabel.h"

namespace Ui {
    class MaintainceHistoryFaultPage;
}

class MaintainceHistoryFaultPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceHistoryFaultPage(QWidget *parent = 0);
    ~MaintainceHistoryFaultPage();
    void updatePage();

private:
    Ui::MaintainceHistoryFaultPage *ui;
    QString m_Detail;
    QList<QPushButton* >m_buttons;
    QList<QList<QLabel* > >m_labels;
    int m_currentPageIndex,m_totalPageIndex,m_totalFaultNum,m_currentPageFaultNum;
    int m_currentButtonsDown;

    void Localareaupdate(int index);
    void DrawFaults(int i);
private slots:

    void on_BTN2Query_pressed();
    void on_returnBtn_pressed();
    void on_BTNHome_pressed();
    void on_BTN8_Next_pressed();
    void on_BTN7_Pre_pressed();
    void ButtonsPressEvent();
};

#endif // MAINTAINCEHISTORYFAULTPAGE_H
