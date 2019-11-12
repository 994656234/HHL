#include "vehiclerunpage.h"
#include "ui_vehiclerunpage.h"

#define DOORCLOSE "background-color: rgb(0,192,0);border:2px solid rgb(255,255,255);font: 20px  \"微软雅黑\";color:rgba(0,0,0,255);"
#define DOOROPEN "background-color: rgb(224,160,192);border:2px solid rgb(255,255,255);font: 20px  \"微软雅黑\";color:rgba(0,0,0,255);"
#define DOOROB    "background-color: brown;border:2px solid rgb(255,255,255);font: 20px  \"微软雅黑\";color:rgba(0,0,0,255);"
#define DOORFAULT "background-color: rgb(255,0,0);border:2px solid rgb(255,255,255);font: 20px  \"微软雅黑\";color:rgba(0,0,0,255);"
#define DOOREMLOCK "background-color: yellow;border:2px solid rgb(255,255,255);font: 20px  \"微软雅黑\";color:rgba(0,0,0,255);"
#define DOORBYPASS "background-color: rgb(180,180,180);;border:2px solid rgb(255,255,255);font: 20px  \"微软雅黑\";color:rgba(0,0,0,255);"
#define DOORUNKNOW "background-color: rgb(255,255,255);border:2px solid rgb(255,255,255);font: 20px  \"微软雅黑\";color:rgba(0,0,0,255);"

#define HVACRUN  "border-image: url(:/image/HVACrun.png);"
#define HVACEMVEN  "border-image: url(:/image/HVACemven.png);"
#define HVACVEN  "border-image: url(:/image/HVACven.png);"
#define HVACOFF "border-image: url(:/image/HVACoff.png);"
#define HVACFAULT  "border-image: url(:/image/HVACfault.png);"
#define HVACUNKNOWN "background-color: rgb(255,255,255);"

#define PISOFF "border:1px solid white;border-radius:15px ;background-color:white;font-size:22px;"
#define PISFAULT "border:1px solid white;border-radius:15px;background-color:red;font-size:22px;"
#define PISACTIVE "border:1px solid white;border-radius:15px;background-color:lightgreen;font-size:22px;"
#define PISCALL "border:1px solid white;border-radius:15px;background-color:yellow;font-size:22px;"
#define PISUNACTIVE "border:1px solid white;border-radius:15px;background-color:rgb(180,180,180);;font-size:22px;"

#define BCUOFF "border-image: url(:/image/Bunknown.png);"
#define BCUAPPLY "border-image: url(:/image/BApply.png);"
#define BCUFAULT "border-image: url(:/image/Bfault.png);"
#define BCURELEASE "border-image: url(:/image/Brelease.png);"
#define BCUNOTRELEASE "border-image: url(:/image/Bnotrelease.png);"

#define ACPRUN  "border-image: url(:/image/ACPRun.png);"
#define ACPSTOP  "border-image: url(:/image/ACPStop.png);"
#define ACPUNKNOWN  "border-image: url(:/image/ACPUnknow.png);"

#define TCUOFF  "border:1px solid white;border-radius:15px ;background-color:white;font-size:22px;"
#define TCUFAULT "border:1px solid white;border-radius:15px;background-color:red;font-size:22px;"
#define TCURUN "border:1px solid white;border-radius:15px;background-color:lightgreen;font-size:22px;"
#define TCUSTOP "border:1px solid white;border-radius:15px;background-color:rgb(180,180,180);font-size:22px;"

#define ACUOFF  "border-image: url(:/image/SIVUnknow.bmp);"
#define ACUFAULT "border-image: url(:/image/SIVFault.bmp);"
#define ACURUN "border-image: url(:/image/SIVRun.bmp);"
#define ACUSTOP "border-image: url(:/image/SIVStop.bmp);"

#define BCCUOFF  "border-image: url(:/image/DCDCUnknow.bmp);"
#define BCCUFAULT "border-image: url(:/image/DCDCFault.bmp);"
#define BCCURUN "border-image: url(:/image/DCDCRun.bmp);"
#define BCCUSTOP "border-image: url(:/image/DCDCStop.bmp);"

#define EMBTNDOWN  "border:5px solid black;border-radius:20px;background-color:red;font-size:22px;"
#define EMBTNUP    "border:5px solid black;border-radius:20px;background-color:lightgreen;font-size:22px;"

