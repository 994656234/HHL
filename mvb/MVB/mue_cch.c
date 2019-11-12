/* ==========================================================================
 *
 *  File      : MUE_CCH.C
 *
 *  Purpose   : MVB UART Emulation - Communication Channel
 *
 *  Project   : General TCN Driver Software
 *              - MVB UART Emulation Protocol (d-000206-nnnnnn)
 *              - TCN Software Architecture   (d-000487-nnnnnn)
 *
 *  Version   : d-000543-nnnnnn
 *
 *  Licence   : Duagon Software Licence (see file 'licence.txt')
 *
 * --------------------------------------------------------------------------
 *
 *  (C) COPYRIGHT, Duagon AG, CH-8953 Dietikon, Switzerland
 *  All Rights Reserved.
 *
 * ==========================================================================
 */


/* ==========================================================================
 *
 *  Pre-processor Definitions:
 *  --------------------------
 *  - MUE_CCH_PRINT_FCT_CALL      - printout of function call
 *                                  (0=disable, 1=enable)
 *  - MUE_CCH_PRINT_FCT_RETURN    - printout of function return
 *                                  (0=disable, 1=enable)
 *  - MUE_CCH_PRINT_FCT_PARAMETER - printout of function parameter
 *                                  (0=disable, 1=enable)
 *  - MUE_CCH_PRINT_FCT_INFO      - printout of function information
 *                                  (0=disable, 1=enable)
 *  - MUE_CCH_PRINT_REG           - printout of register access
 *                                  (0=disable, 1=enable)
 *
 * ==========================================================================
 */
#define MUE_CCH_PRINT_FCT_CALL      0
#define MUE_CCH_PRINT_FCT_RETURN    0
#define MUE_CCH_PRINT_FCT_PARAMETER 0
#define MUE_CCH_PRINT_FCT_INFO      0
#define MUE_CCH_PRINT_REG           0


/* ==========================================================================
 *
 *  Project specific Definitions used for Conditional Compiling
 *
 * ==========================================================================
 */
#ifdef TCN_PRJ
#   include "tcn_prj.h"
#endif


/* ==========================================================================
 *
 *  Include Files
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  TCN Software Architecture
 * --------------------------------------------------------------------------
 */
#include "tcn_def.h"

/* --------------------------------------------------------------------------
 *  MVB UART Emulation
 * --------------------------------------------------------------------------
 */
#include "mue_def.h"
#include "mue_osl.h"
#include "mue_cch.h"
#include "ax99100_lb.h"
/* --------------------------------------------------------------------------
 *  Register Access of MVB UART Emulation
 * --------------------------------------------------------------------------
 */
#include <string.h> /* memset    */
#include <sys/io.h> /* inb, outb */
#include <time.h>   /* time      */


/* ==========================================================================
 *
 *  Local Variables
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Access to register set of MVB UART Emulation:
 *  - cch_reg_data            : address of MVB UART Emulation register "DATA"
 *  - cch_reg_stat            : address of MVB UART Emulation register "STAT"
 *  - cch_reg_stat_txready    : mask value of register "STAT" indicating
 *                              "ready to transmit"
 *  - cch_reg_stat_rxready    : mask value of register "STAT" indicating
 *                              "ready to receive"
 *  - cch_time_start          : used for timeout
 * --------------------------------------------------------------------------
 */
TCN_DECL_LOCAL TCN_DECL_CONST \
    unsigned short  cch_reg_data = (unsigned short)0x4F8; /* reg-index 0 */
TCN_DECL_LOCAL TCN_DECL_CONST \
    unsigned short  cch_reg_stat = (unsigned short)0x4FD; /* reg-index 1 */

TCN_DECL_LOCAL TCN_DECL_CONST \
    UNSIGNED8   cch_reg_stat_txready = (UNSIGNED8)0x60;
TCN_DECL_LOCAL TCN_DECL_CONST \
    UNSIGNED8   cch_reg_stat_rxready = (UNSIGNED8)0x01;

TCN_DECL_LOCAL \
    UNSIGNED32  cch_time_start;


