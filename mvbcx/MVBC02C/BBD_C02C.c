#include <stdio.h>
#include <stdlib.h>             /* srand, rand */
#include <string.h>
#include <time.h>               /* clock       */
#include <pthread.h>

#include "BBD_C02C.h"
#include "os_hal.h"

/* 大小端配置 */
#define BBD_BYTE_ODER_LE  1
#define MVB_DEBUG_PRINT   0

/* PortIndex表 */
static T_BBD_PIT_INFO  *s_ptPitInfo=NULL;
#define BBD_CRC_RECV_FLG   1
#define BBD_NEED_FRESH_TIME 1
/* MVBC02C寄存器基地址 */
static T_TM_ADDR_LIST s_tTmAddrList;
static unsigned short    g_u16STSR = 0x9000;
static unsigned int      g_uiBBDStr = 0;
static int               g_aiPortMap[4096];        //端口映射表
static pthread_t         g_hRecvThread =0;         //接收数据线程
static int               g_iThreadRun = 0;         //线程运行标志
static unsigned char     g_acCount[256];
static unsigned short    *g_psCRCValue = NULL;
static     pthread_mutex_t	g_tMutex;



unsigned char InitTable()
{
    unsigned char  POLY = 0xE5;
    int i = 0;
    int j = 0;

    for(i=0;i<256;i++)
    {
        unsigned char acount = 0;
        for(j=0;j<8;j++)
        {
            if(i & 1<<j)
            {
                acount ++;
            }
        }
        g_acCount[i]=acount;
    }

    for( i=0;i<65536;i++)
    {
        unsigned short crc_tmp = i;

        for (j = 0; j < 8; j++ )
        {
            if ( crc_tmp & 0x8000 )
            {
                crc_tmp ^= (POLY<<8);
                crc_tmp <<=1;
            }
            else
            {
                crc_tmp <<= 1;
            }
        }
        g_psCRCValue[i] = crc_tmp;
    }
    return 0;
}

unsigned char CalMvbCrcVal(const unsigned char * pdata, unsigned char size)
{

    unsigned short  i = 0, j = 0, bits = 0, crc_tmp = 0;
    unsigned char crc = 0, ncrc = 0, remain = 0;

    crc_tmp |= (pdata[0]<<8);
    for ( i = 1; i < size; i++ )
    {
        crc_tmp = crc_tmp|pdata[i];
        crc_tmp = g_psCRCValue[crc_tmp];

    }

    crc_tmp = g_psCRCValue[crc_tmp];

    /* 计算余数 */
    remain = crc_tmp >> 9;

    /* 计算偶校验 */
    bits = 0;

    for ( i = 0; i < size; i++ )
    {
        bits+=g_acCount[pdata[i]];
    }

    bits+=g_acCount[remain];
    ncrc = remain<<1;
    if ( (bits%2) != 0 )
    {
        ncrc |= 0x01;
    }

    crc = ~ncrc;
    return crc;
}


int BBDC02C_GetMVBStatus(unsigned short devaddr, unsigned int * pDevState, unsigned char *  pLinkState)
{
#if 0
    unsigned short  eca=0, ecb=0;
    
    eca = OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_ECA);
    
    ecb = OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_ECB);

    printf("#### %s  ECA=%04x, ECB=%04x\n", __FUNCTION__, eca, ecb);

    printf("#### %s  FC   = %04x\n", __FUNCTION__, OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_FC));
    printf("#### %s  EC   = %04x\n", __FUNCTION__, OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_EC));
    printf("#### %s  SCR  = %04x\n", __FUNCTION__, OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_SCR));
    printf("#### %s  ISR0 = %04x\n", __FUNCTION__, OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_ISR0));
    printf("#### %s  ISR1 = %04x\n", __FUNCTION__, OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_ISR1));
#endif
//    *pDevState  = 0;
//    *pLinkState = ML_LINK_OK;
        
    return 0;
}

int  BBDC02C_EnableBA(const char * fBinName)
{
	return 0;
}

