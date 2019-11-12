#include "doorversioncontrol.h"
#include "ui_doorversioncontrol.h"

DoorVersionControl::DoorVersionControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoorVersionControl)
{
    ui->setupUi(this);
}

DoorVersionControl::~DoorVersionControl()
{
    delete ui;
}

void DoorVersionControl::updateStatus(QList<QString> &status)
{
    QList<QLabel*> door;
    door<<ui->TC1_1<<ui->TC1_2<<ui->TC1_3<<ui->TC1_4<<ui->TC1_5<<ui->TC1_6
        <<ui->MP1_1<<ui->MP1_2<<ui->MP1_3<<ui->MP1_4<<ui->MP1_5<<ui->MP1_6
        <<ui->MP2_1<<ui->MP2_2<<ui->MP2_3<<ui->MP2_4<<ui->MP2_5<<ui->MP2_6
        <<ui->TC2_1<<ui->TC2_2<<ui->TC2_3<<ui->TC2_4<<ui->TC2_5<<ui->TC2_6;

    for(int i=0;i<status.length();i++)
    {
        door.at(i)->setText(status.at(i));
    }
}
