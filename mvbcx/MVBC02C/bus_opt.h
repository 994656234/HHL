#ifndef __BUS_OPT_H__
    #define __BUS_OPT_H__

    #ifndef WORD
        #define WORD  short
    #endif

    #ifndef DWORD
        #define DWORD long
    #endif

    int read8(void *phyAddr, char *pcBuf, int len);
    int read16(void *phyAddr, WORD *pwBuf, int len);
    int read32(void *phyAddr, DWORD *pdwBuf, int len);

    int write8(void *phyAddr, char *pcBuf, int len);
    int write16(void *phyAddr, WORD *pwBuf, int len);
    int write32(void *phyAddr, DWORD *pdwBuf, int len);

#endif

