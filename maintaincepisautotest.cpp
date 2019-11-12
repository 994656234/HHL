#include "maintaincepisautotest.h"
#include "ui_maintaincepisautotest.h"
#define  BTNPRESS "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(187,188,247) , stop:1 rgb(19,20,87));border:0px solid;color: rgb(255, 255, 255);font:20px \"微软雅黑\";"
#define  BTNRELEASE  "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:20px \"微软雅黑\";"
#define  BTNOUTABLE "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:20px \"微软雅黑\";background-color:rgb(192,192,192)"


MaintaincePISAutoTest::MaintaincePISAutoTest(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintaincePISAutoTest)
{
    ui->setupUi(this);
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }
    TestButtons<<ui->BTNStartTest<<ui->BTNStopTest;
    //Signals<<&database->HMiCT_PISTestStart_B1<<&database->HMiCT_PISTestStop_B1;
    for(int i = 0;i<TestButtons.size();i++)
    {
        connect(TestButtons.at(i),SIGNAL(pressed()),this,SLOT(TestButtonsPressEvent()));
    }

}

MaintaincePISAutoTest::~MaintaincePISAutoTest()
{
    delete ui;
}


void MaintaincePISAutoTest::NBpressEvent()
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
}

void MaintaincePISAutoTest::TestButtonsPressEvent()
{
    int tmp_index = ((QPushButton*)this->sender())->whatsThis().toInt()-1;
   // *Signals[tmp_index] = true;
    timer2s[tmp_index] = this->startTimer(2000);
    ((QPushButton*)this->sender())->setStyleSheet(BTNPRESS);
   // database->HMiCT_SetFlagChecker_U8=0xAA;

}

void MaintaincePISAutoTest::timerEvent(QTimerEvent *e)
{
    for(int i = 0; i < 2;i++)
    {
        if(e->timerId() == timer2s[i])
        {
            killTimer(timer2s[i]);
            TestButtons[i]->setStyleSheet(BTNRELEASE);
           // *Signals[i] = false;
          //  database->HMiCT_SetFlagChecker_U8=0x55;
        }
    }
}
