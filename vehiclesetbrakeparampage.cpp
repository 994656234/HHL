#include "vehiclesetbrakeparampage.h"
#include "ui_vehiclesetbrakeparampage.h"

VehicleSetBrakeParamPage::VehicleSetBrakeParamPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleSetBrakeParamPage)
{
    ui->setupUi(this);
    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }
}

VehicleSetBrakeParamPage::~VehicleSetBrakeParamPage()
{
    delete ui;
}


void VehicleSetBrakeParamPage::pushButtonPressedEvent()
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
