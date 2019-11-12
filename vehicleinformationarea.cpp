#include "vehicleinformationarea.h"
#include "ui_vehicleinformationarea.h"
#include "crrcfault.h"
#include "qdebug.h"

#define     LEVEL1  "background-color:red;color:black;font:16px,\"微软雅黑\";"
#define     LEVEL2  "background-color:yellow;color:black;font:16px,\"微软雅黑\";"
#define     LEVEL3  "background-color:white;color:black;font:16px,\"微软雅黑\";"
#define     LEVELNONE  "background-color:rgb(0, 0, 50);color:black;font:16px,\"微软雅黑\";"

#define BUTTONUP "font: 20px, \"微软雅黑\";color: white;background-color: rgb(0, 0, 50);border:2px groove  rgb(100, 100, 200);border-radius:10px;padding:2px 4px"
#define BUTTONDOWN  "font: 20px, \"微软雅黑\";color: white;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(150,150,200,255),stop:1 rgba(0,0,50,255));border:2px groove  rgb(100, 100, 200);border-radius:10px;padding:2px 4px ;"

VehicleInformationArea::VehicleInformationArea(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleInformationArea)
{
    ui->setupUi(this);
    m_confirmfaultIndex = 0;
    m_deletefaultIndex = 0;
}

VehicleInformationArea::~VehicleInformationArea()
{
    delete ui;
}


void VehicleInformationArea::updatePage()
{
    if(0 < CrrcFault::getCrrcFault()->getConfirmFaultListSize() )
    {
        this->ui->BTNConfirmFault->show();
        if(CrrcFault::getCrrcFault()->getConfirmFaultLevel(0) == "1")
        {
            this->ui->LBLFaultName->setStyleSheet(LEVEL1);
        }else if(CrrcFault::getCrrcFault()->getConfirmFaultLevel(0) == "2")
        {
            this->ui->LBLFaultName->setStyleSheet(LEVEL2);
        }else if(CrrcFault::getCrrcFault()->getConfirmFaultLevel(0) == "3")
        {
            this->ui->LBLFaultName->setStyleSheet(LEVEL3);
        }
        this->ui->LBLFaultName->setText("  "+CrrcFault::getCrrcFault()->getConfirmFaultCode(0)+"    "+
                                        CrrcFault::getCrrcFault()->getConfirmFaultLevel(0)+"级故障    "+
                                        CrrcFault::getCrrcFault()->getConfirmFaultName(0)+"    "+
                                        CrrcFault::getCrrcFault()->getConfirmFaultDate(0)+"    "+
                                        CrrcFault::getCrrcFault()->getConfirmFaultTime(0));
    }else
    {
        this->ui->BTNConfirmFault->hide();
        this->ui->LBLFaultName->setText("");
        this->ui->LBLFaultName->setStyleSheet(LEVELNONE);
    }
}

void VehicleInformationArea::on_BTNConfirmFault_pressed()
{
    this->ui->BTNConfirmFault->setStyleSheet(NButtonDOWN);
}

void VehicleInformationArea::on_BTNConfirmFault_released()
{

    if(0 < CrrcFault::getCrrcFault()->getConfirmFaultListSize() )
    {
        CrrcFault::getCrrcFault()->deleteConfirmFault(0);
        this->ui->BTNConfirmFault->setStyleSheet(NButtonUP);
    }
}