/* ==========================================================================
 *
 *  Local Procedures
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Procedure : cch_reg_stat_ready
 *
 *  Purpose   : Check if MVB UART Emulation register "STAT" indicates ready.
 *
 *  Syntax    : UNSIGNED8
 *              cch_reg_stat_ready
 *              (
 *                  UNSIGNED8   card_id,
 *                  UNSIGNED8   reg_stat_mask
 *              );
 * 读 cch_reg_stat寄存器   ，并  & reg_stat_mask
 *  Input     : card_id       - card identifier
 *              reg_stat_mask - mask indicating ready
 *
 *  Return    : 1 = ready, 0 = not ready
 * --------------------------------------------------------------------------
 */
TCN_DECL_LOCAL
UNSIGNED8
cch_reg_stat_ready
(
	UNSIGNED8   card_id,
	UNSIGNED8   reg_stat_mask
)
{
	UNSIGNED8   result;
    UNSIGNED8   reg_stat_value;

    TCN_UNUSED_PARAMETER(UNSIGNED8, card_id);

    result = 0;

    /* ----------------------------------------------------------------------
     *  Read value from MVB UART Emulation register "STAT".
     * ----------------------------------------------------------------------
     */
    //reg_stat_value = (UNSIGNED8)inb(cch_reg_stat); //sjd

    reg_stat_value = ax99100_read_b (cch_reg_stat); // sjd
    //printf("=====status = 0x%x\n",reg_stat_value);
    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_REG)
    MUE_OSL_PRINTF("[%02X]", reg_stat_value);
#endif /* #if (1 == MUE_CCH_PRINT_REG) */

    /* ----------------------------------------------------------------------
     *  Check for ready.
     * ----------------------------------------------------------------------
     */
    if ((reg_stat_value & reg_stat_mask) == reg_stat_mask)
    {
        result = 1;
    } /* if ((reg_stat_value & reg_stat_mask) == reg_stat_mask) */

    return(result);
} /* cch_reg_stat_ready */


/* --------------------------------------------------------------------------
 *  Procedure : cch_put_data8
 *
 *  Purpose   : Write a data packet to MVB UART Emulation register "DATA"
 *              using 8-bit access.
 *
 *  Syntax    : void
 *              cch_put_data8
 *              (
 *                  UNSIGNED8   card_id,
 *                  UNSIGNED16  size,
 *                  UNSIGNED8   *p_packet
 *              );
 *  发送数据包
 *  Input     : card_id  - card identifier
 *              size     - size of data packet (number of bytes)
 *              p_packet - pointer to data packet
 * --------------------------------------------------------------------------
 */
TCN_DECL_LOCAL
void
cch_put_data8
(
	UNSIGNED8   card_id,
	UNSIGNED16  size,
	UNSIGNED8   *p_packet
)
{
    UNSIGNED8*  p8;
    UNSIGNED16  bytes_written;

    TCN_UNUSED_PARAMETER(UNSIGNED8, card_id);

    p8 = p_packet;
    bytes_written = 0;
    while (bytes_written < size)
    {
        /* ------------------------------------------------------------------
         *  Write value to MVB UART Emulation register "DATA".
         * ------------------------------------------------------------------
         */
        //outb((unsigned char)*p8, cch_reg_data); // sjd:
        ax99100_write_b ((unsigned char)*p8, cch_reg_data);// sjd:

        /* ------------------------------------------------------------------
         *  Debugging output.
         * ------------------------------------------------------------------
         */
#if (1 == MUE_CCH_PRINT_REG)
        MUE_OSL_PRINTF("(%02X)", *p8);
#endif /* #if (1 == MUE_CCH_PRINT_REG) */

        p8++;
        bytes_written++;


        //while(!cch_reg_stat_ready(card_id, cch_reg_stat_txready)); //sjd

            /*do{
                UNSIGNED32 cch_time_stop = (UNSIGNED32)time(NULL);
                if (!cch_reg_stat_ready(card_id, cch_reg_stat_txready))
                {
                    while((UNSIGNED32)time(NULL) - cch_time_stop < 2);
                }
                else
                {
                    break;
                }

            }while(!cch_reg_stat_ready(card_id, cch_reg_stat_txready));*/


    } /* while (bytes_written < size) */
} /* cch_put_reg_data8 */


/* --------------------------------------------------------------------------
 *  Procedure : cch_get_data8
 *
 *  Purpose   : Read a data packet from MVB UART Emulation register "DATA"
 *              using 8-bit access.
 *
 *  Syntax    : void
 *              cch_get_data8
 *              (
 *                  UNSIGNED8   card_id,
 *                  UNSIGNED16  size,
 *                  UNSIGNED8   *p_packet
 *              );
 *  将size个字节读到p_packet中去
 *  Input     : card_id  - card identifier
 *              size     - size of data packet (number of bytes)
 *              p_packet - pointer to data packet
 * --------------------------------------------------------------------------
 */
