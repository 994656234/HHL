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
    ACPstatus<<database->CTD_RIOM1GWOLINE_B1<<database->CTR1_DOLOASMON_B1;
    setACPStatus(ui->lbl_airCompressor1,ACPstatus);
    ACPstatus.clear();

    ACPstatus<<database->CTD_RIOM4GWOLINE_B1<<database->CTR4_DOLOASMON_B1;
    setACPStatus(ui->lbl_airCompressor2,ACPstatus);
    ACPstatus.clear();

    ui->lbl_ACP_MC1->setText(QString::number(database->BiCT_MRPMP1_I16/20)+"kpa");
    ui->lbl_ACP_MC2->setText(QString::number(database->BiCT_MRPMP2_I16/20)+"kpa");


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
