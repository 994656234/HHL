#include "vehiclesetairconditionpage.h"
#include "ui_vehiclesetairconditionpage.h"
#include "qdebug.h"


#define BUTTONPRESS "border-top:0px solid rgb(19,20,87);color: rgb(255, 255, 255);background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));font:16px \"微软雅黑\";"
#define BUTTONRELEASE "border-top:3px solid rgb(19,20,87);color: rgb(255, 255, 255);border-bottom:3px solid rgb(187,188,247);border-left:3px solid qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));border-right:3px solid qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));font:16px \"微软雅黑\";"

#define METROPRESS "background-color: rgb(0, 85, 255);border:1px solid black;font:20px \"微软雅黑\";"
#define METRORELEASE "background-color:rgb(170,170,170);border:1px solid black;font:20px \"微软雅黑\";"


VehicleSetAirConditionPage::VehicleSetAirConditionPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleSetAirConditionPage)
{
    ui->setupUi(this);

    metroButtons<<ui->btn_metro1<<ui->btn_metro2<<ui->btn_metro3<<ui->btn_metro4<<ui->BTN_allMetro;
    foreach(QPushButton *button,metroButtons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(metroBTNPressEvent()));
    }

    modeSignal<<&database->DiCT_HVACAutoCoolMode_B1<<&database->DiCT_HVACAutoWarmMode_B1<<&database->DiCT_HVACVenti_B1
            <<&database->DiCT_HVACEmgcyVenti_B1<<&database->DiCT_HVACStop_B1;
    modeButtons<<ui->BTN_mode_autoCool<<ui->BTN_mode_autoWarm<<ui->BTN_mode_wind<<ui->BTN_mode_Ventilate<<ui->BTN_mode_stop;

    foreach(QPushButton *button,modeButtons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(modeBTNPressEvent()));
    }

    temSignal<<&database->DiCT_Reduce0point5_B1<<&database->DiCT_Add0point5_B1;
    temButtons<<ui->BTN_ne_0_5<<ui->BTN_po_0_5;
    foreach(QPushButton *button,temButtons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(temBTNPressEvent()));
    }

    m_setTemp = 0;
    m_modeNum = 0;
    m_temNum = 0;
    m_setTempFlag = 5;

    ui->lbl_cab1_active->hide();
    ui->lbl_cab2_active->hide();

}

VehicleSetAirConditionPage::~VehicleSetAirConditionPage()
{
    delete ui;
}

void VehicleSetAirConditionPage::on_BTN1_pressed()
{
    changePage(uVehicleSetPage);
}

void VehicleSetAirConditionPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void VehicleSetAirConditionPage::updatePage()
{

    //司机室激活
    if(database->CTD_MCTActive_B1)
    {
        ui->lbl_cab1_active->show();
    }
    else
    {
        ui->lbl_cab1_active->hide();
    }

    if(database->CTD_MC2Active_B1)
    {
        ui->lbl_cab2_active->show();
    }
    else
    {
        ui->lbl_cab2_active->hide();
    }


    //客室温度&目标温度
    if(database->CTD_ACTOLINE_B1)
    {
        ui->lbl_tmp1->setText(QString::number(database->ACVP1CT_IusSalTemp_U8,'f',1));
        ui->lbl_settmp1->setText(QString::number(database->ACVP1CT_IusTargTemp_U8,'f',1));
    }
    else
    {
        ui->lbl_tmp1->setText("--");
        ui->lbl_settmp1->setText("--");
    }

    if(database->CTD_AC2OLINE_B1)
    {
        ui->lbl_tmp2->setText(QString::number(database->ACVP2CT_IusSalTemp_U8,'f',1));
        ui->lbl_settmp2->setText(QString::number(database->ACVP2CT_IusTargTemp_U8,'f',1));
    }
    else
    {
        ui->lbl_tmp2->setText("--");
        ui->lbl_settmp2->setText("--");
    }

    if(database->CTD_AC3OLINE_B1)
    {
        ui->lbl_tmp3->setText(QString::number(database->ACVP3CT_IusSalTemp_U8,'f',1));
        ui->lbl_settmp3->setText(QString::number(database->ACVP3CT_IusTargTemp_U8,'f',1));
    }
    else
    {
        ui->lbl_tmp3->setText("--");
        ui->lbl_settmp3->setText("--");
    }

    if(database->CTD_AC4OLINE_B1)
    {
        ui->lbl_tmp4->setText(QString::number(database->ACVP4CT_IusSalTemp_U8,'f',1));
        ui->lbl_settmp4->setText(QString::number(database->ACVP4CT_IusTargTemp_U8,'f',1));
    }
    else
    {
        ui->lbl_tmp4->setText("--");
        ui->lbl_settmp4->setText("--");
    }

}


