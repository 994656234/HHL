#include "maintaincebatterysubsystempage.h"
#include "ui_maintaincebatterysubsystempage.h"

MaintainceBatterySubsystemPage::MaintainceBatterySubsystemPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceBatterySubsystemPage)
{
    ui->setupUi(this);
    line1<<ui->line1_1<<ui->line1_4;
    line2<<ui->line2_1<<ui->line2_4;
    line3<<ui->line3_1<<ui->line3_4;

}

MaintainceBatterySubsystemPage::~MaintainceBatterySubsystemPage()
{
    delete ui;
}

void MaintainceBatterySubsystemPage::updatePage()
{
    line1Status.clear();
    line1Status<<database->ACU1CT_IuiBtyVltg_U16<<database->ACU2CT_IuiBtyVltg_U16;
    updateStatus(line1,line1Status,"V");

    line2Status.clear();
    line2Status<<database->ACU1CT_IiBtyTmp_I16<<database->ACU1CT_IiBtyTmp_I16;
    updateStatus(line2,line2Status,"℃");

    line3Status.clear();
    line3Status<<database->ACU1CT_IiBtyChgCurrent_I16<<database->ACU2CT_IiBtyChgCurrent_I16;
    updateStatus(line3,line3Status,"A");
}

void MaintainceBatterySubsystemPage::updateStatus(QList<QLabel *> lbl, QList<short> status, QString str)
{
    if (lbl.size() != status.size())
    {
        return;
    }
    for(int i=0;i<status.size();i++)
    {
        lbl.at(i)->setText(QString::number(status.at(i)) + str);
    }
}

void MaintainceBatterySubsystemPage::updateStatus(QList<QLabel *> lbl, QList<unsigned short> status, QString str)
{
    if (lbl.size() != status.size())
    {
        return;
    }
    for(int i=0;i<status.size();i++)
    {
        lbl.at(i)->setText(QString::number(status.at(i)) + str);
    }
}

void MaintainceBatterySubsystemPage::on_BTN1_pressed()
{
    changePage(uVehicleMaintainPage);
}

void MaintainceBatterySubsystemPage::on_BTN2_pressed()
{

}

void MaintainceBatterySubsystemPage::on_BTN3_pressed()
{

}

void MaintainceBatterySubsystemPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}
