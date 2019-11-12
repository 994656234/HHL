#include "vehiclelinecircuitbreakerpage.h"
#include "ui_vehiclelinecircuitbreakerpage.h"

#define  BTNPRESS "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(187,188,247) , stop:1 rgb(19,20,87));border:0px solid;color: rgb(255, 255, 255);font:16px \"微软雅黑\";border-radius:10px;"
#define  BTNRELEASE  "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:16px \"微软雅黑\";border-radius:10px;"
#define  BTNOUTABLE "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:16px \"微软雅黑\";border-radius:10px;background-color:rgb(192,192,192)"

VehicleLineCircuitBreakerPage::VehicleLineCircuitBreakerPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleLineCircuitBreakerPage)
{
    ui->setupUi(this);
    ResetButtons<<ui->BTN_SIV_Reset_MC1<<ui->BTN_SIV_Reset_MC2<<ui->BTN_VVVF1<<ui->BTN_VVVF2<<ui->BTN_VVVF3
               <<ui->BTN_VVVF4<<ui->BTN_VVVF5<<ui->BTN_VVVF6;
    ResetSignals<<&database->DiCT_ACU1Reset_B1<<&database->DiCT_ACU2Reset_B1
               <<&database->DiCT_MC1TCUFaultReset_B1<<&database->DiCT_Mp11TCUFaultReset_B1
              <<&database->DiCT_Mp12TCUFaultReset_B1<<&database->DiCT_Mp22TCUFaultReset_B1
             <<&database->DiCT_Mp21TCUFaultReset_B1<<&database->DiCT_MC2TCUFaultReset_B1;
    for(int i = 0;i<ResetButtons.size();i++)
    {
        connect(ResetButtons.at(i),SIGNAL(pressed()),this,SLOT(RstButtonsPressEvent()));
    }
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();

}

VehicleLineCircuitBreakerPage::~VehicleLineCircuitBreakerPage()
{
    delete ui;
}

void VehicleLineCircuitBreakerPage::updatePage()
{

}


void VehicleLineCircuitBreakerPage::RstButtonsPressEvent()
{
    int tmp_index = ((QPushButton*)this->sender())->whatsThis().toInt()-1;
    *ResetSignals[tmp_index] = true;
    timer2s[tmp_index] = this->startTimer(2000);
    ((QPushButton*)this->sender())->setStyleSheet(BTNPRESS);
}

void VehicleLineCircuitBreakerPage::timerEvent(QTimerEvent *e)
{
    for(int i = 0; i < 8;i++)
    {
        if(e->timerId() == timer2s[i])
        {
            killTimer(timer2s[i]);
            ResetButtons[i]->setStyleSheet(BTNRELEASE);
            *ResetSignals[i] = false;
        }
    }
}
