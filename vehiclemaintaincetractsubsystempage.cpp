#include "vehiclemaintaincetractsubsystempage.h"
#include "ui_vehiclemaintaincetractsubsystempage.h"
#include "qdebug.h"
#define LINE "--"

VehicleMaintainceTractSubsystemPage::VehicleMaintainceTractSubsystemPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleMaintainceTractSubsystemPage)
{
    ui->setupUi(this);
    line1<<ui->line1_1<<ui->line1_2<<ui->line1_3<<ui->line1_4<<ui->line1_5<<ui->line1_6;
    line2<<ui->line2_1<<ui->line2_6;
    line3<<ui->line3_1<<ui->line3_2<<ui->line3_3<<ui->line3_4<<ui->line3_5<<ui->line3_6;
    line4<<ui->line4_1<<ui->line4_2<<ui->line4_3<<ui->line4_4<<ui->line4_5<<ui->line4_6;
    line5<<ui->line5_1<<ui->line5_2<<ui->line5_3<<ui->line5_4<<ui->line5_5<<ui->line5_6;
    //line6<<ui->line6_1<<ui->line6_2<<ui->line6_3<<ui->line6_4<<ui->line6_5<<ui->line6_6;
    //line7<<ui->line7_1<<ui->line7_2<<ui->line7_3<<ui->line7_4<<ui->line7_5<<ui->line7_6;
    //line8<<ui->line8_1<<ui->line8_2<<ui->line8_3<<ui->line8_4<<ui->line8_5<<ui->line8_6;
    current=0;
}

VehicleMaintainceTractSubsystemPage::~VehicleMaintainceTractSubsystemPage()
{
    delete ui;
}

void VehicleMaintainceTractSubsystemPage::on_BTN1_pressed()
{
    changePage(uVehicleMaintainPage);
}

void VehicleMaintainceTractSubsystemPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void VehicleMaintainceTractSubsystemPage::updatePage()
{
    line1Status.clear();
    line1Status<<database->TCU1CT_IuiInverterCurrent_U16<<database->TCU2CT_IuiInverterCurrent_U16
                 <<database->TCU3CT_IuiInverterCurrent_U16<<database->TCU4CT_IuiInverterCurrent_U16
                 <<database->TCU5CT_IuiInverterCurrent_U16<<database->TCU6CT_IuiInverterCurrent_U16;
    updateStatus(line1,line1Status,"A");

    line2Status.clear();
    line2Status<<database->ACU1CT_UWCurrent_U16<<database->ACU2CT_UWCurrent_U16;
    updateStatus(line2,line2Status,"A");

    line3Status.clear();
    line3Status<<database->TCU1CT_IiMiddleCurrent_I16<<database->TCU2CT_IiMiddleCurrent_I16
                 <<database->TCU3CT_IiMiddleCurrent_I16<<database->TCU4CT_IiMiddleCurrent_I16
                 <<database->TCU5CT_IiMiddleCurrent_I16<<database->TCU6CT_IiMiddleCurrent_I16;
    updateStatus(line3,line3Status,"A");

    line4Status.clear();
    line4Status<<database->TCU1CT_IiMiddleVoltage_I16<<database->TCU2CT_IiMiddleVoltage_I16
                 <<database->TCU3CT_IiMiddleVoltage_I16<<database->TCU4CT_IiMiddleVoltage_I16
                 <<database->TCU5CT_IiMiddleVoltage_I16<<database->TCU6CT_IiMiddleVoltage_I16;
    updateStatus(line4,line4Status,"V");

    line5Status.clear();
    line5Status<<database->TCU1CT_BRCV_U16<<database->TCU2CT_BRCV_U16
                 <<database->TCU3CT_BRCV_U16<<database->TCU4CT_BRCV_U16
                 <<database->TCU5CT_BRCV_U16<<database->TCU6CT_BRCV_U16;
    updateStatus(line5,line5Status,"A");
}

void VehicleMaintainceTractSubsystemPage::updateStatus(QList<QLabel*> lbl, QList<short> status, QString str)
{
    if (lbl.size() != status.size())
    {
        qDebug()<<"!!!!!";
        return;
    }
    for(int i=0;i<status.size();i++)
    {
        lbl.at(i)->setText(QString::number(status.at(i)) + str);
    }
}

void VehicleMaintainceTractSubsystemPage::updateStatus(QList<QLabel *> lbl, QList<unsigned short> status, QString str)
{
    if (lbl.size() != status.size())
    {
        qDebug()<<"!!!!!";
        return;
    }
    for(int i=0;i<status.size();i++)
    {
        lbl.at(i)->setText(QString::number(status.at(i)) + str);
    }
}

void VehicleMaintainceTractSubsystemPage::on_BTN2_pressed()
{
    if(current>0)
    {
        current--;
    }
    else
    {
        current=0;
    }
}

void VehicleMaintainceTractSubsystemPage::on_BTN3_pressed()
{
    if(current<2)
    {
        current++;
    }
    else
    {
        current=2;
    }
}


QString VehicleMaintainceTractSubsystemPage::isVelid(bool haha, QString status)
{
    if(haha)
    {
        return status;
    }
    else
    {
        return "0";
    }
}
