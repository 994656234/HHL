#include "maintaincerunninggearsubsystempage.h"
#include "ui_maintaincerunninggearsubsystempage.h"

MaintainceRunningGearSubsystemPage::MaintainceRunningGearSubsystemPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceRunningGearSubsystemPage)
{
    ui->setupUi(this);

}

MaintainceRunningGearSubsystemPage::~MaintainceRunningGearSubsystemPage()
{
    delete ui;
}

void MaintainceRunningGearSubsystemPage::on_BTN1_pressed()
{
    changePage(uVehicleMaintainPage);
}

void MaintainceRunningGearSubsystemPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void MaintainceRunningGearSubsystemPage::updatePage()
{

}

void MaintainceRunningGearSubsystemPage::updateStatus(QList<QLabel *> lbl, QList<QString> status)
{
    for(int i=0;i<status.size();i++)
    {
        lbl.at(i)->setText(status.at(i));
    }
}

