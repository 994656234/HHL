#include "database.h"

#include "qdatetime.h"
#include "qdebug.h"
#include "crrcfault.h"

#define TRUSTINVALID_CLEANDATA    1

Database::Database()
{

    DiCT_HMISWVerH_U8=1;
    DiCT_HMISWVerL_U8=1;

    HMIPosition = MainGetDefaultPara::getInt("/Position/HMI");
    //init HMI-CCU
    DiCT_Year_U8=0;
    DiCT_Month_U8=0;
    DiCT_Day_U8=0;
    DiCT_Hour_U8=0;
    DiCT_Minute_U8=0;
    DiCT_Second_U8=0;
    DiCT_TrainNum_U8=0;
    DiCT_LineNum_U8=0;
    DiCT_WheelDia1_U8=0;
    DiCT_WheelDia2_U8=0;
    DiCT_WheelDia5_U8=0;
    DiCT_WheelDia6_U8=0;
    DiCT_EmgyMsgCode_U8=0;


    DiCT_SAVETime_B1=false;
    DiCT_SAVETrainNum_B1=false;
    DiCT_SAVELineNum_B1=false;
    DiCT_SAVEWheelDig1_B1=false;
    DiCT_SAVEWheelDig2_B1=false;
    DiCT_SAVEWheelDig3_B1=false;
    DiCT_SAVEWheelDig4_B1=false;

    DiCT_5barBPSelect_B1 =false;
    DiCT_6barBPSelect_B1 =false;
    DiCT_TowingMode_B1 =false;
    DiCT_BrkRfanForceStart_B1 =false;
    DiCT_BCUStartSelfTest_B1 =false;


    DiCT_SetFlagChecker_U8=0;

    DiCT_HVACEmgcyVenti_B1=false;
    DiCT_HVACVenti_B1=false;
    DiCT_HVACAutoCoolMode_B1=false;
    DiCT_HVACAutoWarmMode_B1=false;
    DiCT_HVACStop_B1=false;
    DiCT_NADA_B1 = false;
    DiCT_Reduce0point5_B1=false;
    DiCT_Reduce1_B1=false;
    DiCT_Reduce1point5_B1=false;
    DiCT_Reduce2_B1=false;
    DiCT_Reduce2point5_B1=false;
    DiCT_Add0point5_B1=false;
    DiCT_Add1_B1=false;
    DiCT_Add1point5_B1=false;
    DiCT_Add2_B1=false;
    DiCT_Add2point5_B1=false;
    DiCT_Add0_B1=false;
    DiCT_Mp11TCUFaultReset_B1=false;
    DiCT_MC1TCUFaultReset_B1=false;
    DiCT_MC2TCUFaultReset_B1=false;
    DiCT_Mp21TCUFaultReset_B1=false;
    DiCT_Mp12TCUFaultReset_B1=false;
    DiCT_Mp22TCUFaultReset_B1=false;
    DiCT_Mp1DynamicBrkCut_B1=false;
    DiCT_MC1DynamicBrkCut_B1=false;
    DiCT_MC2DynamicBrkCut_B1=false;
    DiCT_Mp2DynamicBrkCut_B1=false;
    DiCT_ACU1Reset_B1=false;
    DiCT_ACU2Reset_B1=false;
    DiCT_ACU1Cutoff_B1=false;
    DiCT_ACU2Cutoff_B1=false;
    DiCT_FASReset_B1=false;
    DiCT_FASSlience_B1=false;
    DiCT_TCURunStatClear_B1=false;
    DiCT_ACMRunStatClear_B1=false;
    DiCT_PISTestStart_B1=false;
    DiCT_PISTestStop_B1=false;
    DiCT_TC1APClear_B1=false;
    DiCT_TC2APClear_B1=false;
    DiCT_ACDETestStopFlag_B1=false;
    DiCT_ACDETestStartFlag_B1=false;
    DiCT_BCUSelfTestReq_B1=false;
    DiCT_BCUSelfTestStop_B1=false;
    DiCT_RunStatSetFlag_B1=false;
    DiCT_EmgyMsgStart_B1=false;
    DiCT_EmgyMsgStop_B1=false;

    DiCT_RunStatSetType_U8=0;
    DiCT_ACVPALL_U8=0;
    DiCT_RunStatSetData_U32=0;

    HMiCT_LifeSignal_U16=0;

    HVACWarmStop=false;
    HVACCoolStop=false;
    fangyou=false;
    tamianClean=false;
    DiCT_LINENUM_U8=0;
    DiCT_STARTLINENUM_U8=0;
    DiCT_ENDLINENUM_U8=0;
    DiCT_NEXTLINENUM_U8=0;
    DiCT_NOWLINENUM_U8=0;
    DiCT_FAULT_B1=false;
    DiCT_HALFATOSTART_B1=false;
    DiCT_HALFATOEND_B1=false;
    DiCT_JUMPSET_B1=false;
    DiCT_JUMPCANCEL_B1=false;
    DiCT_SPEED_U16=0;

    DiCT_JUMP1_B1=false;
    DiCT_JUMP2_B1=false;
    DiCT_JUMP3_B1=false;
    DiCT_JUMP4_B1=false;
    DiCT_JUMP5_B1=false;
    DiCT_JUMP6_B1=false;
    DiCT_JUMP7_B1=false;
    DiCT_JUMP8_B1=false;
    DiCT_JUMP9_B1=false;
    DiCT_JUMP10_B1=false;
    DiCT_JUMP11_B1=false;
    DiCT_JUMP12_B1=false;
    DiCT_JUMP13_B1=false;
    DiCT_JUMP14_B1=false;
    DiCT_JUMP15_B1=false;
    DiCT_JUMP16_B1=false;
}

