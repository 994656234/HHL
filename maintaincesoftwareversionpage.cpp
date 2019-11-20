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
            <<ui->lbl_2_1<<ui->lbl_2_2<<ui->lbl_2_3<<ui->lbl_2_4<<ui->lbl_2_5<<ui->lbl_2_6<<ui->lbl_name_3
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
        doorStatussignal<<doorStatus(database->EDCU1_2CT_DOOR276_U16)<<doorStatus(database->EDCU1_2CT_DOOR277_U16)<<doorStatus(database->EDCU1_2CT_DOOR278_U16)
                 <<doorStatus(database->EDCU1_2CT_DOOR279_U16)<<doorStatus(database->EDCU1_2CT_DOOR280_U16)<<doorStatus(database->EDCU1_2CT_DOOR281_U16)

                <<doorStatus(database->EDCU3_4CT_DOOR276_U16)<<doorStatus(database->EDCU3_4CT_DOOR277_U16)<<doorStatus(database->EDCU3_4CT_DOOR278_U16)
                <<doorStatus(database->EDCU3_4CT_DOOR279_U16)<<doorStatus(database->EDCU3_4CT_DOOR280_U16)<<doorStatus(database->EDCU3_4CT_DOOR281_U16)

                <<doorStatus(database->EDCU5_6CT_DOOR276_U16)<<doorStatus(database->EDCU5_6CT_DOOR277_U16)<<doorStatus(database->EDCU5_6CT_DOOR278_U16)
                <<doorStatus(database->EDCU5_6CT_DOOR279_U16)<<doorStatus(database->EDCU5_6CT_DOOR280_U16)<<doorStatus(database->EDCU5_6CT_DOOR281_U16)

               <<doorStatus(database->EDCU7_8CT_DOOR276_U16)<<doorStatus(database->EDCU7_8CT_DOOR277_U16)<<doorStatus(database->EDCU7_8CT_DOOR278_U16)
               <<doorStatus(database->EDCU7_8CT_DOOR279_U16)<<doorStatus(database->EDCU7_8CT_DOOR280_U16)<<doorStatus(database->EDCU7_8CT_DOOR281_U16);
            doorVersion->updateStatus(doorStatussignal);
            doorStatussignal.clear();
            break;
        }
    case OTHERS:
        {
            OtherStatus<<"SIV"<<QString::number(database->ACU1CT_IuiDSPRevision_U16)<<QString::number(database->ACU1CT_IuiPPCRevision_U16)<<QString::number(database->ACU2CT_IuiPPCRevision_U16)<<QString::number(database->ACU2CT_IuiPPCRevision_U16)
                       <<"VVVF"<<TCUVersion(database->TCU1CT_IuiLglSWRevision_U16,database->TCU2CT_IuiInvSWRevision_U16,database->TCU3CT_IuiAdhSWRevision_U16)
                         <<TCUVersion(database->TCU2CT_IuiLglSWRevision_U16,database->TCU2CT_IuiInvSWRevision_U16,database->TCU3CT_IuiAdhSWRevision_U16)
                           <<TCUVersion(database->TCU3CT_IuiLglSWRevision_U16,database->TCU2CT_IuiInvSWRevision_U16,database->TCU3CT_IuiAdhSWRevision_U16)
                             <<TCUVersion(database->TCU4CT_IuiLglSWRevision_U16,database->TCU2CT_IuiInvSWRevision_U16,database->TCU3CT_IuiAdhSWRevision_U16)
                               <<TCUVersion(database->TCU5CT_IuiLglSWRevision_U16,database->TCU2CT_IuiInvSWRevision_U16,database->TCU3CT_IuiAdhSWRevision_U16)
                                 <<TCUVersion(database->TCU6CT_IuiLglSWRevision_U16,database->TCU2CT_IuiInvSWRevision_U16,database->TCU3CT_IuiAdhSWRevision_U16)
                       <<"OBCU"<<"--"<<"--"<<"--"<<"--"
                       <<"走行部"<<"--"<<"--"<<"--"<<"--"
                       <<"FCU"<<QString::number(database->FCU1CT_usSWRev_B1)<<"--"<<"--"<<QString::number(database->FCU2CT_usSWRev_B1)
                       <<"GV"<<turnNumberToQStringDoor(database->B1CT_SWVerHigh_U8,database->B1CT_SWVerLow_U8)<<"--"<<"--"<<turnNumberToQStringDoor(database->B2CT_SWVerHigh_U8,database->B2CT_SWVerLow_U8)
                       <<"PCU"<<turnNumberToQStringPIS(database->PIS1CT_P178_B1,database->PIS1CT_P179_B1,database->PIS1CT_P180_B1)<<"--"<<"--"<<turnNumberToQStringPIS(database->PIS2CT_P178_B1,database->PIS2CT_P179_B1,database->PIS2CT_P180_B1)
                       <<"ACVP"<<QString::number(database->ACVP1CT_IuiHVACSWVersion_U16)<<QString::number(database->ACVP2CT_IuiHVACSWVersion_U16)<<QString::number(database->ACVP3CT_IuiHVACSWVersion_U16)<<QString::number(database->ACVP4CT_IuiHVACSWVersion_U16)
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
                    <<"CCU"<<turnNumberToQString2(database->CTD_CCU1SWVer_U8)<<"--"<<"--"<<turnNumberToQString2(database->CTD_CCU2SWVer_U8)
                    <<"ERM"<<QString::number(database->E1CT_ERMSWVer_U8/16)+"."+QString::number(database->E1CT_ERMSWVer_U8%16)<<"--"<<"--"<<QString::number(database->E2CT_ERMSWVer_U8/16)+"."+QString::number(database->E2CT_ERMSWVer_U8%16)
                    <<"HMI"<<turnNumberToQStringDoor(database->D1CT_HMISWVerH_U8,database->D1CT_HMISWVerL_U8)<<"--"<<"--"<<"--"<<"--"<<turnNumberToQStringDoor(database->D2CT_HMISWVerH_U8,database->D2CT_HMISWVerL_U8)
                    <<"GW"<<QString::number(database->RM1CT_GWVersion_U8)<<QString::number(database->RM2CT_GWVersion_U8)<<QString::number(database->RM3CT_GWVersion_U8)<<QString::number(database->RM6CT_GWVersion_U8)<<QString::number(database->RM5CT_GWVersion_U8)<<QString::number(database->RM4CT_GWVersion_U8)
                    <<"DI"<<QString::number(database->RM1CT_DIVersion_U8)<<QString::number(database->RM2CT_DIVersion_U8)<<QString::number(database->RM3CT_DIVersion_U8)<<QString::number(database->RM6CT_DIVersion_U8)<<QString::number(database->RM5CT_DIVersion_U8)<<QString::number(database->RM4CT_DIVersion_U8)
                    <<"DO"<<QString::number(database->RM1CT_DOVersion_U8)<<QString::number(database->RM2CT_DOVersion_U8)<<QString::number(database->RM3CT_DOVersion_U8)<<QString::number(database->RM6CT_DOVersion_U8)<<QString::number(database->RM5CT_DOVersion_U8)<<QString::number(database->RM4CT_DOVersion_U8)
                    <<"AX"<<QString::number(database->RM1CT_AXVersion_U8)<<QString::number(database->RM2CT_AXVersion_U8)<<"--"<<"--"<<QString::number(database->RM5CT_AXVersion_U8)<<QString::number(database->RM4CT_AXVersion_U8);

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

QString MaintainceSoftwareVersionPage::turnNumberToQStringPIS(unsigned char status1, unsigned char status2, unsigned char status3)
{
    QString str=QString::number(status1)+"."+QString::number(status2)+"."+QString::number(status3);
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

    str=QString::number(status/1000)+"."+QString::number(status%1000/100)+"."+QString::number(status%1000%100/10)+"."+QString::number(status%1000%100%10);
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


QString MaintainceSoftwareVersionPage::doorStatus(unsigned short status)
{
    QString temp=QString::number(status/256)+"."+QString::number(status%256);
    return temp;
}


QString MaintainceSoftwareVersionPage::TCUVersion(unsigned short status1, unsigned short status2, unsigned short status3)
{
    QString temp=QString::number(status1)+"."+QString::number(status2)+"."+QString::number(status3);
    return temp;
}

