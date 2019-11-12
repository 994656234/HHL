#include "vehiclefirewarningpage.h"
#include "ui_vehiclefirewarningpage.h"

#define  FIREOK "border-image: url(:/images/image/firenone.png);"
#define  FIREALARM "border-image: url(:/images/image/firealarm.png);"
#define  FIREFAULT "border-image: url(:/images/image/firefault.png);"
#define  FIREPOLLUTED "border-image: url(:/images/image/firewarn.png);"
#define  FIREUNKNOW "border-image: url(:/images/image/doorunknow.png);"
#define  FIRCUT "border-image: url(:/images/image/bcubypass.png);"

VehicleFireWarningPage::VehicleFireWarningPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleFireWarningPage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();

}

VehicleFireWarningPage::~VehicleFireWarningPage()
{
    delete ui;
}

void VehicleFireWarningPage::updatePage()
{


}

void VehicleFireWarningPage::setFireStatus(QLabel *label, QList<bool> status)
{
    if(status.at(0))
    {
        label->setStyleSheet(FIREALARM);

    }else if(status.at(1))
    {
        label->setStyleSheet(FIREFAULT);

    }else if(status.at(2))
    {
        label->setStyleSheet(FIRCUT);

    }else if(status.at(3))
    {
        label->setStyleSheet(FIREPOLLUTED);

    }else if(status.at(4))
    {
        label->setStyleSheet(FIREOK);

    }else
    {
        label->setStyleSheet(FIREUNKNOW);
    }

}