static E_MVB_PORTSIZE GetPortSize(unsigned short PortAddr,E_MVB_PORTDIR PortDir)
{    
    int iIndex = g_aiPortMap[PortAddr];

    if(PortAddr < 4096)
    {
        if(iIndex<PORT_NUMBER_MAX && iIndex>=0)
        {
            if((s_ptPitInfo->u16PortAddr[iIndex] == PortAddr)&&(s_ptPitInfo->bPortDir[iIndex] == PortDir)&&(s_ptPitInfo->bUsed[iIndex] > 0))
            {
                return s_ptPitInfo->u16PortSize[iIndex];
            }
        }
    }

    db_printf("Not find PortAddr PortAddr:%d PortDir:%d iIndex:%d\n",PortAddr,PortDir,iIndex);
    return E_MVBPORT_SIZE2;             //返回最小值
}

static unsigned short AllocPI(unsigned short * pPi, E_MVB_PORTDIR portdir,unsigned short portaddr, unsigned short portsize)
{
    int i = 0;
    unsigned short pi = 0;
    //===============================================
    for ( i = 0; i < (PORT_NUMBER_MAX-1); i++ )
    {
        if ( 0 == s_ptPitInfo->bUsed[i] )
        {
            break;
        }
        else if(i  == (PORT_NUMBER_MAX-2) )
        {
            return -1;
        }
    }
    //===============================================
    pi = 4*(i+1);
    s_ptPitInfo->u16PortAddr[i] = portaddr;
    s_ptPitInfo->u16PIVal[i]    = pi;
    s_ptPitInfo->bUsed[i]       = 1;
    s_ptPitInfo->u16PortSize[i] = portsize;
    s_ptPitInfo->bPortDir[i]    = portdir; 
    s_ptPitInfo->u16Freshness[i] = 0;
    g_aiPortMap[portaddr] = i;
    //===============================================
    *pPi = pi;

    return pi;
}

static int FreePI(unsigned short PI)
{
    int pos = (PI / 4) - 1;

    if ( PI % 4 )
    {
        return -1;
    }
    if(pos<PORT_NUMBER_MAX && pos>=0)
    {
        if(s_ptPitInfo->u16PortAddr[pos]>=0 &&
            s_ptPitInfo->u16PortAddr[pos]<4096 )
        {
            g_aiPortMap[s_ptPitInfo->u16PortAddr[pos]] = -1;
        }

        s_ptPitInfo->u16PortAddr[pos] = 0;
        s_ptPitInfo->u16PIVal[pos]    = 0;
        s_ptPitInfo->bUsed[pos]       = 0;
        s_ptPitInfo->u16PortSize[pos] = 0;
        s_ptPitInfo->bPortDir[pos]    = 0;
        s_ptPitInfo->u16Freshness[pos] = 0;
    }

    return 0;
}

static int RegPort(E_MVB_PORTDIR portdir,unsigned short portaddr,unsigned short portsize)
{
    unsigned short pi      = 0;
    unsigned short pcs_val = 0;
    unsigned short u16Value = 0;

    if(portaddr >4095)
    {
          return -1;
    }

    //===============================================
    if ( AllocPI(&pi,portdir, portaddr, portsize) < 0 )
    {
        return -1;
    } 

    //===============================================
    OS_WriteWord(s_tTmAddrList.la_pit_addr+(portaddr<<1), pi);
    u16Value = OS_ReadWord(s_tTmAddrList.la_pit_addr+(portaddr<<1));

    if(u16Value != pi)
    {
        db_printf("[%s][%d] err\n");
        return -1;
    }

    //===============================================
    switch ( portsize)
    {
        case E_MVBPORT_SIZE2:
            pcs_val |= (0 << 12);
            break;
        case E_MVBPORT_SIZE4:
            pcs_val |= (1 << 12);
            break;
        case E_MVBPORT_SIZE8:
            pcs_val |= (2 << 12);
            break;
        case E_MVBPORT_SIZE16:
            pcs_val |= (3 << 12);
            break;
        case E_MVBPORT_SIZE32:
            pcs_val |= (4 << 12);
            break;
        default:
            break;
    }
    //===============================================
    if ( E_MVB_PORTDIR_SRC == portdir)
    {
        pcs_val |= (1<<11);
    }
    else
    {
        pcs_val |= (1<<10);
    }
    pcs_val |= (1<<1);

#if BBD_CRC_RECV_FLG
    pcs_val |= (1<<9);   /* 使能TWCS */
#endif
    //===============================================
    OS_WriteWord(PCS0_ADDR(s_tTmAddrList.la_pcs_addr, pi), pcs_val); 

    return 0;
}

