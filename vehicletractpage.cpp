#include "vehicletractpage.h"
#include "ui_vehicletractpage.h"

#define TCUFAULT "border-image: url(:/images/image/tcufault.png);"
#define TCUON "border-image: url(:/images/image/tcurun.png);"
#define TCUOFF "border-image: url(:/images/image/tcuoff.png);"
#define TCUUNKNOW "border-image: url(:/images/image/doorunknow.png);"

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


    setTractStatus(ui->lbl_tract1,database->CTD_TCU1OLINE_B1,database->TCU1CT_IxDCUMajorFlt_B1);
    setTractStatus(ui->lbl_tract2,database->CTD_TCU2OLINE_B1,database->TCU2CT_IxDCUMajorFlt_B1);
    setTractStatus(ui->lbl_tract3,database->CTD_TCU3OLINE_B1,database->TCU3CT_IxDCUMajorFlt_B1);
    setTractStatus(ui->lbl_tract4,database->CTD_TCU4OLINE_B1,database->TCU4CT_IxDCUMajorFlt_B1);
    setTractStatus(ui->lbl_tract5,database->CTD_TCU5OLINE_B1,database->TCU5CT_IxDCUMajorFlt_B1);
    setTractStatus(ui->lbl_tract6,database->CTD_TCU6OLINE_B1,database->TCU6CT_IxDCUMajorFlt_B1);

}

void VehicleTractPage::setTractStatus(QLabel *label,bool guohaha, bool status)
{
    if(!guohaha)
    {
        label->setStyleSheet(TCUUNKNOW);
    }
    else if(guohaha&&status)
    {
        label->setStyleSheet(TCUFAULT);
    }
    else if(guohaha&&!status)
    {
        label->setStyleSheet(TCUON);
    }    
    else
    {
        label->setStyleSheet(TCUOFF);
    }


}
