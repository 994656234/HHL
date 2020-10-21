#ifndef ADDSUBTRACTTESTPAGE_H
#define ADDSUBTRACTTESTPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class AddSubtractTestPage;
}

class AddSubtractTestPage : public MyBase
{
    Q_OBJECT

public:
    explicit AddSubtractTestPage(QWidget *parent = 0);
    ~AddSubtractTestPage();
    void updatePage();
    void timerEvent(QTimerEvent *e);

private:
    Ui::AddSubtractTestPage *ui;
    QList<QPushButton*>buttons;
    QList<QPushButton*> statusButtons;
    QList<bool *> Signals;
    int timer2s[2];
    void setLabelStatus(QList<QLabel*>lbls,QList<QString> status);
    QList<QLabel*> lbls;
    QList<QString> status;

private slots:
    void NBpressEvent();
    void statusBTNPressEvent();
};

#endif // ADDSUBTRACTTESTPAGE_H
