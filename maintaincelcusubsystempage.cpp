#include "maintaincelcusubsystempage.h"
#include "ui_maintaincelcusubsystempage.h"

#define BUTTONPRESS "border-top:0px solid rgb(19,20,87);color: rgb(255, 255, 255);background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));font:16px \"微软雅黑\";"
#define BUTTONRELEASE "border-top:3px solid rgb(19,20,87);color: rgb(255, 255, 255);border-bottom:3px solid rgb(187,188,247);border-left:3px solid qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));border-right:3px solid qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));font:16px \"微软雅黑\";"
#define LINE "--"

MaintainceLCUSubsystemPage::MaintainceLCUSubsystemPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceLCUSubsystemPage)
{
    ui->setupUi(this);
    current_LCU=1;
    currentPage_LCU=1;
    ui->LCU1->setStyleSheet(BUTTONPRESS);
    buttons<<ui->BTN1<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5<<ui->BTN6<<ui->BTN7<<ui->BTN8<<ui->BTN9
            <<ui->BTNHome<<ui->LCU1<<ui->LCU2<<ui->LCU3<<ui->LCU4<<ui->LCU5<<ui->LCU6<<ui->LCU7<<ui->LCU8;
    buttonLCUs<<ui->LCU1<<ui->LCU2<<ui->LCU3<<ui->LCU4<<ui->LCU5<<ui->LCU6<<ui->LCU7<<ui->LCU8;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushButtonPressedEvent()));
    }
    lbl_row1_names<<ui->row1_name_1<<ui->row1_name_2<<ui->row1_name_3<<ui->row1_name_4<<ui->row1_name_5<<ui->row1_name_6
            <<ui->row1_name_7<<ui->row1_name_8<<ui->row1_name_9<<ui->row1_name_10<<ui->row1_name_11<<ui->row1_name_12
            <<ui->row1_name_13<<ui->row1_name_14<<ui->row1_name_15<<ui->row1_name_16;
    lbl_row2_names<<ui->row2_name_1<<ui->row2_name_2<<ui->row2_name_3<<ui->row2_name_4<<ui->row2_name_5<<ui->row2_name_6
            <<ui->row2_name_7<<ui->row2_name_8<<ui->row2_name_9<<ui->row2_name_10<<ui->row2_name_11<<ui->row2_name_12
            <<ui->row2_name_13<<ui->row2_name_14<<ui->row2_name_15<<ui->row2_name_16;
    lbl_row3_names<<ui->row3_name_1<<ui->row3_name_2<<ui->row3_name_3<<ui->row3_name_4<<ui->row3_name_5<<ui->row3_name_6
            <<ui->row3_name_7<<ui->row3_name_8<<ui->row3_name_9<<ui->row3_name_10<<ui->row3_name_11<<ui->row3_name_12
            <<ui->row3_name_13<<ui->row3_name_14<<ui->row3_name_15<<ui->row3_name_16;
    lbl_row4_names<<ui->row4_name_1<<ui->row4_name_2<<ui->row4_name_3<<ui->row4_name_4<<ui->row4_name_5<<ui->row4_name_6
            <<ui->row4_name_7<<ui->row4_name_8<<ui->row4_name_9<<ui->row4_name_10<<ui->row4_name_11<<ui->row4_name_12
            <<ui->row4_name_13<<ui->row4_name_14<<ui->row4_name_15<<ui->row4_name_16;

    lbl_row1_values<<ui->row1_value_1<<ui->row1_value_2<<ui->row1_value_3<<ui->row1_value_4<<ui->row1_value_5<<ui->row1_value_6
            <<ui->row1_value_7<<ui->row1_value_8<<ui->row1_value_9<<ui->row1_value_10<<ui->row1_value_11<<ui->row1_value_12
            <<ui->row1_value_13<<ui->row1_value_14<<ui->row1_value_15<<ui->row1_value_16;
    lbl_row2_values<<ui->row2_value_1<<ui->row2_value_2<<ui->row2_value_3<<ui->row2_value_4<<ui->row2_value_5<<ui->row2_value_6
            <<ui->row2_value_7<<ui->row2_value_8<<ui->row2_value_9<<ui->row2_value_10<<ui->row2_value_11<<ui->row2_value_12
            <<ui->row2_value_13<<ui->row2_value_14<<ui->row2_value_15<<ui->row2_value_16;
    lbl_row3_values<<ui->row3_value_1<<ui->row3_value_2<<ui->row3_value_3<<ui->row3_value_4<<ui->row3_value_5<<ui->row3_value_6
            <<ui->row3_value_7<<ui->row3_value_8<<ui->row3_value_9<<ui->row3_value_10<<ui->row3_value_11<<ui->row3_value_12
            <<ui->row3_value_13<<ui->row3_value_14<<ui->row3_value_15<<ui->row3_value_16;
    lbl_row4_values<<ui->row4_value_1<<ui->row4_value_2<<ui->row4_value_3<<ui->row4_value_4<<ui->row4_value_5<<ui->row4_value_6
            <<ui->row4_value_7<<ui->row4_value_8<<ui->row4_value_9<<ui->row4_value_10<<ui->row4_value_11<<ui->row4_value_12
            <<ui->row4_value_13<<ui->row4_value_14<<ui->row4_value_15<<ui->row4_value_16;
}

MaintainceLCUSubsystemPage::~MaintainceLCUSubsystemPage()
{
    delete ui;
}

