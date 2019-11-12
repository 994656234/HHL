#include "maintaincecommunicationstatepage.h"
#include "ui_maintaincecommunicationstatepage.h"

#define ONLINE "border:2px solid rgb(0,0,50); color: rgb(0, 0, 0); background-color: green;"

MaintainceCommunicationStatePage::MaintainceCommunicationStatePage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceCommunicationStatePage)
{
    ui->setupUi(this);
    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }
}

MaintainceCommunicationStatePage::~MaintainceCommunicationStatePage()
{
    delete ui;
}

void MaintainceCommunicationStatePage::updatePage()
{

}

void MaintainceCommunicationStatePage::pushButtonPressedEvent()
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

void MaintainceCommunicationStatePage::setMVBstatus(QLabel *label, bool status)
{
    if(status)
    {
        label->setStyleSheet(ONLINE);
        label->setText("1");
    }else
    {
        label->setText("0");;
    }
}
