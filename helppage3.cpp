#include "helppage3.h"
#include "ui_helppage3.h"

HelpPage3::HelpPage3(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::HelpPage3)
{
    ui->setupUi(this);
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }
}

HelpPage3::~HelpPage3()
{
    delete ui;
}

void HelpPage3::NBpressEvent()
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
        changePage(uVehicleHelpPage2);
    }
    else if(BTNName=="BTN3")
    {
        changePage(uVehicleHelpPage4);
    }
}
