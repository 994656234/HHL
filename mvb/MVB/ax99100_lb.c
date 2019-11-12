#include <stdio.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sys/time.h>
#include <fcntl.h>

#include "ax99100_lb.h"
#include "ioctl.h"
#include "mue_def.h"

typedef unsigned char BOOL;

static int devfd = -1;		//Device

struct local_test
{
	unsigned int	method;		//DMA or Direct
	unsigned int	direction;	//Read, Write or Both
	double 		timeuse;	    //Test Time
	double		potency;	    //Throughput
	unsigned int 	testTimes;	//Test Times
	unsigned int 	dma_mode;	//Interrupt/Polling

	LB_DMA_ACCESS		dma;
	LB_DIRECT_ACCESS	direct;

	struct timeval starttime,endtime;

	pthread_mutex_t test_lock;
};


/* Direct read/write */
static BOOL LBDirectRead (int handle, PLB_DIRECT_ACCESS LBReg, int TestTimes)
{
	LBReg->TestTimes	= TestTimes;

	if (ioctl(handle, IOCTL_DIRECT_READ, LBReg) < 0) {
		printf("IOCTL_DIRECT_READ failed!!!\n");
		return FALSE;
	}
	return TRUE;
}


static BOOL LBDirectWrite (int handle, PLB_DIRECT_ACCESS LBReg, int TestTimes)
{
	LBReg->TestTimes	= TestTimes;

	if (ioctl(handle, IOCTL_DIRECT_WRITE, LBReg) < 0) {
		printf("IOCTL_DIRECT_WRITE failed!!!\n");
		return FALSE;
	}
	return TRUE;
}


unsigned char ax99100_read_b (unsigned short addr)
{
    struct local_test item;

    item.direction = TEST_READ;
    item.testTimes = 1;
    item.direct.addr = addr;
    item.direct.Length = 1;
    item.direct.Bar = 0;
    LBDirectRead (devfd, &item.direct, item.testTimes);

    //printf("----read data 0x%x = 0x%x\n", addr, item.direct.DataBuffer[0]);
    return item.direct.DataBuffer[0];
}


void ax99100_write_b (unsigned char data, unsigned short addr)
{
    struct local_test item;

    item.direction = TEST_WRITE;
    item.testTimes = 1;
    item.direct.addr = addr;
    item.direct.Length = 1;
    item.direct.Bar = 0;
    item.direct.DataBuffer[0] = data;
    //printf("++++write data = %d\n", item.direct.DataBuffer[0]);
    LBDirectWrite (devfd, &item.direct, item.testTimes);
}


int pc104_init (void)
{
    if (-1 == devfd)
        devfd = open("/dev/locbus", O_RDONLY);

	if (-1 == devfd) {
		printf("Can't open AX99100 localbus\n");
		return MUE_RESULT_INIT;
	}
    return MUE_RESULT_OK;
}

int pc104_close(void)
{
    int ret = -1;
    if(devfd < 0)
        return ret;
    ret = close(devfd);
    devfd = -1;
    return ret;
}

