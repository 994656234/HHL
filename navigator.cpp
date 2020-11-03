#include "navigator.h"
#include "ui_navigator.h"
#include "qdebug.h"
#define NButtonYELLOW  "font: 20px, \"微软雅黑\";color: black;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(255, 255, 127,255),stop:1 rgba(100,100,100,255));"
#define NButton "font: 20px \"微软雅黑\";color:black;transparent;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(170,170,170,255),stop:1 rgba(150,150,150,255));"
Navigator::Navigator(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::Navigator)
{
    ui->setupUi(this);

    buttons<<this->ui->BTNEvent<<this->ui->BTNSetting<<this->ui->BTNMaintaince<<this->ui->BTNByPass<<this->ui->BTNHelp
            <<this->ui->BTNBogieLampSubsystem<<this->ui->BTNSkipback<<this->ui->BTNSkipforward<<this->ui->BTNSpare2<<this->ui->BTNHome;

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
    }else if (BTNname == "BTNBogieLampSubsystem")
    {
        changePage(uVehicleMaintainceRunningGearSubsystemPage);
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

void Navigator::updatePage()
{
    if (database->RMICT_ByPass)
    {
        ui->BTNByPass->setStyleSheet(NButtonYELLOW);
    }
    else
    {
        ui->BTNByPass->setStyleSheet(NButton);
    }

}
