#include "vehiclestatusarea.h"
#include "ui_vehiclestatusarea.h"

#include "qdebug.h"
#include "crrcricomvb.h"
#define ACPFAULT   "border-image: url(:/images/image/ACPfaultbtn.png);background-color:transparent;"
#define ACPWARN   "border-image: url(:/images/image/ACPwarnbtn.png);background-color:transparent;"
#define ACPNORMAL   "border-image: url(:/images/image/ACPnormalbtn.png);background-color:transparent;"

#define SIVNORMAL   "border-image: url(:/images/image/SIVnormalbtn.png);background-color:transparent;"
#define SIVFAULT   "border-image: url(:/images/image/SIVfaultbtn.png);background-color:transparent;"
#define SIVWARN   "border-image: url(:/images/image/SIVwarnbtn.png);background-color:transparent;"

#define BREAKERNORMAL    "border-image: url(:/images/image/breakernormalbtn.png);background-color:transparent;"
#define BREAKERFAULT   "border-image: url(:/images/image/breakerfaultbtn.png);background-color:transparent;"
#define BREAKERWARN   "border-image: url(:/images/image/breakerwarnbtn.png);background-color:transparent;"

#define BCUNORMAL   "border-image: url(:/images/image/BCUnormalbtn.png);background-color:transparent;"
#define BCUFAULT   "border-image: url(:/images/image/BCUfaultbtn.png);background-color:transparent;"
#define BCUWARN   "border-image: url(:/images/image/BCUwarnbtn.png);background-color:transparent;"

#define EDCUNORMAL  "border-image: url(:/images/image/doornormalbtn.png);background-color:transparent;"
#define EDCUFAULT  "border-image: url(:/images/image/doorfaultbtn.png);background-color:transparent;"
#define EDCUWARN   "border-image: url(:/images/image/doorwarnbtn.png);background-color:transparent;"

#define FIRENORMAL   "border-image: url(:/images/image/firenormalbtn.png);background-color:transparent;"
#define FIREFAULT   "border-image: url(:/images/image/firefaultbtn.png);background-color:transparent;"
#define FIREWARN   "border-image: url(:/images/image/firewarnbtn.png);background-color:transparent;"

#define PISNORMAL   "border-image: url(:/images/image/PISnormalbtn.png);background-color:transparent;"
#define PISFAULT   "border-image: url(:/images/image/PISfaultbtn.png);background-color:transparent;"
#define PISWARN   "border-image: url(:/images/image/PISwarnbtn.png);background-color:transparent;"

#define TCUNORMAL   "border-image: url(:/images/image/TCUnormalbtn.png);background-color:transparent;"
#define TCUFAULT   "border-image: url(:/images/image/TCUfaultbtn.png);background-color:transparent;"
#define TCUWARN   "border-image: url(:/images/image/TCUwarnbtn.png);background-color:transparent;"

#define TUOPUNORMAL "border-image: url(:/images/image/tuopu.png);background-color:transparent;"
#define TUOPUFAULT  "border-image: url(:/images/image/tuopufault.png);background-color:transparent;"
#define TUOPUWARN   "border-image: url(:/images/image/tuopuwarning.png);background-color:transparent;"

#define HVACNORMAL   "border-image: url(:/images/image/hvacnormalbtndown.png);background-color:transparent;"
#define HVACFAULT   "border-image: url(:/images/image/hvacfaultbtndown.png);background-color:transparent;"
#define HVACWARN   "border-image: url(:/images/image/hvacwarnbtndown.png);background-color:transparent;"

#define RESETNORMAL   "border-image: url(:/images/image/reset.png);background-color:transparent;"


#define LABELUP    "background-color:rgb(0,0,50);"
#define LABELDOWN  "background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgba(150,150,200,255),stop:1 rgba(0,0,50,255));"

#define  BTNPRESS "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(187,188,247) , stop:1 rgb(19,20,87));border:0px solid;color: rgb(255, 255, 255);font:14px \"微软雅黑\";border-radius:10px;"
#define  BTNRELEASE  "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:14px \"微软雅黑\";border-radius:10px;"
#define  BTNOUTABLE "border:2px solid rgb(187,188,247);color: rgb(255, 255, 255);font:14px \"微软雅黑\";border-radius:10px;background-color:rgb(192,192,192)"

