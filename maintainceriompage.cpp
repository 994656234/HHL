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
    buttons<<ui->TC_AIM<<ui->TC_DI1<<ui->TC_DI2<<ui->TC_DI3<<ui->TC_DI4<<ui->TC_DI5<<ui->TC_DI6<<ui->TC_DO<<ui->MP_DI<<ui->MP_DI2;
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
    Di1name<<"轮缘润滑继电器"<<"踏面清扫继电器"<<"CTS开关"<<"睡眠继电器"<<"司机室占有"<<"列车联挂继电器"
            <<"紧急制动控制断路器"<<"警惕按钮旁路开关状态"<<"警惕按钮延时继电器"<<"总风欠压旁路开关状态"<<"紧急制动接触器"<<"VCU触发的紧急制动继电器"
            <<"紧急制动按钮继电器"<<"紧急制动旁路开关"<<"紧急制动继电器"<<"零速继电器1~5"<<"停放制动施加接触器"<<"所有停放制动缓解断路器"
            <<"所有停放制动缓解继电器"<<"所有气制动旁路开关"<<"所有制动都缓解"<<"紧急制动列车线"<<"远程缓解列车线"<<"司控器断路器";

    this->tcdi1->initialName(Di1name,"DI1","MC");




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

    QList<bool> TCDI1Data,TCDI2Data,TCDI3Data,TCDI4Data,TCDI5Data,TCDI6Data,TCDO1Data,TCDO2Data,
                MPDI1Data,MPDI2Data;
    QList<QString>TCAXData1;
    {

        TCDI1Data<<database->RM1CT_WFLR_B1<<database->RM1CT_TCR_B1<<database->RM1CT_CTS_B1<<database->RM1CT_SLR_B1
                <<database->RM1CT_COR_B1<<database->RM1CT_CTR_B1<<database->RM1CT_EBCB_B1<<database->RM1CT_DMBPS_B1
               <<database->RM1CT_DMYR_B1<<database->RM1CT_LMRGBS_B1<<database->RM1CT_EBK_B1<<database->RM1CT_VCUEBR_B1
              <<database->RM1CT_EMPBR_B1<<database->RM1CT_EBBS_B1<<database->RM1CT_EBR_B1<<database->RM1CT_ZVR_B1
             <<database->RM1CT_PBK_B1<<database->RM1CT_APBRCB_B1<<database->RM1CT_APBRR_B1<<database->RM1CT_ABRBS_B1
            <<database->RM1CT_ETABRR_B1<<database->RM1CT_ETEBL_B1<<database->RM1CT_ETRRL_B1<<database->RM1CT_MCCB_B1

           <<database->RM4CT_WFLR_B1<<database->RM4CT_TCR_B1<<database->RM4CT_CTS_B1<<database->RM4CT_SLR_B1
           <<database->RM4CT_COR_B1<<database->RM4CT_CTR_B1<<database->RM4CT_EBCB_B1<<database->RM4CT_DMBPS_B1
           <<database->RM4CT_DMYR_B1<<database->RM4CT_LMRGBS_B1<<database->RM4CT_EBK_B1<<database->RM4CT_VCUEBR_B1
           <<database->RM4CT_EMPBR_B1<<database->RM4CT_EBBS_B1<<database->RM4CT_EBR_B1<<database->RM4CT_ZVR_B1
           <<database->RM4CT_PBK_B1<<database->RM4CT_APBRCB_B1<<database->RM4CT_APBRR_B1<<database->RM4CT_ABRBS_B1
           <<database->RM4CT_ETABRR_B1<<database->RM4CT_ETEBL_B1<<database->RM4CT_ETRRL_B1<<database->RM4CT_MCCB_B1;

        TCDI2Data<<database->RM1CT_RVBPS_B1<<database->RM1CT_HSCBON_B1<<database->RM1CT_HSCBOFF_B1<<database->RM1CT_Keyrtainline_B1
                <<database->RM1CT_TDL_B1<<database->RM1CT_BDL_B1<<database->RM1CT_FBDL_B1<<database->RM1CT_ETFL_B1
               <<database->RM1CT_ETRL_B1<<database->RM1CT_RESTART_B1<<database->RM1CT_ETETML_B1<<database->RM1CT_PBRBPS_B1
              <<database->RM1CT_PEBS_B1<<database->RM1CT_DIRL12_B1<<database->RM1CT_DIRR12_B1<<database->RM1CT_DRARL_B1
             <<database->RM1CT_DRARR_B1<<database->RM1CT_DOCRL_B1<<database->RM1CT_DOCRR_B1<<database->RM1CT_DCCRL_B1
            <<database->RM1CT_DCCRR_B1<<database->RM1CT_AMR_B1<<database->RM1CT_ARR12_B1<<database->RM1CT_CTSHSD_B1

        <<database->RM4CT_RVBPS_B1<<database->RM4CT_HSCBON_B1<<database->RM4CT_HSCBOFF_B1<<database->RM4CT_Keyrtainline_B1
                        <<database->RM4CT_TDL_B1<<database->RM4CT_BDL_B1<<database->RM4CT_FBDL_B1<<database->RM4CT_ETFL_B1
                       <<database->RM4CT_ETRL_B1<<database->RM4CT_RESTART_B1<<database->RM4CT_ETETML_B1<<database->RM4CT_PBRBPS_B1
                      <<database->RM4CT_PEBS_B1<<database->RM4CT_DIRL12_B1<<database->RM4CT_DIRR12_B1<<database->RM4CT_DRARL_B1
                     <<database->RM4CT_DRARR_B1<<database->RM4CT_DOCRL_B1<<database->RM4CT_DOCRR_B1<<database->RM4CT_DCCRL_B1
                    <<database->RM4CT_DCCRR_B1<<database->RM4CT_AMR_B1<<database->RM4CT_ARR12_B1<<database->RM4CT_CTSHSD_B1;

        TCDI3Data<<database->RM1CT_DBPS_B1<<database->RM1CT_ATPFS_B1<<database->RM1CT_DRBYS_B1<<database->RM1CT_ATPACTIVE_B1
                <<database->RM1CT_RDER_B1<<database->RM1CT_LDER_B1<<database->RM1CT_VZCR_B1<<database->RM1CT_ATOHOLDINGBRAKE_B1
               <<database->RM1CT_PDCS_B1<<database->RM1CT_TLPB_B1<<database->RM1CT_RRPB_B1<<database->RM1CT_EMPB_B1
              <<database->RM1CT_DBYS_B1<<database->RM1CT_COAST_B1<<database->RM1CT_DMS_B1<<database->RM1CT_WM_B1
             <<database->RM1CT_ATPOUTBRAKE_B1<<database->RM1CT_AMTDR_B1<<database->RM1CT_AMBDR_B1<<database->RM1CT_ATPFK1_B1
            <<database->RM1CT_ATPFK2_B1<<database->RM1CT_ATPOTCB_B1<<database->RM1CT_DORSL_B1<<database->RM1CT_DORSR_B1

        <<database->RM4CT_DBPS_B1<<database->RM4CT_ATPFS_B1<<database->RM4CT_DRBYS_B1<<database->RM4CT_ATPACTIVE_B1
                        <<database->RM4CT_RDER_B1<<database->RM4CT_LDER_B1<<database->RM4CT_VZCR_B1<<database->RM4CT_ATOHOLDINGBRAKE_B1
                       <<database->RM4CT_PDCS_B1<<database->RM4CT_TLPB_B1<<database->RM4CT_RRPB_B1<<database->RM4CT_EMPB_B1
                      <<database->RM4CT_DBYS_B1<<database->RM4CT_COAST_B1<<database->RM4CT_DMS_B1<<database->RM4CT_WM_B1
                     <<database->RM4CT_ATPOUTBRAKE_B1<<database->RM4CT_AMTDR_B1<<database->RM4CT_AMBDR_B1<<database->RM4CT_ATPFK1_B1
                    <<database->RM4CT_ATPFK2_B1<<database->RM4CT_ATPOTCB_B1<<database->RM4CT_DORSL_B1<<database->RM4CT_DORSR_B1;

        TCDI4Data<<database->RM1CT_ZVBS_B1<<database->RM1CT_ZVRCB1_B1<<database->RM1CT_ZVRCB2_B1<<database->RM1CT_DOTCB_B1
                <<database->RM1CT_DCTCB_B1<<database->RM1CT_DRCBL_B1<<database->RM1CT_DRCBR_B1<<database->RM1CT_DENACB_B1
               <<database->RM1CT_BSCB_B1<<SPACE<<SPACE<<SPACE
                 <<SPACE<<SPACE<<SPACE<<SPACE
                   <<SPACE<<SPACE<<SPACE<<SPACE
                     <<SPACE<<SPACE<<SPACE<<SPACE
        <<database->RM4CT_ZVBS_B1<<database->RM4CT_ZVRCB1_B1<<database->RM4CT_ZVRCB2_B1<<database->RM4CT_DOTCB_B1
                        <<database->RM4CT_DCTCB_B1<<database->RM4CT_DRCBL_B1<<database->RM4CT_DRCBR_B1<<database->RM4CT_DENACB_B1
                       <<database->RM4CT_BSCB_B1<<SPACE<<SPACE<<SPACE
                         <<SPACE<<SPACE<<SPACE<<SPACE
                           <<SPACE<<SPACE<<SPACE<<SPACE
                             <<SPACE<<SPACE<<SPACE<<SPACE;

        TCDI5Data<<database->RM2CT_BRR1_B1<<database->RM2CT_BRR2_B1<<database->RM2CT_RDRTL_B1<<database->RM2CT_RODTL_B1
                <<database->RM2CT_RCDTL_B1<<database->RM2CT_LZVTLR_B1<<database->RM2CT_RZVTLR_B1<<database->RM2CT_LDRTL_B1
               <<database->RM2CT_LODTL_B1<<database->RM2CT_LCDTL_B1<<database->RM2CT_LZVTLL_B1<<database->RM2CT_RZVTLL_B1
              <<database->RM2CT_VRFAULT_B1<<SPACE<<database->RM2CT_TDL_B1<<database->RM2CT_BDL_B1<<database->RM2CT_ETFL_B1
             <<database->RM2CT_ETRL_B1<<database->RM2CT_BMSCB_B1<<SPACE<<SPACE
               <<SPACE<<SPACE<<SPACE

        <<database->RM5CT_BRR1_B1<<database->RM5CT_BRR2_B1<<database->RM5CT_RDRTL_B1<<database->RM5CT_RODTL_B1
                        <<database->RM5CT_RCDTL_B1<<database->RM5CT_LZVTLR_B1<<database->RM5CT_RZVTLR_B1<<database->RM5CT_LDRTL_B1
                       <<database->RM5CT_LODTL_B1<<database->RM5CT_LCDTL_B1<<database->RM5CT_LZVTLL_B1<<database->RM5CT_RZVTLL_B1
                      <<database->RM5CT_VRFAULT_B1<<SPACE<<database->RM5CT_TDL_B1<<database->RM5CT_BDL_B1<<database->RM5CT_ETFL_B1
                     <<database->RM5CT_ETRL_B1<<database->RM5CT_BMSCB_B1<<SPACE<<SPACE
                       <<SPACE<<SPACE<<SPACE;

        TCDI6Data<<database->RM2CT_TSK_B1<<database->RM2CT_CSCB_B1<<database->RM2CT_BATTERY_B1<<database->RM2CT_standbyfuse_B1
                <<database->RM2CT_LVDR_B1<<database->RM2CT_batterybreaker_B1<<database->RM2CT_middlegrounding_B1<<database->RM2CT_BIS_B1
               <<database->RM2CT_MRPS_B1<<database->RM2CT_SIV_B1<<database->RM2CT_ADUPS1_B1<<database->RM2CT_ADUPS2_B1
              <<database->RM2CT_BBIV1_B1<<database->RM2CT_BBIV2_B1<<database->RM2CT_PBIV_B1<<database->RM2CT_Batteryfuse_B1
             <<database->RM2CT_CMK_B1<<database->RM2CT_CBBIV_B1<<database->RM2CT_EWSV_B1<<database->RM2CT_VVVF3arlm_B1
            <<database->RM2CT_SIVTEMPARLM_B1<<SPACE<<SPACE<<SPACE

        <<database->RM5CT_TSK_B1<<database->RM5CT_CSCB_B1<<database->RM5CT_BATTERY_B1<<database->RM5CT_standbyfuse_B1
                        <<database->RM5CT_LVDR_B1<<database->RM5CT_batterybreaker_B1<<database->RM5CT_middlegrounding_B1<<database->RM5CT_BIS_B1
                       <<database->RM5CT_MRPS_B1<<database->RM5CT_SIV_B1<<database->RM5CT_ADUPS1_B1<<database->RM5CT_ADUPS2_B1
                      <<database->RM5CT_BBIV1_B1<<database->RM5CT_BBIV2_B1<<database->RM5CT_PBIV_B1<<database->RM5CT_Batteryfuse_B1
                     <<database->RM5CT_CMK_B1<<database->RM5CT_CBBIV_B1<<database->RM5CT_EWSV_B1<<database->RM5CT_VVVF3arlm_B1
                    <<database->RM5CT_SIVTEMPARLM_B1<<SPACE<<SPACE<<SPACE;


        TCDO1Data<<database->CTR1_DOWFLR_B1<<database->CTR1_DOTCR_B1<<database->CTR1_DOHVIVDCP_B1<<database->CTR1_DOHIVNC_B1
                <<database->CTR1_DOLVDR_B1<<database->CTR1_DOLOASMON_B1<<database->CTR1_DOBSOI_B1<<database->CTR1_DOPANDI_B1
               <<database->CTR1_DOPANI_B1<<database->CTR1_DOHSCBC_B1<<database->CTR1_DOHSCB0_B1<<database->CTR1_DOVCUEBR_B1
              <<database->CTR1_DOLOACHF_B1<<SPACE<<SPACE<<SPACE
             <<database->CTR4_DOWFLR_B1<<database->CTR4_DOTCR_B1<<database->CTR4_DOHVIVDCP_B1<<database->CTR4_DOHIVNC_B1
                             <<database->CTR4_DOLVDR_B1<<database->CTR4_DOLOASMON_B1<<database->CTR4_DOBSOI_B1<<database->CTR4_DOPANDI_B1
                            <<database->CTR4_DOPANI_B1<<database->CTR4_DOHSCBC_B1<<database->CTR4_DOHSCB0_B1<<database->CTR4_DOVCUEBR_B1
                           <<database->CTR4_DOLOACHF_B1<<SPACE<<SPACE<<SPACE;

        TCAXData1<<QString::number(database->RM1CT_MCREFSETPOINT_U16)<<QString::number(database->RM1CT_ATCREF_U16)<<""<<""
                <<""<<""<<""<<""
               <<QString::number(database->RM4CT_MCREFSETPOINT_U16)<<QString::number(database->RM4CT_ATCREF_U16)<<""<<""
                               <<""<<""<<""<<"";

        MPDI1Data<<database->RM3CT_BRR1_B1<<database->RM3CT_BRR2_B1<<database->RM3CT_MPlightfault_B1<<database->RM3CT_DOWNPAN_B1
                <<database->RM3CT_UPPAN_B1<<database->RM3CT_UPRPAN_B1<<database->RM3CT_PTCB_B1<<database->RM3CT_HVBCB1_B1
                <<database->RM3CT_HVBCB2_B1<<database->RM3CT_PANEBR_B1<<database->RM3CT_FUSE_B1<<database->RM3CT_HSCB1STATE_B1
                <<database->RM3CT_HSCB2STATE_B1<<database->RM3CT_BBIV1_B1<<database->RM3CT_BBIV2_B1<<database->RM3CT_PBIV_B1
                <<database->RM3CT_ExtendPower_B1<<database->RM3CT_ACUPowerCover_B1<<database->RM3CT_PANIV_B1<<database->RM3CT_VVVF1TEMPARLM_B1
                <<database->RM3CT_VVVF2TEMPARLM_B1<<database->RM3CT_WOSEBR_B1<<database->RM3CT_BMSCB_B1<<SPACE

           <<database->RM6CT_BRR1_B1<<database->RM6CT_BRR2_B1<<database->RM6CT_MPlightfault_B1<<database->RM6CT_DOWNPAN_B1
           <<database->RM6CT_UPPAN_B1<<database->RM6CT_UPRPAN_B1<<database->RM6CT_PTCB_B1<<database->RM6CT_HVBCB1_B1
           <<database->RM6CT_HVBCB2_B1<<database->RM6CT_PANEBR_B1<<database->RM6CT_FUSE_B1<<database->RM6CT_HSCB1STATE_B1
           <<database->RM6CT_HSCB2STATE_B1<<database->RM6CT_BBIV1_B1<<database->RM6CT_BBIV2_B1<<database->RM6CT_PBIV_B1
           <<database->RM6CT_ExtendPower_B1<<database->RM6CT_ACUPowerCover_B1<<database->RM6CT_PANIV_B1<<database->RM6CT_VVVF1TEMPARLM_B1
           <<database->RM6CT_VVVF2TEMPARLM_B1<<database->RM6CT_WOSEBR_B1<<database->RM6CT_BMSCB_B1<<SPACE;

        MPDI2Data<<database->CTR3_MP1EXRBATTERY_B1<<database->CTR3_MP1LOYR_B1<<SPACE<<SPACE
                   <<SPACE<<SPACE<<SPACE<<SPACE
                     <<SPACE<<SPACE<<SPACE<<SPACE
                       <<SPACE<<SPACE<<SPACE<<SPACE
                          <<database->CTR6_MP1EXRBATTERY_B1<<database->CTR6_MP1LOYR_B1<<SPACE<<SPACE
                                             <<SPACE<<SPACE<<SPACE<<SPACE
                                               <<SPACE<<SPACE<<SPACE<<SPACE
                                                 <<SPACE<<SPACE<<SPACE<<SPACE;

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
    case TC_DI5:
        this->tcdi1->updateDi(TCDI5Data);
        break;
    case TC_DI6:
        this->tcdi1->updateDi(TCDI6Data);
        break;
    case TC_DO:
        this->tcdo1->updateDo(TCDO1Data);
        this->tcdo2->updateDo(TCDO2Data);
        break;
    case TC_AIM:
        this->ax1->updateAx(TCAXData1);
        break;
    case MP_DI:
        this->di1->updateDi(MPDI1Data);
        break;
    case MP_DO:
        this->tcdo1->updateDo(MPDI2Data);
        this->tcdo2->updateDo(TCDO2Data);
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
         Di1name<<"轮缘润滑继电器"<<"踏面清扫继电器"<<"CTS开关"<<"睡眠继电器"<<"司机室占有"<<"列车联挂继电器"
                 <<"紧急制动控制断路器"<<"警惕按钮旁路开关状态"<<"警惕按钮延时继电器"<<"总风欠压旁路开关状态"<<"紧急制动接触器"<<"VCU触发的紧急制动继电器"
                 <<"紧急制动按钮继电器"<<"紧急制动旁路开关"<<"紧急制动继电器"<<"零速继电器1~5"<<"停放制动施加接触器"<<"所有停放制动缓解断路器"
                 <<"所有停放制动缓解继电器"<<"所有气制动旁路开关"<<"所有制动都缓解"<<"紧急制动列车线"<<"远程缓解列车线"<<"司控器断路器";
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
         Di2Name<<"参考值旁路开关"<<"高速断路器闭合"<<"高速断路器断开"<<"钥匙信号列车线"<<"牵引指令列车线"<<"制动指令列车线"<<"快速制动指令列车线"<<"向前列车线"
                 <<"向后列车线"<<"牵引及辅助逆变器复位信号"<<"紧急牵引列车线"<<"停放制动缓解旁路开关"<<"受电弓使能旁路开关状态"<<"左侧车门门关好状态"<<"右侧车门门关好状态"<<"左侧车门紧急解锁请求联锁状态"
                 <<"右侧车门紧急解锁请求联锁状态"<<"ATC开左侧门"<<"ATC开右侧门"<<"ATC关左侧门"<<"ATC关右侧门"<<"ATO模式继电器"<<"自动折返继电器状态"<<"CTS开关";

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
         Di3Name<<"所有车门关好旁路开关状态"<<"ATP切除"<<"车门紧急解锁请求联锁回路隔离状态"<<"ATP激活"<<"ATC右侧门使能指令"<<"ATC左侧门使能指令"<<"ATC零速指令"<<"ATO保持制动指令"
                 <<"PDCS常开触点"<<"灯测试按钮"<<"远程缓解按钮"<<"蘑菇按钮状态"<<"车门释放隔离状态"<<"惰行位"<<"警惕按钮状态"<<"洗车模式"
                 <<"ATO全常用制动指令"<<"ATO牵引指令继电器AMTDR常开触点"<<"ATO制动指令继电器AMBDR常开触点"<<"ATP切除接触器1常开触点"<<"ATP切除接触器2常闭触点"<<"ATP输出断路器常闭触点"<<"左侧门使能选择开关"<<"右侧门使能选择开关";
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
         Di4Name<<"车门零速旁路开关"<<"车门零速断路器1"<<"车门零速断路器2"<<"开门回路断路器"<<"关门回路断路器"<<"左侧门使能断路器"<<"右侧门使能断路器"<<"紧急使能断路器"
                 <<"制动状态回路断路器"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"
                 <<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留";
         this->tcdi1->initialName(Di4Name,"DI4","MC");
         this->tcdi1->show();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();

     }
     else if(btnName=="TC_DI5")
     {
         refreshAllButtons();
         ui->TC_DI5->setStyleSheet(BUTTONPRESS);
         currentform=TC_DI5;
         QList<QString> Di5Name;
         Di5Name<<"制动缓解继电器1"<<"制动缓解继电器2"<<"右侧门释放列车线"<<"右侧开门列车线"<<"右侧关门列车线"<<"近端零速列车线右侧"<<"远端零速列车线右侧"<<"左侧门释放列车线"
                 <<"左侧开门列车线"<<"左侧关门列车线"<<"近端零速列车线左侧"<<"远端零速列车线左侧"<<"客室照明驱动器故障"<<"保留"<<"牵引指令列车线"<<"制动指令列车线"
                 <<"向前列车线"<<"向后列车线"<<"走行部检测系统断路器"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留";
         this->tcdi1->initialName(Di5Name,"DI5","MC");
         this->tcdi1->show();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();
     }

     else if(btnName=="TC_DI6")
     {
         refreshAllButtons();
         ui->TC_DI6->setStyleSheet(BUTTONPRESS);
         currentform=TC_DI6;
         QList<QString> Di6Name;
         Di6Name<<"列车供电接触器"<<"空压机电机启动断路器"<<"蓄电池断路器"<<"列车准备电压主熔断器"<<"低压检测继电器状态"<<"蓄电池接地断路器状态"<<"中压接地断路器状态"<<"蓄电池隔离开关"
                 <<"主风缸欠压压力开关"<<"SIV正常状态"<<"干燥塔1压力状态"<<"干燥塔2压力状态"<<"转向架1隔离状态"<<"转向架2隔离状态"<<"停放制动隔离阀状态"<<"蓄电池主熔断器1&2并联"
                 <<"空压机启动接触器"<<"制动隔离阀B04状态"<<"外界风源状态"<<"VVVF3感温电缆的状态"<<"SIV感温电缆的状态"<<"保留"<<"保留"<<"保留";
         this->tcdi1->initialName(Di6Name,"DI6","MC");
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
         MPDi1Name<<"制动缓解继电器1"<<"制动缓解继电器2"<<"客室照明驱动器故障"<<"受电弓降弓到位信号"<<"受电弓升弓信号"<<"升弓继电器状态"<<"受电弓回路断路器"<<"Mp高压箱断路器1"
                 <<"Mp高压箱断路器2 "<<"受电弓使能继电器"<<"熔断器箱熔断器状态"<<"高速断路器1状态"<<"高速断路器2状态"<<"转向架1隔离状态"<<"转向架2隔离状态"<<"停放制动隔离阀状态"
                 <<"扩展供电状态"<<"辅助高压箱车间电源端盖的状态"<<"受电弓二位三通阀"<<"VVVF1感温电缆的状态"<<"VVVF2感温电缆的状态"<<"车间电源使能继电器"<<"走行部检测系统断路器"<<"保留";
         this->di1->initialName(MPDi1Name,"DI1","MP");
         this->tcdi1->hide();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->show();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();

     }
     else if(btnName=="MP_DI2")
     {
         refreshAllButtons();
         ui->MP_DI2->setStyleSheet(BUTTONPRESS);
         currentform=MP_DO;
         QList<QString> MPDi2Name;
         MPDi2Name<<"扩展供电状态输出"<<"防油乳化启动控制"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"
                 <<"保留 "<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留";
         this->tcdo1->initialName(MPDi2Name,"DO","MP");
         this->tcdi1->hide();
         this->tcdo1->show();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();

     }

     else if(btnName=="TC_DO")
     {
         refreshAllButtons();
         ui->TC_DO->setStyleSheet(BUTTONPRESS);
         currentform=TC_DO;
         QList<QString> TCDo1Name;
         TCDo1Name<<"触发轮缘润滑"<<"踏面清扫输出"<<"无高压或中压或所有充电机故障"<<"无高压、无中压且无司机室占有"<<"蓄电池欠压"<<"空压机启动允许"<<"任意旁路开关激活"<<"受电弓状态指示"
                 <<"受电弓状态指示"<<"高速断路器闭合"<<"高速断路器断开"<<"VCU触发的紧急制动"<<"VCU触发的紧急照明"<<"保留"<<"保留"<<"保留";
         this->tcdo1->initialName(TCDo1Name,"DO1","MC");
         this->tcdi1->hide();
         this->tcdo1->show();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->hide();
         this->ax1->hide();
         this->ax2->hide();

     }

     else if(btnName=="TC_AIM")
     {
         refreshAllButtons();
         ui->TC_AIM->setStyleSheet(BUTTONPRESS);
         currentform=TC_AIM;
         QList<QString> AIMName1;
         AIMName1<<"司控器输出的牵引/制动参考值"<<"ATC输出的牵引/制动电流环模拟量参考值"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留"<<"保留";
         this->ax1->initialName(AIMName1);
         this->tcdi1->hide();
         this->tcdo1->hide();
         this->tcdo2->hide();
         this->di1->hide();
         this->do1->hide();
         this->ax1->show();
         this->ax2->hide();

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
