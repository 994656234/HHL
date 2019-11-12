/*
 *  linux/drivers/serial/99xx.h
 *
 *  Based on drivers/serial/8250.c by Russell King.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This code is modified to support AX99100 series serial devices
 */


/* Register */
#define REG_LCKSR		0x000
#define REG_PBAR0MR		0x004
	#define BARMR_BADDR	0xFFFFFFF0
#define REG_PBAR1MR		0x008
#define REG_LAS0CFGR		0x00C
	#define LASCFGR_INT_P	(1 << 0)
	#define LASCFGR_INT_L	(1 << 1)
	#define LASCFGR_DRQ_P	(1 << 2)
	#define LASCFGR_DAK_P	(1 << 3)
	#define LASCFGR_LSER	(1 << 4)
	#define LASCFGR_ENDIAN	(1 << 5)
	#define LASCFGR_BW16	(1 << 6)
#define REG_LAS0TIMR		0x010
#define REG_LAS0ADDR		0x014
#define REG_LAS1CFGR		0x018
#define REG_LAS1TIMR		0x01C
#define REG_LAS1ADDR		0x020
#define REG_LIEMR		0x024
	#define LIEMR_RDYPOL	(1 << 4)
	#define LIEMR_ALEPOL	(1 << 5)
	#define LIEMR_DMA0EN	(1 << 8)
	#define LIEMR_DMA1EN	(1 << 9)
	#define LIEMR_LRST	(1 << 14)
	#define LIEMR_SRST	(1 << 15)
	#define LIEMR_L0EINTEN	(1 << 16)
	#define LIEMR_L0RTOIEN	(1 << 17)
	#define LIEMR_L1EINTEN 	(1 << 18)
	#define LIEMR_L1RTOIEN	(1 << 19)
	#define LIEMR_D0DIEN	(1 << 24)
	#define LIEMR_D0AIEN	(1 << 25)
	#define LIEMR_D1DIEN	(1 << 26)
	#define LIEMR_D1AIEN	(1 << 27)

#define REG_LINTSR		0x28
	#define LINTSR_INT0AC	(1 << 0)
	#define LINTSR_L0RTO	(1 << 1)
	#define LINTSR_LINT1AC	(1 << 2)
	#define LINTSR_L1RTO	(1 << 3)
	#define LINTSR_DRQ0AS	(1 << 4)
	#define LINTSR_DRQ1AS	(1 << 5)
	#define LINTSR_INT0ST	(1 << 6)
	#define LINTSR_INT1ST	(1 << 7)
	#define LINTSR_D0ACT	(1 << 8)
	#define LINTSR_D0DON	(1 << 9)
	#define LINTSR_D0ABT	(1 << 10)
	#define LINTSR_D1ACT	(1 << 12)
	#define LINTSR_D1DON	(1 << 13)
	#define LINTSR_D1ABT	(1 << 14)
#define REG_D0PADR		0x030
#define REG_D0PUADR		0x034
#define REG_D0LADR		0x038
#define REG_D0CR		0x03C
#define REG_D1PADR		0x040
#define REG_D1PUADR		0x044
#define REG_D1LADR		0x048
#define REG_D1CR		0x04C
#define REG_DTRGR		0x050

/* DMA setting */
#define DMA_DIRECTION_READ	0x1
#define DMA_DIRECTION_WRITE	0x0
	#define DMACR_LAINC	(1 << 1)
	#define DMACR_DEM	(1 << 2)
	#define DMACR_LS0	(0 << 3)	//Local Space address 0
	#define DMACR_LS1	(1 << 3)	//Local Space address 1
	#define DMACR_DRQ0	(0 << 4)	//DREQ0/DACK1
	#define DMACR_DRQ1	(1 << 4)	//DREQ0/DACK1
#define	DMA_ABORT		(1 << 6)
#define	DMA_START		(1 << 7)
#define DMA_BUFFER_SZ		65535
#define CHANNEL_0		0x00
#define CHANNEL_1		0x01

#define PCI_SUBVEN_ID_AX99100	0x7000
#define PCI_SUBDEV_ID_AX99100	0xa000

#define OFFSET_EEPORM		0x0C8

#define FL_BASE5                0x0005

#if defined(__i386__) && (defined(CONFIG_M386) || defined(CONFIG_M486))
#define _INLINE_ inline
#else
#define _INLINE_
#endif

#define DEFAULT99100_BAUD 115200

/* Device */
#define	DEV_NAME	"ax99100"
#define	CLASS_NAME	"localbus"
#define NODE_NAME	"locbus"

/* Netlink */
#define NETLINK_TEST 17
#define MAX_PAYLOAD_SIZE 1024

/* Direction */
#define	DIRECT_READ	0x00
#define DIRECT_WRITE	0x01

#ifndef TRUE
#   define TRUE     (1==1)
#endif

#ifndef FALSE
#   define FALSE    (!TRUE)
#endif

unsigned char ax99100_read_b (unsigned short addr);
void ax99100_write_b (unsigned char data, unsigned short addr);
int pc104_init (void);
int pc104_close(void);


