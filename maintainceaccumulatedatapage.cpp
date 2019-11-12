#include "maintainceaccumulatedatapage.h"
#include "ui_maintainceaccumulatedatapage.h"

MaintainceAccumulateDataPage::MaintainceAccumulateDataPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceAccumulateDataPage)
{
    ui->setupUi(this);
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


}


void MaintainceAccumulateDataPage::SetTime(QLabel *lbl, QList<unsigned char> status)
{
    lbl->setText(QString::number(status.at(0)+2000)+"/"+QString::number(status.at(1))+"/"+QString::number(status.at(2)));
}

void MaintainceAccumulateDataPage::SetStatus1(QLabel *lbl, unsigned char status)
{
    lbl->setText(QString::number(status));
}

void MaintainceAccumulateDataPage::SetStatus2(QLabel *lbl, QString status)
{
    lbl->setText(status);
}