void Database::updateDatabse(CrrcRicoMvb* crrcRicoMvb)
{

    this->crrcRicoMvb = crrcRicoMvb;
    //0xfff null port
    for (int i = 0; i < 32; i ++)
    {
        this->crrcRicoMvb->setUnsignedChar(0xfff, i, 0);
    }
    /**************************************CCU-All************************************/
    CTALL_LfSign_U16=crrcRicoMvb->getUnsignedInt(0xF,0);
    CTALL_SysTimeMonth_U8=crrcRicoMvb->getUnsignedChar(0xF,2);
    CTALL_SysTimeYear_U8=crrcRicoMvb->getUnsignedChar(0xF,3);
    CTALL_SysTimeHour_U8=crrcRicoMvb->getUnsignedChar(0xF,4);
    CTALL_SysTimeDay_U8=crrcRicoMvb->getUnsignedChar(0xF,5);
    CTALL_SysTimeSecond_U8=crrcRicoMvb->getUnsignedChar(0xF,6);
    CTALL_SysTimeMinute_U8=crrcRicoMvb->getUnsignedChar(0xF,7);
    CTALL_TrainSerialNumber_U16=crrcRicoMvb->getUnsignedInt(0xF,9);

    /**************************************HMI-CCU***********************************/
    {
        HMiCT_LifeSignal_U16++;
        if(HMIPosition==1)
        {
            crrcRicoMvb->setUnsignedChar(0x310,2,DiCT_HMISWVerH_U8);
            crrcRicoMvb->setUnsignedChar(0x310,3,DiCT_HMISWVerL_U8);
            D1CT_HMISWVerH_U8=DiCT_HMISWVerH_U8;
            D1CT_HMISWVerL_U8=DiCT_HMISWVerL_U8;

            D2CT_HMISWVerH_U8=crrcRicoMvb->getUnsignedChar(0x320,2);
            D2CT_HMISWVerL_U8=crrcRicoMvb->getUnsignedChar(0x320,3);


            crrcRicoMvb->setUnsignedInt(0x310,0,HMiCT_LifeSignal_U16);

            crrcRicoMvb->setUnsignedChar(0x310,4,DiCT_Year_U8);
            crrcRicoMvb->setUnsignedChar(0x310,5,DiCT_Month_U8);
            crrcRicoMvb->setUnsignedChar(0x310,6,DiCT_Day_U8);
            crrcRicoMvb->setUnsignedChar(0x310,7,DiCT_Hour_U8);
            crrcRicoMvb->setUnsignedChar(0x310,8,DiCT_Minute_U8);
            crrcRicoMvb->setUnsignedChar(0x310,9,DiCT_Second_U8);
            crrcRicoMvb->setUnsignedChar(0x310,10,DiCT_TrainNum_U8);
            crrcRicoMvb->setUnsignedChar(0x310,11,DiCT_LineNum_U8);
            crrcRicoMvb->setUnsignedChar(0x310,12,DiCT_WheelDia1_U8);
            crrcRicoMvb->setUnsignedChar(0x310,13,DiCT_WheelDia2_U8);
            crrcRicoMvb->setUnsignedChar(0x310,16,DiCT_WheelDia5_U8);
            crrcRicoMvb->setUnsignedChar(0x310,17,DiCT_WheelDia6_U8);


            crrcRicoMvb->setBool(0x310,20,0,DiCT_SAVETime_B1);
            crrcRicoMvb->setBool(0x310,20,1,DiCT_SAVETrainNum_B1);
            crrcRicoMvb->setBool(0x310,20,2,DiCT_SAVELineNum_B1);
            crrcRicoMvb->setBool(0x310,20,3,DiCT_SAVEWheelDig1_B1);
            crrcRicoMvb->setBool(0x310,20,4,DiCT_SAVEWheelDig2_B1);
            crrcRicoMvb->setBool(0x310,20,5,DiCT_SAVEWheelDig3_B1);
            crrcRicoMvb->setBool(0x310,20,6,DiCT_SAVEWheelDig4_B1);

            crrcRicoMvb->setBool(0x310,21,1,DiCT_5barBPSelect_B1);
            crrcRicoMvb->setBool(0x310,21,2,DiCT_6barBPSelect_B1);
            crrcRicoMvb->setBool(0x310,21,3,DiCT_TowingMode_B1);
            crrcRicoMvb->setBool(0x310,21,4,DiCT_BrkRfanForceStart_B1);
            crrcRicoMvb->setBool(0x310,21,5,DiCT_BCUStartSelfTest_B1);

            crrcRicoMvb->setUnsignedChar(0x310,31,DiCT_SetFlagChecker_U8);

            crrcRicoMvb->setBool(0x311,0,0,DiCT_HVACEmgcyVenti_B1);
            crrcRicoMvb->setBool(0x311,0,1,DiCT_HVACVenti_B1);
            crrcRicoMvb->setBool(0x311,0,2,DiCT_HVACAutoCoolMode_B1);
            crrcRicoMvb->setBool(0x311,0,3,DiCT_HVACAutoWarmMode_B1);
            crrcRicoMvb->setBool(0x311,0,4,DiCT_HVACStop_B1);
            crrcRicoMvb->setBool(0x311,0,5,DiCT_NADA_B1);

            crrcRicoMvb->setBool(0x311,1,0,DiCT_Reduce0point5_B1);
            crrcRicoMvb->setBool(0x311,1,1,DiCT_Reduce1_B1);
            crrcRicoMvb->setBool(0x311,1,2,DiCT_Reduce1point5_B1);
            crrcRicoMvb->setBool(0x311,1,3,DiCT_Reduce2_B1);
            crrcRicoMvb->setBool(0x311,1,4,DiCT_Reduce2point5_B1);
            crrcRicoMvb->setBool(0x311,1,5,DiCT_Add0point5_B1);
            crrcRicoMvb->setBool(0x311,1,6,DiCT_Add1_B1);
            crrcRicoMvb->setBool(0x311,1,7,DiCT_Add1point5_B1);
            crrcRicoMvb->setBool(0x311,2,0,DiCT_Add2_B1);
            crrcRicoMvb->setBool(0x311,2,1,DiCT_Add2point5_B1);
            crrcRicoMvb->setBool(0x311,2,2,DiCT_Add0_B1);

            crrcRicoMvb->setBool(0x311,2,6,DiCT_Mp11TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x311,2,7,DiCT_MC1TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x311,4,0,DiCT_MC2TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x311,4,1,DiCT_Mp21TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x311,4,2,DiCT_Mp12TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x311,4,3,DiCT_Mp22TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x311,4,4,DiCT_Mp1DynamicBrkCut_B1);
            crrcRicoMvb->setBool(0x311,4,5,DiCT_MC1DynamicBrkCut_B1);
            crrcRicoMvb->setBool(0x311,4,6,DiCT_MC2DynamicBrkCut_B1);
            crrcRicoMvb->setBool(0x311,4,7,DiCT_Mp2DynamicBrkCut_B1);
            crrcRicoMvb->setBool(0x311,5,0,DiCT_ACU1Reset_B1);
            crrcRicoMvb->setBool(0x311,5,1,DiCT_ACU2Reset_B1);
            crrcRicoMvb->setBool(0x311,5,4,DiCT_ACU1Cutoff_B1);
            crrcRicoMvb->setBool(0x311,5,5,DiCT_ACU2Cutoff_B1);
            crrcRicoMvb->setBool(0x311,6,0,DiCT_FASReset_B1);
            crrcRicoMvb->setBool(0x311,6,1,DiCT_FASSlience_B1);
            crrcRicoMvb->setBool(0x311,6,2,DiCT_TCURunStatClear_B1);
            crrcRicoMvb->setBool(0x311,6,3,DiCT_ACMRunStatClear_B1);
            crrcRicoMvb->setBool(0x311,6,4,DiCT_PISTestStart_B1);
            crrcRicoMvb->setBool(0x311,6,5,DiCT_PISTestStop_B1);
            crrcRicoMvb->setBool(0x311,6,6,DiCT_TC1APClear_B1);
            crrcRicoMvb->setBool(0x311,6,7,DiCT_TC2APClear_B1);


            crrcRicoMvb->setBool(0x311,7,3,DiCT_ACDETestStopFlag_B1);
            crrcRicoMvb->setBool(0x311,7,4,DiCT_ACDETestStartFlag_B1);
            crrcRicoMvb->setBool(0x311,7,7,DiCT_BCUSelfTestReq_B1);
            crrcRicoMvb->setBool(0x311,8,0,DiCT_BCUSelfTestStop_B1);
            crrcRicoMvb->setUnsignedChar(0x311,9,DiCT_ACVPALL_U8);
            crrcRicoMvb->setUnsignedChar(0x311,10,DiCT_EmgyMsgCode_U8);
            crrcRicoMvb->setBool(0x311,11,0,DiCT_EmgyMsgStart_B1);
            crrcRicoMvb->setBool(0x311,11,1,DiCT_EmgyMsgStop_B1);
            crrcRicoMvb->setBool(0x311,26,0,DiCT_RunStatSetFlag_B1);


            crrcRicoMvb->setUnsignedChar(0x311,27,DiCT_RunStatSetType_U8);
            crrcRicoMvb->setUnsignedInt32(0x311,28,DiCT_RunStatSetData_U32);

            crrcRicoMvb->setBool(0x311,2,3,HVACWarmStop);
            crrcRicoMvb->setBool(0x311,2,4,HVACCoolStop);

            crrcRicoMvb->setBool(0x311,7,0,tamianClean);
            crrcRicoMvb->setBool(0x311,7,1,fangyou);


            crrcRicoMvb->setUnsignedChar(0x311,12,DiCT_LINENUM_U8);
            crrcRicoMvb->setUnsignedChar(0x311,13,DiCT_STARTLINENUM_U8);
            crrcRicoMvb->setUnsignedChar(0x311,14,DiCT_ENDLINENUM_U8);
            crrcRicoMvb->setUnsignedChar(0x311,15,DiCT_NEXTLINENUM_U8);
            crrcRicoMvb->setUnsignedChar(0x311,16,DiCT_NOWLINENUM_U8);

            crrcRicoMvb->setBool(0x311,17,0,DiCT_FAULT_B1);
            crrcRicoMvb->setBool(0x311,17,1,DiCT_HALFATOSTART_B1);
            crrcRicoMvb->setBool(0x311,17,2,DiCT_HALFATOEND_B1);
            crrcRicoMvb->setBool(0x311,17,4,DiCT_JUMPSET_B1);
            crrcRicoMvb->setBool(0x311,17,5,DiCT_JUMPCANCEL_B1);

            crrcRicoMvb->setUnsignedInt(0x311,18,DiCT_SPEED_U16);

            crrcRicoMvb->setBool(0x311,20,0,DiCT_JUMP1_B1);
            crrcRicoMvb->setBool(0x311,20,1,DiCT_JUMP2_B1);
            crrcRicoMvb->setBool(0x311,20,2,DiCT_JUMP3_B1);
            crrcRicoMvb->setBool(0x311,20,3,DiCT_JUMP4_B1);
            crrcRicoMvb->setBool(0x311,20,4,DiCT_JUMP5_B1);
            crrcRicoMvb->setBool(0x311,20,5,DiCT_JUMP6_B1);
            crrcRicoMvb->setBool(0x311,20,6,DiCT_JUMP7_B1);
            crrcRicoMvb->setBool(0x311,20,7,DiCT_JUMP8_B1);

            crrcRicoMvb->setBool(0x311,21,0,DiCT_JUMP9_B1);
            crrcRicoMvb->setBool(0x311,21,1,DiCT_JUMP10_B1);
            crrcRicoMvb->setBool(0x311,21,2,DiCT_JUMP11_B1);
            crrcRicoMvb->setBool(0x311,21,3,DiCT_JUMP12_B1);
            crrcRicoMvb->setBool(0x311,21,4,DiCT_JUMP13_B1);
            crrcRicoMvb->setBool(0x311,21,5,DiCT_JUMP14_B1);
            crrcRicoMvb->setBool(0x311,21,6,DiCT_JUMP15_B1);
            crrcRicoMvb->setBool(0x311,21,7,DiCT_JUMP16_B1);



        }
        else if(HMIPosition==2)
        {
            crrcRicoMvb->setUnsignedChar(0x320,2,DiCT_HMISWVerH_U8);
            crrcRicoMvb->setUnsignedChar(0x320,3,DiCT_HMISWVerL_U8);
            D2CT_HMISWVerH_U8=DiCT_HMISWVerH_U8;
            D2CT_HMISWVerL_U8=DiCT_HMISWVerL_U8;

            D1CT_HMISWVerH_U8=crrcRicoMvb->getUnsignedChar(0x310,2);
            D1CT_HMISWVerL_U8=crrcRicoMvb->getUnsignedChar(0x310,3);

            crrcRicoMvb->setUnsignedInt(0x320,0,HMiCT_LifeSignal_U16);
            crrcRicoMvb->setUnsignedChar(0x320,4,DiCT_Year_U8);
            crrcRicoMvb->setUnsignedChar(0x320,5,DiCT_Month_U8);
            crrcRicoMvb->setUnsignedChar(0x320,6,DiCT_Day_U8);
            crrcRicoMvb->setUnsignedChar(0x320,7,DiCT_Hour_U8);
            crrcRicoMvb->setUnsignedChar(0x320,8,DiCT_Minute_U8);
            crrcRicoMvb->setUnsignedChar(0x320,9,DiCT_Second_U8);
            crrcRicoMvb->setUnsignedChar(0x320,10,DiCT_TrainNum_U8);
            crrcRicoMvb->setUnsignedChar(0x320,11,DiCT_LineNum_U8);
            crrcRicoMvb->setUnsignedChar(0x320,12,DiCT_WheelDia1_U8);
            crrcRicoMvb->setUnsignedChar(0x320,13,DiCT_WheelDia2_U8);
            crrcRicoMvb->setUnsignedChar(0x320,16,DiCT_WheelDia5_U8);
            crrcRicoMvb->setUnsignedChar(0x320,17,DiCT_WheelDia6_U8);


            crrcRicoMvb->setBool(0x320,20,0,DiCT_SAVETime_B1);
            crrcRicoMvb->setBool(0x320,20,1,DiCT_SAVETrainNum_B1);
            crrcRicoMvb->setBool(0x320,20,2,DiCT_SAVELineNum_B1);
            crrcRicoMvb->setBool(0x320,20,3,DiCT_SAVEWheelDig1_B1);
            crrcRicoMvb->setBool(0x320,20,4,DiCT_SAVEWheelDig2_B1);
            crrcRicoMvb->setBool(0x320,20,5,DiCT_SAVEWheelDig3_B1);
            crrcRicoMvb->setBool(0x320,20,6,DiCT_SAVEWheelDig4_B1);


            crrcRicoMvb->setUnsignedChar(0x320,31,DiCT_SetFlagChecker_U8);

            crrcRicoMvb->setBool(0x321,0,0,DiCT_HVACEmgcyVenti_B1);
            crrcRicoMvb->setBool(0x321,0,1,DiCT_HVACVenti_B1);
            crrcRicoMvb->setBool(0x321,0,2,DiCT_HVACAutoCoolMode_B1);
            crrcRicoMvb->setBool(0x321,0,3,DiCT_HVACAutoWarmMode_B1);
            crrcRicoMvb->setBool(0x321,0,4,DiCT_HVACStop_B1);
            crrcRicoMvb->setBool(0x321,0,5,DiCT_NADA_B1);

            crrcRicoMvb->setBool(0x321,1,0,DiCT_Reduce0point5_B1);
            crrcRicoMvb->setBool(0x321,1,1,DiCT_Reduce1_B1);
            crrcRicoMvb->setBool(0x321,1,2,DiCT_Reduce1point5_B1);
            crrcRicoMvb->setBool(0x321,1,3,DiCT_Reduce2_B1);
            crrcRicoMvb->setBool(0x321,1,4,DiCT_Reduce2point5_B1);
            crrcRicoMvb->setBool(0x321,1,5,DiCT_Add0point5_B1);
            crrcRicoMvb->setBool(0x321,1,6,DiCT_Add1_B1);
            crrcRicoMvb->setBool(0x321,1,7,DiCT_Add1point5_B1);
            crrcRicoMvb->setBool(0x321,2,0,DiCT_Add2_B1);
            crrcRicoMvb->setBool(0x321,2,1,DiCT_Add2point5_B1);
            crrcRicoMvb->setBool(0x321,2,2,DiCT_Add0_B1);

            crrcRicoMvb->setBool(0x321,2,6,DiCT_Mp11TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x321,2,7,DiCT_MC1TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x321,4,0,DiCT_MC2TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x321,4,1,DiCT_Mp21TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x321,4,2,DiCT_Mp12TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x321,4,3,DiCT_Mp22TCUFaultReset_B1);
            crrcRicoMvb->setBool(0x321,4,4,DiCT_Mp1DynamicBrkCut_B1);
            crrcRicoMvb->setBool(0x321,4,5,DiCT_MC1DynamicBrkCut_B1);
            crrcRicoMvb->setBool(0x321,4,6,DiCT_MC2DynamicBrkCut_B1);
            crrcRicoMvb->setBool(0x321,4,7,DiCT_Mp2DynamicBrkCut_B1);
            crrcRicoMvb->setBool(0x321,5,0,DiCT_ACU1Reset_B1);
            crrcRicoMvb->setBool(0x321,5,1,DiCT_ACU2Reset_B1);
            crrcRicoMvb->setBool(0x321,5,4,DiCT_ACU1Cutoff_B1);
            crrcRicoMvb->setBool(0x321,5,5,DiCT_ACU2Cutoff_B1);
            crrcRicoMvb->setBool(0x321,6,0,DiCT_FASReset_B1);
            crrcRicoMvb->setBool(0x321,6,1,DiCT_FASSlience_B1);
            crrcRicoMvb->setBool(0x321,6,2,DiCT_TCURunStatClear_B1);
            crrcRicoMvb->setBool(0x321,6,3,DiCT_ACMRunStatClear_B1);
            crrcRicoMvb->setBool(0x321,6,4,DiCT_PISTestStart_B1);
            crrcRicoMvb->setBool(0x321,6,5,DiCT_PISTestStop_B1);
            crrcRicoMvb->setBool(0x321,6,6,DiCT_TC1APClear_B1);
            crrcRicoMvb->setBool(0x321,6,7,DiCT_TC2APClear_B1);


            crrcRicoMvb->setBool(0x321,7,3,DiCT_ACDETestStopFlag_B1);
            crrcRicoMvb->setBool(0x321,7,4,DiCT_ACDETestStartFlag_B1);
            crrcRicoMvb->setBool(0x321,7,7,DiCT_BCUSelfTestReq_B1);
            crrcRicoMvb->setBool(0x321,8,0,DiCT_BCUSelfTestStop_B1);
            crrcRicoMvb->setUnsignedChar(0x321,9,DiCT_ACVPALL_U8);
            crrcRicoMvb->setUnsignedChar(0x321,10,DiCT_EmgyMsgCode_U8);
            crrcRicoMvb->setBool(0x321,11,0,DiCT_EmgyMsgStart_B1);
            crrcRicoMvb->setBool(0x321,11,1,DiCT_EmgyMsgStop_B1);
            crrcRicoMvb->setBool(0x321,26,0,DiCT_RunStatSetFlag_B1);


            crrcRicoMvb->setUnsignedChar(0x321,27,DiCT_RunStatSetType_U8);
            crrcRicoMvb->setUnsignedInt32(0x321,28,DiCT_RunStatSetData_U32);

            crrcRicoMvb->setBool(0x321,2,3,HVACWarmStop);
            crrcRicoMvb->setBool(0x321,2,4,HVACCoolStop);


            crrcRicoMvb->setBool(0x321,7,0,tamianClean);
            crrcRicoMvb->setBool(0x321,7,1,fangyou);

            crrcRicoMvb->setUnsignedChar(0x321,12,DiCT_LINENUM_U8);
            crrcRicoMvb->setUnsignedChar(0x321,13,DiCT_STARTLINENUM_U8);
            crrcRicoMvb->setUnsignedChar(0x321,14,DiCT_ENDLINENUM_U8);
            crrcRicoMvb->setUnsignedChar(0x321,15,DiCT_NEXTLINENUM_U8);
            crrcRicoMvb->setUnsignedChar(0x321,16,DiCT_NOWLINENUM_U8);

            crrcRicoMvb->setBool(0x321,17,0,DiCT_FAULT_B1);
            crrcRicoMvb->setBool(0x321,17,1,DiCT_HALFATOSTART_B1);
            crrcRicoMvb->setBool(0x321,17,2,DiCT_HALFATOEND_B1);
            crrcRicoMvb->setBool(0x321,17,4,DiCT_JUMPSET_B1);
            crrcRicoMvb->setBool(0x321,17,5,DiCT_JUMPCANCEL_B1);

            crrcRicoMvb->setUnsignedInt(0x321,18,DiCT_SPEED_U16);

            crrcRicoMvb->setBool(0x321,20,0,DiCT_JUMP1_B1);
            crrcRicoMvb->setBool(0x321,20,1,DiCT_JUMP2_B1);
            crrcRicoMvb->setBool(0x321,20,2,DiCT_JUMP3_B1);
            crrcRicoMvb->setBool(0x321,20,3,DiCT_JUMP4_B1);
            crrcRicoMvb->setBool(0x321,20,4,DiCT_JUMP5_B1);
            crrcRicoMvb->setBool(0x321,20,5,DiCT_JUMP6_B1);
            crrcRicoMvb->setBool(0x321,20,6,DiCT_JUMP7_B1);
            crrcRicoMvb->setBool(0x321,20,7,DiCT_JUMP8_B1);

            crrcRicoMvb->setBool(0x321,21,0,DiCT_JUMP9_B1);
            crrcRicoMvb->setBool(0x321,21,1,DiCT_JUMP10_B1);
            crrcRicoMvb->setBool(0x321,21,2,DiCT_JUMP11_B1);
            crrcRicoMvb->setBool(0x321,21,3,DiCT_JUMP12_B1);
            crrcRicoMvb->setBool(0x321,21,4,DiCT_JUMP13_B1);
            crrcRicoMvb->setBool(0x321,21,5,DiCT_JUMP14_B1);
            crrcRicoMvb->setBool(0x321,21,6,DiCT_JUMP15_B1);
            crrcRicoMvb->setBool(0x321,21,7,DiCT_JUMP16_B1);
        }

    }


    CTD_TRCBLOCK_U8=crrcRicoMvb->getUnsignedChar(0x30A,14);
    CTD_QYFSXX_U8 = crrcRicoMvb->getUnsignedChar(0x30A,20);

    //PIS
    PIS1CT_P2_B1=crrcRicoMvb->getBool(0x910,2,0);
    PIS2CT_P2_B1=crrcRicoMvb->getBool(0x920,2,0);
    //BCU
    B1CT_SWVerHigh_U8=crrcRicoMvb->getUnsignedChar(0x410,0);
    B1CT_SWVerLow_U8=crrcRicoMvb->getUnsignedChar(0x410,1);
    B2CT_SWVerHigh_U8=crrcRicoMvb->getUnsignedChar(0x420,0);
    B2CT_SWVerLow_U8=crrcRicoMvb->getUnsignedChar(0x420,1);
    //FCU
    FCU1CT_usSWRev_B1=crrcRicoMvb->getUnsignedChar(0x810,3);
    FCU2CT_usSWRev_B1=crrcRicoMvb->getUnsignedChar(0x820,3);
    //PIS
    PIS1CT_P178_B1=crrcRicoMvb->getUnsignedChar(0x911,0);
    PIS1CT_P179_B1=crrcRicoMvb->getUnsignedChar(0x911,2);
    PIS1CT_P180_B1=crrcRicoMvb->getUnsignedChar(0x911,2);
    PIS2CT_P178_B1=crrcRicoMvb->getUnsignedChar(0x921,0);
    PIS2CT_P179_B1=crrcRicoMvb->getUnsignedChar(0x921,2);
    PIS2CT_P180_B1=crrcRicoMvb->getUnsignedChar(0x921,2);



    //*********************************RIOM-CCU**************************************//

    RM3CT_CBBIV_B1=crrcRicoMvb->getBool(0x131,20,0);
    RM6CT_CBBIV_B1=crrcRicoMvb->getBool(0x161,20,0);
    RM1CT_DI1NOANSWER_B1 = crrcRicoMvb->getBool(0x110,24,0);
    RM1CT_DI2NOANSWER_B1 = crrcRicoMvb->getBool(0x110,24,1);
    RM1CT_DI3NOANSWER_B1 = crrcRicoMvb->getBool(0x110,24,2);
    RM1CT_DI4NOANSWER_B1 = crrcRicoMvb->getBool(0x110,24,3);
    RM1CT_DO1NOANSWER_B1 = crrcRicoMvb->getBool(0x110,25,0);
    RM1CT_AX1NOANSWER_B1 = crrcRicoMvb->getBool(0x110,25,4);
    RM1CT_LAT_B1 = crrcRicoMvb->getBool(0x110,30,0);
    RM1CT_RLD_B1 = crrcRicoMvb->getBool(0x110,30,1);
    RM1CT_1i0CHECK1_B1 = crrcRicoMvb->getBool(0x110,31,7);
    RM1CT_1i0CHECK0_B1 = crrcRicoMvb->getBool(0x110,31,6);
    RM1CT_PBK_B1 = crrcRicoMvb->getBool(0x111,20,7);
    RM1CT_APBRCB_B1 = crrcRicoMvb->getBool(0x111,20,6);
    RM1CT_APBRR_B1 = crrcRicoMvb->getBool(0x111,20,5);
    RM1CT_ABRBS_B1 = crrcRicoMvb->getBool(0x111,20,4);
    RM1CT_ETABRR_B1 = crrcRicoMvb->getBool(0x111,20,3);
    RM1CT_ETEBL_B1 = crrcRicoMvb->getBool(0x111,20,2);
    RM1CT_ETRRL_B1 = crrcRicoMvb->getBool(0x111,20,1);
    RM1CT_MCCB_B1 = crrcRicoMvb->getBool(0x111,20,0);
    RM1CT_DMYR_B1 = crrcRicoMvb->getBool(0x111,21,7);
    RM1CT_LMRGBS_B1 = crrcRicoMvb->getBool(0x111,21,6);
    RM1CT_EBK_B1 = crrcRicoMvb->getBool(0x111,21,5);
    RM1CT_VCUEBR_B1 = crrcRicoMvb->getBool(0x111,21,4);
    RM1CT_EMPBR_B1 = crrcRicoMvb->getBool(0x111,21,3);
    RM1CT_EBBS_B1 = crrcRicoMvb->getBool(0x111,21,2);
    RM1CT_EBR_B1 = crrcRicoMvb->getBool(0x111,21,1);
    RM1CT_ZVR_B1 = crrcRicoMvb->getBool(0x111,21,0);
    RM1CT_WFLR_B1 = crrcRicoMvb->getBool(0x111,22,7);
    RM1CT_TCR_B1 = crrcRicoMvb->getBool(0x111,22,6);
    RM1CT_CTS_B1 = crrcRicoMvb->getBool(0x111,22,5);
    RM1CT_SLR_B1 = crrcRicoMvb->getBool(0x111,22,4);
    RM1CT_COR_B1 = crrcRicoMvb->getBool(0x111,22,3);
    RM1CT_CTR_B1 = crrcRicoMvb->getBool(0x111,22,2);
    RM1CT_EBCB_B1 = crrcRicoMvb->getBool(0x111,22,1);
    RM1CT_DMBPS_B1 = crrcRicoMvb->getBool(0x111,22,0);
    RM1CT_DRARR_B1 = crrcRicoMvb->getBool(0x111,23,7);
    RM1CT_DOCRL_B1 = crrcRicoMvb->getBool(0x111,23,6);
    RM1CT_DOCRR_B1 = crrcRicoMvb->getBool(0x111,23,5);
    RM1CT_DCCRL_B1 = crrcRicoMvb->getBool(0x111,23,4);
    RM1CT_DCCRR_B1 = crrcRicoMvb->getBool(0x111,23,3);
    RM1CT_AMR_B1 = crrcRicoMvb->getBool(0x111,23,2);
    RM1CT_ARR12_B1 = crrcRicoMvb->getBool(0x111,23,1);
    RM1CT_CTSHSD_B1 = crrcRicoMvb->getBool(0x111,23,0);
    RM1CT_ETRL_B1 = crrcRicoMvb->getBool(0x111,24,7);
    RM1CT_RESTART_B1 = crrcRicoMvb->getBool(0x111,24,6);
    RM1CT_ETETML_B1 = crrcRicoMvb->getBool(0x111,24,5);
    RM1CT_PBRBPS_B1 = crrcRicoMvb->getBool(0x111,24,4);
    RM1CT_PEBS_B1 = crrcRicoMvb->getBool(0x111,24,3);
    RM1CT_DIRL12_B1 = crrcRicoMvb->getBool(0x111,24,2);
    RM1CT_DIRR12_B1 = crrcRicoMvb->getBool(0x111,24,1);
    RM1CT_DRARL_B1 = crrcRicoMvb->getBool(0x111,24,0);
    RM1CT_RVBPS_B1 = crrcRicoMvb->getBool(0x111,25,7);
    RM1CT_HSCBON_B1 = crrcRicoMvb->getBool(0x111,25,6);
    RM1CT_HSCBOFF_B1 = crrcRicoMvb->getBool(0x111,25,5);
    RM1CT_Keyrtainline_B1 = crrcRicoMvb->getBool(0x111,25,4);
    RM1CT_TDL_B1 = crrcRicoMvb->getBool(0x111,25,3);
    RM1CT_BDL_B1 = crrcRicoMvb->getBool(0x111,25,2);
    RM1CT_FBDL_B1 = crrcRicoMvb->getBool(0x111,25,1);
    RM1CT_ETFL_B1 = crrcRicoMvb->getBool(0x111,25,0);
    RM1CT_ATPOUTBRAKE_B1 = crrcRicoMvb->getBool(0x111,26,7);
    RM1CT_AMTDR_B1 = crrcRicoMvb->getBool(0x111,26,6);
    RM1CT_AMBDR_B1 = crrcRicoMvb->getBool(0x111,26,5);
    RM1CT_ATPFK1_B1 = crrcRicoMvb->getBool(0x111,26,4);
    RM1CT_ATPFK2_B1 = crrcRicoMvb->getBool(0x111,26,3);
    RM1CT_ATPOTCB_B1 = crrcRicoMvb->getBool(0x111,26,2);
    RM1CT_DORSL_B1 = crrcRicoMvb->getBool(0x111,26,1);
    RM1CT_DORSR_B1 = crrcRicoMvb->getBool(0x111,26,0);
    RM1CT_PDCS_B1 = crrcRicoMvb->getBool(0x111,27,7);
    RM1CT_TLPB_B1 = crrcRicoMvb->getBool(0x111,27,6);
    RM1CT_RRPB_B1 = crrcRicoMvb->getBool(0x111,27,5);
    RM1CT_EMPB_B1 = crrcRicoMvb->getBool(0x111,27,4);
    RM1CT_DBYS_B1 = crrcRicoMvb->getBool(0x111,27,3);
    RM1CT_COAST_B1 = crrcRicoMvb->getBool(0x111,27,2);
    RM1CT_DMS_B1 = crrcRicoMvb->getBool(0x111,27,1);
    RM1CT_WM_B1 = crrcRicoMvb->getBool(0x111,27,0);
    RM1CT_DBPS_B1 = crrcRicoMvb->getBool(0x111,28,7);
    RM1CT_ATPFS_B1 = crrcRicoMvb->getBool(0x111,28,6);
    RM1CT_DRBYS_B1 = crrcRicoMvb->getBool(0x111,28,5);
    RM1CT_ATPACTIVE_B1 = crrcRicoMvb->getBool(0x111,28,4);
    RM1CT_RDER_B1 = crrcRicoMvb->getBool(0x111,28,3);
    RM1CT_LDER_B1 = crrcRicoMvb->getBool(0x111,28,2);
    RM1CT_VZCR_B1 = crrcRicoMvb->getBool(0x111,28,1);
    RM1CT_ATOHOLDINGBRAKE_B1 = crrcRicoMvb->getBool(0x111,28,0);
    RM1CT_1i1CHECK1_B1 = crrcRicoMvb->getBool(0x111,31,7);
    RM1CT_1i1CHECK0_B1 = crrcRicoMvb->getBool(0x111,31,6);
    RM1CT_BSCB_B1 = crrcRicoMvb->getBool(0x112,21,7);
    RM1CT_ZVBS_B1 = crrcRicoMvb->getBool(0x112,22,7);
    RM1CT_ZVRCB1_B1 = crrcRicoMvb->getBool(0x112,22,6);
    RM1CT_ZVRCB2_B1 = crrcRicoMvb->getBool(0x112,22,5);
    RM1CT_DOTCB_B1 = crrcRicoMvb->getBool(0x112,22,4);
    RM1CT_DCTCB_B1 = crrcRicoMvb->getBool(0x112,22,3);
    RM1CT_DRCBL_B1 = crrcRicoMvb->getBool(0x112,22,2);
    RM1CT_DRCBR_B1 = crrcRicoMvb->getBool(0x112,22,1);
    RM1CT_DENACB_B1 = crrcRicoMvb->getBool(0x112,22,0);
    RM1CT_1i2CHECK1_B1 = crrcRicoMvb->getBool(0x112,31,7);
    RM1CT_1i2CHECK0_B1 = crrcRicoMvb->getBool(0x112,31,6);
    RM2CT_DI1NOANSWER_B1 = crrcRicoMvb->getBool(0x120,24,0);
    RM2CT_DI2NOANSWER_B1 = crrcRicoMvb->getBool(0x120,24,1);
    RM2CT_DO1NOANSWER_B1 = crrcRicoMvb->getBool(0x120,25,0);
    RM2CT_LAT_B1 = crrcRicoMvb->getBool(0x120,30,0);
    RM2CT_RLD_B1 = crrcRicoMvb->getBool(0x120,30,1);
    RM2CT_1i0CHECK1_B1 = crrcRicoMvb->getBool(0x120,31,7);
    RM2CT_1i0CHECK0_B1 = crrcRicoMvb->getBool(0x120,31,6);
    RM2CT_ETFL_B1 = crrcRicoMvb->getBool(0x121,20,7);
    RM2CT_ETRL_B1 = crrcRicoMvb->getBool(0x121,20,6);
    RM2CT_BMSCB_B1 = crrcRicoMvb->getBool(0x121,20,5);
    RM2CT_LODTL_B1 = crrcRicoMvb->getBool(0x121,21,7);
    RM2CT_LCDTL_B1 = crrcRicoMvb->getBool(0x121,21,6);
    RM2CT_LZVTLL_B1 = crrcRicoMvb->getBool(0x121,21,5);
    RM2CT_RZVTLL_B1 = crrcRicoMvb->getBool(0x121,21,4);
    RM2CT_VRFAULT_B1 = crrcRicoMvb->getBool(0x121,21,3);
    RM2CT_TDL_B1 = crrcRicoMvb->getBool(0x121,21,1);
    RM2CT_BDL_B1 = crrcRicoMvb->getBool(0x121,21,0);
    RM2CT_BRR1_B1 = crrcRicoMvb->getBool(0x121,22,7);
    RM2CT_BRR2_B1 = crrcRicoMvb->getBool(0x121,22,6);
    RM2CT_RDRTL_B1 = crrcRicoMvb->getBool(0x121,22,5);
    RM2CT_RODTL_B1 = crrcRicoMvb->getBool(0x121,22,4);
    RM2CT_RCDTL_B1 = crrcRicoMvb->getBool(0x121,22,3);
    RM2CT_LZVTLR_B1 = crrcRicoMvb->getBool(0x121,22,2);
    RM2CT_RZVTLR_B1 = crrcRicoMvb->getBool(0x121,22,1);
    RM2CT_LDRTL_B1 = crrcRicoMvb->getBool(0x121,22,0);
    RM2CT_CMK_B1 = crrcRicoMvb->getBool(0x121,23,7);
    RM2CT_CBBIV_B1 = crrcRicoMvb->getBool(0x121,23,6);
    RM2CT_EWSV_B1 = crrcRicoMvb->getBool(0x121,23,5);
    RM2CT_VVVF3arlm_B1 = crrcRicoMvb->getBool(0x121,23,4);
    RM2CT_SIVTEMPARLM_B1 = crrcRicoMvb->getBool(0x121,23,3);
    RM2CT_MRPS_B1 = crrcRicoMvb->getBool(0x121,24,7);
    RM2CT_SIV_B1 = crrcRicoMvb->getBool(0x121,24,6);
    RM2CT_ADUPS1_B1 = crrcRicoMvb->getBool(0x121,24,5);
    RM2CT_ADUPS2_B1 = crrcRicoMvb->getBool(0x121,24,4);
    RM2CT_BBIV1_B1 = crrcRicoMvb->getBool(0x121,24,3);
    RM2CT_BBIV2_B1 = crrcRicoMvb->getBool(0x121,24,2);
    RM2CT_PBIV_B1 = crrcRicoMvb->getBool(0x121,24,1);
    RM2CT_Batteryfuse_B1 = crrcRicoMvb->getBool(0x121,24,0);
    RM2CT_TSK_B1 = crrcRicoMvb->getBool(0x121,25,7);
    RM2CT_CSCB_B1 = crrcRicoMvb->getBool(0x121,25,6);
    RM2CT_BATTERY_B1 = crrcRicoMvb->getBool(0x121,25,5);
    RM2CT_standbyfuse_B1 = crrcRicoMvb->getBool(0x121,25,4);
    RM2CT_LVDR_B1 = crrcRicoMvb->getBool(0x121,25,3);
    RM2CT_batterybreaker_B1 = crrcRicoMvb->getBool(0x121,25,2);
    RM2CT_middlegrounding_B1 = crrcRicoMvb->getBool(0x121,25,1);
    RM2CT_BIS_B1 = crrcRicoMvb->getBool(0x121,25,0);
    RM2CT_1i1CHECK1_B1 = crrcRicoMvb->getBool(0x121,31,7);
    RM2CT_1i1CHECK0_B1 = crrcRicoMvb->getBool(0x121,31,6);
    RM3CT_DI1NOANSWER_B1 = crrcRicoMvb->getBool(0x130,24,0);
    RM3CT_DO1NOANSWER_B1 = crrcRicoMvb->getBool(0x130,25,0);
    RM3CT_LAT_B1 = crrcRicoMvb->getBool(0x130,30,0);
    RM3CT_RLD_B1 = crrcRicoMvb->getBool(0x130,30,1);
    RM3CT_1i0CHECK1_B1 = crrcRicoMvb->getBool(0x130,31,7);
    RM3CT_1i0CHECK0_B1 = crrcRicoMvb->getBool(0x130,31,6);
    RM3CT_ExtendPower_B1 = crrcRicoMvb->getBool(0x131,20,7);
    RM3CT_ACUPowerCover_B1 = crrcRicoMvb->getBool(0x131,20,6);
    RM3CT_PANIV_B1 = crrcRicoMvb->getBool(0x131,20,5);
    RM3CT_VVVF1TEMPARLM_B1 = crrcRicoMvb->getBool(0x131,20,4);
    RM3CT_VVVF2TEMPARLM_B1 = crrcRicoMvb->getBool(0x131,20,3);
    RM3CT_WOSEBR_B1 = crrcRicoMvb->getBool(0x131,20,2);
    RM3CT_BMSCB_B1 = crrcRicoMvb->getBool(0x131,20,1);
    RM3CT_HVBCB2_B1 = crrcRicoMvb->getBool(0x131,21,7);
    RM3CT_PANEBR_B1 = crrcRicoMvb->getBool(0x131,21,6);
    RM3CT_FUSE_B1 = crrcRicoMvb->getBool(0x131,21,5);
    RM3CT_HSCB1STATE_B1 = crrcRicoMvb->getBool(0x131,21,4);
    RM3CT_HSCB2STATE_B1 = crrcRicoMvb->getBool(0x131,21,3);
    RM3CT_BBIV1_B1 = crrcRicoMvb->getBool(0x131,21,2);
    RM3CT_BBIV2_B1 = crrcRicoMvb->getBool(0x131,21,1);
    RM3CT_PBIV_B1 = crrcRicoMvb->getBool(0x131,21,0);
    RM3CT_BRR1_B1 = crrcRicoMvb->getBool(0x131,22,7);
    RM3CT_BRR2_B1 = crrcRicoMvb->getBool(0x131,22,6);
    RM3CT_MPlightfault_B1 = crrcRicoMvb->getBool(0x131,22,5);
    RM3CT_DOWNPAN_B1 = crrcRicoMvb->getBool(0x131,22,4);
    RM3CT_UPPAN_B1 = crrcRicoMvb->getBool(0x131,22,3);
    RM3CT_UPRPAN_B1 = crrcRicoMvb->getBool(0x131,22,2);
    RM3CT_PTCB_B1 = crrcRicoMvb->getBool(0x131,22,1);
    RM3CT_HVBCB1_B1 = crrcRicoMvb->getBool(0x131,22,0);
    RM3CT_1i1CHECK1_B1 = crrcRicoMvb->getBool(0x131,31,7);
    RM3CT_1i1CHECK0_B1 = crrcRicoMvb->getBool(0x131,31,6);
    RM4CT_DI1NOANSWER_B1 = crrcRicoMvb->getBool(0x140,24,0);
    RM4CT_DI2NOANSWER_B1 = crrcRicoMvb->getBool(0x140,24,1);
    RM4CT_DI3NOANSWER_B1 = crrcRicoMvb->getBool(0x140,24,2);
    RM4CT_DI4NOANSWER_B1 = crrcRicoMvb->getBool(0x140,24,3);
    RM4CT_DO1NOANSWER_B1 = crrcRicoMvb->getBool(0x140,25,0);
    RM4CT_AX1NOANSWER_B1 = crrcRicoMvb->getBool(0x140,25,4);
    RM4CT_LAT_B1 = crrcRicoMvb->getBool(0x140,30,0);
    RM4CT_RLD_B1 = crrcRicoMvb->getBool(0x140,30,1);
    RM4CT_1i0CHECK1_B1 = crrcRicoMvb->getBool(0x140,31,7);
    RM4CT_1i0CHECK0_B1 = crrcRicoMvb->getBool(0x140,31,6);
    RM4CT_PBK_B1 = crrcRicoMvb->getBool(0x141,20,7);
    RM4CT_APBRCB_B1 = crrcRicoMvb->getBool(0x141,20,6);
    RM4CT_APBRR_B1 = crrcRicoMvb->getBool(0x141,20,5);
    RM4CT_ABRBS_B1 = crrcRicoMvb->getBool(0x141,20,4);
    RM4CT_ETABRR_B1 = crrcRicoMvb->getBool(0x141,20,3);
    RM4CT_ETEBL_B1 = crrcRicoMvb->getBool(0x141,20,2);
    RM4CT_ETRRL_B1 = crrcRicoMvb->getBool(0x141,20,1);
    RM4CT_MCCB_B1 = crrcRicoMvb->getBool(0x141,20,0);
    RM4CT_DMYR_B1 = crrcRicoMvb->getBool(0x141,21,7);
    RM4CT_LMRGBS_B1 = crrcRicoMvb->getBool(0x141,21,6);
    RM4CT_EBK_B1 = crrcRicoMvb->getBool(0x141,21,5);
    RM4CT_VCUEBR_B1 = crrcRicoMvb->getBool(0x141,21,4);
    RM4CT_EMPBR_B1 = crrcRicoMvb->getBool(0x141,21,3);
    RM4CT_EBBS_B1 = crrcRicoMvb->getBool(0x141,21,2);
    RM4CT_EBR_B1 = crrcRicoMvb->getBool(0x141,21,1);
    RM4CT_ZVR_B1 = crrcRicoMvb->getBool(0x141,21,0);
    RM4CT_WFLR_B1 = crrcRicoMvb->getBool(0x141,22,7);
    RM4CT_TCR_B1 = crrcRicoMvb->getBool(0x141,22,6);
    RM4CT_CTS_B1 = crrcRicoMvb->getBool(0x141,22,5);
    RM4CT_SLR_B1 = crrcRicoMvb->getBool(0x141,22,4);
    RM4CT_COR_B1 = crrcRicoMvb->getBool(0x141,22,3);
    RM4CT_CTR_B1 = crrcRicoMvb->getBool(0x141,22,2);
    RM4CT_EBCB_B1 = crrcRicoMvb->getBool(0x141,22,1);
    RM4CT_DMBPS_B1 = crrcRicoMvb->getBool(0x141,22,0);
    RM4CT_DRARR_B1 = crrcRicoMvb->getBool(0x141,23,7);
    RM4CT_DOCRL_B1 = crrcRicoMvb->getBool(0x141,23,6);
    RM4CT_DOCRR_B1 = crrcRicoMvb->getBool(0x141,23,5);
    RM4CT_DCCRL_B1 = crrcRicoMvb->getBool(0x141,23,4);
    RM4CT_DCCRR_B1 = crrcRicoMvb->getBool(0x141,23,3);
    RM4CT_AMR_B1 = crrcRicoMvb->getBool(0x141,23,2);
    RM4CT_ARR12_B1 = crrcRicoMvb->getBool(0x141,23,1);
    RM4CT_CTSHSD_B1 = crrcRicoMvb->getBool(0x141,23,0);
    RM4CT_ETRL_B1 = crrcRicoMvb->getBool(0x141,24,7);
    RM4CT_RESTART_B1 = crrcRicoMvb->getBool(0x141,24,6);
    RM4CT_ETETML_B1 = crrcRicoMvb->getBool(0x141,24,5);
    RM4CT_PBRBPS_B1 = crrcRicoMvb->getBool(0x141,24,4);
    RM4CT_PEBS_B1 = crrcRicoMvb->getBool(0x141,24,3);
    RM4CT_DIRL12_B1 = crrcRicoMvb->getBool(0x141,24,2);
    RM4CT_DIRR12_B1 = crrcRicoMvb->getBool(0x141,24,1);
    RM4CT_DRARL_B1 = crrcRicoMvb->getBool(0x141,24,0);
    RM4CT_RVBPS_B1 = crrcRicoMvb->getBool(0x141,25,7);
    RM4CT_HSCBON_B1 = crrcRicoMvb->getBool(0x141,25,6);
    RM4CT_HSCBOFF_B1 = crrcRicoMvb->getBool(0x141,25,5);
    RM4CT_Keyrtainline_B1 = crrcRicoMvb->getBool(0x141,25,4);
    RM4CT_TDL_B1 = crrcRicoMvb->getBool(0x141,25,3);
    RM4CT_BDL_B1 = crrcRicoMvb->getBool(0x141,25,2);
    RM4CT_FBDL_B1 = crrcRicoMvb->getBool(0x141,25,1);
    RM4CT_ETFL_B1 = crrcRicoMvb->getBool(0x141,25,0);
    RM4CT_ATPOUTBRAKE_B1 = crrcRicoMvb->getBool(0x141,26,7);
    RM4CT_AMTDR_B1 = crrcRicoMvb->getBool(0x141,26,6);
    RM4CT_AMBDR_B1 = crrcRicoMvb->getBool(0x141,26,5);
    RM4CT_ATPFK1_B1 = crrcRicoMvb->getBool(0x141,26,4);
    RM4CT_ATPFK2_B1 = crrcRicoMvb->getBool(0x141,26,3);
    RM4CT_ATPOTCB_B1 = crrcRicoMvb->getBool(0x141,26,2);
    RM4CT_DORSL_B1 = crrcRicoMvb->getBool(0x141,26,1);
    RM4CT_DORSR_B1 = crrcRicoMvb->getBool(0x141,26,0);
    RM4CT_PDCS_B1 = crrcRicoMvb->getBool(0x141,27,7);
    RM4CT_TLPB_B1 = crrcRicoMvb->getBool(0x141,27,6);
    RM4CT_RRPB_B1 = crrcRicoMvb->getBool(0x141,27,5);
    RM4CT_EMPB_B1 = crrcRicoMvb->getBool(0x141,27,4);
    RM4CT_DBYS_B1 = crrcRicoMvb->getBool(0x141,27,3);
    RM4CT_COAST_B1 = crrcRicoMvb->getBool(0x141,27,2);
    RM4CT_DMS_B1 = crrcRicoMvb->getBool(0x141,27,1);
    RM4CT_WM_B1 = crrcRicoMvb->getBool(0x141,27,0);
    RM4CT_DBPS_B1 = crrcRicoMvb->getBool(0x141,28,7);
    RM4CT_ATPFS_B1 = crrcRicoMvb->getBool(0x141,28,6);
    RM4CT_DRBYS_B1 = crrcRicoMvb->getBool(0x141,28,5);
    RM4CT_ATPACTIVE_B1 = crrcRicoMvb->getBool(0x141,28,4);
    RM4CT_RDER_B1 = crrcRicoMvb->getBool(0x141,28,3);
    RM4CT_LDER_B1 = crrcRicoMvb->getBool(0x141,28,2);
    RM4CT_VZCR_B1 = crrcRicoMvb->getBool(0x141,28,1);
    RM4CT_ATOHOLDINGBRAKE_B1 = crrcRicoMvb->getBool(0x141,28,0);
    RM4CT_1i1CHECK1_B1 = crrcRicoMvb->getBool(0x141,31,7);
    RM4CT_1i1CHECK0_B1 = crrcRicoMvb->getBool(0x141,31,6);
    RM4CT_BSCB_B1 = crrcRicoMvb->getBool(0x142,21,7);
    RM4CT_ZVBS_B1 = crrcRicoMvb->getBool(0x142,22,7);
    RM4CT_ZVRCB1_B1 = crrcRicoMvb->getBool(0x142,22,6);
    RM4CT_ZVRCB2_B1 = crrcRicoMvb->getBool(0x142,22,5);
    RM4CT_DOTCB_B1 = crrcRicoMvb->getBool(0x142,22,4);
    RM4CT_DCTCB_B1 = crrcRicoMvb->getBool(0x142,22,3);
    RM4CT_DRCBL_B1 = crrcRicoMvb->getBool(0x142,22,2);
    RM4CT_DRCBR_B1 = crrcRicoMvb->getBool(0x142,22,1);
    RM4CT_DENACB_B1 = crrcRicoMvb->getBool(0x142,22,0);
    RM4CT_1i2CHECK1_B1 = crrcRicoMvb->getBool(0x142,31,7);
    RM4CT_1i2CHECK0_B1 = crrcRicoMvb->getBool(0x142,31,6);
    RM5CT_DI1NOANSWER_B1 = crrcRicoMvb->getBool(0x150,24,0);
    RM5CT_DI2NOANSWER_B1 = crrcRicoMvb->getBool(0x150,24,1);
    RM5CT_DO1NOANSWER_B1 = crrcRicoMvb->getBool(0x150,25,0);
    RM5CT_LAT_B1 = crrcRicoMvb->getBool(0x150,30,0);
    RM5CT_RLD_B1 = crrcRicoMvb->getBool(0x150,30,1);
    RM5CT_1i0CHECK1_B1 = crrcRicoMvb->getBool(0x150,31,7);
    RM5CT_1i0CHECK0_B1 = crrcRicoMvb->getBool(0x150,31,6);
    RM5CT_ETFL_B1 = crrcRicoMvb->getBool(0x151,20,7);
    RM5CT_ETRL_B1 = crrcRicoMvb->getBool(0x151,20,6);
    RM5CT_BMSCB_B1 = crrcRicoMvb->getBool(0x151,20,5);
    RM5CT_LODTL_B1 = crrcRicoMvb->getBool(0x151,21,7);
    RM5CT_LCDTL_B1 = crrcRicoMvb->getBool(0x151,21,6);
    RM5CT_LZVTLL_B1 = crrcRicoMvb->getBool(0x151,21,5);
    RM5CT_RZVTLL_B1 = crrcRicoMvb->getBool(0x151,21,4);
    RM5CT_VRFAULT_B1 = crrcRicoMvb->getBool(0x151,21,3);
    RM5CT_TDL_B1 = crrcRicoMvb->getBool(0x151,21,1);
    RM5CT_BDL_B1 = crrcRicoMvb->getBool(0x151,21,0);
    RM5CT_BRR1_B1 = crrcRicoMvb->getBool(0x151,22,7);
    RM5CT_BRR2_B1 = crrcRicoMvb->getBool(0x151,22,6);
    RM5CT_RDRTL_B1 = crrcRicoMvb->getBool(0x151,22,5);
    RM5CT_RODTL_B1 = crrcRicoMvb->getBool(0x151,22,4);
    RM5CT_RCDTL_B1 = crrcRicoMvb->getBool(0x151,22,3);
    RM5CT_LZVTLR_B1 = crrcRicoMvb->getBool(0x151,22,2);
    RM5CT_RZVTLR_B1 = crrcRicoMvb->getBool(0x151,22,1);
    RM5CT_LDRTL_B1 = crrcRicoMvb->getBool(0x151,22,0);
    RM5CT_CMK_B1 = crrcRicoMvb->getBool(0x151,23,7);
    RM5CT_CBBIV_B1 = crrcRicoMvb->getBool(0x151,23,6);
    RM5CT_EWSV_B1 = crrcRicoMvb->getBool(0x151,23,5);
    RM5CT_VVVF3arlm_B1 = crrcRicoMvb->getBool(0x151,23,4);
    RM5CT_SIVTEMPARLM_B1 = crrcRicoMvb->getBool(0x151,23,3);
    RM5CT_MRPS_B1 = crrcRicoMvb->getBool(0x151,24,7);
    RM5CT_SIV_B1 = crrcRicoMvb->getBool(0x151,24,6);
    RM5CT_ADUPS1_B1 = crrcRicoMvb->getBool(0x151,24,5);
    RM5CT_ADUPS2_B1 = crrcRicoMvb->getBool(0x151,24,4);
    RM5CT_BBIV1_B1 = crrcRicoMvb->getBool(0x151,24,3);
    RM5CT_BBIV2_B1 = crrcRicoMvb->getBool(0x151,24,2);
    RM5CT_PBIV_B1 = crrcRicoMvb->getBool(0x151,24,1);
    RM5CT_Batteryfuse_B1 = crrcRicoMvb->getBool(0x151,24,0);
    RM5CT_TSK_B1 = crrcRicoMvb->getBool(0x151,25,7);
    RM5CT_CSCB_B1 = crrcRicoMvb->getBool(0x151,25,6);
    RM5CT_BATTERY_B1 = crrcRicoMvb->getBool(0x151,25,5);
    RM5CT_standbyfuse_B1 = crrcRicoMvb->getBool(0x151,25,4);
    RM5CT_LVDR_B1 = crrcRicoMvb->getBool(0x151,25,3);
    RM5CT_batterybreaker_B1 = crrcRicoMvb->getBool(0x151,25,2);
    RM5CT_middlegrounding_B1 = crrcRicoMvb->getBool(0x151,25,1);
    RM5CT_BIS_B1 = crrcRicoMvb->getBool(0x151,25,0);
    RM5CT_1i1CHECK1_B1 = crrcRicoMvb->getBool(0x151,31,7);
    RM5CT_1i1CHECK0_B1 = crrcRicoMvb->getBool(0x151,31,6);
    RM6CT_DI1NOANSWER_B1 = crrcRicoMvb->getBool(0x160,24,0);
    RM6CT_DO1NOANSWER_B1 = crrcRicoMvb->getBool(0x160,25,0);
    RM6CT_LAT_B1 = crrcRicoMvb->getBool(0x160,30,0);
    RM6CT_RLD_B1 = crrcRicoMvb->getBool(0x160,30,1);
    RM6CT_1i0CHECK1_B1 = crrcRicoMvb->getBool(0x160,31,7);
    RM6CT_1i0CHECK0_B1 = crrcRicoMvb->getBool(0x160,31,6);
    RM6CT_ExtendPower_B1 = crrcRicoMvb->getBool(0x161,20,7);
    RM6CT_ACUPowerCover_B1 = crrcRicoMvb->getBool(0x161,20,6);
    RM6CT_PANIV_B1 = crrcRicoMvb->getBool(0x161,20,5);
    RM6CT_VVVF1TEMPARLM_B1 = crrcRicoMvb->getBool(0x161,20,4);
    RM6CT_VVVF2TEMPARLM_B1 = crrcRicoMvb->getBool(0x161,20,3);
    RM6CT_WOSEBR_B1 = crrcRicoMvb->getBool(0x161,20,2);
    RM6CT_BMSCB_B1 = crrcRicoMvb->getBool(0x161,20,1);
    RM6CT_HVBCB2_B1 = crrcRicoMvb->getBool(0x161,21,7);
    RM6CT_PANEBR_B1 = crrcRicoMvb->getBool(0x161,21,6);
    RM6CT_FUSE_B1 = crrcRicoMvb->getBool(0x161,21,5);
    RM6CT_HSCB1STATE_B1 = crrcRicoMvb->getBool(0x161,21,4);
    RM6CT_HSCB2STATE_B1 = crrcRicoMvb->getBool(0x161,21,3);
    RM6CT_BBIV1_B1 = crrcRicoMvb->getBool(0x161,21,2);
    RM6CT_BBIV2_B1 = crrcRicoMvb->getBool(0x161,21,1);
    RM6CT_PBIV_B1 = crrcRicoMvb->getBool(0x161,21,0);
    RM6CT_BRR1_B1 = crrcRicoMvb->getBool(0x161,22,7);
    RM6CT_BRR2_B1 = crrcRicoMvb->getBool(0x161,22,6);
    RM6CT_MPlightfault_B1 = crrcRicoMvb->getBool(0x161,22,5);
    RM6CT_DOWNPAN_B1 = crrcRicoMvb->getBool(0x161,22,4);
    RM6CT_UPPAN_B1 = crrcRicoMvb->getBool(0x161,22,3);
    RM6CT_UPRPAN_B1 = crrcRicoMvb->getBool(0x161,22,2);
    RM6CT_PTCB_B1 = crrcRicoMvb->getBool(0x161,22,1);
    RM6CT_HVBCB1_B1 = crrcRicoMvb->getBool(0x161,22,0);
    RM6CT_1i1CHECK1_B1 = crrcRicoMvb->getBool(0x161,31,7);
    RM6CT_1i1CHECK0_B1 = crrcRicoMvb->getBool(0x161,31,6);


    RM1CT_GWLifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x110,0);
    RM1CT_GWVersion_U8 = crrcRicoMvb->getUnsignedChar(0x110,1);
    RM1CT_DIVersion_U8 = crrcRicoMvb->getUnsignedChar(0x110,2);
    RM1CT_DOVersion_U8 = crrcRicoMvb->getUnsignedChar(0x110,3);
    RM1CT_AXVersion_U8 = crrcRicoMvb->getUnsignedChar(0x110,4);
    RM1CT_DI1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x110,6);
    RM1CT_DI2LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x110,7);
    RM1CT_DI3LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x110,8);
    RM1CT_DI4LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x110,9);
    RM1CT_DO1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x110,14);
    RM1CT_AX1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x110,18);
    RM2CT_GWLifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x120,0);
    RM2CT_GWVersion_U8 = crrcRicoMvb->getUnsignedChar(0x120,1);
    RM2CT_DIVersion_U8 = crrcRicoMvb->getUnsignedChar(0x120,2);
    RM2CT_DOVersion_U8 = crrcRicoMvb->getUnsignedChar(0x120,3);
    RM2CT_AXVersion_U8 = crrcRicoMvb->getUnsignedChar(0x120,4);
    RM2CT_DI1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x120,6);
    RM2CT_DI2LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x120,7);
    RM2CT_DO1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x120,14);
    RM3CT_GWLifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x130,0);
    RM3CT_GWVersion_U8 = crrcRicoMvb->getUnsignedChar(0x130,1);
    RM3CT_DIVersion_U8 = crrcRicoMvb->getUnsignedChar(0x130,2);
    RM3CT_DOVersion_U8 = crrcRicoMvb->getUnsignedChar(0x130,3);
    RM3CT_DI1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x130,6);
    RM3CT_DO1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x130,14);
    RM4CT_GWLifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x140,0);
    RM4CT_GWVersion_U8 = crrcRicoMvb->getUnsignedChar(0x140,1);
    RM4CT_DIVersion_U8 = crrcRicoMvb->getUnsignedChar(0x140,2);
    RM4CT_DOVersion_U8 = crrcRicoMvb->getUnsignedChar(0x140,3);
    RM4CT_AXVersion_U8 = crrcRicoMvb->getUnsignedChar(0x140,4);
    RM4CT_DI1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x140,6);
    RM4CT_DI2LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x140,7);
    RM4CT_DI3LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x140,8);
    RM4CT_DI4LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x140,9);
    RM4CT_DO1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x140,14);
    RM4CT_AX1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x140,18);
    RM5CT_GWLifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x150,0);
    RM5CT_GWVersion_U8 = crrcRicoMvb->getUnsignedChar(0x150,1);
    RM5CT_DIVersion_U8 = crrcRicoMvb->getUnsignedChar(0x150,2);
    RM5CT_DOVersion_U8 = crrcRicoMvb->getUnsignedChar(0x150,3);
    RM5CT_AXVersion_U8 = crrcRicoMvb->getUnsignedChar(0x150,4);
    RM5CT_DI1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x150,6);
    RM5CT_DI2LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x150,7);
    RM5CT_DO1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x150,14);
    RM6CT_GWLifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x160,0);
    RM6CT_GWVersion_U8 = crrcRicoMvb->getUnsignedChar(0x160,1);
    RM6CT_DIVersion_U8 = crrcRicoMvb->getUnsignedChar(0x160,2);
    RM6CT_DOVersion_U8 = crrcRicoMvb->getUnsignedChar(0x160,3);
    RM6CT_DI1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x160,6);
    RM6CT_DO1LifeSignal_U8 = crrcRicoMvb->getUnsignedChar(0x160,14);

    RM1CT_MCREFSETPOINT_U16 = crrcRicoMvb->getUnsignedInt(0x111,0);
    RM1CT_ATCREF_U16 = crrcRicoMvb->getUnsignedInt(0x111,2);
    RM4CT_MCREFSETPOINT_U16 = crrcRicoMvb->getUnsignedInt(0x141,0);
    RM4CT_ATCREF_U16 = crrcRicoMvb->getUnsignedInt(0x141,2);

    RMICT_ByPass = RM1CT_DMBPS_B1 | RM4CT_DMBPS_B1 | RM1CT_LMRGBS_B1
                    | RM4CT_LMRGBS_B1 |RM1CT_EBBS_B1 | RM4CT_EBBS_B1
                    | RM1CT_ABRBS_B1 | RM4CT_ABRBS_B1 | RM1CT_RVBPS_B1
                    | RM4CT_RVBPS_B1 | RM1CT_PBRBPS_B1 | RM4CT_PBRBPS_B1
                    | RM1CT_PEBS_B1 | RM4CT_PEBS_B1 | RM1CT_DBPS_B1
                    | RM4CT_DBPS_B1 | RM1CT_ATPFS_B1 | RM4CT_ATPFS_B1
                    | RM1CT_ZVBS_B1| RM4CT_ZVBS_B1;
    //CCU-RIOM
    CTR1_DOPANI_B1 = crrcRicoMvb->getBool(0x118,19,7);
    CTR1_DOHSCBC_B1 = crrcRicoMvb->getBool(0x118,19,6);
    CTR1_DOHSCB0_B1 = crrcRicoMvb->getBool(0x118,19,5);
    CTR1_DOVCUEBR_B1 = crrcRicoMvb->getBool(0x118,19,4);
    CTR1_DOLOACHF_B1 = crrcRicoMvb->getBool(0x118,19,3);
    CTR1_DOWFLR_B1 = crrcRicoMvb->getBool(0x118,20,7);
    CTR1_DOTCR_B1 = crrcRicoMvb->getBool(0x118,20,6);
    CTR1_DOHVIVDCP_B1 = crrcRicoMvb->getBool(0x118,20,5);
    CTR1_DOHIVNC_B1 = crrcRicoMvb->getBool(0x118,20,4);
    CTR1_DOLVDR_B1 = crrcRicoMvb->getBool(0x118,20,3);
    CTR1_DOLOASMON_B1 = crrcRicoMvb->getBool(0x118,20,2);
    CTR1_DOBSOI_B1 = crrcRicoMvb->getBool(0x118,20,1);
    CTR1_DOPANDI_B1 = crrcRicoMvb->getBool(0x118,20,0);
    CTR1_1i8CHECK1_B1 = crrcRicoMvb->getBool(0x118,31,7);
    CTR1_1i8CHECK0_B1 = crrcRicoMvb->getBool(0x118,31,6);

    CTR4_DOPANI_B1 = crrcRicoMvb->getBool(0x148,19,7);
    CTR4_DOHSCBC_B1 = crrcRicoMvb->getBool(0x148,19,6);
    CTR4_DOHSCB0_B1 = crrcRicoMvb->getBool(0x148,19,5);
    CTR4_DOVCUEBR_B1 = crrcRicoMvb->getBool(0x148,19,4);
    CTR4_DOLOACHF_B1 = crrcRicoMvb->getBool(0x148,19,3);
    CTR4_DOWFLR_B1 = crrcRicoMvb->getBool(0x148,20,7);
    CTR4_DOTCR_B1 = crrcRicoMvb->getBool(0x148,20,6);
    CTR4_DOHVIVDCP_B1 = crrcRicoMvb->getBool(0x148,20,5);
    CTR4_DOHIVNC_B1 = crrcRicoMvb->getBool(0x148,20,4);
    CTR4_DOLVDR_B1 = crrcRicoMvb->getBool(0x148,20,3);
    CTR4_DOLOASMON_B1 = crrcRicoMvb->getBool(0x148,20,2);
    CTR4_DOBSOI_B1 = crrcRicoMvb->getBool(0x148,20,1);
    CTR4_DOPANDI_B1 = crrcRicoMvb->getBool(0x148,20,0);
    CTR4_1i8CHECK1_B1 = crrcRicoMvb->getBool(0x148,31,7);
    CTR4_1i8CHECK0_B1 = crrcRicoMvb->getBool(0x148,31,6);

    CTR3_MP1EXRBATTERY_B1 = crrcRicoMvb->getBool(0x138,20,7);
    CTR3_MP1LOYR_B1 = crrcRicoMvb->getBool(0x138,20,6);
    CTR3_1i8CHECK1_B1 = crrcRicoMvb->getBool(0x138,31,7);
    CTR3_1i8CHECK0_B1 = crrcRicoMvb->getBool(0x138,31,6);

    CTR6_MP1EXRBATTERY_B1 = crrcRicoMvb->getBool(0x168,20,7);
    CTR6_MP1LOYR_B1 = crrcRicoMvb->getBool(0x168,20,6);
    CTR6_1i8CHECK1_B1 = crrcRicoMvb->getBool(0x168,31,7);
    CTR6_1i8CHECK0_B1 = crrcRicoMvb->getBool(0x168,31,6);





    //*******************************************ERM-CCU***********************************//
    E1CT_ERMSWVerValid_B1 = crrcRicoMvb->getBool(0x210,15,0);
    E2CT_ERMSWVerValid_B1 = crrcRicoMvb->getBool(0x220,15,0);

    E1CT_ERMPLCVer_U8 = crrcRicoMvb->getUnsignedChar(0x210,8);
    E1CT_ERMVxWorksVer_U8 = crrcRicoMvb->getUnsignedChar(0x210,9);
    E1CT_ERMMVBSWVer_U8 = crrcRicoMvb->getUnsignedChar(0x210,10);
    E1CT_ERMSDBVer_U8 = crrcRicoMvb->getUnsignedChar(0x210,11);

    E1CT_ERMSWVer_U8 = crrcRicoMvb->getUnsignedChar(0x210,2);
    E1CT_AcTestStatus_U8 = crrcRicoMvb->getUnsignedChar(0x210,21);
    E1CT_AcTestV0_U8 = crrcRicoMvb->getUnsignedChar(0x210,24);
    E1CT_AcTestVt_U8 = crrcRicoMvb->getUnsignedChar(0x210,25);
    E1CT_AcTestSH_U8 = crrcRicoMvb->getUnsignedChar(0x210,26);
    E1CT_AcTestSL_U8 = crrcRicoMvb->getUnsignedChar(0x210,27);
    E1CT_RidingRate1_U8 = crrcRicoMvb->getUnsignedChar(0x210,28);
    E1CT_RidingRate2_U8 = crrcRicoMvb->getUnsignedChar(0x210,29);
    E1CT_RidingRate3_U8 = crrcRicoMvb->getUnsignedChar(0x210,30);
    E1CT_RidingRate_U8 = crrcRicoMvb->getUnsignedChar(0x210,31);

    E1CT_TotalDistanceYear_U8 = crrcRicoMvb->getUnsignedChar(0x211,7);
    E1CT_TotalDistanceMonth_U8 = crrcRicoMvb->getUnsignedChar(0x211,8);
    E1CT_TotalDistanceDay_U8 = crrcRicoMvb->getUnsignedChar(0x211,9);

    E1CT_TractionECYear_U8 = crrcRicoMvb->getUnsignedChar(0x211,16);
    E1CT_TractionECMonth_U8 = crrcRicoMvb->getUnsignedChar(0x211,17);
    E1CT_TractionECDay_U8 = crrcRicoMvb->getUnsignedChar(0x211,18);

    E1CT_AxPowerECYear_U8 = crrcRicoMvb->getUnsignedChar(0x211,19);
    E1CT_AxPowerECMonth_U8 = crrcRicoMvb->getUnsignedChar(0x211,20);
    E1CT_AxPowerECDay_U8 = crrcRicoMvb->getUnsignedChar(0x211,21);

    E1CT_ReEngyYear_U8 = crrcRicoMvb->getUnsignedChar(0x212,9);
    E1CT_ReEngyMonth_U8 = crrcRicoMvb->getUnsignedChar(0x212,10);
    E1CT_ReEngyDay_U8 = crrcRicoMvb->getUnsignedChar(0x212,11);

    E1CT_ServiceDistanceYear_U8 = crrcRicoMvb->getUnsignedChar(0x212,12);
    E1CT_ServiceDistanceMonth_U8 = crrcRicoMvb->getUnsignedChar(0x212,13);
    E1CT_ServiceDistanceDay_U8 = crrcRicoMvb->getUnsignedChar(0x212,14);

    E1CT_AP1ECYear_U8 = crrcRicoMvb->getUnsignedChar(0x212,15);
    E1CT_AP1ECMonth_U8 = crrcRicoMvb->getUnsignedChar(0x212,16);
    E1CT_AP1ECDay_U8 = crrcRicoMvb->getUnsignedChar(0x212,17);

    E1CT_AP2ECYear_U8 = crrcRicoMvb->getUnsignedChar(0x212,18);
    E1CT_AP2ECMonth_U8 = crrcRicoMvb->getUnsignedChar(0x212,19);
    E1CT_AP2ECDay_U8 = crrcRicoMvb->getUnsignedChar(0x212,20);

    E1CT_TCMSTotalTimeYear_U8 = crrcRicoMvb->getUnsignedChar(0x212,21);
    E1CT_TCMSTotalTimeMonth_U8 = crrcRicoMvb->getUnsignedChar(0x212,22);
    E1CT_TCMSTotalTimeDay_U8 = crrcRicoMvb->getUnsignedChar(0x212,23);



    E2CT_ERMPLCVer_U8 = crrcRicoMvb->getUnsignedChar(0x210,8);
    E2CT_ERMVxWorksVer_U8 = crrcRicoMvb->getUnsignedChar(0x220,9);
    E2CT_ERMMVBSWVer_U8 = crrcRicoMvb->getUnsignedChar(0x220,10);
    E2CT_ERMSDBVer_U8 = crrcRicoMvb->getUnsignedChar(0x220,11);

    E2CT_ERMSWVer_U8 = crrcRicoMvb->getUnsignedChar(0x220,2);
    E2CT_AcTestStatus_U8 = crrcRicoMvb->getUnsignedChar(0x220,21);
    E2CT_AcTestV0_U8 = crrcRicoMvb->getUnsignedChar(0x220,24);
    E2CT_AcTestVt_U8 = crrcRicoMvb->getUnsignedChar(0x220,25);
    E2CT_AcTestSH_U8 = crrcRicoMvb->getUnsignedChar(0x220,26);
    E2CT_AcTestSL_U8 = crrcRicoMvb->getUnsignedChar(0x220,27);
    E2CT_RidingRate1_U8 = crrcRicoMvb->getUnsignedChar(0x220,28);
    E2CT_RidingRate2_U8 = crrcRicoMvb->getUnsignedChar(0x220,29);
    E2CT_RidingRate3_U8 = crrcRicoMvb->getUnsignedChar(0x220,30);
    E2CT_RidingRate_U8 = crrcRicoMvb->getUnsignedChar(0x220,31);
    E2CT_TotalDistanceYear_U8 = crrcRicoMvb->getUnsignedChar(0x222,0);
    E2CT_TotalDistanceMonth_U8 = crrcRicoMvb->getUnsignedChar(0x222,1);
    E2CT_TotalDistanceDay_U8 = crrcRicoMvb->getUnsignedChar(0x222,2);
    E2CT_TractionECYear_U8 = crrcRicoMvb->getUnsignedChar(0x222,3);
    E2CT_TractionECMonth_U8 = crrcRicoMvb->getUnsignedChar(0x222,4);
    E2CT_TractionECDay_U8 = crrcRicoMvb->getUnsignedChar(0x222,5);
    E2CT_AxPowerECYear_U8 = crrcRicoMvb->getUnsignedChar(0x222,6);
    E2CT_AxPowerECMonth_U8 = crrcRicoMvb->getUnsignedChar(0x222,7);
    E2CT_AxPowerECDay_U8 = crrcRicoMvb->getUnsignedChar(0x222,8);
    E2CT_ReEngyYear_U8 = crrcRicoMvb->getUnsignedChar(0x222,9);
    E2CT_ReEngyMonth_U8 = crrcRicoMvb->getUnsignedChar(0x222,10);
    E2CT_ReEngyDay_U8 = crrcRicoMvb->getUnsignedChar(0x222,11);
    E2CT_ServiceDistanceYear_U8 = crrcRicoMvb->getUnsignedChar(0x222,12);
    E2CT_ServiceDistanceMonth_U8 = crrcRicoMvb->getUnsignedChar(0x222,13);
    E2CT_ServiceDistanceDay_U8 = crrcRicoMvb->getUnsignedChar(0x222,14);
    E2CT_AP1ECYear_U8 = crrcRicoMvb->getUnsignedChar(0x222,15);
    E2CT_AP1ECMonth_U8 = crrcRicoMvb->getUnsignedChar(0x222,16);
    E2CT_AP1ECDay_U8 = crrcRicoMvb->getUnsignedChar(0x222,17);
    E2CT_AP2ECYear_U8 = crrcRicoMvb->getUnsignedChar(0x222,18);
    E2CT_AP2ECMonth_U8 = crrcRicoMvb->getUnsignedChar(0x222,19);
    E2CT_AP2ECDay_U8 = crrcRicoMvb->getUnsignedChar(0x222,20);
    E2CT_TCMSTotalTimeYear_U8 = crrcRicoMvb->getUnsignedChar(0x222,21);
    E2CT_TCMSTotalTimeMonth_U8 = crrcRicoMvb->getUnsignedChar(0x222,22);
    E2CT_TCMSTotalTimeDay_U8 = crrcRicoMvb->getUnsignedChar(0x222,23);


    E1CT_AcTestA_I8 = crrcRicoMvb->getSignedChar(0x210,22);
    E1CT_AcTestLevel_I8 = crrcRicoMvb->getSignedChar(0x210,23);
    E2CT_AcTestA_I8 = crrcRicoMvb->getSignedChar(0x220,22);
    E2CT_AcTestLevel_I8 = crrcRicoMvb->getSignedChar(0x220,23);

    E1CT_RunningKilometers_U32 = crrcRicoMvb->getUnsignedInt32(0x211,0);
    E1CT_TractionEngyConsumption_U32 = crrcRicoMvb->getUnsignedInt32(0x211,4);
    E1CT_AxPowerEngyConsumption_U32 = crrcRicoMvb->getUnsignedInt32(0x211,8);
    E1CT_ReEngy_U32 = crrcRicoMvb->getUnsignedInt32(0x211,12);
    E1CT_ServiceDistance_U32 = crrcRicoMvb->getUnsignedInt32(0x211,16);
    E1CT_AP1RunningTime_U32 = crrcRicoMvb->getUnsignedInt32(0x211,20);
    E1CT_AP2RunningTime_U32 = crrcRicoMvb->getUnsignedInt32(0x211,24);
    E1CT_TCMSTotalTime_U32 = crrcRicoMvb->getUnsignedInt32(0x211,28);
    E2CT_RunningKilometers_U32 = crrcRicoMvb->getUnsignedInt32(0x221,0);
    E2CT_TractionEngyConsumption_U32 = crrcRicoMvb->getUnsignedInt32(0x221,4);
    E2CT_AxPowerEngyConsumption_U32 = crrcRicoMvb->getUnsignedInt32(0x221,8);
    E2CT_ReEngy_U32 = crrcRicoMvb->getUnsignedInt32(0x221,12);
    E2CT_ServiceDistance_U32 = crrcRicoMvb->getUnsignedInt32(0x221,16);
    E2CT_AP1RunningTime_U32 = crrcRicoMvb->getUnsignedInt32(0x221,20);
    E2CT_AP2RunningTime_U32 = crrcRicoMvb->getUnsignedInt32(0x221,24);
    E2CT_TCMSTotalTime_U32 = crrcRicoMvb->getUnsignedInt32(0x221,28);


    /****************************************************CCU-HMI********************************************/
    //zaixianhuangtai
    B1CT_MstrGV_B1=crrcRicoMvb->getUnsignedInt(0x711,18);
    B2CT_MstrGV_B1=crrcRicoMvb->getUnsignedInt(0x721,18);
    B3CT_MstrGV_B1=crrcRicoMvb->getUnsignedInt(0x731,18);
    B4CT_MstrGV_B1=crrcRicoMvb->getUnsignedInt(0x741,18);
    B5CT_MstrGV_B1=crrcRicoMvb->getUnsignedInt(0x751,18);
    B6CT_MstrGV_B1=crrcRicoMvb->getUnsignedInt(0x761,18);
    B7CT_MstrGV_B1=crrcRicoMvb->getUnsignedInt(0x771,18);
    B8CT_MstrGV_B1=crrcRicoMvb->getUnsignedInt(0x781,18);

    CTD_CCU1OLINE_B1 = crrcRicoMvb->getBool(0x308,0,0);
    CTD_CCU2OLINE_B1 = crrcRicoMvb->getBool(0x308,0,1);
    CTD_ERM1OLINE_B1 = crrcRicoMvb->getBool(0x308,0,2);
    CTD_ERM2OLINE_B1 = crrcRicoMvb->getBool(0x308,0,3);
    CTD_DDU1OLINE_B1 = crrcRicoMvb->getBool(0x308,0,4);
    CTD_DDU2OLINE_B1 = crrcRicoMvb->getBool(0x308,0,5);
    CTD_RIOM1GWOLINE_B1 = crrcRicoMvb->getBool(0x308,0,6);
    CTD_RIOM2GWOLINE_B1 = crrcRicoMvb->getBool(0x308,0,7);
    CTD_RIOM3GWOLINE_B1 = crrcRicoMvb->getBool(0x308,1,0);
    CTD_RIOM4GWOLINE_B1 = crrcRicoMvb->getBool(0x308,1,1);
    CTD_RIOM5GWOLINE_B1 = crrcRicoMvb->getBool(0x308,1,2);
    CTD_RIOM6GWOLINE_B1 = crrcRicoMvb->getBool(0x308,1,3);
    CTD_RIOM1DI1OLINE_B1 = crrcRicoMvb->getBool(0x308,1,4);
    CTD_RIOM1DI2OLINE_B1 = crrcRicoMvb->getBool(0x308,1,5);
    CTD_RIOM1DI3OLINE_B1 = crrcRicoMvb->getBool(0x308,1,6);
    CTD_RIOM1DI4OLINE_B1 = crrcRicoMvb->getBool(0x308,1,7);
    CTD_RIOM1DO1OLINE_B1 = crrcRicoMvb->getBool(0x308,2,0);
    CTD_RIOM1AX1OLINE_B1 = crrcRicoMvb->getBool(0x308,2,1);
    CTD_RIOM2DI1OLINE_B1 = crrcRicoMvb->getBool(0x308,2,2);
    CTD_RIOM2DI2OLINE_B1 = crrcRicoMvb->getBool(0x308,2,3);
    CTD_RIOM2DO1OLINE_B1 = crrcRicoMvb->getBool(0x308,2,4);
    CTD_RIOM3DI1OLINE_B1 = crrcRicoMvb->getBool(0x308,2,5);
    CTD_RIOM3DO1OLINE_B1 = crrcRicoMvb->getBool(0x308,2,6);
    CTD_RIOM4DI1OLINE_B1 = crrcRicoMvb->getBool(0x308,2,7);
    CTD_RIOM4DI2OLINE_B1 = crrcRicoMvb->getBool(0x308,3,0);
    CTD_RIOM4DI3OLINE_B1 = crrcRicoMvb->getBool(0x308,3,1);
    CTD_RIOM4DI41OLINE_B1 = crrcRicoMvb->getBool(0x308,3,2);
    CTD_RIOM4DO1OLINE_B1 = crrcRicoMvb->getBool(0x308,3,3);
    CTD_RIOM4AX1OLINE_B1 = crrcRicoMvb->getBool(0x308,3,4);
    CTD_RIOM5DI1OLINE_B1 = crrcRicoMvb->getBool(0x308,3,5);
    CTD_RIOM5DI2OLINE_B1 = crrcRicoMvb->getBool(0x308,3,6);
    CTD_RIOM5DO1OLINE_B1 = crrcRicoMvb->getBool(0x308,3,7);
    CTD_RIOM6DI1OLINE_B1 = crrcRicoMvb->getBool(0x308,4,0);
    CTD_RIOM6DO1OLINE_B1 = crrcRicoMvb->getBool(0x308,4,1);
    CTD_TCU1OLINE_B1 = crrcRicoMvb->getBool(0x308,4,2);
    CTD_TCU2OLINE_B1 = crrcRicoMvb->getBool(0x308,4,3);
    CTD_TCU3OLINE_B1 = crrcRicoMvb->getBool(0x308,4,4);
    CTD_TCU4OLINE_B1 = crrcRicoMvb->getBool(0x308,4,5);
    CTD_TCU5OLINE_B1 = crrcRicoMvb->getBool(0x308,4,6);
    CTD_TCU6OLINE_B1 = crrcRicoMvb->getBool(0x308,4,7);
    CTD_BCU1OLINE_B1 = crrcRicoMvb->getBool(0x308,5,0);
    CTD_BCU2OLINE_B1 = crrcRicoMvb->getBool(0x308,5,1);
    CTD_ACU1OLINE_B1 = crrcRicoMvb->getBool(0x308,5,2);
    CTD_ACU2OLINE_B1 = crrcRicoMvb->getBool(0x308,5,3);
    CTD_ACTOLINE_B1 = crrcRicoMvb->getBool(0x308,5,4);
    CTD_AC2OLINE_B1 = crrcRicoMvb->getBool(0x308,5,5);
    CTD_AC3OLINE_B1 = crrcRicoMvb->getBool(0x308,5,6);
    CTD_AC4OLINE_B1 = crrcRicoMvb->getBool(0x308,5,7);
    CTD_PIS1OLINE_B1 = crrcRicoMvb->getBool(0x308,6,0);
    CTD_PIS2OLINE_B1 = crrcRicoMvb->getBool(0x308,6,1);
    CTD_FCU1OLINE_B1 = crrcRicoMvb->getBool(0x308,6,2);
    CTD_FCU2OLINE_B1 = crrcRicoMvb->getBool(0x308,6,3);
    CTD_EDCU1OLINE_B1 = crrcRicoMvb->getBool(0x308,6,4);
    CTD_EDCU2OLINE_B1 = crrcRicoMvb->getBool(0x308,6,5);
    CTD_EDCU3OLINE_B1 = crrcRicoMvb->getBool(0x308,6,6);
    CTD_EDCU4OLINE_B1 = crrcRicoMvb->getBool(0x308,6,7);
    CTD_EDCU5OLINE_B1 = crrcRicoMvb->getBool(0x308,7,0);
    CTD_EDCU6OLINE_B1 = crrcRicoMvb->getBool(0x308,7,1);
    CTD_EDCU7OLINE_B1 = crrcRicoMvb->getBool(0x308,7,2);
    CTD_EDCU8OLINE_B1 = crrcRicoMvb->getBool(0x308,7,3);
    CTD_AMCTOLINE_B1 = crrcRicoMvb->getBool(0x308,7,4);
    CTD_AMC2OLINE_B1 = crrcRicoMvb->getBool(0x308,7,5);
    CTD_PANOLINE_B1 = crrcRicoMvb->getBool(0x308,7,6);
    CTD_CCU1Active_B1 = crrcRicoMvb->getBool(0x308,7,7);
    CTD_CCU2Active_B1 = crrcRicoMvb->getBool(0x308,8,0);
    CTD_MCTActive_B1 = crrcRicoMvb->getBool(0x308,8,1);
    CTD_MC2Active_B1 = crrcRicoMvb->getBool(0x308,8,2);
    CTD_TractiOLINE_B1 = crrcRicoMvb->getBool(0x308,8,3);
    CTD_Brake_B1 = crrcRicoMvb->getBool(0x308,8,4);
    CTD_FastBrake_B1 = crrcRicoMvb->getBool(0x308,8,5);
    CTD_EmgyBrake_B1 = crrcRicoMvb->getBool(0x308,8,6);
    CTD_Backward_B1 = crrcRicoMvb->getBool(0x308,8,7);
    CTD_Forward_B1 = crrcRicoMvb->getBool(0x308,9,0);
    CTD_FASMute_B1 = crrcRicoMvb->getBool(0x308,9,1);
    CTD_AcDeTestOLINE_B1 = crrcRicoMvb->getBool(0x308,9,2);
    CTD_MCTBg1TrustBCU1_B1 = crrcRicoMvb->getBool(0x30A,8,0);
    CTD_MCTBg1TrustBCU2_B1 = crrcRicoMvb->getBool(0x30A,8,1);
    CTD_MCTBg2TrustBCU1_B1 = crrcRicoMvb->getBool(0x30A,8,2);
    CTD_MCTBg2TrustBCU2_B1 = crrcRicoMvb->getBool(0x30A,8,3);
    CTD_MP1Bg1TrustBCU1_B1 = crrcRicoMvb->getBool(0x30A,8,4);
    CTD_MP1Bg1TrustBCU2_B1 = crrcRicoMvb->getBool(0x30A,8,5);
    CTD_MP1Bg2TrustBCU1_B1 = crrcRicoMvb->getBool(0x30A,8,6);
    CTD_MP1Bg2TrustBCU2_B1 = crrcRicoMvb->getBool(0x30A,8,7);
    CTD_MP2Bg1TrustBCU1_B1 = crrcRicoMvb->getBool(0x30A,9,0);
    CTD_MP2Bg1TrustBCU2_B1 = crrcRicoMvb->getBool(0x30A,9,1);
    CTD_MP2Bg2TrustBCU1_B1 = crrcRicoMvb->getBool(0x30A,9,2);
    CTD_MP2Bg2TrustBCU2_B1 = crrcRicoMvb->getBool(0x30A,9,3);
    CTD_MC2Bg1TrustBCU1_B1 = crrcRicoMvb->getBool(0x30A,9,4);
    CTD_MC2Bg1TrustBCU2_B1 = crrcRicoMvb->getBool(0x30A,9,5);
    CTD_MC2Bg2TrustBCU1_B1 = crrcRicoMvb->getBool(0x30A,9,6);
    CTD_MC2Bg2TrustBCU2_B1 = crrcRicoMvb->getBool(0x30A,9,7);
    CTD_BCU1Trust_B1 = crrcRicoMvb->getBool(0x30A,10,0);
    CTD_BCU2Trust_B1 = crrcRicoMvb->getBool(0x30A,10,1);
    CTD_ATCTrustATCT_B1 = crrcRicoMvb->getBool(0x30A,10,2);
    CTD_ATCTrustATC2_B1 = crrcRicoMvb->getBool(0x30A,10,3);
    CTD_FASTrusFCU1_B1 = crrcRicoMvb->getBool(0x30A,10,4);
    CTD_FASTrusFCU2_B1 = crrcRicoMvb->getBool(0x30A,10,5);
    CTD_PISTrusPIS1_B1 = crrcRicoMvb->getBool(0x30A,10,6);
    CTD_PISTrusPIS2_B1 = crrcRicoMvb->getBool(0x30A,10,7);
    CTD_AccTest40Valid_B1 = crrcRicoMvb->getBool(0x30A,11,0);
    CTD_AccTest80Valid_B1 = crrcRicoMvb->getBool(0x30A,11,1);
    CTD_DccTestValid_B1 = crrcRicoMvb->getBool(0x30A,11,2);
    CTD_MP1WorkShop_B1 = crrcRicoMvb->getBool(0x30A,11,3);
    CTD_MP2WorkShop_B1 = crrcRicoMvb->getBool(0x30A,11,4);

    CTD_LineNum_U8 = crrcRicoMvb->getUnsignedChar(0x308,10);
    CTD_TrainNum_U8 = crrcRicoMvb->getUnsignedChar(0x308,11);
    CTD_Grade_U8 = crrcRicoMvb->getUnsignedChar(0x308,12);
    CTD_DriveMode_U8 = crrcRicoMvb->getUnsignedChar(0x308,13);
    CTD_WheelDig1FedBk_U8 = crrcRicoMvb->getUnsignedChar(0x308,22);
    CTD_WheelDig2FedBk_U8 = crrcRicoMvb->getUnsignedChar(0x308,23);
    CTD_WheelDig3FedBk_U8 = crrcRicoMvb->getUnsignedChar(0x308,24);
    CTD_WheelDig4FedBk_U8 = crrcRicoMvb->getUnsignedChar(0x308,25);
    CTD_CCU1SWVer_U8 = crrcRicoMvb->getUnsignedChar(0x308,26);
    CTD_CCU1MVBVer_U8 = crrcRicoMvb->getUnsignedChar(0x308,27);
    CTD_CCU1SDBVer_U8 = crrcRicoMvb->getUnsignedChar(0x308,28);
    CTD_CCU1VxWorksVer_U8 = crrcRicoMvb->getUnsignedChar(0x308,29);
    CTD_CCU1FPGAVer_U8 = crrcRicoMvb->getUnsignedChar(0x308,30);
    CTD_CCU2SWVer_U8 = crrcRicoMvb->getUnsignedChar(0x308,31);
    CTD_CCU2MVBVer_U8 = crrcRicoMvb->getUnsignedChar(0x309,0);
    CTD_CCU2SDBVer_U8 = crrcRicoMvb->getUnsignedChar(0x309,1);
    CTD_CCU2VxWorksVer_U8 = crrcRicoMvb->getUnsignedChar(0x309,2);
    CTD_CCU2FPGAVer_U8 = crrcRicoMvb->getUnsignedChar(0x309,3);
    CTD_Acc40MCLv_U8 = crrcRicoMvb->getUnsignedChar(0x309,4);
    CTD_Acc80MCLv_U8 = crrcRicoMvb->getUnsignedChar(0x309,5);
    CTD_DeMCLv_U8 = crrcRicoMvb->getUnsignedChar(0x309,16);
    CTD_DeBrkMode_U8 = crrcRicoMvb->getUnsignedChar(0x309,17);
    CTD_MP1PanStatus_U8 = crrcRicoMvb->getUnsignedChar(0x30A,12);
    CTD_MP2PanStatus_U8 = crrcRicoMvb->getUnsignedChar(0x30A,13);

    CTD_TrainLimitSpeed_U16 = crrcRicoMvb->getUnsignedInt(0x308,14);
    CTD_TrainSpeed_U16 = crrcRicoMvb->getUnsignedInt(0x308,16);
    CTD_CatenaryVoltage_U16 = crrcRicoMvb->getUnsignedInt(0x308,18);
    CTD_CatenaryCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x308,20);
    CTD_MCTLoad_U16 = crrcRicoMvb->getUnsignedInt(0x309,18);
    CTD_MP1Load_U16 = crrcRicoMvb->getUnsignedInt(0x309,20);
    CTD_MP2Load_U16 = crrcRicoMvb->getUnsignedInt(0x309,22);
    CTD_MC2Load_U16 = crrcRicoMvb->getUnsignedInt(0x309,24);
    CTD_DeStartVelocity_U16 = crrcRicoMvb->getUnsignedInt(0x309,12);
    CTD_DeDistance_U16 = crrcRicoMvb->getUnsignedInt(0x309,14);

    CTD_AcceleratiOLINE40_I16 = crrcRicoMvb->getSignedInt(0x309,6);
    CTD_AcceleratiOLINE80_I16 = crrcRicoMvb->getSignedInt(0x309,8);
    CTD_DeceleratiOLINE_I16 = crrcRicoMvb->getSignedInt(0x309,10);

    CTD_CurrentStatiOLINE_U32 = crrcRicoMvb->getUnsignedInt32(0x309,26);
    CTD_NextStatiOLINEID_U32 = crrcRicoMvb->getUnsignedInt32(0x30A,0);
    CTD_LastStatiOLINEID_U32 = crrcRicoMvb->getUnsignedInt32(0x30A,4);

    CTD_BMS1OLINE_B1=crrcRicoMvb->getBool(0x308,9,3);
    CTD_BMS2OLINE_B1=crrcRicoMvb->getBool(0x308,9,4);
    CTD_BMS3OLINE_B1=crrcRicoMvb->getBool(0x308,9,5);
    CTD_BMS4OLINE_B1=crrcRicoMvb->getBool(0x308,9,6);

    /**************************************************BCU-CCU*****************************************/
    QList<unsigned short int> temp_virtualports,temp_realports;

    temp_realports<<0x410<<0x411<<0x412<<0x413<<0x414<<0x415<<0x416
                    <<0x420<<0x421<<0x422<<0x423<<0x424<<0x425<<0x426;

    temp_virtualports<<0xf410<<0xf411<<0xf412<<0xf413<<0xf414<<0xf415<<0xf416;

    createBCUList(temp_virtualports,temp_realports);


    B1_1CT_MajorFltMC1Bg1_B1=crrcRicoMvb->getBool(0xf410,7,0);
    B1_2CT_MajorFltMC1Bg1_B1=crrcRicoMvb->getBool(0xf410,8,5);
    B2_1CT_MajorFltMC1Bg1_B1=crrcRicoMvb->getBool(0xf410,11,0);
    B2_2CT_MajorFltMC1Bg1_B1=crrcRicoMvb->getBool(0xf410,12,5);
    B3_1CT_MajorFltMC1Bg1_B1=crrcRicoMvb->getBool(0xf410,15,0);
    B3_2CT_MajorFltMC1Bg1_B1=crrcRicoMvb->getBool(0xf410,16,5);
    B4_1CT_MajorFltMC1Bg1_B1=crrcRicoMvb->getBool(0xf410,19,0);
    B4_2CT_MajorFltMC1Bg1_B1=crrcRicoMvb->getBool(0xf410,20,5);


    BiCT_STRdy_B1 = crrcRicoMvb->getBool(0xf411,1,0);
    BiCT_STBrOff_B1 = crrcRicoMvb->getBool(0xf411,1,1);
    BiCT_STAct_B1 = crrcRicoMvb->getBool(0xf411,1,2);
    BiCT_STOK_B1 = crrcRicoMvb->getBool(0xf411,1,3);
    BiCT_STFail_B1 = crrcRicoMvb->getBool(0xf411,1,4);
    BiCT_STExcd24H_B1 = crrcRicoMvb->getBool(0xf411,1,5);
    BiCT_STExcd26H_B1 = crrcRicoMvb->getBool(0xf411,1,6);
    BiCT_MstrGV_B1 = crrcRicoMvb->getBool(0xf411,1,7);
    BiCT_ASPReady_B1 = crrcRicoMvb->getBool(0xf411,2,0);
    BiCT_ZeroSpd_B1 = crrcRicoMvb->getBool(0xf411,2,1);
    BiCT_EBVActMTOne_B1 = crrcRicoMvb->getBool(0xf411,2,2);
    BiCT_HWBrkCMD_B1 = crrcRicoMvb->getBool(0xf411,2,3);
    BiCT_HWTrakCMD_B1 = crrcRicoMvb->getBool(0xf411,2,4);
    BiCT_HWEmTraCMD_B1 = crrcRicoMvb->getBool(0xf411,2,5);
    BiCT_HWFastBrkCMD_B1 = crrcRicoMvb->getBool(0xf411,2,6);
    BiCT_CANTowingModeActive_B1 = crrcRicoMvb->getBool(0xf411,2,7);
    BiCT_EDCtOffMC1Bg2_B1 = crrcRicoMvb->getBool(0xf411,3,0);
    BiCT_EDCtOffMP1Bg1_B1 = crrcRicoMvb->getBool(0xf411,3,1);
    BiCT_EDCtOffMP1Bg2_B1 = crrcRicoMvb->getBool(0xf411,3,2);
    BiCT_EDCtOffMP2Bg1_B1 = crrcRicoMvb->getBool(0xf411,3,3);
    BiCT_EDCtOffMP2Bg2_B1 = crrcRicoMvb->getBool(0xf411,3,4);
    BiCT_EDCtOffMC2Bg2_B1 = crrcRicoMvb->getBool(0xf411,3,5);
    BiCT_UnitWheelOK_B1 = crrcRicoMvb->getBool(0xf411,3,6);
    BiCT_UnitWheelStt_B1 = crrcRicoMvb->getBool(0xf411,3,7);
    BiCT_SttDiaVldMC1Bg1_B1 = crrcRicoMvb->getBool(0xf411,4,0);
    BiCT_SttDiaVldMC1Bg2_B1 = crrcRicoMvb->getBool(0xf411,4,1);
    BiCT_SttDiaVldMp13Bg1_B1 = crrcRicoMvb->getBool(0xf411,4,2);
    BiCT_SttDiaVldMp13Bg2_B1 = crrcRicoMvb->getBool(0xf411,4,3);
    BiCT_SttDiaVldMP2Bg1_B1 = crrcRicoMvb->getBool(0xf411,4,4);
    BiCT_SttDiaVldMP2Bg2_B1 = crrcRicoMvb->getBool(0xf411,4,5);
    BiCT_SttDiaVldMC2Bg1_B1 = crrcRicoMvb->getBool(0xf411,4,6);
    BiCT_SttDiaVldMC2Bg2_B1 = crrcRicoMvb->getBool(0xf411,4,7);
    BiCT_SlideMC1Bg1_B1 = crrcRicoMvb->getBool(0xf411,5,0);
    BiCT_EBActiveMC1Bg1_B1 = crrcRicoMvb->getBool(0xf411,5,1);
    BiCT_BrkApplyMC1Bg1_B1 = crrcRicoMvb->getBool(0xf411,5,2);
    BiCT_BrkRelMC1Bg1_B1 = crrcRicoMvb->getBool(0xf411,5,3);
    BiCT_LwBSRMC1Bg1_B1 = crrcRicoMvb->getBool(0xf411,5,4);
    BiCT_PBrtRelMC1Bg1_B1 = crrcRicoMvb->getBool(0xf411,5,5);
    BiCT_EPBrkStateMC1Bg1_B1 = crrcRicoMvb->getBool(0xf411,5,6);
    BiCT_MssVldVldMC1Bg1_B1 = crrcRicoMvb->getBool(0xf411,5,7);
    BiCT_SlideMC1Bg2_B1 = crrcRicoMvb->getBool(0xf411,6,0);
    BiCT_EBActiveMC1Bg2_B1 = crrcRicoMvb->getBool(0xf411,6,1);
    BiCT_BrkApplyMC1Bg2_B1 = crrcRicoMvb->getBool(0xf411,6,2);
    BiCT_BrkRelMC1Bg2_B1 = crrcRicoMvb->getBool(0xf411,6,3);
    BiCT_LwBSRMC1Bg2_B1 = crrcRicoMvb->getBool(0xf411,6,4);
    BiCT_EPBrkStateMC1Bg2_B1 = crrcRicoMvb->getBool(0xf411,6,5);
    BiCT_MssVldVldMC1Bg2_B1 = crrcRicoMvb->getBool(0xf411,6,6);
    BiCT_SlideMp1Bg1_B1 = crrcRicoMvb->getBool(0xf411,7,0);
    BiCT_EBActiveMp1Bg1_B1 = crrcRicoMvb->getBool(0xf411,7,1);
    BiCT_BrkApplyMP1Bg1_B1 = crrcRicoMvb->getBool(0xf411,7,2);
    BiCT_BrkRelMP1Bg1_B1 = crrcRicoMvb->getBool(0xf411,7,3);
    BiCT_LwBSRMP1Bg1_B1 = crrcRicoMvb->getBool(0xf411,7,4);
    BiCT_PBrtRelMp1Bg1_B1 = crrcRicoMvb->getBool(0xf411,7,5);
    BiCT_EPBrkStateMP1Bg1_B1 = crrcRicoMvb->getBool(0xf411,7,6);
    BiCT_MssVldVldMP1Bg1_B1 = crrcRicoMvb->getBool(0xf411,7,7);
    BiCT_SlideMP1Bg2_B1 = crrcRicoMvb->getBool(0xf411,8,0);
    BiCT_EBActiveMP1Bg2_B1 = crrcRicoMvb->getBool(0xf411,8,1);
    BiCT_BrkApplyMP1Bg2_B1 = crrcRicoMvb->getBool(0xf411,8,2);
    BiCT_BrkRelMP1Bg2_B1 = crrcRicoMvb->getBool(0xf411,8,3);
    BiCT_LwBSRMP1Bg2_B1 = crrcRicoMvb->getBool(0xf411,8,4);
    BiCT_EPBrkStateMP1Bg2_B1 = crrcRicoMvb->getBool(0xf411,8,5);
    BiCT_MssVldVldMP1Bg2_B1 = crrcRicoMvb->getBool(0xf411,8,6);
    BiCT_SlideMP2Bg1_B1 = crrcRicoMvb->getBool(0xf411,9,0);
    BiCT_EBActiveMP2Bg1_B1 = crrcRicoMvb->getBool(0xf411,9,1);
    BiCT_BrkMP2Bg1_B1 = crrcRicoMvb->getBool(0xf411,9,2);
    BiCT_BrkRelMP2Bg1_B1 = crrcRicoMvb->getBool(0xf411,9,3);
    BiCT_LwBSRMP2Bg1_B1 = crrcRicoMvb->getBool(0xf411,9,4);
    BiCT_PBrtRelMP2Bg1_B1 = crrcRicoMvb->getBool(0xf411,9,5);
    BiCT_EPBrkStateMP2Bg1_B1 = crrcRicoMvb->getBool(0xf411,9,6);
    BiCT_MssVldVldMP2Bg1_B1 = crrcRicoMvb->getBool(0xf411,9,7);
    BiCT_SlideMP2Bg2_B1 = crrcRicoMvb->getBool(0xf411,10,0);
    BiCT_EBActiveMP2Bg2_B1 = crrcRicoMvb->getBool(0xf411,10,1);
    BiCT_BrkMP2Bg2_B1 = crrcRicoMvb->getBool(0xf411,10,2);
    BiCT_BrkRelMP2Bg2_B1 = crrcRicoMvb->getBool(0xf411,10,3);
    BiCT_LwBSRMP2Bg2_B1 = crrcRicoMvb->getBool(0xf411,10,4);
    BiCT_EPBrkStateMP2Bg2_B1 = crrcRicoMvb->getBool(0xf411,10,5);
    BiCT_MssVldVldMP2Bg2_B1 = crrcRicoMvb->getBool(0xf411,10,6);
    BiCT_SlideMC2Bg1_B1 = crrcRicoMvb->getBool(0xf411,11,0);
    BiCT_EBActiveMC2Bg1_B1 = crrcRicoMvb->getBool(0xf411,11,1);
    BiCT_BrkApplyMC2Bg1_B1 = crrcRicoMvb->getBool(0xf411,11,2);
    BiCT_BrkRelMC2Bg1_B1 = crrcRicoMvb->getBool(0xf411,11,3);
    BiCT_LwBSRMC2Bg1_B1 = crrcRicoMvb->getBool(0xf411,11,4);
    BiCT_PBrtRelMC2Bg1_B1 = crrcRicoMvb->getBool(0xf411,11,5);
    BiCT_EPBrkStateMC2Bg1_B1 = crrcRicoMvb->getBool(0xf411,11,6);
    BiCT_MssVldVldMC2Bg1_B1 = crrcRicoMvb->getBool(0xf411,11,7);
    BiCT_SlideMC2Bg2_B1 = crrcRicoMvb->getBool(0xf411,12,0);
    BiCT_EBActiveMC2Bg2_B1 = crrcRicoMvb->getBool(0xf411,12,1);
    BiCT_BrkApplyMC2Bg2_B1 = crrcRicoMvb->getBool(0xf411,12,2);
    BiCT_BrkRelMC2Bg2_B1 = crrcRicoMvb->getBool(0xf411,12,3);
    BiCT_LwBSRMC2Bg2_B1 = crrcRicoMvb->getBool(0xf411,12,4);
    BiCT_EPBrkStateMC2Bg2_B1 = crrcRicoMvb->getBool(0xf411,12,5);
    BiCT_MssVldVldMC2Bg2_B1 = crrcRicoMvb->getBool(0xf411,12,6);
    BiCT_HWHalfFullServiceBrakeStatus_B1 = crrcRicoMvb->getBool(0xf411,30,0);
    BiCT_Odometer100m_B1 = crrcRicoMvb->getBool(0xf411,30,1);
    BiCT_BACPVldMC1Bg1_B1 = crrcRicoMvb->getBool(0xf413,30,0);
    BiCT_BCPVldMC1Bg1_B1 = crrcRicoMvb->getBool(0xf413,30,1);
    BiCT_ASPVldMC1Bg1_B1 = crrcRicoMvb->getBool(0xf413,30,2);
    BiCT_BPMC1VldBg1_B1 = crrcRicoMvb->getBool(0xf413,30,3);
    BiCT_BACPVldMC1Bg2_B1 = crrcRicoMvb->getBool(0xf413,30,5);
    BiCT_BCPVldMC1Bg2_B1 = crrcRicoMvb->getBool(0xf413,30,6);
    BiCT_ASPVldMC1Bg2_B1 = crrcRicoMvb->getBool(0xf413,30,7);
    BiCT_PBPVldMC1_B1 = crrcRicoMvb->getBool(0xf413,31,0);
    BiCT_SpdVldMC1Axl1_B1 = crrcRicoMvb->getBool(0xf413,31,2);
    BiCT_SpdVldMC1Axl2_B1 = crrcRicoMvb->getBool(0xf413,31,3);
    BiCT_SpdVldMC1Axl3_B1 = crrcRicoMvb->getBool(0xf413,31,4);
    BiCT_SpdVldMC1Axl4_B1 = crrcRicoMvb->getBool(0xf413,31,5);
    BiCT_BACPVldMP1Bg1_B1 = crrcRicoMvb->getBool(0xf414,30,0);
    BiCT_BCPVldMP1Bg1_B1 = crrcRicoMvb->getBool(0xf414,30,1);
    BiCT_ASPVldMP1Bg1_B1 = crrcRicoMvb->getBool(0xf414,30,2);
    BiCT_MRPVldMP1_B1 = crrcRicoMvb->getBool(0xf414,30,3);
    BiCT_BACPVldMP1Bg2_B1 = crrcRicoMvb->getBool(0xf414,30,5);
    BiCT_BCPVldMP1Bg2_B1 = crrcRicoMvb->getBool(0xf414,30,6);
    BiCT_ASPVldMP1Bg2_B1 = crrcRicoMvb->getBool(0xf414,30,7);
    BiCT_PBPVldMP1_B1 = crrcRicoMvb->getBool(0xf414,31,0);
    BiCT_SpdVldMP1Axl1_B1 = crrcRicoMvb->getBool(0xf414,31,2);
    BiCT_SpdVldMP1Axl2_B1 = crrcRicoMvb->getBool(0xf414,31,3);
    BiCT_SpdVldMP1Axl3_B1 = crrcRicoMvb->getBool(0xf414,31,4);
    BiCT_SpdVldMP1Axl4_B1 = crrcRicoMvb->getBool(0xf414,31,5);
    BiCT_BACPVldMP2Bg1_B1 = crrcRicoMvb->getBool(0xf415,30,0);
    BiCT_BCPVldMP2Bg1_B1 = crrcRicoMvb->getBool(0xf415,30,1);
    BiCT_ASPVldMP2Bg1_B1 = crrcRicoMvb->getBool(0xf415,30,2);
    BiCT_MRPVldMP2_B1 = crrcRicoMvb->getBool(0xf415,30,3);
    BiCT_BACPVldMP2Bg2_B1 = crrcRicoMvb->getBool(0xf415,30,5);
    BiCT_BCPVldMP2Bg2_B1 = crrcRicoMvb->getBool(0xf415,30,6);
    BiCT_ASPVldMP2Bg2_B1 = crrcRicoMvb->getBool(0xf415,30,7);
    BiCT_PBPVldMP2_B1 = crrcRicoMvb->getBool(0xf415,31,0);
    BiCT_SpdVldMP2Axl1_B1 = crrcRicoMvb->getBool(0xf415,31,2);
    BiCT_SpdVldMP2Axl2_B1 = crrcRicoMvb->getBool(0xf415,31,3);
    BiCT_SpdVldMP2Axl3_B1 = crrcRicoMvb->getBool(0xf415,31,4);
    BiCT_SpdVldMP2Axl4_B1 = crrcRicoMvb->getBool(0xf415,31,5);
    BiCT_BACPVldMC2Bg1_B1 = crrcRicoMvb->getBool(0xf416,30,0);
    BiCT_BCPVldMC2Bg1_B1 = crrcRicoMvb->getBool(0xf416,30,1);
    BiCT_ASPVldMC2Bg1_B1 = crrcRicoMvb->getBool(0xf416,30,2);
    BiCT_BPVldMC2Bg1_B1 = crrcRicoMvb->getBool(0xf416,30,3);
    BiCT_BACPVldMC2Bg2_B1 = crrcRicoMvb->getBool(0xf416,30,5);
    BiCT_BCPVldMC2Bg2_B1 = crrcRicoMvb->getBool(0xf416,30,6);
    BiCT_ASPVldMC2Bg2_B1 = crrcRicoMvb->getBool(0xf416,30,7);
    BiCT_PBPVldMC2_B1 = crrcRicoMvb->getBool(0xf416,31,0);
    BiCT_SpdVldMC2Axl1_B1 = crrcRicoMvb->getBool(0xf416,31,2);
    BiCT_SpdVldMC2Axl2_B1 = crrcRicoMvb->getBool(0xf416,31,3);
    BiCT_SpdVldMC2Axl3_B1 = crrcRicoMvb->getBool(0xf416,31,4);
    BiCT_SpdVldMC2Axl4_B1 = crrcRicoMvb->getBool(0xf416,31,5);

    BiCT_MssMC1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf411,14);
    BiCT_MssMC1Bg2_I16 = crrcRicoMvb->getSignedInt(0xf411,16);
    BiCT_MssMP1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf411,18);
    BiCT_MssMP1Bg2_I16 = crrcRicoMvb->getSignedInt(0xf411,20);
    BiCT_MssMP2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf411,22);
    BiCT_MssMP2Bg2_I16 = crrcRicoMvb->getSignedInt(0xf411,24);
    BiCT_MssMC2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf411,26);
    BiCT_MssMC2Bg2_I16 = crrcRicoMvb->getSignedInt(0xf411,28);
    BiCT_EPPossMC1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf412,0);
    BiCT_EPPossMC1Bg2_I16 = crrcRicoMvb->getSignedInt(0xf412,2);
    BiCT_EPPossMP1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf412,4);
    BiCT_EPPossMP1Bg2_I16 = crrcRicoMvb->getSignedInt(0xf412,6);
    BiCT_EPPossMP2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf412,8);
    BiCT_EPPossMP2Bg2_I16 = crrcRicoMvb->getSignedInt(0xf412,10);
    BiCT_EPPossMC2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf412,12);
    BiCT_EPPossMC2Bg2_I16 = crrcRicoMvb->getSignedInt(0xf412,14);
    BiCT_BACPMC1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf413,0);
    BiCT_BCPMC1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf413,2);
    BiCT_ASPMC1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf413,4);
    BiCT_BPMC1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf413,6);
    BiCT_BACPMC1Bg2_I16 = crrcRicoMvb->getSignedInt(0xf413,10);
    BiCT_BCPMC1Bg2_I16 = crrcRicoMvb->getSignedInt(0xf413,12);
    BiCT_ASPMC1Bg2_I16 = crrcRicoMvb->getSignedInt(0xf413,14);
    BiCT_PBPMC1_I16 = crrcRicoMvb->getSignedInt(0xf413,16);
    BiCT_SpdMC1Axl1_I16 = crrcRicoMvb->getSignedInt(0xf413,20);
    BiCT_SpdMC1Axl2_I16 = crrcRicoMvb->getSignedInt(0xf413,22);
    BiCT_SpdMC1Axl3_I16 = crrcRicoMvb->getSignedInt(0xf413,24);
    BiCT_SpdMC1Axl4_I16 = crrcRicoMvb->getSignedInt(0xf413,26);
    BiCT_BACPMP1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf414,0);
    BiCT_BCPMP1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf414,2);
    BiCT_ASPMP1Bg1_I16 = crrcRicoMvb->getSignedInt(0xf414,4);
    BiCT_MRPMP1_I16 = crrcRicoMvb->getSignedInt(0xf414,6);
    BiCT_BACPMP1Bg2_I16 = crrcRicoMvb->getSignedInt(0xf414,10);
    BiCT_BCPMP1Bg2_I16 = crrcRicoMvb->getSignedInt(0xf414,12);
    BiCT_ASPMP1Bg2_I16 = crrcRicoMvb->getSignedInt(0xf414,14);
    BiCT_PBPMP1_I16 = crrcRicoMvb->getSignedInt(0xf414,16);
    BiCT_SpdMP1Axl1_I16 = crrcRicoMvb->getSignedInt(0xf414,20);
    BiCT_SpdMP1Axl2_I16 = crrcRicoMvb->getSignedInt(0xf414,22);
    BiCT_SpdMP1Axl3_I16 = crrcRicoMvb->getSignedInt(0xf414,24);
    BiCT_SpdMP1Axl4_I16 = crrcRicoMvb->getSignedInt(0xf414,26);
    BiCT_BACPMP2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf415,0);
    BiCT_BCPMP2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf415,2);
    BiCT_ASPMP2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf415,4);
    BiCT_MRPMP2_I16 = crrcRicoMvb->getSignedInt(0xf415,6);
    BiCT_BACPMP2Bg2_I16 = crrcRicoMvb->getSignedInt(0xf415,10);
    BiCT_BCPMP2Bg2_I16 = crrcRicoMvb->getSignedInt(0xf415,12);
    BiCT_ASPMP2Bg2_I16 = crrcRicoMvb->getSignedInt(0xf415,14);
    BiCT_PBPMP2_I16 = crrcRicoMvb->getSignedInt(0xf415,16);
    BiCT_SpdMP2Axl1_I16 = crrcRicoMvb->getSignedInt(0xf415,20);
    BiCT_SpdMP2Axl2_I16 = crrcRicoMvb->getSignedInt(0xf415,22);
    BiCT_SpdMP2Axl3_I16 = crrcRicoMvb->getSignedInt(0xf415,24);
    BiCT_SpdMP2Axl4_I16 = crrcRicoMvb->getSignedInt(0xf415,26);
    BiCT_BACPMC2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf416,0);
    BiCT_BCPMC2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf416,2);
    BiCT_ASPMC2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf416,4);
    BiCT_BPMC2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf416,6);
    BiCT_BACPMC2Bg2_I16 = crrcRicoMvb->getSignedInt(0xf416,10);
    BiCT_BCPMC2Bg2_I16 = crrcRicoMvb->getSignedInt(0xf416,12);
    BiCT_ASPMC2Bg2_I16 = crrcRicoMvb->getSignedInt(0xf416,14);
    BiCT_PBPMC2Bg1_I16 = crrcRicoMvb->getSignedInt(0xf416,16);
    BiCT_SpdMC2Axl1_I16 = crrcRicoMvb->getSignedInt(0xf416,20);
    BiCT_SpdMC2Axl2_I16 = crrcRicoMvb->getSignedInt(0xf416,22);
    BiCT_SpdMC2Axl3_I16 = crrcRicoMvb->getSignedInt(0xf416,24);
    BiCT_SpdMC2Axl4_I16 = crrcRicoMvb->getSignedInt(0xf416,26);


    temp_virtualports.clear();
    temp_realports.clear();

    //****************************************TCU-CCU********************************//


    TCU1CT_IxForwardSts_B1 = crrcRicoMvb->getBool(0x510,2,0);
    TCU1CT_IxReverseSts_B1 = crrcRicoMvb->getBool(0x510,2,1);
    TCU1CT_IxTractionSts_B1 = crrcRicoMvb->getBool(0x510,2,2);
    TCU1CT_IxBrakeSts_B1 = crrcRicoMvb->getBool(0x510,2,3);
    TCU1CT_IxMtrCmbSpdVld_B1 = crrcRicoMvb->getBool(0x510,2,6);
    TCU1CT_IxEDBUseable_B1 = crrcRicoMvb->getBool(0x510,3,0);
    TCU1CT_IxEDBVld_B1 = crrcRicoMvb->getBool(0x510,3,1);
    TCU1CT_IxAntiSlideVldBit_B1 = crrcRicoMvb->getBool(0x510,3,2);
    TCU1CT_IxSlip_B1 = crrcRicoMvb->getBool(0x510,3,3);
    TCU1CT_IxEDBFadeOut_B1 = crrcRicoMvb->getBool(0x510,3,4);
    TCU1CT_IxEDBSlide_B1 = crrcRicoMvb->getBool(0x510,3,5);
    TCU1CT_IxChargeCntCmd_B1 = crrcRicoMvb->getBool(0x510,4,0);
    TCU1CT_IxChargeCntSts_B1 = crrcRicoMvb->getBool(0x510,4,1);
    TCU1CT_IxShortCntCmd_B1 = crrcRicoMvb->getBool(0x510,4,2);
    TCU1CT_IxShortCntSts_B1 = crrcRicoMvb->getBool(0x510,4,3);
    TCU1CT_IxInvONOFF_B1 = crrcRicoMvb->getBool(0x510,5,0);
    TCU1CT_IxVVVFSts_B1 = crrcRicoMvb->getBool(0x510,5,1);
    TCU1CT_IxSlide_B1 = crrcRicoMvb->getBool(0x510,5,3);
    TCU1CT_IxWDSetOK_B1 = crrcRicoMvb->getBool(0x510,5,4);
    TCU1CT_IxHSCBPermit_B1 = crrcRicoMvb->getBool(0x510,5,6);
    TCU1CT_IxHSCBSts_B1 = crrcRicoMvb->getBool(0x510,5,7);
    TCU1CT_IxPtgDownWr_B1 = crrcRicoMvb->getBool(0x510,6,0);
    TCU1CT_Ix0BrkRlsWr_B1 = crrcRicoMvb->getBool(0x510,6,1);
    TCU1CT_Ix100EmgTrcWr_B1 = crrcRicoMvb->getBool(0x510,6,2);
    TCU1CT_IxBrkRstFanCntSts_B1 = crrcRicoMvb->getBool(0x510,6,6);
    TCU1CT_IxBrkRstFanStartCmd_B1 = crrcRicoMvb->getBool(0x510,6,7);
    TCU1CT_IxForwardWr_B1 = crrcRicoMvb->getBool(0x510,7,0);
    TCU1CT_IxReverseWr_B1 = crrcRicoMvb->getBool(0x510,7,1);
    TCU1CT_IxTractionWr_B1 = crrcRicoMvb->getBool(0x510,7,2);
    TCU1CT_IxBrakeWr_B1 = crrcRicoMvb->getBool(0x510,7,3);
    TCU1CT_IxEmgTrcWr_B1 = crrcRicoMvb->getBool(0x510,7,4);
    TCU1CT_IxEBWr_B1 = crrcRicoMvb->getBool(0x510,7,5);
    TCU1CT_IxFBWr_B1 = crrcRicoMvb->getBool(0x510,7,6);
    TCU1CT_IxResetWr_B1 = crrcRicoMvb->getBool(0x510,7,7);
    TCU1CT_IxRgnBrkCnsPls_B1 = crrcRicoMvb->getBool(0x512,15,0);
    TCU1CT_IxTrcCnsPls_B1 = crrcRicoMvb->getBool(0x512,15,1);
    TCU1CT_EDBSlide_B1 = crrcRicoMvb->getBool(0x513,2,0);
    TCU1CT_EDBUseable_B1 = crrcRicoMvb->getBool(0x513,2,1);
    TCU1CT_EDBVld_B1 = crrcRicoMvb->getBool(0x513,2,2);
    TCU1CT_EDBFadeOut_B1 = crrcRicoMvb->getBool(0x513,2,3);
    TCU2CT_IxForwardSts_B1 = crrcRicoMvb->getBool(0x520,2,0);
    TCU2CT_IxReverseSts_B1 = crrcRicoMvb->getBool(0x520,2,1);
    TCU2CT_IxTractionSts_B1 = crrcRicoMvb->getBool(0x520,2,2);
    TCU2CT_IxBrakeSts_B1 = crrcRicoMvb->getBool(0x520,2,3);
    TCU2CT_IxMtrCmbSpdVld_B1 = crrcRicoMvb->getBool(0x520,2,6);
    TCU2CT_IxEDBUseable_B1 = crrcRicoMvb->getBool(0x520,3,0);
    TCU2CT_IxEDBVld_B1 = crrcRicoMvb->getBool(0x520,3,1);
    TCU2CT_IxAntiSlideVldBit_B1 = crrcRicoMvb->getBool(0x520,3,2);
    TCU2CT_IxSlip_B1 = crrcRicoMvb->getBool(0x520,3,3);
    TCU2CT_IxEDBFadeOut_B1 = crrcRicoMvb->getBool(0x520,3,4);
    TCU2CT_IxEDBSlide_B1 = crrcRicoMvb->getBool(0x520,3,5);
    TCU2CT_IxChargeCntCmd_B1 = crrcRicoMvb->getBool(0x520,4,0);
    TCU2CT_IxChargeCntSts_B1 = crrcRicoMvb->getBool(0x520,4,1);
    TCU2CT_IxShortCntCmd_B1 = crrcRicoMvb->getBool(0x520,4,2);
    TCU2CT_IxShortCntSts_B1 = crrcRicoMvb->getBool(0x520,4,3);
    TCU2CT_IxInvONOFF_B1 = crrcRicoMvb->getBool(0x520,5,0);
    TCU2CT_IxVVVFSts_B1 = crrcRicoMvb->getBool(0x520,5,1);
    TCU2CT_IxSlide_B1 = crrcRicoMvb->getBool(0x520,5,3);
    TCU2CT_IxWDSetOK_B1 = crrcRicoMvb->getBool(0x520,5,4);
    TCU2CT_IxHSCBPermit_B1 = crrcRicoMvb->getBool(0x520,5,6);
    TCU2CT_IxHSCBSts_B1 = crrcRicoMvb->getBool(0x520,5,7);
    TCU2CT_IxPtgDownWr_B1 = crrcRicoMvb->getBool(0x520,6,0);
    TCU2CT_Ix0BrkRlsWr_B1 = crrcRicoMvb->getBool(0x520,6,1);
    TCU2CT_Ix100EmgTrcWr_B1 = crrcRicoMvb->getBool(0x520,6,2);
    TCU2CT_IxBrkRstFanCntSts_B1 = crrcRicoMvb->getBool(0x520,6,6);
    TCU2CT_IxBrkRstFanStartCmd_B1 = crrcRicoMvb->getBool(0x520,6,7);
    TCU2CT_IxForwardWr_B1 = crrcRicoMvb->getBool(0x520,7,0);
    TCU2CT_IxReverseWr_B1 = crrcRicoMvb->getBool(0x520,7,1);
    TCU2CT_IxTractionWr_B1 = crrcRicoMvb->getBool(0x520,7,2);
    TCU2CT_IxBrakeWr_B1 = crrcRicoMvb->getBool(0x520,7,3);
    TCU2CT_IxEmgTrcWr_B1 = crrcRicoMvb->getBool(0x520,7,4);
    TCU2CT_IxEBWr_B1 = crrcRicoMvb->getBool(0x520,7,5);
    TCU2CT_IxFBWr_B1 = crrcRicoMvb->getBool(0x520,7,6);
    TCU2CT_IxResetWr_B1 = crrcRicoMvb->getBool(0x520,7,7);
    TCU2CT_IxRgnBrkCnsPls_B1 = crrcRicoMvb->getBool(0x522,15,0);
    TCU2CT_IxTrcCnsPls_B1 = crrcRicoMvb->getBool(0x522,15,1);
    TCU2CT_EDBSlide_B1 = crrcRicoMvb->getBool(0x523,2,0);
    TCU2CT_EDBUseable_B1 = crrcRicoMvb->getBool(0x523,2,1);
    TCU2CT_EDBVld_B1 = crrcRicoMvb->getBool(0x523,2,2);
    TCU2CT_EDBFadeOut_B1 = crrcRicoMvb->getBool(0x523,2,3);
    TCU3CT_IxForwardSts_B1 = crrcRicoMvb->getBool(0x530,2,0);
    TCU3CT_IxReverseSts_B1 = crrcRicoMvb->getBool(0x530,2,1);
    TCU3CT_IxTractionSts_B1 = crrcRicoMvb->getBool(0x530,2,2);
    TCU3CT_IxBrakeSts_B1 = crrcRicoMvb->getBool(0x530,2,3);
    TCU3CT_IxMtrCmbSpdVld_B1 = crrcRicoMvb->getBool(0x530,2,6);
    TCU3CT_IxEDBUseable_B1 = crrcRicoMvb->getBool(0x530,3,0);
    TCU3CT_IxEDBVld_B1 = crrcRicoMvb->getBool(0x530,3,1);
    TCU3CT_IxAntiSlideVldBit_B1 = crrcRicoMvb->getBool(0x530,3,2);
    TCU3CT_IxSlip_B1 = crrcRicoMvb->getBool(0x530,3,3);
    TCU3CT_IxEDBFadeOut_B1 = crrcRicoMvb->getBool(0x530,3,4);
    TCU3CT_IxEDBSlide_B1 = crrcRicoMvb->getBool(0x530,3,5);
    TCU3CT_IxChargeCntCmd_B1 = crrcRicoMvb->getBool(0x530,4,0);
    TCU3CT_IxChargeCntSts_B1 = crrcRicoMvb->getBool(0x530,4,1);
    TCU3CT_IxShortCntCmd_B1 = crrcRicoMvb->getBool(0x530,4,2);
    TCU3CT_IxShortCntSts_B1 = crrcRicoMvb->getBool(0x530,4,3);
    TCU3CT_IxInvONOFF_B1 = crrcRicoMvb->getBool(0x530,5,0);
    TCU3CT_IxVVVFSts_B1 = crrcRicoMvb->getBool(0x530,5,1);
    TCU3CT_IxSlide_B1 = crrcRicoMvb->getBool(0x530,5,3);
    TCU3CT_IxWDSetOK_B1 = crrcRicoMvb->getBool(0x530,5,4);
    TCU3CT_IxHSCBPermit_B1 = crrcRicoMvb->getBool(0x530,5,6);
    TCU3CT_IxHSCBSts_B1 = crrcRicoMvb->getBool(0x530,5,7);
    TCU3CT_IxPtgDownWr_B1 = crrcRicoMvb->getBool(0x530,6,0);
    TCU3CT_Ix0BrkRlsWr_B1 = crrcRicoMvb->getBool(0x530,6,1);
    TCU3CT_Ix100EmgTrcWr_B1 = crrcRicoMvb->getBool(0x530,6,2);
    TCU3CT_IxBrkRstFanCntSts_B1 = crrcRicoMvb->getBool(0x530,6,6);
    TCU3CT_IxBrkRstFanStartCmd_B1 = crrcRicoMvb->getBool(0x530,6,7);
    TCU3CT_IxForwardWr_B1 = crrcRicoMvb->getBool(0x530,7,0);
    TCU3CT_IxReverseWr_B1 = crrcRicoMvb->getBool(0x530,7,1);
    TCU3CT_IxTractionWr_B1 = crrcRicoMvb->getBool(0x530,7,2);
    TCU3CT_IxBrakeWr_B1 = crrcRicoMvb->getBool(0x530,7,3);
    TCU3CT_IxEmgTrcWr_B1 = crrcRicoMvb->getBool(0x530,7,4);
    TCU3CT_IxEBWr_B1 = crrcRicoMvb->getBool(0x530,7,5);
    TCU3CT_IxFBWr_B1 = crrcRicoMvb->getBool(0x530,7,6);
    TCU3CT_IxResetWr_B1 = crrcRicoMvb->getBool(0x530,7,7);
    TCU3CT_IxRgnBrkCnsPls_B1 = crrcRicoMvb->getBool(0x532,15,0);
    TCU3CT_IxTrcCnsPls_B1 = crrcRicoMvb->getBool(0x532,15,1);
    TCU3CT_EDBSlide_B1 = crrcRicoMvb->getBool(0x533,2,0);
    TCU3CT_EDBUseable_B1 = crrcRicoMvb->getBool(0x533,2,1);
    TCU3CT_EDBVld_B1 = crrcRicoMvb->getBool(0x533,2,2);
    TCU3CT_EDBFadeOut_B1 = crrcRicoMvb->getBool(0x533,2,3);
    TCU4CT_IxForwardSts_B1 = crrcRicoMvb->getBool(0x540,2,0);
    TCU4CT_IxReverseSts_B1 = crrcRicoMvb->getBool(0x540,2,1);
    TCU4CT_IxTractionSts_B1 = crrcRicoMvb->getBool(0x540,2,2);
    TCU4CT_IxBrakeSts_B1 = crrcRicoMvb->getBool(0x540,2,3);
    TCU4CT_IxMtrCmbSpdVld_B1 = crrcRicoMvb->getBool(0x540,2,6);
    TCU4CT_IxEDBUseable_B1 = crrcRicoMvb->getBool(0x540,3,0);
    TCU4CT_IxEDBVld_B1 = crrcRicoMvb->getBool(0x540,3,1);
    TCU4CT_IxAntiSlideVldBit_B1 = crrcRicoMvb->getBool(0x540,3,2);
    TCU4CT_IxSlip_B1 = crrcRicoMvb->getBool(0x540,3,3);
    TCU4CT_IxEDBFadeOut_B1 = crrcRicoMvb->getBool(0x540,3,4);
    TCU4CT_IxEDBSlide_B1 = crrcRicoMvb->getBool(0x540,3,5);
    TCU4CT_IxChargeCntCmd_B1 = crrcRicoMvb->getBool(0x540,4,0);
    TCU4CT_IxChargeCntSts_B1 = crrcRicoMvb->getBool(0x540,4,1);
    TCU4CT_IxShortCntCmd_B1 = crrcRicoMvb->getBool(0x540,4,2);
    TCU4CT_IxShortCntSts_B1 = crrcRicoMvb->getBool(0x540,4,3);
    TCU4CT_IxInvONOFF_B1 = crrcRicoMvb->getBool(0x540,5,0);
    TCU4CT_IxVVVFSts_B1 = crrcRicoMvb->getBool(0x540,5,1);
    TCU4CT_IxSlide_B1 = crrcRicoMvb->getBool(0x540,5,3);
    TCU4CT_IxWDSetOK_B1 = crrcRicoMvb->getBool(0x540,5,4);
    TCU4CT_IxHSCBPermit_B1 = crrcRicoMvb->getBool(0x540,5,6);
    TCU4CT_IxHSCBSts_B1 = crrcRicoMvb->getBool(0x540,5,7);
    TCU4CT_IxPtgDownWr_B1 = crrcRicoMvb->getBool(0x540,6,0);
    TCU4CT_Ix0BrkRlsWr_B1 = crrcRicoMvb->getBool(0x540,6,1);
    TCU4CT_Ix100EmgTrcWr_B1 = crrcRicoMvb->getBool(0x540,6,2);
    TCU4CT_IxBrkRstFanCntSts_B1 = crrcRicoMvb->getBool(0x540,6,6);
    TCU4CT_IxBrkRstFanStartCmd_B1 = crrcRicoMvb->getBool(0x540,6,7);
    TCU4CT_IxForwardWr_B1 = crrcRicoMvb->getBool(0x540,7,0);
    TCU4CT_IxReverseWr_B1 = crrcRicoMvb->getBool(0x540,7,1);
    TCU4CT_IxTractionWr_B1 = crrcRicoMvb->getBool(0x540,7,2);
    TCU4CT_IxBrakeWr_B1 = crrcRicoMvb->getBool(0x540,7,3);
    TCU4CT_IxEmgTrcWr_B1 = crrcRicoMvb->getBool(0x540,7,4);
    TCU4CT_IxEBWr_B1 = crrcRicoMvb->getBool(0x540,7,5);
    TCU4CT_IxFBWr_B1 = crrcRicoMvb->getBool(0x540,7,6);
    TCU4CT_IxResetWr_B1 = crrcRicoMvb->getBool(0x540,7,7);
    TCU4CT_IxRgnBrkCnsPls_B1 = crrcRicoMvb->getBool(0x542,15,0);
    TCU4CT_IxTrcCnsPls_B1 = crrcRicoMvb->getBool(0x542,15,1);
    TCU4CT_EDBSlide_B1 = crrcRicoMvb->getBool(0x543,2,0);
    TCU4CT_EDBUseable_B1 = crrcRicoMvb->getBool(0x543,2,1);
    TCU4CT_EDBVld_B1 = crrcRicoMvb->getBool(0x543,2,2);
    TCU4CT_EDBFadeOut_B1 = crrcRicoMvb->getBool(0x543,2,3);
    TCU5CT_IxForwardSts_B1 = crrcRicoMvb->getBool(0x550,2,0);
    TCU5CT_IxReverseSts_B1 = crrcRicoMvb->getBool(0x550,2,1);
    TCU5CT_IxTractionSts_B1 = crrcRicoMvb->getBool(0x550,2,2);
    TCU5CT_IxBrakeSts_B1 = crrcRicoMvb->getBool(0x550,2,3);
    TCU5CT_IxMtrCmbSpdVld_B1 = crrcRicoMvb->getBool(0x550,2,6);
    TCU5CT_IxEDBUseable_B1 = crrcRicoMvb->getBool(0x550,3,0);
    TCU5CT_IxEDBVld_B1 = crrcRicoMvb->getBool(0x550,3,1);
    TCU5CT_IxAntiSlideVldBit_B1 = crrcRicoMvb->getBool(0x550,3,2);
    TCU5CT_IxSlip_B1 = crrcRicoMvb->getBool(0x550,3,3);
    TCU5CT_IxEDBFadeOut_B1 = crrcRicoMvb->getBool(0x550,3,4);
    TCU5CT_IxEDBSlide_B1 = crrcRicoMvb->getBool(0x550,3,5);
    TCU5CT_IxChargeCntCmd_B1 = crrcRicoMvb->getBool(0x550,4,0);
    TCU5CT_IxChargeCntSts_B1 = crrcRicoMvb->getBool(0x550,4,1);
    TCU5CT_IxShortCntCmd_B1 = crrcRicoMvb->getBool(0x550,4,2);
    TCU5CT_IxShortCntSts_B1 = crrcRicoMvb->getBool(0x550,4,3);
    TCU5CT_IxInvONOFF_B1 = crrcRicoMvb->getBool(0x550,5,0);
    TCU5CT_IxVVVFSts_B1 = crrcRicoMvb->getBool(0x550,5,1);
    TCU5CT_IxSlide_B1 = crrcRicoMvb->getBool(0x550,5,3);
    TCU5CT_IxWDSetOK_B1 = crrcRicoMvb->getBool(0x550,5,4);
    TCU5CT_IxHSCBPermit_B1 = crrcRicoMvb->getBool(0x550,5,6);
    TCU5CT_IxHSCBSts_B1 = crrcRicoMvb->getBool(0x550,5,7);
    TCU5CT_IxPtgDownWr_B1 = crrcRicoMvb->getBool(0x550,6,0);
    TCU5CT_Ix0BrkRlsWr_B1 = crrcRicoMvb->getBool(0x550,6,1);
    TCU5CT_Ix100EmgTrcWr_B1 = crrcRicoMvb->getBool(0x550,6,2);
    TCU5CT_IxBrkRstFanCntSts_B1 = crrcRicoMvb->getBool(0x550,6,6);
    TCU5CT_IxBrkRstFanStartCmd_B1 = crrcRicoMvb->getBool(0x550,6,7);
    TCU5CT_IxForwardWr_B1 = crrcRicoMvb->getBool(0x550,7,0);
    TCU5CT_IxReverseWr_B1 = crrcRicoMvb->getBool(0x550,7,1);
    TCU5CT_IxTractionWr_B1 = crrcRicoMvb->getBool(0x550,7,2);
    TCU5CT_IxBrakeWr_B1 = crrcRicoMvb->getBool(0x550,7,3);
    TCU5CT_IxEmgTrcWr_B1 = crrcRicoMvb->getBool(0x550,7,4);
    TCU5CT_IxEBWr_B1 = crrcRicoMvb->getBool(0x550,7,5);
    TCU5CT_IxFBWr_B1 = crrcRicoMvb->getBool(0x550,7,6);
    TCU5CT_IxResetWr_B1 = crrcRicoMvb->getBool(0x550,7,7);
    TCU5CT_IxRgnBrkCnsPls_B1 = crrcRicoMvb->getBool(0x552,15,0);
    TCU5CT_IxTrcCnsPls_B1 = crrcRicoMvb->getBool(0x552,15,1);
    TCU5CT_EDBSlide_B1 = crrcRicoMvb->getBool(0x553,2,0);
    TCU5CT_EDBUseable_B1 = crrcRicoMvb->getBool(0x553,2,1);
    TCU5CT_EDBVld_B1 = crrcRicoMvb->getBool(0x553,2,2);
    TCU5CT_EDBFadeOut_B1 = crrcRicoMvb->getBool(0x553,2,3);
    TCU6CT_IxForwardSts_B1 = crrcRicoMvb->getBool(0x560,2,0);
    TCU6CT_IxReverseSts_B1 = crrcRicoMvb->getBool(0x560,2,1);
    TCU6CT_IxTractionSts_B1 = crrcRicoMvb->getBool(0x560,2,2);
    TCU6CT_IxBrakeSts_B1 = crrcRicoMvb->getBool(0x560,2,3);
    TCU6CT_IxMtrCmbSpdVld_B1 = crrcRicoMvb->getBool(0x560,2,6);
    TCU6CT_IxEDBUseable_B1 = crrcRicoMvb->getBool(0x560,3,0);
    TCU6CT_IxEDBVld_B1 = crrcRicoMvb->getBool(0x560,3,1);
    TCU6CT_IxAntiSlideVldBit_B1 = crrcRicoMvb->getBool(0x560,3,2);
    TCU6CT_IxSlip_B1 = crrcRicoMvb->getBool(0x560,3,3);
    TCU6CT_IxEDBFadeOut_B1 = crrcRicoMvb->getBool(0x560,3,4);
    TCU6CT_IxEDBSlide_B1 = crrcRicoMvb->getBool(0x560,3,5);
    TCU6CT_IxChargeCntCmd_B1 = crrcRicoMvb->getBool(0x560,4,0);
    TCU6CT_IxChargeCntSts_B1 = crrcRicoMvb->getBool(0x560,4,1);
    TCU6CT_IxShortCntCmd_B1 = crrcRicoMvb->getBool(0x560,4,2);
    TCU6CT_IxShortCntSts_B1 = crrcRicoMvb->getBool(0x560,4,3);
    TCU6CT_IxInvONOFF_B1 = crrcRicoMvb->getBool(0x560,5,0);
    TCU6CT_IxVVVFSts_B1 = crrcRicoMvb->getBool(0x560,5,1);
    TCU6CT_IxSlide_B1 = crrcRicoMvb->getBool(0x560,5,3);
    TCU6CT_IxWDSetOK_B1 = crrcRicoMvb->getBool(0x560,5,4);
    TCU6CT_IxHSCBPermit_B1 = crrcRicoMvb->getBool(0x560,5,6);
    TCU6CT_IxHSCBSts_B1 = crrcRicoMvb->getBool(0x560,5,7);
    TCU6CT_IxPtgDownWr_B1 = crrcRicoMvb->getBool(0x560,6,0);
    TCU6CT_Ix0BrkRlsWr_B1 = crrcRicoMvb->getBool(0x560,6,1);
    TCU6CT_Ix100EmgTrcWr_B1 = crrcRicoMvb->getBool(0x560,6,2);
    TCU6CT_IxBrkRstFanCntSts_B1 = crrcRicoMvb->getBool(0x560,6,6);
    TCU6CT_IxBrkRstFanStartCmd_B1 = crrcRicoMvb->getBool(0x560,6,7);
    TCU6CT_IxForwardWr_B1 = crrcRicoMvb->getBool(0x560,7,0);
    TCU6CT_IxReverseWr_B1 = crrcRicoMvb->getBool(0x560,7,1);
    TCU6CT_IxTractionWr_B1 = crrcRicoMvb->getBool(0x560,7,2);
    TCU6CT_IxBrakeWr_B1 = crrcRicoMvb->getBool(0x560,7,3);
    TCU6CT_IxEmgTrcWr_B1 = crrcRicoMvb->getBool(0x560,7,4);
    TCU6CT_IxEBWr_B1 = crrcRicoMvb->getBool(0x560,7,5);
    TCU6CT_IxFBWr_B1 = crrcRicoMvb->getBool(0x560,7,6);
    TCU6CT_IxResetWr_B1 = crrcRicoMvb->getBool(0x560,7,7);
    TCU6CT_IxRgnBrkCnsPls_B1 = crrcRicoMvb->getBool(0x562,15,0);
    TCU6CT_IxTrcCnsPls_B1 = crrcRicoMvb->getBool(0x562,15,1);
    TCU6CT_EDBSlide_B1 = crrcRicoMvb->getBool(0x563,2,0);
    TCU6CT_EDBUseable_B1 = crrcRicoMvb->getBool(0x563,2,1);
    TCU6CT_EDBVld_B1 = crrcRicoMvb->getBool(0x563,2,2);
    TCU6CT_EDBFadeOut_B1 = crrcRicoMvb->getBool(0x563,2,3);

    TCU1CT_IxDCUMajorFlt_B1= crrcRicoMvb->getBool(0x511,10,7);
    TCU2CT_IxDCUMajorFlt_B1= crrcRicoMvb->getBool(0x521,10,7);
    TCU3CT_IxDCUMajorFlt_B1= crrcRicoMvb->getBool(0x531,10,7);
    TCU4CT_IxDCUMajorFlt_B1= crrcRicoMvb->getBool(0x541,10,7);
    TCU5CT_IxDCUMajorFlt_B1= crrcRicoMvb->getBool(0x551,10,7);
    TCU6CT_IxDCUMajorFlt_B1= crrcRicoMvb->getBool(0x561,10,7);


    TCU1CT_IuiDCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x510,0);
    TCU1CT_IuiEDBAbility_U16 = crrcRicoMvb->getUnsignedInt(0x510,8);
    TCU1CT_IuiEDBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x510,10);
    TCU1CT_IuiTrcEffortLcl_U16 = crrcRicoMvb->getUnsignedInt(0x510,12);
    TCU1CT_IuiInverterCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x510,20);
    TCU1CT_IuiMotorCmbSpeed_U16 = crrcRicoMvb->getUnsignedInt(0x510,22);
    TCU1CT_IuiMtr1Spd_U16 = crrcRicoMvb->getUnsignedInt(0x510,24);
    TCU1CT_IuiMtr2Spd_U16 = crrcRicoMvb->getUnsignedInt(0x510,26);
    TCU1CT_CHOPTIME_U16 = crrcRicoMvb->getUnsignedInt(0x510,28);
    TCU1CT_WHEELDIAM_U16 = crrcRicoMvb->getUnsignedInt(0x510,30);
    TCU1CT_IuiCalTBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x511,12);
    TCU1CT_BRCV_U16 = crrcRicoMvb->getUnsignedInt(0x511,14);
    TCU1CT_IuiMtr1Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x512,0);
    TCU1CT_IuiMtr2Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x512,2);
    TCU1CT_IuiLglSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x512,8);
    TCU1CT_IuiInvSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x512,10);
    TCU1CT_IuiAdhSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x512,12);
    TCU1CT_DCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x513,0);
    TCU1CT_EDBPoss_U16 = crrcRicoMvb->getUnsignedInt(0x513,4);
    TCU1CT_EDBAch_U16 = crrcRicoMvb->getUnsignedInt(0x513,6);
    TCU2CT_IuiDCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x520,0);
    TCU2CT_IuiEDBAbility_U16 = crrcRicoMvb->getUnsignedInt(0x520,8);
    TCU2CT_IuiEDBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x520,10);
    TCU2CT_IuiTrcEffortLcl_U16 = crrcRicoMvb->getUnsignedInt(0x520,12);
    TCU2CT_IuiInverterCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x520,20);
    TCU2CT_IuiMotorCmbSpeed_U16 = crrcRicoMvb->getUnsignedInt(0x520,22);
    TCU2CT_IuiMtr1Spd_U16 = crrcRicoMvb->getUnsignedInt(0x520,24);
    TCU2CT_IuiMtr2Spd_U16 = crrcRicoMvb->getUnsignedInt(0x520,26);
    TCU2CT_CHOPTIME_U16 = crrcRicoMvb->getUnsignedInt(0x520,28);
    TCU2CT_WHEELDIAM_U16 = crrcRicoMvb->getUnsignedInt(0x520,30);
    TCU2CT_IuiCalTBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x521,12);
    TCU2CT_BRCV_U16 = crrcRicoMvb->getUnsignedInt(0x511,14);
    TCU2CT_IuiMtr1Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x522,0);
    TCU2CT_IuiMtr2Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x522,2);
    TCU2CT_IuiLglSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x522,8);
    TCU2CT_IuiInvSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x522,10);
    TCU2CT_IuiAdhSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x522,12);
    TCU2CT_DCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x523,0);
    TCU2CT_EDBPoss_U16 = crrcRicoMvb->getUnsignedInt(0x523,4);
    TCU2CT_EDBAch_U16 = crrcRicoMvb->getUnsignedInt(0x523,6);
    TCU3CT_IuiDCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x530,0);
    TCU3CT_IuiEDBAbility_U16 = crrcRicoMvb->getUnsignedInt(0x530,8);
    TCU3CT_IuiEDBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x530,10);
    TCU3CT_IuiTrcEffortLcl_U16 = crrcRicoMvb->getUnsignedInt(0x530,12);
    TCU3CT_IuiInverterCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x530,20);
    TCU3CT_IuiMotorCmbSpeed_U16 = crrcRicoMvb->getUnsignedInt(0x530,22);
    TCU3CT_IuiMtr1Spd_U16 = crrcRicoMvb->getUnsignedInt(0x530,24);
    TCU3CT_IuiMtr2Spd_U16 = crrcRicoMvb->getUnsignedInt(0x530,26);
    TCU3CT_CHOPTIME_U16 = crrcRicoMvb->getUnsignedInt(0x530,28);
    TCU3CT_WHEELDIAM_U16 = crrcRicoMvb->getUnsignedInt(0x530,30);
    TCU3CT_IuiCalTBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x531,12);
    TCU1CT_BRCV_U16 = crrcRicoMvb->getUnsignedInt(0x511,14);
    TCU3CT_IuiMtr1Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x532,0);
    TCU3CT_IuiMtr2Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x532,2);
    TCU3CT_IuiLglSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x532,8);
    TCU3CT_IuiInvSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x532,10);
    TCU3CT_IuiAdhSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x532,12);
    TCU3CT_DCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x533,0);
    TCU3CT_EDBPoss_U16 = crrcRicoMvb->getUnsignedInt(0x533,4);
    TCU3CT_EDBAch_U16 = crrcRicoMvb->getUnsignedInt(0x533,6);
    TCU4CT_IuiDCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x540,0);
    TCU4CT_IuiEDBAbility_U16 = crrcRicoMvb->getUnsignedInt(0x540,8);
    TCU4CT_IuiEDBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x540,10);
    TCU4CT_IuiTrcEffortLcl_U16 = crrcRicoMvb->getUnsignedInt(0x540,12);
    TCU4CT_IuiInverterCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x540,20);
    TCU4CT_IuiMotorCmbSpeed_U16 = crrcRicoMvb->getUnsignedInt(0x540,22);
    TCU4CT_IuiMtr1Spd_U16 = crrcRicoMvb->getUnsignedInt(0x540,24);
    TCU4CT_IuiMtr2Spd_U16 = crrcRicoMvb->getUnsignedInt(0x540,26);
    TCU4CT_CHOPTIME_U16 = crrcRicoMvb->getUnsignedInt(0x540,28);
    TCU4CT_WHEELDIAM_U16 = crrcRicoMvb->getUnsignedInt(0x540,30);
    TCU4CT_IuiCalTBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x541,12);
    TCU4CT_BRCV_U16 = crrcRicoMvb->getUnsignedInt(0x511,14);
    TCU4CT_IuiMtr1Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x542,0);
    TCU4CT_IuiMtr2Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x542,2);
    TCU4CT_IuiLglSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x542,8);
    TCU4CT_IuiInvSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x542,10);
    TCU4CT_IuiAdhSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x542,12);
    TCU4CT_DCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x543,0);
    TCU4CT_EDBPoss_U16 = crrcRicoMvb->getUnsignedInt(0x543,4);
    TCU4CT_EDBAch_U16 = crrcRicoMvb->getUnsignedInt(0x543,6);
    TCU5CT_IuiDCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x550,0);
    TCU5CT_IuiEDBAbility_U16 = crrcRicoMvb->getUnsignedInt(0x550,8);
    TCU5CT_IuiEDBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x550,10);
    TCU5CT_IuiTrcEffortLcl_U16 = crrcRicoMvb->getUnsignedInt(0x550,12);
    TCU5CT_IuiInverterCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x550,20);
    TCU5CT_IuiMotorCmbSpeed_U16 = crrcRicoMvb->getUnsignedInt(0x550,22);
    TCU5CT_IuiMtr1Spd_U16 = crrcRicoMvb->getUnsignedInt(0x550,24);
    TCU5CT_IuiMtr2Spd_U16 = crrcRicoMvb->getUnsignedInt(0x550,26);
    TCU5CT_CHOPTIME_U16 = crrcRicoMvb->getUnsignedInt(0x550,28);
    TCU5CT_WHEELDIAM_U16 = crrcRicoMvb->getUnsignedInt(0x550,30);
    TCU5CT_IuiCalTBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x551,12);
    TCU5CT_BRCV_U16 = crrcRicoMvb->getUnsignedInt(0x511,14);
    TCU5CT_IuiMtr1Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x552,0);
    TCU5CT_IuiMtr2Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x552,2);
    TCU5CT_IuiLglSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x552,8);
    TCU5CT_IuiInvSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x552,10);
    TCU5CT_IuiAdhSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x552,12);
    TCU5CT_DCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x553,0);
    TCU5CT_EDBPoss_U16 = crrcRicoMvb->getUnsignedInt(0x553,4);
    TCU5CT_EDBAch_U16 = crrcRicoMvb->getUnsignedInt(0x553,6);
    TCU6CT_IuiDCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x560,0);
    TCU6CT_IuiEDBAbility_U16 = crrcRicoMvb->getUnsignedInt(0x560,8);
    TCU6CT_IuiEDBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x560,10);
    TCU6CT_IuiTrcEffortLcl_U16 = crrcRicoMvb->getUnsignedInt(0x560,12);
    TCU6CT_IuiInverterCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x560,20);
    TCU6CT_IuiMotorCmbSpeed_U16 = crrcRicoMvb->getUnsignedInt(0x560,22);
    TCU6CT_IuiMtr1Spd_U16 = crrcRicoMvb->getUnsignedInt(0x560,24);
    TCU6CT_IuiMtr2Spd_U16 = crrcRicoMvb->getUnsignedInt(0x560,26);
    TCU6CT_CHOPTIME_U16 = crrcRicoMvb->getUnsignedInt(0x560,28);
    TCU6CT_WHEELDIAM_U16 = crrcRicoMvb->getUnsignedInt(0x560,30);
    TCU6CT_IuiCalTBEffort_U16 = crrcRicoMvb->getUnsignedInt(0x561,12);
    TCU6CT_BRCV_U16 = crrcRicoMvb->getUnsignedInt(0x511,14);
    TCU6CT_IuiMtr1Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x562,0);
    TCU6CT_IuiMtr2Tmp_U16 = crrcRicoMvb->getUnsignedInt(0x562,2);
    TCU6CT_IuiLglSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x562,8);
    TCU6CT_IuiInvSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x562,10);
    TCU6CT_IuiAdhSWRevision_U16 = crrcRicoMvb->getUnsignedInt(0x562,12);
    TCU6CT_DCUAlive_U16 = crrcRicoMvb->getUnsignedInt(0x563,0);
    TCU6CT_EDBPoss_U16 = crrcRicoMvb->getUnsignedInt(0x563,4);
    TCU6CT_EDBAch_U16 = crrcRicoMvb->getUnsignedInt(0x563,6);

    TCU1CT_IiPowerGrdVoltage_I16 = crrcRicoMvb->getSignedInt(0x510,14);
    TCU1CT_IiMiddleVoltage_I16 = crrcRicoMvb->getSignedInt(0x510,16);
    TCU1CT_IiMiddleCurrent_I16 = crrcRicoMvb->getSignedInt(0x510,18);
    TCU2CT_IiPowerGrdVoltage_I16 = crrcRicoMvb->getSignedInt(0x520,14);
    TCU2CT_IiMiddleVoltage_I16 = crrcRicoMvb->getSignedInt(0x520,16);
    TCU2CT_IiMiddleCurrent_I16 = crrcRicoMvb->getSignedInt(0x520,18);
    TCU3CT_IiPowerGrdVoltage_I16 = crrcRicoMvb->getSignedInt(0x530,14);
    TCU3CT_IiMiddleVoltage_I16 = crrcRicoMvb->getSignedInt(0x530,16);
    TCU3CT_IiMiddleCurrent_I16 = crrcRicoMvb->getSignedInt(0x530,18);
    TCU4CT_IiPowerGrdVoltage_I16 = crrcRicoMvb->getSignedInt(0x540,14);
    TCU4CT_IiMiddleVoltage_I16 = crrcRicoMvb->getSignedInt(0x540,16);
    TCU4CT_IiMiddleCurrent_I16 = crrcRicoMvb->getSignedInt(0x540,18);
    TCU5CT_IiPowerGrdVoltage_I16 = crrcRicoMvb->getSignedInt(0x550,14);
    TCU5CT_IiMiddleVoltage_I16 = crrcRicoMvb->getSignedInt(0x550,16);
    TCU5CT_IiMiddleCurrent_I16 = crrcRicoMvb->getSignedInt(0x550,18);
    TCU6CT_IiPowerGrdVoltage_I16 = crrcRicoMvb->getSignedInt(0x550,14);
    TCU6CT_IiMiddleVoltage_I16 = crrcRicoMvb->getSignedInt(0x550,16);
    TCU6CT_IiMiddleCurrent_I16 = crrcRicoMvb->getSignedInt(0x550,18);\



    TCU1CT_IxMotoISO=crrcRicoMvb->getBool(0x511,11,6);
    TCU2CT_IxMotoISO=crrcRicoMvb->getBool(0x521,11,6);
    TCU3CT_IxMotoISO=crrcRicoMvb->getBool(0x531,11,6);
    TCU4CT_IxMotoISO=crrcRicoMvb->getBool(0x541,11,6);
    TCU5CT_IxMotoISO=crrcRicoMvb->getBool(0x551,11,6);
    TCU6CT_IxMotoISO=crrcRicoMvb->getBool(0x561,11,6);



    ACU1CT_IxBBOC_B1 = crrcRicoMvb->getBool(0x610,14,1);
    ACU1CT_IxKM1S_B1 = crrcRicoMvb->getBool(0x610,14,2);
    ACU1CT_IxKM2S_B1 = crrcRicoMvb->getBool(0x610,14,3);
    ACU1CT_IxA1OS_B1 = crrcRicoMvb->getBool(0x610,14,4);
    ACU1CT_IxKMAS_B1 = crrcRicoMvb->getBool(0x610,14,5);
    ACU1CT_IxFANS_B1 = crrcRicoMvb->getBool(0x610,14,6);
    ACU1CT_IxDBPS_B1 = crrcRicoMvb->getBool(0x610,14,7);
    ACU1CT_IxBOOV_B1 = crrcRicoMvb->getBool(0x610,15,0);
    ACU1CT_IxBOLV_B1 = crrcRicoMvb->getBool(0x610,15,1);
    ACU1CT_IxBILV_B1 = crrcRicoMvb->getBool(0x610,15,2);
    ACU1CT_IxBIOV_B1 = crrcRicoMvb->getBool(0x610,15,3);
    ACU1CT_IxBOOC_B1 = crrcRicoMvb->getBool(0x610,15,4);
    ACU1CT_IxBGDU_B1 = crrcRicoMvb->getBool(0x610,15,5);
    ACU1CT_IxBGOH_B1 = crrcRicoMvb->getBool(0x610,15,6);
    ACU1CT_IxBKMF_B1 = crrcRicoMvb->getBool(0x610,15,7);
    ACU1CT_IxChgMinorF_B1 = crrcRicoMvb->getBool(0x610,16,0);
    ACU1CT_IxChgMediumF_B1 = crrcRicoMvb->getBool(0x610,16,1);
    ACU1CT_IxChgMajorF_B1 = crrcRicoMvb->getBool(0x610,16,2);
    ACU1CT_IxSIVMinorF_B1 = crrcRicoMvb->getBool(0x610,16,3);
    ACU1CT_IxSIVMediumF_B1 = crrcRicoMvb->getBool(0x610,16,4);
    ACU1CT_IxSIVMajorF_B1 = crrcRicoMvb->getBool(0x610,16,5);
    ACU1CT_IxQF11S_B1 = crrcRicoMvb->getBool(0x610,16,6);
    ACU1CT_IxBGOS_B1 = crrcRicoMvb->getBool(0x610,16,7);
    ACU1CT_IxRest_B1 = crrcRicoMvb->getBool(0x610,17,0);
    ACU1CT_IxSIVOFFWire_B1 = crrcRicoMvb->getBool(0x610,17,1);
    ACU1CT_IxSIVStus_B1 = crrcRicoMvb->getBool(0x610,17,2);
    ACU1CT_IxK12S_B1 = crrcRicoMvb->getBool(0x610,17,3);
    ACU1CT_IxK13S_B1 = crrcRicoMvb->getBool(0x610,17,4);
    ACU1CT_IxSIVCnsPls_B1 = crrcRicoMvb->getBool(0x610,17,7);
    ACU1CT_IxK13C_B1 = crrcRicoMvb->getBool(0x610,18,0);
    ACU1CT_IxKM11ChrgC_B1 = crrcRicoMvb->getBool(0x610,18,1);
    ACU1CT_IxChgCnsPls_B1 = crrcRicoMvb->getBool(0x610,18,2);
    ACU1CT_IxBtyLowTmpAlm_B1 = crrcRicoMvb->getBool(0x610,18,4);
    ACU1CT_IxBtyOverTmpAlm_B1 = crrcRicoMvb->getBool(0x610,18,5);
    ACU1CT_IxBtyUVltgYellowAlm_B1 = crrcRicoMvb->getBool(0x610,18,6);
    ACU1CT_IxBtyUVltgRedAlm_B1 = crrcRicoMvb->getBool(0x610,18,7);
    ACU1CT_IxDCOK_B1 = crrcRicoMvb->getBool(0x610,19,0);
    ACU1CT_IxKM11S_B1 = crrcRicoMvb->getBool(0x610,19,1);
    ACU1CT_IxKM1C_B1 = crrcRicoMvb->getBool(0x610,19,2);
    ACU1CT_IxKM2C_B1 = crrcRicoMvb->getBool(0x610,19,3);
    ACU1CT_IxKMAC_B1 = crrcRicoMvb->getBool(0x610,19,5);
    ACU1CT_IxSIVOK_B1 = crrcRicoMvb->getBool(0x610,19,6);
    ACU1CT_IxK12C_B1 = crrcRicoMvb->getBool(0x610,19,7);
    ACU2CT_IxBBOC_B1 = crrcRicoMvb->getBool(0x620,14,1);
    ACU2CT_IxKM1S_B1 = crrcRicoMvb->getBool(0x620,14,2);
    ACU2CT_IxKM2S_B1 = crrcRicoMvb->getBool(0x620,14,3);
    ACU2CT_IxA1OS_B1 = crrcRicoMvb->getBool(0x620,14,4);
    ACU2CT_IxKMAS_B1 = crrcRicoMvb->getBool(0x620,14,5);
    ACU2CT_IxFANS_B1 = crrcRicoMvb->getBool(0x620,14,6);
    ACU2CT_IxDBPS_B1 = crrcRicoMvb->getBool(0x620,14,7);
    ACU2CT_IxBOOV_B1 = crrcRicoMvb->getBool(0x620,15,0);
    ACU2CT_IxBOLV_B1 = crrcRicoMvb->getBool(0x620,15,1);
    ACU2CT_IxBILV_B1 = crrcRicoMvb->getBool(0x620,15,2);
    ACU2CT_IxBIOV_B1 = crrcRicoMvb->getBool(0x620,15,3);
    ACU2CT_IxBOOC_B1 = crrcRicoMvb->getBool(0x620,15,4);
    ACU2CT_IxBGDU_B1 = crrcRicoMvb->getBool(0x620,15,5);
    ACU2CT_IxBGOH_B1 = crrcRicoMvb->getBool(0x620,15,6);
    ACU2CT_IxBKMF_B1 = crrcRicoMvb->getBool(0x620,15,7);
    ACU2CT_IxChgMinorF_B1 = crrcRicoMvb->getBool(0x620,16,0);
    ACU2CT_IxChgMediumF_B1 = crrcRicoMvb->getBool(0x620,16,1);
    ACU2CT_IxChgMajorF_B1 = crrcRicoMvb->getBool(0x620,16,2);
    ACU2CT_IxSIVMinorF_B1 = crrcRicoMvb->getBool(0x620,16,3);
    ACU2CT_IxSIVMediumF_B1 = crrcRicoMvb->getBool(0x620,16,4);
    ACU2CT_IxSIVMajorF_B1 = crrcRicoMvb->getBool(0x620,16,5);
    ACU2CT_IxQF11S_B1 = crrcRicoMvb->getBool(0x620,16,6);
    ACU2CT_IxBGOS_B1 = crrcRicoMvb->getBool(0x620,16,7);
    ACU2CT_IxRest_B1 = crrcRicoMvb->getBool(0x620,17,0);
    ACU2CT_IxSIVOFFWire_B1 = crrcRicoMvb->getBool(0x620,17,1);
    ACU2CT_IxSIVStus_B1 = crrcRicoMvb->getBool(0x620,17,2);
    ACU2CT_IxK12S_B1 = crrcRicoMvb->getBool(0x620,17,3);
    ACU2CT_IxK13S_B1 = crrcRicoMvb->getBool(0x620,17,4);
    ACU2CT_IxSIVCnsPls_B1 = crrcRicoMvb->getBool(0x620,17,7);
    ACU2CT_IxK13C_B1 = crrcRicoMvb->getBool(0x620,18,0);
    ACU2CT_IxKM11ChrgC_B1 = crrcRicoMvb->getBool(0x620,18,1);
    ACU2CT_IxChgCnsPls_B1 = crrcRicoMvb->getBool(0x620,18,2);
    ACU2CT_IxBtyLowTmpAlm_B1 = crrcRicoMvb->getBool(0x620,18,4);
    ACU2CT_IxBtyOverTmpAlm_B1 = crrcRicoMvb->getBool(0x620,18,5);
    ACU2CT_IxBtyUVltgYellowAlm_B1 = crrcRicoMvb->getBool(0x620,18,6);
    ACU2CT_IxBtyUVltgRedAlm_B1 = crrcRicoMvb->getBool(0x620,18,7);
    ACU2CT_IxDCOK_B1 = crrcRicoMvb->getBool(0x620,19,0);
    ACU2CT_IxKM11S_B1 = crrcRicoMvb->getBool(0x620,19,1);
    ACU2CT_IxKM1C_B1 = crrcRicoMvb->getBool(0x620,19,2);
    ACU2CT_IxKM2C_B1 = crrcRicoMvb->getBool(0x620,19,3);
    ACU2CT_IxKMAC_B1 = crrcRicoMvb->getBool(0x620,19,5);
    ACU2CT_IxSIVOK_B1 = crrcRicoMvb->getBool(0x620,19,6);
    ACU2CT_IxK12C_B1 = crrcRicoMvb->getBool(0x620,19,7);

    ACU1CT_IuiACEAlive_U16 = crrcRicoMvb->getUnsignedInt(0x610,0);
    ACU1CT_IuiDSPRevision_U16 = crrcRicoMvb->getUnsignedInt(0x610,2);
    ACU1CT_IuiPPCRevision_U16 = crrcRicoMvb->getUnsignedInt(0x610,4);
    ACU1CT_IuiBtyVltg_U16 = crrcRicoMvb->getUnsignedInt(0x610,6);
    ACU1CT_IiBtyTmp_I16 = crrcRicoMvb->getUnsignedInt(0x610,8);
    ACU1CT_IuiLInptVltg_U16 = crrcRicoMvb->getUnsignedInt(0x610,20);
    ACU1CT_IuiInvOptVltg_U16 = crrcRicoMvb->getUnsignedInt(0x610,22);
    ACU1CT_IuiInvInptCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x610,26);
    ACU1CT_UWCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x610,28);

    ACU2CT_IuiACEAlive_U16 = crrcRicoMvb->getUnsignedInt(0x620,0);
    ACU2CT_IuiDSPRevision_U16 = crrcRicoMvb->getUnsignedInt(0x620,2);
    ACU2CT_IuiPPCRevision_U16 = crrcRicoMvb->getUnsignedInt(0x620,4);
    ACU2CT_IuiBtyVltg_U16 = crrcRicoMvb->getUnsignedInt(0x620,6);
    ACU2CT_IiBtyTmp_I16 = crrcRicoMvb->getUnsignedInt(0x620,8);
    ACU2CT_IuiLInptVltg_U16 = crrcRicoMvb->getUnsignedInt(0x620,20);
    ACU2CT_IuiInvOptVltg_U16 = crrcRicoMvb->getUnsignedInt(0x620,22);
    ACU2CT_IuiInvInptCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x620,26);
    ACU2CT_UWCurrent_U16 = crrcRicoMvb->getUnsignedInt(0x620,28);
    ACU1CT_IiBtyChgCurrent_I16 = crrcRicoMvb->getSignedInt(0x610,24);
    ACU2CT_IiBtyChgCurrent_I16 = crrcRicoMvb->getSignedInt(0x620,24);



    //************************************************EDCU1_2-CCU******************************************//
    temp_virtualports<<0xf710<<0xf711<<0xf712;
    temp_realports<<0x710<<0x711<<0x712<<0x720<<0x721<<0x722;
    createEDCUList(this->CTD_EDCU1OLINE_B1,this->CTD_EDCU2OLINE_B1,temp_virtualports,temp_realports);

    EDCU1_2CT_DOOR159_B1 = crrcRicoMvb->getBool(0xf711,2,0);
    EDCU1_2CT_DOOR160_B1 = crrcRicoMvb->getBool(0xf711,2,1);
    EDCU1_2CT_DOOR161_B1 = crrcRicoMvb->getBool(0xf711,2,2);
    EDCU1_2CT_DOOR162_B1 = crrcRicoMvb->getBool(0xf711,2,3);
    EDCU1_2CT_DOOR163_B1 = crrcRicoMvb->getBool(0xf711,2,4);
    EDCU1_2CT_DOOR164_B1 = crrcRicoMvb->getBool(0xf711,2,5);
    EDCU1_2CT_DOOR165_B1 = crrcRicoMvb->getBool(0xf711,2,6);
    EDCU1_2CT_DOOR166_B1 = crrcRicoMvb->getBool(0xf711,2,7);
    EDCU1_2CT_DOOR167_B1 = crrcRicoMvb->getBool(0xf711,3,0);
    EDCU1_2CT_DOOR168_B1 = crrcRicoMvb->getBool(0xf711,3,1);
    EDCU1_2CT_DOOR169_B1 = crrcRicoMvb->getBool(0xf711,3,2);
    EDCU1_2CT_DOOR170_B1 = crrcRicoMvb->getBool(0xf711,3,3);
    EDCU1_2CT_DOOR171_B1 = crrcRicoMvb->getBool(0xf711,3,4);
    EDCU1_2CT_DOOR172_B1 = crrcRicoMvb->getBool(0xf711,3,5);
    EDCU1_2CT_DOOR173_B1 = crrcRicoMvb->getBool(0xf711,3,6);
    EDCU1_2CT_DOOR174_B1 = crrcRicoMvb->getBool(0xf711,3,7);
    EDCU1_2CT_DOOR175_B1 = crrcRicoMvb->getBool(0xf711,4,0);
    EDCU1_2CT_DOOR176_B1 = crrcRicoMvb->getBool(0xf711,4,1);
    EDCU1_2CT_DOOR177_B1 = crrcRicoMvb->getBool(0xf711,4,2);
    EDCU1_2CT_DOOR178_B1 = crrcRicoMvb->getBool(0xf711,4,3);
    EDCU1_2CT_DOOR179_B1 = crrcRicoMvb->getBool(0xf711,4,4);
    EDCU1_2CT_DOOR180_B1 = crrcRicoMvb->getBool(0xf711,4,5);
    EDCU1_2CT_DOOR181_B1 = crrcRicoMvb->getBool(0xf711,4,6);
    EDCU1_2CT_DOOR182_B1 = crrcRicoMvb->getBool(0xf711,4,7);
    EDCU1_2CT_DOOR183_B1 = crrcRicoMvb->getBool(0xf711,5,0);
    EDCU1_2CT_DOOR184_B1 = crrcRicoMvb->getBool(0xf711,5,1);
    EDCU1_2CT_DOOR185_B1 = crrcRicoMvb->getBool(0xf711,5,2);
    EDCU1_2CT_DOOR186_B1 = crrcRicoMvb->getBool(0xf711,5,3);
    EDCU1_2CT_DOOR187_B1 = crrcRicoMvb->getBool(0xf711,5,4);
    EDCU1_2CT_DOOR188_B1 = crrcRicoMvb->getBool(0xf711,5,5);
    EDCU1_2CT_DOOR189_B1 = crrcRicoMvb->getBool(0xf711,5,6);
    EDCU1_2CT_DOOR190_B1 = crrcRicoMvb->getBool(0xf711,5,7);
    EDCU1_2CT_DOOR191_B1 = crrcRicoMvb->getBool(0xf711,6,0);
    EDCU1_2CT_DOOR192_B1 = crrcRicoMvb->getBool(0xf711,6,1);
    EDCU1_2CT_DOOR193_B1 = crrcRicoMvb->getBool(0xf711,6,2);
    EDCU1_2CT_DOOR194_B1 = crrcRicoMvb->getBool(0xf711,6,3);
    EDCU1_2CT_DOOR195_B1 = crrcRicoMvb->getBool(0xf711,6,4);
    EDCU1_2CT_DOOR196_B1 = crrcRicoMvb->getBool(0xf711,6,5);
    EDCU1_2CT_DOOR197_B1 = crrcRicoMvb->getBool(0xf711,6,6);
    EDCU1_2CT_DOOR198_B1 = crrcRicoMvb->getBool(0xf711,6,7);
    EDCU1_2CT_DOOR199_B1 = crrcRicoMvb->getBool(0xf711,7,0);
    EDCU1_2CT_DOOR200_B1 = crrcRicoMvb->getBool(0xf711,7,1);
    EDCU1_2CT_DOOR201_B1 = crrcRicoMvb->getBool(0xf711,7,2);
    EDCU1_2CT_DOOR202_B1 = crrcRicoMvb->getBool(0xf711,7,3);
    EDCU1_2CT_DOOR203_B1 = crrcRicoMvb->getBool(0xf711,7,4);
    EDCU1_2CT_DOOR204_B1 = crrcRicoMvb->getBool(0xf711,7,5);
    EDCU1_2CT_DOOR205_B1 = crrcRicoMvb->getBool(0xf711,7,6);
    EDCU1_2CT_DOOR206_B1 = crrcRicoMvb->getBool(0xf711,7,7);
    EDCU1_2CT_DOOR207_B1 = crrcRicoMvb->getBool(0xf711,8,0);
    EDCU1_2CT_DOOR208_B1 = crrcRicoMvb->getBool(0xf711,8,1);
    EDCU1_2CT_DOOR209_B1 = crrcRicoMvb->getBool(0xf711,8,2);
    EDCU1_2CT_DOOR210_B1 = crrcRicoMvb->getBool(0xf711,8,3);
    EDCU1_2CT_DOOR211_B1 = crrcRicoMvb->getBool(0xf711,8,4);
    EDCU1_2CT_DOOR212_B1 = crrcRicoMvb->getBool(0xf711,8,5);
    EDCU1_2CT_DOOR213_B1 = crrcRicoMvb->getBool(0xf711,8,6);
    EDCU1_2CT_DOOR214_B1 = crrcRicoMvb->getBool(0xf711,8,7);
    EDCU1_2CT_DOOR215_B1 = crrcRicoMvb->getBool(0xf711,9,0);
    EDCU1_2CT_DOOR216_B1 = crrcRicoMvb->getBool(0xf711,9,1);
    EDCU1_2CT_DOOR217_B1 = crrcRicoMvb->getBool(0xf711,9,2);
    EDCU1_2CT_DOOR218_B1 = crrcRicoMvb->getBool(0xf711,9,3);
    EDCU1_2CT_DOOR219_B1 = crrcRicoMvb->getBool(0xf711,9,4);
    EDCU1_2CT_DOOR220_B1 = crrcRicoMvb->getBool(0xf711,9,5);
    EDCU1_2CT_DOOR221_B1 = crrcRicoMvb->getBool(0xf711,9,6);
    EDCU1_2CT_DOOR222_B1 = crrcRicoMvb->getBool(0xf711,9,7);
    EDCU1_2CT_DOOR223_B1 = crrcRicoMvb->getBool(0xf711,10,0);
    EDCU1_2CT_DOOR224_B1 = crrcRicoMvb->getBool(0xf711,10,1);
    EDCU1_2CT_DOOR225_B1 = crrcRicoMvb->getBool(0xf711,10,2);
    EDCU1_2CT_DOOR226_B1 = crrcRicoMvb->getBool(0xf711,10,3);
    EDCU1_2CT_DOOR227_B1 = crrcRicoMvb->getBool(0xf711,10,4);
    EDCU1_2CT_DOOR228_B1 = crrcRicoMvb->getBool(0xf711,10,5);
    EDCU1_2CT_DOOR229_B1 = crrcRicoMvb->getBool(0xf711,10,6);
    EDCU1_2CT_DOOR230_B1 = crrcRicoMvb->getBool(0xf711,10,7);
    EDCU1_2CT_DOOR231_B1 = crrcRicoMvb->getBool(0xf711,11,0);
    EDCU1_2CT_DOOR232_B1 = crrcRicoMvb->getBool(0xf711,11,1);
    EDCU1_2CT_DOOR233_B1 = crrcRicoMvb->getBool(0xf711,11,2);
    EDCU1_2CT_DOOR234_B1 = crrcRicoMvb->getBool(0xf711,11,3);
    EDCU1_2CT_DOOR235_B1 = crrcRicoMvb->getBool(0xf711,11,4);
    EDCU1_2CT_DOOR236_B1 = crrcRicoMvb->getBool(0xf711,11,5);
    EDCU1_2CT_DOOR237_B1 = crrcRicoMvb->getBool(0xf711,11,6);
    EDCU1_2CT_DOOR238_B1 = crrcRicoMvb->getBool(0xf711,11,7);
    EDCU1_2CT_DOOR239_B1 = crrcRicoMvb->getBool(0xf711,12,0);
    EDCU1_2CT_DOOR240_B1 = crrcRicoMvb->getBool(0xf711,12,1);
    EDCU1_2CT_DOOR241_B1 = crrcRicoMvb->getBool(0xf711,12,2);
    EDCU1_2CT_DOOR242_B1 = crrcRicoMvb->getBool(0xf711,12,3);
    EDCU1_2CT_DOOR243_B1 = crrcRicoMvb->getBool(0xf711,12,4);
    EDCU1_2CT_DOOR244_B1 = crrcRicoMvb->getBool(0xf711,12,5);
    EDCU1_2CT_DOOR245_B1 = crrcRicoMvb->getBool(0xf711,12,6);
    EDCU1_2CT_DOOR246_B1 = crrcRicoMvb->getBool(0xf711,12,7);
    EDCU1_2CT_DOOR247_B1 = crrcRicoMvb->getBool(0xf711,13,0);
    EDCU1_2CT_DOOR248_B1 = crrcRicoMvb->getBool(0xf711,13,1);
    EDCU1_2CT_DOOR249_B1 = crrcRicoMvb->getBool(0xf711,13,2);
    EDCU1_2CT_DOOR250_B1 = crrcRicoMvb->getBool(0xf711,13,3);
    EDCU1_2CT_DOOR251_B1 = crrcRicoMvb->getBool(0xf711,13,4);
    EDCU1_2CT_DOOR252_B1 = crrcRicoMvb->getBool(0xf711,13,5);
    EDCU1_2CT_DOOR253_B1 = crrcRicoMvb->getBool(0xf711,13,6);
    EDCU1_2CT_DOOR254_B1 = crrcRicoMvb->getBool(0xf711,13,7);

    EDCU1_2CT_DOOR276_U16 = crrcRicoMvb->getUnsignedInt(0xf712,0);
    EDCU1_2CT_DOOR277_U16 = crrcRicoMvb->getUnsignedInt(0xf712,2);
    EDCU1_2CT_DOOR278_U16 = crrcRicoMvb->getUnsignedInt(0xf712,4);
    EDCU1_2CT_DOOR279_U16 = crrcRicoMvb->getUnsignedInt(0xf712,6);
    EDCU1_2CT_DOOR280_U16 = crrcRicoMvb->getUnsignedInt(0xf712,8);
    EDCU1_2CT_DOOR281_U16 = crrcRicoMvb->getUnsignedInt(0xf712,10);


    temp_virtualports.clear();
    temp_realports.clear();

    //*********************************EDCU3_4-CCU******************************************//
    temp_virtualports<<0xf730<<0xf731<<0xf732;
    temp_realports<<0x730<<0x731<<0x732<<0x740<<0x741<<0x742;
    createEDCUList(this->CTD_EDCU3OLINE_B1,this->CTD_EDCU4OLINE_B1,temp_virtualports,temp_realports);


    EDCU3_4CT_DOOR159_B1 = crrcRicoMvb->getBool(0xf731,2,0);
    EDCU3_4CT_DOOR160_B1 = crrcRicoMvb->getBool(0xf731,2,1);
    EDCU3_4CT_DOOR161_B1 = crrcRicoMvb->getBool(0xf731,2,2);
    EDCU3_4CT_DOOR162_B1 = crrcRicoMvb->getBool(0xf731,2,3);
    EDCU3_4CT_DOOR163_B1 = crrcRicoMvb->getBool(0xf731,2,4);
    EDCU3_4CT_DOOR164_B1 = crrcRicoMvb->getBool(0xf731,2,5);
    EDCU3_4CT_DOOR165_B1 = crrcRicoMvb->getBool(0xf731,2,6);
    EDCU3_4CT_DOOR166_B1 = crrcRicoMvb->getBool(0xf731,2,7);
    EDCU3_4CT_DOOR167_B1 = crrcRicoMvb->getBool(0xf731,3,0);
    EDCU3_4CT_DOOR168_B1 = crrcRicoMvb->getBool(0xf731,3,1);
    EDCU3_4CT_DOOR169_B1 = crrcRicoMvb->getBool(0xf731,3,2);
    EDCU3_4CT_DOOR170_B1 = crrcRicoMvb->getBool(0xf731,3,3);
    EDCU3_4CT_DOOR171_B1 = crrcRicoMvb->getBool(0xf731,3,4);
    EDCU3_4CT_DOOR172_B1 = crrcRicoMvb->getBool(0xf731,3,5);
    EDCU3_4CT_DOOR173_B1 = crrcRicoMvb->getBool(0xf731,3,6);
    EDCU3_4CT_DOOR174_B1 = crrcRicoMvb->getBool(0xf731,3,7);
    EDCU3_4CT_DOOR175_B1 = crrcRicoMvb->getBool(0xf731,4,0);
    EDCU3_4CT_DOOR176_B1 = crrcRicoMvb->getBool(0xf731,4,1);
    EDCU3_4CT_DOOR177_B1 = crrcRicoMvb->getBool(0xf731,4,2);
    EDCU3_4CT_DOOR178_B1 = crrcRicoMvb->getBool(0xf731,4,3);
    EDCU3_4CT_DOOR179_B1 = crrcRicoMvb->getBool(0xf731,4,4);
    EDCU3_4CT_DOOR180_B1 = crrcRicoMvb->getBool(0xf731,4,5);
    EDCU3_4CT_DOOR181_B1 = crrcRicoMvb->getBool(0xf731,4,6);
    EDCU3_4CT_DOOR182_B1 = crrcRicoMvb->getBool(0xf731,4,7);
    EDCU3_4CT_DOOR183_B1 = crrcRicoMvb->getBool(0xf731,5,0);
    EDCU3_4CT_DOOR184_B1 = crrcRicoMvb->getBool(0xf731,5,1);
    EDCU3_4CT_DOOR185_B1 = crrcRicoMvb->getBool(0xf731,5,2);
    EDCU3_4CT_DOOR186_B1 = crrcRicoMvb->getBool(0xf731,5,3);
    EDCU3_4CT_DOOR187_B1 = crrcRicoMvb->getBool(0xf731,5,4);
    EDCU3_4CT_DOOR188_B1 = crrcRicoMvb->getBool(0xf731,5,5);
    EDCU3_4CT_DOOR189_B1 = crrcRicoMvb->getBool(0xf731,5,6);
    EDCU3_4CT_DOOR190_B1 = crrcRicoMvb->getBool(0xf731,5,7);
    EDCU3_4CT_DOOR191_B1 = crrcRicoMvb->getBool(0xf731,6,0);
    EDCU3_4CT_DOOR192_B1 = crrcRicoMvb->getBool(0xf731,6,1);
    EDCU3_4CT_DOOR193_B1 = crrcRicoMvb->getBool(0xf731,6,2);
    EDCU3_4CT_DOOR194_B1 = crrcRicoMvb->getBool(0xf731,6,3);
    EDCU3_4CT_DOOR195_B1 = crrcRicoMvb->getBool(0xf731,6,4);
    EDCU3_4CT_DOOR196_B1 = crrcRicoMvb->getBool(0xf731,6,5);
    EDCU3_4CT_DOOR197_B1 = crrcRicoMvb->getBool(0xf731,6,6);
    EDCU3_4CT_DOOR198_B1 = crrcRicoMvb->getBool(0xf731,6,7);
    EDCU3_4CT_DOOR199_B1 = crrcRicoMvb->getBool(0xf731,7,0);
    EDCU3_4CT_DOOR200_B1 = crrcRicoMvb->getBool(0xf731,7,1);
    EDCU3_4CT_DOOR201_B1 = crrcRicoMvb->getBool(0xf731,7,2);
    EDCU3_4CT_DOOR202_B1 = crrcRicoMvb->getBool(0xf731,7,3);
    EDCU3_4CT_DOOR203_B1 = crrcRicoMvb->getBool(0xf731,7,4);
    EDCU3_4CT_DOOR204_B1 = crrcRicoMvb->getBool(0xf731,7,5);
    EDCU3_4CT_DOOR205_B1 = crrcRicoMvb->getBool(0xf731,7,6);
    EDCU3_4CT_DOOR206_B1 = crrcRicoMvb->getBool(0xf731,7,7);
    EDCU3_4CT_DOOR207_B1 = crrcRicoMvb->getBool(0xf731,8,0);
    EDCU3_4CT_DOOR208_B1 = crrcRicoMvb->getBool(0xf731,8,1);
    EDCU3_4CT_DOOR209_B1 = crrcRicoMvb->getBool(0xf731,8,2);
    EDCU3_4CT_DOOR210_B1 = crrcRicoMvb->getBool(0xf731,8,3);
    EDCU3_4CT_DOOR211_B1 = crrcRicoMvb->getBool(0xf731,8,4);
    EDCU3_4CT_DOOR212_B1 = crrcRicoMvb->getBool(0xf731,8,5);
    EDCU3_4CT_DOOR213_B1 = crrcRicoMvb->getBool(0xf731,8,6);
    EDCU3_4CT_DOOR214_B1 = crrcRicoMvb->getBool(0xf731,8,7);
    EDCU3_4CT_DOOR215_B1 = crrcRicoMvb->getBool(0xf731,9,0);
    EDCU3_4CT_DOOR216_B1 = crrcRicoMvb->getBool(0xf731,9,1);
    EDCU3_4CT_DOOR217_B1 = crrcRicoMvb->getBool(0xf731,9,2);
    EDCU3_4CT_DOOR218_B1 = crrcRicoMvb->getBool(0xf731,9,3);
    EDCU3_4CT_DOOR219_B1 = crrcRicoMvb->getBool(0xf731,9,4);
    EDCU3_4CT_DOOR220_B1 = crrcRicoMvb->getBool(0xf731,9,5);
    EDCU3_4CT_DOOR221_B1 = crrcRicoMvb->getBool(0xf731,9,6);
    EDCU3_4CT_DOOR222_B1 = crrcRicoMvb->getBool(0xf731,9,7);
    EDCU3_4CT_DOOR223_B1 = crrcRicoMvb->getBool(0xf731,10,0);
    EDCU3_4CT_DOOR224_B1 = crrcRicoMvb->getBool(0xf731,10,1);
    EDCU3_4CT_DOOR225_B1 = crrcRicoMvb->getBool(0xf731,10,2);
    EDCU3_4CT_DOOR226_B1 = crrcRicoMvb->getBool(0xf731,10,3);
    EDCU3_4CT_DOOR227_B1 = crrcRicoMvb->getBool(0xf731,10,4);
    EDCU3_4CT_DOOR228_B1 = crrcRicoMvb->getBool(0xf731,10,5);
    EDCU3_4CT_DOOR229_B1 = crrcRicoMvb->getBool(0xf731,10,6);
    EDCU3_4CT_DOOR230_B1 = crrcRicoMvb->getBool(0xf731,10,7);
    EDCU3_4CT_DOOR231_B1 = crrcRicoMvb->getBool(0xf731,11,0);
    EDCU3_4CT_DOOR232_B1 = crrcRicoMvb->getBool(0xf731,11,1);
    EDCU3_4CT_DOOR233_B1 = crrcRicoMvb->getBool(0xf731,11,2);
    EDCU3_4CT_DOOR234_B1 = crrcRicoMvb->getBool(0xf731,11,3);
    EDCU3_4CT_DOOR235_B1 = crrcRicoMvb->getBool(0xf731,11,4);
    EDCU3_4CT_DOOR236_B1 = crrcRicoMvb->getBool(0xf731,11,5);
    EDCU3_4CT_DOOR237_B1 = crrcRicoMvb->getBool(0xf731,11,6);
    EDCU3_4CT_DOOR238_B1 = crrcRicoMvb->getBool(0xf731,11,7);
    EDCU3_4CT_DOOR239_B1 = crrcRicoMvb->getBool(0xf731,12,0);
    EDCU3_4CT_DOOR240_B1 = crrcRicoMvb->getBool(0xf731,12,1);
    EDCU3_4CT_DOOR241_B1 = crrcRicoMvb->getBool(0xf731,12,2);
    EDCU3_4CT_DOOR242_B1 = crrcRicoMvb->getBool(0xf731,12,3);
    EDCU3_4CT_DOOR243_B1 = crrcRicoMvb->getBool(0xf731,12,4);
    EDCU3_4CT_DOOR244_B1 = crrcRicoMvb->getBool(0xf731,12,5);
    EDCU3_4CT_DOOR245_B1 = crrcRicoMvb->getBool(0xf731,12,6);
    EDCU3_4CT_DOOR246_B1 = crrcRicoMvb->getBool(0xf731,12,7);
    EDCU3_4CT_DOOR247_B1 = crrcRicoMvb->getBool(0xf731,13,0);
    EDCU3_4CT_DOOR248_B1 = crrcRicoMvb->getBool(0xf731,13,1);
    EDCU3_4CT_DOOR249_B1 = crrcRicoMvb->getBool(0xf731,13,2);
    EDCU3_4CT_DOOR250_B1 = crrcRicoMvb->getBool(0xf731,13,3);
    EDCU3_4CT_DOOR251_B1 = crrcRicoMvb->getBool(0xf731,13,4);
    EDCU3_4CT_DOOR252_B1 = crrcRicoMvb->getBool(0xf731,13,5);
    EDCU3_4CT_DOOR253_B1 = crrcRicoMvb->getBool(0xf731,13,6);
    EDCU3_4CT_DOOR254_B1 = crrcRicoMvb->getBool(0xf731,13,7);

    EDCU3_4CT_DOOR276_U16 = crrcRicoMvb->getUnsignedInt(0xf732,0);
    EDCU3_4CT_DOOR277_U16 = crrcRicoMvb->getUnsignedInt(0xf732,2);
    EDCU3_4CT_DOOR278_U16 = crrcRicoMvb->getUnsignedInt(0xf732,4);
    EDCU3_4CT_DOOR279_U16 = crrcRicoMvb->getUnsignedInt(0xf732,6);
    EDCU3_4CT_DOOR280_U16 = crrcRicoMvb->getUnsignedInt(0xf732,8);
    EDCU3_4CT_DOOR281_U16 = crrcRicoMvb->getUnsignedInt(0xf732,10);

    temp_virtualports.clear();
    temp_realports.clear();

    //***************************************EDCU5_6-CCU********************************************//
    temp_virtualports<<0xf750<<0xf751<<0xf752;
    temp_realports<<0x750<<0x751<<0x752<<0x760<<0x761<<0x762;
    createEDCUList(this->CTD_EDCU5OLINE_B1,this->CTD_EDCU6OLINE_B1,temp_virtualports,temp_realports);

    EDCU5_6CT_DOOR159_B1 = crrcRicoMvb->getBool(0xf751,2,0);
    EDCU5_6CT_DOOR160_B1 = crrcRicoMvb->getBool(0xf751,2,1);
    EDCU5_6CT_DOOR161_B1 = crrcRicoMvb->getBool(0xf751,2,2);
    EDCU5_6CT_DOOR162_B1 = crrcRicoMvb->getBool(0xf751,2,3);
    EDCU5_6CT_DOOR163_B1 = crrcRicoMvb->getBool(0xf751,2,4);
    EDCU5_6CT_DOOR164_B1 = crrcRicoMvb->getBool(0xf751,2,5);
    EDCU5_6CT_DOOR165_B1 = crrcRicoMvb->getBool(0xf751,2,6);
    EDCU5_6CT_DOOR166_B1 = crrcRicoMvb->getBool(0xf751,2,7);
    EDCU5_6CT_DOOR167_B1 = crrcRicoMvb->getBool(0xf751,3,0);
    EDCU5_6CT_DOOR168_B1 = crrcRicoMvb->getBool(0xf751,3,1);
    EDCU5_6CT_DOOR169_B1 = crrcRicoMvb->getBool(0xf751,3,2);
    EDCU5_6CT_DOOR170_B1 = crrcRicoMvb->getBool(0xf751,3,3);
    EDCU5_6CT_DOOR171_B1 = crrcRicoMvb->getBool(0xf751,3,4);
    EDCU5_6CT_DOOR172_B1 = crrcRicoMvb->getBool(0xf751,3,5);
    EDCU5_6CT_DOOR173_B1 = crrcRicoMvb->getBool(0xf751,3,6);
    EDCU5_6CT_DOOR174_B1 = crrcRicoMvb->getBool(0xf751,3,7);
    EDCU5_6CT_DOOR175_B1 = crrcRicoMvb->getBool(0xf751,4,0);
    EDCU5_6CT_DOOR176_B1 = crrcRicoMvb->getBool(0xf751,4,1);
    EDCU5_6CT_DOOR177_B1 = crrcRicoMvb->getBool(0xf751,4,2);
    EDCU5_6CT_DOOR178_B1 = crrcRicoMvb->getBool(0xf751,4,3);
    EDCU5_6CT_DOOR179_B1 = crrcRicoMvb->getBool(0xf751,4,4);
    EDCU5_6CT_DOOR180_B1 = crrcRicoMvb->getBool(0xf751,4,5);
    EDCU5_6CT_DOOR181_B1 = crrcRicoMvb->getBool(0xf751,4,6);
    EDCU5_6CT_DOOR182_B1 = crrcRicoMvb->getBool(0xf751,4,7);
    EDCU5_6CT_DOOR183_B1 = crrcRicoMvb->getBool(0xf751,5,0);
    EDCU5_6CT_DOOR184_B1 = crrcRicoMvb->getBool(0xf751,5,1);
    EDCU5_6CT_DOOR185_B1 = crrcRicoMvb->getBool(0xf751,5,2);
    EDCU5_6CT_DOOR186_B1 = crrcRicoMvb->getBool(0xf751,5,3);
    EDCU5_6CT_DOOR187_B1 = crrcRicoMvb->getBool(0xf751,5,4);
    EDCU5_6CT_DOOR188_B1 = crrcRicoMvb->getBool(0xf751,5,5);
    EDCU5_6CT_DOOR189_B1 = crrcRicoMvb->getBool(0xf751,5,6);
    EDCU5_6CT_DOOR190_B1 = crrcRicoMvb->getBool(0xf751,5,7);
    EDCU5_6CT_DOOR191_B1 = crrcRicoMvb->getBool(0xf751,6,0);
    EDCU5_6CT_DOOR192_B1 = crrcRicoMvb->getBool(0xf751,6,1);
    EDCU5_6CT_DOOR193_B1 = crrcRicoMvb->getBool(0xf751,6,2);
    EDCU5_6CT_DOOR194_B1 = crrcRicoMvb->getBool(0xf751,6,3);
    EDCU5_6CT_DOOR195_B1 = crrcRicoMvb->getBool(0xf751,6,4);
    EDCU5_6CT_DOOR196_B1 = crrcRicoMvb->getBool(0xf751,6,5);
    EDCU5_6CT_DOOR197_B1 = crrcRicoMvb->getBool(0xf751,6,6);
    EDCU5_6CT_DOOR198_B1 = crrcRicoMvb->getBool(0xf751,6,7);
    EDCU5_6CT_DOOR199_B1 = crrcRicoMvb->getBool(0xf751,7,0);
    EDCU5_6CT_DOOR200_B1 = crrcRicoMvb->getBool(0xf751,7,1);
    EDCU5_6CT_DOOR201_B1 = crrcRicoMvb->getBool(0xf751,7,2);
    EDCU5_6CT_DOOR202_B1 = crrcRicoMvb->getBool(0xf751,7,3);
    EDCU5_6CT_DOOR203_B1 = crrcRicoMvb->getBool(0xf751,7,4);
    EDCU5_6CT_DOOR204_B1 = crrcRicoMvb->getBool(0xf751,7,5);
    EDCU5_6CT_DOOR205_B1 = crrcRicoMvb->getBool(0xf751,7,6);
    EDCU5_6CT_DOOR206_B1 = crrcRicoMvb->getBool(0xf751,7,7);
    EDCU5_6CT_DOOR207_B1 = crrcRicoMvb->getBool(0xf751,8,0);
    EDCU5_6CT_DOOR208_B1 = crrcRicoMvb->getBool(0xf751,8,1);
    EDCU5_6CT_DOOR209_B1 = crrcRicoMvb->getBool(0xf751,8,2);
    EDCU5_6CT_DOOR210_B1 = crrcRicoMvb->getBool(0xf751,8,3);
    EDCU5_6CT_DOOR211_B1 = crrcRicoMvb->getBool(0xf751,8,4);
    EDCU5_6CT_DOOR212_B1 = crrcRicoMvb->getBool(0xf751,8,5);
    EDCU5_6CT_DOOR213_B1 = crrcRicoMvb->getBool(0xf751,8,6);
    EDCU5_6CT_DOOR214_B1 = crrcRicoMvb->getBool(0xf751,8,7);
    EDCU5_6CT_DOOR215_B1 = crrcRicoMvb->getBool(0xf751,9,0);
    EDCU5_6CT_DOOR216_B1 = crrcRicoMvb->getBool(0xf751,9,1);
    EDCU5_6CT_DOOR217_B1 = crrcRicoMvb->getBool(0xf751,9,2);
    EDCU5_6CT_DOOR218_B1 = crrcRicoMvb->getBool(0xf751,9,3);
    EDCU5_6CT_DOOR219_B1 = crrcRicoMvb->getBool(0xf751,9,4);
    EDCU5_6CT_DOOR220_B1 = crrcRicoMvb->getBool(0xf751,9,5);
    EDCU5_6CT_DOOR221_B1 = crrcRicoMvb->getBool(0xf751,9,6);
    EDCU5_6CT_DOOR222_B1 = crrcRicoMvb->getBool(0xf751,9,7);
    EDCU5_6CT_DOOR223_B1 = crrcRicoMvb->getBool(0xf751,10,0);
    EDCU5_6CT_DOOR224_B1 = crrcRicoMvb->getBool(0xf751,10,1);
    EDCU5_6CT_DOOR225_B1 = crrcRicoMvb->getBool(0xf751,10,2);
    EDCU5_6CT_DOOR226_B1 = crrcRicoMvb->getBool(0xf751,10,3);
    EDCU5_6CT_DOOR227_B1 = crrcRicoMvb->getBool(0xf751,10,4);
    EDCU5_6CT_DOOR228_B1 = crrcRicoMvb->getBool(0xf751,10,5);
    EDCU5_6CT_DOOR229_B1 = crrcRicoMvb->getBool(0xf751,10,6);
    EDCU5_6CT_DOOR230_B1 = crrcRicoMvb->getBool(0xf751,10,7);
    EDCU5_6CT_DOOR231_B1 = crrcRicoMvb->getBool(0xf751,11,0);
    EDCU5_6CT_DOOR232_B1 = crrcRicoMvb->getBool(0xf751,11,1);
    EDCU5_6CT_DOOR233_B1 = crrcRicoMvb->getBool(0xf751,11,2);
    EDCU5_6CT_DOOR234_B1 = crrcRicoMvb->getBool(0xf751,11,3);
    EDCU5_6CT_DOOR235_B1 = crrcRicoMvb->getBool(0xf751,11,4);
    EDCU5_6CT_DOOR236_B1 = crrcRicoMvb->getBool(0xf751,11,5);
    EDCU5_6CT_DOOR237_B1 = crrcRicoMvb->getBool(0xf751,11,6);
    EDCU5_6CT_DOOR238_B1 = crrcRicoMvb->getBool(0xf751,11,7);
    EDCU5_6CT_DOOR239_B1 = crrcRicoMvb->getBool(0xf751,12,0);
    EDCU5_6CT_DOOR240_B1 = crrcRicoMvb->getBool(0xf751,12,1);
    EDCU5_6CT_DOOR241_B1 = crrcRicoMvb->getBool(0xf751,12,2);
    EDCU5_6CT_DOOR242_B1 = crrcRicoMvb->getBool(0xf751,12,3);
    EDCU5_6CT_DOOR243_B1 = crrcRicoMvb->getBool(0xf751,12,4);
    EDCU5_6CT_DOOR244_B1 = crrcRicoMvb->getBool(0xf751,12,5);
    EDCU5_6CT_DOOR245_B1 = crrcRicoMvb->getBool(0xf751,12,6);
    EDCU5_6CT_DOOR246_B1 = crrcRicoMvb->getBool(0xf751,12,7);
    EDCU5_6CT_DOOR247_B1 = crrcRicoMvb->getBool(0xf751,13,0);
    EDCU5_6CT_DOOR248_B1 = crrcRicoMvb->getBool(0xf751,13,1);
    EDCU5_6CT_DOOR249_B1 = crrcRicoMvb->getBool(0xf751,13,2);
    EDCU5_6CT_DOOR250_B1 = crrcRicoMvb->getBool(0xf751,13,3);
    EDCU5_6CT_DOOR251_B1 = crrcRicoMvb->getBool(0xf751,13,4);
    EDCU5_6CT_DOOR252_B1 = crrcRicoMvb->getBool(0xf751,13,5);
    EDCU5_6CT_DOOR253_B1 = crrcRicoMvb->getBool(0xf751,13,6);
    EDCU5_6CT_DOOR254_B1 = crrcRicoMvb->getBool(0xf751,13,7);


    EDCU5_6CT_DOOR276_U16 = crrcRicoMvb->getUnsignedInt(0xf752,0);
    EDCU5_6CT_DOOR277_U16 = crrcRicoMvb->getUnsignedInt(0xf752,2);
    EDCU5_6CT_DOOR278_U16 = crrcRicoMvb->getUnsignedInt(0xf752,4);
    EDCU5_6CT_DOOR279_U16 = crrcRicoMvb->getUnsignedInt(0xf752,6);
    EDCU5_6CT_DOOR280_U16 = crrcRicoMvb->getUnsignedInt(0xf752,8);
    EDCU5_6CT_DOOR281_U16 = crrcRicoMvb->getUnsignedInt(0xf752,10);
    temp_virtualports.clear();
    temp_realports.clear();

