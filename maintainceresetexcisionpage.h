#ifndef MAINTAINCERESETEXCISIONPAGE_H
#define MAINTAINCERESETEXCISIONPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qtimer.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class MaintainceResetExcisionPage;
}


class MaintainceResetExcisionPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceResetExcisionPage(QWidget *parent = 0);
    ~MaintainceResetExcisionPage();
    void updatePage();

private:
    Ui::MaintainceResetExcisionPage *ui;
    QList<QPushButton *> CutButtons;
    QList<bool* > CutSignals;



private slots:
    void pushButtonPressedEvent();
    void CutButtonsPressEvent();


};

#endif // MAINTAINCERESETEXCISIONPAGE_H
