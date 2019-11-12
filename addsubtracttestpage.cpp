#include "addsubtracttestpage.h"
#include "ui_addsubtracttestpage.h"
#define  BTNPRESS "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(187,188,247) , stop:1 rgb(19,20,87));border:0px solid;color: rgb(255, 255, 255);font:20px \"微软雅黑\";"
#define  BTNRELEASE  "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:20px \"微软雅黑\";"
#define  BTNOUTABLE "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:20px \"微软雅黑\";background-color:rgb(192,192,192)"

AddSubtractTestPage::AddSubtractTestPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::AddSubtractTestPage)
{
    ui->setupUi(this);
    buttons<<ui->BTN1<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }

    statusButtons<<ui->BTNStartTest<<ui->BTNStopTest;

    Signals<<&database->DiCT_ACDETestStartFlag_B1<<&database->DiCT_ACDETestStopFlag_B1;

    foreach(QPushButton* button,statusButtons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(statusBTNPressEvent()));
    }

    lbls<<ui->lbl_metroSpeed<<ui->lbl_level<<ui->lbl_40Speed<<ui->lbl_40Level
            <<ui->lbl_80Speed<<ui->lbl_80Level<<ui->lbl_subBrakeSpeed<<ui->lbl_brakeDistance
            <<ui->lbl_subLevel<<ui->lbl_subSpeed<<ui->lbl_brakeMode;
}

AddSubtractTestPage::~AddSubtractTestPage()
{
    delete ui;
}

void AddSubtractTestPage::NBpressEvent()
{
    QString BTNName=((QPushButton*)this->sender())->objectName();
    if(BTNName=="BTN1")
    {
        changePage(uVehicleMaintainPage);
    }
    else if(BTNName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }
    else
    {}

}

void AddSubtractTestPage::statusBTNPressEvent()
{
    int tmp_index = ((QPushButton*)this->sender())->whatsThis().toInt()-1;
    //*Signals[tmp_index]=true;
    timer2s[tmp_index] = this->startTimer(2000);
    ((QPushButton*)this->sender())->setStyleSheet(BTNPRESS);
    //database->HMiCT_SetFlagChecker_U8=0xAA;
}

void AddSubtractTestPage::timerEvent(QTimerEvent *e)
{

    for(int i = 0; i < 2;i++)
    {
        if(e->timerId() == timer2s[i])
        {
            killTimer(timer2s[i]);
            statusButtons[i]->setStyleSheet(BTNRELEASE);
           // *Signals[i] = false;
            //database->HMiCT_SetFlagChecker_U8=0x55;
        }
    }
}


void AddSubtractTestPage::updatePage()
{


}


void AddSubtractTestPage::setLabelStatus(QList<QLabel *> lbls, QList<QString> status)
{
    for(int i=0;i<lbls.length();i++)
    {
        lbls.value(i)->setText(status.value(i));
    }
}