//***********************************************EDCU7_8-CCU*****************************************//
    temp_virtualports<<0xf770<<0xf771<<0xf772;
    temp_realports<<0x770<<0x771<<0x772<<0x780<<0x781<<0x782;
    createEDCUList(this->CTD_EDCU7OLINE_B1,this->CTD_EDCU8OLINE_B1,temp_virtualports,temp_realports);

    EDCU7_8CT_DOOR159_B1 = crrcRicoMvb->getBool(0xf771,2,0);
    EDCU7_8CT_DOOR160_B1 = crrcRicoMvb->getBool(0xf771,2,1);
    EDCU7_8CT_DOOR161_B1 = crrcRicoMvb->getBool(0xf771,2,2);
    EDCU7_8CT_DOOR162_B1 = crrcRicoMvb->getBool(0xf771,2,3);
    EDCU7_8CT_DOOR163_B1 = crrcRicoMvb->getBool(0xf771,2,4);
    EDCU7_8CT_DOOR164_B1 = crrcRicoMvb->getBool(0xf771,2,5);
    EDCU7_8CT_DOOR165_B1 = crrcRicoMvb->getBool(0xf771,2,6);
    EDCU7_8CT_DOOR166_B1 = crrcRicoMvb->getBool(0xf771,2,7);
    EDCU7_8CT_DOOR167_B1 = crrcRicoMvb->getBool(0xf771,3,0);
    EDCU7_8CT_DOOR168_B1 = crrcRicoMvb->getBool(0xf771,3,1);
    EDCU7_8CT_DOOR169_B1 = crrcRicoMvb->getBool(0xf771,3,2);
    EDCU7_8CT_DOOR170_B1 = crrcRicoMvb->getBool(0xf771,3,3);
    EDCU7_8CT_DOOR171_B1 = crrcRicoMvb->getBool(0xf771,3,4);
    EDCU7_8CT_DOOR172_B1 = crrcRicoMvb->getBool(0xf771,3,5);
    EDCU7_8CT_DOOR173_B1 = crrcRicoMvb->getBool(0xf771,3,6);
    EDCU7_8CT_DOOR174_B1 = crrcRicoMvb->getBool(0xf771,3,7);
    EDCU7_8CT_DOOR175_B1 = crrcRicoMvb->getBool(0xf771,4,0);
    EDCU7_8CT_DOOR176_B1 = crrcRicoMvb->getBool(0xf771,4,1);
    EDCU7_8CT_DOOR177_B1 = crrcRicoMvb->getBool(0xf771,4,2);
    EDCU7_8CT_DOOR178_B1 = crrcRicoMvb->getBool(0xf771,4,3);
    EDCU7_8CT_DOOR179_B1 = crrcRicoMvb->getBool(0xf771,4,4);
    EDCU7_8CT_DOOR180_B1 = crrcRicoMvb->getBool(0xf771,4,5);
    EDCU7_8CT_DOOR181_B1 = crrcRicoMvb->getBool(0xf771,4,6);
    EDCU7_8CT_DOOR182_B1 = crrcRicoMvb->getBool(0xf771,4,7);
    EDCU7_8CT_DOOR183_B1 = crrcRicoMvb->getBool(0xf771,5,0);
    EDCU7_8CT_DOOR184_B1 = crrcRicoMvb->getBool(0xf771,5,1);
    EDCU7_8CT_DOOR185_B1 = crrcRicoMvb->getBool(0xf771,5,2);
    EDCU7_8CT_DOOR186_B1 = crrcRicoMvb->getBool(0xf771,5,3);
    EDCU7_8CT_DOOR187_B1 = crrcRicoMvb->getBool(0xf771,5,4);
    EDCU7_8CT_DOOR188_B1 = crrcRicoMvb->getBool(0xf771,5,5);
    EDCU7_8CT_DOOR189_B1 = crrcRicoMvb->getBool(0xf771,5,6);
    EDCU7_8CT_DOOR190_B1 = crrcRicoMvb->getBool(0xf771,5,7);
    EDCU7_8CT_DOOR191_B1 = crrcRicoMvb->getBool(0xf771,6,0);
    EDCU7_8CT_DOOR192_B1 = crrcRicoMvb->getBool(0xf771,6,1);
    EDCU7_8CT_DOOR193_B1 = crrcRicoMvb->getBool(0xf771,6,2);
    EDCU7_8CT_DOOR194_B1 = crrcRicoMvb->getBool(0xf771,6,3);
    EDCU7_8CT_DOOR195_B1 = crrcRicoMvb->getBool(0xf771,6,4);
    EDCU7_8CT_DOOR196_B1 = crrcRicoMvb->getBool(0xf771,6,5);
    EDCU7_8CT_DOOR197_B1 = crrcRicoMvb->getBool(0xf771,6,6);
    EDCU7_8CT_DOOR198_B1 = crrcRicoMvb->getBool(0xf771,6,7);
    EDCU7_8CT_DOOR199_B1 = crrcRicoMvb->getBool(0xf771,7,0);
    EDCU7_8CT_DOOR200_B1 = crrcRicoMvb->getBool(0xf771,7,1);
    EDCU7_8CT_DOOR201_B1 = crrcRicoMvb->getBool(0xf771,7,2);
    EDCU7_8CT_DOOR202_B1 = crrcRicoMvb->getBool(0xf771,7,3);
    EDCU7_8CT_DOOR203_B1 = crrcRicoMvb->getBool(0xf771,7,4);
    EDCU7_8CT_DOOR204_B1 = crrcRicoMvb->getBool(0xf771,7,5);
    EDCU7_8CT_DOOR205_B1 = crrcRicoMvb->getBool(0xf771,7,6);
    EDCU7_8CT_DOOR206_B1 = crrcRicoMvb->getBool(0xf771,7,7);
    EDCU7_8CT_DOOR207_B1 = crrcRicoMvb->getBool(0xf771,8,0);
    EDCU7_8CT_DOOR208_B1 = crrcRicoMvb->getBool(0xf771,8,1);
    EDCU7_8CT_DOOR209_B1 = crrcRicoMvb->getBool(0xf771,8,2);
    EDCU7_8CT_DOOR210_B1 = crrcRicoMvb->getBool(0xf771,8,3);
    EDCU7_8CT_DOOR211_B1 = crrcRicoMvb->getBool(0xf771,8,4);
    EDCU7_8CT_DOOR212_B1 = crrcRicoMvb->getBool(0xf771,8,5);
    EDCU7_8CT_DOOR213_B1 = crrcRicoMvb->getBool(0xf771,8,6);
    EDCU7_8CT_DOOR214_B1 = crrcRicoMvb->getBool(0xf771,8,7);
    EDCU7_8CT_DOOR215_B1 = crrcRicoMvb->getBool(0xf771,9,0);
    EDCU7_8CT_DOOR216_B1 = crrcRicoMvb->getBool(0xf771,9,1);
    EDCU7_8CT_DOOR217_B1 = crrcRicoMvb->getBool(0xf771,9,2);
    EDCU7_8CT_DOOR218_B1 = crrcRicoMvb->getBool(0xf771,9,3);
    EDCU7_8CT_DOOR219_B1 = crrcRicoMvb->getBool(0xf771,9,4);
    EDCU7_8CT_DOOR220_B1 = crrcRicoMvb->getBool(0xf771,9,5);
    EDCU7_8CT_DOOR221_B1 = crrcRicoMvb->getBool(0xf771,9,6);
    EDCU7_8CT_DOOR222_B1 = crrcRicoMvb->getBool(0xf771,9,7);
    EDCU7_8CT_DOOR223_B1 = crrcRicoMvb->getBool(0xf771,10,0);
    EDCU7_8CT_DOOR224_B1 = crrcRicoMvb->getBool(0xf771,10,1);
    EDCU7_8CT_DOOR225_B1 = crrcRicoMvb->getBool(0xf771,10,2);
    EDCU7_8CT_DOOR226_B1 = crrcRicoMvb->getBool(0xf771,10,3);
    EDCU7_8CT_DOOR227_B1 = crrcRicoMvb->getBool(0xf771,10,4);
    EDCU7_8CT_DOOR228_B1 = crrcRicoMvb->getBool(0xf771,10,5);
    EDCU7_8CT_DOOR229_B1 = crrcRicoMvb->getBool(0xf771,10,6);
    EDCU7_8CT_DOOR230_B1 = crrcRicoMvb->getBool(0xf771,10,7);
    EDCU7_8CT_DOOR231_B1 = crrcRicoMvb->getBool(0xf771,11,0);
    EDCU7_8CT_DOOR232_B1 = crrcRicoMvb->getBool(0xf771,11,1);
    EDCU7_8CT_DOOR233_B1 = crrcRicoMvb->getBool(0xf771,11,2);
    EDCU7_8CT_DOOR234_B1 = crrcRicoMvb->getBool(0xf771,11,3);
    EDCU7_8CT_DOOR235_B1 = crrcRicoMvb->getBool(0xf771,11,4);
    EDCU7_8CT_DOOR236_B1 = crrcRicoMvb->getBool(0xf771,11,5);
    EDCU7_8CT_DOOR237_B1 = crrcRicoMvb->getBool(0xf771,11,6);
    EDCU7_8CT_DOOR238_B1 = crrcRicoMvb->getBool(0xf771,11,7);
    EDCU7_8CT_DOOR239_B1 = crrcRicoMvb->getBool(0xf771,12,0);
    EDCU7_8CT_DOOR240_B1 = crrcRicoMvb->getBool(0xf771,12,1);
    EDCU7_8CT_DOOR241_B1 = crrcRicoMvb->getBool(0xf771,12,2);
    EDCU7_8CT_DOOR242_B1 = crrcRicoMvb->getBool(0xf771,12,3);
    EDCU7_8CT_DOOR243_B1 = crrcRicoMvb->getBool(0xf771,12,4);
    EDCU7_8CT_DOOR244_B1 = crrcRicoMvb->getBool(0xf771,12,5);
    EDCU7_8CT_DOOR245_B1 = crrcRicoMvb->getBool(0xf771,12,6);
    EDCU7_8CT_DOOR246_B1 = crrcRicoMvb->getBool(0xf771,12,7);
    EDCU7_8CT_DOOR247_B1 = crrcRicoMvb->getBool(0xf771,13,0);
    EDCU7_8CT_DOOR248_B1 = crrcRicoMvb->getBool(0xf771,13,1);
    EDCU7_8CT_DOOR249_B1 = crrcRicoMvb->getBool(0xf771,13,2);
    EDCU7_8CT_DOOR250_B1 = crrcRicoMvb->getBool(0xf771,13,3);
    EDCU7_8CT_DOOR251_B1 = crrcRicoMvb->getBool(0xf771,13,4);
    EDCU7_8CT_DOOR252_B1 = crrcRicoMvb->getBool(0xf771,13,5);
    EDCU7_8CT_DOOR253_B1 = crrcRicoMvb->getBool(0xf771,13,6);
    EDCU7_8CT_DOOR254_B1 = crrcRicoMvb->getBool(0xf771,13,7);

    EDCU7_8CT_DOOR276_U16 = crrcRicoMvb->getUnsignedInt(0xf772,0);
    EDCU7_8CT_DOOR277_U16 = crrcRicoMvb->getUnsignedInt(0xf772,2);
    EDCU7_8CT_DOOR278_U16 = crrcRicoMvb->getUnsignedInt(0xf772,4);
    EDCU7_8CT_DOOR279_U16 = crrcRicoMvb->getUnsignedInt(0xf772,6);
    EDCU7_8CT_DOOR280_U16 = crrcRicoMvb->getUnsignedInt(0xf772,8);
    EDCU7_8CT_DOOR281_U16 = crrcRicoMvb->getUnsignedInt(0xf772,10);

    //*******************************************FCU-CCU***********************************//
    createFCUList();

    FCU1CT_SHD1Alarm1_B1 = crrcRicoMvb->getBool(0xf810,5,0);
    FCU1CT_SHD1Flt1_B1 = crrcRicoMvb->getBool(0xf810,5,1);
    FCU1CT_SHD2Alarm1_B1 = crrcRicoMvb->getBool(0xf810,5,2);
    FCU1CT_SHD2Flt1_B1 = crrcRicoMvb->getBool(0xf810,5,3);
    FCU1CT_SHD3Alarm1_B1 = crrcRicoMvb->getBool(0xf810,5,4);
    FCU1CT_SHD3Flt1_B1 = crrcRicoMvb->getBool(0xf810,5,5);
    FCU1CT_SHD4Alarm1_B1 = crrcRicoMvb->getBool(0xf810,5,6);
    FCU1CT_SHD4Flt1_B1 = crrcRicoMvb->getBool(0xf810,5,7);
    FCU1CT_SHD5Alarm1_B1 = crrcRicoMvb->getBool(0xf810,6,0);
    FCU1CT_SHD5Flt1_B1 = crrcRicoMvb->getBool(0xf810,6,1);
    FCU1CT_SHD6Alarm1_B1 = crrcRicoMvb->getBool(0xf810,6,2);
    FCU1CT_SHD6Flt1_B1 = crrcRicoMvb->getBool(0xf810,6,3);
    FCU1CT_SHD7Alarm1_B1 = crrcRicoMvb->getBool(0xf810,6,4);
    FCU1CT_SHD7Flt1_B1 = crrcRicoMvb->getBool(0xf810,6,5);
    FCU1CT_SHD1Alarm2_B1 = crrcRicoMvb->getBool(0xf810,6,6);
    FCU1CT_SHD1Flt2_B1 = crrcRicoMvb->getBool(0xf810,6,7);
    FCU1CT_SHD2Alarm2_B1 = crrcRicoMvb->getBool(0xf810,7,0);
    FCU1CT_SHD2Flt2_B1 = crrcRicoMvb->getBool(0xf810,7,1);
    FCU1CT_SHD3Alarm2_B1 = crrcRicoMvb->getBool(0xf810,7,2);
    FCU1CT_SHD3Flt2_B1 = crrcRicoMvb->getBool(0xf810,7,3);
    FCU1CT_SHD4Alarm2_B1 = crrcRicoMvb->getBool(0xf810,7,4);
    FCU1CT_SHD4Flt2_B1 = crrcRicoMvb->getBool(0xf810,7,5);
    FCU1CT_SHD1Alarm3_B1 = crrcRicoMvb->getBool(0xf810,7,6);
    FCU1CT_SHD1Flt3_B1 = crrcRicoMvb->getBool(0xf810,7,7);
    FCU1CT_SHD2Alarm3_B1 = crrcRicoMvb->getBool(0xf810,8,0);
    FCU1CT_SHD2Flt3_B1 = crrcRicoMvb->getBool(0xf810,8,1);
    FCU1CT_SHD3Alarm3_B1 = crrcRicoMvb->getBool(0xf810,8,2);
    FCU1CT_SHD3Flt3_B1 = crrcRicoMvb->getBool(0xf810,8,3);
    FCU1CT_SHD4Alarm3_B1 = crrcRicoMvb->getBool(0xf810,8,4);
    FCU1CT_SHD4Flt3_B1 = crrcRicoMvb->getBool(0xf810,8,5);
    FCU1CT_SHD1Alarm4_B1 = crrcRicoMvb->getBool(0xf810,8,6);
    FCU1CT_SHD1Flt4_B1 = crrcRicoMvb->getBool(0xf810,8,7);
    FCU1CT_SHD2Alarm4_B1 = crrcRicoMvb->getBool(0xf810,9,0);
    FCU1CT_SHD2Flt4_B1 = crrcRicoMvb->getBool(0xf810,9,1);
    FCU1CT_SHD3Alarm4_B1 = crrcRicoMvb->getBool(0xf810,9,2);
    FCU1CT_SHD3Flt4_B1 = crrcRicoMvb->getBool(0xf810,9,3);
    FCU1CT_SHD4Alarm4_B1 = crrcRicoMvb->getBool(0xf810,9,4);
    FCU1CT_SHD4Flt4_B1 = crrcRicoMvb->getBool(0xf810,9,5);
    FCU1CT_SHD5Alarm4_B1 = crrcRicoMvb->getBool(0xf810,9,6);
    FCU1CT_SHD5Flt4_B1 = crrcRicoMvb->getBool(0xf810,9,7);
    FCU1CT_SHD6Alarm4_B1 = crrcRicoMvb->getBool(0xf810,10,0);
    FCU1CT_SHD6Flt4_B1 = crrcRicoMvb->getBool(0xf810,10,1);
    FCU1CT_SHD7Alarm4_B1 = crrcRicoMvb->getBool(0xf810,10,2);
    FCU1CT_SHD7Flt4_B1 = crrcRicoMvb->getBool(0xf810,10,3);

