#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "bus_opt.h"

#define MAX_PACKET_LEN 1024
#define DEVICE_BUS_NAME  "/dev/device_bus"

#define BUS_READ_CMD  0x11
#define BUS_WRITE_CMD 0x12
#define BUS_QUERY_CMD 0x13
#define BUS_ADDR_CMD  0x14


static int read_bus(void *phyAddr, char *pcBuf, int len)
{
    int ret = 0;
    int fd = 0;
    
    fd = open(DEVICE_BUS_NAME, O_RDWR);
    if (fd < 0)
    {
        perror("open driver error:");	
        return -1;
    }
    ret = ioctl(fd, BUS_ADDR_CMD, (long)phyAddr);
    if (ret >= 0)
    {
        ret = read(fd, pcBuf, len);
    }
    close(fd);
    
    return ret;
}

static int write_bus(void *phyAddr, char *pcBuf, int len)
{
    int ret = 0;
    int fd = 0;
    
    fd = open(DEVICE_BUS_NAME, O_RDWR);
    if (fd < 0)
    {
        perror("open driver error:");	
        return -1;
    }
    ret = ioctl(fd, BUS_ADDR_CMD, (long)phyAddr);
    if (ret >= 0)
    {
        ret = write(fd, pcBuf, len);
    }
    close(fd);
    
    return ret;
}

int read8(void *phyAddr, char *pcBuf, int len)
{
    int iSize = len;
    int iRecvLen = 0;
    char *ptr = (char *)pcBuf;
    
    while (iSize > 0)
    {
        iRecvLen = iSize > MAX_PACKET_LEN ? MAX_PACKET_LEN : iSize;
        iRecvLen = read_bus(phyAddr, ptr, iRecvLen);
        if (iRecvLen > 0)
        {
            iSize -= iRecvLen;
            ptr += iRecvLen;
        }
        else
        {
            return iRecvLen;
        }
    }
    return (len - iSize);
}

int read16(void *phyAddr, WORD *pwBuf, int len)
{
    int iSize = len << 1;
    int iRecvLen = 0;
    char *ptr = (char *)pwBuf;
    
    while (iSize > 0)
    {
        iRecvLen = iSize > MAX_PACKET_LEN ? MAX_PACKET_LEN : iSize;
        iRecvLen = read_bus(phyAddr, ptr, iRecvLen);
        if (iRecvLen > 0)
        {
            iSize -= iRecvLen;
            ptr += iRecvLen;
        }
        else
        {
            return iRecvLen;
        }
    }
    return (len << 1 - iSize) >> 1;
}


int read32(void *phyAddr, DWORD *pdwBuf, int len)
{
    int iSize = len << 2;
    int iRecvLen = 0;
    char *ptr = (char *)pdwBuf;
    
    while (iSize > 0)
    {
        iRecvLen = iSize > MAX_PACKET_LEN ? MAX_PACKET_LEN : iSize;
        iRecvLen = read_bus(phyAddr, ptr, iRecvLen);
        if (iRecvLen > 0)
        {
            iSize -= iRecvLen;
            ptr += iRecvLen;
        }
        else
        {
            return iRecvLen;
        }
    }
    return (len << 2 - iSize) >> 2;
}

int write8(void *phyAddr, char *pcBuf, int len)
{
    int iSize = len;
    int iSendLen = 0;
    char *ptr = pcBuf;
    
    while (iSize > 0)
    {
        iSendLen = iSize > MAX_PACKET_LEN ? MAX_PACKET_LEN : iSize;
        iSendLen = write_bus(phyAddr, ptr, iSendLen);
        if (iSendLen > 0)
        {
            iSize -= iSendLen;
            ptr += iSendLen;
        }
        else
        {
            return iSendLen;
        }
    }
    return (len - iSize);
}

int write16(void *phyAddr, WORD *pwBuf, int len)
{
    int iSize = len << 1;
    int iSendLen = 0;
    char *ptr = (char *)pwBuf;
    
    while (iSize > 0)
    {
        iSendLen = iSize > MAX_PACKET_LEN ? MAX_PACKET_LEN : iSize;
        iSendLen = write_bus(phyAddr, ptr, iSendLen);
        if (iSendLen > 0)
        {
            iSize -= iSendLen;
            ptr += iSendLen;
        }
        else
        {
            return iSendLen;
        }
    }
    return (len << 1 - iSize) >> 1;
}

int write32(void *phyAddr, DWORD *pdwBuf, int len)
{
    int iSize = len << 2;
    int iSendLen = 0;
    char *ptr = (char *)pdwBuf;
    
    while (iSize > 0)
    {
        iSendLen = iSize > MAX_PACKET_LEN ? MAX_PACKET_LEN : iSize;
        iSendLen = write_bus(phyAddr, ptr, iSendLen);
        if (iSendLen > 0)
        {
            iSize -= iSendLen;
            ptr += iSendLen;
        }
        else
        {
            return iSendLen;
        }
    }
    return (len << 2 - iSize) >> 2;
}

