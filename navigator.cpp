#include "navigator.h"
#include "ui_navigator.h"
#include "qdebug.h"

Navigator::Navigator(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::Navigator)
{
    ui->setupUi(this);


    buttons<<this->ui->BTNEvent<<this->ui->BTNSetting<<this->ui->BTNMaintaince<<this->ui->BTNByPass<<this->ui->BTNHelp
            <<this->ui->BTNLeaveB<<this->ui->BTNSkipback<<this->ui->BTNSkipforward<<this->ui->BTNSpare2<<this->ui->BTNHome;

    foreach (QPushButton *button, buttons)
    {
        connect(button, SIGNAL(pressed()), this, SLOT(NBpressEvent()));
    }
}

Navigator::~Navigator()
{
    delete ui;
}

void Navigator::NBpressEvent()
{
    QString BTNname = ((QPushButton *)this->sender())->objectName();

    if(BTNname == "BTNEvent")
    {
        changePage(uMaintainceCurrentFaultPage);
    }else if(BTNname == "BTNSetting")
    {
        changePage(uVehicleSetPage);
    }else if(BTNname == "BTNMaintaince")
    {
        changePage(uVehiclePasswordPage);

    }else if(BTNname == "BTNByPass")
    {
        changePage(uVehicleByPassPage);
    }else if(BTNname == "BTNHelp")
    {
        changePage(uVehicleHelpPage);
    }else if(BTNname == "BTNSkipback")
    {

    }else if(BTNname == "BTNSkipforward")
    {


    }else if(BTNname == "BTNHome")
    {
        changePage(uVehicleTrainArea);
    }else
    {

    }
    this->ui->BTNHome->setStyleSheet("border-image: url(:/images/image/Home.png);");
}

void Navigator::refreshAllButtons()
{
    foreach(QPushButton* button,buttons)
    {
        button->setStyleSheet(NButtonUP);
    }
}