TCN_DECL_LOCAL
void
cch_get_data8
(
	UNSIGNED8   card_id,
	UNSIGNED16  size,
	UNSIGNED8   *p_packet
)
{
    UNSIGNED8   *p8;
    UNSIGNED16  bytes_read;

    TCN_UNUSED_PARAMETER(UNSIGNED8, card_id);

    p8 = p_packet;
    bytes_read = 0;
    while (bytes_read < size)
    {
        /* ------------------------------------------------------------------
         *  Read value from MVB UART Emulation register "DATA".
         * ------------------------------------------------------------------
         */
        //*p8 = (UNSIGNED8)inb(cch_reg_data); //sjd

        *p8 = ax99100_read_b (cch_reg_data);// sjd
        //printf("----%d:read data = 0x%x", bytes_read, *p8);
        /* ------------------------------------------------------------------
         *  Debugging output.
         * ------------------------------------------------------------------
         */
#if (1 == MUE_CCH_PRINT_REG)
        MUE_OSL_PRINTF("[%02X]", *p8);
#endif /* #if (1 == MUE_CCH_PRINT_REG) */

        p8++;
        bytes_read++;
        //if (bytes_read == size)
        //    break;
        //while(!cch_reg_stat_ready(card_id, cch_reg_stat_rxready)); //sjd

    } /* while (bytes_written < size) */
} /* cch_get_data8 */


/* --------------------------------------------------------------------------
 *  Procedure : cch_cch_timeout_start
 *
 *  Purpose   : Initialise the timeout.
 * 初始化cch_time_start变量
 *  Syntax    : void
 *              cch_timeout_start (void);
 * --------------------------------------------------------------------------
 */
TCN_DECL_LOCAL
void
cch_timeout_start
(
	UNSIGNED8 card_id
)
{
    TCN_UNUSED_PARAMETER(UNSIGNED8, card_id);

    cch_time_start = (UNSIGNED32)time(NULL);

} /* cch_timeout_start */


/* --------------------------------------------------------------------------
 *  Procedure : cch_timeout_expired
 *
 *  Purpose   : Initialise the timeout.
 *
 *  Syntax    : UNSIGNED8
 *              cch_timeout_expired (void);
 *  得到cch_time_stop并与cch_time_start比较，用于超时判断
 *  Return    : 0 = timeout not expired, 1 = timeout expired
 * --------------------------------------------------------------------------
 */
TCN_DECL_LOCAL
UNSIGNED8
cch_timeout_expired
(
	UNSIGNED8   card_id
)
{
    UNSIGNED8   result;
    UNSIGNED32  cch_time_stop;
    UNSIGNED32  cch_time_diff;

    TCN_UNUSED_PARAMETER(UNSIGNED8, card_id);

    result = 0;

    cch_time_stop = (UNSIGNED32)time(NULL);
    cch_time_diff = (UNSIGNED32)(cch_time_stop - cch_time_start);

    if (1 < cch_time_diff)
    {
        result = 1;
    } /* if (1 < cch_time_diff) */

    return(result);

} /* cch_timeout_expired */


/* ==========================================================================
 *
 *  Public Procedures
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Procedure : mue_cch_init
 *
 *  Purpose   : Initialises communication channel.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_cch_init
(
	UNSIGNED8   card_id
)
{
    MUE_RESULT  mue_result;
    int         res;

    TCN_UNUSED_PARAMETER(UNSIGNED8, card_id);

    mue_result = MUE_RESULT_OK;

    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_FCT_CALL)
    MUE_OSL_PRINTF("mue_cch_init(card_id=%d)\n", card_id);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_CALL) */

    /* ----------------------------------------------------------------------
     *  Enable access to register set of MVB UART Emulation.
     * ----------------------------------------------------------------------
     */
    //res = iopl(3); //sjd:
    res = 0;
    if (0 != res)
    {
#if (1 == MUE_CCH_PRINT_FCT_INFO)
        MUE_OSL_PRINTF("ERROR: iopl()=%d\n", res);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_INFO) */
        mue_result = MUE_RESULT_INIT;
    } /* end "if (0 != res)" */

    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_FCT_RETURN)
    MUE_OSL_PRINTF("mue_cch_init(card_id=%d)=%d\n", \
        card_id, mue_result);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_RETURN) */

    mue_result = pc104_init(); // sjd
    return(mue_result);

} /* mue_cch_init */


