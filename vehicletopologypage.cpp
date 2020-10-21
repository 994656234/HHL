#include "vehicletopologypage.h"
#include "ui_vehicletopologypage.h"
#include "qdebug.h"

#define DEVICEOFF "background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);border-radius:3px;"
#define DEVICEON "background-color: rgb(85, 255, 0);color: rgb(0, 0, 0);border-radius:3px;"
#define DEVICEFLOW "background-color: rgb(255, 255, 127);color: rgb(0, 0, 0);border-radius:3px;"
#define DEVICEPARTON "background-color: rgb(170, 170, 255);color: rgb(0, 0, 0);border-radius:3px;"

VehicleTopologyPage::VehicleTopologyPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleTopologyPage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();

}

VehicleTopologyPage::~VehicleTopologyPage()
{
    delete ui;
}

void VehicleTopologyPage::updatePage()
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

    //BMS
    deviceStatus(ui->lbl_BMS1,database->CTD_BMS1OLINE_B1);
    deviceStatus(ui->lbl_BMS2,database->CTD_BMS2OLINE_B1);
    deviceStatus(ui->lbl_BMS3,database->CTD_BMS3OLINE_B1);
    deviceStatus(ui->lbl_BMS4,database->CTD_BMS4OLINE_B1);

    //MC1
    setMainFlowDevice(ui->lbl_VCU1,database->CTD_CCU1Active_B1,database->CTD_CCU1OLINE_B1);
    deviceStatus(ui->lbl_ERM1,database->CTD_ERM1OLINE_B1);
    deviceStatus(ui->lbl_RIOM10,database->CTD_RIOM1GWOLINE_B1);
    deviceStatus(ui->lbl_OBCU1,database->CTD_AMCTOLINE_B1);
    deviceStatus(ui->lbl_GV1,database->CTD_BCU1OLINE_B1);
    deviceStatus(ui->lbl_DDU1,database->CTD_DDU1OLINE_B1);
    deviceStatus(ui->lbl_RIOM11,database->CTD_RIOM2GWOLINE_B1);
    deviceStatus(ui->lbl_VVVF3_1,database->CTD_TCU1OLINE_B1);
    deviceStatus(ui->lbl_SIV1,database->CTD_ACU1OLINE_B1);
    deviceStatus(ui->lbl_ACVP,database->CTD_ACTOLINE_B1);
    deviceStatus(ui->lbl_Panto,database->CTD_PANOLINE_B1);
    deviceStatus(ui->lbl_FCU1,database->CTD_FCU1OLINE_B1);
    setMainFlowDevice(ui->lbl_PCU1,database->PIS1CT_P2_B1,database->CTD_PIS1OLINE_B1);

    //MP1
    deviceStatus(ui->lbl_VVVF1_1,database->CTD_TCU2OLINE_B1);
    deviceStatus(ui->lbl_VVVF2_1,database->CTD_TCU3OLINE_B1);
    deviceStatus(ui->lbl_ACVP2,database->CTD_AC2OLINE_B1);
    deviceStatus(ui->lbl_RIOM3,database->CTD_RIOM3GWOLINE_B1);

    //MP2
    deviceStatus(ui->lbl_VVVF1_2,database->CTD_TCU4OLINE_B1);
    deviceStatus(ui->lbl_VVVF2_2,database->CTD_TCU5OLINE_B1);
    deviceStatus(ui->lbl_ACVP3,database->CTD_AC3OLINE_B1);
    deviceStatus(ui->lbl_RIOM4,database->CTD_RIOM6GWOLINE_B1);

    //MC2
    setMainFlowDevice(ui->lbl_VCU2,database->CTD_CCU2Active_B1,database->CTD_CCU2OLINE_B1);
    deviceStatus(ui->lbl_ERM2,database->CTD_ERM2OLINE_B1);
    deviceStatus(ui->lbl_RIOM10_2,database->CTD_RIOM4GWOLINE_B1);
    deviceStatus(ui->lbl_OBCU2,database->CTD_AMC2OLINE_B1);
    deviceStatus(ui->lbl_GV2,database->CTD_BCU2OLINE_B1);
    deviceStatus(ui->lbl_DDU2,database->CTD_DDU2OLINE_B1);
    deviceStatus(ui->lbl_RIOM11_2,database->CTD_RIOM5GWOLINE_B1);
    deviceStatus(ui->lbl_VVVF3_2,database->CTD_TCU6OLINE_B1);
    deviceStatus(ui->lbl_SIV2,database->CTD_ACU2OLINE_B1);
    deviceStatus(ui->lbl_ACVP4,database->CTD_AC4OLINE_B1);
    deviceStatus(ui->lbl_FCU2,database->CTD_FCU2OLINE_B1);
    setMainFlowDevice(ui->lbl_PCU2,database->PIS2CT_P2_B1,database->CTD_PIS2OLINE_B1);

    setEDCUstatus(ui->lbl_EDCU5R_1,database->CTD_EDCU1OLINE_B1,database->B1CT_MstrGV_B1);
    setEDCUstatus(ui->lbl_EDCU6L_1,database->CTD_EDCU2OLINE_B1,database->B2CT_MstrGV_B1);
    setEDCUstatus(ui->lbl_EDCU5R_2,database->CTD_EDCU3OLINE_B1,database->B3CT_MstrGV_B1);
    setEDCUstatus(ui->lbl_EDCU6L_2,database->CTD_EDCU4OLINE_B1,database->B4CT_MstrGV_B1);
    setEDCUstatus(ui->lbl_EDCU5R_3,database->CTD_EDCU5OLINE_B1,database->B5CT_MstrGV_B1);
    setEDCUstatus(ui->lbl_EDCU6L_3,database->CTD_EDCU6OLINE_B1,database->B6CT_MstrGV_B1);
    setEDCUstatus(ui->lbl_EDCU5R_4,database->CTD_EDCU7OLINE_B1,database->B7CT_MstrGV_B1);
    setEDCUstatus(ui->lbl_EDCU6L_4,database->CTD_EDCU8OLINE_B1,database->B8CT_MstrGV_B1);

}



void VehicleTopologyPage::deviceStatus(QLabel *label, bool status)
{
    if(status)
    {
        label->setStyleSheet(DEVICEON);
    }
    else
    {
        label->setStyleSheet(DEVICEOFF);
    }
}

void VehicleTopologyPage::setMainFlowDevice(QLabel *label, bool flag, bool status)
{
    if(status)
    {
        if(flag)
        {
            label->setStyleSheet(DEVICEON);
        }
        else
        {
            label->setStyleSheet(DEVICEFLOW);
        }
    }
    else
    {
        label->setStyleSheet(DEVICEOFF);
    }
}

void VehicleTopologyPage::setEDCUstatus(QLabel *label,bool flag, unsigned short status)
{
    if(flag)
    {
        if(status==1)
        {
            label->setStyleSheet(DEVICEON);
        }
        else if(status==2)
        {
            label->setStyleSheet(DEVICEFLOW);
        }
        else if(status==3)
        {
            label->setStyleSheet(DEVICEPARTON);
        }
        else
        {
            label->setStyleSheet(DEVICEOFF);
        }
    }
    else
    {
        label->setStyleSheet(DEVICEOFF);
    }


}


