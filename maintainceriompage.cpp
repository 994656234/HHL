#include "maintainceriompage.h"
#include "ui_maintainceriompage.h"

#define BUTTONPRESS "border-top:0px solid rgb(19,20,87);color: rgb(255, 255, 255);background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));font:16px \"微软雅黑\";"
#define BUTTONRELEASE "border-top:3px solid rgb(19,20,87);color: rgb(255, 255, 255);border-bottom:3px solid rgb(187,188,247);border-left:3px solid qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));border-right:3px solid qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(19,20,87), stop:1 rgb(187,188,247));font:16px \"微软雅黑\";"
#define DI_LENGTH 24
#define SPACE 0


MaintainceRIOMPage::MaintainceRIOMPage(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::MaintainceRIOMPage)
{
    ui->setupUi(this);
    buttons<<ui->TC_AIM<<ui->TC_DI1<<ui->TC_DI2<<ui->TC_DI3<<ui->TC_DI4<<ui->TC_DO<<ui->MP_DI<<ui->MP_DO;
    foreach(QPushButton* button,buttons)
    {
        connect(button,SIGNAL(pressed()),this,SLOT(buttonsPressEvent()));
    }

    tcdi1=new TCDIControl(this);
    tcdi1->setGeometry(20,30,tcdi1->width(),tcdi1->height());
    tcdi1->show();

    tcdo1=new TCDOControl(this);
    tcdo1->setGeometry(16,30,tcdo1->width(),tcdo1->height());
    tcdo1->hide();

    tcdo2=new TCDOControl(this);
    tcdo2->setGeometry(16,40+tcdo1->height(),tcdo2->width(),tcdo2->height());
    tcdo2->hide();

    ax1=new AXControl(this);
    ax1->setGeometry(95,30,ax1->width(),ax1->height());
    ax1->hide();

    ax2=new AXControl(this);
    ax2->setGeometry(95,40+ax1->height(),ax2->width(),ax2->height());
    ax2->hide();

    di1=new DIControl(this);
    di1->setGeometry(60,30,di1->width(),di1->height());
    di1->hide();

    do1=new DoControl(this);
    do1->setGeometry(60,30,do1->width(),do1->height());
    do1->hide();

    currentform = TC_DI1;
    ui->TC_DI1->setStyleSheet(BUTTONPRESS);
    QList <QString> Di1name;
    Di1name<<"司机室激活"<<"联挂状态"<<"AB箱感温电缆状态"<<"保留"<<"保留"<<"司机钥匙激活"
            <<"向前指令"<<"向后指令"<<"洗车模式"<<"牵引指令"<<"制动指令"<<"快速制动"
            <<"牵引安全"<<"警惕电路状态"<<"紧急牵引模式"<<"空压机启动状态"<<"ATC切除"<<"ATC折返"
            <<"ATO激活"<<"ATC牵引"<<"ATC制动"<<"ATC施加保持制动"<<"ATO开左门信号"<<"ATO开右门信号";

    this->tcdi1->initialName(Di1name,"DI1","TC");




}

MaintainceRIOMPage::~MaintainceRIOMPage()
{
    delete ui;
}

void MaintainceRIOMPage::on_BTNHome_pressed()
{
    changePage(uVehicleTrainArea);
}

void MaintainceRIOMPage::on_BTN1_pressed()
{
    changePage(uVehicleMaintainPage);
}

