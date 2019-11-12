#include "maintainceaccumulatorsubsystempage.h"
#include "ui_maintainceaccumulatorsubsystempage.h"

#define LINE "--"

MaintainceAccumulatorSubsystemPage::MaintainceAccumulatorSubsystemPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceAccumulatorSubsystemPage)
{
    ui->setupUi(this);
    current_acc=0;
    line1<<ui->line1_name;
    line2<<ui->line2_name;
    line3<<ui->line3_name;
    line4<<ui->line4_name;
    line5<<ui->line5_name;
    line6<<ui->line6_name;
    line7<<ui->line7_name;
    line8<<ui->line8_name;
}

MaintainceAccumulatorSubsystemPage::~MaintainceAccumulatorSubsystemPage()
{
    delete ui;
}

void MaintainceAccumulatorSubsystemPage::on_BTN1_pressed()
{
    changePage(uVehicleMaintainPage);
}

void MaintainceAccumulatorSubsystemPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void MaintainceAccumulatorSubsystemPage::on_BTN2_pressed()
{
    if(current_acc>0)
    {
        current_acc--;
    }
    else
    {
        current_acc=0;
    }
}

void MaintainceAccumulatorSubsystemPage::on_BTN3_pressed()
{
    if(current_acc<1)
    {
        current_acc++;
    }
    else
    {
        current_acc=1;
    }
}

void MaintainceAccumulatorSubsystemPage::updatePage()
{

        line1Status<<"超压电池数量";
        updateStatus(line1,line1Status);
        line1Status.clear();

        line2Status<<"低压电池数量";
        updateStatus(line2,line2Status);
        line2Status.clear();

        line3Status<<"超温电池数量";
        updateStatus(line3,line3Status);
        line3Status.clear();

        line4Status<<"超压报警电池";
        updateStatus(line4,line4Status);
        line4Status.clear();

        line5Status<<"超压报警电池电压值(mV)";
        updateStatus(line5,line5Status);
        line5Status.clear();

        line6Status<<"低压报警电池";
        updateStatus(line6,line6Status);
        line6Status.clear();

        line7Status<<"低压报警电池电压值(mV)";
        updateStatus(line7,line7Status);
        line7Status.clear();

        line8Status<<"超温报警电池";
        updateStatus(line8,line8Status);
        line8Status.clear();



}

void MaintainceAccumulatorSubsystemPage::updateStatus(QList<QLabel *> lbl, QList<QString> status)
{
    for(int i=0;i<status.size();i++)
    {
        lbl.at(i)->setText(status.at(i));
    }
}