/* --------------------------------------------------------------------------
 *  Procedure : mue_cch_close
 *
 *  Purpose   : Closes communication channel.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_cch_close
(
	UNSIGNED8   card_id
)
{
    MUE_RESULT  mue_result;

    TCN_UNUSED_PARAMETER(UNSIGNED8, card_id);

    mue_result = MUE_RESULT_OK;

    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_FCT_CALL)
    MUE_OSL_PRINTF("mue_cch_close(card_id=%d)\n", card_id);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_CALL) */

    /* ----------------------------------------------------------------------
     *  Nothing to do.
     * ----------------------------------------------------------------------
     */
    pc104_close();

    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_FCT_RETURN)
    MUE_OSL_PRINTF("mue_cch_close(card_id=%d)=%d\n", \
        card_id, mue_result);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_RETURN) */

    return(mue_result);

} /* mue_cch_close */


/* --------------------------------------------------------------------------
 *  Procedure : mue_cch_clean_up
 *
 *  Purpose   : Performs a clean-up of the communication channel.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_cch_clean_up
(
	UNSIGNED8   card_id
)
{
    MUE_RESULT  mue_result;
    UNSIGNED8   packet[35];
    UNSIGNED16  size;

    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_FCT_CALL)
    MUE_OSL_PRINTF("mue_cch_clean_up(card_id=%d)\n", card_id);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_CALL) */

    mue_result = MUE_RESULT_OK;

    /* ----------------------------------------------------------------------
     *  Facts for devices based on MVB UART Emulation with register set:
     *  - The size of the longest MVB UART Emulation Command is 35 bytes.
     *  - If a MVB UART Emulation Command will response with data, then
     *    this data located in the UART RX-FIFO can be cleared by sending
     *    any byte.
     *  Assuming following scenario:
     *  - At least one byte of a MVB UART Emulation Command has been sent.
     *  - In this case 34 bytes must be send to synchronise the MVB UART
     *    Emulation Protocol.
     *  Conclusion:
     *  - Transmit at least 35 bytes, which will synchronise the MVB UART
     *    Emulation Protocol and clear the UART RX-FIFO.
     *  - Don't check for TX-ready before transmitting, since interruption
     *    of a previous transmit communication may result in TX-status
     *    "not ready".
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == mue_result)
    {
        size = 35;
        memset((void*)packet, 0, size);
        cch_put_data8(card_id, size, packet);//写入35个0
    } /* if (MUE_RESULT_OK == mue_result) */

    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_FCT_RETURN)
    MUE_OSL_PRINTF("mue_cch_clean_up(card_id=%d)=%d\n", \
        card_id, mue_result);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_RETURN) */

    return(mue_result);

} /* mue_cch_clean_up */


/* --------------------------------------------------------------------------
 *  Procedure : mue_cch_transmit
 *
 *  Purpose   : Transmits data packet to communication channel.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_cch_transmit
(
	UNSIGNED8   card_id,
	UNSIGNED8   size,
	WORD8       *p_packet
)
{
    MUE_RESULT  mue_result;
    UNSIGNED8   txready;

    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_FCT_CALL)
    MUE_OSL_PRINTF("mue_cch_transmit(card_id=%d)\n", card_id);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_CALL) */
