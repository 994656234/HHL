#include "vehicletractpage.h"
#include "ui_vehicletractpage.h"

#define TCUFAULT "border-image: url(:/images/image/tcufault.png);"
#define TCUON "border-image: url(:/images/image/tcurun.png);"
#define TCUOFF "border-image: url(:/images/image/tcuoff.png);"
#define TCUUNKNOW "border-image: url(:/images/image/doorunknow.png);"
#define  TCUCUT  "border-image: url(:/images/image/cut.png);"

VehicleTractPage::VehicleTractPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleTractPage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();
}

VehicleTractPage::~VehicleTractPage()
{
    delete ui;
}

void VehicleTractPage::updatePage()
{
    //司机室激活
    if(database->CTD_MCTActive_B1)
    {
        ui->lbl_cab1_active->show();
    }
    else
    {
        ui->lbl_cab1_active->hide();
    }

    if(database->CTD_MC2Active_B1)
    {
        ui->lbl_cab2_active->show();
    }
    else
    {
        ui->lbl_cab2_active->hide();
    }

    //列车运行方向
    if(database->CTD_Forward_B1)
    {
        ui->lbl_cab1_direction->show();
    }
    else
    {
        ui->lbl_cab1_direction->hide();
    }

    if(database->CTD_Backward_B1)
    {
        ui->lbl_cab2_direction->show();
    }
    else
    {
        ui->lbl_cab2_direction->hide();
    }

    setTractStatus(ui->lbl_tract1,database->TCU1CT_IxMotoISO,database->TCU1CT_IxDCUMajorFlt_B1,database->TCU1CT_IxVVVFSts_B1);
    setTractStatus(ui->lbl_tract2,database->TCU2CT_IxMotoISO,database->TCU2CT_IxDCUMajorFlt_B1,database->TCU2CT_IxVVVFSts_B1);
    setTractStatus(ui->lbl_tract3,database->TCU3CT_IxMotoISO,database->TCU3CT_IxDCUMajorFlt_B1,database->TCU3CT_IxVVVFSts_B1);
    setTractStatus(ui->lbl_tract4,database->TCU4CT_IxMotoISO,database->TCU4CT_IxDCUMajorFlt_B1,database->TCU4CT_IxVVVFSts_B1);
    setTractStatus(ui->lbl_tract5,database->TCU5CT_IxMotoISO,database->TCU5CT_IxDCUMajorFlt_B1,database->TCU5CT_IxVVVFSts_B1);
    setTractStatus(ui->lbl_tract6,database->TCU6CT_IxMotoISO,database->TCU6CT_IxDCUMajorFlt_B1,database->TCU6CT_IxVVVFSts_B1);

}

void VehicleTractPage::setTractStatus(QLabel *label,bool cut,bool guohaha, bool status)
{
    if(cut)
    {
        label->setStyleSheet(TCUCUT);
    }
    else if(guohaha)
    {
        label->setStyleSheet(TCUFAULT);
    }
    else if(status)
    {
        label->setStyleSheet(TCUON);
    }
    else
    {
        label->setStyleSheet(TCUOFF);
    }
}
