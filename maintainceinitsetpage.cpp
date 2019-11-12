#include "maintainceinitsetpage.h"
#include "ui_maintainceinitsetpage.h"
#include "crrcfault.h"

MaintainceInitSetPage::MaintainceInitSetPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceInitSetPage)
{
    ui->setupUi(this);
    if(MainGetDefaultPara::getInt("/Position/HMI") == 1)
    {
        ui->backgroundlbl->setText("\n\n当前位置 ： TC1");
        this->ui->TC1HMIDBVlbl->setText("TC1 HMI DBVersion:"+CrrcFault::getCrrcFault()->getFaultTypeVersion());
        this->ui->TC2HMIDBVlbl->hide();

        ui->TC1Btn->setStyleSheet(PButtonDOWN);
    }else if(MainGetDefaultPara::getInt("/Position/HMI") == 2)
    {
        ui->backgroundlbl->setText("\n\n当前位置 ： TC2");
        this->ui->TC2HMIDBVlbl->setText("TC2 HMI DBVersion:"+CrrcFault::getCrrcFault()->getFaultTypeVersion());
        this->ui->TC1HMIDBVlbl->hide();

        ui->TC2Btn->setStyleSheet(PButtonDOWN);

    }else
    {
        ui->backgroundlbl->setText("配置文件错误");
    }
    this->ui->TC1HMIDBVlbl->setText("TC1 HMI DBVersion:"+CrrcFault::getCrrcFault()->getFaultTypeVersion());
}

MaintainceInitSetPage::~MaintainceInitSetPage()
{
    delete ui;
}

void MaintainceInitSetPage::on_BTN_back_pressed()
{
    changePage(uVehicleMaintainPage);
}

void MaintainceInitSetPage::on_TC1Btn_pressed()
{
    ui->TC1Btn->setStyleSheet(PButtonDOWN);
    ui->TC2Btn->setStyleSheet("font: 24px, \"微软雅黑\";color: white;background-color: rgb(0, 128, 128);border: 2px solid white;");
    MainGetDefaultPara::set("/Position/HMI",1);
    ui->backgroundlbl->setText("\n\n当前位置 ： TC1");
}

void MaintainceInitSetPage::on_TC2Btn_pressed()
{
    ui->TC2Btn->setStyleSheet(PButtonDOWN);
    ui->TC1Btn->setStyleSheet("font: 24px, \"微软雅黑\";color: white;background-color: rgb(0, 128, 128);border: 2px solid white;");
    MainGetDefaultPara::set("/Position/HMI",2);
    ui->backgroundlbl->setText("\n\n当前位置 ： TC2");
}

void MaintainceInitSetPage::on_HMIReboot_pressed()
{
    //logger()->info("人工重启！");
    system("reboot");
}
