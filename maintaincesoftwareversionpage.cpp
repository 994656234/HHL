#include "maintaincesoftwareversionpage.h"
#include "ui_maintaincesoftwareversionpage.h"
#include "qdebug.h"

#define LINE ""

MaintainceSoftwareVersionPage::MaintainceSoftwareVersionPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceSoftwareVersionPage)
{
    ui->setupUi(this);

    ui->widget->hide();

    doorVersion=new DoorVersionControl(this);
    doorVersion->setGeometry(30,100,doorVersion->width(),doorVersion->height());
    doorVersion->hide();

    riomlcuVersion=new RIOMLCUVersionControl(this);
    riomlcuVersion->setGeometry(30,100,riomlcuVersion->width(),riomlcuVersion->height());
    riomlcuVersion->show();


    currentVersion=TCMS1;

    buttons<<ui->BTN2<<ui->BTN3<<ui->BTN4<<ui->BTN5;
    foreach(QPushButton *button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(pushBottonPressedEvent()));
    }

    line<<ui->lbl_name_1
            <<ui->lbl_1_1<<ui->lbl_1_2<<ui->lbl_1_3<<ui->lbl_1_4<<ui->lbl_name_2
            <<ui->lbl_2_1<<ui->lbl_2_2<<ui->lbl_2_3<<ui->lbl_2_4<<ui->lbl_name_3
            <<ui->lbl_3_1<<ui->lbl_3_2<<ui->lbl_3_3<<ui->lbl_3_4<<ui->lbl_name_4
            <<ui->lbl_4_1<<ui->lbl_4_2<<ui->lbl_4_3<<ui->lbl_4_4<<ui->lbl_name_5
            <<ui->lbl_5_1<<ui->lbl_5_2<<ui->lbl_5_3<<ui->lbl_5_4<<ui->lbl_name_6
            <<ui->lbl_6_1<<ui->lbl_6_2<<ui->lbl_6_3<<ui->lbl_6_4<<ui->lbl_name_7
            <<ui->lbl_7_1<<ui->lbl_7_2<<ui->lbl_7_3<<ui->lbl_7_4<<ui->lbl_name_8
            <<ui->lbl_8_1<<ui->lbl_8_2<<ui->lbl_8_3<<ui->lbl_8_4<<ui->lbl_name_9
            <<ui->lbl_9_1<<ui->lbl_9_2<<ui->lbl_9_3<<ui->lbl_9_4;



}

MaintainceSoftwareVersionPage::~MaintainceSoftwareVersionPage()
{
    delete ui;
}


void MaintainceSoftwareVersionPage::on_BTN1_pressed()
{
    changePage(uVehicleMaintainPage);
}

void MaintainceSoftwareVersionPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void MaintainceSoftwareVersionPage::on_BTN2_pressed()
{

}

void MaintainceSoftwareVersionPage::on_BTN3_pressed()
{

}

void MaintainceSoftwareVersionPage::on_BTN4_pressed()
{

}

void MaintainceSoftwareVersionPage::updatePage()
{

    switch(currentVersion)
    {
    case EDCU:
       {

            break;
        }
    case OTHERS:
        {
            OtherStatus<<"SIV"<<"--"<<"--"<<"--"<<"--"
                       <<"VVVF"<<"--"<<"--"<<"--"<<"--"
                       <<"OBCU"<<"--"<<"--"<<"--"<<"--"
                       <<"走行部"<<"--"<<"--"<<"--"<<"--"
                       <<"FCU"<<"--"<<"--"<<"--"<<"--"
                       <<"GV"<<"--"<<"--"<<"--"<<"--"
                       <<"PCU"<<"--"<<"--"<<"--"<<"--"
                       <<"ACVP"<<"--"<<"--"<<"--"<<"--"
                       <<"受电弓"<<"--"<<"--"<<"--"<<"--";

            for(int i = 0; i<line.size();i++)
            {
                line.at(i)->setText(OtherStatus.at(i));
            }
            OtherStatus.clear();
            break;
        }
    case TCMS1:
        {

            RIOM_LCUStatus
                    <<"CCU"<<"--"<<"--"<<"--"<<"--"
                    <<"ERM"<<"--"<<"--"<<"--"<<"--"
                    <<"HMI"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"
                    <<"GW"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"
                    <<"DI"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"
                    <<"DO"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--"
                    <<"AX"<<"--"<<"--"<<"--"<<"--"<<"--"<<"--";

            riomlcuVersion->updateStatus(RIOM_LCUStatus);
            RIOM_LCUStatus.clear();
            break;
        }
    }
}

