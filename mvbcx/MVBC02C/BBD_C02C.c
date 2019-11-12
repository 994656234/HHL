#include <stdio.h>
#include <stdlib.h>             /* srand, rand */
#include <string.h>
#include <time.h>               /* clock       */

#include "BBD_C02C.h"
#include "os_hal.h"

/* 大小端配置 */
#define BBD_BYTE_ODER_LE  1

/* MVBC02C寄存器基地址 */
static T_TM_ADDR_LIST s_tTmAddrList;

/* PortIndex表 */
static T_BBD_PIT_INFO  s_tPitInfo;

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
    unsigned short i;
    for ( i = 0; i < (PORT_NUMBER_MAX-1); i++ )
    {
        if((s_tPitInfo.u16PortAddr[i] == PortAddr)&&(s_tPitInfo.bPortDir[i] == PortDir)&&(s_tPitInfo.bUsed > 0))
        {
            return s_tPitInfo.u16PortSize[i];
           
        }
    }
    db_printf("Not find PortAddr\n");
    return E_MVBPORT_SIZE2;             //返回最小值
}

static unsigned short AllocPI(unsigned short * pPi, E_MVB_PORTDIR portdir,unsigned short portaddr, unsigned short portsize)
{
    int i = 0;
    unsigned short pi = 0;
    //===============================================
    for ( i = 0; i < (PORT_NUMBER_MAX-1); i++ )
    {
        if ( 0 == s_tPitInfo.bUsed[i] )
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
    s_tPitInfo.u16PortAddr[i] = portaddr;
    s_tPitInfo.u16PIVal[i]    = pi;
    s_tPitInfo.bUsed[i]       = 1;
    s_tPitInfo.u16PortSize[i] = portsize;
    s_tPitInfo.bPortDir[i]    = portdir;
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
    if(pos<PORT_NUMBER_MAX)
    {
        s_tPitInfo.u16PortAddr[pos] = 0;
        s_tPitInfo.u16PIVal[pos]    = 0;
        s_tPitInfo.bUsed[pos]       = 0;
        s_tPitInfo.u16PortSize[pos] = 0;
        s_tPitInfo.bPortDir[pos]    = 0;
    }
    return 0;
}

static int RegPort(E_MVB_PORTDIR portdir,unsigned short portaddr,unsigned short portsize)
{
    unsigned short pi      = 0;
    unsigned short pcs_val = 0;
    //===============================================
    if ( AllocPI(&pi,portdir, portaddr, portsize) < 0 )
    {

        return -1;
    } 

    //===============================================
    OS_WriteWord(s_tTmAddrList.la_pit_addr+(portaddr<<1), pi);
    
    pcs_val=0;
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
    //===============================================
    OS_WriteWord(PCS0_ADDR(s_tTmAddrList.la_pcs_addr, pi), pcs_val); 
    
    return 0;
}

static int UnRegPort(unsigned short portAddr)
{
    unsigned short pi = 0;
    UINT16 u16Value = 0;
    
    pi = OS_ReadWord(s_tTmAddrList.la_pit_addr+(portAddr<<1));
    if ( 0 == FreePI(pi) )
    {
         OS_WriteWord(s_tTmAddrList.la_pit_addr+(portAddr<<1), 0x0000);
        u16Value = OS_ReadWord(s_tTmAddrList.la_pit_addr+(portAddr<<1));
        if(0 != u16Value)
        {
            printf("[%s][%d] err\n");
            return -1;
        }
        
        OS_WriteWord(PCS0_ADDR(s_tTmAddrList.la_pcs_addr, pi), 0x0000); 
        u16Value = OS_ReadWord(PCS0_ADDR(s_tTmAddrList.la_pcs_addr, pi));
        
        if(0 != u16Value)
        {
            printf("[%s][%d] err\n");
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
	memset(&s_tTmAddrList, 0, sizeof(T_TM_ADDR_LIST));
    memset(&s_tPitInfo,    0, sizeof(T_BBD_PIT_INFO));

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

    //===============================================
    ePortSize=GetPortSize(u16PortAddr,E_MVB_PORTDIR_SRC);
    //===============================================
    
    /* 1st: Get pi */
    pi = OS_ReadWord(s_tTmAddrList.la_pit_addr+(u16PortAddr<<1));
    if ( 0 == pi )
    {
        return MUE_RESULT_ERROR;
    }

    ND_Dbg("****  %s: PA=%04x  PI=%04x, PCS1=%x, DA=%x\n", __FUNCTION__, u16PortAddr, pi,
    PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi), LA_DA_ADDR(s_tTmAddrList.la_da_addr, pi));

    /* 2nd: cache the value pcs1 */
    pcs1 = OS_ReadWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi));

    addr = LA_DA_ADDR(s_tTmAddrList.la_da_addr, pi);
    
    if ( !((pcs1>>6) & 0x01) )
    {
        addr |= 0x20;
        
        /* invert VP */
        pcs1 |= (1<<6);
    }
    else
    {
        /* invert VP */
        pcs1 &= ~(1<<6);
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

#if 0
	val_tmp = OS_ReadWord(addr);	

    if ( val != val_tmp )
    {
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

        ND_Dbg("****  %s:  2nd Write DA: val=%04x val_tmp=%4x readback=%04x \n", __FUNCTION__, 
                  val, val_tmp, OS_ReadWord(addr));

        brk = 1;
    }
 #endif   
    OS_WriteWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi), pcs1);

	ND_Dbg("****  %s:  addr=%04x  val = %04x, val_tmp = %04x\n", __FUNCTION__, addr, val, val_tmp);
    ND_Dbg("****  %s:  PCS0=%04x \n", __FUNCTION__, OS_ReadWord(PCS0_ADDR(s_tTmAddrList.la_pcs_addr, pi)));
    ND_Dbg("****  %s:  PCS1=%04x \n", __FUNCTION__, OS_ReadWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi)));
    ND_Dbg("****  %s:  PCS2=%04x \n", __FUNCTION__, OS_ReadWord(PCS2_ADDR(s_tTmAddrList.la_pcs_addr, pi)));