#define ESCAPEDOORCLOSE   "border-image: url(:/image/EscapeDoorClose.png);"
#define ESCAPEDOOROPEN    "border-image: url(:/image/EscapeDoorOpen.png);"
#define ESCAPERAMPCLOSE   "border-image: url(:/image/EscapeRampClose.png);"
#define ESCAPERAMPOPEN    "border-image: url(:/image/EscapeRampOpen.png);"

#define COUPLEMC1    "border-image: url(:/image/CoupleMC1.png);"
#define COUPLEMC2    "border-image: url(:/image/CoupleMC2.png);"

VehicleRunPage::VehicleRunPage(QWidget *parent) :
    BasePage(parent),
    ui(new Ui::VehicleRunPage)
{
    ui->setupUi(this);
    count = 0;
    this->ui->groupBox->hide();


    Speedometer = new CtrlSpeedometer(this);
    Speedometer ->setGeometry(380,300,Speedometer->width(),Speedometer->height());

}

VehicleRunPage::~VehicleRunPage()
{
    delete ui;
}
void VehicleRunPage::showEvent(QShowEvent *e)
{

}
void VehicleRunPage::updatePage()
{
    updateRunStatus();
    updateTrainStatus();
}
void VehicleRunPage::updateRunStatus()
{
    //级位
    if(this->database->CTHM_Traction_B1)
    {
        setTracBrakeBarValue(this->database->CTHM_Grade_U8);
        ui->lbl_tracBrkvalue->setStyleSheet("font-size:22px;color: lightgreen;");
        ui->lbl_tracBrkvalue->setText("牵引级位："+QString::number(this->database->CTHM_Grade_U8)+"%");

    }else if(this->database->CTHM_Brake_B1)
    {
        setTracBrakeBarValue(0-this->database->CTHM_Grade_U8);
        ui->lbl_tracBrkvalue->setStyleSheet("font-size:22px;color: red;");
        ui->lbl_tracBrkvalue->setText("制动级位："+QString::number(this->database->CTHM_Grade_U8)+"%");
    }else
    {
        setTracBrakeBarValue(0);
        ui->lbl_tracBrkvalue->setStyleSheet("font-size:22px;color: black;");
        ui->lbl_tracBrkvalue->setText("惰行");
    }
    ui->lbl_battery->setText(QString::number((float)this->database->BC1CT_OutputVoltage_U16/10)+"V   "
                             +QString::number((float)this->database->BC2CT_OutputVoltage_U16/10)+"V");
    Speedometer->setSpeenometerValue(this->database->CTHM_TrainSpeed_U16/10);

    setLowVoltageBarValue(this->database->BC1CT_OutputVoltage_U16/10,this->database->BC2CT_OutputVoltage_U16/10);

}
void VehicleRunPage::updateTrainStatus()
{
    //钥匙
    if(this->database->CTHM_MC1Active_B1)
    {
        this->ui->VehicleRun_mc1Active->show();
        this->ui->VehicleRun_mc2Active->hide();
    }else if(this->database->CTHM_MC2Active_B1)
    {
        this->ui->VehicleRun_mc2Active->show();
        this->ui->VehicleRun_mc1Active->hide();
    }else
    {
        this->ui->VehicleRun_mc1Active->hide();
        this->ui->VehicleRun_mc2Active->hide();
    }
    //方向
    if(this->database->CTHM_Forward_B1)
    {
        this->ui->VehicleRun_forward->show();
        this->ui->VehicleRun_backward->hide();
    }else if(this->database->CTHM_Backward_B1)
    {
        this->ui->VehicleRun_forward->hide();
        this->ui->VehicleRun_backward->show();
    }else
    {
        this->ui->VehicleRun_forward->hide();
        this->ui->VehicleRun_backward->hide();
    }
    //车门 offline--fault--bypass--emlock--obr--close--open
    QList<bool> DoorStatus;
    DoorStatus<<this->database->CTHM_MDCU1On_B1<<this->database->DR1CT_SerFault_B1<<this->database->DR1CT_Cutout_B1<<this->database->DR1CT_EmgyUnlock_B1
                <<this->database->DR1CT_ObtDetected_B1<<this->database->DR1CT_CloseAndLocked_B1<<this->database->DR1CT_OpenCompletly_B1;
    setDoorStatus(this->ui->VehicleRun_EDCU1_MC1,DoorStatus);
    DoorStatus.clear();

    DoorStatus<<this->database->CTHM_MDCU2On_B1<<this->database->DR2CT_SerFault_B1<<this->database->DR2CT_Cutout_B1<<this->database->DR2CT_EmgyUnlock_B1
                <<this->database->DR2CT_ObtDetected_B1<<this->database->DR2CT_CloseAndLocked_B1<<this->database->DR2CT_OpenCompletly_B1;
    setDoorStatus(this->ui->VehicleRun_EDCU2_MC1,DoorStatus);
    DoorStatus.clear();

    DoorStatus<<this->database->CTHM_MDCU3On_B1<<this->database->DR3CT_SerFault_B1<<this->database->DR3CT_Cutout_B1<<this->database->DR3CT_EmgyUnlock_B1
                <<this->database->DR3CT_ObtDetected_B1<<this->database->DR3CT_CloseAndLocked_B1<<this->database->DR3CT_OpenCompletly_B1;
    setDoorStatus(this->ui->VehicleRun_EDCU1_T,DoorStatus);
    DoorStatus.clear();

    DoorStatus<<this->database->CTHM_MDCU4On_B1<<this->database->DR4CT_SerFault_B1<<this->database->DR4CT_Cutout_B1<<this->database->DR4CT_EmgyUnlock_B1
                <<this->database->DR4CT_ObtDetected_B1<<this->database->DR4CT_CloseAndLocked_B1<<this->database->DR4CT_OpenCompletly_B1;
    setDoorStatus(this->ui->VehicleRun_EDCU2_T,DoorStatus);
    DoorStatus.clear();

    DoorStatus<<this->database->CTHM_MDCU5On_B1<<this->database->DR5CT_SerFault_B1<<this->database->DR5CT_Cutout_B1<<this->database->DR5CT_EmgyUnlock_B1
                <<this->database->DR5CT_ObtDetected_B1<<this->database->DR5CT_CloseAndLocked_B1<<this->database->DR5CT_OpenCompletly_B1;
    setDoorStatus(this->ui->VehicleRun_EDCU1_MC2,DoorStatus);
    DoorStatus.clear();

    DoorStatus<<this->database->CTHM_MDCU6On_B1<<this->database->DR6CT_SerFault_B1<<this->database->DR6CT_Cutout_B1<<this->database->DR6CT_EmgyUnlock_B1
                <<this->database->DR6CT_ObtDetected_B1<<this->database->DR6CT_CloseAndLocked_B1<<this->database->DR6CT_OpenCompletly_B1;
    setDoorStatus(this->ui->VehicleRun_EDCU2_MC2,DoorStatus);
    DoorStatus.clear();
    //牵引 offline--fault--run--stop
    QList<bool> TCUStatus;
    TCUStatus<<this->database->CTHM_TCU1On_B1<<this->database->TR1CT_SerFaultTCU_B1<<this->database->TR1CT_TractionOK_B1;
    setTCUStatus(this->ui->VehicleRun_motor1_MC1,TCUStatus);
    TCUStatus.clear();

    TCUStatus<<this->database->CTHM_TCU2On_B1<<this->database->TR2CT_SerFaultTCU_B1<<this->database->TR2CT_TractionOK_B1;
    setTCUStatus(this->ui->VehicleRun_motor2_MC1,TCUStatus);
    TCUStatus.clear();

    TCUStatus<<this->database->CTHM_TCU3On_B1<<this->database->TR3CT_SerFaultTCU_B1<<this->database->TR3CT_TractionOK_B1;
    setTCUStatus(this->ui->VehicleRun_motor1_MC2,TCUStatus);
    TCUStatus.clear();

    TCUStatus<<this->database->CTHM_TCU4On_B1<<this->database->TR4CT_SerFaultTCU_B1<<this->database->TR4CT_TractionOK_B1;
    setTCUStatus(this->ui->VehicleRun_motor2_MC2,TCUStatus);
    TCUStatus.clear();

    //制动 offline--fault--apply--release
    QList<bool> BCUStatus;
    BCUStatus<<this->database->CTHM_BCU1On_B1<<this->database->BR1CT_SeriousFault_B1
            <<!this->database->BR1CT_Bogie1BrReleased_B1<<this->database->BR1CT_BrakeNotReleaseBogie1_B1;
    setBCUStatus(this->ui->VehicleRun_BCU1_MC1,BCUStatus);
    BCUStatus.clear();

    BCUStatus<<this->database->CTHM_BCU1On_B1<<this->database->BR1CT_SeriousFault_B1
            <<!this->database->BR1CT_Bogie2BrReleased_B1<<this->database->BR1CT_BrakeNotReleaseBogie2_B1;
    setBCUStatus(this->ui->VehicleRun_BCU2_MC1,BCUStatus);
    BCUStatus.clear();

    BCUStatus<<this->database->CTHM_BCU2On_B1<<this->database->BR2CT_SeriousFault_B1
            <<!this->database->BR2CT_Bogie1BrReleased_B1<<this->database->BR2CT_BrakeNotReleaseBogie1_B1;;
    setBCUStatus(this->ui->VehicleRun_BCU1_T,BCUStatus);
    BCUStatus.clear();

    BCUStatus<<this->database->CTHM_BCU2On_B1<<this->database->BR2CT_SeriousFault_B1
            <<!this->database->BR2CT_Bogie2BrReleased_B1<<this->database->BR2CT_BrakeNotReleaseBogie2_B1;;
    setBCUStatus(this->ui->VehicleRun_BCU2_T,BCUStatus);
    BCUStatus.clear();

    BCUStatus<<this->database->CTHM_BCU3On_B1<<this->database->BR3CT_SeriousFault_B1
            <<!this->database->BR3CT_Bogie1BrReleased_B1<<this->database->BR3CT_BrakeNotReleaseBogie1_B1;;
    setBCUStatus(this->ui->VehicleRun_BCU1_MC2,BCUStatus);
    BCUStatus.clear();

    BCUStatus<<this->database->CTHM_BCU3On_B1<<this->database->BR3CT_SeriousFault_B1
            <<!this->database->BR3CT_Bogie2BrReleased_B1<<this->database->BR3CT_BrakeNotReleaseBogie2_B1;;
    setBCUStatus(this->ui->VehicleRun_BCU2_MC2,BCUStatus);
    BCUStatus.clear();
    //pis offline--fault--active--call--unactice
    QList<bool> PISStatus;
    PISStatus<<(this->database->CTHM_PIS1On_B1||this->database->CTHM_PIS2On_B1)<<this->database->PS1CT_PECU11Fault_B1
               <<this->database->PS1CT_PECU11Active_B1<<this->database->PS1CT_PECU11Call_B1;
    setPISStatus(this->ui->VehicleRun_PECU1_MC1,PISStatus);
    PISStatus.clear();

    PISStatus<<(this->database->CTHM_PIS1On_B1||this->database->CTHM_PIS2On_B1)<<this->database->PS1CT_PECU12Fault_B1
               <<this->database->PS1CT_PECU12Active_B1<<this->database->PS1CT_PECU12Call_B1;
    setPISStatus(this->ui->VehicleRun_PECU2_MC1,PISStatus);
    PISStatus.clear();

    PISStatus<<(this->database->CTHM_PIS1On_B1||this->database->CTHM_PIS2On_B1)<<this->database->PS1CT_PECU21Fault_B1
               <<this->database->PS1CT_PECU21Active_B1<<this->database->PS1CT_PECU21Call_B1;
    setPISStatus(this->ui->VehicleRun_PECU1_T,PISStatus);
    PISStatus.clear();

    PISStatus<<(this->database->CTHM_PIS1On_B1||this->database->CTHM_PIS2On_B1)<<this->database->PS1CT_PECU22Fault_B1
               <<this->database->PS1CT_PECU22Active_B1<<this->database->PS1CT_PECU22Call_B1;
    setPISStatus(this->ui->VehicleRun_PECU2_T,PISStatus);
    PISStatus.clear();

    PISStatus<<(this->database->CTHM_PIS1On_B1||this->database->CTHM_PIS2On_B1)<<this->database->PS1CT_PECU31Fault_B1
               <<this->database->PS1CT_PECU31Active_B1<<this->database->PS1CT_PECU31Call_B1;
    setPISStatus(this->ui->VehicleRun_PECU1_MC2,PISStatus);
    PISStatus.clear();

    PISStatus<<(this->database->CTHM_PIS1On_B1||this->database->CTHM_PIS2On_B1)<<this->database->PS1CT_PECU32Fault_B1
               <<this->database->PS1CT_PECU32Active_B1<<this->database->PS1CT_PECU32Call_B1;
    setPISStatus(this->ui->VehicleRun_PECU2_MC2,PISStatus);
    PISStatus.clear();
    //空调 offline--fault--emven--cold--warm--ven--stop
    setHVACStatus(this->ui->VehicleRun_HVAC_MC1,this->database->CTHM_HVAC1On_B1,this->database->AC1CT_WorkMode_U8);
    setHVACStatus(this->ui->VehicleRun_HVAC_T,this->database->CTHM_HVAC2On_B1,this->database->AC2CT_WorkMode_U8);
    setHVACStatus(this->ui->VehicleRun_HVAC_MC2,this->database->CTHM_HVAC3On_B1,this->database->AC3CT_WorkMode_U8);

    this->ui->VehicleRun_OutTemp_MC1->setText(QString::number(this->database->AC1CT_ExternalTemp_U8-30)+"℃");
    this->ui->VehicleRun_OutTemp_T->setText(QString::number(this->database->AC2CT_ExternalTemp_U8-30)+"℃");
    this->ui->VehicleRun_OutTemp_MC2->setText(QString::number(this->database->AC3CT_ExternalTemp_U8-30)+"℃");
    //空压机
    if(this->database->CTHM_RIOM1GWOnline_B1)
    {
        if(this->database->RM1CT_DIM4Ch07KeySwitch2_B1)
        {
            this->ui->VehicleRun_ACP_MC1->setStyleSheet(ACPRUN);
        }else
        {
            this->ui->VehicleRun_ACP_MC1->setStyleSheet(ACPSTOP);
        }
    }else
    {
        this->ui->VehicleRun_ACP_MC1->setStyleSheet(ACPUNKNOWN);
    }

    if(this->database->CTHM_RIOM3GWOnline_B1)
    {
        if(this->database->RM3CT_DIM4Ch07KeySwitch2_B1)
        {
            this->ui->VehicleRun_ACP_MC2->setStyleSheet(ACPRUN);
        }else
        {
            this->ui->VehicleRun_ACP_MC2->setStyleSheet(ACPSTOP);
        }
    }else
    {
        this->ui->VehicleRun_ACP_MC2->setStyleSheet(ACPUNKNOWN);
    }


    //辅助
    QList<bool> ACUStatus;
    ACUStatus<<this->database->CTHM_ACU1On_B1<<this->database->AX1CT_FaultStatus_B1<<this->database->AX1CT_RunningStatus_B1;
    setACUStatus(this->ui->VehicleRun_ACU1_T,ACUStatus);
    ACUStatus.clear();

    ACUStatus<<this->database->CTHM_ACU2On_B1<<this->database->AX2CT_FaultStatus_B1<<this->database->AX2CT_RunningStatus_B1;
    setACUStatus(this->ui->VehicleRun_ACU2_T,ACUStatus);
    ACUStatus.clear();

    //充电机
    QList<bool> BCCUStatus;
    BCCUStatus<<this->database->CTHM_BCCU1On_B1<<this->database->BC1CT_ChargerFault_B1<<!this->database->BC1CT_ChargerStop_B1;
    setBCCUStatus(this->ui->VehicleRun_BCCU1_T,BCCUStatus);
    BCCUStatus.clear();

    BCCUStatus<<this->database->CTHM_BCCU2On_B1<<this->database->BC2CT_ChargerFault_B1<<!this->database->BC2CT_ChargerStop_B1;
    setBCCUStatus(this->ui->VehicleRun_BCCU2_T,BCCUStatus);
    BCCUStatus.clear();

    //EM BTN
    setLableStatus(this->ui->VehicleRun_EMBtn_MC1,this->database->RM1CT_DIM2Ch09EmgyButton_B1,EMBTNDOWN,EMBTNUP);
    setLableStatus(this->ui->VehicleRun_EMBtn_MC2,this->database->RM3CT_DIM2Ch09EmgyButton_B1,EMBTNDOWN,EMBTNUP);

    //逃生门
    setLableStatus(this->ui->VehicleRun_EscapeDoor_MC1,this->database->RM1CT_DIM1Ch17EmgyExitSwitch_B1,ESCAPEDOORCLOSE,ESCAPEDOOROPEN);
    setLableStatus(this->ui->VehicleRun_EscapeDoor_MC2,this->database->RM3CT_DIM1Ch17EmgyExitSwitch_B1,ESCAPEDOORCLOSE,ESCAPEDOOROPEN);
    setLableStatus(this->ui->VehicleRun_EscapeRamp_MC1,this->database->RM1CT_DIM1Ch18EmgyExitRampSwitch_B1,ESCAPERAMPCLOSE,ESCAPERAMPOPEN);
    setLableStatus(this->ui->VehicleRun_EscapeRamp_MC2,this->database->RM3CT_DIM1Ch18EmgyExitRampSwitch_B1,ESCAPERAMPCLOSE,ESCAPERAMPOPEN);

    //连挂
    setLableStatus(this->ui->VehicleRun_Couple_MC1,this->database->RM1CT_DIM3Ch08Couple_B1,COUPLEMC1,"");
    setLableStatus(this->ui->VehicleRun_Couple_MC2,this->database->RM3CT_DIM3Ch08Couple_B1,COUPLEMC2,"");

}

