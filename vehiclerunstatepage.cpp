#include "vehiclerunstatepage.h"
#include "ui_vehiclerunstatepage.h"

VehicleRunStatePage::VehicleRunStatePage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleRunStatePage)
{
    ui->setupUi(this);
}

VehicleRunStatePage::~VehicleRunStatePage()
{
    delete ui;
}

void VehicleRunStatePage::updatePage()
{

}
void VehicleRunStatePage::showEvent(QShowEvent *)
{

}

