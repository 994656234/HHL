#ifndef __OS_HAL_H__

    #define __OS_HAL_H__

    #ifdef NETDBG_LIB_ENABLE

        #include "netDebug.h"
        #define ND_Dbg_Hal(format,...) NETDBG_DebugPrint(DEBUG_LEVEL_4,"Hal: "format"",##__VA_ARGS__);
        #define ND_Dbg(format,...)     NETDBG_DebugPrint(DEBUG_LEVEL_3,"DBG: "format"",##__VA_ARGS__);
        #define ND_Inf(format,...)     NETDBG_DebugPrint(DEBUG_LEVEL_2,"INF: "format"",##__VA_ARGS__);
        #define ND_Err(format,...)     NETDBG_DebugPrint(DEBUG_LEVEL_1,"ERR: "format"",##__VA_ARGS__);

    #else
        #define ND_Dbg_Hal(format,...) 
        #define ND_Dbg(format,...)     
        #define ND_Inf(format,...)     
        #define ND_Err(format,...)  
        
    #endif

    #define M_DEBUG_ENABLE 1
    #if M_DEBUG_ENABLE
        #define db_printf(fmt,args...)   printf(fmt, ##args)
    #else
        #define db_printf(fmt,...)  
    #endif

    /*函数返回值定义*/
    #define  FUNC_ERROR 	(0)
    #define  FUNC_OK 	    (1)

    /* ==========================================================================
     *
     *  Data Types
     *
     * ==========================================================================
     */

    /* --------------------------------------------------------------------------
     *  8-bit data types
     * --------------------------------------------------------------------------
     */
        typedef unsigned char       UINT8;
        typedef char                INT8;

    /* --------------------------------------------------------------------------
     *  16-bit data types
     * --------------------------------------------------------------------------
     */
        typedef unsigned short      UINT16;
        typedef short               INT16;

    /* --------------------------------------------------------------------------
     *  32-bit data types
     * --------------------------------------------------------------------------
     */
        typedef unsigned int        UINT32;
        typedef int                 INT32;

    /* --------------------------------------------------------------------------
     *  64-bit data types
     * --------------------------------------------------------------------------
     */
        typedef unsigned long long  UINT64;
        typedef long long           INT64;

    /* ==========================================================================
     *
     *  MVBC02C Memory Operate Function
     *
     * ==========================================================================
     */
 
    #if defined(__cplusplus)
    extern "C"
    {
    #endif

        void OS_WriteWord(UINT32 addr, UINT16 value);

        void OS_WriteByte(UINT32 addr, UINT8 value);

        UINT16 OS_ReadWord(UINT32 addr);

        void OS_CleanTM(void);

    #if defined(__cplusplus)
    }
    #endif

#endif
