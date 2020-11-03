#include "vehiclemaintainpage.h"
#include "ui_vehiclemaintainpage.h"
#include "qdebug.h"

#define  BTNPRESS "background:rgb(187,188,247);border:0px solid;color: rgb(255, 255, 255);font:20px \"微软雅黑\";"
#define  BTNRELEASE  "background:rgb(0,0,50);border:0px solid;color: rgb(255, 255, 255);font:20px \"微软雅黑\";"


VehicleMaintainPage::VehicleMaintainPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleMaintainPage)
{
    ui->setupUi(this);
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome
            <<ui->BTN_AuxiliarySubsystem<<ui->BTN_BogieLampSubsystem<<ui->BTN_BrakeSubsystem
            <<ui->BTN_CommunicationStatus<<ui->BTN_DataManage<<ui->BTN_DataMonitor<<ui->BTN_HistoryFault<<ui->BTN_MetroSet
            <<ui->BTN_RIOMTest<<ui->BTN_SoftwareVersion<<ui->BTN_TractSubsystem<<ui->BTN_HMIInitSet
            <<ui->BTN_autoStationTest<<ui->BTN_cumulateData<<ui->BTN_speedTest<<ui->BTN_Cut<<ui->BTN_Battery;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }

    //ui->BTN_TractSubsystem->hide();
    //ui->BTN_TractSubsystem->setEnabled(false);
    ui->BTN_BrakeSubsystem->hide();
    ui->BTN_BrakeSubsystem->setEnabled(false);
    ui->BTN_AuxiliarySubsystem->hide();
    ui->BTN_AuxiliarySubsystem->setEnabled(false);
    ui->BTN_BogieLampSubsystem->hide();
    ui->BTN_BogieLampSubsystem->setEnabled(false);
    //ui->BTN_Accumulate->hide();
    //ui->BTN_Accumulate->setEnabled(false);
    ui->BTN_CommunicationStatus->hide();
    ui->BTN_CommunicationStatus->setEnabled(false);

    this->fangyouFlag=true;
    this->qiangqiflag = true;

}

VehicleMaintainPage::~VehicleMaintainPage()
{
    delete ui;
}

void VehicleMaintainPage::NBpressEvent()
{
    QString BTNName=((QPushButton*)this->sender())->objectName();
    if(BTNName=="BTN1")
    {
        changePage(uVehicleTrainArea);
    }
    else if(BTNName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }
    else if(BTNName=="BTN_HistoryFault")
    {
        changePage(uMaintainceHistoryFaultPage);
    }
    else if(BTNName=="BTN_DataManage")
    {
        changePage(uMaintaincePasswordPage);
    }
    else if(BTNName=="BTN_CommunicationStatus")
    {
        changePage(uVehicleMaintainceCommunicationStatePage);
    }
    else if(BTNName=="BTN_SoftwareVersion")
    {
        changePage(uVehicleMaintainceSoftwareVersionPage);
    }
    else if(BTNName=="BTN_MetroSet")
    {
        changePage(uVehicleMaintainceWheelDiameterSetPage);
    }
    else if(BTNName=="BTN_RIOMTest")
    {
        changePage(uVehicleMaintainceRIOMPage);
    }
    else if(BTNName=="BTN_DataMonitor")
    {
         changePage(uVehicleMaintainceAllPortsPage);
    }
    else if(BTNName=="BTN_TractSubsystem")
    {
        changePage(uVehicleMaintainceTractSubsystemPage);
    }
    else if(BTNName=="BTN_BrakeSubsystem")
    {
        changePage(uVehicleMaintainceBrakeSubsystemPage);
    }
    else if(BTNName=="BTN_AuxiliarySubsystem")
    {
        changePage(uVehicleMaintainceAuxiliarySubsystemPage);
    }
    else if(BTNName=="BTN_BogieLampSubsystem")
    {
        changePage(uVehicleMaintainceRunningGearSubsystemPage);
    }
    else if(BTNName=="BTN_HMIInitSet")
    {
        changePage(uVehicleMaintainceInitSetPage);
    }
    else if(BTNName=="BTN_autoStationTest")
    {
        changePage(uMaintaincePISAutoTest);
    }
    else if(BTNName=="BTN_cumulateData")
    {
        changePage(uMaintainceAccumulateDataPage);
    }
    else if(BTNName=="BTN_speedTest")
    {
        changePage(uMaintainceAddSubtractTestPage);
    }
    else if(BTNName=="BTN_Battery")
    {
        changePage(uMaintainceBatterySubsystemPage);
    }
    else if(BTNName=="BTN_Cut")
    {
        changePage(uMaintainceAccumulatorSubsystemPage);
    }
    else
    {

    }

}

void VehicleMaintainPage::on_BTN_fangyou_pressed()
{
    if(fangyouFlag)
    {
        ui->BTN_fangyou->setStyleSheet(BTNPRESS);
        fangyouFlag=false;
        database->fangyou=true;
    }
    else
    {
        ui->BTN_fangyou->setStyleSheet(BTNRELEASE);
        fangyouFlag=true;
        database->fangyou=false;
    }
}


void VehicleMaintainPage::on_BTN_qiangqi_pressed()
{


        if(qiangqiflag)
        {
            ui->BTN_qiangqi->setStyleSheet(BTNPRESS);
            qiangqiflag=false;
            database->DiCT_BrkRfanForceStart_B1=true;
        }
        else
        {
            ui->BTN_qiangqi->setStyleSheet(BTNRELEASE);
            qiangqiflag=true;
            database->DiCT_BrkRfanForceStart_B1=false;
        }
}