//    FCU2CT_SHD1Alarm1_B1 = crrcRicoMvb->getBool(0x820,5,0);
//    FCU2CT_SHD1Flt1_B1 = crrcRicoMvb->getBool(0x820,5,1);
//    FCU2CT_SHD2Alarm1_B1 = crrcRicoMvb->getBool(0x820,5,2);
//    FCU2CT_SHD2Flt1_B1 = crrcRicoMvb->getBool(0x820,5,3);
//    FCU2CT_SHD3Alarm1_B1 = crrcRicoMvb->getBool(0x820,5,4);
//    FCU2CT_SHD3Flt1_B1 = crrcRicoMvb->getBool(0x820,5,5);
//    FCU2CT_SHD4Alarm1_B1 = crrcRicoMvb->getBool(0x820,5,6);
//    FCU2CT_SHD4Flt1_B1 = crrcRicoMvb->getBool(0x820,5,7);
//    FCU2CT_SHD5Alarm1_B1 = crrcRicoMvb->getBool(0x820,6,0);
//    FCU2CT_SHD5Flt1_B1 = crrcRicoMvb->getBool(0x820,6,1);
//    FCU2CT_SHD6Alarm1_B1 = crrcRicoMvb->getBool(0x820,6,2);
//    FCU2CT_SHD6Flt1_B1 = crrcRicoMvb->getBool(0x820,6,3);
//    FCU2CT_SHD7Alarm1_B1 = crrcRicoMvb->getBool(0x820,6,4);
//    FCU2CT_SHD7Flt1_B1 = crrcRicoMvb->getBool(0x820,6,5);
//    FCU2CT_SHD1Alarm2_B1 = crrcRicoMvb->getBool(0x820,6,6);
//    FCU2CT_SHD1Flt2_B1 = crrcRicoMvb->getBool(0x820,6,7);
//    FCU2CT_SHD2Alarm2_B1 = crrcRicoMvb->getBool(0x820,7,0);
//    FCU2CT_SHD2Flt2_B1 = crrcRicoMvb->getBool(0x820,7,1);
//    FCU2CT_SHD3Alarm2_B1 = crrcRicoMvb->getBool(0x820,7,2);
//    FCU2CT_SHD3Flt2_B1 = crrcRicoMvb->getBool(0x820,7,3);
//    FCU2CT_SHD4Alarm2_B1 = crrcRicoMvb->getBool(0x820,7,4);
//    FCU2CT_SHD4Flt2_B1 = crrcRicoMvb->getBool(0x820,7,5);
//    FCU2CT_SHD1Alarm3_B1 = crrcRicoMvb->getBool(0x820,7,6);
//    FCU2CT_SHD1Flt3_B1 = crrcRicoMvb->getBool(0x820,7,7);
//    FCU2CT_SHD2Alarm3_B1 = crrcRicoMvb->getBool(0x820,8,0);
//    FCU2CT_SHD2Flt3_B1 = crrcRicoMvb->getBool(0x820,8,1);
//    FCU2CT_SHD3Alarm3_B1 = crrcRicoMvb->getBool(0x820,8,2);
//    FCU2CT_SHD3Flt3_B1 = crrcRicoMvb->getBool(0x820,8,3);
//    FCU2CT_SHD4Alarm3_B1 = crrcRicoMvb->getBool(0x820,8,4);
//    FCU2CT_SHD4Flt3_B1 = crrcRicoMvb->getBool(0x820,8,5);
//    FCU2CT_SHD1Alarm4_B1 = crrcRicoMvb->getBool(0x820,8,6);
//    FCU2CT_SHD1Flt4_B1 = crrcRicoMvb->getBool(0x820,8,7);
//    FCU2CT_SHD2Alarm4_B1 = crrcRicoMvb->getBool(0x820,9,0);
//    FCU2CT_SHD2Flt4_B1 = crrcRicoMvb->getBool(0x820,9,1);
//    FCU2CT_SHD3Alarm4_B1 = crrcRicoMvb->getBool(0x820,9,2);
//    FCU2CT_SHD3Flt4_B1 = crrcRicoMvb->getBool(0x820,9,3);
//    FCU2CT_SHD4Alarm4_B1 = crrcRicoMvb->getBool(0x820,9,4);
//    FCU2CT_SHD4Flt4_B1 = crrcRicoMvb->getBool(0x820,9,5);
//    FCU2CT_SHD5Alarm4_B1 = crrcRicoMvb->getBool(0x820,9,6);
//    FCU2CT_SHD5Flt4_B1 = crrcRicoMvb->getBool(0x820,9,7);
//    FCU2CT_SHD6Alarm4_B1 = crrcRicoMvb->getBool(0x820,10,0);
//    FCU2CT_SHD6Flt4_B1 = crrcRicoMvb->getBool(0x820,10,1);
//    FCU2CT_SHD7Alarm4_B1 = crrcRicoMvb->getBool(0x820,10,2);
//    FCU2CT_SHD7Flt4_B1 = crrcRicoMvb->getBool(0x820,10,3);


    //********************************************************PIS-CCU*******************************************//
    createPISList();

    PISiCT_P81_B1 = crrcRicoMvb->getBool(0xf910,12,0);
    PISiCT_P82_B1 = crrcRicoMvb->getBool(0xf910,12,1);
    PISiCT_P83_B1 = crrcRicoMvb->getBool(0xf910,12,2);
    PISiCT_P84_B1 = crrcRicoMvb->getBool(0xf910,12,3);
    PISiCT_P85_B1 = crrcRicoMvb->getBool(0xf910,12,4);
    PISiCT_P86_B1 = crrcRicoMvb->getBool(0xf910,12,5);
    PISiCT_P89_B1 = crrcRicoMvb->getBool(0xf910,13,0);
    PISiCT_P90_B1 = crrcRicoMvb->getBool(0xf910,13,1);
    PISiCT_P91_B1 = crrcRicoMvb->getBool(0xf910,13,2);
    PISiCT_P92_B1 = crrcRicoMvb->getBool(0xf910,13,3);
    PISiCT_P93_B1 = crrcRicoMvb->getBool(0xf910,13,4);
    PISiCT_P94_B1 = crrcRicoMvb->getBool(0xf910,13,5);
    PISiCT_P97_B1 = crrcRicoMvb->getBool(0xf910,14,0);
    PISiCT_P98_B1 = crrcRicoMvb->getBool(0xf910,14,1);
    PISiCT_P99_B1 = crrcRicoMvb->getBool(0xf910,14,2);
    PISiCT_P100_B1 = crrcRicoMvb->getBool(0xf910,14,3);
    PISiCT_P101_B1 = crrcRicoMvb->getBool(0xf910,14,4);
    PISiCT_P102_B1 = crrcRicoMvb->getBool(0xf910,14,5);
    PISiCT_P105_B1 = crrcRicoMvb->getBool(0xf910,15,0);
    PISiCT_P106_B1 = crrcRicoMvb->getBool(0xf910,15,1);
    PISiCT_P107_B1 = crrcRicoMvb->getBool(0xf910,15,2);
    PISiCT_P108_B1 = crrcRicoMvb->getBool(0xf910,15,3);
    PISiCT_P109_B1 = crrcRicoMvb->getBool(0xf910,15,4);
    PISiCT_P110_B1 = crrcRicoMvb->getBool(0xf910,15,5);
    PISiCT_P113_B1 = crrcRicoMvb->getBool(0xf910,16,0);
    PISiCT_P114_B1 = crrcRicoMvb->getBool(0xf910,16,1);
    PISiCT_P115_B1 = crrcRicoMvb->getBool(0xf910,16,2);
    PISiCT_P116_B1 = crrcRicoMvb->getBool(0xf910,16,3);
    PISiCT_P117_B1 = crrcRicoMvb->getBool(0xf910,16,4);
    PISiCT_P118_B1 = crrcRicoMvb->getBool(0xf910,16,5);
    PISiCT_P121_B1 = crrcRicoMvb->getBool(0xf910,17,0);
    PISiCT_P122_B1 = crrcRicoMvb->getBool(0xf910,17,1);
    PISiCT_P123_B1 = crrcRicoMvb->getBool(0xf910,17,2);
    PISiCT_P124_B1 = crrcRicoMvb->getBool(0xf910,17,3);
    PISiCT_P125_B1 = crrcRicoMvb->getBool(0xf910,17,4);
    PISiCT_P126_B1 = crrcRicoMvb->getBool(0xf910,17,5);
    PISiCT_P129_B1 = crrcRicoMvb->getBool(0xf910,18,0);
    PISiCT_P130_B1 = crrcRicoMvb->getBool(0xf910,18,1);
    PISiCT_P131_B1 = crrcRicoMvb->getBool(0xf910,18,2);
    PISiCT_P132_B1 = crrcRicoMvb->getBool(0xf910,18,3);
    PISiCT_P133_B1 = crrcRicoMvb->getBool(0xf910,18,4);
    PISiCT_P134_B1 = crrcRicoMvb->getBool(0xf910,18,5);
    PISiCT_P137_B1 = crrcRicoMvb->getBool(0xf910,19,0);
    PISiCT_P138_B1 = crrcRicoMvb->getBool(0xf910,19,1);
    PISiCT_P139_B1 = crrcRicoMvb->getBool(0xf910,19,2);
    PISiCT_P140_B1 = crrcRicoMvb->getBool(0xf910,19,3);
    PISiCT_P141_B1 = crrcRicoMvb->getBool(0xf910,19,4);
    PISiCT_P142_B1 = crrcRicoMvb->getBool(0xf910,19,5);
    PISiCT_P145_B1 = crrcRicoMvb->getBool(0xf910,20,0);
    PISiCT_P146_B1 = crrcRicoMvb->getBool(0xf910,20,1);
    PISiCT_P147_B1 = crrcRicoMvb->getBool(0xf910,20,2);
    PISiCT_P148_B1 = crrcRicoMvb->getBool(0xf910,20,3);
    PISiCT_P149_B1 = crrcRicoMvb->getBool(0xf910,20,4);
    PISiCT_P150_B1 = crrcRicoMvb->getBool(0xf910,20,5);
    PISiCT_P153_B1 = crrcRicoMvb->getBool(0xf910,21,0);
    PISiCT_P154_B1 = crrcRicoMvb->getBool(0xf910,21,1);
    PISiCT_P155_B1 = crrcRicoMvb->getBool(0xf910,21,2);
    PISiCT_P156_B1 = crrcRicoMvb->getBool(0xf910,21,3);
    PISiCT_P157_B1 = crrcRicoMvb->getBool(0xf910,21,4);
    PISiCT_P158_B1 = crrcRicoMvb->getBool(0xf910,21,5);
    PISiCT_P161_B1 = crrcRicoMvb->getBool(0xf910,22,0);
    PISiCT_P162_B1 = crrcRicoMvb->getBool(0xf910,22,1);
    PISiCT_P163_B1 = crrcRicoMvb->getBool(0xf910,22,2);
    PISiCT_P164_B1 = crrcRicoMvb->getBool(0xf910,22,3);
    PISiCT_P165_B1 = crrcRicoMvb->getBool(0xf910,22,4);
    PISiCT_P166_B1 = crrcRicoMvb->getBool(0xf910,22,5);
    PISiCT_P169_B1 = crrcRicoMvb->getBool(0xf910,23,0);
    PISiCT_P170_B1 = crrcRicoMvb->getBool(0xf910,23,1);
    PISiCT_P171_B1 = crrcRicoMvb->getBool(0xf910,23,2);
    PISiCT_P172_B1 = crrcRicoMvb->getBool(0xf910,23,3);
    PISiCT_P173_B1 = crrcRicoMvb->getBool(0xf910,23,4);
    PISiCT_P174_B1 = crrcRicoMvb->getBool(0xf910,23,5);




    //*******************************************HVAC-CCU***********************************************//
    ACVP1CT_IxVentFrqCnvtPrt1_B1 = crrcRicoMvb->getBool(0xA10,16,0);
    ACVP1CT_IxVentFrqCnvtComFlt1_B1 = crrcRicoMvb->getBool(0xA10,16,1);
    ACVP1CT_IxEmcyVentIntComFlt1_B1 = crrcRicoMvb->getBool(0xA10,16,2);
    ACVP1CT_IxCondMotorFlt11_B1 = crrcRicoMvb->getBool(0xA10,16,3);
    ACVP1CT_IxCondMotorFlt12_B1 = crrcRicoMvb->getBool(0xA10,16,4);
    ACVP1CT_IxEmcyVentIntPrt1_B1 = crrcRicoMvb->getBool(0xA10,16,5);
    ACVP1CT_IxRASnsFlt1_B1 = crrcRicoMvb->getBool(0xA10,16,6);
    ACVP1CT_IxFASnsFlt1_B1 = crrcRicoMvb->getBool(0xA10,16,7);
    ACVP1CT_IxDeloadFshU1_B1 = crrcRicoMvb->getBool(0xA10,17,0);
    ACVP1CT_IxDeloadFshU2_B1 = crrcRicoMvb->getBool(0xA10,17,1);
    ACVP1CT_IxHVACMSSts_B1 = crrcRicoMvb->getBool(0xA10,17,2);
    ACVP1CT_IxIOBoardComFlt1_B1 = crrcRicoMvb->getBool(0xA10,18,1);
    ACVP1CT_IxCmpFrqCnvsComFlt11_B1 = crrcRicoMvb->getBool(0xA10,18,2);
    ACVP1CT_IxCmpFrqCnvsComFlt12_B1 = crrcRicoMvb->getBool(0xA10,18,3);
    ACVP1CT_IxFADamperFlt11_B1 = crrcRicoMvb->getBool(0xA10,18,4);
    ACVP1CT_IxFADamperFlt12_B1 = crrcRicoMvb->getBool(0xA10,18,5);
    ACVP1CT_IxRADamperFlt1_B1 = crrcRicoMvb->getBool(0xA10,18,6);
    ACVP1CT_IxCmpFrqCnvtPrt11_B1 = crrcRicoMvb->getBool(0xA10,19,0);
    ACVP1CT_IxCmpFrqCnvtPrt12_B1 = crrcRicoMvb->getBool(0xA10,19,1);
    ACVP1CT_IxCmpOverloadPrt11_B1 = crrcRicoMvb->getBool(0xA10,19,2);
    ACVP1CT_IxCmpOverloadPrt12_B1 = crrcRicoMvb->getBool(0xA10,19,3);
    ACVP1CT_IxCmpHVFlt11_B1 = crrcRicoMvb->getBool(0xA10,19,4);
    ACVP1CT_IxCmpHVFlt12_B1 = crrcRicoMvb->getBool(0xA10,19,5);
    ACVP1CT_IxCmpLVFlt11_B1 = crrcRicoMvb->getBool(0xA10,19,6);
    ACVP1CT_IxCmpLVFlt12_B1 = crrcRicoMvb->getBool(0xA10,19,7);
    ACVP1CT_IxVentFrqCnvtPrt2_B1 = crrcRicoMvb->getBool(0xA10,20,0);
    ACVP1CT_IxVentFrqCnvtComFlt2_B1 = crrcRicoMvb->getBool(0xA10,20,1);
    ACVP1CT_IxEmcyVentIntComFlt2_B1 = crrcRicoMvb->getBool(0xA10,20,2);
    ACVP1CT_IxCondMotorFlt21_B1 = crrcRicoMvb->getBool(0xA10,20,3);
    ACVP1CT_IxCondMotorFlt22_B1 = crrcRicoMvb->getBool(0xA10,20,4);
    ACVP1CT_IxEmcyVentIntPrt2_B1 = crrcRicoMvb->getBool(0xA10,20,5);
    ACVP1CT_IxRASnsFlt2_B1 = crrcRicoMvb->getBool(0xA10,20,6);
    ACVP1CT_IxFASnsFlt2_B1 = crrcRicoMvb->getBool(0xA10,20,7);
    ACVP1CT_IxIOBoardComFlt2_B1 = crrcRicoMvb->getBool(0xA10,22,1);
    ACVP1CT_IxCmpFrqCnvsComFlt21_B1 = crrcRicoMvb->getBool(0xA10,22,2);
    ACVP1CT_IxCmpFrqCnvsComFlt22_B1 = crrcRicoMvb->getBool(0xA10,22,3);
    ACVP1CT_IxFADamperFlt21_B1 = crrcRicoMvb->getBool(0xA10,22,4);
    ACVP1CT_IxFADamperFlt22_B1 = crrcRicoMvb->getBool(0xA10,22,5);
    ACVP1CT_IxRADamperFlt2_B1 = crrcRicoMvb->getBool(0xA10,22,6);
    ACVP1CT_IxCmpFrqCnvtPrt21_B1 = crrcRicoMvb->getBool(0xA10,23,0);
    ACVP1CT_IxCmpFrqCnvtPrt22_B1 = crrcRicoMvb->getBool(0xA10,23,1);
    ACVP1CT_IxCmpOverloadPrt21_B1 = crrcRicoMvb->getBool(0xA10,23,2);
    ACVP1CT_IxCmpOverloadPrt22_B1 = crrcRicoMvb->getBool(0xA10,23,3);
    ACVP1CT_IxCmpHVFlt21_B1 = crrcRicoMvb->getBool(0xA10,23,4);
    ACVP1CT_IxCmpHVFlt22_B1 = crrcRicoMvb->getBool(0xA10,23,5);
    ACVP1CT_IxCmpLVFlt21_B1 = crrcRicoMvb->getBool(0xA10,23,6);
    ACVP1CT_IxCmpLVFlt22_B1 = crrcRicoMvb->getBool(0xA10,23,7);
    ACVP1CT_IxMinorFlt_B1 = crrcRicoMvb->getBool(0xA10,25,1);
    ACVP1CT_IxMediumFlt_B1 = crrcRicoMvb->getBool(0xA10,25,2);
    ACVP1CT_IxMajorFlt_B1 = crrcRicoMvb->getBool(0xA10,25,3);
    ACVP1CT_IxAirCleaner1Flt_B1 = crrcRicoMvb->getBool(0xA10,25,4);
    ACVP1CT_IxAirCleaner2Flt_B1 = crrcRicoMvb->getBool(0xA10,25,5);
    ACVP2CT_IxVentFrqCnvtPrt1_B1 = crrcRicoMvb->getBool(0xA20,16,0);
    ACVP2CT_IxVentFrqCnvtComFlt1_B1 = crrcRicoMvb->getBool(0xA20,16,1);
    ACVP2CT_IxEmcyVentIntComFlt1_B1 = crrcRicoMvb->getBool(0xA20,16,2);
    ACVP2CT_IxCondMotorFlt11_B1 = crrcRicoMvb->getBool(0xA20,16,3);
    ACVP2CT_IxCondMotorFlt12_B1 = crrcRicoMvb->getBool(0xA20,16,4);
    ACVP2CT_IxEmcyVentIntPrt1_B1 = crrcRicoMvb->getBool(0xA20,16,5);
    ACVP2CT_IxRASnsFlt1_B1 = crrcRicoMvb->getBool(0xA20,16,6);
    ACVP2CT_IxFASnsFlt1_B1 = crrcRicoMvb->getBool(0xA20,16,7);
    ACVP2CT_IxDeloadFshU1_B1 = crrcRicoMvb->getBool(0xA20,17,0);
    ACVP2CT_IxDeloadFshU2_B1 = crrcRicoMvb->getBool(0xA20,17,1);
    ACVP2CT_IxHVACMSSts_B1 = crrcRicoMvb->getBool(0xA20,17,2);
    ACVP2CT_IxIOBoardComFlt1_B1 = crrcRicoMvb->getBool(0xA20,18,1);
    ACVP2CT_IxCmpFrqCnvsComFlt11_B1 = crrcRicoMvb->getBool(0xA20,18,2);
    ACVP2CT_IxCmpFrqCnvsComFlt12_B1 = crrcRicoMvb->getBool(0xA20,18,3);
    ACVP2CT_IxFADamperFlt11_B1 = crrcRicoMvb->getBool(0xA20,18,4);
    ACVP2CT_IxFADamperFlt12_B1 = crrcRicoMvb->getBool(0xA20,18,5);
    ACVP2CT_IxRADamperFlt1_B1 = crrcRicoMvb->getBool(0xA20,18,6);
    ACVP2CT_IxCmpFrqCnvtPrt11_B1 = crrcRicoMvb->getBool(0xA20,19,0);
    ACVP2CT_IxCmpFrqCnvtPrt12_B1 = crrcRicoMvb->getBool(0xA20,19,1);
    ACVP2CT_IxCmpOverloadPrt11_B1 = crrcRicoMvb->getBool(0xA20,19,2);
    ACVP2CT_IxCmpOverloadPrt12_B1 = crrcRicoMvb->getBool(0xA20,19,3);
    ACVP2CT_IxCmpHVFlt11_B1 = crrcRicoMvb->getBool(0xA20,19,4);
    ACVP2CT_IxCmpHVFlt12_B1 = crrcRicoMvb->getBool(0xA20,19,5);
    ACVP2CT_IxCmpLVFlt11_B1 = crrcRicoMvb->getBool(0xA20,19,6);
    ACVP2CT_IxCmpLVFlt12_B1 = crrcRicoMvb->getBool(0xA20,19,7);
    ACVP2CT_IxVentFrqCnvtPrt2_B1 = crrcRicoMvb->getBool(0xA20,20,0);
    ACVP2CT_IxVentFrqCnvtComFlt2_B1 = crrcRicoMvb->getBool(0xA20,20,1);
    ACVP2CT_IxEmcyVentIntComFlt2_B1 = crrcRicoMvb->getBool(0xA20,20,2);
    ACVP2CT_IxCondMotorFlt21_B1 = crrcRicoMvb->getBool(0xA20,20,3);
    ACVP2CT_IxCondMotorFlt22_B1 = crrcRicoMvb->getBool(0xA20,20,4);
    ACVP2CT_IxEmcyVentIntPrt2_B1 = crrcRicoMvb->getBool(0xA20,20,5);
    ACVP2CT_IxRASnsFlt2_B1 = crrcRicoMvb->getBool(0xA20,20,6);
    ACVP2CT_IxFASnsFlt2_B1 = crrcRicoMvb->getBool(0xA20,20,7);
    ACVP2CT_IxIOBoardComFlt2_B1 = crrcRicoMvb->getBool(0xA20,22,1);
    ACVP2CT_IxCmpFrqCnvsComFlt21_B1 = crrcRicoMvb->getBool(0xA20,22,2);
    ACVP2CT_IxCmpFrqCnvsComFlt22_B1 = crrcRicoMvb->getBool(0xA20,22,3);
    ACVP2CT_IxFADamperFlt21_B1 = crrcRicoMvb->getBool(0xA20,22,4);
    ACVP2CT_IxFADamperFlt22_B1 = crrcRicoMvb->getBool(0xA20,22,5);
    ACVP2CT_IxRADamperFlt2_B1 = crrcRicoMvb->getBool(0xA20,22,6);
    ACVP2CT_IxCmpFrqCnvtPrt21_B1 = crrcRicoMvb->getBool(0xA20,23,0);
    ACVP2CT_IxCmpFrqCnvtPrt22_B1 = crrcRicoMvb->getBool(0xA20,23,1);
    ACVP2CT_IxCmpOverloadPrt21_B1 = crrcRicoMvb->getBool(0xA20,23,2);
    ACVP2CT_IxCmpOverloadPrt22_B1 = crrcRicoMvb->getBool(0xA20,23,3);
    ACVP2CT_IxCmpHVFlt21_B1 = crrcRicoMvb->getBool(0xA20,23,4);
    ACVP2CT_IxCmpHVFlt22_B1 = crrcRicoMvb->getBool(0xA20,23,5);
    ACVP2CT_IxCmpLVFlt21_B1 = crrcRicoMvb->getBool(0xA20,23,6);
    ACVP2CT_IxCmpLVFlt22_B1 = crrcRicoMvb->getBool(0xA20,23,7);
    ACVP2CT_IxMinorFlt_B1 = crrcRicoMvb->getBool(0xA20,25,1);
    ACVP2CT_IxMediumFlt_B1 = crrcRicoMvb->getBool(0xA20,25,2);
    ACVP2CT_IxMajorFlt_B1 = crrcRicoMvb->getBool(0xA20,25,3);
    ACVP2CT_IxAirCleaner1Flt_B1 = crrcRicoMvb->getBool(0xA20,25,4);
    ACVP2CT_IxAirCleaner2Flt_B1 = crrcRicoMvb->getBool(0xA20,25,5);
    ACVP3CT_IxVentFrqCnvtPrt1_B1 = crrcRicoMvb->getBool(0xA30,16,0);
    ACVP3CT_IxVentFrqCnvtComFlt1_B1 = crrcRicoMvb->getBool(0xA30,16,1);
    ACVP3CT_IxEmcyVentIntComFlt1_B1 = crrcRicoMvb->getBool(0xA30,16,2);
    ACVP3CT_IxCondMotorFlt11_B1 = crrcRicoMvb->getBool(0xA30,16,3);
    ACVP3CT_IxCondMotorFlt12_B1 = crrcRicoMvb->getBool(0xA30,16,4);
    ACVP3CT_IxEmcyVentIntPrt1_B1 = crrcRicoMvb->getBool(0xA30,16,5);
    ACVP3CT_IxRASnsFlt1_B1 = crrcRicoMvb->getBool(0xA30,16,6);
    ACVP3CT_IxFASnsFlt1_B1 = crrcRicoMvb->getBool(0xA30,16,7);
    ACVP3CT_IxDeloadFshU1_B1 = crrcRicoMvb->getBool(0xA30,17,0);
    ACVP3CT_IxDeloadFshU2_B1 = crrcRicoMvb->getBool(0xA30,17,1);
    ACVP3CT_IxHVACMSSts_B1 = crrcRicoMvb->getBool(0xA30,17,2);
    ACVP3CT_IxIOBoardComFlt1_B1 = crrcRicoMvb->getBool(0xA30,18,1);
    ACVP3CT_IxCmpFrqCnvsComFlt11_B1 = crrcRicoMvb->getBool(0xA30,18,2);
    ACVP3CT_IxCmpFrqCnvsComFlt12_B1 = crrcRicoMvb->getBool(0xA30,18,3);
    ACVP3CT_IxFADamperFlt11_B1 = crrcRicoMvb->getBool(0xA30,18,4);
    ACVP3CT_IxFADamperFlt12_B1 = crrcRicoMvb->getBool(0xA30,18,5);
    ACVP3CT_IxRADamperFlt1_B1 = crrcRicoMvb->getBool(0xA30,18,6);
    ACVP3CT_IxCmpFrqCnvtPrt11_B1 = crrcRicoMvb->getBool(0xA30,19,0);
    ACVP3CT_IxCmpFrqCnvtPrt12_B1 = crrcRicoMvb->getBool(0xA30,19,1);
    ACVP3CT_IxCmpOverloadPrt11_B1 = crrcRicoMvb->getBool(0xA30,19,2);
    ACVP3CT_IxCmpOverloadPrt12_B1 = crrcRicoMvb->getBool(0xA30,19,3);
    ACVP3CT_IxCmpHVFlt11_B1 = crrcRicoMvb->getBool(0xA30,19,4);
    ACVP3CT_IxCmpHVFlt12_B1 = crrcRicoMvb->getBool(0xA30,19,5);
    ACVP3CT_IxCmpLVFlt11_B1 = crrcRicoMvb->getBool(0xA30,19,6);
    ACVP3CT_IxCmpLVFlt12_B1 = crrcRicoMvb->getBool(0xA30,19,7);
    ACVP3CT_IxVentFrqCnvtPrt2_B1 = crrcRicoMvb->getBool(0xA30,20,0);
    ACVP3CT_IxVentFrqCnvtComFlt2_B1 = crrcRicoMvb->getBool(0xA30,20,1);
    ACVP3CT_IxEmcyVentIntComFlt2_B1 = crrcRicoMvb->getBool(0xA30,20,2);
    ACVP3CT_IxCondMotorFlt21_B1 = crrcRicoMvb->getBool(0xA30,20,3);
    ACVP3CT_IxCondMotorFlt22_B1 = crrcRicoMvb->getBool(0xA30,20,4);
    ACVP3CT_IxEmcyVentIntPrt2_B1 = crrcRicoMvb->getBool(0xA30,20,5);
    ACVP3CT_IxRASnsFlt2_B1 = crrcRicoMvb->getBool(0xA30,20,6);
    ACVP3CT_IxFASnsFlt2_B1 = crrcRicoMvb->getBool(0xA30,20,7);
    ACVP3CT_IxIOBoardComFlt2_B1 = crrcRicoMvb->getBool(0xA30,22,1);
    ACVP3CT_IxCmpFrqCnvsComFlt21_B1 = crrcRicoMvb->getBool(0xA30,22,2);
    ACVP3CT_IxCmpFrqCnvsComFlt22_B1 = crrcRicoMvb->getBool(0xA30,22,3);
    ACVP3CT_IxFADamperFlt21_B1 = crrcRicoMvb->getBool(0xA30,22,4);
    ACVP3CT_IxFADamperFlt22_B1 = crrcRicoMvb->getBool(0xA30,22,5);
    ACVP3CT_IxRADamperFlt2_B1 = crrcRicoMvb->getBool(0xA30,22,6);
    ACVP3CT_IxCmpFrqCnvtPrt21_B1 = crrcRicoMvb->getBool(0xA30,23,0);
    ACVP3CT_IxCmpFrqCnvtPrt22_B1 = crrcRicoMvb->getBool(0xA30,23,1);
    ACVP3CT_IxCmpOverloadPrt21_B1 = crrcRicoMvb->getBool(0xA30,23,2);
    ACVP3CT_IxCmpOverloadPrt22_B1 = crrcRicoMvb->getBool(0xA30,23,3);
    ACVP3CT_IxCmpHVFlt21_B1 = crrcRicoMvb->getBool(0xA30,23,4);
    ACVP3CT_IxCmpHVFlt22_B1 = crrcRicoMvb->getBool(0xA30,23,5);
    ACVP3CT_IxCmpLVFlt21_B1 = crrcRicoMvb->getBool(0xA30,23,6);
    ACVP3CT_IxCmpLVFlt22_B1 = crrcRicoMvb->getBool(0xA30,23,7);
    ACVP3CT_IxMinorFlt_B1 = crrcRicoMvb->getBool(0xA30,25,1);
    ACVP3CT_IxMediumFlt_B1 = crrcRicoMvb->getBool(0xA30,25,2);
    ACVP3CT_IxMajorFlt_B1 = crrcRicoMvb->getBool(0xA30,25,3);
    ACVP3CT_IxAirCleaner1Flt_B1 = crrcRicoMvb->getBool(0xA30,25,4);
    ACVP3CT_IxAirCleaner2Flt_B1 = crrcRicoMvb->getBool(0xA30,25,5);
    ACVP4CT_IxVentFrqCnvtPrt1_B1 = crrcRicoMvb->getBool(0xA40,16,0);
    ACVP4CT_IxVentFrqCnvtComFlt1_B1 = crrcRicoMvb->getBool(0xA40,16,1);
    ACVP4CT_IxEmcyVentIntComFlt1_B1 = crrcRicoMvb->getBool(0xA40,16,2);
    ACVP4CT_IxCondMotorFlt11_B1 = crrcRicoMvb->getBool(0xA40,16,3);
    ACVP4CT_IxCondMotorFlt12_B1 = crrcRicoMvb->getBool(0xA40,16,4);
    ACVP4CT_IxEmcyVentIntPrt1_B1 = crrcRicoMvb->getBool(0xA40,16,5);
    ACVP4CT_IxRASnsFlt1_B1 = crrcRicoMvb->getBool(0xA40,16,6);
    ACVP4CT_IxFASnsFlt1_B1 = crrcRicoMvb->getBool(0xA40,16,7);
    ACVP4CT_IxDeloadFshU1_B1 = crrcRicoMvb->getBool(0xA40,17,0);
    ACVP4CT_IxDeloadFshU2_B1 = crrcRicoMvb->getBool(0xA40,17,1);
    ACVP4CT_IxHVACMSSts_B1 = crrcRicoMvb->getBool(0xA40,17,2);
    ACVP4CT_IxIOBoardComFlt1_B1 = crrcRicoMvb->getBool(0xA40,18,1);
    ACVP4CT_IxCmpFrqCnvsComFlt11_B1 = crrcRicoMvb->getBool(0xA40,18,2);
    ACVP4CT_IxCmpFrqCnvsComFlt12_B1 = crrcRicoMvb->getBool(0xA40,18,3);
    ACVP4CT_IxFADamperFlt11_B1 = crrcRicoMvb->getBool(0xA40,18,4);
    ACVP4CT_IxFADamperFlt12_B1 = crrcRicoMvb->getBool(0xA40,18,5);
    ACVP4CT_IxRADamperFlt1_B1 = crrcRicoMvb->getBool(0xA40,18,6);
    ACVP4CT_IxCmpFrqCnvtPrt11_B1 = crrcRicoMvb->getBool(0xA40,19,0);
    ACVP4CT_IxCmpFrqCnvtPrt12_B1 = crrcRicoMvb->getBool(0xA40,19,1);
    ACVP4CT_IxCmpOverloadPrt11_B1 = crrcRicoMvb->getBool(0xA40,19,2);
    ACVP4CT_IxCmpOverloadPrt12_B1 = crrcRicoMvb->getBool(0xA40,19,3);
    ACVP4CT_IxCmpHVFlt11_B1 = crrcRicoMvb->getBool(0xA40,19,4);
    ACVP4CT_IxCmpHVFlt12_B1 = crrcRicoMvb->getBool(0xA40,19,5);
    ACVP4CT_IxCmpLVFlt11_B1 = crrcRicoMvb->getBool(0xA40,19,6);
    ACVP4CT_IxCmpLVFlt12_B1 = crrcRicoMvb->getBool(0xA40,19,7);
    ACVP4CT_IxVentFrqCnvtPrt2_B1 = crrcRicoMvb->getBool(0xA40,20,0);
    ACVP4CT_IxVentFrqCnvtComFlt2_B1 = crrcRicoMvb->getBool(0xA40,20,1);
    ACVP4CT_IxEmcyVentIntComFlt2_B1 = crrcRicoMvb->getBool(0xA40,20,2);
    ACVP4CT_IxCondMotorFlt21_B1 = crrcRicoMvb->getBool(0xA40,20,3);
    ACVP4CT_IxCondMotorFlt22_B1 = crrcRicoMvb->getBool(0xA40,20,4);
    ACVP4CT_IxEmcyVentIntPrt2_B1 = crrcRicoMvb->getBool(0xA40,20,5);
    ACVP4CT_IxRASnsFlt2_B1 = crrcRicoMvb->getBool(0xA40,20,6);
    ACVP4CT_IxFASnsFlt2_B1 = crrcRicoMvb->getBool(0xA40,20,7);
    ACVP4CT_IxIOBoardComFlt2_B1 = crrcRicoMvb->getBool(0xA40,22,1);
    ACVP4CT_IxCmpFrqCnvsComFlt21_B1 = crrcRicoMvb->getBool(0xA40,22,2);
    ACVP4CT_IxCmpFrqCnvsComFlt22_B1 = crrcRicoMvb->getBool(0xA40,22,3);
    ACVP4CT_IxFADamperFlt21_B1 = crrcRicoMvb->getBool(0xA40,22,4);
    ACVP4CT_IxFADamperFlt22_B1 = crrcRicoMvb->getBool(0xA40,22,5);
    ACVP4CT_IxRADamperFlt2_B1 = crrcRicoMvb->getBool(0xA40,22,6);
    ACVP4CT_IxCmpFrqCnvtPrt21_B1 = crrcRicoMvb->getBool(0xA40,23,0);
    ACVP4CT_IxCmpFrqCnvtPrt22_B1 = crrcRicoMvb->getBool(0xA40,23,1);
    ACVP4CT_IxCmpOverloadPrt21_B1 = crrcRicoMvb->getBool(0xA40,23,2);
    ACVP4CT_IxCmpOverloadPrt22_B1 = crrcRicoMvb->getBool(0xA40,23,3);
    ACVP4CT_IxCmpHVFlt21_B1 = crrcRicoMvb->getBool(0xA40,23,4);
    ACVP4CT_IxCmpHVFlt22_B1 = crrcRicoMvb->getBool(0xA40,23,5);
    ACVP4CT_IxCmpLVFlt21_B1 = crrcRicoMvb->getBool(0xA40,23,6);
    ACVP4CT_IxCmpLVFlt22_B1 = crrcRicoMvb->getBool(0xA40,23,7);
    ACVP4CT_IxMinorFlt_B1 = crrcRicoMvb->getBool(0xA40,25,1);
    ACVP4CT_IxMediumFlt_B1 = crrcRicoMvb->getBool(0xA40,25,2);
    ACVP4CT_IxMajorFlt_B1 = crrcRicoMvb->getBool(0xA40,25,3);
    ACVP4CT_IxAirCleaner1Flt_B1 = crrcRicoMvb->getBool(0xA40,25,4);
    ACVP4CT_IxAirCleaner2Flt_B1 = crrcRicoMvb->getBool(0xA40,25,5);


    ACVP1CT_IusSalTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA10,2);
    ACVP1CT_IusExtTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA10,3);
    ACVP1CT_IusFADamperSts12_U8 = crrcRicoMvb->getUnsignedChar(0xA10,4);
    ACVP1CT_IusFADamperSts11_U8 = crrcRicoMvb->getUnsignedChar(0xA10,5);
    ACVP1CT_IusFADamperSts22_U8 = crrcRicoMvb->getUnsignedChar(0xA10,6);
    ACVP1CT_IusFADamperSts21_U8 = crrcRicoMvb->getUnsignedChar(0xA10,7);
    ACVP1CT_IusRADamperSts1_U8 = crrcRicoMvb->getUnsignedChar(0xA10,9);
    ACVP1CT_IusRADamperSts2_U8 = crrcRicoMvb->getUnsignedChar(0xA10,11);
    ACVP1CT_IusUnitSts2_U8 = crrcRicoMvb->getUnsignedChar(0xA10,12);
    ACVP1CT_IusUnitSts1_U8 = crrcRicoMvb->getUnsignedChar(0xA10,13);
    ACVP1CT_IusTargTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA10,30);
    ACVP2CT_IusSalTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA20,2);
    ACVP2CT_IusExtTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA20,3);
    ACVP2CT_IusFADamperSts12_U8 = crrcRicoMvb->getUnsignedChar(0xA20,4);
    ACVP2CT_IusFADamperSts11_U8 = crrcRicoMvb->getUnsignedChar(0xA20,5);
    ACVP2CT_IusFADamperSts22_U8 = crrcRicoMvb->getUnsignedChar(0xA20,6);
    ACVP2CT_IusFADamperSts21_U8 = crrcRicoMvb->getUnsignedChar(0xA20,7);
    ACVP2CT_IusRADamperSts1_U8 = crrcRicoMvb->getUnsignedChar(0xA20,9);
    ACVP2CT_IusRADamperSts2_U8 = crrcRicoMvb->getUnsignedChar(0xA20,11);
    ACVP2CT_IusUnitSts2_U8 = crrcRicoMvb->getUnsignedChar(0xA20,12);
    ACVP2CT_IusUnitSts1_U8 = crrcRicoMvb->getUnsignedChar(0xA20,13);
    ACVP2CT_IusTargTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA20,30);
    ACVP3CT_IusSalTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA30,2);
    ACVP3CT_IusExtTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA30,3);
    ACVP3CT_IusFADamperSts12_U8 = crrcRicoMvb->getUnsignedChar(0xA30,4);
    ACVP3CT_IusFADamperSts11_U8 = crrcRicoMvb->getUnsignedChar(0xA30,5);
    ACVP3CT_IusFADamperSts22_U8 = crrcRicoMvb->getUnsignedChar(0xA30,6);
    ACVP3CT_IusFADamperSts21_U8 = crrcRicoMvb->getUnsignedChar(0xA30,7);
    ACVP3CT_IusRADamperSts1_U8 = crrcRicoMvb->getUnsignedChar(0xA30,9);
    ACVP3CT_IusRADamperSts2_U8 = crrcRicoMvb->getUnsignedChar(0xA30,11);
    ACVP3CT_IusUnitSts2_U8 = crrcRicoMvb->getUnsignedChar(0xA30,12);
    ACVP3CT_IusUnitSts1_U8 = crrcRicoMvb->getUnsignedChar(0xA30,13);
    ACVP3CT_IusTargTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA30,30);
    ACVP4CT_IusSalTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA40,2);
    ACVP4CT_IusExtTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA40,3);
    ACVP4CT_IusFADamperSts12_U8 = crrcRicoMvb->getUnsignedChar(0xA40,4);
    ACVP4CT_IusFADamperSts11_U8 = crrcRicoMvb->getUnsignedChar(0xA40,5);
    ACVP4CT_IusFADamperSts22_U8 = crrcRicoMvb->getUnsignedChar(0xA40,6);
    ACVP4CT_IusFADamperSts21_U8 = crrcRicoMvb->getUnsignedChar(0xA40,7);
    ACVP4CT_IusRADamperSts1_U8 = crrcRicoMvb->getUnsignedChar(0xA40,9);
    ACVP4CT_IusRADamperSts2_U8 = crrcRicoMvb->getUnsignedChar(0xA40,11);
    ACVP4CT_IusUnitSts2_U8 = crrcRicoMvb->getUnsignedChar(0xA40,12);
    ACVP4CT_IusUnitSts1_U8 = crrcRicoMvb->getUnsignedChar(0xA40,13);
    ACVP4CT_IusTargTemp_U8 = crrcRicoMvb->getUnsignedChar(0xA40,30);

    ACVP1CT_IuiDevIsAlive_U16 = crrcRicoMvb->getUnsignedInt(0xA10,0);
    ACVP1CT_IuiHVACSWVersion_U16 = crrcRicoMvb->getUnsignedInt(0xA10,14);
    ACVP2CT_IuiDevIsAlive_U16 = crrcRicoMvb->getUnsignedInt(0xA20,0);
    ACVP2CT_IuiHVACSWVersion_U16 = crrcRicoMvb->getUnsignedInt(0xA20,14);
    ACVP3CT_IuiDevIsAlive_U16 = crrcRicoMvb->getUnsignedInt(0xA30,0);
    ACVP3CT_IuiHVACSWVersion_U16 = crrcRicoMvb->getUnsignedInt(0xA30,14);
    ACVP4CT_IuiDevIsAlive_U16 = crrcRicoMvb->getUnsignedInt(0xA40,0);
    ACVP4CT_IuiHVACSWVersion_U16 = crrcRicoMvb->getUnsignedInt(0xA40,14);


    ACVP1CT_IudHVACCns_U32 = crrcRicoMvb->getUnsignedInt32(0xA10,26);
    ACVP2CT_IudHVACCns_U32 = crrcRicoMvb->getUnsignedInt32(0xA20,26);
    ACVP3CT_IudHVACCns_U32 = crrcRicoMvb->getUnsignedInt32(0xA30,26);
    ACVP4CT_IudHVACCns_U32 = crrcRicoMvb->getUnsignedInt32(0xA40,26);

    //***********************************BMS-CCU*********************************************//
    BMS1CT_SWVERSION_U16=crrcRicoMvb->getUnsignedInt(0xD10,15);
    BMS2CT_SWVERSION_U16=crrcRicoMvb->getUnsignedInt(0xD20,15);
    BMS3CT_SWVERSION_U16=crrcRicoMvb->getUnsignedInt(0xD30,15);
    BMS4CT_SWVERSION_U16=crrcRicoMvb->getUnsignedInt(0xD40,15);

    BMS1CT_FLAG_U8 = crrcRicoMvb->getUnsignedChar(0xD10,12);
    BMS2CT_FLAG_U8 = crrcRicoMvb->getUnsignedChar(0xD20,12);
    BMS3CT_FLAG_U8 = crrcRicoMvb->getUnsignedChar(0xD30,12);
    BMS4CT_FLAG_U8 = crrcRicoMvb->getUnsignedChar(0xD40,12);
    BMS1CT_TMPE_U8 = crrcRicoMvb->getUnsignedChar(0xD10,13);
    BMS2CT_TMPE_U8 = crrcRicoMvb->getUnsignedChar(0xD20,13);
    BMS3CT_TMPE_U8 = crrcRicoMvb->getUnsignedChar(0xD30,13);
    BMS4CT_TMPE_U8 = crrcRicoMvb->getUnsignedChar(0xD40,13);

    //***********************************PAN--CCU*******************************************//
    PANCT_PGHA_B1 = crrcRicoMvb->getBool(0xC10,2,7);
    PANCT_ArcAlarmLevel1_B1 = crrcRicoMvb->getBool(0xC10,2,6);
    PANCT_ArcAlarmLevel2_B1 = crrcRicoMvb->getBool(0xC10,2,5);
    PANCT_ArcAlarmLevel3_B1 = crrcRicoMvb->getBool(0xC10,2,4);
    PANCT_TemperatureAlarmLevel1_B1 = crrcRicoMvb->getBool(0xC10,2,3);
    PANCT_TemperatureAlarmLevel2_B1 = crrcRicoMvb->getBool(0xC10,2,2);
    PANCT_HRCA_B1 = crrcRicoMvb->getBool(0xC10,2,1);
    PANCT_HFCA_B1 = crrcRicoMvb->getBool(0xC10,2,0);
    PANCT_PVRCA_B1 = crrcRicoMvb->getBool(0xC10,3,7);
    PANCT_PVFCA_B1 = crrcRicoMvb->getBool(0xC10,3,6);
    PANCT_DBLA_B1 = crrcRicoMvb->getBool(0xC10,3,5);
    PANCT_DBCA_B1 = crrcRicoMvb->getBool(0xC10,3,4);
    PANCT_SRNC_B1 = crrcRicoMvb->getBool(0xC10,3,3);
    PANCT_SFNC_B1 = crrcRicoMvb->getBool(0xC10,3,2);
    PANCT_SuspensionsystemAbnormal_B1 = crrcRicoMvb->getBool(0xC10,3,1);

    PANCT_PCMUisAlive_U16 = crrcRicoMvb->getUnsignedInt(0xC10,0);


    updateSystemStatus();

    createERMList(this->CTD_ERM1OLINE_B1,this->CTD_ERM2OLINE_B1);

    EiCT_RunningKilometers_U32=crrcRicoMvb->getUnsignedInt32(0xf212,4);
    EiCT_TractionEngyConsumption_U32=crrcRicoMvb->getUnsignedInt32(0xf212,8);
    EiCT_AxPowerEngyConsumption_U32=crrcRicoMvb->getUnsignedInt32(0xf212,12);
    EiCT_ReEngy_U32=crrcRicoMvb->getUnsignedInt32(0xf212,20);
    //
    EiCT_ServiceDistance_U32=crrcRicoMvb->getUnsignedInt32(0xf211,16);

    EiCT_AP1RunningTime_U32=crrcRicoMvb->getUnsignedInt32(0xf212,24);
    EiCT_AP2RunningTime_U32=crrcRicoMvb->getUnsignedInt32(0xf212,28);

    EiCT_TCMSTotalTime_U32=crrcRicoMvb->getUnsignedInt32(0xf211,28);

    EiCT_TotalDistanceYear_U8=crrcRicoMvb->getUnsignedChar(0xf211,7);
    EiCT_TotalDistanceMonth_U8=crrcRicoMvb->getUnsignedChar(0xf211,8);
    EiCT_TotalDistanceDay_U8=crrcRicoMvb->getUnsignedChar(0xf211,9);

    EiCT_TractionECYear_U8=crrcRicoMvb->getUnsignedChar(0xf211,16);
    EiCT_TractionECMonth_U8=crrcRicoMvb->getUnsignedChar(0xf211,17);
    EiCT_TractionECDay_U8=crrcRicoMvb->getUnsignedChar(0xf211,18);

    EiCT_AxPowerECYear_U8=crrcRicoMvb->getUnsignedChar(0xf211,19);
    EiCT_AxPowerECMonth_U8=crrcRicoMvb->getUnsignedChar(0xf211,20);
    EiCT_AxPowerECDay_U8=crrcRicoMvb->getUnsignedChar(0xf211,21);

    EiCT_ReEngyYear_U8=crrcRicoMvb->getUnsignedChar(0xf211,22);
    EiCT_ReEngyMonth_U8=crrcRicoMvb->getUnsignedChar(0xf211,23);
    EiCT_ReEngyDay_U8=crrcRicoMvb->getUnsignedChar(0xf211,24);

    //
    EiCT_ServiceDistanceYear_U8=crrcRicoMvb->getUnsignedChar(0xf212,12);
    EiCT_ServiceDistanceMonth_U8=crrcRicoMvb->getUnsignedChar(0xf212,13);
    EiCT_ServiceDistanceDay_U8=crrcRicoMvb->getUnsignedChar(0xf212,14);

    EiCT_AP1ECYear_U8=crrcRicoMvb->getUnsignedChar(0xf211,10);
    EiCT_AP1ECMonth_U8=crrcRicoMvb->getUnsignedChar(0xf211,11);
    EiCT_AP1ECDay_U8=crrcRicoMvb->getUnsignedChar(0xf211,12);

    EiCT_AP2ECYear_U8=crrcRicoMvb->getUnsignedChar(0xf211,13);
    EiCT_AP2ECMonth_U8=crrcRicoMvb->getUnsignedChar(0xf211,14);
    EiCT_AP2ECDay_U8=crrcRicoMvb->getUnsignedChar(0xf211,15);

    //
    EiCT_TCMSTotalTimeYear_U8=crrcRicoMvb->getUnsignedChar(0xf211,4);
    EiCT_TCMSTotalTimeMonth_U8=crrcRicoMvb->getUnsignedChar(0xf211,5);
    EiCT_TCMSTotalTimeDay_U8=crrcRicoMvb->getUnsignedChar(0xf211,6);

}