static int UnRegPort(unsigned short portAddr)
{
    unsigned short pi = 0;
    UINT16 u16Value = 0;
    int iPortIndex = 0;

    iPortIndex = g_aiPortMap[portAddr];

    if(iPortIndex >=PORT_NUMBER_MAX || iPortIndex<0)
    {
        return -1;
    }

    pi = s_ptPitInfo->u16PIVal[iPortIndex];

    if ( 0 == FreePI(pi) )
    {
         OS_WriteWord(s_tTmAddrList.la_pit_addr+(portAddr<<1), 0x0000);
        u16Value = OS_ReadWord(s_tTmAddrList.la_pit_addr+(portAddr<<1));
        if(0 != u16Value)
        {
            db_printf("[%s][%d] err\n");
            return -1;
        }
        
        OS_WriteWord(PCS0_ADDR(s_tTmAddrList.la_pcs_addr, pi), 0x0000); 
        u16Value = OS_ReadWord(PCS0_ADDR(s_tTmAddrList.la_pcs_addr, pi));
        
        if(0 != u16Value)
        {
            db_printf("[%s][%d] err\n");
            return -1;
        }
        OS_WriteWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi), 0x0000);
        OS_WriteWord(PCS2_ADDR(s_tTmAddrList.la_pcs_addr, pi), 0x0000);
        OS_WriteWord(PCS3_ADDR(s_tTmAddrList.la_pcs_addr, pi), 0x0000);
        

        {
            unsigned int da_addr = LA_DA_ADDR(s_tTmAddrList.la_da_addr, pi);
            unsigned int i = 0;

            for ( i = 0; i < 32; i+=2)
            {
                OS_WriteWord((da_addr|0x20)+i, 0x0000);
                OS_WriteWord((da_addr)+i, 0x0000);                
            }
        }
    }
    else
    {   
        return -1;
    }

    return 0;
}

static void * BBDC02C_Create()
{
    pthread_mutexattr_t mutexattr;

    memset(&s_tTmAddrList, 0, sizeof(T_TM_ADDR_LIST));
    memset(g_aiPortMap,-1,sizeof(g_aiPortMap));

    if(NULL == s_ptPitInfo)
    {
        s_ptPitInfo = (T_BBD_PIT_INFO *)malloc(sizeof(T_BBD_PIT_INFO));

    }
    memset(s_ptPitInfo,0,sizeof(T_BBD_PIT_INFO));

    if(NULL == g_psCRCValue)
    {
        g_psCRCValue = (unsigned short*)malloc(65536*sizeof(unsigned short));
        InitTable();
    }

    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_TIMED_NP);
    pthread_mutex_init(&g_tMutex,&mutexattr);
    pthread_mutexattr_destroy(&mutexattr);

    return (void *)1;
}


MUE_RESULT BBDC02C_PutData(unsigned short u16PortAddr , unsigned char *pData)
{
    E_MVB_PORTSIZE ePortSize;
    
    unsigned int   addr = 0;
    unsigned int   i    = 0;
    unsigned int   vp   = 0;
    unsigned short pi   = 0;
    unsigned short val  = 0, val_tmp  = 0;
    unsigned short pcs1 = 0, pcs1_tmp = 0;
    unsigned char  brk = 0;
    int iPortIndex = 0;
#if BBD_CRC_RECV_FLG
    unsigned char  cs = 0;
    unsigned short aCs[4];
#endif

    iPortIndex = g_aiPortMap[u16PortAddr];

    if(iPortIndex >=PORT_NUMBER_MAX || iPortIndex<0)
    {
        return -1;
    }
    //===============================================
    ePortSize=GetPortSize(u16PortAddr,E_MVB_PORTDIR_SRC);
    //===============================================
    
    pi = s_ptPitInfo->u16PIVal[iPortIndex];

    pthread_mutex_lock(&g_tMutex);
    /* 2nd: cache the value pcs1 */
    pcs1 = OS_ReadWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi));

    addr = LA_DA_ADDR(s_tTmAddrList.la_da_addr, pi);
    
    if ( !((pcs1>>6) & 0x01) )
    {
        addr |= 0x20;
        
        /* invert VP */
        pcs1 |= (1<<6);
        vp = 1;
    }
    else
    {
        /* invert VP */
        pcs1 &= ~(1<<6);
        vp = 0;
    }
    
    for ( i = 0; i < ePortSize;  )
    {

#if  BBD_BYTE_ODER_LE
        val = (pData[i] << 8) | pData[i+1];        
#else
        val = (pData[i+1] << 8) | pData[i]; 
#endif
    
        OS_WriteWord(addr+i, val);
        i+=2;
    }   