void MaintainceLCUSubsystemPage::updatePage()
{

    if(current_LCU==1)
    {
        if(currentPage_LCU==1)
        {
            row1Names<<"LCU1生命信号"<<"A组电源状态"<<"A组供电状态"<<"CAN1级联通信状态"<<"B组电源状态"<<"B组供电断开"<<"CAN2级联通信状态"<<"通信板状态"
                    <<"通信板can1状态"<<"通信板can2状态"<<"存储板状态"<<"存储板can1状态"<<"存储板can2状态"<<"主控板A can1状态"<<"主控板A can2状态"<<"主控板A输入状态";

            row1Values<<database->LU1CT_PwAFlt_B1<<database->LU1CT_PwAOffA_B1<<database->LU1CT_LcuCan1Flt_B1
                    <<database->LU1CT_PwBFlt_B1<<database->LU1CT_PwBOff_B1<<database->LU1CT_LcuCan2Flt_B1<<database->LU1CT_MVBFlt_B1
                    <<database->LU1CT_MVBCan1Flt_B1<<database->LU1CT_MVBCan2Flt_B1<<database->LU1CT_ETHFlt_B1<<database->LU1CT_ETHCan1Flt_B1
                    <<database->LU1CT_ETHCan2Flt_B1<<database->LU1CT_CtlACan1Flt_B1<<database->LU1CT_CtlACan2Flt_B1<<database->LU1CT_CtlAIptFlt_B1;

            value1=changeSignalStatus(row1Values);
            value1.prepend(QString::number(database->LU1CT_LfSgn_U16));
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"主控板A输出状态"<<"主控板A状态"<<"主控板A为当前工作组"<<"主控板B can1状态"<<"主控板B can2状态"<<"主控板B输入状态"<<"主控板B输出状态"<<"主控板B状态"
                    <<"主控板B为当前工作组"<<"IO板1A can1"<<"IO板1A can2"<<"IO板1A状态"<<"IO板1A为当前工作组"<<"IO板1B can1"<<"IO板1B can2"<<"IO板1B状态";

            row2Values<<database->LU1CT_CtlAOptFlt_B1<<database->LU1CT_CtlAOffLine_B1<<database->LU1CT_CtlATrust_B1<<database->LU1CT_CtlBCan1Flt_B1
                    <<database->LU1CT_CtlBCan2Flt_B1<<database->LU1CT_CtlBIptFlt_B1<<database->LU1CT_CtlBOptFlt_B1<<database->LU1CT_CtlBOffLine_B1
                    <<database->LU1CT_CtlBTrust_B1<<database->LU1CT_IO1ACan1Flt_B1<<database->LU1CT_IO1ACan2Flt_B1<<database->LU1CT_IO1AOffLine_B1
                    <<database->LU1CT_IO1ATrust_B1<<database->LU1CT_IO1BCan1Flt_B1<<database->LU1CT_IO1BCan2Flt_B1<<database->LU1CT_IO1BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板1B为当前工作组"<<"IO板2A can1"<<"IO板2A can2"<<"IO板2A状态"<<"IO板2A为当前工作组"<<"IO板2B can1"<<"IO板2B can2"<<"IO板2B状态"
                    <<"IO板2B为当前工作组"<<"IO板3A can1"<<"IO板3A can2"<<"IO板3A状态"<<"IO板3A为当前工作组"<<"IO板3B can1"<<"IO板3B can2"<<"IO板3B状态";

            row3Values<<database->LU1CT_IO1BTrust_B1<<database->LU1CT_IO2ACan1Flt_B1<<database->LU1CT_IO2ACan2Flt_B1<<database->LU1CT_IO2AOffLine_B1
                    <<database->LU1CT_IO2ATrust_B1<<database->LU1CT_IO2BCan1Flt_B1<<database->LU1CT_IO2BCan2Flt_B1<<database->LU1CT_IO2BOffLine_B1
                    <<database->LU1CT_IO2BTrust_B1<<database->LU1CT_IO3ACan1Flt_B1<<database->LU1CT_IO3ACan2Flt_B1<<database->LU1CT_IO3AOffLine_B1
                    <<database->LU1CT_IO3ATrust_B1<<database->LU1CT_IO3BCan1Flt_B1<<database->LU1CT_IO3BCan2Flt_B1<<database->LU1CT_IO3BOffLine_B1;
            value1=changeSignalStatus(row3Values);
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<"IO板3B为当前工作组"<<"IO板4A can1"<<"IO板4A can2"<<"IO板4A状态"<<"IO板4A为当前工作组"<<"IO板4B can1"<<"IO板4B can2"<<"IO板4B状态"
                    <<"IO板4B为当前工作组"<<"IO板5A can1"<<"IO板5A can2"<<"IO板5A状态"<<"IO板5A为当前工作组"<<"IO板5B can1"<<"IO板5B can2"<<"IO板5B状态";
            row4Values<<database->LU1CT_IO3BTrust_B1<<database->LU1CT_IO4ACan1Flt_B1<<database->LU1CT_IO4ACan2Flt_B1<<database->LU1CT_IO4AOffLine_B1
                    <<database->LU1CT_IO4ATrust_B1<<database->LU1CT_IO4BCan1Flt_B1<<database->LU1CT_IO4BCan2Flt_B1<<database->LU1CT_IO4BOffLine_B1
                    <<database->LU1CT_IO4BTrust_B1<<database->LU1CT_IO5ACan1Flt_B1<<database->LU1CT_IO5ACan2Flt_B1<<database->LU1CT_IO5AOffLine_B1
                    <<database->LU1CT_IO5ATrust_B1<<database->LU1CT_IO5BCan1Flt_B1<<database->LU1CT_IO5BCan2Flt_B1<<database->LU1CT_IO5AOffLine_B1;
            value1=changeSignalStatus(row4Values);
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();

        }
        else if(currentPage_LCU==2)
        {
            row1Names<<"IO板5B为当前工作组"<<"IO板6A can1"<<"IO板6A can2"<<"IO板6A状态"<<"IO板6A为当前工作组"<<"IO板6B can1"<<"IO板6B can2"<<"IO板6B状态"
                    <<"IO板6B为当前工作组"<<"IO板7A can1"<<"IO板7A can2"<<"IO板7A状态"<<"IO板7A为当前工作组"<<"IO板7B can1"<<"IO板7B can2"<<"IO板7B状态";
            row1Values<<database->LU1CT_IO5BTrust_B1<<database->LU1CT_IO6ACan1Flt_B1<<database->LU1CT_IO6ACan2Flt_B1<<database->LU1CT_IO6AOffLine_B1
                    <<database->LU1CT_IO6ATrust_B1<<database->LU1CT_IO6BCan1Flt_B1<<database->LU1CT_IO6BCan2Flt_B1<<database->LU1CT_IO6BOffLine_B1
                    <<database->LU1CT_IO6BTrust_B1<<database->LU1CT_IO7ACan1Flt_B1<<database->LU1CT_IO7ACan2Flt_B1<<database->LU1CT_IO7AOffLine_B1
                    <<database->LU1CT_IO7ATrust_B1<<database->LU1CT_IO7BCan1Flt_B1<<database->LU1CT_IO7BCan2Flt_B1<<database->LU1CT_IO7BOffLine_B1;
            value1=changeSignalStatus(row1Values);
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"IO板7B为当前工作组"<<"IO板8A can1"<<"IO板8A can2"<<"IO板8A状态"<<"IO板8A为当前工作组"<<"IO板8B can1"<<"IO板8B can2"<<"IO板8B状态"
                    <<"IO板8B为当前工作组"<<"IO板9A can1"<<"IO板9A can2"<<"IO板9A状态"<<"IO板9A为当前工作组"<<"IO板9B can1"<<"IO板9B can2"<<"IO板9B状态";
            row2Values<<database->LU1CT_IO7BTrust_B1<<database->LU1CT_IO8ACan1Flt_B1<<database->LU1CT_IO8ACan2Flt_B1<<database->LU1CT_IO8AOffLine_B1
                    <<database->LU1CT_IO8ATrust_B1<<database->LU1CT_IO8BCan1Flt_B1<<database->LU1CT_IO8BCan2Flt_B1<<database->LU1CT_IO8BOffLine_B1
                    <<database->LU1CT_IO8BTrust_B1<<database->LU1CT_IO9ACan1Flt_B1<<database->LU1CT_IO9ACan2Flt_B1<<database->LU1CT_IO9AOffLine_B1
                    <<database->LU1CT_IO9ATrust_B1<<database->LU1CT_IO9BCan1Flt_B1<<database->LU1CT_IO9BCan2Flt_B1<<database->LU1CT_IO9BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板9B为当前工作组"<<"IO板10A can1"<<"IO板10A can2"<<"IO板10A状态"<<"IO板10A为当前工作组"<<"IO板10B can1"<<"IO板10B can2"<<"IO板10B状态"
                    <<"IO板10B为当前工作组"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--";
            row3Values<<database->LU1CT_IO9BTrust_B1<<database->LU1CT_IO10ACan1Flt_B1<<database->LU1CT_IO10ACan2Flt_B1<<database->LU1CT_IO10AOffLine_B1
                    <<database->LU1CT_IO10ATrust_B1<<database->LU1CT_IO10BCan1Flt_B1<<database->LU1CT_IO10BCan2Flt_B1<<database->LU1CT_IO10BOffLine_B1
                    <<database->LU1CT_IO10BTrust_B1;
            value1=changeSignalStatus(row3Values);
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();
        }
    }
    else if(current_LCU==2)
    {
        if(currentPage_LCU==1)
        {
            row1Names<<"LCU2生命信号"<<"A组电源状态"<<"A组供电状态"<<"CAN1级联通信状态"<<"B组电源状态"<<"B组供电断开"<<"CAN2级联通信状态"<<"通信板状态"
                    <<"通信板can1状态"<<"通信板can2状态"<<"存储板状态"<<"存储板can1状态"<<"存储板can2状态"<<"主控板A can1状态"<<"主控板A can2状态"<<"主控板A输入状态";

            row1Values<<database->LU2CT_PwAFlt_B1<<database->LU2CT_PwAOffA_B1<<database->LU2CT_LcuCan1Flt_B1
                    <<database->LU2CT_PwBFlt_B1<<database->LU2CT_PwBOff_B1<<database->LU2CT_LcuCan2Flt_B1<<database->LU2CT_MVBFlt_B1
                    <<database->LU2CT_MVBCan1Flt_B1<<database->LU2CT_MVBCan2Flt_B1<<database->LU2CT_ETHFlt_B1<<database->LU2CT_ETHCan1Flt_B1
                    <<database->LU2CT_ETHCan2Flt_B1<<database->LU2CT_CtlACan1Flt_B1<<database->LU2CT_CtlACan2Flt_B1<<database->LU2CT_CtlAIptFlt_B1;

            value1=changeSignalStatus(row1Values);
            value1.prepend(QString::number(database->LU2CT_LfSgn_U16));
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"主控板A输出状态"<<"主控板A状态"<<"主控板A为当前工作组"<<"主控板B can1状态"<<"主控板B can2状态"<<"主控板B输入状态"<<"主控板B输出状态"<<"主控板B状态"
                    <<"主控板B为当前工作组"<<"IO板1A can1"<<"IO板1A can2"<<"IO板1A状态"<<"IO板1A为当前工作组"<<"IO板1B can1"<<"IO板1B can2"<<"IO板1B状态";

            row2Values<<database->LU2CT_CtlAOptFlt_B1<<database->LU2CT_CtlAOffLine_B1<<database->LU2CT_CtlATrust_B1<<database->LU2CT_CtlBCan1Flt_B1
                    <<database->LU2CT_CtlBCan2Flt_B1<<database->LU2CT_CtlBIptFlt_B1<<database->LU2CT_CtlBOptFlt_B1<<database->LU2CT_CtlBOffLine_B1
                    <<database->LU2CT_CtlBTrust_B1<<database->LU2CT_IO1ACan1Flt_B1<<database->LU2CT_IO1ACan2Flt_B1<<database->LU2CT_IO1AOffLine_B1
                    <<database->LU2CT_IO1ATrust_B1<<database->LU2CT_IO1BCan1Flt_B1<<database->LU2CT_IO1BCan2Flt_B1<<database->LU2CT_IO1BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板1B为当前工作组"<<"IO板2A can1"<<"IO板2A can2"<<"IO板2A状态"<<"IO板2A为当前工作组"<<"IO板2B can1"<<"IO板2B can2"<<"IO板2B状态"
                    <<"IO板2B为当前工作组"<<"IO板3A can1"<<"IO板3A can2"<<"IO板3A状态"<<"IO板3A为当前工作组"<<"IO板3B can1"<<"IO板3B can2"<<"IO板3B状态";

            row3Values<<database->LU2CT_IO1BTrust_B1<<database->LU2CT_IO2ACan1Flt_B1<<database->LU2CT_IO2ACan2Flt_B1<<database->LU2CT_IO2AOffLine_B1
                    <<database->LU2CT_IO2ATrust_B1<<database->LU2CT_IO2BCan1Flt_B1<<database->LU2CT_IO2BCan2Flt_B1<<database->LU2CT_IO2BOffLine_B1
                    <<database->LU2CT_IO2BTrust_B1<<database->LU2CT_IO3ACan1Flt_B1<<database->LU2CT_IO3ACan2Flt_B1<<database->LU2CT_IO3AOffLine_B1
                    <<database->LU2CT_IO3ATrust_B1<<database->LU2CT_IO3BCan1Flt_B1<<database->LU2CT_IO3BCan2Flt_B1<<database->LU2CT_IO3BOffLine_B1;
            value1=changeSignalStatus(row3Values);
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<"IO板3B为当前工作组"<<"IO板4A can1"<<"IO板4A can2"<<"IO板4A状态"<<"IO板4A为当前工作组"<<"IO板4B can1"<<"IO板4B can2"<<"IO板4B状态"
                    <<"IO板4B为当前工作组"<<"IO板5A can1"<<"IO板5A can2"<<"IO板5A状态"<<"IO板5A为当前工作组"<<"IO板5B can1"<<"IO板5B can2"<<"IO板5B状态";
            row4Values<<database->LU2CT_IO3BTrust_B1<<database->LU2CT_IO4ACan1Flt_B1<<database->LU2CT_IO4ACan2Flt_B1<<database->LU2CT_IO4AOffLine_B1
                    <<database->LU2CT_IO4ATrust_B1<<database->LU2CT_IO4BCan1Flt_B1<<database->LU2CT_IO4BCan2Flt_B1<<database->LU2CT_IO4BOffLine_B1
                    <<database->LU2CT_IO4BTrust_B1<<database->LU2CT_IO5ACan1Flt_B1<<database->LU2CT_IO5ACan2Flt_B1<<database->LU2CT_IO5AOffLine_B1
                    <<database->LU2CT_IO5ATrust_B1<<database->LU2CT_IO5BCan1Flt_B1<<database->LU2CT_IO5BCan2Flt_B1<<database->LU2CT_IO5BOffLine_B1;
            value1=changeSignalStatus(row4Values);
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();

        }
        else if(currentPage_LCU==2)
        {
            row1Names<<"IO板5B为当前工作组"<<"IO板6A can1"<<"IO板6A can2"<<"IO板6A状态"<<"IO板6A为当前工作组"<<"IO板6B can1"<<"IO板6B can2"<<"IO板6B状态"
                    <<"IO板6B为当前工作组"<<"IO板7A can1"<<"IO板7A can2"<<"IO板7A状态"<<"IO板7A为当前工作组"<<"IO板7B can1"<<"IO板7B can2"<<"IO板7B状态";
            row1Values<<database->LU2CT_IO5BTrust_B1<<database->LU2CT_IO6ACan1Flt_B1<<database->LU2CT_IO6ACan2Flt_B1<<database->LU2CT_IO6AOffLine_B1
                    <<database->LU2CT_IO6ATrust_B1<<database->LU2CT_IO6BCan1Flt_B1<<database->LU2CT_IO6BCan2Flt_B1<<database->LU2CT_IO6BOffLine_B1
                    <<database->LU2CT_IO6BTrust_B1<<database->LU2CT_IO7ACan1Flt_B1<<database->LU2CT_IO7ACan2Flt_B1<<database->LU2CT_IO7AOffLine_B1
                    <<database->LU2CT_IO7ATrust_B1<<database->LU2CT_IO7BCan1Flt_B1<<database->LU2CT_IO7BCan2Flt_B1<<database->LU2CT_IO7BOffLine_B1;
            value1=changeSignalStatus(row1Values);
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"IO板7B为当前工作组"<<"IO板8A can1"<<"IO板8A can2"<<"IO板8A状态"<<"IO板8A为当前工作组"<<"IO板8B can1"<<"IO板8B can2"<<"IO板8B状态"
                    <<"IO板8B为当前工作组"<<"IO板9A can1"<<"IO板9A can2"<<"IO板9A状态"<<"IO板9A为当前工作组"<<"IO板9B can1"<<"IO板9B can2"<<"IO板9B状态";
            row2Values<<database->LU2CT_IO7BTrust_B1<<database->LU2CT_IO8ACan1Flt_B1<<database->LU2CT_IO8ACan2Flt_B1<<database->LU2CT_IO8AOffLine_B1
                    <<database->LU2CT_IO8ATrust_B1<<database->LU2CT_IO8BCan1Flt_B1<<database->LU2CT_IO8BCan2Flt_B1<<database->LU2CT_IO8BOffLine_B1
                    <<database->LU2CT_IO8BTrust_B1<<database->LU2CT_IO9ACan1Flt_B1<<database->LU2CT_IO9ACan2Flt_B1<<database->LU2CT_IO9AOffLine_B1
                    <<database->LU2CT_IO9ATrust_B1<<database->LU2CT_IO9BCan1Flt_B1<<database->LU2CT_IO9BCan2Flt_B1<<database->LU2CT_IO9BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板9B为当前工作组"<<"IO板10A can1"<<"IO板10A can2"<<"IO板10A状态"<<"IO板10A为当前工作组"<<"IO板10B can1"<<"IO板10B can2"<<"IO板10B状态"
                    <<"IO板10B为当前工作组"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--";
            row3Values<<database->LU2CT_IO9BTrust_B1<<database->LU2CT_IO10ACan1Flt_B1<<database->LU2CT_IO10ACan2Flt_B1<<database->LU2CT_IO10AOffLine_B1
                    <<database->LU2CT_IO10ATrust_B1<<database->LU2CT_IO10BCan1Flt_B1<<database->LU2CT_IO10BCan2Flt_B1<<database->LU2CT_IO10BOffLine_B1
                    <<database->LU2CT_IO10BTrust_B1;
            value1=changeSignalStatus(row3Values);
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();
        }
    }
    else if(current_LCU==3)
    {
        if(currentPage_LCU==1)
        {
            row1Names<<"LCU3生命信号"<<"A组电源状态"<<"A组供电状态"<<"CAN1级联通信状态"<<"B组电源状态"<<"B组供电断开"<<"CAN2级联通信状态"<<"通信板状态"
                    <<"通信板can1状态"<<"通信板can2状态"<<"存储板状态"<<"存储板can1状态"<<"存储板can2状态"<<"主控板A can1状态"<<"主控板A can2状态"<<"主控板A输入状态";

            row1Values<<database->LU3CT_PwAFlt_B1<<database->LU3CT_PwAOffA_B1<<database->LU3CT_LcuCan1Flt_B1
                    <<database->LU3CT_PwBFlt_B1<<database->LU3CT_PwBOff_B1<<database->LU3CT_LcuCan2Flt_B1<<database->LU3CT_MVBFlt_B1
                    <<database->LU3CT_MVBCan1Flt_B1<<database->LU3CT_MVBCan2Flt_B1<<database->LU3CT_ETHFlt_B1<<database->LU3CT_ETHCan1Flt_B1
                    <<database->LU3CT_ETHCan2Flt_B1<<database->LU3CT_CtlACan1Flt_B1<<database->LU3CT_CtlACan2Flt_B1<<database->LU3CT_CtlAIptFlt_B1;

            value1=changeSignalStatus(row1Values);
            value1.prepend(QString::number(database->LU3CT_LfSgn_U16));
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"主控板A输出状态"<<"主控板A状态"<<"主控板A为当前工作组"<<"主控板B can1状态"<<"主控板B can2状态"<<"主控板B输入状态"<<"主控板B输出状态"<<"主控板B状态"
                    <<"主控板B为当前工作组"<<"IO板1A can1"<<"IO板1A can2"<<"IO板1A状态"<<"IO板1A为当前工作组"<<"IO板1B can1"<<"IO板1B can2"<<"IO板1B状态";

            row2Values<<database->LU3CT_CtlAOptFlt_B1<<database->LU3CT_CtlAOffLine_B1<<database->LU3CT_CtlATrust_B1<<database->LU3CT_CtlBCan1Flt_B1
                    <<database->LU3CT_CtlBCan2Flt_B1<<database->LU3CT_CtlBIptFlt_B1<<database->LU3CT_CtlBOptFlt_B1<<database->LU3CT_CtlBOffLine_B1
                    <<database->LU3CT_CtlBTrust_B1<<database->LU3CT_IO1ACan1Flt_B1<<database->LU3CT_IO1ACan2Flt_B1<<database->LU3CT_IO1AOffLine_B1
                    <<database->LU3CT_IO1ATrust_B1<<database->LU3CT_IO1BCan1Flt_B1<<database->LU3CT_IO1BCan2Flt_B1<<database->LU3CT_IO1BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板1B为当前工作组"<<"IO板2A can1"<<"IO板2A can2"<<"IO板2A状态"<<"IO板2A为当前工作组"<<"IO板2B can1"<<"IO板2B can2"<<"IO板2B状态"
                    <<"IO板2B为当前工作组"<<"IO板3A can1"<<"IO板3A can2"<<"IO板3A状态"<<"IO板3A为当前工作组"<<"IO板3B can1"<<"IO板3B can2"<<"IO板3B状态";

            row3Values<<database->LU3CT_IO1BTrust_B1<<database->LU3CT_IO2ACan1Flt_B1<<database->LU3CT_IO2ACan2Flt_B1<<database->LU3CT_IO2AOffLine_B1
                    <<database->LU3CT_IO2ATrust_B1<<database->LU3CT_IO2BCan1Flt_B1<<database->LU3CT_IO2BCan2Flt_B1<<database->LU3CT_IO2BOffLine_B1
                    <<database->LU3CT_IO2BTrust_B1<<database->LU3CT_IO3ACan1Flt_B1<<database->LU3CT_IO3ACan2Flt_B1<<database->LU3CT_IO3AOffLine_B1
                    <<database->LU3CT_IO3ATrust_B1<<database->LU3CT_IO3BCan1Flt_B1<<database->LU3CT_IO3BCan2Flt_B1<<database->LU3CT_IO3BOffLine_B1;
            value1=changeSignalStatus(row3Values);
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<"IO板3B为当前工作组"<<"IO板4A can1"<<"IO板4A can2"<<"IO板4A状态"<<"IO板4A为当前工作组"<<"IO板4B can1"<<"IO板4B can2"<<"IO板4B状态"
                    <<"IO板4B为当前工作组"<<"IO板5A can1"<<"IO板5A can2"<<"IO板5A状态"<<"IO板5A为当前工作组"<<"IO板5B can1"<<"IO板5B can2"<<"IO板5B状态";
            row4Values<<database->LU3CT_IO3BTrust_B1<<database->LU3CT_IO4ACan1Flt_B1<<database->LU3CT_IO4ACan2Flt_B1<<database->LU3CT_IO4AOffLine_B1
                    <<database->LU3CT_IO4ATrust_B1<<database->LU3CT_IO4BCan1Flt_B1<<database->LU3CT_IO4BCan2Flt_B1<<database->LU3CT_IO4BOffLine_B1
                    <<database->LU3CT_IO4BTrust_B1<<database->LU3CT_IO5ACan1Flt_B1<<database->LU3CT_IO5ACan2Flt_B1<<database->LU3CT_IO5AOffLine_B1
                    <<database->LU3CT_IO5ATrust_B1<<database->LU3CT_IO5BCan1Flt_B1<<database->LU3CT_IO5BCan2Flt_B1<<database->LU3CT_IO5BOffLine_B1;
            value1=changeSignalStatus(row4Values);
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();

        }
        else if(currentPage_LCU==2)
        {
            row1Names<<"IO板5B为当前工作组"<<"IO板6A can1"<<"IO板6A can2"<<"IO板6A状态"<<"IO板6A为当前工作组"<<"IO板6B can1"<<"IO板6B can2"<<"IO板6B状态"
                    <<"IO板6B为当前工作组"<<"IO板7A can1"<<"IO板7A can2"<<"IO板7A状态"<<"IO板7A为当前工作组"<<"IO板7B can1"<<"IO板7B can2"<<"IO板7B状态";
            row1Values<<database->LU3CT_IO5BTrust_B1<<database->LU3CT_IO6ACan1Flt_B1<<database->LU3CT_IO6ACan2Flt_B1<<database->LU3CT_IO6AOffLine_B1
                    <<database->LU3CT_IO6ATrust_B1<<database->LU3CT_IO6BCan1Flt_B1<<database->LU3CT_IO6BCan2Flt_B1<<database->LU3CT_IO6BOffLine_B1
                    <<database->LU3CT_IO6BTrust_B1<<database->LU3CT_IO7ACan1Flt_B1<<database->LU3CT_IO7ACan2Flt_B1<<database->LU3CT_IO7AOffLine_B1
                    <<database->LU3CT_IO7ATrust_B1<<database->LU3CT_IO7BCan1Flt_B1<<database->LU3CT_IO7BCan2Flt_B1<<database->LU3CT_IO7BOffLine_B1;
            value1=changeSignalStatus(row1Values);
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"IO板7B为当前工作组"<<"IO板8A can1"<<"IO板8A can2"<<"IO板8A状态"<<"IO板8A为当前工作组"<<"IO板8B can1"<<"IO板8B can2"<<"IO板8B状态"
                    <<"IO板8B为当前工作组"<<"IO板9A can1"<<"IO板9A can2"<<"IO板9A状态"<<"IO板9A为当前工作组"<<"IO板9B can1"<<"IO板9B can2"<<"IO板9B状态";
            row2Values<<database->LU3CT_IO7BTrust_B1<<database->LU3CT_IO8ACan1Flt_B1<<database->LU3CT_IO8ACan2Flt_B1<<database->LU3CT_IO8AOffLine_B1
                    <<database->LU3CT_IO8ATrust_B1<<database->LU3CT_IO8BCan1Flt_B1<<database->LU3CT_IO8BCan2Flt_B1<<database->LU3CT_IO8BOffLine_B1
                    <<database->LU3CT_IO8BTrust_B1<<database->LU3CT_IO9ACan1Flt_B1<<database->LU3CT_IO9ACan2Flt_B1<<database->LU3CT_IO9AOffLine_B1
                    <<database->LU3CT_IO9ATrust_B1<<database->LU3CT_IO9BCan1Flt_B1<<database->LU3CT_IO9BCan2Flt_B1<<database->LU3CT_IO9BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板9B为当前工作组"<<"IO板10A can1"<<"IO板10A can2"<<"IO板10A状态"<<"IO板10A为当前工作组"<<"IO板10B can1"<<"IO板10B can2"<<"IO板10B状态"
                    <<"IO板10B为当前工作组"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--";
            row3Values<<database->LU3CT_IO9BTrust_B1<<database->LU3CT_IO10ACan1Flt_B1<<database->LU3CT_IO10ACan2Flt_B1<<database->LU3CT_IO10AOffLine_B1
                    <<database->LU3CT_IO10ATrust_B1<<database->LU3CT_IO10BCan1Flt_B1<<database->LU3CT_IO10BCan2Flt_B1<<database->LU3CT_IO10BOffLine_B1
                    <<database->LU3CT_IO10BTrust_B1;
            value1=changeSignalStatus(row3Values);
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();
        }
    }
    else if(current_LCU==4)
    {
        if(currentPage_LCU==1)
        {
            row1Names<<"LCU4生命信号"<<"A组电源状态"<<"A组供电状态"<<"CAN1级联通信状态"<<"B组电源状态"<<"B组供电断开"<<"CAN2级联通信状态"<<"通信板状态"
                    <<"通信板can1状态"<<"通信板can2状态"<<"存储板状态"<<"存储板can1状态"<<"存储板can2状态"<<"主控板A can1状态"<<"主控板A can2状态"<<"主控板A输入状态";

            row1Values<<database->LU4CT_PwAFlt_B1<<database->LU4CT_PwAOffA_B1<<database->LU4CT_LcuCan1Flt_B1
                    <<database->LU4CT_PwBFlt_B1<<database->LU4CT_PwBOff_B1<<database->LU4CT_LcuCan2Flt_B1<<database->LU4CT_MVBFlt_B1
                    <<database->LU4CT_MVBCan1Flt_B1<<database->LU4CT_MVBCan2Flt_B1<<database->LU4CT_ETHFlt_B1<<database->LU4CT_ETHCan1Flt_B1
                    <<database->LU4CT_ETHCan2Flt_B1<<database->LU4CT_CtlACan1Flt_B1<<database->LU4CT_CtlACan2Flt_B1<<database->LU4CT_CtlAIptFlt_B1;
            value1=changeSignalStatus(row1Values);
            value1.prepend(QString::number(database->LU4CT_LfSgn_U16));
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"主控板A输出状态"<<"主控板A状态"<<"主控板A为当前工作组"<<"主控板B can1状态"<<"主控板B can2状态"<<"主控板B输入状态"<<"主控板B输出状态"<<"主控板B状态"
                    <<"主控板B为当前工作组"<<"IO板1A can1"<<"IO板1A can2"<<"IO板1A状态"<<"IO板1A为当前工作组"<<"IO板1B can1"<<"IO板1B can2"<<"IO板1B状态";

            row2Values<<database->LU4CT_CtlAOptFlt_B1<<database->LU4CT_CtlAOffLine_B1<<database->LU4CT_CtlATrust_B1<<database->LU4CT_CtlBCan1Flt_B1
                    <<database->LU4CT_CtlBCan2Flt_B1<<database->LU4CT_CtlBIptFlt_B1<<database->LU4CT_CtlBOptFlt_B1<<database->LU4CT_CtlBOffLine_B1
                    <<database->LU4CT_CtlBTrust_B1<<database->LU4CT_IO1ACan1Flt_B1<<database->LU4CT_IO1ACan2Flt_B1<<database->LU4CT_IO1AOffLine_B1
                    <<database->LU4CT_IO1ATrust_B1<<database->LU4CT_IO1BCan1Flt_B1<<database->LU4CT_IO1BCan2Flt_B1<<database->LU4CT_IO1BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板1B为当前工作组"<<"IO板2A can1"<<"IO板2A can2"<<"IO板2A状态"<<"IO板2A为当前工作组"<<"IO板2B can1"<<"IO板2B can2"<<"IO板2B状态"
                    <<"IO板2B为当前工作组"<<"IO板3A can1"<<"IO板3A can2"<<"IO板3A状态"<<"IO板3A为当前工作组"<<"IO板3B can1"<<"IO板3B can2"<<"IO板3B状态";

            row3Values<<database->LU4CT_IO1BTrust_B1<<database->LU4CT_IO2ACan1Flt_B1<<database->LU4CT_IO2ACan2Flt_B1<<database->LU4CT_IO2AOffLine_B1
                    <<database->LU4CT_IO2ATrust_B1<<database->LU4CT_IO2BCan1Flt_B1<<database->LU4CT_IO2BCan2Flt_B1<<database->LU4CT_IO2BOffLine_B1
                    <<database->LU4CT_IO2BTrust_B1<<database->LU4CT_IO3ACan1Flt_B1<<database->LU4CT_IO3ACan2Flt_B1<<database->LU4CT_IO3AOffLine_B1
                    <<database->LU4CT_IO3ATrust_B1<<database->LU4CT_IO3BCan1Flt_B1<<database->LU4CT_IO3BCan2Flt_B1<<database->LU4CT_IO3BOffLine_B1;
            value1=changeSignalStatus(row3Values);
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<"IO板3B为当前工作组"<<"IO板4A can1"<<"IO板4A can2"<<"IO板4A状态"<<"IO板4A为当前工作组"<<"IO板4B can1"<<"IO板4B can2"<<"IO板4B状态"
                    <<"IO板4B为当前工作组"<<"IO板5A can1"<<"IO板5A can2"<<"IO板5A状态"<<"IO板5A为当前工作组"<<"IO板5B can1"<<"IO板5B can2"<<"IO板5B状态";
            row4Values<<database->LU4CT_IO3BTrust_B1<<database->LU4CT_IO4ACan1Flt_B1<<database->LU4CT_IO4ACan2Flt_B1<<database->LU4CT_IO4AOffLine_B1
                    <<database->LU4CT_IO4ATrust_B1<<database->LU4CT_IO4BCan1Flt_B1<<database->LU4CT_IO4BCan2Flt_B1<<database->LU4CT_IO4BOffLine_B1
                    <<database->LU4CT_IO4BTrust_B1<<database->LU4CT_IO5ACan1Flt_B1<<database->LU4CT_IO5ACan2Flt_B1<<database->LU4CT_IO5AOffLine_B1
                    <<database->LU4CT_IO5ATrust_B1<<database->LU4CT_IO5BCan1Flt_B1<<database->LU4CT_IO5BCan2Flt_B1<<database->LU4CT_IO5BOffLine_B1;
            value1=changeSignalStatus(row4Values);
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();

        }
        else if(currentPage_LCU==2)
        {
            row1Names<<"IO板5B为当前工作组"<<"IO板6A can1"<<"IO板6A can2"<<"IO板6A状态"<<"IO板6A为当前工作组"<<"IO板6B can1"<<"IO板6B can2"<<"IO板6B状态"
                    <<"IO板6B为当前工作组"<<"IO板7A can1"<<"IO板7A can2"<<"IO板7A状态"<<"IO板7A为当前工作组"<<"IO板7B can1"<<"IO板7B can2"<<"IO板7B状态";
            row1Values<<database->LU4CT_IO5BTrust_B1<<database->LU4CT_IO6ACan1Flt_B1<<database->LU4CT_IO6ACan2Flt_B1<<database->LU4CT_IO6AOffLine_B1
                    <<database->LU4CT_IO6ATrust_B1<<database->LU4CT_IO6BCan1Flt_B1<<database->LU4CT_IO6BCan2Flt_B1<<database->LU4CT_IO6BOffLine_B1
                    <<database->LU4CT_IO6BTrust_B1<<database->LU4CT_IO7ACan1Flt_B1<<database->LU4CT_IO7ACan2Flt_B1<<database->LU4CT_IO7AOffLine_B1
                    <<database->LU4CT_IO7ATrust_B1<<database->LU4CT_IO7BCan1Flt_B1<<database->LU4CT_IO7BCan2Flt_B1<<database->LU4CT_IO7BOffLine_B1;
            value1=changeSignalStatus(row1Values);
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"IO板7B为当前工作组"<<"IO板8A can1"<<"IO板8A can2"<<"IO板8A状态"<<"IO板8A为当前工作组"<<"IO板8B can1"<<"IO板8B can2"<<"IO板8B状态"
                    <<"IO板8B为当前工作组"<<"IO板9A can1"<<"IO板9A can2"<<"IO板9A状态"<<"IO板9A为当前工作组"<<"IO板9B can1"<<"IO板9B can2"<<"IO板9B状态";
            row2Values<<database->LU4CT_IO7BTrust_B1<<database->LU4CT_IO8ACan1Flt_B1<<database->LU4CT_IO8ACan2Flt_B1<<database->LU4CT_IO8AOffLine_B1
                    <<database->LU4CT_IO8ATrust_B1<<database->LU4CT_IO8BCan1Flt_B1<<database->LU4CT_IO8BCan2Flt_B1<<database->LU4CT_IO8BOffLine_B1
                    <<database->LU4CT_IO8BTrust_B1<<database->LU4CT_IO9ACan1Flt_B1<<database->LU4CT_IO9ACan2Flt_B1<<database->LU4CT_IO9AOffLine_B1
                    <<database->LU4CT_IO9ATrust_B1<<database->LU4CT_IO9BCan1Flt_B1<<database->LU4CT_IO9BCan2Flt_B1<<database->LU4CT_IO9BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板9B为当前工作组"<<"IO板10A can1"<<"IO板10A can2"<<"IO板10A状态"<<"IO板10A为当前工作组"<<"IO板10B can1"<<"IO板10B can2"<<"IO板10B状态"
                    <<"IO板10B为当前工作组"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--";
            row3Values<<database->LU4CT_IO9BTrust_B1<<database->LU4CT_IO10ACan1Flt_B1<<database->LU4CT_IO10ACan2Flt_B1<<database->LU4CT_IO10AOffLine_B1
                    <<database->LU4CT_IO10ATrust_B1<<database->LU4CT_IO10BCan1Flt_B1<<database->LU4CT_IO10BCan2Flt_B1<<database->LU4CT_IO10BOffLine_B1
                    <<database->LU4CT_IO10BTrust_B1;
            value1=changeSignalStatus(row3Values);
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();
        }
    }
    else if(current_LCU==5)
    {
        if(currentPage_LCU==1)
        {
            row1Names<<"LCU5生命信号"<<"A组电源状态"<<"A组供电状态"<<"CAN1级联通信状态"<<"B组电源状态"<<"B组供电断开"<<"CAN2级联通信状态"<<"通信板状态"
                    <<"通信板can1状态"<<"通信板can2状态"<<"存储板状态"<<"存储板can1状态"<<"存储板can2状态"<<"主控板A can1状态"<<"主控板A can2状态"<<"主控板A输入状态";

            row1Values<<database->LU5CT_PwAFlt_B1<<database->LU5CT_PwAOffA_B1<<database->LU5CT_LcuCan1Flt_B1
                    <<database->LU5CT_PwBFlt_B1<<database->LU5CT_PwBOff_B1<<database->LU5CT_LcuCan2Flt_B1<<database->LU5CT_MVBFlt_B1
                    <<database->LU5CT_MVBCan1Flt_B1<<database->LU5CT_MVBCan2Flt_B1<<database->LU5CT_ETHFlt_B1<<database->LU5CT_ETHCan1Flt_B1
                    <<database->LU5CT_ETHCan2Flt_B1<<database->LU5CT_CtlACan1Flt_B1<<database->LU5CT_CtlACan2Flt_B1<<database->LU5CT_CtlAIptFlt_B1;

            value1=changeSignalStatus(row1Values);
            value1.prepend(QString::number(database->LU5CT_LfSgn_U16));
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"主控板A输出状态"<<"主控板A状态"<<"主控板A为当前工作组"<<"主控板B can1状态"<<"主控板B can2状态"<<"主控板B输入状态"<<"主控板B输出状态"<<"主控板B状态"
                    <<"主控板B为当前工作组"<<"IO板1A can1"<<"IO板1A can2"<<"IO板1A状态"<<"IO板1A为当前工作组"<<"IO板1B can1"<<"IO板1B can2"<<"IO板1B状态";

            row2Values<<database->LU5CT_CtlAOptFlt_B1<<database->LU5CT_CtlAOffLine_B1<<database->LU5CT_CtlATrust_B1<<database->LU5CT_CtlBCan1Flt_B1
                    <<database->LU5CT_CtlBCan2Flt_B1<<database->LU5CT_CtlBIptFlt_B1<<database->LU5CT_CtlBOptFlt_B1<<database->LU5CT_CtlBOffLine_B1
                    <<database->LU5CT_CtlBTrust_B1<<database->LU5CT_IO1ACan1Flt_B1<<database->LU5CT_IO1ACan2Flt_B1<<database->LU5CT_IO1AOffLine_B1
                    <<database->LU5CT_IO1ATrust_B1<<database->LU5CT_IO1BCan1Flt_B1<<database->LU5CT_IO1BCan2Flt_B1<<database->LU5CT_IO1BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板1B为当前工作组"<<"IO板2A can1"<<"IO板2A can2"<<"IO板2A状态"<<"IO板2A为当前工作组"<<"IO板2B can1"<<"IO板2B can2"<<"IO板2B状态"
                    <<"IO板2B为当前工作组"<<"IO板3A can1"<<"IO板3A can2"<<"IO板3A状态"<<"IO板3A为当前工作组"<<"IO板3B can1"<<"IO板3B can2"<<"IO板3B状态";

            row3Values<<database->LU5CT_IO1BTrust_B1<<database->LU5CT_IO2ACan1Flt_B1<<database->LU5CT_IO2ACan2Flt_B1<<database->LU5CT_IO2AOffLine_B1
                    <<database->LU5CT_IO2ATrust_B1<<database->LU5CT_IO2BCan1Flt_B1<<database->LU5CT_IO2BCan2Flt_B1<<database->LU5CT_IO2BOffLine_B1
                    <<database->LU5CT_IO2BTrust_B1<<database->LU5CT_IO3ACan1Flt_B1<<database->LU5CT_IO3ACan2Flt_B1<<database->LU5CT_IO3AOffLine_B1
                    <<database->LU5CT_IO3ATrust_B1<<database->LU5CT_IO3BCan1Flt_B1<<database->LU5CT_IO3BCan2Flt_B1<<database->LU5CT_IO3BOffLine_B1;
            value1=changeSignalStatus(row3Values);
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<"IO板3B为当前工作组"<<"IO板4A can1"<<"IO板4A can2"<<"IO板4A状态"<<"IO板4A为当前工作组"<<"IO板4B can1"<<"IO板4B can2"<<"IO板4B状态"
                    <<"IO板4B为当前工作组"<<"IO板5A can1"<<"IO板5A can2"<<"IO板5A状态"<<"IO板5A为当前工作组"<<"IO板5B can1"<<"IO板5B can2"<<"IO板5B状态";
            row4Values<<database->LU5CT_IO3BTrust_B1<<database->LU5CT_IO4ACan1Flt_B1<<database->LU5CT_IO4ACan2Flt_B1<<database->LU5CT_IO4AOffLine_B1
                    <<database->LU5CT_IO4ATrust_B1<<database->LU5CT_IO4BCan1Flt_B1<<database->LU5CT_IO4BCan2Flt_B1<<database->LU5CT_IO4BOffLine_B1
                    <<database->LU5CT_IO4BTrust_B1<<database->LU5CT_IO5ACan1Flt_B1<<database->LU5CT_IO5ACan2Flt_B1<<database->LU5CT_IO5AOffLine_B1
                    <<database->LU5CT_IO5ATrust_B1<<database->LU5CT_IO5BCan1Flt_B1<<database->LU5CT_IO5BCan2Flt_B1<<database->LU5CT_IO5BOffLine_B1;
            value1=changeSignalStatus(row4Values);
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();

        }
        else if(currentPage_LCU==2)
        {
            row1Names<<"IO板5B为当前工作组"<<"IO板6A can1"<<"IO板6A can2"<<"IO板6A状态"<<"IO板6A为当前工作组"<<"IO板6B can1"<<"IO板6B can2"<<"IO板6B状态"
                    <<"IO板6B为当前工作组"<<"IO板7A can1"<<"IO板7A can2"<<"IO板7A状态"<<"IO板7A为当前工作组"<<"IO板7B can1"<<"IO板7B can2"<<"IO板7B状态";
            row1Values<<database->LU5CT_IO5BTrust_B1<<database->LU5CT_IO6ACan1Flt_B1<<database->LU5CT_IO6ACan2Flt_B1<<database->LU5CT_IO6AOffLine_B1
                    <<database->LU5CT_IO6ATrust_B1<<database->LU5CT_IO6BCan1Flt_B1<<database->LU5CT_IO6BCan2Flt_B1<<database->LU5CT_IO6BOffLine_B1
                    <<database->LU5CT_IO6BTrust_B1<<database->LU5CT_IO7ACan1Flt_B1<<database->LU5CT_IO7ACan2Flt_B1<<database->LU5CT_IO7AOffLine_B1
                    <<database->LU5CT_IO7ATrust_B1<<database->LU5CT_IO7BCan1Flt_B1<<database->LU5CT_IO7BCan2Flt_B1<<database->LU5CT_IO7BOffLine_B1;
            value1=changeSignalStatus(row1Values);
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"IO板7B为当前工作组"<<"IO板8A can1"<<"IO板8A can2"<<"IO板8A状态"<<"IO板8A为当前工作组"<<"IO板8B can1"<<"IO板8B can2"<<"IO板8B状态"
                    <<"IO板8B为当前工作组"<<"IO板9A can1"<<"IO板9A can2"<<"IO板9A状态"<<"IO板9A为当前工作组"<<"IO板9B can1"<<"IO板9B can2"<<"IO板9B状态";
            row2Values<<database->LU5CT_IO7BTrust_B1<<database->LU5CT_IO8ACan1Flt_B1<<database->LU5CT_IO8ACan2Flt_B1<<database->LU5CT_IO8AOffLine_B1
                    <<database->LU5CT_IO8ATrust_B1<<database->LU5CT_IO8BCan1Flt_B1<<database->LU5CT_IO8BCan2Flt_B1<<database->LU5CT_IO8BOffLine_B1
                    <<database->LU5CT_IO8BTrust_B1<<database->LU5CT_IO9ACan1Flt_B1<<database->LU5CT_IO9ACan2Flt_B1<<database->LU5CT_IO9AOffLine_B1
                    <<database->LU5CT_IO9ATrust_B1<<database->LU5CT_IO9BCan1Flt_B1<<database->LU5CT_IO9BCan2Flt_B1<<database->LU5CT_IO9BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板9B为当前工作组"<<"IO板10A can1"<<"IO板10A can2"<<"IO板10A状态"<<"IO板10A为当前工作组"<<"IO板10B can1"<<"IO板10B can2"<<"IO板10B状态"
                    <<"IO板10B为当前工作组"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--";
            row3Values<<database->LU5CT_IO9BTrust_B1<<database->LU5CT_IO10ACan1Flt_B1<<database->LU5CT_IO10ACan2Flt_B1<<database->LU5CT_IO10AOffLine_B1
                    <<database->LU5CT_IO10ATrust_B1<<database->LU5CT_IO10BCan1Flt_B1<<database->LU5CT_IO10BCan2Flt_B1<<database->LU5CT_IO10BOffLine_B1
                    <<database->LU5CT_IO10BTrust_B1;
            value1=changeSignalStatus(row3Values);
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();
        }
    }
    else if(current_LCU==6)
    {
        if(currentPage_LCU==1)
        {
            row1Names<<"LCU6生命信号"<<"A组电源状态"<<"A组供电状态"<<"CAN1级联通信状态"<<"B组电源状态"<<"B组供电断开"<<"CAN2级联通信状态"<<"通信板状态"
                    <<"通信板can1状态"<<"通信板can2状态"<<"存储板状态"<<"存储板can1状态"<<"存储板can2状态"<<"主控板A can1状态"<<"主控板A can2状态"<<"主控板A输入状态";

            row1Values<<database->LU6CT_PwAFlt_B1<<database->LU6CT_PwAOffA_B1<<database->LU6CT_LcuCan1Flt_B1
                    <<database->LU6CT_PwBFlt_B1<<database->LU6CT_PwBOff_B1<<database->LU6CT_LcuCan2Flt_B1<<database->LU6CT_MVBFlt_B1
                    <<database->LU6CT_MVBCan1Flt_B1<<database->LU6CT_MVBCan2Flt_B1<<database->LU6CT_ETHFlt_B1<<database->LU6CT_ETHCan1Flt_B1
                    <<database->LU6CT_ETHCan2Flt_B1<<database->LU6CT_CtlACan1Flt_B1<<database->LU6CT_CtlACan2Flt_B1<<database->LU6CT_CtlAIptFlt_B1;

            value1=changeSignalStatus(row1Values);
            value1.prepend(QString::number(database->LU6CT_LfSgn_U16));
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"主控板A输出状态"<<"主控板A状态"<<"主控板A为当前工作组"<<"主控板B can1状态"<<"主控板B can2状态"<<"主控板B输入状态"<<"主控板B输出状态"<<"主控板B状态"
                    <<"主控板B为当前工作组"<<"IO板1A can1"<<"IO板1A can2"<<"IO板1A状态"<<"IO板1A为当前工作组"<<"IO板1B can1"<<"IO板1B can2"<<"IO板1B状态";

            row2Values<<database->LU6CT_CtlAOptFlt_B1<<database->LU6CT_CtlAOffLine_B1<<database->LU6CT_CtlATrust_B1<<database->LU6CT_CtlBCan1Flt_B1
                    <<database->LU6CT_CtlBCan2Flt_B1<<database->LU6CT_CtlBIptFlt_B1<<database->LU6CT_CtlBOptFlt_B1<<database->LU6CT_CtlBOffLine_B1
                    <<database->LU6CT_CtlBTrust_B1<<database->LU6CT_IO1ACan1Flt_B1<<database->LU6CT_IO1ACan2Flt_B1<<database->LU6CT_IO1AOffLine_B1
                    <<database->LU6CT_IO1ATrust_B1<<database->LU6CT_IO1BCan1Flt_B1<<database->LU6CT_IO1BCan2Flt_B1<<database->LU6CT_IO1BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板1B为当前工作组"<<"IO板2A can1"<<"IO板2A can2"<<"IO板2A状态"<<"IO板2A为当前工作组"<<"IO板2B can1"<<"IO板2B can2"<<"IO板2B状态"
                    <<"IO板2B为当前工作组"<<"IO板3A can1"<<"IO板3A can2"<<"IO板3A状态"<<"IO板3A为当前工作组"<<"IO板3B can1"<<"IO板3B can2"<<"IO板3B状态";

            row3Values<<database->LU6CT_IO1BTrust_B1<<database->LU6CT_IO2ACan1Flt_B1<<database->LU6CT_IO2ACan2Flt_B1<<database->LU6CT_IO2AOffLine_B1
                    <<database->LU6CT_IO2ATrust_B1<<database->LU6CT_IO2BCan1Flt_B1<<database->LU6CT_IO2BCan2Flt_B1<<database->LU6CT_IO2BOffLine_B1
                    <<database->LU6CT_IO2BTrust_B1<<database->LU6CT_IO3ACan1Flt_B1<<database->LU6CT_IO3ACan2Flt_B1<<database->LU6CT_IO3AOffLine_B1
                    <<database->LU6CT_IO3ATrust_B1<<database->LU6CT_IO3BCan1Flt_B1<<database->LU6CT_IO3BCan2Flt_B1<<database->LU6CT_IO3BOffLine_B1;
            value1=changeSignalStatus(row3Values);
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<"IO板3B为当前工作组"<<"IO板4A can1"<<"IO板4A can2"<<"IO板4A状态"<<"IO板4A为当前工作组"<<"IO板4B can1"<<"IO板4B can2"<<"IO板4B状态"
                    <<"IO板4B为当前工作组"<<"IO板5A can1"<<"IO板5A can2"<<"IO板5A状态"<<"IO板5A为当前工作组"<<"IO板5B can1"<<"IO板5B can2"<<"IO板5B状态";
            row4Values<<database->LU6CT_IO3BTrust_B1<<database->LU6CT_IO4ACan1Flt_B1<<database->LU6CT_IO4ACan2Flt_B1<<database->LU6CT_IO4AOffLine_B1
                    <<database->LU6CT_IO4ATrust_B1<<database->LU6CT_IO4BCan1Flt_B1<<database->LU6CT_IO4BCan2Flt_B1<<database->LU6CT_IO4BOffLine_B1
                    <<database->LU6CT_IO4BTrust_B1<<database->LU6CT_IO5ACan1Flt_B1<<database->LU6CT_IO5ACan2Flt_B1<<database->LU6CT_IO5AOffLine_B1
                    <<database->LU6CT_IO5ATrust_B1<<database->LU6CT_IO5BCan1Flt_B1<<database->LU6CT_IO5BCan2Flt_B1<<database->LU6CT_IO5BOffLine_B1;
            value1=changeSignalStatus(row4Values);
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();

        }
        else if(currentPage_LCU==2)
        {
            row1Names<<"IO板5B为当前工作组"<<"IO板6A can1"<<"IO板6A can2"<<"IO板6A状态"<<"IO板6A为当前工作组"<<"IO板6B can1"<<"IO板6B can2"<<"IO板6B状态"
                    <<"IO板6B为当前工作组"<<"IO板7A can1"<<"IO板7A can2"<<"IO板7A状态"<<"IO板7A为当前工作组"<<"IO板7B can1"<<"IO板7B can2"<<"IO板7B状态";
            row1Values<<database->LU6CT_IO5BTrust_B1<<database->LU6CT_IO6ACan1Flt_B1<<database->LU6CT_IO6ACan2Flt_B1<<database->LU6CT_IO6AOffLine_B1
                    <<database->LU6CT_IO6ATrust_B1<<database->LU6CT_IO6BCan1Flt_B1<<database->LU6CT_IO6BCan2Flt_B1<<database->LU6CT_IO6BOffLine_B1
                    <<database->LU6CT_IO6BTrust_B1<<database->LU6CT_IO7ACan1Flt_B1<<database->LU6CT_IO7ACan2Flt_B1<<database->LU6CT_IO7AOffLine_B1
                    <<database->LU6CT_IO7ATrust_B1<<database->LU6CT_IO7BCan1Flt_B1<<database->LU6CT_IO7BCan2Flt_B1<<database->LU6CT_IO7BOffLine_B1;
            value1=changeSignalStatus(row1Values);
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"IO板7B为当前工作组"<<"IO板8A can1"<<"IO板8A can2"<<"IO板8A状态"<<"IO板8A为当前工作组"<<"IO板8B can1"<<"IO板8B can2"<<"IO板8B状态"
                    <<"IO板8B为当前工作组"<<"IO板9A can1"<<"IO板9A can2"<<"IO板9A状态"<<"IO板9A为当前工作组"<<"IO板9B can1"<<"IO板9B can2"<<"IO板9B状态";
            row2Values<<database->LU6CT_IO7BTrust_B1<<database->LU6CT_IO8ACan1Flt_B1<<database->LU6CT_IO8ACan2Flt_B1<<database->LU6CT_IO8AOffLine_B1
                    <<database->LU6CT_IO8ATrust_B1<<database->LU6CT_IO8BCan1Flt_B1<<database->LU6CT_IO8BCan2Flt_B1<<database->LU6CT_IO8BOffLine_B1
                    <<database->LU6CT_IO8BTrust_B1<<database->LU6CT_IO9ACan1Flt_B1<<database->LU6CT_IO9ACan2Flt_B1<<database->LU6CT_IO9AOffLine_B1
                    <<database->LU6CT_IO9ATrust_B1<<database->LU6CT_IO9BCan1Flt_B1<<database->LU6CT_IO9BCan2Flt_B1<<database->LU6CT_IO9BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板9B为当前工作组"<<"IO板10A can1"<<"IO板10A can2"<<"IO板10A状态"<<"IO板10A为当前工作组"<<"IO板10B can1"<<"IO板10B can2"<<"IO板10B状态"
                    <<"IO板10B为当前工作组"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--";
            row3Values<<database->LU6CT_IO9BTrust_B1<<database->LU6CT_IO10ACan1Flt_B1<<database->LU6CT_IO10ACan2Flt_B1<<database->LU6CT_IO10AOffLine_B1
                    <<database->LU6CT_IO10ATrust_B1<<database->LU6CT_IO10BCan1Flt_B1<<database->LU6CT_IO10BCan2Flt_B1<<database->LU6CT_IO10BOffLine_B1
                    <<database->LU6CT_IO10BTrust_B1;
            value1=changeSignalStatus(row3Values);
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();
        }
    }
    else if(current_LCU==7)
    {
        if(currentPage_LCU==1)
        {
            row1Names<<"LCU7生命信号"<<"A组电源状态"<<"A组供电状态"<<"CAN1级联通信状态"<<"B组电源状态"<<"B组供电断开"<<"CAN2级联通信状态"<<"通信板状态"
                    <<"通信板can1状态"<<"通信板can2状态"<<"存储板状态"<<"存储板can1状态"<<"存储板can2状态"<<"主控板A can1状态"<<"主控板A can2状态"<<"主控板A输入状态";

            row1Values<<database->LU7CT_PwAFlt_B1<<database->LU7CT_PwAOffA_B1<<database->LU7CT_LcuCan1Flt_B1
                    <<database->LU7CT_PwBFlt_B1<<database->LU7CT_PwBOff_B1<<database->LU7CT_LcuCan2Flt_B1<<database->LU7CT_MVBFlt_B1
                    <<database->LU7CT_MVBCan1Flt_B1<<database->LU7CT_MVBCan2Flt_B1<<database->LU7CT_ETHFlt_B1<<database->LU7CT_ETHCan1Flt_B1
                    <<database->LU7CT_ETHCan2Flt_B1<<database->LU7CT_CtlACan1Flt_B1<<database->LU7CT_CtlACan2Flt_B1<<database->LU7CT_CtlAIptFlt_B1;

            value1=changeSignalStatus(row1Values);
            value1.prepend(QString::number(database->LU7CT_LfSgn_U16));
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"主控板A输出状态"<<"主控板A状态"<<"主控板A为当前工作组"<<"主控板B can1状态"<<"主控板B can2状态"<<"主控板B输入状态"<<"主控板B输出状态"<<"主控板B状态"
                    <<"主控板B为当前工作组"<<"IO板1A can1"<<"IO板1A can2"<<"IO板1A状态"<<"IO板1A为当前工作组"<<"IO板1B can1"<<"IO板1B can2"<<"IO板1B状态";

            row2Values<<database->LU7CT_CtlAOptFlt_B1<<database->LU7CT_CtlAOffLine_B1<<database->LU7CT_CtlATrust_B1<<database->LU7CT_CtlBCan1Flt_B1
                    <<database->LU7CT_CtlBCan2Flt_B1<<database->LU7CT_CtlBIptFlt_B1<<database->LU7CT_CtlBOptFlt_B1<<database->LU7CT_CtlBOffLine_B1
                    <<database->LU7CT_CtlBTrust_B1<<database->LU7CT_IO1ACan1Flt_B1<<database->LU7CT_IO1ACan2Flt_B1<<database->LU7CT_IO1AOffLine_B1
                    <<database->LU7CT_IO1ATrust_B1<<database->LU7CT_IO1BCan1Flt_B1<<database->LU7CT_IO1BCan2Flt_B1<<database->LU7CT_IO1BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板1B为当前工作组"<<"IO板2A can1"<<"IO板2A can2"<<"IO板2A状态"<<"IO板2A为当前工作组"<<"IO板2B can1"<<"IO板2B can2"<<"IO板2B状态"
                    <<"IO板2B为当前工作组"<<"IO板3A can1"<<"IO板3A can2"<<"IO板3A状态"<<"IO板3A为当前工作组"<<"IO板3B can1"<<"IO板3B can2"<<"IO板3B状态";

            row3Values<<database->LU7CT_IO1BTrust_B1<<database->LU7CT_IO2ACan1Flt_B1<<database->LU7CT_IO2ACan2Flt_B1<<database->LU7CT_IO2AOffLine_B1
                    <<database->LU7CT_IO2ATrust_B1<<database->LU7CT_IO2BCan1Flt_B1<<database->LU7CT_IO2BCan2Flt_B1<<database->LU7CT_IO2BOffLine_B1
                    <<database->LU7CT_IO2BTrust_B1<<database->LU7CT_IO3ACan1Flt_B1<<database->LU7CT_IO3ACan2Flt_B1<<database->LU7CT_IO3AOffLine_B1
                    <<database->LU7CT_IO3ATrust_B1<<database->LU7CT_IO3BCan1Flt_B1<<database->LU7CT_IO3BCan2Flt_B1<<database->LU7CT_IO3BOffLine_B1;
            value1=changeSignalStatus(row3Values);
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<"IO板3B为当前工作组"<<"IO板4A can1"<<"IO板4A can2"<<"IO板4A状态"<<"IO板4A为当前工作组"<<"IO板4B can1"<<"IO板4B can2"<<"IO板4B状态"
                    <<"IO板4B为当前工作组"<<"IO板5A can1"<<"IO板5A can2"<<"IO板5A状态"<<"IO板5A为当前工作组"<<"IO板5B can1"<<"IO板5B can2"<<"IO板5B状态";
            row4Values<<database->LU7CT_IO3BTrust_B1<<database->LU7CT_IO4ACan1Flt_B1<<database->LU7CT_IO4ACan2Flt_B1<<database->LU7CT_IO4AOffLine_B1
                    <<database->LU7CT_IO4ATrust_B1<<database->LU7CT_IO4BCan1Flt_B1<<database->LU7CT_IO4BCan2Flt_B1<<database->LU7CT_IO4BOffLine_B1
                    <<database->LU7CT_IO4BTrust_B1<<database->LU7CT_IO5ACan1Flt_B1<<database->LU7CT_IO5ACan2Flt_B1<<database->LU7CT_IO5AOffLine_B1
                    <<database->LU7CT_IO5ATrust_B1<<database->LU7CT_IO5BCan1Flt_B1<<database->LU7CT_IO5BCan2Flt_B1<<database->LU7CT_IO5BOffLine_B1;
            value1=changeSignalStatus(row4Values);
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();

        }
        else if(currentPage_LCU==2)
        {
            row1Names<<"IO板5B为当前工作组"<<"IO板6A can1"<<"IO板6A can2"<<"IO板6A状态"<<"IO板6A为当前工作组"<<"IO板6B can1"<<"IO板6B can2"<<"IO板6B状态"
                    <<"IO板6B为当前工作组"<<"IO板7A can1"<<"IO板7A can2"<<"IO板7A状态"<<"IO板7A为当前工作组"<<"IO板7B can1"<<"IO板7B can2"<<"IO板7B状态";
            row1Values<<database->LU7CT_IO5BTrust_B1<<database->LU7CT_IO6ACan1Flt_B1<<database->LU7CT_IO6ACan2Flt_B1<<database->LU7CT_IO6AOffLine_B1
                    <<database->LU7CT_IO6ATrust_B1<<database->LU7CT_IO6BCan1Flt_B1<<database->LU7CT_IO6BCan2Flt_B1<<database->LU7CT_IO6BOffLine_B1
                    <<database->LU7CT_IO6BTrust_B1<<database->LU7CT_IO7ACan1Flt_B1<<database->LU7CT_IO7ACan2Flt_B1<<database->LU7CT_IO7AOffLine_B1
                    <<database->LU7CT_IO7ATrust_B1<<database->LU7CT_IO7BCan1Flt_B1<<database->LU7CT_IO7BCan2Flt_B1<<database->LU7CT_IO7BOffLine_B1;
            value1=changeSignalStatus(row1Values);
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"IO板7B为当前工作组"<<"IO板8A can1"<<"IO板8A can2"<<"IO板8A状态"<<"IO板8A为当前工作组"<<"IO板8B can1"<<"IO板8B can2"<<"IO板8B状态"
                    <<"IO板8B为当前工作组"<<"IO板9A can1"<<"IO板9A can2"<<"IO板9A状态"<<"IO板9A为当前工作组"<<"IO板9B can1"<<"IO板9B can2"<<"IO板9B状态";
            row2Values<<database->LU7CT_IO7BTrust_B1<<database->LU7CT_IO8ACan1Flt_B1<<database->LU7CT_IO8ACan2Flt_B1<<database->LU7CT_IO8AOffLine_B1
                    <<database->LU7CT_IO8ATrust_B1<<database->LU7CT_IO8BCan1Flt_B1<<database->LU7CT_IO8BCan2Flt_B1<<database->LU7CT_IO8BOffLine_B1
                    <<database->LU7CT_IO8BTrust_B1<<database->LU7CT_IO9ACan1Flt_B1<<database->LU7CT_IO9ACan2Flt_B1<<database->LU7CT_IO9AOffLine_B1
                    <<database->LU7CT_IO9ATrust_B1<<database->LU7CT_IO9BCan1Flt_B1<<database->LU7CT_IO9BCan2Flt_B1<<database->LU7CT_IO9BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板9B为当前工作组"<<"IO板10A can1"<<"IO板10A can2"<<"IO板10A状态"<<"IO板10A为当前工作组"<<"IO板10B can1"<<"IO板10B can2"<<"IO板10B状态"
                    <<"IO板10B为当前工作组"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--";
            row3Values<<database->LU7CT_IO9BTrust_B1<<database->LU7CT_IO10ACan1Flt_B1<<database->LU7CT_IO10ACan2Flt_B1<<database->LU7CT_IO10AOffLine_B1
                    <<database->LU7CT_IO10ATrust_B1<<database->LU7CT_IO10BCan1Flt_B1<<database->LU7CT_IO10BCan2Flt_B1<<database->LU7CT_IO10BOffLine_B1
                    <<database->LU7CT_IO10BTrust_B1;
            value1=changeSignalStatus(row3Values);
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();
        }
    }
    else if(current_LCU==8)
    {
        if(currentPage_LCU==1)
        {
            row1Names<<"LCU8生命信号"<<"A组电源状态"<<"A组供电状态"<<"CAN1级联通信状态"<<"B组电源状态"<<"B组供电断开"<<"CAN2级联通信状态"<<"通信板状态"
                    <<"通信板can1状态"<<"通信板can2状态"<<"存储板状态"<<"存储板can1状态"<<"存储板can2状态"<<"主控板A can1状态"<<"主控板A can2状态"<<"主控板A输入状态";

            row1Values<<database->LU8CT_PwAFlt_B1<<database->LU8CT_PwAOffA_B1<<database->LU8CT_LcuCan1Flt_B1
                    <<database->LU8CT_PwBFlt_B1<<database->LU8CT_PwBOff_B1<<database->LU8CT_LcuCan2Flt_B1<<database->LU8CT_MVBFlt_B1
                    <<database->LU8CT_MVBCan1Flt_B1<<database->LU8CT_MVBCan2Flt_B1<<database->LU8CT_ETHFlt_B1<<database->LU8CT_ETHCan1Flt_B1
                    <<database->LU8CT_ETHCan2Flt_B1<<database->LU8CT_CtlACan1Flt_B1<<database->LU8CT_CtlACan2Flt_B1<<database->LU8CT_CtlAIptFlt_B1;

            value1=changeSignalStatus(row1Values);
            value1.prepend(QString::number(database->LU8CT_LfSgn_U16));
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"主控板A输出状态"<<"主控板A状态"<<"主控板A为当前工作组"<<"主控板B can1状态"<<"主控板B can2状态"<<"主控板B输入状态"<<"主控板B输出状态"<<"主控板B状态"
                    <<"主控板B为当前工作组"<<"IO板1A can1"<<"IO板1A can2"<<"IO板1A状态"<<"IO板1A为当前工作组"<<"IO板1B can1"<<"IO板1B can2"<<"IO板1B状态";

            row2Values<<database->LU8CT_CtlAOptFlt_B1<<database->LU8CT_CtlAOffLine_B1<<database->LU8CT_CtlATrust_B1<<database->LU8CT_CtlBCan1Flt_B1
                    <<database->LU8CT_CtlBCan2Flt_B1<<database->LU8CT_CtlBIptFlt_B1<<database->LU8CT_CtlBOptFlt_B1<<database->LU8CT_CtlBOffLine_B1
                    <<database->LU8CT_CtlBTrust_B1<<database->LU8CT_IO1ACan1Flt_B1<<database->LU8CT_IO1ACan2Flt_B1<<database->LU8CT_IO1AOffLine_B1
                    <<database->LU8CT_IO1ATrust_B1<<database->LU8CT_IO1BCan1Flt_B1<<database->LU8CT_IO1BCan2Flt_B1<<database->LU8CT_IO1BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板1B为当前工作组"<<"IO板2A can1"<<"IO板2A can2"<<"IO板2A状态"<<"IO板2A为当前工作组"<<"IO板2B can1"<<"IO板2B can2"<<"IO板2B状态"
                    <<"IO板2B为当前工作组"<<"IO板3A can1"<<"IO板3A can2"<<"IO板3A状态"<<"IO板3A为当前工作组"<<"IO板3B can1"<<"IO板3B can2"<<"IO板3B状态";

            row3Values<<database->LU8CT_IO1BTrust_B1<<database->LU8CT_IO2ACan1Flt_B1<<database->LU8CT_IO2ACan2Flt_B1<<database->LU8CT_IO2AOffLine_B1
                    <<database->LU8CT_IO2ATrust_B1<<database->LU8CT_IO2BCan1Flt_B1<<database->LU8CT_IO2BCan2Flt_B1<<database->LU8CT_IO2BOffLine_B1
                    <<database->LU8CT_IO2BTrust_B1<<database->LU8CT_IO3ACan1Flt_B1<<database->LU8CT_IO3ACan2Flt_B1<<database->LU8CT_IO3AOffLine_B1
                    <<database->LU8CT_IO3ATrust_B1<<database->LU8CT_IO3BCan1Flt_B1<<database->LU8CT_IO3BCan2Flt_B1<<database->LU8CT_IO3BOffLine_B1;
            value1=changeSignalStatus(row3Values);
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<"IO板3B为当前工作组"<<"IO板4A can1"<<"IO板4A can2"<<"IO板4A状态"<<"IO板4A为当前工作组"<<"IO板4B can1"<<"IO板4B can2"<<"IO板4B状态"
                    <<"IO板4B为当前工作组"<<"IO板5A can1"<<"IO板5A can2"<<"IO板5A状态"<<"IO板5A为当前工作组"<<"IO板5B can1"<<"IO板5B can2"<<"IO板5B状态";
            row4Values<<database->LU8CT_IO3BTrust_B1<<database->LU8CT_IO4ACan1Flt_B1<<database->LU8CT_IO4ACan2Flt_B1<<database->LU8CT_IO4AOffLine_B1
                    <<database->LU8CT_IO4ATrust_B1<<database->LU8CT_IO4BCan1Flt_B1<<database->LU8CT_IO4BCan2Flt_B1<<database->LU8CT_IO4BOffLine_B1
                    <<database->LU8CT_IO4BTrust_B1<<database->LU8CT_IO5ACan1Flt_B1<<database->LU8CT_IO5ACan2Flt_B1<<database->LU8CT_IO5AOffLine_B1
                    <<database->LU8CT_IO5ATrust_B1<<database->LU8CT_IO5BCan1Flt_B1<<database->LU8CT_IO5BCan2Flt_B1<<database->LU8CT_IO5BOffLine_B1;
            value1=changeSignalStatus(row4Values);
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();

        }
        else if(currentPage_LCU==2)
        {
            row1Names<<"IO板5B为当前工作组"<<"IO板6A can1"<<"IO板6A can2"<<"IO板6A状态"<<"IO板6A为当前工作组"<<"IO板6B can1"<<"IO板6B can2"<<"IO板6B状态"
                    <<"IO板6B为当前工作组"<<"IO板7A can1"<<"IO板7A can2"<<"IO板7A状态"<<"IO板7A为当前工作组"<<"IO板7B can1"<<"IO板7B can2"<<"IO板7B状态";
            row1Values<<database->LU8CT_IO5BTrust_B1<<database->LU8CT_IO6ACan1Flt_B1<<database->LU8CT_IO6ACan2Flt_B1<<database->LU8CT_IO6AOffLine_B1
                    <<database->LU8CT_IO6ATrust_B1<<database->LU8CT_IO6BCan1Flt_B1<<database->LU8CT_IO6BCan2Flt_B1<<database->LU8CT_IO6BOffLine_B1
                    <<database->LU8CT_IO6BTrust_B1<<database->LU8CT_IO7ACan1Flt_B1<<database->LU8CT_IO7ACan2Flt_B1<<database->LU8CT_IO7AOffLine_B1
                    <<database->LU8CT_IO7ATrust_B1<<database->LU8CT_IO7BCan1Flt_B1<<database->LU8CT_IO7BCan2Flt_B1<<database->LU8CT_IO7BOffLine_B1;
            value1=changeSignalStatus(row1Values);
            setLCUStatus(lbl_row1_names,row1Names);
            setLCUStatus(lbl_row1_values,value1);
            row1Names.clear();
            row1Values.clear();
            value1.clear();

            row2Names<<"IO板7B为当前工作组"<<"IO板8A can1"<<"IO板8A can2"<<"IO板8A状态"<<"IO板8A为当前工作组"<<"IO板8B can1"<<"IO板8B can2"<<"IO板8B状态"
                    <<"IO板8B为当前工作组"<<"IO板9A can1"<<"IO板9A can2"<<"IO板9A状态"<<"IO板9A为当前工作组"<<"IO板9B can1"<<"IO板9B can2"<<"IO板9B状态";
            row2Values<<database->LU8CT_IO7BTrust_B1<<database->LU8CT_IO8ACan1Flt_B1<<database->LU8CT_IO8ACan2Flt_B1<<database->LU8CT_IO8AOffLine_B1
                    <<database->LU8CT_IO8ATrust_B1<<database->LU8CT_IO8BCan1Flt_B1<<database->LU8CT_IO8BCan2Flt_B1<<database->LU8CT_IO8BOffLine_B1
                    <<database->LU8CT_IO8BTrust_B1<<database->LU8CT_IO9ACan1Flt_B1<<database->LU8CT_IO9ACan2Flt_B1<<database->LU8CT_IO9AOffLine_B1
                    <<database->LU8CT_IO9ATrust_B1<<database->LU8CT_IO9BCan1Flt_B1<<database->LU8CT_IO9BCan2Flt_B1<<database->LU8CT_IO9BOffLine_B1;
            value1=changeSignalStatus(row2Values);
            setLCUStatus(lbl_row2_names,row2Names);
            setLCUStatus(lbl_row2_values,value1);
            row2Names.clear();
            row2Values.clear();
            value1.clear();

            row3Names<<"IO板9B为当前工作组"<<"IO板10A can1"<<"IO板10A can2"<<"IO板10A状态"<<"IO板10A为当前工作组"<<"IO板10B can1"<<"IO板10B can2"<<"IO板10B状态"
                    <<"IO板10B为当前工作组"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--";
            row3Values<<database->LU8CT_IO9BTrust_B1<<database->LU8CT_IO10ACan1Flt_B1<<database->LU8CT_IO10ACan2Flt_B1<<database->LU8CT_IO10AOffLine_B1
                    <<database->LU8CT_IO10ATrust_B1<<database->LU8CT_IO10BCan1Flt_B1<<database->LU8CT_IO10BCan2Flt_B1<<database->LU8CT_IO10BOffLine_B1
                    <<database->LU8CT_IO10BTrust_B1;
            value1=changeSignalStatus(row3Values);
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row3_names,row3Names);
            setLCUStatus(lbl_row3_values,value1);
            row3Names.clear();
            row3Values.clear();
            value1.clear();

            row4Names<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            value1<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE
                    <<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE<<LINE;
            setLCUStatus(lbl_row4_names,row4Names);
            setLCUStatus(lbl_row4_values,value1);
            row4Names.clear();
            row4Values.clear();
            value1.clear();
        }
    }
    else
    {}

}