void Database::copyPort(unsigned short int sink, unsigned short int source)
{
    for (int i = 0; i < 32; i ++)
    {
        this->crrcRicoMvb->setUnsignedChar(sink, i, this->crrcRicoMvb->getUnsignedChar(source, i));
    }
}

/***********************************************************EDCU**************************************************************/

void Database::createEDCUList(bool edcu1Online, bool edcu2Online, QList<unsigned short> virtualports, QList<unsigned short> realports)
{

  if (realports.size() != 6)
  {
      //_LOG <<virtualports.at(0) <<"EDCU the size of the real ports is not enough";
      return;
  }

  if (virtualports.size() != 3)
  {
      //_LOG << "EDCU the size of the virtual ports is not enough";

      return;
  }
  //virtualport1:7i0 virtualport2:7i1
  unsigned short virtualport1 = virtualports.at(0);
  unsigned short virtualport2 = virtualports.at(1);
  unsigned short virtualport3 = virtualports.at(2);

  //virtualporti_1:7i0 virtualporti_2:7i1
  unsigned short realport1_1 = realports.at(0);
  unsigned short realport1_2 = realports.at(1);
  unsigned short realport1_3 = realports.at(2);
  unsigned short realport2_1 = realports.at(3);
  unsigned short realport2_2 = realports.at(4);
  unsigned short realport2_3 = realports.at(5);

  if (1 == this->crrcRicoMvb->getUnsignedInt(realport1_2, 18)  && true == edcu1Online)     // edcu1 master
  {
      this->copyPort(virtualport1,realport1_1);
      this->copyPort(virtualport2,realport1_2);
      this->copyPort(virtualport3,realport1_3);
  }
  else if (1 == this->crrcRicoMvb->getUnsignedInt(realport2_2, 18) && true == edcu2Online)   // edcu2 master
  {
      this->copyPort(virtualport1,realport2_1);
      this->copyPort(virtualport2,realport2_2);
      this->copyPort(virtualport3,realport2_3);
  }else
  {

      // 门1 trust
      if (this->crrcRicoMvb->getBool(realport1_2, 22, 0) && true == edcu1Online )//门控器1-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,2,this->crrcRicoMvb->getUnsignedChar(realport1_2,2));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,3,this->crrcRicoMvb->getUnsignedChar(realport1_2,3));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,0,this->crrcRicoMvb->getUnsignedInt(realport1_3,0));

      }
      else if (this->crrcRicoMvb->getBool(realport2_2, 22, 0) && true == edcu2Online)//门控器2-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,2,this->crrcRicoMvb->getUnsignedChar(realport2_2,2));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,3,this->crrcRicoMvb->getUnsignedChar(realport2_2,3));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,0,this->crrcRicoMvb->getUnsignedInt(realport2_3,0));

      }else
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,2,0);
          this->crrcRicoMvb->setUnsignedChar(virtualport2,3,0);
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,0,0);
      }

      // 门2 trust
      if (this->crrcRicoMvb->getBool(realport1_2, 22, 1) && true == edcu1Online )//门控器1-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,4,this->crrcRicoMvb->getUnsignedChar(realport1_2,4));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,5,this->crrcRicoMvb->getUnsignedChar(realport1_2,5));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,2,this->crrcRicoMvb->getUnsignedInt(realport1_3,2));

      }
      else if (this->crrcRicoMvb->getBool(realport2_2, 22, 1) && true == edcu2Online)//门控器2-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,4,this->crrcRicoMvb->getUnsignedChar(realport2_2,4));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,5,this->crrcRicoMvb->getUnsignedChar(realport2_2,5));
          //version
          this->crrcRicoMvb->setUnsignedChar(virtualport3,2,this->crrcRicoMvb->getUnsignedInt(realport2_3,2));

      }else
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,4,0);
          this->crrcRicoMvb->setUnsignedChar(virtualport2,5,0);
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,2,0);
      }

      // 门3 trust
      if (this->crrcRicoMvb->getBool(realport1_2, 22, 2) && true == edcu1Online )//门控器1-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,6,this->crrcRicoMvb->getUnsignedChar(realport1_2,6));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,7,this->crrcRicoMvb->getUnsignedChar(realport1_2,7));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,4,this->crrcRicoMvb->getUnsignedInt(realport1_3,4));

      }
      else if (this->crrcRicoMvb->getBool(realport2_2, 22, 2) && true == edcu2Online)//门控器2-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,6,this->crrcRicoMvb->getUnsignedChar(realport2_2,6));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,7,this->crrcRicoMvb->getUnsignedChar(realport2_2,7));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,5,this->crrcRicoMvb->getUnsignedInt(realport2_3,5));

      }else
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,6,0);
          this->crrcRicoMvb->setUnsignedChar(virtualport2,7,0);
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,4,0);
      }

      // 门4 trust
      if (this->crrcRicoMvb->getBool(realport1_2, 22, 3) && true == edcu1Online )//门控器1-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,8,this->crrcRicoMvb->getUnsignedChar(realport1_2,8));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,9,this->crrcRicoMvb->getUnsignedChar(realport1_2,9));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,6,this->crrcRicoMvb->getUnsignedInt(realport1_3,6));

      }
      else if (this->crrcRicoMvb->getBool(realport2_2, 22, 3) && true == edcu2Online)//门控器2-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,8,this->crrcRicoMvb->getUnsignedChar(realport2_2,8));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,9,this->crrcRicoMvb->getUnsignedChar(realport2_2,9));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,6,this->crrcRicoMvb->getUnsignedInt(realport2_3,6));

      }else
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,8,0);
          this->crrcRicoMvb->setUnsignedChar(virtualport2,9,0);
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,6,0);
      }

      // 门5 trust
      if (this->crrcRicoMvb->getBool(realport1_2, 22, 4) && true == edcu1Online )//门控器1-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,10,this->crrcRicoMvb->getUnsignedChar(realport1_2,10));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,11,this->crrcRicoMvb->getUnsignedChar(realport1_2,11));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,8,this->crrcRicoMvb->getUnsignedInt(realport1_3,8));

      }
      else if (this->crrcRicoMvb->getBool(realport2_2, 22, 4) && true == edcu2Online)//门控器2-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,10,this->crrcRicoMvb->getUnsignedChar(realport2_2,10));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,11,this->crrcRicoMvb->getUnsignedChar(realport2_2,11));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,8,this->crrcRicoMvb->getUnsignedInt(realport2_3,8));

      }else
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,10,0);
          this->crrcRicoMvb->setUnsignedChar(virtualport2,11,0);
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,8,0);
      }


      // 门6 trust
      if (this->crrcRicoMvb->getBool(realport1_2, 22, 5) && true == edcu1Online )//门控器1-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,12,this->crrcRicoMvb->getUnsignedChar(realport1_2,12));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,13,this->crrcRicoMvb->getUnsignedChar(realport1_2,13));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,10,this->crrcRicoMvb->getUnsignedInt(realport1_3,10));

      }
      else if (this->crrcRicoMvb->getBool(realport2_2, 22, 5) && true == edcu2Online)//门控器2-1有效
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,12,this->crrcRicoMvb->getUnsignedChar(realport2_2,12));
          this->crrcRicoMvb->setUnsignedChar(virtualport2,13,this->crrcRicoMvb->getUnsignedChar(realport2_2,13));
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,10,this->crrcRicoMvb->getUnsignedInt(realport2_3,10));

      }else
      {
          //state
          this->crrcRicoMvb->setUnsignedChar(virtualport2,12,0);
          this->crrcRicoMvb->setUnsignedChar(virtualport2,13,0);
          //version
          this->crrcRicoMvb->setUnsignedInt(virtualport3,10,0);
      }
  }
}


