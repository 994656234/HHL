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
    status<<database->RM2CT_BBIV1_B1<<database->B1_1CT_MajorFltMC1Bg1_B1<<database->BiCT_BrkApplyMC1Bg1_B1<<database->BiCT_BrkRelMC1Bg1_B1;
    brakeStatus(ui->lbl_brake1_1,status);
    status.clear();

    status<<database->RM2CT_BBIV2_B1<<database->B1_2CT_MajorFltMC1Bg1_B1<<database->BiCT_BrkApplyMC1Bg2_B1<<database->BiCT_BrkRelMC1Bg2_B1;
    brakeStatus(ui->lbl_brake1_2,status);
    status.clear();

    status<<database->RM3CT_BBIV1_B1<<database->B2_1CT_MajorFltMC1Bg1_B1<<database->BiCT_BrkApplyMP1Bg1_B1<<database->BiCT_BrkRelMP1Bg1_B1;
    brakeStatus(ui->lbl_brake2_1,status);
    status.clear();

    status<<database->RM3CT_BBIV2_B1<<database->B2_2CT_MajorFltMC1Bg1_B1<<database->BiCT_BrkApplyMP1Bg2_B1<<database->BiCT_BrkRelMP1Bg2_B1;
    brakeStatus(ui->lbl_brake2_2,status);
    status.clear();

    status<<database->RM6CT_BBIV1_B1<<database->B3_1CT_MajorFltMC1Bg1_B1<<database->BiCT_BrkMP2Bg1_B1<<database->BiCT_BrkRelMP2Bg1_B1;
    brakeStatus(ui->lbl_brake3_1,status);
    status.clear();

    status<<database->RM6CT_BBIV2_B1<<database->B3_2CT_MajorFltMC1Bg1_B1<<database->BiCT_BrkMP2Bg2_B1<<database->BiCT_BrkRelMP2Bg2_B1;
    brakeStatus(ui->lbl_brake3_2,status);
    status.clear();

    status<<database->RM5CT_BBIV1_B1<<database->B4_1CT_MajorFltMC1Bg1_B1<<database->BiCT_BrkApplyMC2Bg1_B1<<database->BiCT_BrkRelMC2Bg1_B1;
    brakeStatus(ui->lbl_brake4_1,status);
    status.clear();


    status<<database->RM5CT_BBIV2_B1<<database->B4_2CT_MajorFltMC1Bg1_B1<<database->BiCT_BrkApplyMC2Bg2_B1<<database->BiCT_BrkRelMC2Bg2_B1;
    brakeStatus(ui->lbl_brake4_2,status);
    status.clear();






    stopBrakeStatus(ui->lbl_stopbrake1,database->BiCT_PBrtRelMC1Bg1_B1);
    stopBrakeStatus(ui->lbl_stopbrake2,database->BiCT_PBrtRelMp1Bg1_B1);
    stopBrakeStatus(ui->lbl_stopbrake3,database->BiCT_PBrtRelMP2Bg1_B1);
    stopBrakeStatus(ui->lbl_stopbrake4,database->BiCT_PBrtRelMC2Bg1_B1);

    ui->lbl_break1_1_pressure->setText(QString::number((int)database->BiCT_BCPMC1Bg1_I16/20)+"kpa");
    ui->lbl_break1_2_pressure->setText(QString::number((int)database->BiCT_BCPMC1Bg2_I16/20)+"kpa");
    ui->lbl_break2_1_pressure->setText(QString::number((int)database->BiCT_BCPMP1Bg1_I16/20)+"kpa");
    ui->lbl_break2_2_pressure->setText(QString::number((int)database->BiCT_BCPMP1Bg2_I16/20)+"kpa");
    ui->lbl_break3_1_pressure->setText(QString::number((int)database->BiCT_BCPMP2Bg1_I16/20)+"kpa");
    ui->lbl_break3_2_pressure->setText(QString::number((int)database->BiCT_BCPMP2Bg2_I16/20)+"kpa");
    ui->lbl_break4_1_pressure->setText(QString::number((int)database->BiCT_BCPMC2Bg1_I16/20)+"kpa");
    ui->lbl_break4_2_pressure->setText(QString::number((int)database->BiCT_BCPMC2Bg2_I16/20)+"kpa");




}

void VehicleBrakePage::brakeStatus(QLabel * label ,QList<bool> status)
{
    if(!status.at(0))
    {
        label->setStyleSheet(BRAKECUT);
    }
    else if(status.at(1))
    {
        label->setStyleSheet(BRAKEFAULT);
    }
    else if(status.at(2))
    {
        label->setStyleSheet(BRAKENORMALON);
    }
    else if(status.at(3))
    {
        label->setStyleSheet(BRAKENORMALOFF);
    }
    else
    {
        label->setStyleSheet(BRAKENORMALOFF);
    }


}


void VehicleBrakePage::stopBrakeStatus(QLabel *label,bool status)
{
    if(!status)
    {
        label->setStyleSheet(STOPBRAKEON);
    }
    else
    {
        label->setStyleSheet(STOPBRAKEOFF);
    }

}