void MaintainceRIOMPage::updatePage()
{

    QList<bool> TCDI1Data,TCDI2Data,TCDI3Data,TCDI4Data,TCDO1Data,TCDO2Data,
                MPDI1Data,MPDO1Data,MDI1Data,MDO1Data;
    QList<QString>TCAXData1,TCAXData2;
    {
        /*

        TCDI1Data<<database->RM1CT_D1C1_CabAct_B1<<database->RM1CT_D1C2_Uncoupl_B1<<database->RM1CT_D1C3_ABWetLine_B1<<SPACE
                <<SPACE<<database->RM1CT_D1C6_CabKeyAct_B1<<database->RM1CT_D1C7_ForwadDr_B1<<database->RM1CT_D1C8_BackDr_B1
                <<database->RM1CT_D1C9_WashMode_B1<<database->RM1CT_D1C10_Trac_B1<<database->RM1CT_D1C11_Brk_B1<<database->RM1CT_D1C12_FB_B1
                <<database->RM1CT_D1C13_TrcSafe_B1<<database->RM1CT_D1C14_AlarmWork_B1<<database->RM1CT_D1C15_EmrTrc_B1<<database->RM1CT_D1C16_CompWork_B1
                <<database->RM1CT_D1C17_ATCCut_B1<<database->RM1CT_D1C18_ATCAutoBack_B1<<database->RM1CT_D1C19_ATCAct_B1<<database->RM1CT_D1C20_ATCTrc_B1
                <<database->RM1CT_D1C21_ATCBrk_B1<<database->RM1CT_D1C22_ATCHdBrkApl_B1<<database->RM1CT_D1C23_ATCOpLtDr_B1<<database->RM1CT_D1C24_ATCOpRtDr_B1
                <<database->RM1RCT_D1C1_CabAct_B1<<database->RM1RCT_D1C2_Uncoupl_B1<<database->RM1RCT_D1C3_ABWetLine_B1<<SPACE
                <<SPACE<<database->RM1RCT_D1C6_CabKeyAct_B1<<database->RM1RCT_D1C7_ForwadDr_B1<<database->RM1RCT_D1C8_BackDr_B1
                <<database->RM1RCT_D1C9_WashMode_B1<<database->RM1RCT_D1C10_Trac_B1<<database->RM1RCT_D1C11_Brk_B1<<database->RM1RCT_D1C12_FB_B1
                <<database->RM1RCT_D1C13_TrcSafe_B1<<database->RM1RCT_D1C14_AlarmWork_B1<<database->RM1RCT_D1C15_EmrTrc_B1<<database->RM1RCT_D1C16_CompWork_B1
                <<database->RM1RCT_D1C17_ATCCut_B1<<database->RM1RCT_D1C18_ATCAutoBack_B1<<database->RM1RCT_D1C19_ATCAct_B1<<database->RM1RCT_D1C20_ATCTrc_B1
                <<database->RM1RCT_D1C21_ATCBrk_B1<<database->RM1RCT_D1C22_ATCHdBrkApl_B1<<database->RM1RCT_D1C23_ATCOpLtDr_B1<<database->RM1RCT_D1C24_ATCOpRtDr_B1
                <<database->RM6RCT_D1C1_CabAct_B1<<database->RM6RCT_D1C2_Uncoupl_B1<<database->RM6RCT_D1C3_ABWetLine_B1<<SPACE
                <<SPACE<<database->RM6RCT_D1C6_CabKeyAct_B1<<database->RM6RCT_D1C7_ForwadDr_B1<<database->RM6RCT_D1C8_BackDr_B1
                <<database->RM6RCT_D1C9_WashMode_B1<<database->RM6RCT_D1C10_Trac_B1<<database->RM6RCT_D1C11_Brk_B1<<database->RM6RCT_D1C12_FB_B1
                <<database->RM6RCT_D1C13_TrcSafe_B1<<database->RM6RCT_D1C14_AlarmWork_B1<<database->RM6RCT_D1C15_EmrTrc_B1<<database->RM6RCT_D1C16_CompWork_B1
                <<database->RM6RCT_D1C17_ATCCut_B1<<database->RM6RCT_D1C18_ATCAutoBack_B1<<database->RM6RCT_D1C19_ATCAct_B1<<database->RM6RCT_D1C20_ATCTrc_B1
                <<database->RM6RCT_D1C21_ATCBrk_B1<<database->RM6RCT_D1C22_ATCHdBrkApl_B1<<database->RM6RCT_D1C23_ATCOpLtDr_B1<<database->RM6RCT_D1C24_ATCOpRtDr_B1
                <<database->RM6CT_D1C1_CabAct_B1<<database->RM6CT_D1C2_Uncoupl_B1<<database->RM6CT_D1C3_ABWetLine_B1<<SPACE
                <<SPACE<<database->RM6CT_D1C6_CabKeyAct_B1<<database->RM6CT_D1C7_ForwadDr_B1<<database->RM6CT_D1C8_BackDr_B1
                <<database->RM6CT_D1C9_WashMode_B1<<database->RM6CT_D1C10_Trac_B1<<database->RM6CT_D1C11_Brk_B1<<database->RM6CT_D1C12_FB_B1
                <<database->RM6CT_D1C13_TrcSafe_B1<<database->RM6CT_D1C14_AlarmWork_B1<<database->RM6CT_D1C15_EmrTrc_B1<<database->RM6CT_D1C16_CompWork_B1
                <<database->RM6CT_D1C17_ATCCut_B1<<database->RM6CT_D1C18_ATCAutoBack_B1<<database->RM6CT_D1C19_ATCAct_B1<<database->RM6CT_D1C20_ATCTrc_B1
                <<database->RM6CT_D1C21_ATCBrk_B1<<database->RM6CT_D1C22_ATCHdBrkApl_B1<<database->RM6CT_D1C23_ATCOpLtDr_B1<<database->RM6CT_D1C24_ATCOpRtDr_B1;

        TCDI2Data<<database->RM1CT_D2C1_EmrBrkLp_B1<<database->RM1CT_D2C2_ServBrkRlsLp_B1<<database->RM1CT_D2C3_AlmBtnPress_B1<<database->RM1CT_D2C4_HdBrkApl_B1
                <<database->RM1CT_D2C5_HdBrkRls_B1<<database->RM1CT_D2C6_SafLp_B1<<database->RM1CT_D2C7_RisPan_B1<<database->RM1CT_D2C8_DrpPan_B1
                <<SPACE<<database->RM1CT_D2C10_RisPanEnb_B1<<database->RM1CT_D2C11_ForcPump_B1<<database->RM1CT_D2C12_ZeroSpd_B1
                <<database->RM1CT_D2C13_ForcRls_B1<<database->RM1CT_D2C14_SIVReset_B1<<database->RM1CT_D2C15_HdBrkRlsLp_B1<<database->RM1CT_D2C16_DrMode_B1
                <<database->RM1CT_D2C17_OpnRtDrEnb_B1<<database->RM1CT_D2C18_OpnLtDrEnb_B1<<database->RM1CT_D2C19_ReClsOpn_B1<<database->RM1CT_D2C20_OpenLrDr_B1
                <<database->RM1CT_D2C21_CloseLtDr_B1<<database->RM1CT_D2C22_OpenRtDr_B1<<database->RM1CT_D2C23_CloseRtDr_B1<<database->RM1CT_D2C24_FireAlarm_B1
                <<database->RM1RCT_D2C1_EmrBrkLp_B1<<database->RM1RCT_D2C2_ServBrkRlsLp_B1<<database->RM1RCT_D2C3_AlmBtnPress_B1<<database->RM1RCT_D2C4_HdBrkApl_B1
                <<database->RM1RCT_D2C5_HdBrkRls_B1<<database->RM1RCT_D2C6_SafLp_B1<<database->RM1RCT_D2C7_RisPan_B1<<database->RM1RCT_D2C8_DrpPan_B1
                <<SPACE<<database->RM1RCT_D2C10_RisPanEnb_B1<<database->RM1RCT_D2C11_ForcPump_B1<<database->RM1RCT_D2C12_ZeroSpd_B1
                <<database->RM1RCT_D2C13_ForcRls_B1<<database->RM1RCT_D2C14_SIVReset_B1<<database->RM1RCT_D2C15_HdBrkRlsLp_B1<<database->RM1RCT_D2C16_DrMode_B1
                <<database->RM1RCT_D2C17_OpnRtDrEnb_B1<<database->RM1RCT_D2C18_OpnLtDrEnb_B1<<database->RM1RCT_D2C19_ReClsOpn_B1<<database->RM1RCT_D2C20_OpenLrDr_B1
                <<database->RM1RCT_D2C21_CloseLtDr_B1<<database->RM1RCT_D2C22_OpenRtDr_B1<<database->RM1RCT_D2C23_CloseRtDr_B1<<database->RM1RCT_D2C24_FireAlarm_B1
                <<database->RM6RCT_D2C1_EmrBrkLp_B1<<database->RM6RCT_D2C2_ServBrkRlsLp_B1<<database->RM6RCT_D2C3_AlmBtnPress_B1<<database->RM6RCT_D2C4_HdBrkApl_B1
                <<database->RM6RCT_D2C5_HdBrkRls_B1<<database->RM6RCT_D2C6_SafLp_B1<<database->RM6RCT_D2C7_RisPan_B1<<database->RM6RCT_D2C8_DrpPan_B1
                <<SPACE<<database->RM6RCT_D2C10_RisPanEnb_B1<<database->RM6RCT_D2C11_ForcPump_B1<<database->RM6RCT_D2C12_ZeroSpd_B1
                <<database->RM6RCT_D2C13_ForcRls_B1<<database->RM6RCT_D2C14_SIVReset_B1<<database->RM6RCT_D2C15_HdBrkRlsLp_B1<<database->RM6RCT_D2C16_DrMode_B1
                <<database->RM6RCT_D2C17_OpnRtDrEnb_B1<<database->RM6RCT_D2C18_OpnLtDrEnb_B1<<database->RM6RCT_D2C19_ReClsOpn_B1<<database->RM6RCT_D2C20_OpenLrDr_B1
                <<database->RM6RCT_D2C21_CloseLtDr_B1<<database->RM6RCT_D2C22_OpenRtDr_B1<<database->RM6RCT_D2C23_CloseRtDr_B1<<database->RM6RCT_D2C24_FireAlarm_B1
                <<database->RM6CT_D2C1_EmrBrkLp_B1<<database->RM6CT_D2C2_ServBrkRlsLp_B1<<database->RM6CT_D2C3_AlmBtnPress_B1<<database->RM6CT_D2C4_HdBrkApl_B1
                <<database->RM6CT_D2C5_HdBrkRls_B1<<database->RM6CT_D2C6_SafLp_B1<<database->RM6CT_D2C7_RisPan_B1<<database->RM6CT_D2C8_DrpPan_B1
                <<SPACE<<database->RM6CT_D2C10_RisPanEnb_B1<<database->RM6CT_D2C11_ForcPump_B1<<database->RM6CT_D2C12_ZeroSpd_B1
                <<database->RM6CT_D2C13_ForcRls_B1<<database->RM6CT_D2C14_SIVReset_B1<<database->RM6CT_D2C15_HdBrkRlsLp_B1<<database->RM6CT_D2C16_DrMode_B1
                <<database->RM6CT_D2C17_OpnRtDrEnb_B1<<database->RM6CT_D2C18_OpnLtDrEnb_B1<<database->RM6CT_D2C19_ReClsOpn_B1<<database->RM6CT_D2C20_OpenLrDr_B1
                <<database->RM6CT_D2C21_CloseLtDr_B1<<database->RM6CT_D2C22_OpenRtDr_B1<<database->RM6CT_D2C23_CloseRtDr_B1<<database->RM6CT_D2C24_FireAlarm_B1;

        TCDI3Data<<database->RM1CT_D3C1_BrkUnit1Cld_B1<<database->RM1CT_D3C2_BrkUnit2Cld_B1<<database->RM1CT_D3C3_ElcHt1Cld_B1<<database->RM1CT_D3C4_ElcHt2Cld_B1
                <<database->RM1CT_D3C5_Bog1Iso_B1<<database->RM1CT_D3C6_Bog2Iso_B1<<database->RM1CT_D3C7_HdBrkIso_B1<<database->RM1CT_D3C8_MRPIso_B1
                <<database->RM1CT_D3C9_DrClosedByps_B1<<database->RM1CT_D3C10_LtDrClosed_B1<<database->RM1CT_D3C11_RtDrClosed_B1<<database->RM1CT_D3C12_ZeroSpdByps_B1
                <<database->RM1CT_D3C13_BackupMode_B1<<database->RM1CT_D3C14_AlrmBtnByps_B1<<database->RM1CT_D3C15_PanRisEnbByps_B1<<database->RM1CT_D3C16_ServBrkResByps_B1
                <<database->RM1CT_D3C17_EmrBrkBtn_B1<<SPACE<<database->RM1CT_D3C19_HdBrkResByps_B1<<database->RM1CT_D3C20_CompPwr_B1
                <<database->RM1CT_D3C21_EmrBrkByps_B1<<database->RM1CT_D3C22_SafBrkByps_B1<<SPACE<<SPACE
                <<database->RM1RCT_D3C1_BrkUnit1Cld_B1<<database->RM1RCT_D3C2_BrkUnit2Cld_B1<<database->RM1RCT_D3C3_ElcHt1Cld_B1<<database->RM1RCT_D3C4_ElcHt2Cld_B1
                <<database->RM1RCT_D3C5_Bog1Iso_B1<<database->RM1RCT_D3C6_Bog2Iso_B1<<database->RM1RCT_D3C7_HdBrkIso_B1<<database->RM1RCT_D3C8_MRPIso_B1
                <<database->RM1RCT_D3C9_DrClosedByps_B1<<database->RM1RCT_D3C10_LtDrClosed_B1<<database->RM1RCT_D3C11_RtDrClosed_B1<<database->RM1RCT_D3C12_ZeroSpdByps_B1
                <<database->RM1RCT_D3C13_BackupMode_B1<<database->RM1RCT_D3C14_AlrmBtnByps_B1<<database->RM1RCT_D3C15_PanRisEnbByps_B1<<database->RM1RCT_D3C16_ServBrkResByps_B1
                <<database->RM1RCT_D3C17_EmrBrkBtn_B1<<SPACE<<database->RM1RCT_D3C19_HdBrkResByps_B1<<database->RM1RCT_D3C20_CompPwr_B1
                <<database->RM1RCT_D3C21_EmrBrkByps_B1<<database->RM1RCT_D3C22_SafBrkByps_B1<<SPACE<<SPACE
                <<database->RM6RCT_D3C1_BrkUnit1Cld_B1<<database->RM6RCT_D3C2_BrkUnit2Cld_B1<<database->RM6RCT_D3C3_ElcHt1Cld_B1<<database->RM6RCT_D3C4_ElcHt2Cld_B1
                <<database->RM6RCT_D3C5_Bog1Iso_B1<<database->RM6RCT_D3C6_Bog2Iso_B1<<database->RM6RCT_D3C7_HdBrkIso_B1<<database->RM6RCT_D3C8_MRPIso_B1
                <<database->RM6RCT_D3C9_DrClosedByps_B1<<database->RM6RCT_D3C10_LtDrClosed_B1<<database->RM6RCT_D3C11_RtDrClosed_B1<<database->RM6RCT_D3C12_ZeroSpdByps_B1
                <<database->RM6RCT_D3C13_BackupMode_B1<<database->RM6RCT_D3C14_AlrmBtnByps_B1<<database->RM6RCT_D3C15_PanRisEnbByps_B1<<database->RM6RCT_D3C16_ServBrkResByps_B1
                <<database->RM6RCT_D3C17_EmrBrkBtn_B1<<SPACE<<database->RM6RCT_D3C19_HdBrkResByps_B1<<database->RM6RCT_D3C20_CompPwr_B1
                <<database->RM6RCT_D3C21_EmrBrkByps_B1<<database->RM6RCT_D3C22_SafBrkByps_B1<<SPACE<<SPACE
                <<database->RM6CT_D3C1_BrkUnit1Cld_B1<<database->RM6CT_D3C2_BrkUnit2Cld_B1<<database->RM6CT_D3C3_ElcHt1Cld_B1<<database->RM6CT_D3C4_ElcHt2Cld_B1
                <<database->RM6CT_D3C5_Bog1Iso_B1<<database->RM6CT_D3C6_Bog2Iso_B1<<database->RM6CT_D3C7_HdBrkIso_B1<<database->RM6CT_D3C8_MRPIso_B1
                <<database->RM6CT_D3C9_DrClosedByps_B1<<database->RM6CT_D3C10_LtDrClosed_B1<<database->RM6CT_D3C11_RtDrClosed_B1<<database->RM6CT_D3C12_ZeroSpdByps_B1
                <<database->RM6CT_D3C13_BackupMode_B1<<database->RM6CT_D3C14_AlrmBtnByps_B1<<database->RM6CT_D3C15_PanRisEnbByps_B1<<database->RM6CT_D3C16_ServBrkResByps_B1
                <<database->RM6CT_D3C17_EmrBrkBtn_B1<<SPACE<<database->RM6CT_D3C19_HdBrkResByps_B1<<database->RM6CT_D3C20_CompPwr_B1
                <<database->RM6CT_D3C21_EmrBrkByps_B1<<database->RM6CT_D3C22_SafBrkByps_B1<<SPACE<<SPACE;

        TCDI4Data<<database->RM1CT_D4C1_LCUAWork_B1<<database->RM1CT_D4C2_LCUBWork_B1<<database->RM1CT_D4C3_LightSenrFlt_B1<<database->RM1CT_D4C4_LightPwr1Flt_B1
                <<database->RM1CT_D4C5_LightPwr1Flt_B1<<database->RM1CT_D4C6_CabKeyAct_B1<<database->RM1CT_D4C7_ForwadDr_B1<<database->RM1CT_D4C8_BackDr_B1
                <<SPACE<<database->RM1CT_D4C10_Trac_B1<<database->RM1CT_D4C11_Brk_B1<<database->RM1CT_D4C12_FB_B1
                <<SPACE<<SPACE<<database->RM1CT_D4C15_BatteryLoop_B1<<database->RM1CT_D4C16_CompWork_B1
                <<database->RM1CT_D4C17_DC24Stus_B1<<database->RM1CT_D4C18_ATCAutoBack_B1<<database->RM1CT_D4C19_ATCAct_B1<<database->RM1CT_D4C20_ATCTrc_B1
                <<database->RM1CT_D4C21_ATCBrk_B1<<database->RM1CT_D4C22_ATCdBrkApl_B1<<database->RM1CT_D4C23_LtDrClosed_B1<<database->RM1CT_D4C24_RtDrClosed_B1
                <<database->RM1RCT_D4C1_LCUAWork_B1<<database->RM1RCT_D4C2_LCUBWork_B1<<database->RM1RCT_D4C3_LightSenrFlt_B1<<database->RM1RCT_D4C4_LightPwr1Flt_B1
                <<database->RM1RCT_D4C5_LightPwr1Flt_B1<<database->RM1RCT_D4C6_CabKeyAct_B1<<database->RM1RCT_D4C7_ForwadDr_B1<<database->RM1RCT_D4C8_BackDr_B1
                <<SPACE<<database->RM1RCT_D4C10_Trac_B1<<database->RM1RCT_D4C11_Brk_B1<<database->RM1RCT_D4C12_FB_B1
                <<SPACE<<SPACE<<database->RM1RCT_D4C15_BatteryLoop_B1<<database->RM1RCT_D4C16_CompWork_B1
                <<database->RM1RCT_D4C17_DC24Stus_B1<<database->RM1RCT_D4C18_ATCAutoBack_B1<<database->RM1RCT_D4C19_ATCAct_B1<<database->RM1RCT_D4C20_ATCTrc_B1
                <<database->RM1RCT_D4C21_ATCBrk_B1<<database->RM1RCT_D4C22_ATCdBrkApl_B1<<database->RM1RCT_D4C23_LtDrClosed_B1<<database->RM1RCT_D4C24_RtDrClosed_B1
                <<database->RM6RCT_D4C1_LCUAWork_B1<<database->RM6RCT_D4C2_LCUBWork_B1<<database->RM6RCT_D4C3_LightSenrFlt_B1<<database->RM6RCT_D4C4_LightPwr1Flt_B1
                <<database->RM6RCT_D4C5_LightPwr1Flt_B1<<database->RM6RCT_D4C6_CabKeyAct_B1<<database->RM6RCT_D4C7_ForwadDr_B1<<database->RM6RCT_D4C8_BackDr_B1
                <<SPACE<<database->RM6RCT_D4C10_Trac_B1<<database->RM6RCT_D4C11_Brk_B1<<database->RM6RCT_D4C12_FB_B1
                <<SPACE<<SPACE<<database->RM6RCT_D4C15_BatteryLoop_B1<<database->RM6RCT_D4C16_CompWork_B1
                <<database->RM6RCT_D4C17_DC24Stus_B1<<database->RM6RCT_D4C18_ATCAutoBack_B1<<database->RM6RCT_D4C19_ATCAct_B1<<database->RM6RCT_D4C20_ATCTrc_B1
                <<database->RM6RCT_D4C21_ATCBrk_B1<<database->RM6RCT_D4C22_ATCdBrkApl_B1<<database->RM6RCT_D4C23_LtDrClosed_B1<<database->RM6RCT_D4C24_RtDrClosed_B1
                <<database->RM6CT_D4C1_LCUAWork_B1<<database->RM6CT_D4C2_LCUBWork_B1<<database->RM6CT_D4C3_LightSenrFlt_B1<<database->RM6CT_D4C4_LightPwr1Flt_B1
                <<database->RM6CT_D4C5_LightPwr1Flt_B1<<database->RM6CT_D4C6_CabKeyAct_B1<<database->RM6CT_D4C7_ForwadDr_B1<<database->RM6CT_D4C8_BackDr_B1
                <<SPACE<<database->RM6CT_D4C10_Trac_B1<<database->RM6CT_D4C11_Brk_B1<<database->RM6CT_D4C12_FB_B1
                <<SPACE<<SPACE<<database->RM6CT_D4C15_BatteryLoop_B1<<database->RM6CT_D4C16_CompWork_B1
                <<database->RM6CT_D4C17_DC24Stus_B1<<database->RM6CT_D4C18_ATCAutoBack_B1<<database->RM6CT_D4C19_ATCAct_B1<<database->RM6CT_D4C20_ATCTrc_B1
                <<database->RM6CT_D4C21_ATCBrk_B1<<database->RM6CT_D4C22_ATCdBrkApl_B1<<database->RM6CT_D4C23_LtDrClosed_B1<<database->RM6CT_D4C24_RtDrClosed_B1;

         MPDI1Data<<database->RM2CT_D1C1_BrkUnit1Cld_B1<<database->RM2CT_D1C2_BrkUnit2Cld_B1<<database->RM2CT_D1C3_ElcHt1Cld_B1<<database->RM2CT_D1C4_ElcHt2Cld_B1
                 <<database->RM2CT_D1C5_Bog1Iso_B1<<database->RM2CT_D1C6_Bog2Iso_B1<<database->RM2CT_D1C7_HdBrkIso_B1<<database->RM2CT_D1C8_MRPIso_B1
                 <<SPACE<<database->RM2CT_D1C10_ManRisPan_B1<<database->RM2CT_D1C11_LightSenrFlt_B1<<database->RM2CT_D1C12_LightPwr1Flt_B1
                 <<database->RM2CT_D1C13_LightPwr2Flt_B1<<SPACE<<database->RM2CT_D1C15_PanRiseEnb_B1<<SPACE
                 <<database->RM2CT_D1C17_PanUp_B1<<database->RM2CT_D1C18_PanDown_B1<<database->RM2CT_D1C19_ADDDrpPanFlt_B1<<database->RM2CT_D1C20_ErnRisPanOn_B1
                 <<database->RM2CT_D1C21_PHWetLine_B1<<database->RM2CT_D1C22_WkspSafe_B1<<SPACE<<SPACE
                 <<database->RM5CT_D1C1_BrkUnit1Cld_B1<<database->RM5CT_D1C2_BrkUnit2Cld_B1<<database->RM5CT_D1C3_ElcHt1Cld_B1<<database->RM5CT_D1C4_ElcHt2Cld_B1
                 <<database->RM5CT_D1C5_Bog1Iso_B1<<database->RM5CT_D1C6_Bog2Iso_B1<<database->RM5CT_D1C7_HdBrkIso_B1<<database->RM5CT_D1C8_MRPIso_B1
                 <<SPACE<<database->RM5CT_D1C10_ManRisPan_B1<<database->RM5CT_D1C11_LightSenrFlt_B1<<database->RM5CT_D1C12_LightPwr1Flt_B1
                 <<database->RM5CT_D1C13_LightPwr2Flt_B1<<SPACE<<database->RM5CT_D1C15_PanRiseEnb_B1<<SPACE
                 <<database->RM5CT_D1C17_PanUp_B1<<database->RM5CT_D1C18_PanDown_B1<<database->RM5CT_D1C19_ADDDrpPanFlt_B1<<database->RM5CT_D1C20_ErnRisPanOn_B1
                 <<database->RM5CT_D1C21_PHWetLine_B1<<database->RM5CT_D1C22_WkspSafe_B1<<SPACE<<SPACE;

         MDI1Data<<database->RM3CT_D1C1_BrkUnit1Cld_B1<<database->RM3CT_D1C2_BrkUnit2Cld_B1<<database->RM3CT_D1C3_ElcHt1Cld_B1<<database->RM3CT_D1C4_ElcHt2Cld_B1
                 <<database->RM3CT_D1C5_Bog1Iso_B1<<database->RM3CT_D1C6_Bog2Iso_B1<<database->RM3CT_D1C7_HdBrkIso_B1<<database->RM3CT_D1C8_MRPIso_B1
                 <<database->RM3CT_D1C9_LightSenrFlt_B1<<database->RM3CT_D1C10_LightPwr1Flt_B1<<database->RM3CT_D1C11_LightPwr2Flt_B1<<SPACE
                 <<database->RM3CT_D1C13_Uncoupl_B1<<SPACE<<SPACE<<SPACE
                 <<SPACE<<SPACE<<SPACE<<SPACE
                 <<database->RM3CT_D1C21_PAWetLine_B1<<SPACE<<SPACE<<SPACE

                 <<database->RM4CT_D1C1_BrkUnit1Cld_B1<<database->RM4CT_D1C2_BrkUnit2Cld_B1<<database->RM4CT_D1C3_ElcHt1Cld_B1<<database->RM4CT_D1C4_ElcHt2Cld_B1
                 <<database->RM4CT_D1C5_Bog1Iso_B1<<database->RM4CT_D1C6_Bog2Iso_B1<<database->RM4CT_D1C7_HdBrkIso_B1<<database->RM4CT_D1C8_MRPIso_B1
                 <<database->RM4CT_D1C9_LightSenrFlt_B1<<database->RM4CT_D1C10_LightPwr1Flt_B1<<database->RM4CT_D1C11_LightPwr2Flt_B1<<SPACE
                 <<database->RM4CT_D1C13_Uncoupl_B1<<SPACE<<SPACE<<SPACE
                 <<SPACE<<SPACE<<SPACE<<SPACE
                 <<database->RM4CT_D1C21_PAWetLine_B1<<SPACE<<SPACE<<SPACE;

         TCAXData1<<SPACE<<SPACE<<SPACE<<QString::number(database->RM1CT_AI1C4_ATCMCLv_U16)
                 <<SPACE<<SPACE<<QString::number(database->RM1CT_AI1C7_MCLv_U16)<<SPACE
                 <<SPACE<<SPACE<<SPACE<<QString::number(database->RM1RCT_AI1C4_ATCMCLv_U16)
                 <<SPACE<<SPACE<<QString::number(database->RM1RCT_AI1C7_MCLv_U16)<<SPACE
                 <<SPACE<<SPACE<<SPACE<<QString::number(database->RM6RCT_AI1C4_ATCMCLv_U16)
                 <<SPACE<<SPACE<<QString::number(database->RM6RCT_AI1C7_MCLv_U16)<<SPACE
                 <<SPACE<<SPACE<<SPACE<<QString::number(database->RM6CT_AI1C4_ATCMCLv_U16)
                 <<SPACE<<SPACE<<QString::number(database->RM6CT_AI1C7_MCLv_U16)<<SPACE;

          TCAXData2<<SPACE<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<QString::number(database->RM1CT_AI2C7_MCLv_U16)<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<QString::number(database->RM1RCT_AI2C7_MCLv_U16)<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<QString::number(database->RM6RCT_AI2C7_MCLv_U16)<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<QString::number(database->RM6CT_AI2C7_MCLv_U16)<<SPACE;

          TCDO1Data<<database->CTRM1_DO1CH1_TrainBack_B1<<database->CTRM1_DO1CH2_PandoUp_B1<<database->CTRM1_DO1CH3_PandoDown_B1<<database->CTRM1_DO1CH4_HBClosed_B1
                  <<database->CTRM1_DO1CH5_HBOpen_B1<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE
                  <<database->CTRM1R_DO1CH1_TrainBack_B1<<database->CTRM1R_DO1CH2_PandoUp_B1<<database->CTRM1R_DO1CH3_PandoDown_B1<<database->CTRM1R_DO1CH4_HBClosed_B1
                  <<database->CTRM1R_DO1CH5_HBOpen_B1<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE
                  <<database->CTRM6R_DO1CH1_TrainBack_B1<<database->CTRM6R_DO1CH2_PandoUp_B1<<database->CTRM6R_DO1CH3_PandoDown_B1<<database->CTRM6R_DO1CH4_HBClosed_B1
                  <<database->CTRM6R_DO1CH5_HBOpen_B1<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE
                  <<database->CTRM6_DO1CH1_TrainBack_B1<<database->CTRM6_DO1CH2_PandoUp_B1<<database->CTRM6_DO1CH3_PandoDown_B1<<database->CTRM6_DO1CH4_HBClosed_B1
                  <<database->CTRM6_DO1CH5_HBOpen_B1<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE
                  <<SPACE<<SPACE<<SPACE<<SPACE;

            TCDO2Data<<database->CTRM1_DO2CH1_B1<<SPACE<<database->CTRM1_DO2CH3_B1<<SPACE
                    <<database->CTRM1_DO2CH5_EmrLight_B1<<SPACE<<SPACE<<SPACE
                    <<SPACE<<SPACE<<SPACE<<SPACE
                    <<SPACE<<SPACE<<SPACE<<SPACE
                    <<database->CTRM1R_DO2CH1_B1<<SPACE<<database->CTRM1R_DO2CH3_B1<<SPACE
                    <<database->CTRM1R_DO2CH5_EmrLight_B1<<SPACE<<SPACE<<SPACE
                    <<SPACE<<SPACE<<SPACE<<SPACE
                    <<SPACE<<SPACE<<SPACE<<SPACE
                    <<database->CTRM6R_DO2CH1_B1<<SPACE<<database->CTRM6R_DO2CH3_B1<<SPACE
                    <<database->CTRM6R_DO2CH5_EmrLight_B1<<SPACE<<SPACE<<SPACE
                    <<SPACE<<SPACE<<SPACE<<SPACE
                    <<SPACE<<SPACE<<SPACE<<SPACE
                    <<database->CTRM6_DO2CH1_B1<<SPACE<<database->CTRM6_DO2CH3_B1<<SPACE
                    <<database->CTRM6_DO2CH5_EmrLight_B1<<SPACE<<SPACE<<SPACE
                    <<SPACE<<SPACE<<SPACE<<SPACE
                    <<SPACE<<SPACE<<SPACE<<SPACE;


             MPDO1Data<<SPACE<<SPACE<<database->CTRM2_DO1CH3_EmrLight_B1<<SPACE
                     <<SPACE<<SPACE<<SPACE<<SPACE
                     <<SPACE<<SPACE<<SPACE<<SPACE
                     <<SPACE<<SPACE<<SPACE<<SPACE
                     <<SPACE<<SPACE<<database->CTRM5_DO1CH3_EmrLight_B1<<SPACE
                     <<SPACE<<SPACE<<SPACE<<SPACE
                     <<SPACE<<SPACE<<SPACE<<SPACE
                     <<SPACE<<SPACE<<SPACE<<SPACE;

                     */

    }
    switch (currentform)
    {
    case TC_DI1:
        this->tcdi1->updateDi(TCDI1Data);
        break;
    case TC_DI2:
        this->tcdi1->updateDi(TCDI2Data);
        break;
    case TC_DI3:
        this->tcdi1->updateDi(TCDI3Data);
        break;
    case TC_DI4:
        this->tcdi1->updateDi(TCDI4Data);
        break;
    case TC_DO:
        this->tcdo1->updateDo(TCDO1Data);
        this->tcdo2->updateDo(TCDO2Data);
        break;
    case TC_AIM:
        this->ax1->updateAx(TCAXData1);
        this->ax2->updateAx(TCAXData2);
        break;
    case MP_DI:
        this->di1->updateDi(MPDI1Data);
        break;
    case MP_DO:
        this->do1->updateDo(MPDO1Data);
        break;
    }



}


