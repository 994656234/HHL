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

    ui->BTN_TCU_2_2->hide();
    ui->BTN_TCU_3_2->hide();

    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }

    CutButtons<<ui->BTN_SIV_1<<ui->BTN_SIV_2<<ui->BTN_TCU_1<<ui->BTN_TCU_2_1
             <<ui->BTN_TCU_3_1<<ui->BTN_TCU_4;

    CutSignals<<&database->DiCT_ACU1Cutoff_B1<<&database->DiCT_ACU2Cutoff_B1<<&database->DiCT_MC1DynamicBrkCut_B1
             <<&database->DiCT_Mp1DynamicBrkCut_B1<<&database->DiCT_Mp2DynamicBrkCut_B1<<&database->DiCT_MC2DynamicBrkCut_B1;




    for(int i = 0;i<CutButtons.size();i++)
    {
        connect(CutButtons.at(i),SIGNAL(pressed()),this,SLOT(CutButtonsPressEvent()));
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
        *CutSignals.at(tmp_index) = false;
        ((QPushButton*)this->sender())->setStyleSheet(BTNRELEASE);
    }else
    {
        *CutSignals.at(tmp_index)= true;
        ((QPushButton*)this->sender())->setStyleSheet(BTNPRESS);
    }

}

void MaintainceResetExcisionPage::updatePage()
{

}
