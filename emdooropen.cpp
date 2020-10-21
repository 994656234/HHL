#include "emdooropen.h"
#include "ui_emdooropen.h"
#include "vehiclestatusarea.h"

EmDoorOPen::EmDoorOPen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmDoorOPen)
{
    ui->setupUi(this);
}

EmDoorOPen::~EmDoorOPen()
{
    delete ui;
}

void EmDoorOPen::on_pushButton_pressed()
{
    this->hide();
    VehicleStatusArea::emDooropenflag=1;
}