void Database::createBCUList( QList<unsigned short> virtualports, QList<unsigned short> realports)
{
    if (realports.size() != 14)
    {
        //_LOG << "EBCU the size of the real ports is not enough";

        return;
    }

    if (virtualports.size() != 7)
    {
        //_LOG << "EBCU the size of the virtual ports is not enough";

        return;
    }


    for(int i=0;i<7;i++)
    {
        if(CTD_BCU1OLINE_B1&&CTD_BCU1Trust_B1)
        {
            this->copyPort(virtualports.at(i),realports.at(i));
        }
        else if(CTD_BCU2OLINE_B1&&CTD_BCU2Trust_B1)
        {
            this->copyPort(virtualports.at(i),realports.at(i+7));
        }
        else
        {
            this->copyPort( virtualports.at(i),0xfff);
        }
    }


}


void Database::updateSystemStatus()
{

    long HAVCFaultFlag=0;
    long SIVFaultFlag=0;
    long VVVFFaultFlag=0;
    long PISAllFaultFlag=0;
    long EDCUFaultFlag=0;
    long BCUFaultFlag=0;

    HAVCFaultFlag=getAllHVACFault();
    SIVFaultFlag=getAllSIVFault();
    VVVFFaultFlag=getAllVVVFFault();
    PISAllFaultFlag=getAllPISFault();
    EDCUFaultFlag=getAllEDCUFault();
    BCUFaultFlag=getAllBCUFault();

  //HVAC
  if(
     !this->CTD_ACTOLINE_B1 ||!this->CTD_AC2OLINE_B1 ||!this->CTD_AC3OLINE_B1 ||
     !this->CTD_AC4OLINE_B1||(HAVCFaultFlag!=0))
  {
      Status_HVAC = 2;
  }else if(0)
  {
      Status_HVAC = 1;
  }else
  {
      Status_HVAC = 0;
  }

  //SIV
  if(!this->CTD_ACU1OLINE_B1 ||!this->CTD_ACU2OLINE_B1
     ||this->ACU1CT_IxSIVMajorF_B1||this->ACU2CT_IxSIVMajorF_B1
     ||(SIVFaultFlag!=0)
     )
  {
      Status_SIV = 2;
  }else if(0)
  {
      Status_SIV = 1;
  }else
  {
      Status_SIV = 0;
  }

  //EDCU
  if(!this->CTD_EDCU1OLINE_B1 ||!this->CTD_EDCU2OLINE_B1 ||!this->CTD_EDCU3OLINE_B1 ||
          !this->CTD_EDCU4OLINE_B1 ||!this->CTD_EDCU5OLINE_B1 ||!this->CTD_EDCU6OLINE_B1 ||
          !this->CTD_EDCU7OLINE_B1 ||!this->CTD_EDCU8OLINE_B1
          ||(EDCUFaultFlag!=0))
  {
      Status_EDCU = 2;
  }else if(0)
  {
      Status_EDCU = 1;
  }else
  {
      Status_EDCU = 0;
  }
  //PIS]

  long PISFaultFlag=0;
  PISFaultFlag=crrcRicoMvb->getUnsignedInt(0x910,16)+crrcRicoMvb->getUnsignedInt(0x910,17)+
          crrcRicoMvb->getUnsignedInt(0x910,18)+crrcRicoMvb->getUnsignedInt(0x910,19)+

          crrcRicoMvb->getUnsignedInt(0x920,16)+crrcRicoMvb->getUnsignedInt(0x920,17)+
          crrcRicoMvb->getUnsignedInt(0x920,18)+crrcRicoMvb->getUnsignedInt(0x920,19);

  if(!this->CTD_PIS1OLINE_B1 || !this->CTD_PIS2OLINE_B1||(PISAllFaultFlag!=0)
     )
  {
      Status_PIS = 2;
  }else if(
           PISFaultFlag
           )
  {
      Status_PIS = 1;
  }else
  {
      Status_PIS = 0;
  }

  //BCU
  if(!this->CTD_BCU1OLINE_B1||!this->CTD_BCU2OLINE_B1
     ||(BCUFaultFlag!=0)
     )
  {
      Status_BCU = 2;
  }else if(//qiechu

          (this->BiCT_EDCtOffMC1Bg2_B1)||(this->BiCT_EDCtOffMP1Bg1_B1)||
          (this->BiCT_EDCtOffMP1Bg2_B1)||(this->BiCT_EDCtOffMP2Bg1_B1)||
          (this->BiCT_EDCtOffMP2Bg2_B1)||(this->BiCT_EDCtOffMC2Bg2_B1)
           )
  {
      Status_BCU = 1;
  }else
  {
      Status_BCU = 0;
  }

  //TCU
  if(!this->CTD_TCU1OLINE_B1||!this->CTD_TCU2OLINE_B1||!this->CTD_TCU3OLINE_B1||!this->CTD_TCU4OLINE_B1||!this->CTD_TCU5OLINE_B1||!this->CTD_TCU6OLINE_B1
     ||(this->TCU1CT_IxDCUMajorFlt_B1)
     ||(this->TCU2CT_IxDCUMajorFlt_B1)||(this->TCU3CT_IxDCUMajorFlt_B1)||(this->TCU4CT_IxDCUMajorFlt_B1)||(this->TCU5CT_IxDCUMajorFlt_B1)||(this->TCU6CT_IxDCUMajorFlt_B1)
     ||(VVVFFaultFlag!=0)
          )
  {
      Status_TCU = 2;
  }else if(0)
  {
      Status_TCU = 1;
  }else
  {
      Status_TCU = 0;
  }


  //fire
  long FCUFaultFlag=0;

  FCUFaultFlag=!this->CTD_FCU1OLINE_B1+!this->CTD_FCU2OLINE_B1+crrcRicoMvb->getUnsignedInt(0x810,5)+crrcRicoMvb->getUnsignedInt32(0x810,6)+
          crrcRicoMvb->getUnsignedInt32(0x810,8)+crrcRicoMvb->getUnsignedInt(0x810,10)+

          crrcRicoMvb->getUnsignedInt(0x820,5)+crrcRicoMvb->getUnsignedInt32(0x820,6)+
          crrcRicoMvb->getUnsignedInt32(0x820,8)+crrcRicoMvb->getUnsignedInt(0x820,10);




  if(FCUFaultFlag)
  {
      Status_FIRE = 2;
  }else if(0)//fire warn  污染/屏蔽
  {
      Status_FIRE = 1;
  }else
  {
      Status_FIRE = 0;
  }

  if((!this->CTD_RIOM2GWOLINE_B1&&!this->RM2CT_CMK_B1)||
         (!this->CTD_RIOM5GWOLINE_B1&&!this->RM5CT_CMK_B1)
          )
  {
      Status_ACP = 2;

  }else if(0)
  {
      Status_ACP = 1;
  }else
  {
      Status_ACP = 0;
  }

  //TUOPU

  if(!this->CTD_CCU1OLINE_B1||!this->CTD_CCU2OLINE_B1||!this->CTD_ERM1OLINE_B1||!this->CTD_ERM2OLINE_B1
         ||!this->CTD_DDU1OLINE_B1||!this->CTD_DDU2OLINE_B1||!this->CTD_RIOM1GWOLINE_B1||!this->CTD_RIOM2GWOLINE_B1
          ||!this->CTD_RIOM3GWOLINE_B1||!this->CTD_RIOM4GWOLINE_B1||!this->CTD_RIOM5GWOLINE_B1||!this->CTD_RIOM6GWOLINE_B1
          ||!this->CTD_TCU1OLINE_B1||!this->CTD_TCU2OLINE_B1||!this->CTD_TCU3OLINE_B1||!this->CTD_TCU4OLINE_B1
          ||!this->CTD_TCU5OLINE_B1||!this->CTD_TCU6OLINE_B1||!this->CTD_BCU1OLINE_B1||!this->CTD_BCU2OLINE_B1
          ||!this->CTD_ACU1OLINE_B1||!this->CTD_ACU2OLINE_B1||!this->CTD_ACTOLINE_B1||!this->CTD_AC2OLINE_B1
          ||!this->CTD_AC3OLINE_B1||!this->CTD_AC4OLINE_B1||!this->CTD_PIS1OLINE_B1||!this->CTD_PIS2OLINE_B1
          ||!this->CTD_FCU1OLINE_B1||!this->CTD_FCU2OLINE_B1||!this->CTD_EDCU1OLINE_B1||!this->CTD_EDCU2OLINE_B1
          ||!this->CTD_EDCU3OLINE_B1||!this->CTD_EDCU4OLINE_B1||!this->CTD_EDCU5OLINE_B1||!this->CTD_EDCU6OLINE_B1
          ||!this->CTD_EDCU7OLINE_B1||!this->CTD_EDCU8OLINE_B1||!this->CTD_AMCTOLINE_B1||!this->CTD_AMC2OLINE_B1
          ||!this->CTD_PANOLINE_B1
     )
  {
      Status_TUOPU=2;
  }
  else if(0)
  {
      Status_TUOPU=1;
  }
  else
  {
      Status_TUOPU=0;
  }

}

