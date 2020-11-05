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
        button->setStyleSheet(METROPRESS);
    }

    modeSignal<<&database->DiCT_HVACEmgcyVenti_B1<<&database->DiCT_HVACVenti_B1<<&database->DiCT_HVACAutoCoolMode_B1
             <<&database->DiCT_HVACAutoWarmMode_B1<<&database->DiCT_HVACStop_B1<<&database->HVACWarmStop<<&database->HVACCoolStop;

    modeButtons<<ui->BTN_mode_autoCool<<ui->BTN_mode_autoWarm<<ui->BTN_mode_wind<<ui->BTN_mode_Ventilate<<ui->BTN_mode_stop
              <<ui->BTN_warmstop<<ui->BTN_coolstop;

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
    m_setTempFlag = 2;

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
        ui->lbl_tmp1->setText(QString::number(database->ACVP1CT_IusSalTemp_U8-30,'f',1));
        ui->lbl_settmp1->setText(QString::number(database->ACVP1CT_IusTargTemp_U8,'f',1));
    }
    else
    {
        ui->lbl_tmp1->setText("--");
        ui->lbl_settmp1->setText("--");
    }

    if(database->CTD_AC2OLINE_B1)
    {
        ui->lbl_tmp2->setText(QString::number(database->ACVP2CT_IusSalTemp_U8-30,'f',1));
        ui->lbl_settmp2->setText(QString::number(database->ACVP2CT_IusTargTemp_U8,'f',1));
    }
    else
    {
        ui->lbl_tmp2->setText("--");
        ui->lbl_settmp2->setText("--");
    }

    if(database->CTD_AC3OLINE_B1)
    {
        ui->lbl_tmp3->setText(QString::number(database->ACVP3CT_IusSalTemp_U8-30,'f',1));
        ui->lbl_settmp3->setText(QString::number(database->ACVP3CT_IusTargTemp_U8,'f',1));
    }
    else
    {
        ui->lbl_tmp3->setText("--");
        ui->lbl_settmp3->setText("--");
    }

    if(database->CTD_AC4OLINE_B1)
    {
        ui->lbl_tmp4->setText(QString::number(database->ACVP4CT_IusSalTemp_U8-30,'f',1));
        ui->lbl_settmp4->setText(QString::number(database->ACVP4CT_IusTargTemp_U8,'f',1));
    }
    else
    {
        ui->lbl_tmp4->setText("--");
        ui->lbl_settmp4->setText("--");
    }

    xinFenglbl<<ui->lbl_MC1_1_1<<ui->lbl_MC1_1_2<<ui->lbl_MC1_2_1<<ui->lbl_MC1_2_2;
    huiFenglbl<<ui->lbl_huifeng_MC1_1<<ui->lbl_huifeng_MC1_2;
    xinFengStatus<<database->ACVP1CT_IusFADamperSts11_U8<<database->ACVP1CT_IusFADamperSts12_U8
                   <<database->ACVP1CT_IusFADamperSts21_U8<<database->ACVP1CT_IusFADamperSts22_U8;
    huiFengStatus<<database->ACVP1CT_IusRADamperSts1_U8<<database->ACVP1CT_IusRADamperSts2_U8;
    setXinFengStatus(xinFenglbl,xinFengStatus);
    setHuiFengStatus(huiFenglbl,huiFengStatus);
    xinFengStatus.clear();
    huiFengStatus.clear();
    xinFenglbl.clear();
    huiFenglbl.clear();

    xinFenglbl<<ui->lbl_MP1_1_1<<ui->lbl_MP1_1_2<<ui->lbl_MP1_2_1<<ui->lbl_MP1_2_2;
    huiFenglbl<<ui->lbl_huifeng_MP1_1<<ui->lbl_huifeng_MP1_2;
    xinFengStatus<<database->ACVP2CT_IusFADamperSts11_U8<<database->ACVP2CT_IusFADamperSts12_U8
                   <<database->ACVP2CT_IusFADamperSts21_U8<<database->ACVP2CT_IusFADamperSts22_U8;
    huiFengStatus<<database->ACVP2CT_IusRADamperSts1_U8<<database->ACVP2CT_IusRADamperSts2_U8;
    setXinFengStatus(xinFenglbl,xinFengStatus);
    setHuiFengStatus(huiFenglbl,huiFengStatus);
    xinFengStatus.clear();
    huiFengStatus.clear();
    xinFenglbl.clear();
    huiFenglbl.clear();

    xinFenglbl<<ui->lbl_MP2_1_1<<ui->lbl_MP2_1_2<<ui->lbl_MP2_2_1<<ui->lbl_MP2_2_2;
    huiFenglbl<<ui->lbl_huifeng_MP2_1<<ui->lbl_huifeng_MP2_2;
    xinFengStatus<<database->ACVP3CT_IusFADamperSts11_U8<<database->ACVP3CT_IusFADamperSts12_U8
                   <<database->ACVP3CT_IusFADamperSts21_U8<<database->ACVP3CT_IusFADamperSts22_U8;
    huiFengStatus<<database->ACVP3CT_IusRADamperSts1_U8<<database->ACVP3CT_IusRADamperSts2_U8;
    setXinFengStatus(xinFenglbl,xinFengStatus);
    setHuiFengStatus(huiFenglbl,huiFengStatus);
    xinFengStatus.clear();
    huiFengStatus.clear();
    xinFenglbl.clear();
    huiFenglbl.clear();

    xinFenglbl<<ui->lbl_MC2_1_1<<ui->lbl_MC2_1_2<<ui->lbl_MC2_2_1<<ui->lbl_MC2_2_2;
    huiFenglbl<<ui->lbl_huifeng_MC2_1<<ui->lbl_huifeng_MC2_2;
    xinFengStatus<<database->ACVP4CT_IusFADamperSts11_U8<<database->ACVP4CT_IusFADamperSts12_U8
                   <<database->ACVP4CT_IusFADamperSts21_U8<<database->ACVP4CT_IusFADamperSts22_U8;
    huiFengStatus<<database->ACVP4CT_IusRADamperSts1_U8<<database->ACVP4CT_IusRADamperSts2_U8;
    setXinFengStatus(xinFenglbl,xinFengStatus);
    setHuiFengStatus(huiFenglbl,huiFengStatus);
    xinFengStatus.clear();
    huiFengStatus.clear();
    xinFenglbl.clear();
    huiFenglbl.clear();
}


