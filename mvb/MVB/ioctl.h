/* Definition for IOCTL */
#define IOCTL_IO_SET_REGISTER		_IOW(0xD0, 11, int) //IO set Register
#define IOCTL_IO_READ_REGISTER		_IOW(0xD0, 12, int) //IO read Register
#define IOCTL_MEM_SET_REGISTER		_IOW(0xD0, 13, int) //MEM set Register
#define IOCTL_MEM_READ_REGISTER		_IOW(0xD0, 14, int) //MEM read Register
#define IOCTL_DIRECT_READ		_IOW(0xD0, 15, int) //Direct Read
#define IOCTL_DIRECT_WRITE		_IOW(0xD0, 16, int) //Direct Write
#define IOCTL_DMA_READ			_IOW(0xD0, 17, int) //DMA Read
#define IOCTL_DMA_WRITE			_IOW(0xD0, 18, int) //DMA Write

#define	SUCCESS			0
#define	DMA_ERR_TIMEOUT		-1
#define	ERR_DATA_PATTERN	-2

#define DMA_INTERRUPT		0x01
#define DMA_POLLING		0x00

#define TEST_READ	0x01
#define TEST_WRITE	0x00


/* Setting table */
typedef enum _MMAP_BAR
{
	BAR0,
	BAR1,
	BAR4,	//IO
	BAR5	//MEM
} MMAP_BAR;

typedef enum _REG_TYPE
{
	REG_8BIT,
	REG_16BIT,
	REG_32BIT

} REG_TYPE;

typedef enum _MAP_TYPE
{
	IO_MAP,
	MEM_MAP

} MAP_TYPE;

typedef enum _MMAP_CHANNEL
{
	CHANNEL0,
	CHANNEL1
} MMAP_CHANNEL;

/* Direct read/write */
typedef struct _LB_DIRECT_ACCESS
{
	MMAP_BAR    		Bar;
	MAP_TYPE    		MapType;
	unsigned long	   	Length;
	unsigned char   	DataBuffer[40];
	int			TestTimes;

	int			status;
    unsigned short addr;
} LB_DIRECT_ACCESS, *PLB_DIRECT_ACCESS;

/* DMA read/write */
typedef struct _LB_DMA_ACCESS
{
	MMAP_CHANNEL	Channel;		// DMA engine
	unsigned char	DataBuffer[65536];
	unsigned long	Offset;
	unsigned long	LocalAddress;

	unsigned char	Increase;		// Local Address Increase
	unsigned char	Demand;			// Demand Mode
	unsigned char	Space;			// Local Space
	unsigned char	DDRQ;			// DREQ/DACK

	unsigned int	Mode;			// True(1):INT False(0):Polling
	unsigned long	Size;
	int	  	TestTimes;

	unsigned long	InterruptMask;
	unsigned long	InterruptClear;

	int		status;
}LB_DMA_ACCESS, *PLB_DMA_ACCESS;

/* Register */
typedef struct _LB_REG
{
	unsigned long 	 	Offset;
	unsigned long		Value;
	MMAP_BAR 		Bar;
} LB_REG, *PLB_REG;