void Database::createRIOMList(bool riom1trust,bool riom7trust,bool riom6trust,bool riom8trust)
{
    if(riom1trust)
    {
        copyPort(0xf110,0x110);
        copyPort(0xf111,0x111);
        copyPort(0xf112,0x112);
    }else if(riom7trust)
    {
        copyPort(0xf110,0x170);
        copyPort(0xf111,0x171);
        copyPort(0xf112,0x172);
    }else {
#ifdef TRUSTINVALID_CLEANDATA

        copyPort(0xf110,0xfff);
        copyPort(0xf111,0xfff);
        copyPort(0xf112,0xfff);
#endif
    }

    if(riom6trust)
    {
        copyPort(0xf160,0x160);
        copyPort(0xf161,0x161);
        copyPort(0xf162,0x162);
    }else if(riom8trust)
    {
        copyPort(0xf160,0x180);
        copyPort(0xf161,0x181);
        copyPort(0xf162,0x182);
    }else {
#ifdef TRUSTINVALID_CLEANDATA

        copyPort(0xf160,0xfff);
        copyPort(0xf161,0xfff);
        copyPort(0xf162,0xfff);
#endif
    }


}


void Database::createPISList()
{


   if(this->crrcRicoMvb->getBool(0x910,2,0)&&this->CTD_PIS1OLINE_B1)
   {
       this->copyPort(0xf910,0x910);
       this->copyPort(0xf911,0x911);
   }
   else if(this->crrcRicoMvb->getBool(0x920,2,0)&&this->CTD_PIS2OLINE_B1)
   {
       this->copyPort(0xf910,0x920);
       this->copyPort(0xf911,0x921);
   }
   else
   {
       this->copyPort(0xf910,0xfff);
       this->copyPort(0xf911,0xfff);
   }
}

