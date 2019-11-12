#include "vehiclemthistoryfaultpage.h"
#include "ui_vehiclemthistoryfaultpage.h"

VehicleMTHistoryFaultPage::VehicleMTHistoryFaultPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleMTHistoryFaultPage)
{
    ui->setupUi(this);
    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }
}

VehicleMTHistoryFaultPage::~VehicleMTHistoryFaultPage()
{
    delete ui;
}

void VehicleMTHistoryFaultPage::pushButtonPressedEvent()
{
    QString btnName=((QPushButton*)this->sender())->objectName();
    if(btnName=="BTN1")
    {
        changePage(uVehicleMaintainPage);
    }
    else if(btnName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }
}
