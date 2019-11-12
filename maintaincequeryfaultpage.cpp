#include "maintaincequeryfaultpage.h"
#include "ui_maintaincequeryfaultpage.h"
#include "crrcfault.h"

#define BUTTONQUERYUP "font: 20px, \"微软雅黑\";color: white;background-color: rgb(0, 0, 50);border:2px groove  rgb(100, 100, 200);border-radius:10px;padding:2px 4px"
#define BUTTONQUERYDISABLE  "font: 20px, \"微软雅黑\";color: white;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 lightgray,stop:1 rgba(0,0,50,255));border:2px groove  rgb(100, 100, 200);border-radius:10px;padding:2px 4px ;"


MaintainceQueryFaultPage::MaintainceQueryFaultPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceQueryFaultPage)
{
    ui->setupUi(this);

    QList <QPushButton* >TrainBtnList;

    TrainBtnList<<this->ui->BTNTC1<<this->ui->BTNMP1<<this->ui->BTNM1<<this->ui->BTNM2<<this->ui->BTNMP2<<this->ui->BTNTC2<<this->ui->BTNTRAIN;
    foreach (QPushButton *button,TrainBtnList)
    {
        connect(button, SIGNAL(clicked()), this, SLOT(TrainSelectEvent()));
    }

    QList <QPushButton* >SysBtnList;
    SysBtnList<<this->ui->BTNTCMS<<this->ui->BTNBCU<<this->ui->BTNDCU
            <<this->ui->BTNACU<<this->ui->BTNEDCU<<this->ui->BTNPIS
            <<this->ui->BTNREC<<this->ui->BTNHVAC;
    foreach (QPushButton *button, SysBtnList)
    {
        connect(button, SIGNAL(clicked()), this, SLOT(SystemSelectEvent()));
    }

    QList <QPushButton* >NumBtnList;
    NumBtnList<<this->ui->BTNNum1<<this->ui->BTNNum2<<this->ui->BTNNum3<<this->ui->BTNNum4<<this->ui->BTNNum5<<this->ui->BTNNum6<<this->ui->BTNNum7
              <<this->ui->BTNNum8<<this->ui->BTNNum9<<this->ui->BTNNum0<<this->ui->BTNNumC<<this->ui->BTNQUERY;
    foreach (QPushButton *button,NumBtnList)
    {
        connect(button, SIGNAL(clicked()), this, SLOT(NumPressEvent()));
    }

    this->ui->LBL_Alarm->hide();
    m_TrainSelect = "";
    m_SysSelect = "";
    m_CodeInput = "";
}

MaintainceQueryFaultPage::~MaintainceQueryFaultPage()
{
    delete ui;
}

void MaintainceQueryFaultPage::TrainSelectEvent()
{
    m_TrainSelect = ((QPushButton *)this->sender())->text();
    CrrcFault::getCrrcFault()->getQueryFaultOfEachVehicle(m_TrainSelect);
    changePage(uMaintainceShowQueryFaultPage);

}
void MaintainceQueryFaultPage::SystemSelectEvent()
{
    m_SysSelect = ((QPushButton *)this->sender())->text();
    CrrcFault::getCrrcFault()->getQueryFaultOfEachSystem(m_SysSelect);
    changePage(uMaintainceShowQueryFaultPage);
}

void MaintainceQueryFaultPage::NumPressEvent()
{
    this->ui->LBL_Alarm->hide();
    if(((QPushButton *)this->sender())->text() == "查询")
    {
        if(CrrcFault::getCrrcFault()->getQueryFaultOfEachCode(m_CodeInput))
        {
            changePage(uMaintainceShowQueryFaultPage);
        }else
        {
            this->ui->LBL_Alarm->show();
        }
        m_CodeInput = "";
    }
    else if(((QPushButton *)this->sender())->text() == "C")
    {
        m_CodeInput = "";
    }else
    {
        m_CodeInput += ((QPushButton *)this->sender())->text();
    }
}
void MaintainceQueryFaultPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}
void MaintainceQueryFaultPage::updatePage()
{

    this->ui->LBLCodeInput->setText(m_CodeInput);

    if(CrrcFault::getCrrcFault()->isRunning())
    {
        setBtnsStyle(this->ui->BTNTC1,CrrcFault::getCrrcFault()->getFaultCntOfEachVehicle("TC1"));
        setBtnsStyle(this->ui->BTNMP1,CrrcFault::getCrrcFault()->getFaultCntOfEachVehicle("MP1"));
        setBtnsStyle(this->ui->BTNM1,CrrcFault::getCrrcFault()->getFaultCntOfEachVehicle("M1"));
        setBtnsStyle(this->ui->BTNM2,CrrcFault::getCrrcFault()->getFaultCntOfEachVehicle("M2"));
        setBtnsStyle(this->ui->BTNMP2,CrrcFault::getCrrcFault()->getFaultCntOfEachVehicle("MP2"));
        setBtnsStyle(this->ui->BTNTC2,CrrcFault::getCrrcFault()->getFaultCntOfEachVehicle("TC2"));

        setBtnsStyle(this->ui->BTNTCMS,CrrcFault::getCrrcFault()->getFaultCntOfEachSystem("TCMS"));
        setBtnsStyle(this->ui->BTNBCU,CrrcFault::getCrrcFault()->getFaultCntOfEachSystem("BCU"));
        setBtnsStyle(this->ui->BTNDCU,CrrcFault::getCrrcFault()->getFaultCntOfEachSystem("DCU"));
        setBtnsStyle(this->ui->BTNACU,CrrcFault::getCrrcFault()->getFaultCntOfEachSystem("ACU"));
        setBtnsStyle(this->ui->BTNEDCU,CrrcFault::getCrrcFault()->getFaultCntOfEachSystem("EDCU"));
        setBtnsStyle(this->ui->BTNPIS,CrrcFault::getCrrcFault()->getFaultCntOfEachSystem("PIS"));
        setBtnsStyle(this->ui->BTNHVAC,CrrcFault::getCrrcFault()->getFaultCntOfEachSystem("HVAC"));
        setBtnsStyle(this->ui->BTNREC,CrrcFault::getCrrcFault()->getFaultCntOfEachSystem("REC"));

    }
}
void MaintainceQueryFaultPage::setBtnsStyle(QPushButton* btn,int cnt)
{
    if(cnt>0)
    {
        btn->setStyleSheet(BUTTONQUERYUP);
        btn->setDisabled(false);
    }else
    {
        btn->setStyleSheet(BUTTONQUERYDISABLE);
        btn->setDisabled(true);

    }
}

void MaintainceQueryFaultPage::on_returnBtn_pressed()
{
    changePage(uMaintainceHistoryFaultPage);
}
