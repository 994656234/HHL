#include "vehiclepispage.h"
#include "ui_vehiclepispage.h"

#define  PISNORMAL "border-image: url(:/images/image/pisnoactive.png);"
#define  PISFAULT "border-image: url(:/images/image/pisfault.png);"
#define  PISTALK "border-image: url(:/images/image/pisdriveractive.png);"
#define  PISWARNING "border-image: url(:/images/image/pispassengeractive.png);"
#define  PISUNKNOW  "border-image: url(:/images/image/doorunknow.png);"

VehiclePISPage::VehiclePISPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehiclePISPage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();
}

VehiclePISPage::~VehiclePISPage()
{
    delete ui;
}

void VehiclePISPage::updatePage()
{


}
