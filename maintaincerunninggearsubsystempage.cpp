#include "maintaincerunninggearsubsystempage.h"
#include "ui_maintaincerunninggearsubsystempage.h"

MaintainceRunningGearSubsystemPage::MaintainceRunningGearSubsystemPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceRunningGearSubsystemPage)
{
    ui->setupUi(this);
    column1<<ui->line1_1<<ui->line2_1<<ui->line3_1<<ui->line4_1
           <<ui->line5_1<<ui->line6_1<<ui->line7_1<<ui->line8_1
           <<ui->line9_1<<ui->line10_1<<ui->line11_1<<ui->line12_1
           <<ui->line13_1<<ui->line14_1<<ui->line15_1<<ui->line16_1;
    column2<<ui->line1_2<<ui->line2_2<<ui->line3_2<<ui->line4_2
           <<ui->line5_2<<ui->line6_2<<ui->line7_2<<ui->line8_2
           <<ui->line9_2<<ui->line10_2<<ui->line11_2<<ui->line12_2
           <<ui->line13_1<<ui->line14_2<<ui->line15_2<<ui->line16_2;

    column3<<ui->line1_3<<ui->line2_3<<ui->line3_3<<ui->line4_3
           <<ui->line5_3<<ui->line6_3<<ui->line7_3<<ui->line8_3
           <<ui->line9_3<<ui->line10_3<<ui->line11_3<<ui->line12_3
           <<ui->line13_3<<ui->line14_3<<ui->line15_3<<ui->line16_3;

    column4<<ui->line1_4<<ui->line2_4<<ui->line3_4<<ui->line4_4
           <<ui->line5_4<<ui->line6_4<<ui->line7_4<<ui->line8_4
           <<ui->line9_4<<ui->line10_4<<ui->line11_4<<ui->line12_4
           <<ui->line13_4<<ui->line14_4<<ui->line15_4<<ui->line16_4;
}

MaintainceRunningGearSubsystemPage::~MaintainceRunningGearSubsystemPage()
{
    delete ui;
}

void MaintainceRunningGearSubsystemPage::on_BTN1_pressed()
{
    changePage(uVehicleTrainArea);
}

void MaintainceRunningGearSubsystemPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void MaintainceRunningGearSubsystemPage::updatePage()
{
    updateStatus(column1,database->BMS1CT_TMPE_U8,database->BMS1CT_FLAG_U8);
    updateStatus(column2,database->BMS2CT_TMPE_U8,database->BMS2CT_FLAG_U8);
    updateStatus(column3,database->BMS3CT_TMPE_U8,database->BMS3CT_FLAG_U8);
    updateStatus(column4,database->BMS4CT_TMPE_U8,database->BMS4CT_FLAG_U8);
}

void MaintainceRunningGearSubsystemPage::updateStatus(QList<QLabel *> lbl, unsigned char value, unsigned char flag)
{
    if(flag > 0 && flag < 17 )
    {
        lbl.at(flag)->setText(QString::number(value - 55));
    }
    else
    {
        for(int i =0; i< lbl.size(); i++)
        {
            lbl.at(flag)->setText("--");
        }
    }
}