void VehicleSetAirConditionPage::metroBTNPressEvent()
{
    int metroNum= ((QPushButton*)this->sender())->whatsThis().toInt();
    //database->HMiCT_SAVEHVACPosition_U8=metroNum;

    if(metroNum==5)
    {
        for(int i=0;i<5;i++)
        {
            metroButtons.at(i)->setStyleSheet(METROPRESS);
        }
    }
    else
    {
        for(int i=0;i<5;i++)
        {
            metroButtons.at(i)->setStyleSheet(METRORELEASE);
        }
        metroButtons.at(metroNum-1)->setStyleSheet(METROPRESS);
    }


}

void VehicleSetAirConditionPage::modeBTNPressEvent()
{
    m_modeNum=((QPushButton*)this->sender())->whatsThis().toInt()-5;
    for(int i=0;i<5;i++)
    {
        modeButtons.at(i)->setStyleSheet(BUTTONRELEASE);
    }
    ((QPushButton*)this->sender())->setStyleSheet(BUTTONPRESS);
}

void VehicleSetAirConditionPage::temBTNPressEvent()
{

    m_temNum=((QPushButton*)this->sender())->whatsThis().toInt()-13;
    for(int i=0;i<2;i++)
    {              
        temButtons.at(i)->setStyleSheet(BUTTONRELEASE);
    }

    ((QPushButton*)this->sender())->setStyleSheet(BUTTONPRESS);
    if(((QPushButton*)this->sender())->text() == "+")
    {
        if(m_setTemp<2.5)
        {
           m_setTemp+= 0.5;
        }
        if(m_setTempFlag<10)
        {
            m_setTempFlag++;
        }


    }
    if(((QPushButton*)this->sender())->text() == "-")
    {
        if(m_setTemp>-2.5)
        {

            m_setTemp-= 0.5;
        }
        if(m_setTempFlag>0)
        {
            m_setTempFlag--;
        }

    }
    this->ui->tempoffset->setText(QString::number(m_setTemp,10,1));
}

void VehicleSetAirConditionPage::timerEvent(QTimerEvent *e)
{   

    if(e->timerId() == timer_2s[0])
    {
        killTimer(timer_2s[0]);
        modeButtons.at(m_modeNum-1)->setStyleSheet(BUTTONRELEASE);
        *modeSignal.at(m_modeNum-1)=false;
        //m_modeNum = 0;
        ui->BTN_confirm->setStyleSheet(BUTTONRELEASE);
        for(int i=0;i<5;i++)
        {
            modeButtons.at(i)->setDisabled(false);;
        }
        database->DiCT_SetFlagChecker_U8=0x55;


    }
    if(e->timerId() == timer_2s[1])
    {
        killTimer(timer_2s[1]);
        temButtons.at(m_temNum)->setStyleSheet(BUTTONRELEASE);
        switch(m_setTempFlag)
        {
        case 0:
            database->DiCT_Reduce2point5_B1=false;
            break;
        case 1 :
            database->DiCT_Reduce2_B1=false;
            break;
        case 2:
            database->DiCT_Reduce1point5_B1=false;
            break;
        case 3 :
            database->DiCT_Reduce1_B1=false;
            break;
        case 4:
            database->DiCT_Reduce0point5_B1=false;
            break;
        case 5:
            database->DiCT_Add0_B1=false;
            break;
        case 6:
            database->DiCT_Add0point5_B1=false;
            break;
        case 7 :
            database->DiCT_Add1_B1=false;
            break;
        case 8:
            database->DiCT_Add1point5_B1=false;
            break;
        case 9 :
            database->DiCT_Add2_B1=false;
            break;
        case 10:
            database->DiCT_Add2point5_B1=false;
            break;
        default :
                 ;
        }
        ui->BTN_comfirm1->setStyleSheet(BUTTONRELEASE);
        database->DiCT_SetFlagChecker_U8=0x55;

    }

}

