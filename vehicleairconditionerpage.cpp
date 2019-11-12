#include "vehicleairconditionerpage.h"
#include "ui_vehicleairconditionerpage.h"


#define HVACUNKNOW "border-image: url(:/images/image/HVACunKnow.png);"
#define HVACFAULT  "border-image: url(:/images/image/HVACfault.png);"
#define HVACEMGVEN  "border-image: url(:/images/image/HVACemven.png);"
#define HVACVEN  "border-image: url(:/images/image/HVACven.png);"
#define HVACWARM "border-image: url(:/images/image/HVACWarm.png);"
#define HVACCOOL "border-image: url(:/images/image/HVACCool.png);"
#define HVACSTOP "border-image: url(:/images/image/HVACoff.png);"

#define AIRCOMON "background-color: rgb(85, 255, 0);border:2px  solid;border-color:rgb(255,255,255);font:16px,\"微软雅黑\";"
#define AIRCOMOFF "border:2px  solid;border-color:rgb(255,255,255);background-color: rgb(195, 195, 195);font:16px,\"微软雅黑\";"
#define AIRCOMUNKNOW "border-image: url(:/images/image/doorunknow.png);"


VehicleAirConditionerPage::VehicleAirConditionerPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleAirConditionerPage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();
}

VehicleAirConditionerPage::~VehicleAirConditionerPage()
{
    delete ui;
}

void VehicleAirConditionerPage::updatePage()
{
    //司机室激活
    if(database->CTD_MCTActive_B1)
    {
        ui->lbl_cab1_active->show();
    }
    else
    {
        ui->lbl_cab1_active->hide();
    }

    if(database->CTD_MC2Active_B1)
    {
        ui->lbl_cab2_active->show();
    }
    else
    {
        ui->lbl_cab2_active->hide();
    }

    //列车运行方向
    if(database->CTD_Forward_B1)
    {
        ui->lbl_cab1_direction->show();
    }
    else
    {
        ui->lbl_cab1_direction->hide();
    }

    if(database->CTD_Backward_B1)
    {
        ui->lbl_cab2_direction->show();
    }
    else
    {
        ui->lbl_cab2_direction->hide();
    }


    //HVACstatus<<



}

void VehicleAirConditionerPage::getAirConditionStatus(QLabel *label, QList<bool> status)
{
    if(!status.at(0))
    {
        label->setStyleSheet(HVACUNKNOW);
    }
    else if(status.at(1))
    {
        label->setStyleSheet(HVACFAULT);
    }
    else if(status.at(2))
    {
        label->setStyleSheet(HVACEMGVEN);
    }
    else if(status.at(3))
    {
        label->setStyleSheet(HVACVEN);
    }
    else if(status.at(4))
    {
        label->setStyleSheet(HVACWARM);
    }
    else if(status.at(5))
    {
        label->setStyleSheet(HVACCOOL);
    }
    else if(status.at(6))
    {
        label->setStyleSheet(HVACSTOP);
    }
    else
    {
        label->setStyleSheet(HVACUNKNOW);
    }

}