void Database::createFCUList()
{
    if(this->CTD_FASTrusFCU1_B1&&this->CTD_FCU1OLINE_B1)
    {
        this->copyPort(0xf810,0x810);
    }
    else if(this->CTD_FASTrusFCU2_B1&&this->CTD_FCU2OLINE_B1)
    {
        this->copyPort(0xf810,0x820);
    }
    else
    {
        this->copyPort(0xf810,0xfff);
    }
}

void Database::createERMList(bool erm1trust,bool erm2trust)
{
    if(erm1trust)
    {
        copyPort(0xf210,0x210);
        copyPort(0xf211,0x211);
        copyPort(0xf212,0x212);
        copyPort(0xf213,0x213);

    }else if(erm2trust)
    {
        copyPort(0xf210,0x220);
        copyPort(0xf211,0x221);
        copyPort(0xf212,0x222);
        copyPort(0xf213,0x223);
    }else
    {
        copyPort(0xf210,0xfff);
        copyPort(0xf211,0xfff);
        copyPort(0xf212,0xfff);
        copyPort(0xf213,0xfff);
    }


}

bool Database::checkCcu1Online(unsigned char lifeSignal)
{
    static unsigned char oldLifeSignal = 0;
    static unsigned short int counter = 5;

    //qDebug()<< "old: " << QString::number(oldLifeSignal) << " lifeSignal:" << QString::number(lifeSignal);

    if (oldLifeSignal == lifeSignal)
    {
        counter ++;
    }
    else
    {
        counter = 0;
    }
   //qDebug()<<"counter = " << counter;

    oldLifeSignal = lifeSignal;

    if (counter > 1000)
    {
        counter = 100;
    }

    if (counter > 10)
    {
        return false;
    }
    else
    {
        return true;
    }
}

long Database::getAllHVACFault()
{
    long sum=0;
    sum=crrcRicoMvb->getUnsignedChar(0xA10,16)+crrcRicoMvb->getUnsignedChar(0xA10,18)+
            crrcRicoMvb->getUnsignedChar(0xA10,19)+crrcRicoMvb->getUnsignedChar(0xA10,20)+
            crrcRicoMvb->getUnsignedChar(0xA10,22)+crrcRicoMvb->getUnsignedChar(0xA10,23)+
            crrcRicoMvb->getUnsignedChar(0xA10,25)+
            crrcRicoMvb->getUnsignedChar(0xA20,16)+crrcRicoMvb->getUnsignedChar(0xA20,18)+
                        crrcRicoMvb->getUnsignedChar(0xA20,19)+crrcRicoMvb->getUnsignedChar(0xA20,20)+
                        crrcRicoMvb->getUnsignedChar(0xA20,22)+crrcRicoMvb->getUnsignedChar(0xA20,23)+
                        crrcRicoMvb->getUnsignedChar(0xA20,25)+
            crrcRicoMvb->getUnsignedChar(0xA30,16)+crrcRicoMvb->getUnsignedChar(0xA30,18)+
                        crrcRicoMvb->getUnsignedChar(0xA30,19)+crrcRicoMvb->getUnsignedChar(0xA30,20)+
                        crrcRicoMvb->getUnsignedChar(0xA30,22)+crrcRicoMvb->getUnsignedChar(0xA30,23)+
                        crrcRicoMvb->getUnsignedChar(0xA30,25)+
            crrcRicoMvb->getUnsignedChar(0xA40,16)+crrcRicoMvb->getUnsignedChar(0xA40,18)+
                        crrcRicoMvb->getUnsignedChar(0xA40,19)+crrcRicoMvb->getUnsignedChar(0xA40,20)+
                        crrcRicoMvb->getUnsignedChar(0xA40,22)+crrcRicoMvb->getUnsignedChar(0xA40,23)+
                        crrcRicoMvb->getUnsignedChar(0xA40,25);
            return sum;
}

long Database::getAllSIVFault()
{
    long sum=0;
    sum=crrcRicoMvb->getUnsignedChar(0x610,10)+crrcRicoMvb->getUnsignedChar(0x610,11)+
            crrcRicoMvb->getUnsignedChar(0x610,12)+crrcRicoMvb->getUnsignedChar(0x610,13)+
            crrcRicoMvb->getBool(0x610,14,0)+crrcRicoMvb->getBool(0x610,14,1)+
            crrcRicoMvb->getUnsignedChar(0x610,15)+
            crrcRicoMvb->getBool(0x610,16,0)+crrcRicoMvb->getBool(0x610,16,1)+
            crrcRicoMvb->getBool(0x610,16,2)+crrcRicoMvb->getBool(0x610,16,3)+
            crrcRicoMvb->getBool(0x610,16,4)+crrcRicoMvb->getBool(0x610,16,5)+
            crrcRicoMvb->getBool(0x610,18,4)+
            crrcRicoMvb->getBool(0x610,18,5)+crrcRicoMvb->getBool(0x610,18,6)+
            crrcRicoMvb->getBool(0x610,18,7)+

            crrcRicoMvb->getUnsignedChar(0x620,10)+crrcRicoMvb->getUnsignedChar(0x620,11)+
                        crrcRicoMvb->getUnsignedChar(0x620,12)+crrcRicoMvb->getUnsignedChar(0x620,13)+
                        crrcRicoMvb->getBool(0x620,14,0)+crrcRicoMvb->getBool(0x620,14,1)+
                        crrcRicoMvb->getUnsignedChar(0x620,15)+
                        crrcRicoMvb->getBool(0x620,16,0)+crrcRicoMvb->getBool(0x620,16,1)+
                        crrcRicoMvb->getBool(0x620,16,2)+crrcRicoMvb->getBool(0x620,16,3)+
                        crrcRicoMvb->getBool(0x620,16,4)+crrcRicoMvb->getBool(0x620,16,5)+
                        crrcRicoMvb->getBool(0x620,18,4)+
                        crrcRicoMvb->getBool(0x620,18,5)+crrcRicoMvb->getBool(0x620,18,6)+
                        crrcRicoMvb->getBool(0x620,18,7);

    return sum;

}

long Database::getAllVVVFFault()
{
    long sum=0;
    sum=crrcRicoMvb->getUnsignedChar(0x511,0)+crrcRicoMvb->getUnsignedChar(0x511,1)+
            crrcRicoMvb->getUnsignedChar(0x511,2)+crrcRicoMvb->getUnsignedChar(0x511,3)+
            crrcRicoMvb->getBool(0x511,4,0)+crrcRicoMvb->getUnsignedChar(0x511,5)+
            crrcRicoMvb->getUnsignedChar(0x511,6)+crrcRicoMvb->getUnsignedChar(0x511,7)+
            crrcRicoMvb->getUnsignedChar(0x511,8)+crrcRicoMvb->getUnsignedChar(0x511,9)+
            crrcRicoMvb->getUnsignedChar(0x511,10)+crrcRicoMvb->getUnsignedChar(0x511,11)+

            crrcRicoMvb->getUnsignedChar(0x521,0)+crrcRicoMvb->getUnsignedChar(0x521,1)+
                        crrcRicoMvb->getUnsignedChar(0x521,2)+crrcRicoMvb->getUnsignedChar(0x521,3)+
                        crrcRicoMvb->getBool(0x521,4,0)+crrcRicoMvb->getUnsignedChar(0x521,5)+
                        crrcRicoMvb->getUnsignedChar(0x521,6)+crrcRicoMvb->getUnsignedChar(0x521,7)+
                        crrcRicoMvb->getUnsignedChar(0x521,8)+crrcRicoMvb->getUnsignedChar(0x521,9)+
                        crrcRicoMvb->getUnsignedChar(0x521,10)+crrcRicoMvb->getUnsignedChar(0x521,11)+

            crrcRicoMvb->getUnsignedChar(0x531,0)+crrcRicoMvb->getUnsignedChar(0x531,1)+
                        crrcRicoMvb->getUnsignedChar(0x531,2)+crrcRicoMvb->getUnsignedChar(0x531,3)+
                        crrcRicoMvb->getBool(0x531,4,0)+crrcRicoMvb->getUnsignedChar(0x531,5)+
                        crrcRicoMvb->getUnsignedChar(0x531,6)+crrcRicoMvb->getUnsignedChar(0x531,7)+
                        crrcRicoMvb->getUnsignedChar(0x531,8)+crrcRicoMvb->getUnsignedChar(0x531,9)+
                        crrcRicoMvb->getUnsignedChar(0x531,10)+crrcRicoMvb->getUnsignedChar(0x531,11)+

            crrcRicoMvb->getUnsignedChar(0x541,0)+crrcRicoMvb->getUnsignedChar(0x541,1)+
                        crrcRicoMvb->getUnsignedChar(0x541,2)+crrcRicoMvb->getUnsignedChar(0x541,3)+
                        crrcRicoMvb->getBool(0x541,4,0)+crrcRicoMvb->getUnsignedChar(0x541,5)+
                        crrcRicoMvb->getUnsignedChar(0x541,6)+crrcRicoMvb->getUnsignedChar(0x541,7)+
                        crrcRicoMvb->getUnsignedChar(0x541,8)+crrcRicoMvb->getUnsignedChar(0x541,9)+
                        crrcRicoMvb->getUnsignedChar(0x541,10)+crrcRicoMvb->getUnsignedChar(0x541,11)+

            crrcRicoMvb->getUnsignedChar(0x551,0)+crrcRicoMvb->getUnsignedChar(0x551,1)+
                        crrcRicoMvb->getUnsignedChar(0x551,2)+crrcRicoMvb->getUnsignedChar(0x551,3)+
                        crrcRicoMvb->getBool(0x551,4,0)+crrcRicoMvb->getUnsignedChar(0x551,5)+
                        crrcRicoMvb->getUnsignedChar(0x551,6)+crrcRicoMvb->getUnsignedChar(0x551,7)+
                        crrcRicoMvb->getUnsignedChar(0x551,8)+crrcRicoMvb->getUnsignedChar(0x551,9)+
                        crrcRicoMvb->getUnsignedChar(0x551,10)+crrcRicoMvb->getUnsignedChar(0x551,11)+

            crrcRicoMvb->getUnsignedChar(0x561,0)+crrcRicoMvb->getUnsignedChar(0x561,1)+
                        crrcRicoMvb->getUnsignedChar(0x561,2)+crrcRicoMvb->getUnsignedChar(0x561,3)+
                        crrcRicoMvb->getBool(0x561,4,0)+crrcRicoMvb->getUnsignedChar(0x561,5)+
                        crrcRicoMvb->getUnsignedChar(0x561,6)+crrcRicoMvb->getUnsignedChar(0x561,7)+
                        crrcRicoMvb->getUnsignedChar(0x561,8)+crrcRicoMvb->getUnsignedChar(0x561,9)+
                        crrcRicoMvb->getUnsignedChar(0x561,10)+crrcRicoMvb->getUnsignedChar(0x561,11);
    return sum;

}

long Database::getAllPISFault()
{
    long sum=0;
    sum=crrcRicoMvb->getBool(0x910,2,4)+crrcRicoMvb->getBool(0x910,2,5)+
            crrcRicoMvb->getBool(0x910,2,6)+crrcRicoMvb->getBool(0x910,2,7)+
            crrcRicoMvb->getUnsignedChar(0x910,3)+crrcRicoMvb->getUnsignedChar(0x910,4)+
            crrcRicoMvb->getUnsignedChar(0x910,5)+crrcRicoMvb->getUnsignedChar(0x910,6)+
            crrcRicoMvb->getUnsignedChar(0x910,7)+crrcRicoMvb->getUnsignedChar(0x910,8)+
            crrcRicoMvb->getUnsignedChar(0x910,9)+crrcRicoMvb->getUnsignedChar(0x910,10)+
            crrcRicoMvb->getUnsignedChar(0x910,11)+crrcRicoMvb->getUnsignedChar(0x910,12)+
            crrcRicoMvb->getUnsignedChar(0x910,13)+crrcRicoMvb->getUnsignedChar(0x910,14)+
            crrcRicoMvb->getUnsignedChar(0x910,15)+

            crrcRicoMvb->getBool(0x920,2,4)+crrcRicoMvb->getBool(0x920,2,5)+
                        crrcRicoMvb->getBool(0x920,2,6)+crrcRicoMvb->getBool(0x920,2,7)+
                        crrcRicoMvb->getUnsignedChar(0x920,3)+crrcRicoMvb->getUnsignedChar(0x920,4)+
                        crrcRicoMvb->getUnsignedChar(0x920,5)+crrcRicoMvb->getUnsignedChar(0x920,6)+
                        crrcRicoMvb->getUnsignedChar(0x920,7)+crrcRicoMvb->getUnsignedChar(0x920,8)+
                        crrcRicoMvb->getUnsignedChar(0x920,9)+crrcRicoMvb->getUnsignedChar(0x920,10)+
                        crrcRicoMvb->getUnsignedChar(0x920,11)+crrcRicoMvb->getUnsignedChar(0x920,12)+
                        crrcRicoMvb->getUnsignedChar(0x920,13)+crrcRicoMvb->getUnsignedChar(0x920,14)+
                        crrcRicoMvb->getUnsignedChar(0x920,15);
    return sum;

}


long Database::getAllEDCUFault()
{
    long sum=0;
    sum=crrcRicoMvb->getUnsignedInt32(0x710,0)+crrcRicoMvb->getUnsignedInt32(0x710,4)+
            crrcRicoMvb->getUnsignedInt32(0x710,8)+crrcRicoMvb->getUnsignedInt32(0x710,12)+
            crrcRicoMvb->getUnsignedInt32(0x710,16)+crrcRicoMvb->getUnsignedInt32(0x710,20)+

            crrcRicoMvb->getUnsignedInt32(0x720,0)+crrcRicoMvb->getUnsignedInt32(0x720,4)+
                        crrcRicoMvb->getUnsignedInt32(0x720,8)+crrcRicoMvb->getUnsignedInt32(0x720,12)+
                        crrcRicoMvb->getUnsignedInt32(0x720,16)+crrcRicoMvb->getUnsignedInt32(0x720,20)+

            crrcRicoMvb->getUnsignedInt32(0x730,0)+crrcRicoMvb->getUnsignedInt32(0x730,4)+
                        crrcRicoMvb->getUnsignedInt32(0x730,8)+crrcRicoMvb->getUnsignedInt32(0x730,12)+
                        crrcRicoMvb->getUnsignedInt32(0x730,16)+crrcRicoMvb->getUnsignedInt32(0x730,20)+

            crrcRicoMvb->getUnsignedInt32(0x740,0)+crrcRicoMvb->getUnsignedInt32(0x740,4)+
                        crrcRicoMvb->getUnsignedInt32(0x740,8)+crrcRicoMvb->getUnsignedInt32(0x740,12)+
                        crrcRicoMvb->getUnsignedInt32(0x740,16)+crrcRicoMvb->getUnsignedInt32(0x740,20)+

            crrcRicoMvb->getUnsignedInt32(0x750,0)+crrcRicoMvb->getUnsignedInt32(0x750,4)+
                        crrcRicoMvb->getUnsignedInt32(0x750,8)+crrcRicoMvb->getUnsignedInt32(0x750,12)+
                        crrcRicoMvb->getUnsignedInt32(0x750,16)+crrcRicoMvb->getUnsignedInt32(0x750,20)+

            crrcRicoMvb->getUnsignedInt32(0x760,0)+crrcRicoMvb->getUnsignedInt32(0x760,4)+
                        crrcRicoMvb->getUnsignedInt32(0x760,8)+crrcRicoMvb->getUnsignedInt32(0x760,12)+
                        crrcRicoMvb->getUnsignedInt32(0x760,16)+crrcRicoMvb->getUnsignedInt32(0x760,20)+

            crrcRicoMvb->getUnsignedInt32(0x770,0)+crrcRicoMvb->getUnsignedInt32(0x770,4)+
                        crrcRicoMvb->getUnsignedInt32(0x770,8)+crrcRicoMvb->getUnsignedInt32(0x770,12)+
                        crrcRicoMvb->getUnsignedInt32(0x770,16)+crrcRicoMvb->getUnsignedInt32(0x770,20)+

            crrcRicoMvb->getUnsignedInt32(0x780,0)+crrcRicoMvb->getUnsignedInt32(0x780,4)+
                        crrcRicoMvb->getUnsignedInt32(0x780,8)+crrcRicoMvb->getUnsignedInt32(0x780,12)+
                        crrcRicoMvb->getUnsignedInt32(0x780,16)+crrcRicoMvb->getUnsignedInt32(0x780,20);

    return sum;
}

long Database::getAllBCUFault()
{
    long sum=0;
    sum=crrcRicoMvb->getUnsignedInt32(0x410,4)+crrcRicoMvb->getUnsignedInt32(0x410,8)+
            crrcRicoMvb->getUnsignedInt32(0x410,12)+crrcRicoMvb->getUnsignedInt32(0x410,16)+
            +crrcRicoMvb->getUnsignedChar(0x410,20)+crrcRicoMvb->getBool(0x410,21,0)+
            crrcRicoMvb->getBool(0x410,21,1)+crrcRicoMvb->getBool(0x411,1,1)+

            crrcRicoMvb->getUnsignedInt32(0x420,4)+crrcRicoMvb->getUnsignedInt32(0x420,8)+
                        crrcRicoMvb->getUnsignedInt32(0x420,12)+crrcRicoMvb->getUnsignedInt32(0x410,16)+
                        +crrcRicoMvb->getUnsignedChar(0x420,20)+crrcRicoMvb->getBool(0x420,21,0)+
                        crrcRicoMvb->getBool(0x420,21,1)+crrcRicoMvb->getBool(0x421,1,1);

    return sum;

}