#if (1 == MUE_CCH_PRINT_FCT_PARAMETER)
    MUE_OSL_PRINTF("- size  =%d\n", size);
    if (0 < size)
    {
        MUE_OSL_PRINTF(                                             \
            "- packet=0x%02X,0x%02X,0x%02X,0x%02X,"                 \
                     "0x%02X,0x%02X,0x%02X,0x%02X\n",               \
            p_packet[ 0], p_packet[ 1], p_packet[ 2], p_packet[ 3], \
            p_packet[ 4], p_packet[ 5], p_packet[ 6], p_packet[ 7]);
    } /* if (0 < size) */
    if (7 < size)
    {
        MUE_OSL_PRINTF(                                             \
            "         0x%02X,0x%02X,0x%02X,0x%02X,"                 \
                     "0x%02X,0x%02X,0x%02X,0x%02X\n",               \
            p_packet[ 8], p_packet[ 9], p_packet[10], p_packet[11], \
            p_packet[12], p_packet[13], p_packet[14], p_packet[15]);
    } /* if (7 < size) */
    if (15 < size)
    {
        MUE_OSL_PRINTF(                                             \
            "         0x%02X,0x%02X,0x%02X,0x%02X,"                 \
                     "0x%02X,0x%02X,0x%02X,0x%02X\n",               \
            p_packet[16], p_packet[17], p_packet[18], p_packet[19], \
            p_packet[20], p_packet[21], p_packet[22], p_packet[23]);
    } /* if (15 < size) */
    if (23 < size)
    {
        MUE_OSL_PRINTF(                                             \
            "         0x%02X,0x%02X,0x%02X,0x%02X,"                 \
                     "0x%02X,0x%02X,0x%02X,0x%02X\n",               \
            p_packet[24], p_packet[25], p_packet[26], p_packet[27], \
            p_packet[28], p_packet[29], p_packet[30], p_packet[31]);
    } /* if (23 < size) */
    if (31 < size)
    {
        MUE_OSL_PRINTF(                                             \
            "         0x%02X,0x%02X,0x%02X,0x%02X\n",               \
            p_packet[32], p_packet[33], p_packet[34], p_packet[35]);
    } /* if (31 < size) */
#endif /* #if (1 == MUE_CCH_PRINT_FCT_PARAMETER) */

    /* ----------------------------------------------------------------------
     *  Transmit data packet.
     * ----------------------------------------------------------------------
     */
    if (0 == size)
    {
        mue_result = MUE_RESULT_OK;
    } /* if (0 == size) */
    else
    {
        /* ------------------------------------------------------------------
         *  Poll for TX-ready or timeout.
         * ------------------------------------------------------------------
         */
        txready = 0;
        cch_timeout_start(card_id);//设置定时器初值，作超时判断使用
        while (1)//判断是否可以发送
        {
            if (cch_reg_stat_ready(card_id, cch_reg_stat_txready))//读cch_reg_stat寄存器的值，相当于if((*cch_reg_stat & cch_reg_stat_txready) == cch_reg_stat_txready)
            {
                txready = 1;
                break;
            } /* if (cch_reg_stat_ready(...)) */

            if (cch_timeout_expired(card_id))//判断是否超时，1超时，0未超时
            {
                if (cch_reg_stat_ready(card_id, cch_reg_stat_txready))//if((*cch_reg_stat & cch_reg_stat_txready) == cch_reg_stat_txready)
                {
                    txready = 1;
                } /* if (cch_reg_stat_ready(...)) */
                break;
            } /* if (cch_timeout_expired(card_id)) */

        } /* while (1) */

        /* ------------------------------------------------------------------
         *  Put data packet to UART FIFO.
         * ------------------------------------------------------------------
         */
        //printf("===========txready===============\n"); //sjd
        if (txready)
        {
            cch_put_data8(card_id, (UNSIGNED16)size, (UNSIGNED8*)p_packet);//数据发送，一次写一个字节，写完size大小后返回
            mue_result = MUE_RESULT_OK;
        } /* if (txready) */
        else
        {
            mue_result = MUE_RESULT_TRANSMIT_TIMEOUT;
        } /* else */

    } /* else */

    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_FCT_RETURN)
    MUE_OSL_PRINTF("mue_cch_transmit(card_id=%d)=%d\n", \
        card_id, mue_result);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_RETURN) */

    return(mue_result);

} /* mue_cch_transmit */


/* --------------------------------------------------------------------------
 *  Procedure : mue_cch_receive
 *
 *  Purpose   : Receives data packet from communication channel.
 * 判断是否可以接收数据，若可以则接size大小的数据到缓冲区
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_cch_receive
(
	UNSIGNED8   card_id,
	UNSIGNED8   size,
	WORD8       *p_packet
)
{
    MUE_RESULT  mue_result;
    UNSIGNED8   rxready;

    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_FCT_CALL)
    MUE_OSL_PRINTF("mue_cch_receive(card_id=%d)\n", card_id);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_CALL) */
