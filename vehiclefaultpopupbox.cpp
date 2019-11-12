#include "vehiclefaultpopupbox.h"
#include "ui_vehiclefaultpopupbox.h"

VehicleFaultPopupBox::VehicleFaultPopupBox(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleFaultPopupBox)
{
    ui->setupUi(this);
}

VehicleFaultPopupBox::~VehicleFaultPopupBox()
{
    delete ui;
}
