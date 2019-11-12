#ifndef MAINTAINCEALLPORTSPAGE_H
#define MAINTAINCEALLPORTSPAGE_H
#include "mybase.h"
#include "qpushbutton.h"
#include "qlist.h"
#include "crrcricomvb.h"
#include "qpainter.h"

#include <QWidget>

namespace Ui {
    class MaintainceAllPortsPage;
}

class MaintainceAllPortsPage : public MyBase
{
    Q_OBJECT

public:
    explicit MaintainceAllPortsPage(QWidget *parent = 0);
    ~MaintainceAllPortsPage();
    void updatePage();
    void paintEvent(QPaintEvent *);
    void installMvb(CrrcRicoMvb* crrcRicoMvb);

private:
    Ui::MaintainceAllPortsPage *ui;
    QList<QPushButton*> buttons;
    CrrcRicoMvb* crrcRicoMvb;
    QList <int>m_PortsList;
    QList <int> VCUAPort,VCUBPort,RIOMPort,DDUPort,ERMPort,PCEPort,ACEPort,BCEPort,EDCUAPort,TDSPort,HVACPort,ATCPort,PISPort,FASPort,PCUPort;
private slots:
    void NBpressEvent();

};

#endif // MAINTAINCEALLPORTSPAGE_H
