#ifndef __BBDC02C_H__
    #define __BBDC02C_H__

    #include "os_hal.h"
    #include "tcn_def.h"
    #include "C02C_Def.h"
    /**  端口大小类型*/ 
    typedef enum _E_MVB_PORTSIZE{
        E_MVBPORT_SIZE2  = 2,     ///<  2 Bytes
        E_MVBPORT_SIZE4  = 4,     ///<  4 Bytes
        E_MVBPORT_SIZE8  = 8,     ///<  8 Bytes
        E_MVBPORT_SIZE16 = 16,    ///<  16 Bytes
        E_MVBPORT_SIZE32 = 32     ///<  32 Bytes
    }E_MVB_PORTSIZE;
        
        
     /**  端口类型*/
    typedef  enum _E_MVB_PORTDIR{
        E_MVB_PORTDIR_SNK = 0,        ///< Sink 端口   
        E_MVB_PORTDIR_SRC = 1         ///< Source 端口
    }E_MVB_PORTDIR;   
    
    
    typedef struct _T_C02C_PARAM{
        UINT32  tm_mod;                                     /* E_TM_MODE */
        void *  rev;
    }T_C02C_PARAM;

    typedef struct _T_BBD_PIT_INFO{
        unsigned short  u16PortAddr[PORT_NUMBER_MAX];
        unsigned short  u16PIVal[PORT_NUMBER_MAX];
        unsigned char   bUsed[PORT_NUMBER_MAX];             /* 0: free; !0: used */
        E_MVB_PORTSIZE  u16PortSize[PORT_NUMBER_MAX];       /* 端口大小：add by Wurst */
        E_MVB_PORTDIR   bPortDir[PORT_NUMBER_MAX];          /* 端口方向：0：Sink；1：Source */
        unsigned short  u16Freshness[PORT_NUMBER_MAX];
    }T_BBD_PIT_INFO;
    
    #if defined(__cplusplus)
        extern "C"
        {
    #endif
        
        int BBDC02C_GetMVBStatus(unsigned short devaddr, unsigned int * pDevState, unsigned char *  pLinkState);
        int BBDC02C_EnableBA(const char * fBinName);
        

        static E_MVB_PORTSIZE GetPortSize(unsigned short PortAddr, E_MVB_PORTDIR PortDir);                   //查找端口大小
        static unsigned short AllocPI(unsigned short * pPi, E_MVB_PORTDIR portdir,unsigned short portaddr, unsigned short portsize);
        static int FreePI(unsigned short PI);
        static int RegPort(E_MVB_PORTDIR portdir,unsigned short portaddr,unsigned short portsize);
        static int UnRegPort(unsigned short portAddr);
        static void * BBDC02C_Create();
        
        
        MUE_RESULT BBDC02C_PutData(unsigned short u16PortAddr , unsigned char *pData);
        MUE_RESULT BBDC02C_Uninit(void);
        MUE_RESULT BBDC02C_GetData(unsigned short u16PortAddr, unsigned char *p_port_status, unsigned char *pData, unsigned short  *pu16Freshness);
        MUE_RESULT BBDC02C_RegPort( E_MVB_PORTDIR portdir,unsigned short portaddr,unsigned short portsize);
        MUE_RESULT BBDC02C_UnRegPort(unsigned short portaddr);
        MUE_RESULT BBDC02C_Init(void);
        MUE_RESULT BBDC02C_Start(unsigned short device_address);

    #if defined(__cplusplus)
        }
    #endif

#endif