#define GRAY "background-color: rgb(159, 158, 159);"

VehicleStatusArea::VehicleStatusArea(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleStatusArea)
{
    ui->setupUi(this);

    buttons<<this->ui->BTNHVAC<<this->ui->BTNSIV<<this->ui->BTNEDCU<<this->ui->BTNPIS<<this->ui->BTNBCU
            <<this->ui->BTNTCU<<this->ui->BTNFire<<this->ui->BTNACP<<this->ui->BTNTolopogy<<this->ui->BTNReset;

    labels<<this->ui->LBLHVAC<<this->ui->LBLSIV<<this->ui->LBLEDCU<<this->ui->LBLPIS<<this->ui->LBLBCU
            <<this->ui->LBLTCU<<this->ui->LBLFire<<this->ui->LBLACP<<this->ui->LBLTolopogy<<this->ui->LBLReset;
    doorPushButton<<ui->BTNResetFirealarm<<ui->BTNResetFireBEEP;
    boorStatus<<&database->DiCT_FASReset_B1<<&database->DiCT_FASSlience_B1;
    for(int i=0;i<doorPushButton.size();i++)
       {
           connect(doorPushButton.at(i),SIGNAL(clicked()),this,SLOT(firePushButtonEvent()));
       }

    Btnstatus<<HVACNORMAL<<SIVNORMAL<<EDCUNORMAL<<PISNORMAL<<BCUNORMAL<<TCUNORMAL<<FIRENORMAL<<ACPNORMAL<<TUOPUNORMAL<<RESETNORMAL;
    for(int i = 0; i<buttons.size();i++)
    {
        connect(buttons[i],SIGNAL(pressed()),this,SLOT(changeTrainStatus()));
        buttons[i]->setStyleSheet(Btnstatus[i]);
        labels[i]->setStyleSheet(LABELUP);
    }

    ui->lbl_level_name->hide();
    ui->lbl_level_value->hide();
    ui->lbl_notract_nobrake->show();

    ui->BTNResetFirealarm->hide();
    ui->BTNResetFireBEEP->hide();
    ui->BTNEmergencyBrocast->hide();
    ui->label_wheelclean->hide();

    this->fireflag=true;
    this->fangyouFlag=true;

    emDialogPage=new EMDialogPage(this);
    emDialogPage->setGeometry(330,30,emDialogPage->width(),emDialogPage->height());

    emDoorOpen=new EmDoorOPen(this);
    emDoorOpen->setGeometry(280,90,emDoorOpen->width(),emDoorOpen->height());
    emDoorOpen->raise();


    emDialogPage->hide();
    ui->lbl_qianyinfengsuo->hide();
    ui->lbl_qianyinfengsuo_2->hide();
    emDooropenflag=0;

}

int VehicleStatusArea::emDooropenflag=0;

