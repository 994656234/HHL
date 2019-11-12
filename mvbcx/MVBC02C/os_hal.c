#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "os_hal.h"

#define PLATFORM_IMX6
//#define PLATFORM_72XX

#ifdef PLATFORM_72XX

    #include <asm/io.h>
    /*#define MVBBASE		0xfa000000*/
    #define MVBBASE		0xfb0e0000

    void OS_WriteWord(UINT32 addr, UINT16 value)
    {	
        printf("%s: addr = 0x%04x, value = %04x\n", __FUNCTION__, addr, value);
        *(volatile UINT16 *)(MVBBASE+addr) = value;
    }

    void OS_WriteByte(UINT32 addr, UINT8 value)
    {
        printf("%s: addr = 0x%04x, value = %04x\n", __FUNCTION__, addr, value);
        *(volatile UINT8 *)(MVBBASE+addr) = value;
    }

    UINT16 OS_ReadWord(UINT32 addr)
    {
        printf("%s: addr = 0x%04\n", __FUNCTION__, addr);
        return *(volatile UINT16 *)(MVBBASE+addr);
    }

    void OS_CleanTM()
    {
        UINT16 val = 0;
        UINT32   i = 0;
        for ( i = 0; i < 0xFFFF; )
        {
            *(volatile UINT16 *)(MVBBASE+i) = val;
            i+=2;
        }
        return;
    }

#elif defined PLATFORM_IMX6
    #include "bus_opt.h"
    #define MVBBASE		0x08000000
    void OS_WriteWord(UINT32 addr, UINT16 value)
    {
        //*(volatile unsigned short *)addr = value;
        //write16((volatile void *)MVBBASE,  &value, 1);
        ND_Dbg_Hal("<%s> [W] %08x, val=%04x\n", __FUNCTION__, MVBBASE+addr, value);
        write16((volatile void *)(MVBBASE+(addr<<1)),  &value, 1);
        return;
    }

    void OS_WriteByte(UINT32 addr, UINT8 value)
    {
        //*(volatile unsigned char *)addr = value;
        write8((volatile void *)(MVBBASE+(addr<<1)),  &value, 1);
    }

    UINT16 OS_ReadWord(UINT32 addr)
    {
        UINT16 val = 0;
        //return *(volatile unsigned short *)addr;	
        
        read16((volatile void *)(MVBBASE+(addr<<1)),  &val, 1);
        //printf("[Read  Reg] %08x, val=%04x\n", MVBBASE+addr, val);
        ND_Dbg_Hal("<%s> [R]  %08x, val=%04x\n", __FUNCTION__, MVBBASE+addr, val);
        return val;
    }

    void OS_CleanTM(void)
    {
        UINT16 val = 0;
        UINT32   i = 0;

        for ( i = 0; i < 0xFFFF; )
        {
            //writeMem(i, 0x0000);
            write16((volatile void *)MVBBASE+(i<<1),  &val, 1);
            i+=2;
        }
        return;
    }

#endif 