void MaintainceLCUSubsystemPage::pushButtonPressedEvent()
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
    else if(btnName=="LCU1")
    {
        current_LCU=1;
        currentPage_LCU=1;
        refreshAllButtons();
        ui->LCU1->setStyleSheet(BUTTONPRESS);
    }
    else if(btnName=="LCU2")
    {
        current_LCU=2;
        currentPage_LCU=1;
        refreshAllButtons();
        ui->LCU2->setStyleSheet(BUTTONPRESS);
    }
    else if(btnName=="LCU3")
    {
        current_LCU=3;
        currentPage_LCU=1;
        refreshAllButtons();
        ui->LCU3->setStyleSheet(BUTTONPRESS);
    }
    else if(btnName=="LCU4")
    {
        current_LCU=4;
        currentPage_LCU=1;
        refreshAllButtons();
        ui->LCU4->setStyleSheet(BUTTONPRESS);
    }
    else if(btnName=="LCU5")
    {
        current_LCU=5;
        currentPage_LCU=1;
        refreshAllButtons();
        ui->LCU5->setStyleSheet(BUTTONPRESS);
    }
    else if(btnName=="LCU6")
    {
        current_LCU=6;
        currentPage_LCU=1;
        refreshAllButtons();
        ui->LCU6->setStyleSheet(BUTTONPRESS);
    }
    else if(btnName=="LCU7")
    {
        current_LCU=7;
        currentPage_LCU=1;
        refreshAllButtons();
        ui->LCU7->setStyleSheet(BUTTONPRESS);
    }
    else if(btnName=="LCU8")
    {
        current_LCU=8;
        currentPage_LCU=1;
        refreshAllButtons();
        ui->LCU8->setStyleSheet(BUTTONPRESS);
    }
}

void MaintainceLCUSubsystemPage::refreshAllButtons()
{
    foreach(QPushButton* button,buttonLCUs)
    {
        button->setStyleSheet(BUTTONRELEASE);
    }
}

void MaintainceLCUSubsystemPage::setLCUStatus(QList<QLabel *> lbl, QList<QString> status)
{
    for(int i=0;i<status.size();i++)
    {
        lbl.at(i)->setText(status.at(i));
    }
}

QList<QString> MaintainceLCUSubsystemPage::changeSignalStatus(QList<bool> status)
{
    QList<QString> tem;
    for(int i=0;i<status.size();i++)
    {
        tem<<QString::number(status.at(i));
    }
    return tem;
}

void MaintainceLCUSubsystemPage::on_BTN7_pressed()
{
    if(currentPage_LCU>1)
    {
        currentPage_LCU--;
    }
    else
    {
        currentPage_LCU=1;
    }
}

void MaintainceLCUSubsystemPage::on_BTN8_pressed()
{
    if(currentPage_LCU<2)
    {
        currentPage_LCU++;
    }
    else
    {
        currentPage_LCU=2;
    }

}
