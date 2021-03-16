#include "vehiclesetpage.h"
#include "ui_vehiclesetpage.h"

VehicleSetPage::VehicleSetPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleSetPage)
{
    ui->setupUi(this);
    ui->BTN_setBrakeParam->hide();
    ui->BTN_setBrakeParam->setEnabled(false);
}

VehicleSetPage::~VehicleSetPage()
{
    delete ui;
}

//void VehicleSetPage::on_BTN_queryStation_pressed()
//{
//    changePage(uVehicleSetStationPage);
//}

void VehicleSetPage::on_BTN_setAirCondition_pressed()
{
    changePage(uVehicleSetAirConditionPage);
}

void VehicleSetPage::on_BTN_setBrakeParam_pressed()
{
    changePage(uVehicleSetBrakeParamPage);
}

void VehicleSetPage::on_BTN_setLight_pressed()
{
    changePage(uVehicleSetIntensityControlPage);
}

void VehicleSetPage::on_BTN_setBrakeTest_pressed()
{
    changePage(uVehicleSetBrakeTestPage);
}

void VehicleSetPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void VehicleSetPage::on_BTN_setTime_pressed()
{
    changePage(uVehicleMTTimeSetPage);
}

void VehicleSetPage::on_BTN_setCut_pressed()
{
    changePage(uVehicleMaintainceResetExcisionPage);
}

void VehicleSetPage::on_BTN_simulateStation_pressed()
{
    changePage(uVehicleSetSimlateStation);
}
