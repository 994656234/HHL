#include "vehiclesetstationpage.h"
#include "ui_vehiclesetstationpage.h"
#include "qdebug.h"

#define ONFOCUS "border-right:2px solid rgb(255,255,0);border-bottom:2px solid rgb(255,255,0);color:rgb(255,255,255);font:24px \"微软雅黑\";"
#define OUTFOCUS "border-right:2px solid rgb(255,188,142);border-bottom:2px solid rgb(255,188,142);color:rgb(255,255,255);font:24px \"微软雅黑\";"
#define  BTNPRESS "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(187,188,247) , stop:1 rgb(19,20,87));border:0px solid;color: rgb(255, 255, 255);font:20px \"微软雅黑\";border-radius:10px;"
#define  BTNRELEASE  "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:20px \"微软雅黑\";border-radius:10px;"

VehicleSetStationPage::VehicleSetStationPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleSetStationPage)
{
    ui->setupUi(this);    
    buttons<<ui->BTNStation1<<ui->BTNStation2<<ui->BTNStation3<<ui->BTNStation4<<ui->BTNStation5<<ui->BTNStation6
            <<ui->BTNStation7<<ui->BTNStation8<<ui->BTNStation9<<ui->BTNStation10<<ui->BTNStation11<<ui->BTNStation12
             <<ui->BTNEmgyStart<<ui->BTNEmgyStop;
    foreach(QPushButton* button , buttons)
    {
        connect(button,SIGNAL(clicked()),this,SLOT(buttonPushEvent()));
    }
    setStationNumber=0;
}

VehicleSetStationPage::~VehicleSetStationPage()
{
    delete ui;
}

void VehicleSetStationPage::showEvent(QShowEvent *)
{
    this->database->DiCT_SetFlagChecker_U8 = 0xAA;
}
void VehicleSetStationPage::hideEvent(QHideEvent *)
{
    this->database->DiCT_SetFlagChecker_U8 = 0x55;
    killTimer(timerstart);
    this->database->DiCT_EmgyMsgStart_B1 = false;
    this->database->DiCT_EmgyMsgStop_B1 = false;
    this->database->DiCT_EmgyMsgCode_U8 =  0;

    for(int i = 0;i<buttons.size();i++)
    {
        buttons.at(i)->setStyleSheet(BTNRELEASE);
    }
}

void VehicleSetStationPage::on_BTN1_pressed()
{
    changePage(uVehicleSetPage);
}

void VehicleSetStationPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void VehicleSetStationPage::on_BTN9_pressed()
{

}

void VehicleSetStationPage::buttonPushEvent()
{

    int number=((QPushButton*)sender())->whatsThis().toInt();
    if(number==13)
    {
        this->database->DiCT_EmgyMsgStart_B1 = true;
        timerstart = startTimer(1000);
        ((QPushButton*)sender())->setStyleSheet(BTNPRESS);
    }
    else if(number==14)
    {
        timerstart = startTimer(1000);
        this->database->DiCT_EmgyMsgStop_B1 = true;
        ((QPushButton*)sender())->setStyleSheet(BTNPRESS);
    }
    else
    {
        setStationNumber=number;
        for(int i = 0;i<buttons.size();i++)
        {
            buttons.at(i)->setStyleSheet(BTNRELEASE);
        }
        ((QPushButton*)sender())->setStyleSheet(BTNPRESS);
    }

}

void VehicleSetStationPage::updatePage()
{
    this->database->DiCT_EmgyMsgCode_U8=setStationNumber;
    //qDebug()<< this->database->DiCT_EmgyMsgStart_B1<<"++++++++++"<<this->database->DiCT_EmgyMsgStop_B1<<"+++++++++++++++"<<this->database->DiCT_EmgyMsgCode_U8;
}

void VehicleSetStationPage::timerEvent(QTimerEvent *e)
{
        killTimer(timerstart);
        this->database->DiCT_EmgyMsgStop_B1 = false;
        this->database->DiCT_EmgyMsgStart_B1 = false;
      //  this->database->DiCT_EmgyMsgCode_U8 =  0;
        timerstart=0;
        for(int i = 0;i<buttons.size();i++)
        {
            buttons.at(i)->setStyleSheet(BTNRELEASE);
        }
}
