#include "vehicleairconditionerpage.h"
#include "ui_vehicleairconditionerpage.h"


#define HVACUNKNOW "border-image: url(:/images/image/HVACunKnow.png);"
#define HVACFAULT  "border-image: url(:/images/image/HVACfault.png);"
#define HVACEMGVEN  "border-image: url(:/images/image/HVACemven.png);"
#define HVACVEN  "border-image: url(:/images/image/HVACven.png);"
#define HVACWARM "border-image: url(:/images/image/HVACWarm.png);"
#define HVACCOOL "border-image: url(:/images/image/HVACCool.png);"
#define HVACSTOP "border-image: url(:/images/image/HVACoff.png);"

#define HVACyuCool "border-image: url(:/images/image/HVAyuCool.png);"
#define HVACyuWarm "border-image: url(:/images/image/HVACyuWarm.png);"
#define Auto   "border-image: url(:/images/image/HVACauto.png);"

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


    getAirConditionStatus(ui->lbl_airCondition1_1,database->ACVP1CT_IusUnitSts1_U8);
    getAirConditionStatus(ui->lbl_airCondition1_2,database->ACVP1CT_IusUnitSts2_U8);

    getAirConditionStatus(ui->lbl_airCondition2_1,database->ACVP2CT_IusUnitSts1_U8);
    getAirConditionStatus(ui->lbl_airCondition2_2,database->ACVP2CT_IusUnitSts2_U8);

    getAirConditionStatus(ui->lbl_airCondition3_1,database->ACVP3CT_IusUnitSts1_U8);
    getAirConditionStatus(ui->lbl_airCondition3_2,database->ACVP3CT_IusUnitSts2_U8);

    getAirConditionStatus(ui->lbl_airCondition4_1,database->ACVP4CT_IusUnitSts1_U8);
    getAirConditionStatus(ui->lbl_airCondition4_2,database->ACVP4CT_IusUnitSts2_U8);

    //减载
    getAirConditionDeload(ui->lbl_deload1,database->ACVP1CT_IxDeloadFshU1_B1 | database->ACVP1CT_IxDeloadFshU2_B1);
    getAirConditionDeload(ui->lbl_deload3,database->ACVP2CT_IxDeloadFshU1_B1 | database->ACVP2CT_IxDeloadFshU2_B1);
    getAirConditionDeload(ui->lbl_deload5,database->ACVP3CT_IxDeloadFshU1_B1 | database->ACVP3CT_IxDeloadFshU2_B1);
    getAirConditionDeload(ui->lbl_deload7,database->ACVP4CT_IxDeloadFshU1_B1 | database->ACVP4CT_IxDeloadFshU2_B1);
}



void VehicleAirConditionerPage::getAirConditionStatus(QLabel *label, unsigned char  status )
{
    if(status==1)
    {
        label->setStyleSheet(HVACFAULT);
    }
    else if(status==2)
    {
        label->setStyleSheet(HVACEMGVEN);
    }
    else if(status==3)
    {
        label->setStyleSheet(HVACyuCool);
    }
    else if(status==4)
    {
        label->setStyleSheet(Auto);
    }
    else if(status==5)
    {
        label->setStyleSheet(HVACCOOL);
    }
    else if(status==6)
    {
        label->setStyleSheet(HVACyuWarm);
    }
    else if(status==7)
    {
        label->setStyleSheet(HVACWARM);
    }
    else if(status==8)
    {
        label->setStyleSheet(HVACVEN);
    }
    else if(status==9)
    {
        label->setStyleSheet(HVACSTOP);
    }
    else
    {
        label->setStyleSheet(HVACUNKNOW);
    }
}

void VehicleAirConditionerPage::getAirConditionDeload(QLabel *label, bool status)
{
    if (status)
    {
        label->show();
    }
    else
    {
        label->hide();
    }
}


