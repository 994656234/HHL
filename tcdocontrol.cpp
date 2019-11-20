#include "tcdocontrol.h"
#include "ui_tcdocontrol.h"
#include "qdebug.h"

#define DO_LENGTH (16)

TCDOControl::TCDOControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCDOControl)
{
    ui->setupUi(this);
}

TCDOControl::~TCDOControl()
{
    delete ui;
}

void TCDOControl::initialName(QList<QString> &names, QString str, QString traintype)
{
    if(names.length()!=DO_LENGTH)
    {
        //_LOG << "the length do not equal to" << DI_LENGTH;
        return;
    }
    QList<QLabel*>labels;
    labels<<ui->lbl_CH1_Name<<ui->lbl_CH2_Name<<ui->lbl_CH3_Name<<ui->lbl_CH4_Name<<ui->lbl_CH5_Name<<ui->lbl_CH6_Name<<ui->lbl_CH7_Name
            <<ui->lbl_CH8_Name<<ui->lbl_CH9_Name<<ui->lbl_CH10_Name<<ui->lbl_CH11_Name<<ui->lbl_CH12_Name<<ui->lbl_CH13_Name
            <<ui->lbl_CH14_Name<<ui->lbl_CH15_Name<<ui->lbl_CH16_Name;
    for(int i=0;i<names.length();i++)
    {
        labels.at(i)->setText(names.at(i));
    }

    QList<QLabel*> labelsName;
    labelsName<<ui->lbl_CH1<<ui->lbl_CH2<<ui->lbl_CH3<<ui->lbl_CH4<<ui->lbl_CH5<<ui->lbl_CH6<<ui->lbl_CH7<<ui->lbl_CH8
            <<ui->lbl_CH9<<ui->lbl_CH10<<ui->lbl_CH11<<ui->lbl_CH12<<ui->lbl_CH13<<ui->lbl_CH14<<ui->lbl_CH15<<ui->lbl_CH16;
    for(int i=0;i<labelsName.length();i++)
    {
        labelsName.at(i)->setText(str+"-"+QString::number(i+1));
    }

    if(traintype=="MC")
    {
        ui->TrainType1->setText("MC1");
        ui->TrainType2->setText("MC2");
        ui->TrainType3->setText("MC1");
        ui->TrainType4->setText("MC2");
    }
    else if(traintype=="MP")
    {
        ui->TrainType1->setText("MP1");
        ui->TrainType2->setText("MP2");
        ui->TrainType3->setText("MP1");
        ui->TrainType4->setText("MP2");
    }
    else
    {}
}

void TCDOControl::updateDo(QList<bool> &state)
{
    if(state.length()!=DO_LENGTH*2)
    {
        qDebug()<< "TCDO's length do not equal to" << DO_LENGTH*4;
        return;
    }
    QList<QLabel*> labels;
    labels<<ui->lbl_CH1_State1<<ui->lbl_CH2_State1<<ui->lbl_CH3_State1<<ui->lbl_CH4_State1<<ui->lbl_CH5_State1<<ui->lbl_CH6_State1
            <<ui->lbl_CH7_State1<<ui->lbl_CH8_State1<<ui->lbl_CH9_State1<<ui->lbl_CH10_State1<<ui->lbl_CH11_State1<<ui->lbl_CH12_State1
            <<ui->lbl_CH13_State1<<ui->lbl_CH14_State1<<ui->lbl_CH15_State1<<ui->lbl_CH16_State1
            <<ui->lbl_CH1_State2<<ui->lbl_CH2_State2<<ui->lbl_CH3_State2<<ui->lbl_CH4_State2<<ui->lbl_CH5_State2<<ui->lbl_CH6_State2
            <<ui->lbl_CH7_State2<<ui->lbl_CH8_State2<<ui->lbl_CH9_State2<<ui->lbl_CH10_State2<<ui->lbl_CH11_State2<<ui->lbl_CH12_State2
            <<ui->lbl_CH13_State2<<ui->lbl_CH14_State2<<ui->lbl_CH15_State2<<ui->lbl_CH16_State2;
    for(int i=0;i<state.length();i++)
    {
        if(state.at(i))
        {
            labels.at(i)->setText("1");
            labels.at(i)->setStyleSheet("background-color:rgb(85, 255, 0)");
        }
        else
        {
            labels.at(i)->setText("0");
            labels.at(i)->setStyleSheet("background-color:rgb(0,0,0)");
        }
    }
}