#if BBD_CRC_RECV_FLG

    memset(aCs, 0, sizeof(unsigned short)*2);
    switch (ePortSize)
    {
        case E_MVBPORT_SIZE2:
        case E_MVBPORT_SIZE4:
        case E_MVBPORT_SIZE8:
            cs = CalMvbCrcVal(pData, ePortSize);
            aCs[0] = cs << (8*vp);
            OS_WriteWord(PCS3_ADDR(s_tTmAddrList.la_pcs_addr, pi), aCs[0]);
            break;
        case E_MVBPORT_SIZE16:
        case E_MVBPORT_SIZE32:
            for ( i = 0; i < ePortSize/8; i++ )
            {
                cs = CalMvbCrcVal(pData+(i*8), 8);
                aCs[i] = cs << (8*vp);
                OS_WriteWord(PCS3_ADDR(s_tTmAddrList.la_pcs_addr, pi) + 8*i, aCs[i]);
            }
            break;
        default:
            break;
    }
 #endif
    OS_WriteWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi), pcs1);

    //ND_Dbg("****  %s:  addr=%04x  val = %04x, val_tmp = %04x\n", __FUNCTION__, addr, val, val_tmp);
    //ND_Dbg("****  %s:  PCS0=%04x \n", __FUNCTION__, OS_ReadWord(PCS0_ADDR(s_tTmAddrList.la_pcs_addr, pi)));
    //ND_Dbg("****  %s:  PCS1=%04x \n", __FUNCTION__, OS_ReadWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi)));
    //ND_Dbg("****  %s:  PCS2=%04x \n", __FUNCTION__, OS_ReadWord(PCS2_ADDR(s_tTmAddrList.la_pcs_addr, pi)));

#if 1

    usleep(1);
    pcs1_tmp = OS_ReadWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi));

    if ( pcs1_tmp != pcs1 )
    {
        OS_WriteWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi), pcs1);
        ND_Err("****  %s: Read Back PCS1 Not Same, pcs1=%04x , %04x\n",__FUNCTION__, pcs1, pcs1_tmp);
        //ND_Err("****  %s: Read Back PCS1 Not Same, PA=%04x  TACK = %04x\n", __FUNCTION__, u16PortAddr, OS_ReadWord(PCS2_ADDR(s_tTmAddrList.la_pcs_addr, pi)));
    }
#endif
    pthread_mutex_unlock(&g_tMutex);
	return MUE_RESULT_OK;
}


MUE_RESULT BBDC02C_Uninit(void)
{
    OS_CleanTM();
    if(s_ptPitInfo)
    {
        free(s_ptPitInfo);
        s_ptPitInfo = NULL;
    }
#ifdef BBD_NEED_FRESH_TIME

    g_iThreadRun = 0;
    pthread_join(g_hRecvThread,NULL);
    g_hRecvThread = NULL;
#endif

    if(g_psCRCValue)
     {
          free(g_psCRCValue);
          g_psCRCValue = NULL;
     }
    pthread_mutex_destroy(&g_tMutex);
    return MUE_RESULT_OK;
}