#if 0
	if ( brk )
    {
        ND_Dbg("****  %s:  SRC = %04x \n", __FUNCTION__, OS_ReadWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_SCR));
        
        return MUE_RESULT_ERROR;
	}

    pcs1_tmp = OS_ReadWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi));

    if ( pcs1_tmp != pcs1 )
    {
        ND_Err("****  %s: Read Back PCS1 Not Same, pcs1=%04x , %04x\n",__FUNCTION__, pcs1, pcs1_tmp);
        ND_Err("****  %s: Read Back PCS1 Not Same, PA=%04x  TACK = %04x\n", __FUNCTION__, u16PortAddr, OS_ReadWord(PCS2_ADDR(s_tTmAddrList.la_pcs_addr, pi)));
    }
#endif

	return MUE_RESULT_OK;
}


MUE_RESULT BBDC02C_Uninit(void)
{
    OS_CleanTM();
    return MUE_RESULT_OK;
}


MUE_RESULT BBDC02C_GetData(unsigned short u16PortAddr, unsigned char *p_port_status, unsigned char *pData, unsigned short  *pu8Freshness)
{
    E_MVB_PORTSIZE ePortSize;
        
    unsigned int   da_addr = 0;
    unsigned int   i    = 0;
    unsigned int   n    = 0;
    unsigned int   vp   = 0;
    unsigned short pi   = 0;
    unsigned short val  = 0;
    unsigned short pcs2_val = 0;
    unsigned char  sta1 = 0;
    unsigned char  sta2 = 0;
    
    //===============================================
    ePortSize=GetPortSize(u16PortAddr,E_MVB_PORTDIR_SNK);
    //===============================================
    printf("****ePortSize =%d\n", ePortSize);
    
    pi = OS_ReadWord(s_tTmAddrList.la_pit_addr+(u16PortAddr<<1));
    if ( 0 == pi )
    {
        return MUE_RESULT_ERROR;
    }
    printf("****  %s: PA=%04x  PI=%04x\n", __FUNCTION__, u16PortAddr, pi);

    da_addr = LA_DA_ADDR(s_tTmAddrList.la_da_addr, pi);
    /* 防止程序在读数据时，MVBC翻转了VP指针。这里读两次，如果两次都翻转了返回错误 */
    for ( n = 0; n < 2; n++ )
    {
        /* 判断端口数据更新 */
        pcs2_val = OS_ReadWord(PCS2_ADDR(s_tTmAddrList.la_pcs_addr, pi));
        /*ND_Inf("****  Read Data[1] Port[%04x] PCS2=%04x\n", u16PortAddr, pcs2_val);*/
        /* 端口数据被更新后PCS2的值会被MVBC置0xFFFF ,没有数据更新时，MVB卡会自动每一毫秒对pcs2_val的值做减1操作*/
        if ( pcs2_val == 0xFFFF )
        {
            *pu8Freshness = 0xFFFF & (~pcs2_val);
            *p_port_status=0;
        }
        else
        {
            *pu8Freshness = 0xFFFF & (~pcs2_val);
        }
#if 0
        if ( pcs2_val >= 1 )
        {
            pcs2_val--;
        }

        OS_WriteWord(PCS2_ADDR(s_tTmAddrList.la_pcs_addr, pi), pcs2_val);
#endif
        sta1 = 0;
        sta2 = 0;
        for ( i = 0; i < ePortSize;  )
        {
            val = OS_ReadWord(PCS1_ADDR(s_tTmAddrList.la_pcs_addr, pi));
            
            vp = (val>>6) & 0x01;
            if ( vp )
            {
                val = OS_ReadWord((da_addr|0x20)+i);
                sta1 = 1;
            }
            else
            {
                val = OS_ReadWord(da_addr+i);
                sta2 = 1;
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

            if ( sta1 && sta2 )
            {
                ND_Err("**** VP Changed In Recieve Port Data.[n=%d]\n", n);                
                break;
            }   
            
        }
        
        if ( sta1 != sta2 )
        {
            break;
        }
    }    

    /* 两次读取数据时VP都发生了翻转，让此次读取动作返回错误 */
    if ( sta1 && sta2 )
    {
        return MUE_RESULT_ERROR;
    }


    printf("============================OK\n");
	return MUE_RESULT_OK;

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
    s_tTmAddrList.la_pit_addr         = TM_MODE2_LA_PIT_ADDR;
    s_tTmAddrList.la_da_addr          = TM_MODE2_LA_DA_ADDR;
    s_tTmAddrList.la_ft_addr          = TM_MODE2_LA_FT_ADDR;
    s_tTmAddrList.la_pcs_addr         = TM_MODE2_LA_PCS_ADDR;
    s_tTmAddrList.da_pit_addr         = TM_MODE2_DA_PIT_ADDR;
    s_tTmAddrList.da_da_addr          = TM_MODE2_DA_DA_ADDR;
    s_tTmAddrList.da_pcs_addr         = TM_MODE2_DA_PCS_ADDR;
    s_tTmAddrList.service_area_addr   = TM_MODE2_SERVICE_AREA_ADDR;
    s_tTmAddrList.sa_intreg_addr      = TM_MODE2_SA_INTREG_ADDR;   
    //=====================================================================
    OS_CleanTM();
	return MUE_RESULT_OK;
}

MUE_RESULT BBDC02C_Start(unsigned short device_address)
{
    unsigned short  regval = 0;
    
    
    /* 初始化SCR: Reset MVBC. 没有配置Mode之前使用Mode0的地址 */
	OS_WriteWord(TM_MODE0_SA_INTREG_ADDR+TM_SA_REG_OFFSET_SCR, 0x0000);
    usleep(1000);
    
    /* 初始化SCR: Configuration Mode */
	OS_WriteWord(TM_MODE0_SA_INTREG_ADDR+TM_SA_REG_OFFSET_SCR, 0x0001);
    printf("%s: Set Mode %d\n", __FUNCTION__, E_TM_MODE2);

    regval = OS_ReadWord(TM_MODE0_SA_INTREG_ADDR+TM_SA_REG_OFFSET_MCR);
    printf("%s: Get MCR Value: %02x\n", __FUNCTION__, regval);

    regval=0;

    regval &= ~(0x0007);
    /* 初始化MCR: Set Mode:2  Wurst */
    regval |= 0x0002;
    
    /* ICD */
    regval |= (1<<7);

    OS_WriteWord(TM_MODE0_SA_INTREG_ADDR+TM_SA_REG_OFFSET_MCR, regval);
	
	/* SCR */
	OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_SCR, 0x9401);
	
	/* DR: Decoder Register  */
	OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_DR, 0x2028);
    
	/* STSR: Sink-Time Supervision Register  */
    OS_WriteWord(s_tTmAddrList.sa_intreg_addr+TM_SA_REG_OFFSET_STSR, 0x1400);

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
    //=====================================================================
	return MUE_RESULT_OK; 
}



