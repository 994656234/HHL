#include "vehicleaircompressorpage.h"
#include "ui_vehicleaircompressorpage.h"

#define ACPNORMAL "border-image: url(:/images/image/acpoff.png);"
#define ACPFAULT  "border-image: url(:/images/image/ACPfault.png);"
#define ACPRUN "border-image: url(:/images/image/acprun.png);"
#define ACPUNKNOW "border-image: url(:/images/image/doorunknow.png);"

VehicleAirCompressorPage::VehicleAirCompressorPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleAirCompressorPage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();

}

VehicleAirCompressorPage::~VehicleAirCompressorPage()
{
    delete ui;
}

void VehicleAirCompressorPage::updatePage()
{
    ACPstatus<<database->CTD_RIOM2GWOLINE_B1<<database->RM2CT_CMK_B1;
    setACPStatus(ui->lbl_airCompressor1,ACPstatus);
    ACPstatus.clear();

    ACPstatus<<database->CTD_RIOM5GWOLINE_B1<<database->RM5CT_CMK_B1;
    setACPStatus(ui->lbl_airCompressor2,ACPstatus);
    ACPstatus.clear();


}

void VehicleAirCompressorPage::setACPStatus(QLabel *label, QList<bool> status)
{
    if(status.at(0))
    {
        if(status.at(1))
        {
            label->setStyleSheet(ACPRUN);
        }else
        {
            label->setStyleSheet(ACPNORMAL);
        }
    }else
    {
        label->setStyleSheet(ACPFAULT);
    }
}