void MaintainceSoftwareVersionPage::pushBottonPressedEvent()
{
    QString btnName=((QPushButton*)this->sender())->objectName();
    if(btnName=="BTN2")
    {
        ui->widget->hide();
        doorVersion->hide();
        riomlcuVersion->show();
        currentVersion=TCMS1;

    }
    else if(btnName=="BTN3")
    {
        ui->widget->hide();
        riomlcuVersion->hide();
        doorVersion->show();
        currentVersion=EDCU;
    }
    else if(btnName=="BTN4")
    {
        ui->widget->show();
        riomlcuVersion->hide();
        doorVersion->hide();
        currentVersion=OTHERS;
    }
}

void MaintainceSoftwareVersionPage::updateTCMSStatus(QList<QString> status, QList<QLabel *> labels)
{
    if(status.length()!=labels.length())
    {
        qDebug()<<"TCMS1 status's size is not == labels ="<<status.size();
        return;
    }

    for(int i=0;i<status.size();i++)
    {
        if(""==status.at(i))
        {
            labels.at(i)->setText("--");
        }
        else
        {
            labels.at(i)->setText(status.at(i));
        }
    }
}

QString MaintainceSoftwareVersionPage::turnNumberToQString(unsigned char status)
{
    QString str=QString::number(status/10)+"."+QString::number(status%10);
    return str;

}

QString MaintainceSoftwareVersionPage::turnNumberToQString2(unsigned char status)
{
    QString str=QString::number(status/100)+"."+QString::number((status%100)/10)+"."+QString::number((status%100)%10);
    return str;
}

QString MaintainceSoftwareVersionPage::turnNumberToQStringDoor(unsigned char status1,unsigned char status2)
{
    QString str=QString::number(status1)+"."+QString::number(status2);
    return str;
}

QString MaintainceSoftwareVersionPage::turnNumberToQStringSIV(unsigned char status1, unsigned char status2, unsigned char status3, unsigned char status4)
{
    QString str=QString::number(status1)+"."+QString::number(status2)+"."+QString::number(status3)+"."+QString::number(status4);
    return str;
}

QString MaintainceSoftwareVersionPage::turnNumberToQStringLCU(unsigned char status)
{
    QString str=QString::number(status/32)+"."+QString::number(status%32);
    return str;
}
QString MaintainceSoftwareVersionPage::turnNumberToQStringDCU(unsigned short int status)
{
    QString str;
//    str = QString::number(status/256/8)+"."+
//          QString::number(status/256%8)+"."+
//          QString::number(status%256/16)+"."+
//          QString::number(status%256/16);
    str=QString::number(status/1000)+"."+QString::number(status%1000/100)+"."+QString::number(status%1000%100/10)+"."+QString::number(status%1000%100%10);
   // str = QString::number(status/10000)+"."+QString::number(status%10000/1000)+"."+QString::number(status%10000%1000/100)+"."+QString::number(status%10000%1000%100/10)+"."+QString::number(status%10000%1000%100%10);
    return str;
}


QString MaintainceSoftwareVersionPage::turnNumberToQStringHVAC(unsigned char status1,unsigned char status2)
{
    QString temp;
    if(status2<10)
    {
        temp="0"+QString::number(status2);
    }
    else
    {
        temp=QString::number(status2);
    }

    QString str=QString::number(status1)+"."+temp;
    return str;
}
