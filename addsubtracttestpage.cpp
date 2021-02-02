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
            <<ui->lbl_subLevel<<ui->lbl_subSpeed;


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
    *Signals[tmp_index]=true;
    timer2s[tmp_index] = this->startTimer(2000);
    ((QPushButton*)this->sender())->setStyleSheet(BTNPRESS);
    database->DiCT_SetFlagChecker_U8=0xAA;
}

void AddSubtractTestPage::timerEvent(QTimerEvent *e)
{

    for(int i = 0; i < 2;i++)
    {
        if(e->timerId() == timer2s[i])
        {
            killTimer(timer2s[i]);
            statusButtons[i]->setStyleSheet(BTNRELEASE);
            *Signals[i] = false;
            database->DiCT_SetFlagChecker_U8=0x55;
        }
    }
}


void AddSubtractTestPage::updatePage()
{
    // qDebug()<<database->DiCT_ACDETestStartFlag_B1<<"                      "<<database->DiCT_ACDETestStopFlag_B1;
    unsigned short speed,speed1;
    //unsigned char acc40MCLv,acc120MCLv;
    if (database->CTD_TrainSpeed_U16 > 700)
    {
        speed1 = database->TCU1CT_AcceleratiSpeed_U16;
        //acc120MCLv = database->CTD_Acc80MCLv_U8;

        //acc40MCLv = 0;
        speed = 0;
    }
    else
    {
        speed = database->TCU1CT_AcceleratiSpeed_U16;
        //acc40MCLv = database->CTD_Acc40MCLv_U8;

        speed1 = 0;
        //acc120MCLv = 0;
    }
    status<<QString::number(database->CTD_TrainSpeed_U16*0.1,'f',1)+"km/h"<<QString::number(database->CTD_Grade_U8)+"%"
                <<QString::number(speed*0.01,'f',2)+"m/s2"<<QString::number(database->CTD_Acc40MCLv_U8)+"%"
                <<QString::number(speed1*0.01,'f',2)+"m/s2"<<QString::number(database->CTD_Acc80MCLv_U8)+"%"
                <<QString::number(database->CTD_DeStartVelocity_U16*0.01,'f',1)+"km/h"<<QString::number(database->CTD_DeDistance_U16,'f',1)+"m"
                <<QString::number(-database->CTD_DeMCLv_U8)+"%"<<QString::number(database->CTD_DeceleratiOLINE_I16*0.01,'f',2)+"m/s2"
                ;
        setLabelStatus(lbls,status);
        status.clear();

        if(database->CTD_AcDeTestOLINE_B1)
        {
            ui->lbl_testStatus->setText("测试进行中");
        }
        else
        {
            ui->lbl_testStatus->setText("");
        }


        if(database->CTD_DeBrkMode_U8==1)
        {
            ui->lbl_brakeMode->setText("只有电制动");
        }
        else if(database->CTD_DeBrkMode_U8==2)
        {
            ui->lbl_brakeMode->setText("只有空气制动");
        }
        else if(database->CTD_DeBrkMode_U8==3)
        {
            ui->lbl_brakeMode->setText("电制动和空气制动都有");
        }
        else
        {
            ui->lbl_brakeMode->setText("");
        }

}


void AddSubtractTestPage::setLabelStatus(QList<QLabel *> lbls, QList<QString> status)
{
    for(int i=0;i<lbls.length();i++)
    {
        lbls.value(i)->setText(status.value(i));
    }
}