MUE_RESULT GetData(unsigned short u16PortAddr, unsigned char *p_port_status, unsigned char *puData, unsigned short  *pu16Freshness)
{
    E_MVB_PORTSIZE ePortSize;

    unsigned int   da_addr = 0;
    unsigned int   i    = 0;
    unsigned int   n    = 0;
    unsigned int   vp   = 0;
    unsigned short pi   = 0;
    unsigned short val  = 0;
    unsigned short pcs2_val = 0, aCs[4];
    unsigned char pData[64] = {0};

    int iPortIndex = g_aiPortMap[u16PortAddr];

    if(iPortIndex >=PORT_NUMBER_MAX || iPortIndex<0)
    {
        return MUE_RESULT_ERROR;
    }

    ePortSize=GetPortSize(u16PortAddr,E_MVB_PORTDIR_SNK);

    pi = s_ptPitInfo->u16PIVal[iPortIndex];
    if ( 0 == pi )
    {
        return MUE_RESULT_ERROR;
    }


    da_addr = LA_DA_ADDR(s_tTmAddrList.la_da_addr, pi);
    /* 读数据时即使有翻转也没关系，有两个buf区，且对应了不同的CRC*/
    pthread_mutex_lock(&g_tMutex);
    for ( n = 0; n < 1; n++ )
    {
        if(s_ptPitInfo->u16Freshness[iPortIndex] < 0x400)
        {
            *pu16Freshness  = s_ptPitInfo->u16Freshness[iPortIndex] << 6;// x64
            *p_port_status = 0;
        }
        else
        {
             *pu16Freshness = 65535;
        }

        val = OS_ReadWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi));

        vp = (val>>6) & 0x01;
        for ( i = 0; i < ePortSize;  )
        {
            if ( vp )
            {
                val = OS_ReadWord((da_addr|0x20)+i);
            }
            else
            {
                val = OS_ReadWord(da_addr+i);
            }

            //memcpy(pData+i, &val, 2);
#if   BBD_BYTE_ODER_LE
            pData[i+1] = val & 0xFF;
            pData[i]   = (val >> 8) & 0xFF;
#else
            pData[i] = val & 0xFF;
            pData[i+1]   = (val >> 8) & 0xFF;
#endif
            i+=2;

#if BBD_CRC_RECV_FLG
            switch (ePortSize)
            {
                case E_MVBPORT_SIZE2:
                case E_MVBPORT_SIZE4:
                case E_MVBPORT_SIZE8:
                    if ( i == ePortSize )
                    {
                        aCs[0] = OS_ReadWord(PCS3_ADDR(s_tTmAddrList.la_pcs_addr, pi));
                    }
                    break;
                case E_MVBPORT_SIZE16:
                case E_MVBPORT_SIZE32:
                    if ( (i%8) == 0 )
                    {
                        aCs[i/8-1] = OS_ReadWord(PCS3_ADDR(s_tTmAddrList.la_pcs_addr, pi) + 8*(i/8-1));
                    }
                    break;
                default:
                    break;
            }
#endif
        }
    }
    pthread_mutex_unlock(&g_tMutex);

#if BBD_CRC_RECV_FLG
    switch (ePortSize)
    {
        case E_MVBPORT_SIZE2:
        case E_MVBPORT_SIZE4:
        case E_MVBPORT_SIZE8:
            if ( ((aCs[0] >> (8*vp)) & 0xFF) != CalMvbCrcVal(pData, ePortSize) )
            {
#if MVB_DEBUG_PRINT
                printf("BBDC02C_GetData:CRC-%d Error(port-%04x, size-%d) *pcs2_val:%d\n ", 0, u16PortAddr, ePortSize,pcs2_val);
                printf("--- %02x %02x %02x %02x %02x %02x %02x %02x  crc=%02x\n", pData[0], pData[1],pData[2],pData[3],pData[4],pData[5],pData[6],pData[7], ((aCs[0] >> (8*vp)) & 0xFF));
                //TmpReadDaArea(da_addr, vp);
#endif

                return MUE_RESULT_ERROR;
            }
            break;
        case E_MVBPORT_SIZE16:
        case E_MVBPORT_SIZE32:
            for ( i = 0; i < ePortSize/8; i++ )
            {
                if ( ((aCs[i] >> (8*vp)) & 0xFF) != CalMvbCrcVal(pData+(i*8), 8) )
                {
#if MVB_DEBUG_PRINT
                    printf("BBDC02C_GetData:CRC-%d Error(port-%04x, size-%d)pcs2_val:%d\n", i, u16PortAddr, ePortSize,pcs2_val);
                    int j = 0;
                    for ( j = 0; j < ePortSize/8; j++ )
                    {
                        printf("--- %02x %02x %02x %02x %02x %02x %02x %02x  crc=%02x\n", pData[j*8], pData[j*8+1],pData[j*8+2],pData[j*8+3],
                                              pData[j*8+4],pData[j*8+5],pData[j*8+6],pData[j*8+7], ((aCs[j] >> (8*vp)) & 0xFF));
                    }
#endif
                    //TmpReadDaArea(da_addr, vp);

                    return MUE_RESULT_ERROR;
                }
            }
            break;
        default:
            break;
    }