#if (1 == MUE_CCH_PRINT_FCT_PARAMETER)
    MUE_OSL_PRINTF("- size  =%d\n", size);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_PARAMETER) */

    /* ----------------------------------------------------------------------
     *  Receive data packet.
     * ----------------------------------------------------------------------
     */
    if (0 == size)
    {
        mue_result = MUE_RESULT_OK;
    } /* if (0 == size) */
    else
    {
        /* ------------------------------------------------------------------
         *  Poll for RX-ready or timeout.
         * ------------------------------------------------------------------
         */
        rxready = 0;
        cch_timeout_start(card_id);
        //判断是否可以接受数据
        while (1)
        {
            if (cch_reg_stat_ready(card_id, cch_reg_stat_rxready))//if((*cch_reg_stat &cch_reg_stat_rxready) == cch_reg_stat_rxready)
            {
                rxready = 1;
                break;
            } /* if (cch_reg_stat_ready(...)) */

            if (cch_timeout_expired(card_id))// 判断是否超时
            {
                if (cch_reg_stat_ready(card_id, cch_reg_stat_rxready))
                {
                    rxready = 1;
                } /* if (cch_reg_stat_ready(...)) */
                break;
            } /* if (cch_timeout_expired(card_id)) */

        } /* while (1) */

        /* ------------------------------------------------------------------
         *  Get data packet from UART FIFO.
         * ------------------------------------------------------------------
         */
        if (rxready)
        {
            cch_get_data8(card_id, (UNSIGNED16)size, (UNSIGNED8*)p_packet);
            mue_result = MUE_RESULT_OK;
        } /* if (rxready) */
        else
        {
            mue_result = MUE_RESULT_RECEIVE_TIMEOUT;
        } /* else */

    } /* else */

    /* ----------------------------------------------------------------------
     *  Debugging output.
     * ----------------------------------------------------------------------
     */
#if (1 == MUE_CCH_PRINT_FCT_RETURN)
    MUE_OSL_PRINTF("mue_cch_receive(card_id=%d)=%d\n", \
        card_id, mue_result);
#endif /* #if (1 == MUE_CCH_PRINT_FCT_RETURN) */
#if (1 == MUE_CCH_PRINT_FCT_PARAMETER)
    MUE_OSL_PRINTF("- size  =%d\n", size);
    if (0 < size)
    {
        MUE_OSL_PRINTF(                                             \
            "- packet=0x%02X,0x%02X,0x%02X,0x%02X,"                 \
                     "0x%02X,0x%02X,0x%02X,0x%02X\n",               \
            p_packet[ 0], p_packet[ 1], p_packet[ 2], p_packet[ 3], \
            p_packet[ 4], p_packet[ 5], p_packet[ 6], p_packet[ 7]);
    } /* if (0 < size) */
    if (7 < size)
    {
        MUE_OSL_PRINTF(                                             \
            "         0x%02X,0x%02X,0x%02X,0x%02X,"                 \
                     "0x%02X,0x%02X,0x%02X,0x%02X\n",               \
            p_packet[ 8], p_packet[ 9], p_packet[10], p_packet[11], \
            p_packet[12], p_packet[13], p_packet[14], p_packet[15]);
    } /* if (7 < size) */
    if (15 < size)
    {
        MUE_OSL_PRINTF(                                             \
            "         0x%02X,0x%02X,0x%02X,0x%02X,"                 \
                     "0x%02X,0x%02X,0x%02X,0x%02X\n",               \
            p_packet[16], p_packet[17], p_packet[18], p_packet[19], \
            p_packet[20], p_packet[21], p_packet[22], p_packet[23]);
    } /* if (15 < size) */
    if (23 < size)
    {
        MUE_OSL_PRINTF(                                             \
            "         0x%02X,0x%02X,0x%02X,0x%02X,"                 \
                     "0x%02X,0x%02X,0x%02X,0x%02X\n",               \
            p_packet[24], p_packet[25], p_packet[26], p_packet[27], \
            p_packet[28], p_packet[29], p_packet[30], p_packet[31]);
    } /* if (23 < size) */
    if (31 < size)
    {
        MUE_OSL_PRINTF(                                             \
            "         0x%02X,0x%02X,0x%02X,0x%02X\n",               \
            p_packet[32], p_packet[33], p_packet[34], p_packet[35]);
    } /* if (31 < size) */
#endif /* #if (1 == MUE_CCH_PRINT_FCT_PARAMETER) */

    return(mue_result);

} /* mue_cch_receive */
