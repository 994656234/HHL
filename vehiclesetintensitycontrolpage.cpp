#include "vehiclesetintensitycontrolpage.h"
#include "ui_vehiclesetintensitycontrolpage.h"
#include "h8.h"

#define BRIGHTNESSSCALE  255

#define BUTTONPRESS "border-top:0px solid rgb(19,20,87);color: rgb(255, 255, 255);background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));font:16px \"微软雅黑\";"
#define BUTTONRELEASE "border-top:3px solid rgb(19,20,87);color: rgb(255, 255, 255);border-bottom:3px solid rgb(187,188,247);border-left:3px solid qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));border-right:3px solid qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));font:16px \"微软雅黑\";"

VehicleSetIntensityControlPage::VehicleSetIntensityControlPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleSetIntensityControlPage)
{
    ui->setupUi(this);
    m_BrightValuefactor = 0.8;
    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome
            <<ui->BTN_mode_auto<<ui->BTN_mode_hand<<ui->BTN_set_add<<ui->BTN_set_sub;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }
    ui->BTN_mode_auto->setStyleSheet(BUTTONPRESS);
    ui->BTN_set_add->setEnabled(false);
    ui->BTN_set_sub->setEnabled(false);
}

VehicleSetIntensityControlPage::~VehicleSetIntensityControlPage()
{
    delete ui;
}

void VehicleSetIntensityControlPage::pushButtonPressedEvent()
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
    else if(btnName=="BTN_mode_auto")
    {
        ui->BTN_mode_auto->setStyleSheet(BUTTONPRESS);
        ui->BTN_mode_hand->setStyleSheet(BUTTONRELEASE);
        ui->BTN_set_add->setEnabled(false);
        ui->BTN_set_sub->setEnabled(false);

        H8::getH8()->setBrightness(0);
    }
    else if(btnName=="BTN_mode_hand")
    {
        ui->BTN_mode_hand->setStyleSheet(BUTTONPRESS);
        ui->BTN_mode_auto->setStyleSheet(BUTTONRELEASE);
        ui->BTN_set_add->setEnabled(true);
        ui->BTN_set_sub->setEnabled(true);
        H8::getH8()->setBrightness(m_BrightValuefactor);
    }
    else if(btnName=="BTN_set_sub")
    {
        if(m_BrightValuefactor > 0.1)
        {
            m_BrightValuefactor -= 0.1;
        }
        H8::getH8()->setBrightness((int)BRIGHTNESSSCALE*m_BrightValuefactor);
        this->ui->lbl_set_value->setText(QString::number(m_BrightValuefactor,'f',1));
    }
    else if(btnName=="BTN_set_add")
    {
        if(m_BrightValuefactor < 1)
        {
            m_BrightValuefactor += 0.1;
        }
        H8::getH8()->setBrightness((int)BRIGHTNESSSCALE*m_BrightValuefactor);
        this->ui->lbl_set_value->setText(QString::number(m_BrightValuefactor,'f',1));
    }
}