void VehicleRunPage::setLableStatus(QLabel* lbl, bool value, QString styleTRUE, QString styleFALSE)
{
    if(value)
    {
        lbl->setStyleSheet(styleTRUE);
    }else
    {
        lbl->setStyleSheet(styleFALSE);
    }
}


void VehicleRunPage::setLowVoltageBarValue(int value1,int value2)
{
    int height ;
    if (value1 >= 0 && value1 <=30)
    {
        if(value1 >= 0 && value1 <= 15)
        {
            height = 2*value1;
        }
        else if (value1 > 15 && value1 <= 25)
        {
            height = 5*(value1-15)+30;
        }
        else if(value1 > 25 && value1 <= 28)
        {
            height = 27*(value1-25)+80;
        }
        else if (value1 > 28 && value1 <= 30)
        {
            height = 10*(value1-28)+80+80;
        }
        ui->Barlabel_LowVoltagevalue->setGeometry(40,220-height,10,height);
        ui->Barlabel_LowVoltagevalueLine->setGeometry(31,220-height,40,5);
    }

    if (value2 >= 0 && value2 <=30)
    {
        if(value2 >= 0 && value2 <= 15)
        {
            height = 2*value2;
        }
        else if (value2 > 15 && value2 <= 25)
        {
            height = 5*(value2-15)+30;
        }
        else if(value2 > 25 && value2 <= 28)
        {
            height = 27*(value2-25)+80;
        }
        else if (value2 > 28 && value2 <= 30)
        {
            height = 10*(value2-28)+80+80;
        }
        ui->Barlabel_LowVoltagevalue2->setGeometry(110,220-height,10,height);
        ui->Barlabel_LowVoltagevalue2Line->setGeometry(101,220-height,40,5);
    }
}
void VehicleRunPage::setTracBrakeBarValue(int value)
{
    int height ;
    if (value > 0 )
    {
        height = (100+value)*180/200;
    }
    else
    {
        value = -value;
        height = (100-value)*180/200;
    }
    ui->Barlabel_TraBrakevalue->setGeometry(40,220-height,10,height+2);
    ui->Barlabel_TraBrakeLine->setGeometry(31,220-height,40,5);

}

