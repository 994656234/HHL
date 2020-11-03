#include "bypasspage2.h"
#include "ui_bypasspage2.h"
#define BYPASSOFF "font: 20px  \"微软雅黑\";color: white;background-color: green;border:2px  solid black;border-radius:8px;"
#define BYPASSON "font: 20px  \"微软雅黑\";color: black;background-color: yellow;border:2px  solid black;border-radius:8px;"

ByPassPage2::ByPassPage2(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::ByPassPage2)
{
    ui->setupUi(this);
    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();
}

ByPassPage2::~ByPassPage2()
{
    delete ui;
}

void ByPassPage2::pushButtonPressedEvent()
{
    QString btnName=((QPushButton*)this->sender())->objectName();
    if(btnName=="BTN1")
    {
        changePage(uVehicleByPassPage);
    }
    else if(btnName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }
}

void ByPassPage2::updatePage()
{

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


    setStatus(ui->lbl1_1,database->RM1CT_DRBYS_B1);
    setStatus(ui->lbl1_2,database->RM4CT_DRBYS_B1);
    setStatus(ui->lbl2_1,database->RM1CT_DBYS_B1);
    setStatus(ui->lbl2_2,database->RM4CT_DBYS_B1);
    setGeLiStatus(ui->lbl3_1,database->RM2CT_BIS_B1);
    setGeLiStatus(ui->lbl3_2,database->RM5CT_BIS_B1);
    setGeLiStatus(ui->lbl4_1,database->RM2CT_PBIV_B1);
    setGeLiStatus(ui->lbl4_2,database->RM5CT_PBIV_B1);
    setGeLiStatus(ui->lbl5_1,!database->RM2CT_BBIV1_B1);
    setGeLiStatus(ui->lbl5_2,!database->RM5CT_BBIV1_B1);
    setGeLiStatus(ui->lbl6_1,!database->RM2CT_BBIV2_B1);
    setGeLiStatus(ui->lbl6_2,!database->RM5CT_BBIV2_B1);
    setGeLiStatus(ui->lbl7_1,database->RM3CT_PBIV_B1);
    setGeLiStatus(ui->lbl7_2,database->RM6CT_PBIV_B1);
    setGeLiStatus(ui->lbl8_1,!database->RM3CT_BBIV1_B1);
    setGeLiStatus(ui->lbl8_2,!database->RM6CT_BBIV1_B1);
    setGeLiStatus(ui->lbl9_1,!database->RM3CT_BBIV2_B1);
    setGeLiStatus(ui->lbl9_2,!database->RM6CT_BBIV2_B1);
    setGeLiStatus(ui->lbl10_1,database->RM2CT_CBBIV_B1);
    setGeLiStatus(ui->lbl10_2,database->RM5CT_CBBIV_B1);

}


void ByPassPage2::setStatus(QLabel *lbl, bool status)
{
    if(status)
    {
        lbl->setStyleSheet(BYPASSON);
        lbl->setText("旁路");
    }
    else
    {
        lbl->setStyleSheet(BYPASSOFF);
        lbl->setText("未旁路");
    }
}

void ByPassPage2::setGeLiStatus(QLabel *lbl, bool status)
{
    if(status)
    {
        lbl->setStyleSheet(BYPASSON);
        lbl->setText("隔离");
    }
    else
    {
        lbl->setStyleSheet(BYPASSOFF);
        lbl->setText("未隔离");
    }
}
