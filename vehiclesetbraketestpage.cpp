#include "vehiclesetbraketestpage.h"
#include "ui_vehiclesetbraketestpage.h"
#include "qdebug.h"

#define TESTSUCCESS "color: rgb(255, 255, 255);font:23px \"微软雅黑\";background-color: rgb(85, 255, 0);"
#define TESTFAULT "background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);font:23px \"微软雅黑\";"
#define NORMALSIGNAL "background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);font:23px \"微软雅黑\";"

#define BTNPRESS "font: 20px, \"微软雅黑\";color: black;background-color:blue;"
#define BTNRELEASE "font: 20px, \"微软雅黑\";color: black;transparent;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(170,170,170,255),stop:1 rgba(150,150,150,255));"

#define GREEN "background-color: rgb(0, 255, 0);font: 18px, \"微软雅黑\";"
#define RED "background-color: rgb(255, 0, 0);font: 18px, \"微软雅黑\";"
#define GRAY "background-color: rgb(159, 158, 159);font: 18px, \"微软雅黑\";"
#define WHITE "background-color: rgb(255, 255, 255);font: 18px, \"微软雅黑\";"

VehicleSetBrakeTestPage::VehicleSetBrakeTestPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleSetBrakeTestPage)
{
    ui->setupUi(this);
    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome<<ui->BTN_start<<ui->BTN_stop;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }

    testButtons<<ui->BTN_start<<ui->BTN_stop;
    testSignals<<&database->DiCT_BCUSelfTestReq_B1<<&database->DiCT_BCUSelfTestStop_B1;
    for(int i = 0;i<testButtons.size();i++)
    {
        connect(testButtons.at(i),SIGNAL(pressed()),this,SLOT(TestButtonsPressEvent()));
    }
    ui->BTN_stop->hide();
    ui->BTN_stop->setEnabled(false);
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();


}

VehicleSetBrakeTestPage::~VehicleSetBrakeTestPage()
{
    delete ui;
}

void VehicleSetBrakeTestPage::pushButtonPressedEvent()
{
    QString btnName=((QPushButton*)this->sender())->objectName();

    if(btnName=="BTN1")
    {
        changePage(uVehicleSetPage);
    }
    else if(btnName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }

}


void VehicleSetBrakeTestPage::timerEvent(QTimerEvent *e)
{
    for(int i = 0; i < 2;i++)
    {
        if(e->timerId() == timer2s[i])
        {
            killTimer(timer2s[i]);
            testButtons[i]->setStyleSheet(BTNRELEASE);
            *testSignals[i] = false;
        }
    }

}

void VehicleSetBrakeTestPage::updatePage()
{
   //
    //司机室激活
    if(database->CTD_MCTActive_B1)
    {
        ui->lbl_cab1_active->show();
    }
    else
    {
        ui->lbl_cab1_active->hide();
    }

    if(database->CTD_MC2Active_B1)
    {
        ui->lbl_cab2_active->show();
    }
    else
    {
        ui->lbl_cab2_active->hide();
    }

    //列车运行方向
    if(database->CTD_Forward_B1)
    {
        ui->lbl_cab1_direction->show();
    }
    else
    {
        ui->lbl_cab1_direction->hide();
    }

    if(database->CTD_Backward_B1)
    {
        ui->lbl_cab2_direction->show();
    }
    else
    {
        ui->lbl_cab2_direction->hide();
    }

    if(database->BiCT_STRdy_B1)
    {
        ui->lbl_testCondition1->setStyleSheet(GREEN);
        ui->lbl_testCondition1->setText("自检条件满足");
    }
    else
    {
        ui->lbl_testCondition1->setStyleSheet(RED);
        ui->lbl_testCondition1->setText("自检条件不满足");
    }


    if(database->BiCT_STAct_B1)
    {
        ui->lbl_testStatus1->setStyleSheet(GREEN);
        ui->lbl_testStatus1->setText("自检进行中");
    }
    else if(database->BiCT_STBrOff_B1)
    {
        ui->lbl_testStatus1->setStyleSheet(GRAY);
        ui->lbl_testStatus1->setText("自检退出");
    }
    else
    {
        ui->lbl_testStatus1->setStyleSheet(WHITE);
        ui->lbl_testStatus1->setText("--");
    }



    if(database->BiCT_STOK_B1)
    {
        ui->lbl_testResult1->setStyleSheet(GREEN);
        ui->lbl_testResult1->setText("自检成功");
    }
    else if(database->BiCT_STFail_B1)
    {
        ui->lbl_testResult1->setStyleSheet(RED);
        ui->lbl_testResult1->setText("自检失败");
    }
    else
    {
        ui->lbl_testResult1->setStyleSheet(WHITE);
        ui->lbl_testResult1->setText("--");
    }

}

void VehicleSetBrakeTestPage::TestButtonsPressEvent()
{
    int tmp_index = ((QPushButton*)this->sender())->whatsThis().toInt()-1;
    *testSignals[tmp_index] = true;
    timer2s[tmp_index] = this->startTimer(2000);
    ((QPushButton*)this->sender())->setStyleSheet(BTNPRESS);
}