void VehicleStatusArea::changeTrainStatus()
{
    QString BTNname = ((QPushButton *)this->sender())->objectName();

    for(int i = 0; i<buttons.size();i++)
    {
        labels[i]->setStyleSheet(LABELUP);

    }

    if(BTNname == "BTNHVAC")
    {
        changePage(uVehicleAirConditionerPage);
        this->ui->LBLHVAC->setStyleSheet(LABELDOWN);
//        ui->lbl_mode->setGeometry(20,80,111,31);
//        ui->LBLSpeed->setGeometry(20,150,111,31);

//        ui->LBLNetV->setGeometry(820,80,51,31);
//        ui->LBL_metrolimitspeed->setGeometry(880,80,41,31);
//        ui->LBLNetV_5->setGeometry(930,80,61,31);

//        ui->LBLNetV_3->setGeometry(820,160,51,31);
//        ui->lbl_metrospeed->setGeometry(880,160,41,31);
//        ui->LBLNetV_6->setGeometry(930,160,61,31);

//        ui->label_3->setGeometry(810,70,191,51);
//        ui->label_4->setGeometry(810,150,191,51);
        ui->BTNResetFirealarm->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNEmergencyBrocast->hide();

    }else if(BTNname == "BTNSIV")
    {
        changePage(uVehicleAuxiliaryPage);
        this->ui->LBLSIV->setStyleSheet(LABELDOWN);
//        ui->lbl_mode->setGeometry(20,80,111,31);
//        ui->LBLSpeed->setGeometry(20,150,111,31);

//        ui->LBLNetV->setGeometry(820,80,51,31);
//        ui->LBL_metrolimitspeed->setGeometry(880,80,41,31);
//        ui->LBLNetV_5->setGeometry(930,80,61,31);

//        ui->LBLNetV_3->setGeometry(820,160,51,31);
//        ui->lbl_metrospeed->setGeometry(880,160,41,31);
//        ui->LBLNetV_6->setGeometry(930,160,61,31);

//        ui->label_3->setGeometry(810,70,191,51);
//        ui->label_4->setGeometry(810,150,191,51);
        ui->BTNResetFirealarm->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNEmergencyBrocast->hide();

    }else if(BTNname == "BTNEDCU")
    {
        changePage(uVehicleDoorPage);
        this->ui->LBLEDCU->setStyleSheet(LABELDOWN);
        ui->BTNResetFirealarm->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNEmergencyBrocast->hide();

    }else if(BTNname == "BTNPIS")
    {
        changePage(uVehiclePISPage);
        this->ui->LBLPIS->setStyleSheet(LABELDOWN);
        ui->BTNResetFirealarm->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNEmergencyBrocast->show();

    }else if(BTNname == "BTNBCU")
    {
        changePage(uVehicleBrakePage);
        this->ui->LBLBCU->setStyleSheet(LABELDOWN);
        ui->BTNResetFirealarm->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNEmergencyBrocast->hide();

    }else if(BTNname == "BTNTCU")
    {
        changePage(uVehicleTractPage);
        this->ui->LBLTCU->setStyleSheet(LABELDOWN);
        ui->BTNResetFirealarm->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNEmergencyBrocast->hide();

    }else if(BTNname == "BTNFire")
    {
        changePage(uVehicleFireWarningPage);
        this->ui->LBLFire->setStyleSheet(LABELDOWN);
        ui->BTNResetFirealarm->show();
        ui->BTNResetFireBEEP->show();
        ui->BTNEmergencyBrocast->hide();
    }else if(BTNname == "BTNACP")
    {
        changePage(uVehicleAirCompressorPage);
        this->ui->LBLACP->setStyleSheet(LABELDOWN);
        ui->BTNResetFirealarm->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNEmergencyBrocast->hide();

    }else if(BTNname == "BTNTolopogy")
    {
        changePage(uVehicleTopologyPage);
        this->ui->LBLTolopogy->setStyleSheet(LABELDOWN);
        ui->BTNResetFirealarm->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNEmergencyBrocast->hide();
    }
    else if(BTNname=="BTNReset")
    {
        changePage(uVehicleLineCircuitBreakerPage);
        this->ui->LBLReset->setStyleSheet(LABELDOWN);
        ui->BTNResetFirealarm->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNEmergencyBrocast->hide();
    }
    else
    {
        ui->BTNResetFirealarm->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNEmergencyBrocast->hide();
    }



}

