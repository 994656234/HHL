#ifndef MAINTAINCEDATAMANAGEPAGE_H
#define MAINTAINCEDATAMANAGEPAGE_H
#include "mybase.h"
#include "qpushbutton.h"

#include <QWidget>
#include "qpushbutton.h"
#include "qtimer.h"

namespace Ui {
    class MaintainceDataManagePage;
}

class MaintainceDataManagePage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceDataManagePage(QWidget *parent = 0);
    ~MaintainceDataManagePage();

private:
    Ui::MaintainceDataManagePage *ui;
    QList<QPushButton* > m_Numbuttons,m_Selectbuttons;
    QPushButton* m_button;
    QTimer* timer2s;
    void hideEvent(QHideEvent *);
private slots:
    void pushButtonPressedEvent();
    void NumbuttonsPressedEvent();
    void SelectbuttonsPressedEvent();
    void ConfirmPressEvent();
};

#endif // MAINTAINCEDATAMANAGEPAGE_H
