#include "bypasspage.h"
#include "ui_bypasspage.h"
#define BYPASSOFF "font: 20px  \"微软雅黑\";color: white;background-color: green;border:2px  solid black;border-radius:8px;"
#define BYPASSON "font: 20px  \"微软雅黑\";color: black;background-color: yellow;border:2px  solid black;border-radius:8px;"

ByPassPage::ByPassPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::ByPassPage)
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

ByPassPage::~ByPassPage()
{
    delete ui;
}

void ByPassPage::pushButtonPressedEvent()
{
    QString btnName=((QPushButton*)this->sender())->objectName();
    if(btnName=="BTN1")
    {
        changePage(uVehicleTrainArea);
    }
    else if(btnName == "BTN2")
    {
        changePage(uVehicleByPassPage2);
    }
    else if(btnName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }
}



void ByPassPage::updatePage()
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


    setStatus(ui->lbl1_1,database->RM1CT_DMBPS_B1);
    setStatus(ui->lbl1_2,database->RM4CT_DMBPS_B1);
    setStatus(ui->lbl2_1,database->RM1CT_LMRGBS_B1);
    setStatus(ui->lbl2_2,database->RM4CT_LMRGBS_B1);
    setStatus(ui->lbl3_1,database->RM1CT_EBBS_B1);
    setStatus(ui->lbl3_2,database->RM4CT_EBBS_B1);
    setStatus(ui->lbl4_1,database->RM1CT_ABRBS_B1);
    setStatus(ui->lbl4_2,database->RM4CT_ABRBS_B1);
    setStatus(ui->lbl5_1,database->RM1CT_RVBPS_B1);
    setStatus(ui->lbl5_2,database->RM4CT_RVBPS_B1);
    setStatus(ui->lbl6_1,database->RM1CT_PBRBPS_B1);
    setStatus(ui->lbl6_2,database->RM4CT_PBRBPS_B1);
    setStatus(ui->lbl7_1,database->RM1CT_PEBS_B1);
    setStatus(ui->lbl7_2,database->RM4CT_PEBS_B1);
    setStatus(ui->lbl8_1,database->RM1CT_DBPS_B1);
    setStatus(ui->lbl8_2,database->RM4CT_DBPS_B1);
    setStatus(ui->lbl9_1,database->RM1CT_ATPFS_B1);
    setStatus(ui->lbl9_2,database->RM4CT_ATPFS_B1);
    setStatus(ui->lbl10_1,database->RM1CT_ZVBS_B1);
    setStatus(ui->lbl10_2,database->RM4CT_ZVBS_B1);


}


void ByPassPage::setStatus(QLabel *lbl, bool status)
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