#endif

    memcpy(puData,pData,ePortSize);

    return MUE_RESULT_OK;

}


MUE_RESULT BBDC02C_GetData(unsigned short u16PortAddr, unsigned char *p_port_status, unsigned char *pData, unsigned short  *pu16Freshness)
{

    return GetData(u16PortAddr, p_port_status, pData, pu16Freshness);

}


MUE_RESULT BBDC02C_RegPort(E_MVB_PORTDIR portdir,unsigned short portaddr,unsigned short portsize)
{
   if ( RegPort(portdir,portaddr,portsize) == 0 )
       return MUE_RESULT_OK;
   else
       return MUE_RESULT_ERROR;
}

MUE_RESULT BBDC02C_UnRegPort(unsigned short portaddr)
{
   if ( UnRegPort(portaddr) == 0 )
       return MUE_RESULT_OK;
   else
       return MUE_RESULT_ERROR;    
}

MUE_RESULT BBDC02C_Init(void)
{
    BBDC02C_Create();
    //=====================================================================
    s_tTmAddrList.tm_mod              = TM_MODE_DEFAULT;
    if(E_TM_MODE2 == s_tTmAddrList.tm_mod)
    {
        s_tTmAddrList.la_pit_addr         = TM_MODE2_LA_PIT_ADDR;
        s_tTmAddrList.la_da_addr          = TM_MODE2_LA_DA_ADDR;
        s_tTmAddrList.la_ft_addr          = TM_MODE2_LA_FT_ADDR;
        s_tTmAddrList.la_pcs_addr         = TM_MODE2_LA_PCS_ADDR;
        s_tTmAddrList.da_pit_addr         = TM_MODE2_DA_PIT_ADDR;
        s_tTmAddrList.da_da_addr          = TM_MODE2_DA_DA_ADDR;
        s_tTmAddrList.da_pcs_addr         = TM_MODE2_DA_PCS_ADDR;
        s_tTmAddrList.service_area_addr   = TM_MODE2_SERVICE_AREA_ADDR;
        s_tTmAddrList.sa_intreg_addr      = TM_MODE2_SA_INTREG_ADDR;
    }
    else if(E_TM_MODE4 == s_tTmAddrList.tm_mod)
    {
        s_tTmAddrList.la_pit_addr         = TM_MODE4_LA_PIT_ADDR;
        s_tTmAddrList.la_da_addr          = TM_MODE4_LA_DA_ADDR;
        s_tTmAddrList.la_ft_addr          = TM_MODE4_LA_FT_ADDR;
        s_tTmAddrList.la_pcs_addr         = TM_MODE4_LA_PCS_ADDR;
        s_tTmAddrList.da_pit_addr         = TM_MODE4_DA_PIT_ADDR;
        s_tTmAddrList.da_da_addr          = TM_MODE4_DA_DA_ADDR;
        s_tTmAddrList.da_pcs_addr         = TM_MODE4_DA_PCS_ADDR;
        s_tTmAddrList.service_area_addr   = TM_MODE4_SERVICE_AREA_ADDR;
        s_tTmAddrList.sa_intreg_addr      = TM_MODE4_SA_INTREG_ADDR;
    }
    //=====================================================================
    OS_CleanTM();

	return MUE_RESULT_OK;
}