void MaintainceRIOMPage::buttonsPressEvent()
{
     QString btnName = ((QPushButton *)this->sender())->objectName();
     if(btnName=="TC_DI1")
     {
         refreshAllButtons();
         ui->TC_DI1->setStyleSheet(BUTTONPRESS);
         currentform = TC_DI1;
         QList <QString> Di1name;
         Di1name<<"司机室激活"<<"联挂状态"<<"AB箱感温电缆状态"<<"保留"<<"保留"<<"司机钥匙激活"
                 <<"向前指令"<<"向后指令"<<"洗车模式"<<"牵引指令"<<"制动指令"<<"快速制动"
                 <<"牵引安全"<<"警惕电路状态"<<"紧急牵引模式"<<"空压机启动状态"<<"ATC切除"<<"ATC折返"
                 <<"ATO激活"<<"ATC牵引"<<"ATC制动"<<"ATC施加保持制动"<<"ATO开左门信号"<<"ATO开右门信号";
         this->tcdi1->initialName(Di1name,"DI1","MC");
         this->tcdi1->show();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();
     }
     else if(btnName=="TC_DI2")
     {
         refreshAllButtons();
         ui->TC_DI2->setStyleSheet(BUTTONPRESS);
         currentform=TC_DI2;
         QList<QString> Di2Name;
         Di2Name<<"紧急制动环路"<<"常用制动缓解环路状态"<<"警惕按钮按下"<<"停放制动施加指令"<<"停放制动缓解指令"<<"安全环路状态"<<"升弓指令"<<"降弓指令"
                 <<"保留"<<"升弓使能旁路"<<"强迫泵风指令"<<"零速环路状态"<<"强迫缓解指令"<<"逆变器复位"<<"停放制动缓解环路状态"<<"门模式开关"
                 <<"开右门使能"<<"开左门使能"<<"再开闭"<<"开左门信号"<<"关左门信号"<<"开右门信号"<<"关右门信号"<<"火灾报警";

         this->tcdi1->initialName(Di2Name,"DI2","MC");
         this->tcdi1->show();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();

     }
     else if(btnName=="TC_DI3")
     {
         refreshAllButtons();
         ui->TC_DI3->setStyleSheet(BUTTONPRESS);
         currentform=TC_DI3;
         QList<QString> Di3Name;
         Di3Name<<"制动单元电源1状态"<<"制动单元电源2状态"<<"电热接触器1状态"<<"电热接触器2状态"<<"转向架1隔离状态"<<"转向架2隔离状态"<<"停放制动隔离状态"<<"总风隔离状态"
                 <<"门关好旁路"<<"左门关好"<<"右门关好"<<"零速旁路开关"<<"备用模式"<<"警惕按钮旁路"<<"升弓使能旁路"<<"常用缓解旁路"
                 <<"紧急制动按钮"<<"保留"<<"停放制动缓解旁路"<<"空压机供电状态"<<"紧急制动旁路"<<"安全环路旁路"<<"保留"<<"保留";
         this->tcdi1->initialName(Di3Name,"DI3","MC");
         this->tcdi1->show();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();
     }
     else if(btnName=="TC_DI4")
     {
         refreshAllButtons();
         ui->TC_DI4->setStyleSheet(BUTTONPRESS);
         currentform=TC_DI4;
         QList<QString> Di4Name;
         Di4Name<<"LCU选择A组"<<"LCU选择B组"<<"光传感器故障"<<"客室一路照明电源故障"<<"客室二路照明电源故障"<<"司机钥匙激活"<<"向前指令"<<"向后指令"
                 <<"保留"<<"牵引指令"<<"制动指令"<<"快速制动"<<"保留"<<"保留"<<"蓄电池启动环路状态"<<"蓄电池输出接触器状态"
                 <<"DC24V模块状态"<<"ATC折返"<<"ATO激活"<<"ATC牵引"<<"ATC制动"<<"ATC施加保持制动"<<"右门关好"<<"左门关好";
         this->tcdi1->initialName(Di4Name,"DI4","MC");
         this->tcdi1->show();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();

     }
     else if(btnName=="MP_DI")
     {
         refreshAllButtons();
         ui->MP_DI->setStyleSheet(BUTTONPRESS);
         currentform=MP_DI;
         QList<QString> MPDi1Name;
         MPDi1Name<<"制动单元电源1状态"<<"制动单元电源2状态"<<"电热接触器1状态"<<"电热接触器2状态"<<"转向架1隔离状态"<<"转向架2隔离状态"<<"停放制动隔离状态"<<"总风隔离状态"
                 <<"保留"<<"人工升弓(仅MP2车)"<<"光传感器故障"<<"客室一路侧照明电源故障"<<"客室二路侧照明电源故障"<<"保留"<<"升弓允许(仅MP1车)"<<"保留"
                 <<"升弓到位状态"<<"降弓到位状态"<<"ADD故障降弓"<<"应急升弓泵工作(仅MP1车)"<<"PH箱感温电缆状态"<<"车间电源安全"<<"保留"<<"保留";
         this->di1->initialName(MPDi1Name,"DI1","MP");
         this->tcdi1->hide();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->show();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();

     }
     else if(btnName=="TC_DO")
     {
         refreshAllButtons();
         ui->TC_DO->setStyleSheet(BUTTONPRESS);
         currentform=TC_DO;
         QList<QString> TCDo1Name,TCDo2Name;
         TCDo1Name<<"列车后溜"<<"受电弓升指示"<<"受电弓降指示"<<"高速断路器合指示"<<"高速断路器断指示"<<"保留"<<"保留"<<"保留"
                 <<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留";
         TCDo2Name<<"列车后溜"<<"保留"<<"空压机启动"<<"保留"<<"应急照明启动"<<"保留"<<"保留"<<"保留"
                 <<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留";
         this->tcdo1->initialName(TCDo1Name,"DO1","MC");
         this->tcdo2->initialName(TCDo2Name,"DO2","MC");
         this->tcdi1->hide();
         this->tcdo1->show();
         this->tcdo2->show();
         this->di1->hide();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();

     }
     else if(btnName=="MP_DO")
     {
         refreshAllButtons();
         ui->MP_DO->setStyleSheet(BUTTONPRESS);
         currentform=MP_DO;
         QList<QString> MPDo1Name;
         MPDo1Name<<"保留"<<"保留"<<"应急照明启动"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"
                 <<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留";
         this->do1->initialName(MPDo1Name,"DO1","MP");
         this->tcdi1->hide();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->show();
         this->ax1->hide();
         this->ax2->hide();
     }

     else if(btnName=="TC_AIM")
     {
         refreshAllButtons();
         ui->TC_AIM->setStyleSheet(BUTTONPRESS);
         currentform=TC_AIM;
         QList<QString> AIMName1,AIMName2;
         AIMName1<<"保留"<<"保留"<<"保留"<<"司控器级位电流采集（信号）"<<"保留"<<"保留"<<"司控器级位电压采集"<<"保留";
         AIMName2<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"司控器级位电压采集"<<"保留";
         this->ax1->initialName(AIMName1);
         this->ax2->initialName(AIMName2);
         this->tcdi1->hide();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->hide();
         this->ax1->show();
         this->ax2->show();

     }
     else
     {}



}


void MaintainceRIOMPage::refreshAllButtons()
{
    foreach(QPushButton* button,buttons)
    {
        button->setStyleSheet(BUTTONRELEASE);
    }
}
