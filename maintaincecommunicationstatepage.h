#ifndef MAINTAINCECOMMUNICATIONSTATEPAGE_H
#define MAINTAINCECOMMUNICATIONSTATEPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qlabel.h"

#include <QWidget>

namespace Ui {
    class MaintainceCommunicationStatePage;
}

class MaintainceCommunicationStatePage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceCommunicationStatePage(QWidget *parent = 0);
    ~MaintainceCommunicationStatePage();
    void updatePage();
    void setMVBstatus(QLabel *label,bool status);

private:
    Ui::MaintainceCommunicationStatePage *ui;
    QList<bool> MVBstatus;
    QList<QLabel *> MVBlabel;
private slots:
    void pushButtonPressedEvent();
};

#endif // MAINTAINCECOMMUNICATIONSTATEPAGE_H
