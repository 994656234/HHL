#include "vehiclemaintainpage.h"
#include "ui_vehiclemaintainpage.h"
#include "qdebug.h"

VehicleMaintainPage::VehicleMaintainPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleMaintainPage)
{
    ui->setupUi(this);
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome
            <<ui->BTN_AuxiliarySubsystem<<ui->BTN_BogieLampSubsystem<<ui->BTN_BrakeSubsystem
            <<ui->BTN_CommunicationStatus<<ui->BTN_DataManage<<ui->BTN_DataMonitor<<ui->BTN_HistoryFault<<ui->BTN_MetroSet
            <<ui->BTN_RIOMTest<<ui->BTN_SoftwareVersion<<ui->BTN_TractSubsystem<<ui->BTN_HMIInitSet
            <<ui->BTN_autoStationTest<<ui->BTN_cumulateData<<ui->BTN_speedTest<<ui->BTN_Cut<<ui->BTN_Accumulate;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }
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
    else if(BTNName=="BTN_Accumulate")
    {
        changePage(uMaintainceAccumulatorSubsystemPage);
    }
    else if(BTNName=="BTN_Cut")
    {
        changePage(uVehicleMaintainceResetExcisionPage);
    }
    else
    {

    }

}
