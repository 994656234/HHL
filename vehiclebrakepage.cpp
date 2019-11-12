#include "vehiclebrakepage.h"
#include "ui_vehiclebrakepage.h"

#define  BRAKECUT  "border-image: url(:/images/image/cut.png);"
#define  BRAKEFAULT  "border-image: url(:/images/image/bcufault.png);"

#define  BRAKENORMALON  "border-image: url(:/images/image/bcuapp.png);"
#define  BRAKENORMALOFF  "border-image: url(:/images/image/bcurelease.png);"

#define  STOPBRAKEON "border-image: url(:/images/image/bcupbapp.png);"
#define  STOPBRAKEOFF "border-image: url(:/images/image/bcupbaoff.png);"

VehicleBrakePage::VehicleBrakePage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleBrakePage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();
}

VehicleBrakePage::~VehicleBrakePage()
{
    delete ui;
}


void VehicleBrakePage::updatePage()
{

}

void VehicleBrakePage::brakeStatus(QLabel * label ,QList<bool> status)
{
    if(status.at(0))
    {
        label->setStyleSheet(BRAKECUT);
    }
    else if(status.at(1))
    {
        label->setStyleSheet(BRAKEFAULT);
    }
    else if(status.at(2)&&!status.at(3))
    {
        label->setStyleSheet(BRAKENORMALON);
    }
    else
    {
        label->setStyleSheet(BRAKENORMALOFF);
    }


}


void VehicleBrakePage::stopBrakeStatus(QLabel *label, QList<bool> status)
{
    if(!status.at(0))
    {
        label->setStyleSheet(STOPBRAKEON);
    }
    else
    {
        label->setStyleSheet(STOPBRAKEOFF);
    }

}
