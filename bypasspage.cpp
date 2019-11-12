#include "bypasspage.h"
#include "ui_bypasspage.h"
#define BYPASSOFF "font: 20px  \"微软雅黑\";color: white;background-color: green;border:2px  solid black;border-radius:8px;"
#define BYPASSON "font: 20px  \"微软雅黑\";color: black;background-color: yellow;border:2px  solid black;border-radius:8px;"

ByPassPage::ByPassPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::ByPassPage)
{
    ui->setupUi(this);
    QList<QPushButton*> buttons;
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9<<ui->BTNHome;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }
    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();
    ui->lbl_cab1_direction->hide();
    ui->lbl_cab2_direction->hide();
}

ByPassPage::~ByPassPage()
{
    delete ui;
}

void ByPassPage::pushButtonPressedEvent()
{
    QString btnName=((QPushButton*)this->sender())->objectName();
    if(btnName=="BTN1")
    {
        changePage(uVehicleTrainArea);
    }
    else if(btnName=="BTNHome")
    {
        changePage(uVehicleTrainArea);
    }
}



void ByPassPage::updatePage()
{


}


void ByPassPage::setStatus(QLabel *lbl, bool status)
{
    if(status)
    {
        lbl->setStyleSheet(BYPASSON);
        lbl->setText("旁路");
    }
    else
    {
        lbl->setStyleSheet(BYPASSOFF);
        lbl->setText("未旁路");
    }
}