void VehicleSetAirConditionPage::metroBTNPressEvent()
{
    int metroNum= ((QPushButton*)this->sender())->whatsThis().toInt();
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
    for(int i=0;i<7;i++)
    {
        modeButtons.at(i)->setStyleSheet(BUTTONRELEASE);
        *modeSignal.at(i) = false;
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
        if(m_setTemp<2)
        {
           m_setTemp+= 1;
        }
        if(m_setTempFlag<4)
        {
            m_setTempFlag++;
        }


    }
    if(((QPushButton*)this->sender())->text() == "-")
    {
        if(m_setTemp>-2)
        {

            m_setTemp-= 1;
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
    if(e->timerId() == timerID1)
    {
        killTimer(timerID1);
        if(3 == m_modeNum || 4 == m_modeNum)
        {
            *modeSignal.at(m_modeNum-1)=true;
        }else
        {
            *modeSignal.at(m_modeNum-1)=false;
        }
        ui->BTN_confirm->setStyleSheet(BUTTONRELEASE);
        for(int i=0;i<7;i++)
        {
            modeButtons.at(i)->setDisabled(false);;
        }
        database->DiCT_SetFlagChecker_U8=0x55;
        timerID1=0;
    }

    if(e->timerId() == timerID2)
    {
        killTimer(timerID2);
        temButtons.at(m_temNum)->setStyleSheet(BUTTONRELEASE);
        if(m_setTempFlag==0)
        {
            database->DiCT_Reduce2_B1=false;
        }
        else if(m_setTempFlag==1)
        {
            database->DiCT_Reduce1_B1=false;
        }
        else if(m_setTempFlag==2)
        {
            database->DiCT_Add0_B1=false;
        }
        else if(m_setTempFlag==3)
        {
            database->DiCT_Add1_B1=false;
        }
        else if(m_setTempFlag==4)
        {
            database->DiCT_Add2_B1=false;
        }

//        switch(m_setTempFlag)
//        {

//        case 0 :
//            database->DiCT_Reduce2_B1=false;
//            break;
//        case 1 :
//            database->DiCT_Reduce1_B1=false;
//            break;
//        case 2:
//            database->DiCT_Add0_B1=false;
//            break;
//        case 3 :
//            database->DiCT_Add1_B1=false;
//            break;
//       case 4 :
//            database->DiCT_Add2_B1=false;
//            break;
//        default :
//            ;
//        }
        ui->BTN_comfirm1->setStyleSheet(BUTTONRELEASE);
        database->DiCT_SetFlagChecker_U8=0x55;
        timerID2=0;

    }

}

void VehicleSetAirConditionPage::on_BTN_confirm_pressed()
{
    if(m_modeNum==0)
        return ;
    ui->BTN_confirm->setStyleSheet(BUTTONPRESS);
    database->DiCT_SetFlagChecker_U8=0xAA;
    *modeSignal.at(m_modeNum-1)=true;
    timerID1 = this->startTimer(2000);
    for(int i=0;i<7;i++)
    {
        modeButtons.at(i)->setDisabled(true);;
    }

}


void VehicleSetAirConditionPage::on_BTN_comfirm1_pressed()
{

    ui->BTN_comfirm1->setStyleSheet(BUTTONPRESS);
    database->DiCT_SetFlagChecker_U8=0XAA;
    if(m_setTempFlag==0)
    {
        database->DiCT_Reduce2_B1=true;
    }
    else if(m_setTempFlag==1)
    {
        database->DiCT_Reduce1_B1=true;
    }
    else if(m_setTempFlag==2)
    {
        database->DiCT_Add0_B1=true;
    }
    else if(m_setTempFlag==3)
    {
        database->DiCT_Add1_B1=true;
    }
    else if(m_setTempFlag==4)
    {
        database->DiCT_Add2_B1=true;
    }

    timerID2= this->startTimer(2000);

}


void VehicleSetAirConditionPage::hideEvent(QHideEvent *)
{
        killTimer(timerID1);
        ui->BTN_confirm->setStyleSheet(BUTTONRELEASE);
        for(int i=0;i<modeButtons.size();i++)
        {
            modeButtons.at(i)->setDisabled(false);;
            *modeSignal.at(i)=false;
        }
        database->DiCT_SetFlagChecker_U8=0x55;

        killTimer(timerID2);
        ui->BTN_comfirm1->setStyleSheet(BUTTONRELEASE);
        for(int i=0;i<temButtons.size();i++)
        {
            temButtons.at(i)->setDisabled(false);;
            temButtons.at(i)->setStyleSheet(BUTTONRELEASE);
        }
        database->DiCT_Reduce2_B1=false;
        database->DiCT_Reduce1_B1=false;
        database->DiCT_Add0_B1=false;
        database->DiCT_Add1_B1=false;
        database->DiCT_Add2_B1=false;
}

void VehicleSetAirConditionPage::on_BTN_newwind_open_pressed()
{
    if(ui->BTN_newwind_open->text() == "强制关闭")
    {
        this->ui->BTN_newwind_open->setText("取消强制");
        database->DiCT_NADA_B1 = true;
    }else if(ui->BTN_newwind_open->text() == "取消强制")
    {
        this->ui->BTN_newwind_open->setText("强制关闭");
        database->DiCT_NADA_B1 = false;
    }
}


void VehicleSetAirConditionPage::setXinFengStatus(QList<QLabel *> lbl, QList<unsigned char> status)
{
    if(lbl.length()!=status.length())
    {
        qDebug()<<"空调设置界面新风阀lbl.length！=status.length;";
        return;
    }
    for(int i=0;i<lbl.length();i++)
    {
        if(status.at(i)==1)
        {
            lbl.at(i)->setText("故障");
            lbl.at(i)->setStyleSheet("background-color:red;color:white;");
        }
        else if(status.at(i)==2)
        {
            lbl.at(i)->setText("关闭");
            lbl.at(i)->setStyleSheet("background-color:rgb(0,0,50);color:white;");
        }
        else if(status.at(i)==3)
        {
            lbl.at(i)->setText("全开");
            lbl.at(i)->setStyleSheet("background-color:rgb(0,0,50);color:white;");
        }
        else if(status.at(i)==4)
        {
            lbl.at(i)->setText("2/3");
            lbl.at(i)->setStyleSheet("background-color:rgb(0,0,50);color:white;");
        }
        else if(status.at(i)==5)
        {
            lbl.at(i)->setText("1/3");
            lbl.at(i)->setStyleSheet("background-color:rgb(0,0,50);color:white;");
        }
        else
        {
            lbl.at(i)->setText("--");
            lbl.at(i)->setStyleSheet("background-color:rgb(0,0,50);color:white;");
        }
    }
}

void VehicleSetAirConditionPage::setHuiFengStatus(QList<QLabel *> lbl, QList<unsigned char> status)
{
    if(lbl.length()!=status.length())
    {
        qDebug()<<"空调设置界面回风阀lbl.length!=status.length!";
        return;
    }
    for(int i=0;i<lbl.length();i++)
    {
        if(status.at(i)==1)
        {
            lbl.at(i)->setText("故障");
            lbl.at(i)->setStyleSheet("background-color:red;color:white;");
        }
        else if(status.at(i)==2)
        {
            lbl.at(i)->setText("关");
            lbl.at(i)->setStyleSheet("background-color:rgb(0,0,50);color:white;");
        }
        else if(status.at(i)==3)
        {
            lbl.at(i)->setText("开");
            lbl.at(i)->setStyleSheet("background-color:rgb(0,0,50);color:white;");
        }
        else
        {
            lbl.at(i)->setText("--");
            lbl.at(i)->setStyleSheet("background-color:rgb(0,0,50);color:white;");
        }
    }
}
