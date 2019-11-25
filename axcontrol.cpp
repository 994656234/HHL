#include "axcontrol.h"
#include "ui_axcontrol.h"
#include "qdebug.h"

#define AX_LENGTH (8)

AXControl::AXControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AXControl)
{
    ui->setupUi(this);
}

AXControl::~AXControl()
{
    delete ui;
}


void AXControl::initialName(QList<QString> &names)
{
    if (names.length() != AX_LENGTH)
    {
        qDebug()<< "the length ax not equal to" << AX_LENGTH;

        return;
    }

    QList<QLabel *> labels;

    labels << ui->CH1Namelbl << ui->CH2Namelbl << ui->CH3Namelbl << ui->CH4Namelbl
           << ui->CH5Namelbl << ui->CH6Namelbl << ui->CH7Namelbl << ui->CH8Namelbl;

    for (int i = 0; i < names.length(); i ++)
    {
        labels.at(i)->setText(names.at(i));
    }
}

void AXControl::updateAx(QList<QString> &state)
{
    if (state.length() != (AX_LENGTH ) *2)
    {
        qDebug() <<"the length ax"<< state.size()<< "not equal to" << (AX_LENGTH ) * 2;

        return;
    }

    QList<QLabel *> labels;

    labels<<ui->AIN1_Status1<<ui->AIN2_Status1<<ui->AIN3_Status1<<ui->AIN4_Status1<<ui->AIN5_Status1<<ui->AIN6_Status1<<ui->AIN7_Status1<<ui->AIN8_Status1
            <<ui->AIN1_Status2<<ui->AIN2_Status2<<ui->AIN3_Status2<<ui->AIN4_Status2<<ui->AIN5_Status2<<ui->AIN6_Status2<<ui->AIN7_Status2<<ui->AIN8_Status2;

    for (int i = 0; i < state.length(); i ++)
    {
        labels.at(i)->setText(state.at(i));
    }


}
