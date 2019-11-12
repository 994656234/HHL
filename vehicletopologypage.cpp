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

    //MC1
    deviceStatus(ui->lbl_VCU1,database->CTD_CCU1OLINE_B1);
    deviceStatus(ui->lbl_ERM1,database->CTD_ERM1OLINE_B1);
    deviceStatus(ui->lbl_RIOM10,database->CTD_RIOM1GWOLINE_B1);
    deviceStatus(ui->lbl_OBCU1,database->CTD_AMCTOLINE_B1);
    deviceStatus(ui->lbl_GV1,database->CTD_BCU1OLINE_B1);
    //deviceStatus(lbl_PCU1,database->CTD_PIS1OLINE_B1);
    deviceStatus(ui->lbl_DDU1,database->CTD_DDU1OLINE_B1);
    deviceStatus(ui->lbl_RIOM11,database->CTD_RIOM2GWOLINE_B1);
    deviceStatus(ui->lbl_VVVF3_1,database->CTD_TCU1OLINE_B1);
    deviceStatus(ui->lbl_SIV1,database->CTD_FCU1OLINE_B1);
    deviceStatus(ui->lbl_ACVP,database->CTD_ACTOLINE_B1);
    deviceStatus(ui->lbl_Panto,database->CTD_PANOLINE_B1);

    //MP1
    deviceStatus(ui->lbl_VVVF1_1,database->CTD_TCU2OLINE_B1);
    deviceStatus(ui->lbl_VVVF2_1,database->CTD_TCU3OLINE_B1);
    deviceStatus(ui->lbl_ACVP2,database->CTD_AC2OLINE_B1);

    //MP2
    deviceStatus(ui->lbl_VVVF1_2,database->CTD_TCU4OLINE_B1);
    deviceStatus(ui->lbl_VVVF2_2,database->CTD_TCU5OLINE_B1);
    deviceStatus(ui->lbl_ACVP3,database->CTD_AC3OLINE_B1);

    //MC2
    deviceStatus(ui->lbl_VCU2,database->CTD_CCU2OLINE_B1);
    deviceStatus(ui->lbl_ERM2,database->CTD_ERM2OLINE_B1);
    deviceStatus(ui->lbl_RIOM10_2,database->CTD_RIOM4GWOLINE_B1);
    deviceStatus(ui->lbl_OBCU2,database->CTD_AMC2OLINE_B1);
    deviceStatus(ui->lbl_GV2,database->CTD_BCU2OLINE_B1);
    deviceStatus(ui->lbl_DDU2,database->CTD_DDU2OLINE_B1);
    deviceStatus(ui->lbl_RIOM11_2,database->CTD_RIOM5GWOLINE_B1);
    deviceStatus(ui->lbl_VVVF3_2,database->CTD_TCU6OLINE_B1);
    deviceStatus(ui->lbl_SIV2,database->CTD_ACU2OLINE_B1);
    deviceStatus(ui->lbl_ACVP4,database->CTD_AC4OLINE_B1);


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
