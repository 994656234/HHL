#include "vehicleauxiliarypage.h"
#include "ui_vehicleauxiliarypage.h"
#define SIVFAULT "border-image: url(:/images/image/sivfault.bmp);"
#define SIVNORMAL "border-image: url(:/images/image/sivrun.bmp);"
#define SIVSTOP "border-image: url(:/images/image/sivunknown.bmp);"
#define SIVUNKNOW "border-image: url(:/images/image/doorunknow.png);"

#define BCMFAULT "border-image: url(:/images/image/sivfault2.bmp);"
#define BCMNORMAL "border-image: url(:/images/image/sivrun2.bmp);"
#define BCMSTOP "border-image: url(:/images/image/sivunknown2.bmp);"
#define BCMUNKNOW "border-image: url(:/images/image/doorunknow.png);"

#define METROPOWERON "border-image: url(:/images/image/workshoponsupply.png);"
#define METROPOWEROFF "border-image: url(:/images/image/workshoponnosupply.png);"

VehicleAuxiliaryPage::VehicleAuxiliaryPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleAuxiliaryPage)
{
    ui->setupUi(this);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();
}

VehicleAuxiliaryPage::~VehicleAuxiliaryPage()
{
    delete ui;
}

void VehicleAuxiliaryPage::updatePage()
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

    if(database->CTD_MP1WorkShop_B1)
    {
        ui->lbl_metroPower1->setStyleSheet(METROPOWERON);
    }
    else
    {
        ui->lbl_metroPower1->setStyleSheet(METROPOWEROFF);
    }

    if(database->CTD_MP2WorkShop_B1)
    {
        ui->lbl_metroPower2->setStyleSheet(METROPOWERON);
    }
    else
    {
        ui->lbl_metroPower2->setStyleSheet(METROPOWEROFF);
    }
    SIVStatus <<database->CTD_ACU1OLINE_B1<<database->ACU1CT_IxSIVMajorF_B1<<database->ACU1CT_IxSIVOK_B1;
    setSIVStatus(ui->lbl_AC1,SIVStatus);
    SIVStatus.clear();

    SIVStatus <<database->CTD_ACU2OLINE_B1<<database->ACU2CT_IxSIVMajorF_B1<<database->ACU2CT_IxSIVOK_B1;
    setSIVStatus(ui->lbl_AC2,SIVStatus);
    SIVStatus.clear();

    BCMStatus<<database->CTD_ACU1OLINE_B1<<database->ACU1CT_IxChgMajorF_B1<<database->ACU1CT_IxDCOK_B1;
    setBCMStatus(ui->lbl_DC1,BCMStatus);
    BCMStatus.clear();

    BCMStatus<<database->CTD_ACU2OLINE_B1<<database->ACU2CT_IxChgMajorF_B1<<database->ACU2CT_IxDCOK_B1;
    setBCMStatus(ui->lbl_DC2,BCMStatus);
    BCMStatus.clear();


}

void VehicleAuxiliaryPage::setSIVStatus(QLabel *label, QList<bool> status)
{

    if(!status.at(0))
    {
        label->setStyleSheet(SIVUNKNOW);
    }
    else if(status.at(1))
    {
        label->setStyleSheet(SIVFAULT);
    }
    else if(status.at(2))
    {
        label->setStyleSheet(SIVNORMAL);
    }
    else
    {
        label->setStyleSheet(SIVSTOP);
    }

}

void VehicleAuxiliaryPage::setBCMStatus(QLabel *label, QList<bool> status)
{
    if(!status.at(0))
    {
        label->setStyleSheet(BCMUNKNOW);
    }
    else if(status.at(1))
    {
        label->setStyleSheet(BCMFAULT);
    }
    else if(status.at(2))
    {
        label->setStyleSheet(BCMNORMAL);
    }
    else
    {
        label->setStyleSheet(BCMSTOP);
    }
}