static int DecPCS2Count(unsigned short u16PortAddr)
{
    unsigned int   da_addr = 0;
    unsigned short pcs2_val = 0;
    int iPortIndex = 0;
    unsigned short pi   = 0;

    iPortIndex = g_aiPortMap[u16PortAddr];

    if(iPortIndex >=PORT_NUMBER_MAX || iPortIndex<0)
    {
        return -1;
    }

    pi = s_ptPitInfo->u16PIVal[iPortIndex];

    da_addr = LA_DA_ADDR(s_tTmAddrList.la_da_addr, pi);

    pthread_mutex_lock(&g_tMutex);
    pcs2_val = OS_ReadWord(PCS2_ADDR(s_tTmAddrList.la_pcs_addr, pi));
    pthread_mutex_unlock(&g_tMutex);

    if(0xFFFF == pcs2_val)
    {
         s_ptPitInfo->u16Freshness[iPortIndex] =0;
         pthread_mutex_lock(&g_tMutex);
         OS_WriteWord(PCS2_ADDR(s_tTmAddrList.la_pcs_addr, pi), 0xFFFE);
         pthread_mutex_unlock(&g_tMutex);
    }
    else
    {
        if(s_ptPitInfo->u16Freshness[iPortIndex] <0x400)
        {
             s_ptPitInfo->u16Freshness[iPortIndex] ++;
        }
    }


    return 0;
}

static void * MVBCountFreshThread(void *arg)
{
    while(g_iThreadRun)
    {
        int i =0;

        for (i = 0; i < PORT_NUMBER_MAX; i++)
        {
            if (1 == s_ptPitInfo->bUsed[i] && s_ptPitInfo->bPortDir[i] == E_MVB_PORTDIR_SNK)
            {
                DecPCS2Count(s_ptPitInfo->u16PortAddr[i]);
            }
        }


        usleep(64000);
    }

    return NULL;
}


MUE_RESULT BBDC02C_Start(unsigned short device_address)
{
    unsigned short  regval = 0;
    
    
    /* 初始化SCR: Reset MVBC. 没有配置Mode之前使用Mode0的地址 */
	OS_WriteWord(TM_MODE0_SA_INTREG_ADDR+TM_SA_REG_OFFSET_SCR, 0x0000);
    usleep(1000);
    
    /* 初始化SCR: Configuration Mode */
	OS_WriteWord(TM_MODE0_SA_INTREG_ADDR+TM_SA_REG_OFFSET_SCR, 0x0001);

    printf("%s: Set Mode %d\n", __FUNCTION__, TM_MODE_DEFAULT);

    regval = OS_ReadWord(TM_MODE0_SA_INTREG_ADDR+TM_SA_REG_OFFSET_MCR);

    printf("%s: Get MCR Value: %02x\n", __FUNCTION__, regval);

    regval=0;

    regval &= ~(0x0007);
    /* 初始化MCR: Set Mode:2  Wurst */
    regval |= TM_MODE_DEFAULT;
    
    /* ICD */
    regval |= (1<<7);

    OS_WriteWord(TM_MODE0_SA_INTREG_ADDR+TM_SA_REG_OFFSET_MCR, regval);
	
	/* SCR */
	OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_SCR, 0x9401);
	
	/* DR: Decoder Register  */
	OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_DR, 0x2028);
    
	/* STSR: Sink-Time Supervision Register  */
    OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_STSR, g_u16STSR);

    /* Set Device Address */
    printf("Write Device Address:(R 0x%04x) 0x%04x\n", OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_DAOR),device_address);
    OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_DAOR, device_address);
    //OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_DAOR);
    usleep(10000);
    OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_DAOK, 0x0094);

    /* Read Back Device Address */
    regval = OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_DAOR);
    printf("Read Device Address1:0x%04x\n", regval);
    if ( regval != device_address )
    {
        printf("InitDevice[BBD] Error!  Write Device Address Error\n");
        return MUE_RESULT_ERROR;
    }
    /*
    usleep(1000000);
    printf("Read Device Address2:0x%04x\n", OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_DAOR));
    printf("Read Device Address key:0x%04x\n", OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_DAOK));
    */
    
	/* SCR  0x9403 */
	//OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_SCR, 0x9443);
	OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_SCR, 0x9403); 
	//OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_SCR, 0x9603);
	//OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_SCR, 0x8403);
	//OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_SCR, 0x95C3); 

    /* Interrupt */
    OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_IMR0, 0xFFFF); 
    OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_IMR1, 0xFF87);    


#ifdef BBD_NEED_FRESH_TIME
    if(0 == g_hRecvThread)
    {
        g_iThreadRun = 1;
        pthread_create(&g_hRecvThread, NULL, MVBCountFreshThread, NULL);
    }
#endif
    //=====================================================================
	return MUE_RESULT_OK; 
}



