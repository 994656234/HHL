#include "maintainceaccumulatorsubsystempage.h"
#include "ui_maintainceaccumulatorsubsystempage.h"
#define  BTNPRESS "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(187,188,247) , stop:1 rgb(19,20,87));border:0px solid;color: rgb(255, 255, 255);font:20px \"微软雅黑\";"
#define  BTNRELEASE  "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:20px \"微软雅黑\";"
#define  BTNOUTABLE "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:20px \"微软雅黑\";background-color:rgb(192,192,192)"


MaintainceAccumulatorSubsystemPage::MaintainceAccumulatorSubsystemPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceAccumulatorSubsystemPage)
{
    ui->setupUi(this);
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


void MaintainceAccumulatorSubsystemPage::updatePage()
{

    //  qDebug()<< database->tamianClean;

}



void MaintainceAccumulatorSubsystemPage::on_BTNStartTest_pressed()
{
    ui->BTNStartTest->setStyleSheet(BTNPRESS);
    timer2s[0] = this->startTimer(120000);
    database->tamianClean=true;
    database->DiCT_SetFlagChecker_U8=0xAA;
    ui->BTNStartTest->setEnabled(false);
}

void MaintainceAccumulatorSubsystemPage::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == timer2s[0])
    {
        killTimer(timer2s[0]);
        ui->BTNStartTest->setStyleSheet(BTNRELEASE);
        database->tamianClean=false;
        database->DiCT_SetFlagChecker_U8=0x55;
        ui->BTNStartTest->setEnabled(true);

    }
}
