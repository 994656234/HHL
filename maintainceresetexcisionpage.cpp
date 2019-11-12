#include "maintainceresetexcisionpage.h"
#include "ui_maintainceresetexcisionpage.h"
#include "qdebug.h"

#define  BTNPRESS "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(187,188,247) , stop:1 rgb(19,20,87));border:0px solid;color: rgb(255, 255, 255);font:20px \"微软雅黑\";border-radius:10px;"
#define  BTNRELEASE  "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:20px \"微软雅黑\";border-radius:10px;"
#define  BTNOUTABLE "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:20px \"微软雅黑\";border-radius:10px;background-color:rgb(192,192,192)"

MaintainceResetExcisionPage::MaintainceResetExcisionPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceResetExcisionPage)
{
    ui->setupUi(this); 

    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }

    CutButtons<<ui->BTN_DCU_Ele_Excision_M1<<ui->BTN_DCU_Ele_Excision_M2<<ui->BTN_DCU_Ele_Excision_Mp1<<ui->BTN_DCU_Ele_Excision_Mp2
            <<ui->BTN_SIV_Excision_M1<<ui->BTN_SIV_Excision_M2<<ui->BTN_SIV_Excision_TC1<<ui->BTN_SIV_Excision_TC2;

    ResetButtons<<ui->BTN_DCU_Reset_M1<<ui->BTN_DCU_Reset_M2<<ui->BTN_DCU_Reset_Mp1<<ui->BTN_DCU_Reset_Mp2
            <<ui->BTN_SIV_Reset_M1<<ui->BTN_SIV_Reset_M2<<ui->BTN_SIV_Reset_TC1<<ui->BTN_SIV_Reset_TC2;


   // CutSignals<<&database->HMiCT_M1DynamicBrkCut_B1<<&database->HMiCT_M2DynamicBrkCut_B1<<&database->HMiCT_Mp1DynamicBrkCut_B1<<&database->HMiCT_Mp2DynamicBrkCut_B1
    //        <<&database->HMiCT_ACU2Cutoff_B1<<&database->HMiCT_ACU3Cutoff_B1<<&database->HMiCT_ACU1Cutoff_B1<<&database->HMiCT_ACU4Cutoff_B1;

   // ResetSignals<<&database->HMiCT_M1DCUFaultReset_B1<<&database->HMiCT_M2DCUFaultReset_B1<<&database->HMiCT_Mp1DCUFaultReset_B1<<&database->HMiCT_Mp2DCUFaultReset_B1
   //         <<&database->HMiCT_ACU2Reset_B1<<&database->HMiCT_ACU3Reset_B1<<&database->HMiCT_ACU1Reset_B1<<&database->HMiCT_ACU4Reset_B1;



    for(int i = 0;i<CutButtons.size();i++)
    {
        connect(CutButtons.at(i),SIGNAL(pressed()),this,SLOT(CutButtonsPressEvent()));
    }
    for(int i = 0;i<ResetButtons.size();i++)
    {
        ResetButtons.at(i)->hide();
        connect(ResetButtons.at(i),SIGNAL(pressed()),this,SLOT(RstButtonsPressEvent()));
    }


    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();

}

MaintainceResetExcisionPage::~MaintainceResetExcisionPage()
{
    delete ui;
}

void MaintainceResetExcisionPage::pushButtonPressedEvent()
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


void MaintainceResetExcisionPage::CutButtonsPressEvent()
{

    int tmp_index = ((QPushButton*)this->sender())->whatsThis().toInt()-1;
    if(*CutSignals[tmp_index]==true)
    {

        //*CutSignals[tmp_index] = false;
        ((QPushButton*)this->sender())->setStyleSheet(BTNRELEASE);
        ResetButtons[tmp_index]->setStyleSheet(BTNRELEASE);
        ResetButtons[tmp_index]->setDisabled(false);
    }else
    {

        //*CutSignals[tmp_index] = true;
        ResetButtons[tmp_index]->setStyleSheet(BTNOUTABLE);
        ResetButtons[tmp_index]->setDisabled(true);
        ((QPushButton*)this->sender())->setStyleSheet(BTNPRESS);
    }

}

void MaintainceResetExcisionPage::RstButtonsPressEvent()
{
    int tmp_index = ((QPushButton*)this->sender())->whatsThis().toInt()-1;
    //*ResetSignals[tmp_index] = true;
    timer2s[tmp_index] = this->startTimer(2000);
    ((QPushButton*)this->sender())->setStyleSheet(BTNPRESS);

}

void MaintainceResetExcisionPage::timerEvent(QTimerEvent *e)
{
    for(int i = 0; i < 8;i++)
    {
        if(e->timerId() == timer2s[i])
        {
            killTimer(timer2s[i]);
            ResetButtons[i]->setStyleSheet(BTNRELEASE);
            //*ResetSignals[i] = false;
        }
    }
}


void MaintainceResetExcisionPage::updatePage()
{

}
