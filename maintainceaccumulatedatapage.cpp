#include "maintainceaccumulatedatapage.h"
#include "ui_maintainceaccumulatedatapage.h"

MaintainceAccumulateDataPage::MaintainceAccumulateDataPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceAccumulateDataPage)
{
    ui->setupUi(this);
    ui->lbl_8->hide();
    ui->lbl_repaircomsuption_T->hide();
    ui->lbl_repaircomsuption->hide();
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }
}

MaintainceAccumulateDataPage::~MaintainceAccumulateDataPage()
{
    delete ui;
}


void MaintainceAccumulateDataPage::NBpressEvent()
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

void MaintainceAccumulateDataPage::updatePage()
{

    signalTimeDatas<<database->EiCT_TotalDistanceYear_U8<<database->EiCT_TotalDistanceMonth_U8<<database->EiCT_TotalDistanceDay_U8;
    SetTime(ui->lbl_ACCMile_T,signalTimeDatas);
    signalTimeDatas.clear();

    signalTimeDatas<<database->EiCT_TractionECYear_U8<<database->EiCT_TractionECMonth_U8<<database->EiCT_TractionECDay_U8;
    SetTime(ui->lbl_TCUcomsuption_T,signalTimeDatas);
    signalTimeDatas.clear();

    signalTimeDatas<<database->EiCT_AxPowerECYear_U8<<database->EiCT_AxPowerECMonth_U8<<database->EiCT_AxPowerECDay_U8;
    SetTime(ui->lbl_ACUcomsuption_T,signalTimeDatas);
    signalTimeDatas.clear();

    signalTimeDatas<<database->EiCT_ReEngyYear_U8<<database->EiCT_ReEngyMonth_U8<<database->EiCT_ReEngyDay_U8;
    SetTime(ui->lbl_recomsuption_T,signalTimeDatas);
    signalTimeDatas.clear();

    signalTimeDatas<<database->EiCT_ServiceDistanceYear_U8<<database->EiCT_ServiceDistanceMonth_U8<<database->EiCT_ServiceDistanceDay_U8;
    SetTime(ui->lbl_repaircomsuption_T,signalTimeDatas);
    signalTimeDatas.clear();

    signalTimeDatas<<database->EiCT_AP1ECYear_U8<<database->EiCT_AP1ECMonth_U8<<database->EiCT_AP1ECDay_U8;
    SetTime(ui->lbl_ACP1runtime_T,signalTimeDatas);
    signalTimeDatas.clear();

    signalTimeDatas<<database->EiCT_AP2ECYear_U8<<database->EiCT_AP2ECMonth_U8<<database->EiCT_AP2ECDay_U8;
    SetTime(ui->lbl_ACP2runtime_T,signalTimeDatas);
    signalTimeDatas.clear();

    signalTimeDatas<<database->EiCT_TCMSTotalTimeYear_U8<<database->EiCT_TCMSTotalTimeMonth_U8<<database->EiCT_TCMSTotalTimeDay_U8;
    SetTime(ui->lbl_TCMSTime_T,signalTimeDatas);
    signalTimeDatas.clear();


    SetStatus1(ui->lbl_ACCMile,database->EiCT_RunningKilometers_U32);
    SetStatus3(ui->lbl_TCUcomsuption,database->EiCT_TractionEngyConsumption_U32);
    SetStatus3(ui->lbl_ACUcomsuption,database->EiCT_AxPowerEngyConsumption_U32);
    SetStatus3(ui->lbl_recomsuption,database->EiCT_ReEngy_U32);
    SetStatus1(ui->lbl_repaircomsuption,database->EiCT_ServiceDistance_U32);
    SetStatus2(ui->lbl_ACP1runtime,database->EiCT_AP1RunningTime_U32);
    SetStatus2(ui->lbl_ACP2runtime,database->EiCT_AP2RunningTime_U32);
    SetStatus2(ui->lbl_TCMSTime,database->EiCT_TCMSTotalTime_U32);


}


void MaintainceAccumulateDataPage::SetTime(QLabel *lbl, QList<unsigned char> status)
{
    lbl->setText(QString::number(status.at(0)+2000)+"/"+QString::number(status.at(1))+"/"+QString::number(status.at(2)));
}

void MaintainceAccumulateDataPage::SetStatus1(QLabel *lbl, unsigned int status)
{
    lbl->setText(QString::number(status)+"km");
}

void MaintainceAccumulateDataPage::SetStatus2(QLabel *lbl, unsigned int status)
{
    lbl->setText(QString::number(status)+"min");
}

void MaintainceAccumulateDataPage::SetStatus3(QLabel *lbl, unsigned int status)
{
    lbl->setText(QString::number(status)+"Kwh");
}

//void MaintainceAccumulateDataPage::SetStatus2(QLabel *lbl, QString status)
//{
//    lbl->setText(status);
//}