void VehicleSetAirConditionPage::on_BTN_confirm_pressed()
{
    if(m_modeNum==0)
        return ;
    ui->BTN_confirm->setStyleSheet(BUTTONPRESS);
    database->DiCT_SetFlagChecker_U8=0xAA;
    *modeSignal.at(m_modeNum-1)=true;
    timer_2s[0] = this->startTimer(2000);
    for(int i=0;i<5;i++)
    {
        modeButtons.at(i)->setDisabled(true);;
    }

}


void VehicleSetAirConditionPage::on_BTN_comfirm1_pressed()
{
    ui->BTN_comfirm1->setStyleSheet(BUTTONPRESS);
    database->DiCT_SetFlagChecker_U8=0XAA;
    switch(m_setTempFlag)
    {
    case 0:
        database->DiCT_Reduce2point5_B1=true;
        break;
    case 1 :
        database->DiCT_Reduce2_B1=true;
        break;
    case 2:
        database->DiCT_Reduce1point5_B1=true;
        break;
    case 3 :
        database->DiCT_Reduce1_B1=true;
        break;
    case 4:
        database->DiCT_Reduce0point5_B1=true;
        break;
    case 5:
        database->DiCT_Add0_B1=true;
        break;
    case 6:
        database->DiCT_Add0point5_B1=true;
        break;
    case 7 :
        database->DiCT_Add1_B1=true;
        break;
    case 8:
        database->DiCT_Add1point5_B1=true;
        break;
    case 9 :
        database->DiCT_Add2_B1=true;
        break;
    case 10:
        database->DiCT_Add2point5_B1=true;
        break;
    default :
             ;
    }
    timer_2s[1] = this->startTimer(2000);

}


void VehicleSetAirConditionPage::hideEvent(QHideEvent *)
{
    killTimer(timer_2s[0]);
        m_modeNum = 0;
        ui->BTN_confirm->setStyleSheet(BUTTONRELEASE);
        for(int i=0;i<modeButtons.size();i++)
        {
            modeButtons.at(i)->setDisabled(false);;
            modeButtons.at(i)->setStyleSheet(BUTTONRELEASE);
            *modeSignal.at(i)=false;
        }
        database->DiCT_SetFlagChecker_U8=0x55;

        killTimer(timer_2s[1]);
        ui->BTN_comfirm1->setStyleSheet(BUTTONRELEASE);
        for(int i=0;i<temButtons.size();i++)
        {
            temButtons.at(i)->setDisabled(false);;
            temButtons.at(i)->setStyleSheet(BUTTONRELEASE);
        }
        database->DiCT_Reduce2point5_B1=false;
        database->DiCT_Reduce2_B1=false;
        database->DiCT_Reduce1point5_B1=false;
        database->DiCT_Reduce1_B1=false;
        database->DiCT_Reduce0point5_B1=false;
        database->DiCT_Add0_B1=false;
        database->DiCT_Add0point5_B1=false;
        database->DiCT_Add1_B1=false;
        database->DiCT_Add1point5_B1=false;
        database->DiCT_Add2_B1=false;
        database->DiCT_Add2point5_B1=false;
}