VehicleStatusArea::~VehicleStatusArea()
{
    delete ui;
}
void VehicleStatusArea::updatePage()
{

    //紧急制动
    if(database->CTD_EmgyBrake_B1)
    {
        ui->LBLSpeed->show();
        ui->lbl_progressbar_value->setGeometry(30,139+100,45,5);
        ui->lbl_progressbar_bg_value->setGeometry(41,141+100,9,0);
        ui->lbl_notract_nobrake->hide();
        ui->lbl_level_name->show();
        ui->lbl_level_value->show();
        ui->lbl_level_name->setText("制动");
        ui->lbl_level_value->setText("100%");
    }
    else
    {
        ui->LBLSpeed->hide();
        setProgressBar(database->CTD_TractiOLINE_B1,database->CTD_Brake_B1,database->CTD_Grade_U8,database->CTD_FastBrake_B1);

    }
    //牵引制动级位
    //setProgressBar(database->CTD_TractiOLINE_B1,database->CTD_Brake_B1,database->CTD_Grade_U8,database->CTD_FastBrake_B1);

    //限速和速度
    ui->LBL_metrolimitspeed->setText(QString::number(database->CTD_TrainLimitSpeed_U16/10));
    ui->lbl_metrospeed->setText(QString::number(database->CTD_TrainSpeed_U16/10));
    //驾驶模式
    if(database->CTD_DriveMode_U8==0)
    {
        ui->lbl_mode->setText("无模式");
    }
    else if(database->CTD_DriveMode_U8==1)
    {
        ui->lbl_mode->setText("紧急牵引");
    }
    else if(database->CTD_DriveMode_U8==2)
    {
        ui->lbl_mode->setText("洗车模式");
    }
    else if(database->CTD_DriveMode_U8==3)
    {
        ui->lbl_mode->setText("EUM模式");
    }
    else if(database->CTD_DriveMode_U8==4)
    {
        ui->lbl_mode->setText("AM模式");
    }
    else if(database->CTD_DriveMode_U8==5)
    {
        ui->lbl_mode->setText("CM模式");
    }
    else if(database->CTD_DriveMode_U8==6)
    {
        ui->lbl_mode->setText("RM模式");
    }
    else if(database->CTD_DriveMode_U8==7)
    {
        ui->lbl_mode->setText("无人折返");
    }
    else
    {
        ui->lbl_mode->setText("--");
    }
    if(database->CTD_TRCBLOCK_U8)
    {
        ui->lbl_qianyinfengsuo->show();
        ui->lbl_qianyinfengsuo_2->show();
        switch(database->CTD_QYFSXX_U8)
        {
        case 1:
            ui->lbl_qianyinfengsuo->setText("ATO、CM、自动折返模式\n下,速度大于125km/h。");
            break;
        case 2:
            ui->lbl_qianyinfengsuo->setText("非轮盘清洁模式下,四个以上\n牵引控制单元的牵引和电制动\n切除。");
            break;
        case 3:
            ui->lbl_qianyinfengsuo->setText("四个以上转向架的气制动丢\n失。");
            break;
        case 4:
            ui->lbl_qianyinfengsuo->setText("所有停放制动不缓解,若此没\n有“停放制动缓解旁路”信号,\n则网络将会牵引封锁。");
            break;
        case 5:
            ui->lbl_qianyinfengsuo->setText("列车发出牵引指令后,5s内列\n车仍然不能缓解所有制动,则触\n发牵引封锁。");
            break;
        default:
            ui->lbl_qianyinfengsuo->setText("");
            break;
        }
    }
    else
    {
        ui->lbl_qianyinfengsuo->hide();
        ui->lbl_qianyinfengsuo_2->hide();
    }

    //轮盘清洁激活
    if (database->CTB_WheelCleaning_B1)
    {
        ui->label_wheelclean->show();
    }
    else
    {
        ui->label_wheelclean->hide();
    }
    //开关门
//    if(database->CTHM_TCMSOpenEnable_B1)
//    {
//        if(database->CTHM_LtDrOpenEnable_B1)
//        {
//            ui->NB_openLeftDoor->setEnabled(true);
//            ui->NB_closeLeftDoor->setEnabled(true);

//        }else
//        {
//            ui->NB_openLeftDoor->setEnabled(false);
//            ui->NB_closeLeftDoor->setEnabled(false);
//        }

//        if(database->CTHM_RtDrOpenEnable_B1)
//        {
//            ui->NB_openRightDoor->setEnabled(true);
//            ui->NB_closeRightDoor->setEnabled(true);
//        }else
//        {
//            ui->NB_openRightDoor->setEnabled(false);
//            ui->NB_closeRightDoor->setEnabled(false);
//        }
//    }
//    else
//    {
//        ui->NB_openLeftDoor->setEnabled(false);
//        ui->NB_closeLeftDoor->setEnabled(false);
//        ui->NB_openRightDoor->setEnabled(false);
//        ui->NB_closeRightDoor->setEnabled(false);
//    }


//    if(!database->checkCcu1Online(database->CTALL_LfSign_U16))
//    {
//#ifndef USE_DEBUG_MODE
//        emDialogPage->raise();
//        emDialogPage->show();
//        emDialogPage->setLabelText("通信中断");
//#endif
//    }

//    else if(database->CTD_TrainSpeed_U16>database->CTD_TrainLimitSpeed_U16)
//    {
//        emDialogPage->raise();
//        emDialogPage->show();
//        emDialogPage->setLabelText("超速警告\n请减速");
//    }
//    else
//    {
//        emDialogPage->hide();
//    }

    if((database->CTD_TrainSpeed_U16*0.1)>=125)
    {
        emDialogPage->raise();
        emDialogPage->show();
        emDialogPage->setLabelText("超速警告\n请减速");
    }
    else
    {
        emDialogPage->hide();
    }


    static unsigned short int t_Status_HVAC = 0;
    static unsigned short int t_Status_PIS = 0;
    static unsigned short int t_Status_TCU = 0;
    static unsigned short int t_Status_BCU = 0;
    static unsigned short int t_Status_ACP = 0;
    static unsigned short int t_Status_FIRE = 0;
    static unsigned short int t_Status_SIV = 0;
    static unsigned short int t_Status_EDCU = 0;
    static unsigned short int t_Status_TUOPU = 0;

    this->setLabelStatus(this->database->Status_HVAC,t_Status_HVAC,this->ui->BTNHVAC,HVACFAULT,HVACWARN,HVACNORMAL);
    this->setLabelStatus(this->database->Status_SIV,t_Status_SIV,this->ui->BTNSIV,SIVFAULT,SIVWARN,SIVNORMAL);
    this->setLabelStatus(this->database->Status_TCU,t_Status_TCU,this->ui->BTNTCU,TCUFAULT,TCUWARN,TCUNORMAL);
    this->setLabelStatus(this->database->Status_PIS,t_Status_PIS,this->ui->BTNPIS,PISFAULT,PISWARN,PISNORMAL);
    this->setLabelStatus(this->database->Status_EDCU,t_Status_EDCU,this->ui->BTNEDCU,EDCUFAULT,EDCUWARN,EDCUNORMAL);
    this->setLabelStatus(this->database->Status_BCU,t_Status_BCU,this->ui->BTNBCU,BCUFAULT,BCUWARN,BCUNORMAL);
    this->setLabelStatus(this->database->Status_FIRE,t_Status_FIRE,this->ui->BTNFire,FIREFAULT,FIREWARN,FIRENORMAL);
    this->setLabelStatus(this->database->Status_ACP,t_Status_ACP,this->ui->BTNACP,ACPFAULT,ACPWARN,ACPNORMAL);
    this->setLabelStatus(this->database->Status_TUOPU,t_Status_TUOPU,this->ui->BTNTolopogy,TUOPUFAULT,TUOPUWARN,TUOPUNORMAL);

  //紧急解锁弹窗，确认后不再重复弹出，恢复又发生则继续弹
    int doorflag=0;
    doorflag=isDoorEmOpen();

    if(doorflag>0&&this->emDooropenflag==0)
    {
        emDoorOpen->show();
    }
    else
    {
        emDoorOpen->hide();
    }

    if(doorflag==0)
        this->emDooropenflag=0;

}
void VehicleStatusArea::setLabelStatus(unsigned short int status,unsigned short int &t_status,QPushButton* btn,QString Faultstr,QString Warningstr,QString Normalstr)
{

    if(status == t_status)
    {
        t_status = status;
        return ;
    }
    switch (status)
    {
    case 2:
        btn->setStyleSheet(Faultstr);
        break;
    case 1:
        btn->setStyleSheet(Warningstr);
        break;
    case 0:
        btn->setStyleSheet(Normalstr);
        break;
    }
    t_status = status;


}
void VehicleStatusArea::refreshAllButton()
{
    for(int i = 0; i<buttons.size();i++)
    {
        labels[i]->setStyleSheet(LABELUP);
        //隐藏开门和火灾按钮
    }
    ui->BTNEmergencyBrocast->hide();
    ui->BTNResetFirealarm->hide();
    ui->BTNResetFireBEEP->hide();
}

