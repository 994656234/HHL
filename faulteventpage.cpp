#include "faulteventpage.h"
#include "ui_faulteventpage.h"

#define FAULTBUTTONUP "background-color: rgb(0, 0, 50);border:0px;"
#define FAULTBUTTONDOWN "background-color: rgb(255, 0, 0);border:0px;"
#define LABELPRESS "color: rgb(255, 255, 255);background-color: rgb(255, 0, 0);font:14px \"微软雅黑\";"
#define LABELRELEASE "color: rgb(255, 255, 255);background-color: rgb(0, 0, 50);font:14px \"微软雅黑\";"

FaultEventPage::FaultEventPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::FaultEventPage)
{
    ui->setupUi(this);
    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }


    faultButtons<<ui->BTN_1_bg<<ui->BTN_2_bg<<ui->BTN_3_bg<<ui->BTN_4_bg<<ui->BTN_5_bg<<ui->BTN_6_bg<<ui->BTN_7_bg<<ui->BTN_8_bg
            <<ui->BTN_9_bg;
    foreach(QPushButton* button,faultButtons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(faultPushButtonPressedEvent()));
    }

    this->labelList1<<ui->lbl_1_confirm<<ui->lbl_1_faultCode<<ui->lbl_1_faultDevice<<ui->lbl_1_faultLevel<<ui->lbl_1_faultName
            <<ui->lbl_1_startTime;
    this->labelList2<<ui->lbl_2_confirm<<ui->lbl_2_faultCode<<ui->lbl_2_faultDevice<<ui->lbl_2_faultLevel<<ui->lbl_2_faultName
            <<ui->lbl_2_startTime;
    this->labelList3<<ui->lbl_3_confirm<<ui->lbl_3_faultCode<<ui->lbl_3_faultDevice<<ui->lbl_3_faultLevel<<ui->lbl_3_faultName
            <<ui->lbl_3_startTime;
    this->labelList4<<ui->lbl_4_confirm<<ui->lbl_4_faultCode<<ui->lbl_4_faultDevice<<ui->lbl_4_faultLevel<<ui->lbl_4_faultName
            <<ui->lbl_4_startTime;
    this->labelList5<<ui->lbl_5_confirm<<ui->lbl_5_faultCode<<ui->lbl_5_faultDevice<<ui->lbl_5_faultLevel<<ui->lbl_5_faultName
            <<ui->lbl_5_startTime;
    this->labelList6<<ui->lbl_6_confirm<<ui->lbl_6_faultCode<<ui->lbl_6_faultDevice<<ui->lbl_6_faultLevel<<ui->lbl_6_faultName
            <<ui->lbl_6_startTime;
    this->labelList7<<ui->lbl_7_confirm<<ui->lbl_7_faultCode<<ui->lbl_7_faultDevice<<ui->lbl_7_faultLevel<<ui->lbl_7_faultName
            <<ui->lbl_7_startTime;
    this->labelList8<<ui->lbl_8_confirm<<ui->lbl_8_faultCode<<ui->lbl_8_faultDevice<<ui->lbl_8_faultLevel<<ui->lbl_8_faultName
            <<ui->lbl_8_startTime;
    this->labelList9<<ui->lbl_9_confirm<<ui->lbl_9_faultCode<<ui->lbl_9_faultDevice<<ui->lbl_9_faultLevel<<ui->lbl_9_faultName
            <<ui->lbl_9_startTime;
    this->labelbg<<ui->lbl_bg_1<<ui->lbl_bg_2<<ui->lbl_bg_3<<ui->lbl_bg_4<<ui->lbl_bg_5<<ui->lbl_bg_6<<ui->lbl_bg_7
            <<ui->lbl_bg_8<<ui->lbl_bg_9;
    foreach(QPushButton* button,faultButtons)
    {
        button->raise();
    }

}

FaultEventPage::~FaultEventPage()
{
    delete ui;
}



void FaultEventPage::pushButtonPressedEvent()
{
    QString btnName=((QPushButton*)this->sender())->objectName();
    if(btnName=="BTN1")
    {
        changePage(uVehicleTrainArea);
    }
    else if(btnName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }
}

void FaultEventPage::faultPushButtonPressedEvent()
{
    foreach(QPushButton* button,faultButtons)
    {
        button->setStyleSheet(FAULTBUTTONUP);
    }
    QString btnName=((QPushButton*)this->sender())->objectName();
    if(btnName=="BTN_1_bg")
    {
        refreshAll();
        ui->lbl_bg_1->setStyleSheet(LABELPRESS);
        foreach(QLabel* label,labelList1)
        {
            label->setStyleSheet(LABELPRESS);
        }
    }
    else if(btnName=="BTN_2_bg")
    {
        refreshAll();
        ui->lbl_bg_2->setStyleSheet(LABELPRESS);
        foreach(QLabel*label,labelList2)
        {
            label->setStyleSheet(LABELPRESS);
        }
    }
}

void FaultEventPage::refreshAll()
{
    foreach(QLabel* label,labelList1)
    {
        label->setStyleSheet(LABELRELEASE);
    }

    foreach(QLabel* label,labelList2)
    {
        label->setStyleSheet(LABELRELEASE);
    }

    foreach(QLabel* label,labelList3)
    {
        label->setStyleSheet(LABELRELEASE);
    }

    foreach(QLabel* label,labelList4)
    {
        label->setStyleSheet(LABELRELEASE);
    }

    foreach(QLabel* label,labelList5)
    {
        label->setStyleSheet(LABELRELEASE);
    }

    foreach(QLabel* label,labelList6)
    {
        label->setStyleSheet(LABELRELEASE);
    }

    foreach(QLabel* label,labelList7)
    {
        label->setStyleSheet(LABELRELEASE);
    }

    foreach(QLabel* label,labelList8)
    {
        label->setStyleSheet(LABELRELEASE);
    }

    foreach(QLabel* label,labelList9)
    {
        label->setStyleSheet(LABELRELEASE);
    }

    foreach(QLabel* label,labelbg)
    {
        label->setStyleSheet(LABELRELEASE);
    }
}