void VehicleRunPage::setDoorStatus(QLabel *lbl, QList<bool> signal)
{
    //车门 offline--fault--bypass--emlock--obr--close--open
    if(!signal.at(0))
    {
        lbl->setStyleSheet(DOORUNKNOW);
    }else if(signal.at(1))
    {
        lbl->setStyleSheet(DOORFAULT);
    }else if(signal.at(2))
    {
        lbl->setStyleSheet(DOORBYPASS);
    }else if(signal.at(3))
    {
        lbl->setStyleSheet(DOOREMLOCK);
    }else if(signal.at(4))
    {
        lbl->setStyleSheet(DOOROB);
    }else if(signal.at(5))
    {
        lbl->setStyleSheet(DOORCLOSE);
    }else if(signal.at(6))
    {
        lbl->setStyleSheet(DOOROPEN);
    }else
    {
        lbl->setStyleSheet(DOORUNKNOW);
    }
}
void VehicleRunPage::setHVACStatus(QLabel *lbl, bool online, unsigned char signal)
{
    //空调 offline--fault--emven--cold--warm--ven--stop
    if(online)
    {
        switch (signal) {
        case 1:
            lbl->setStyleSheet(HVACFAULT);
            break;
        case 2:
        case 3:
            lbl->setStyleSheet(HVACRUN);
            break;
        case 4:
            lbl->setStyleSheet(HVACVEN);
            break;
        case 5:
            lbl->setStyleSheet(HVACOFF);
            break;
        case 6:
            lbl->setStyleSheet(HVACEMVEN);
            break;
        default:
            lbl->setStyleSheet(HVACUNKNOWN);
            break;
        }
    }else
    {
        lbl->setStyleSheet(HVACUNKNOWN);
    }

}
void VehicleRunPage::setPISStatus(QLabel* lbl,QList<bool> signal)
{
    //pis offline--fault--active--call--unactice
    if(!signal.at(0))
    {
        lbl->setStyleSheet(PISOFF);
    }else if(signal.at(1))
    {
        lbl->setStyleSheet(PISFAULT);
    }else if(signal.at(2))
    {
        lbl->setStyleSheet(PISACTIVE);
    }else if(signal.at(3))
    {
        lbl->setStyleSheet(PISCALL);
    }else
    {
        lbl->setStyleSheet(PISUNACTIVE);
    }
}
void VehicleRunPage::setBCUStatus(QLabel* lbl,QList<bool> signal)
{
    //制动 offline--not release--fault--apply--release
    if(!signal.at(0))
    {
        lbl->setStyleSheet(BCUOFF);
    }else if(signal.at(1))
    {
        lbl->setStyleSheet(BCUFAULT);
    }else if(signal.at(2))
    {
        lbl->setStyleSheet(BCUAPPLY);
    }else if(signal.at(3))
    {
        lbl->setStyleSheet(BCURELEASE);
    }else if(signal.at(4))
    {
        lbl->setStyleSheet(BCURELEASE);
    }else
    {
        lbl->setStyleSheet(PISUNACTIVE);
    }
}
void VehicleRunPage::setTCUStatus(QLabel* lbl,QList<bool> signal)
{

    if(!signal.at(0))
    {
        lbl->setStyleSheet(TCUOFF);
    }else if(signal.at(1))
    {
        lbl->setStyleSheet(TCUFAULT);
    }else if(signal.at(2))
    {
        lbl->setStyleSheet(TCURUN);
    }else
    {
        lbl->setStyleSheet(TCUSTOP);
    }
}
void VehicleRunPage::setACUStatus(QLabel* lbl,QList<bool> signal)
{

    if(!signal.at(0))
    {
        lbl->setStyleSheet(ACUOFF);
    }else if(signal.at(1))
    {
        lbl->setStyleSheet(ACUFAULT);
    }else if(signal.at(2))
    {
        lbl->setStyleSheet(ACURUN);
    }else
    {
        lbl->setStyleSheet(ACUSTOP);
    }
}
void VehicleRunPage::setBCCUStatus(QLabel* lbl,QList<bool> signal)
{

    if(!signal.at(0))
    {
        lbl->setStyleSheet(BCCUOFF);
    }else if(signal.at(1))
    {
        lbl->setStyleSheet(BCCUFAULT);
    }else if(signal.at(2))
    {
        lbl->setStyleSheet(BCCURUN);
    }else
    {
        lbl->setStyleSheet(BCCUSTOP);
    }
}
void VehicleRunPage::on_btn_VehicleRun_help_clicked()
{
    this->ui->groupBox->show();
    this->ui->groupBox->raise();
}
void VehicleRunPage::on_BTNCloseHelppage_pressed()
{
    this->ui->groupBox->hide();
}
void VehicleRunPage::closeEvent(QCloseEvent *)
{
    this->ui->groupBox->hide();
}

void VehicleRunPage::on_BTNStationSet_pressed()
{
    changePage(uVehicleSetStationPage);
}

void VehicleRunPage::on_BTNBypass_pressed()
{
    changePage(uVehicleBypassPage);
}