void VehicleStatusArea::setProgressBar(bool tract,bool brake,unsigned short value,bool quickBrake)
{
    if(tract&&!brake)
    {
        ui->lbl_progressbar_value->setGeometry(30,139-value,45,5);
        ui->lbl_progressbar_bg_value->setGeometry(41,141-value,9,100+value);
        ui->lbl_notract_nobrake->hide();
        ui->lbl_level_name->show();
        ui->lbl_level_value->show();
        ui->lbl_level_name->setText("牵引");
        ui->lbl_level_value->setText(QString::number(value)+"%");

    }
    else if(!tract&&brake)
    {
        ui->lbl_progressbar_value->setGeometry(30,139+value,45,5);
        ui->lbl_progressbar_bg_value->setGeometry(41,141+value,9,100-value);
        ui->lbl_notract_nobrake->hide();
        ui->lbl_level_name->show();
        ui->lbl_level_value->show();
        if(!quickBrake)
        {
            ui->lbl_level_name->setText("制动");
        }
        else
        {
            ui->lbl_level_name->setText("快速\n制动");
        }

        ui->lbl_level_value->setText(QString::number(value)+"%");

    }
    else
    {
        ui->lbl_progressbar_value->setGeometry(30,139,45,5);
        ui->lbl_progressbar_bg_value->setGeometry(41,141,9,100);
        ui->lbl_level_name->hide();
        ui->lbl_level_value->hide();
        ui->lbl_notract_nobrake->show();
    }

}

