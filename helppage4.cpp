#include "helppage4.h"
#include "ui_helppage4.h"

HelpPage4::HelpPage4(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::HelpPage4)
{
    ui->setupUi(this);
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }
}

HelpPage4::~HelpPage4()
{
    delete ui;
}

void HelpPage4::NBpressEvent()
{
    QString BTNName=((QPushButton*)this->sender())->objectName();
    if(BTNName=="BTN1")
    {
        changePage(uVehicleTrainArea);
    }
    else if(BTNName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }
    else if(BTNName=="BTN2")
    {
        changePage(uVehicleHelpPage3);
    }
    else if(BTNName=="BTN3")
    {
        changePage(uVehicleHelpPage5);
    }
}
