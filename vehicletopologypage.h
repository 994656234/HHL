#ifndef VEHICLETOPOLOGYPAGE_H
#define VEHICLETOPOLOGYPAGE_H
#include "mybase.h"
#include "qlabel.h"
#include "MainGetDefaultPara.h"


#include <QWidget>

namespace Ui {
    class VehicleTopologyPage;
}

class VehicleTopologyPage : public MyBase
{
    Q_OBJECT

public:
    explicit VehicleTopologyPage(QWidget *parent = 0);
    ~VehicleTopologyPage();
    void updatePage();

private:
    Ui::VehicleTopologyPage *ui;
    void deviceStatus(QLabel *label,bool status);
    MainGetDefaultPara *getParam;

};

#endif // VEHICLETOPOLOGYPAGE_H