void VehicleStatusArea::firePushButtonEvent()
{
    int whichButton=((QPushButton*)this->sender())->whatsThis().toInt()-1;
    database->DiCT_SetFlagChecker_U8=0xAA;
    *boorStatus[whichButton]=true;
    ((QPushButton*)this->sender())->setStyleSheet(BTNPRESS);
    ((QPushButton*)this->sender())->setEnabled(false);
    time3s[whichButton]=this->startTimer(2000);
}

void VehicleStatusArea::timerEvent(QTimerEvent *e)
{
    for(int i = 0; i < 2;i++)
        {
            if(e->timerId() == time3s[i])
            {
                killTimer(time3s[i]);
                doorPushButton.at(i)->setStyleSheet(BTNRELEASE);
                doorPushButton.at(i)->setEnabled(true);
                *boorStatus.at(i) = false;
                database->DiCT_SetFlagChecker_U8=0x55;
            }
        }
}



void VehicleStatusArea::on_BTNEmergencyBrocast_pressed()
{
    changePage(uVehicleSetStationPage);
}

void VehicleStatusArea::showEvent(QTimerEvent *e)
{
    if(currentPage == uVehicleTrainArea)
    {
        ui->BTNEmergencyBrocast->hide();
        ui->BTNResetFireBEEP->hide();
        ui->BTNResetFirealarm->hide();
    }
}

//void VehicleStatusArea::on_BTN_fangyou_pressed()
//{

//    if(fangyouFlag)
//    {
//        //ui->BTN_fangyou->setStyleSheet(BTNPRESS);
//        fangyouFlag=false;
//        database->fangyou=true;
//    }
//    else
//    {
//        //ui->BTN_fangyou->setStyleSheet(BTNRELEASE);
//        fangyouFlag=true;
//        database->fangyou=false;
//    }
//}

int VehicleStatusArea::isDoorEmOpen()
{
    int sum=database->EDCU1_2CT_DOOR167_B1+database->EDCU1_2CT_DOOR183_B1+database->EDCU1_2CT_DOOR199_B1
            +database->EDCU1_2CT_DOOR215_B1+database->EDCU1_2CT_DOOR231_B1+database->EDCU1_2CT_DOOR247_B1+

            database->EDCU3_4CT_DOOR167_B1+database->EDCU3_4CT_DOOR183_B1+database->EDCU3_4CT_DOOR199_B1
            +database->EDCU3_4CT_DOOR215_B1+database->EDCU3_4CT_DOOR231_B1+database->EDCU3_4CT_DOOR247_B1+

            database->EDCU5_6CT_DOOR167_B1+database->EDCU5_6CT_DOOR183_B1+database->EDCU5_6CT_DOOR199_B1
            +database->EDCU5_6CT_DOOR215_B1+database->EDCU5_6CT_DOOR231_B1+database->EDCU5_6CT_DOOR247_B1+

            database->EDCU7_8CT_DOOR167_B1+database->EDCU7_8CT_DOOR183_B1+database->EDCU7_8CT_DOOR199_B1
            +database->EDCU7_8CT_DOOR215_B1+database->EDCU7_8CT_DOOR231_B1+database->EDCU7_8CT_DOOR247_B1;

    return sum;
}
