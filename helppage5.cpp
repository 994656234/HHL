#include "helppage5.h"
#include "ui_helppage5.h"

HelpPage5::HelpPage5(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::HelpPage5)
{
    ui->setupUi(this);
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(NBpressEvent()));
    }
}

HelpPage5::~HelpPage5()
{
    delete ui;
}

void HelpPage5::NBpressEvent()
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
        changePage(uVehicleHelpPage4);
    }
}
