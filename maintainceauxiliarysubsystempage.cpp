#include "maintainceauxiliarysubsystempage.h"
#include "ui_maintainceauxiliarysubsystempage.h"
#define LINE "--"

MaintainceAuxiliarySubsystemPage::MaintainceAuxiliarySubsystemPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceAuxiliarySubsystemPage)
{
    ui->setupUi(this);
    line1<<ui->line1_name<<ui->line1_1<<ui->line1_2<<ui->line1_3<<ui->line1_4;
    line2<<ui->line2_name<<ui->line2_1<<ui->line2_2<<ui->line2_3<<ui->line2_4;
    line3<<ui->line3_name<<ui->line3_1<<ui->line3_2<<ui->line3_3<<ui->line3_4;
    line4<<ui->line4_name<<ui->line4_1<<ui->line4_2<<ui->line4_3<<ui->line4_4;
    line5<<ui->line5_name<<ui->line5_1<<ui->line5_2<<ui->line5_3<<ui->line5_4;
    line6<<ui->line6_name<<ui->line6_1<<ui->line6_2<<ui->line6_3<<ui->line6_4;
    line7<<ui->line7_name<<ui->line7_1<<ui->line7_2<<ui->line7_3<<ui->line7_4;
    line8<<ui->line8_name<<ui->line8_1<<ui->line8_2<<ui->line8_3<<ui->line8_4;
    current_auxi=0;
}

MaintainceAuxiliarySubsystemPage::~MaintainceAuxiliarySubsystemPage()
{
    delete ui;
}


void MaintainceAuxiliarySubsystemPage::on_BTN1_pressed()
{
    changePage(uVehicleMaintainPage);
}

void MaintainceAuxiliarySubsystemPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void MaintainceAuxiliarySubsystemPage::updatePage()
{


}

void MaintainceAuxiliarySubsystemPage::updateStatus(QList<QLabel *> lbl, QList<QString> status)
{
    for(int i=0;i<status.size();i++)
    {
        lbl.at(i)->setText(status.at(i));
    }
}

void MaintainceAuxiliarySubsystemPage::on_BTN2_pressed()
{
    if(current_auxi>0)
    {
        current_auxi--;
    }
    else
    {
        current_auxi=0;
    }
}

void MaintainceAuxiliarySubsystemPage::on_BTN3_pressed()
{
    if(current_auxi<2)
    {
        current_auxi++;
    }
    else
    {
        current_auxi=2;
    }
}
