 /*==========================================================================
 *
 *  File      : MUE_APP.C
 *
 *  Purpose   : MVB UART Emulation - Application Example
 *
 *  Project   : Host Driver Software MUE for MDFULL
 *              - MVB UART Emulation Protocol (d-000206-nnnnnn)
 *
 *  License   : Duagon Software License (see file 'license.txt')
 *
 * --------------------------------------------------------------------------
 *
 *  (C) COPYRIGHT, duagon AG, CH-8953 Dietikon, Switzerland
 *  All Rights Reserved.
 *
 * ==========================================================================
 */


/* ==========================================================================
 *
 *  Pre-processor Definitions:
 *  --------------------------
 *  - MUE_APP_PRINT   - debug printouts
 *
 * ==========================================================================
 */
//#define MUE_APP_PRINT


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
#include "mue_acc.h"
#include "mue_sv.h"
#include "mue_pd_full.h"

/* --------------------------------------------------------------------------
 *  MVB BA Configuration by D2000 Tool
 * --------------------------------------------------------------------------
 */
#include "mue_ba_config.h"

/* --------------------------------------------------------------------------
 *  Miscellaneous
 * --------------------------------------------------------------------------
 */
#include <string.h> /* memset, memcpy */


/* ==========================================================================
 *
 *  Procedures
 *
 * ==========================================================================
 */

void cdelay (int seconds) //sjd
{
    UNSIGNED32 cch_time_stop = (UNSIGNED32)time(NULL);

    while(((UNSIGNED32)time(NULL) - cch_time_stop) < seconds);
}
/* --------------------------------------------------------------------------
 *  Procedure : mue_app_init_device
 * --------------------------------------------------------------------------
 */
TCN_DECL_LOCAL
MUE_RESULT
mue_app_init_device
(
    void    *p_bus_ctrl
)
{
    MUE_RESULT  result;
    BITSET16    sv_device_config;
    BITSET16    sv_device_config_put __attribute__((unused));
    BITSET16    sv_device_config_get __attribute__((unused));
    WORD16      pd_port_address;
    BITSET16    pd_port_config;


    /* ----------------------------------------------------------------------
     *  Initialise MVB UART Emulation
     * ----------------------------------------------------------------------
     */
#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("- mue_acc_init()\n");
#endif /* #ifdef MUE_APP_PRINT */

    result = mue_acc_init(p_bus_ctrl);

#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("- mue_acc_init()=%d\n", (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */


    /* ----------------------------------------------------------------------
     *  Clean-up MVB UART Emulation
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_acc_clean_up()\n");
#endif /* #ifdef MUE_APP_PRINT */

        result = mue_acc_clean_up(p_bus_ctrl);

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_acc_clean_up()=%d\n", (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */


    /* ----------------------------------------------------------------------
     *  Soft reset of MVB Controller (i.e. disconnect from MVB bus)
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
        sv_device_config = (BITSET16)0x0000;

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_sv_put_device_config(0x%04X)\n", \
            (unsigned int)sv_device_config);
#endif /* #ifdef MUE_APP_PRINT */

        result = mue_sv_put_device_config(p_bus_ctrl, sv_device_config);

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_sv_put_device_config(0x%04X)=%d\n", \
            (unsigned int)sv_device_config, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */


    /* ----------------------------------------------------------------------
     *  Clear configuration of all MVB Process Data Ports
     *  (i.e. configure all ports as SINK)
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_pd_full_put_port_config(ALL)\n");
#endif /* #ifdef MUE_APP_PRINT */
        pd_port_address = 0;
        while ((MUE_RESULT_OK == result) && \
               (pd_port_address < mue_pd_full_port_number_max))
        {
            pd_port_config = (BITSET16)(pd_port_address);
            result =                        \
                mue_pd_full_put_port_config \
                (                           \
                    p_bus_ctrl,             \
                    pd_port_config          \
                );
            if (MUE_RESULT_OK != result)
            {
#ifdef MUE_APP_PRINT
                MUE_OSL_PRINTF                                            \
                    ("- ERROR: mue_pd_full_put_port_config(0x%04X)=%d\n", \
                        (unsigned int)pd_port_config, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */
            } /* if (MUE_RESULT_OK != result) */
            else
            {
                pd_port_address++;
            } /* else */
        } /* while ((MUE_RESULT_OK == result) && (pd_port_address < ...)) */
    } /* if (MUE_RESULT_OK == result) */

    return(result);

} /* mue_app_init_device */


/* --------------------------------------------------------------------------
 *  Procedure : mue_app_init_port
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_app_init_port
(
    void        *p_bus_ctrl,
    BITSET16    pd_port_config
)
{
    MUE_RESULT  result;
    WORD16      pd_port_address;
    WORD8       pd_port_data[MUE_PD_FULL_PORT_SIZE_MAX];
                /* ----------------------------------------------------------
                 *  NOTE:
                 *  "pd_port_data" is a buffer of 32 bytes, which
                 *  is the max. size of a MVB Process Data port.
                 * ----------------------------------------------------------
                 */


    /* ----------------------------------------------------------------------
     *  Configure MVB Process Data Port
     * ----------------------------------------------------------------------
     */
#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("- mue_pd_full_put_port_config(0x%04X)\n", \
        (unsigned int)pd_port_config);
#endif /* #ifdef MUE_APP_PRINT */

    result =                        \
        mue_pd_full_put_port_config \
        (                           \
            p_bus_ctrl,             \
            pd_port_config          \
        );

#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("- mue_pd_full_put_port_config(0x%04X)=%d\n", \
        (unsigned int)pd_port_config, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */


    /* ----------------------------------------------------------------------
     *  Set all bytes of port data to 0x00
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
        pd_port_address = \
            (WORD16)(pd_port_config & mue_pd_full_port_config_la_mask);
        memset((void*)pd_port_data, 0, mue_pd_full_port_size_max);

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_pd_full_put_port_data(0x%03X)\n", \
            (unsigned int)pd_port_address);
#endif /* #ifdef MUE_APP_PRINT */

        result =                            \
            mue_pd_full_put_port_data       \
            (                               \
                p_bus_ctrl,                 \
                pd_port_address,            \
                mue_pd_full_port_size_max,  \
                pd_port_data                \
            );

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_pd_full_put_port_data(0x%03X)=%d\n", \
            (unsigned int)pd_port_address, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */


    return(result);

} /* mue_app_init_port */

/*****************************************************************************
port_dir:
#define MUE_PD_FULL_PORT_CONFIG_SINK      0x0000 // sink port
#define MUE_PD_FULL_PORT_CONFIG_SRC       0x8000 // source port

port_size:
#define MUE_PD_FULL_PORT_CONFIG_FC_MASK 0x7000   // mask for port size
#define MUE_PD_FULL_PORT_CONFIG_FC4     0x4000 // port size 16 words
#define MUE_PD_FULL_PORT_CONFIG_FC3     0x3000 // port size  8 words
#define MUE_PD_FULL_PORT_CONFIG_FC2     0x2000 // port size  4 words
#define MUE_PD_FULL_PORT_CONFIG_FC1     0x1000 // port size  2 words
#define MUE_PD_FULL_PORT_CONFIG_FC0     0x0000 // port size  1 word

#define MUE_PD_FULL_PORT_CONFIG_LA_MASK 0x0FFF // mask for logical address
*****************************************************************************/
TCN_DECL_PUBLIC
MUE_RESULT
mue_init_port
(
    void        *p_bus_ctrl,
    BITSET16	port_dir,
    BITSET16	port_addr,
    BITSET16	port_size
)
{
    BITSET16	pd_port_config = port_dir | (port_addr & MUE_PD_FULL_PORT_CONFIG_LA_MASK) | port_size;
	
    return mue_app_init_port (p_bus_ctrl, pd_port_config);
}


TCN_DECL_PUBLIC
MUE_RESULT
mue_start_mvb_communication
(
    void        *p_bus_ctrl,
    BITSET16 	device_address
)
{
    device_address &= MUE_SV_DEVICE_CONFIG_DA_MASK;

    return mue_sv_put_device_config(p_bus_ctrl, device_address | MUE_SV_DEVICE_CONFIG_LINE_A | MUE_SV_DEVICE_CONFIG_LINE_B |
                                    MUE_SV_DEVICE_CONFIG_LED_DNR); //mue_sv.h
}

TCN_DECL_PUBLIC
MUE_RESULT
mue_stop_mvb_communication
(
    void        *p_bus_ctrl
)
{
    return mue_sv_put_device_config(p_bus_ctrl, 0x0000);
}

/* --------------------------------------------------------------------------
 *  Procedure : mue_app_main
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_app_main (void)
{
    MUE_RESULT  result;
    UNSIGNED8   bus_id;
    void        *p_bus_ctrl;
    BITSET16    sv_device_config __attribute__((unused));
    BITSET16    pd_port_config __attribute__((unused));
    WORD16      pd_port_address;
    BITSET8     pd_port_status;
    UNSIGNED16  pd_port_freshness;
    WORD8       pd_port_data_get[MUE_PD_FULL_PORT_SIZE_MAX];
    WORD8       pd_port_data_put[MUE_PD_FULL_PORT_SIZE_MAX];
                /* ----------------------------------------------------------
                 *  NOTE:
                 *  "pd_port_data_xxx" is a buffer of 32 bytes, which
                 *  is the max. size of a MVB Process Data port.
                 *  For any port communication always use a buffer
                 *  of this max. size!
                 * ----------------------------------------------------------
                 */


#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("******************\n");
    MUE_OSL_PRINTF("* mue_app_main() *\n");
    MUE_OSL_PRINTF("******************\n");
#endif /* #ifdef MUE_APP_PRINT */


    /* ----------------------------------------------------------------------
     *  Identification of MVB Device
     * ----------------------------------------------------------------------
     */
    bus_id = 0;
    p_bus_ctrl = (void*)&bus_id;


    /* ----------------------------------------------------------------------
     *  Initialise MVB Device
     * ----------------------------------------------------------------------
     */
#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("- mue_app_init_device()\n");
#endif /* #ifdef MUE_APP_PRINT */

    result = mue_app_init_device(p_bus_ctrl);

#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("- mue_app_init_device()=%d\n", (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    /* ----------------------------------------------------------------------
     *  Configure MVB Process Data Port:
     *  - port_address   = 0x200    -> 0x0200
     *  - port_size      = 32 bytes -> 0x4000
     *  - port_direction = SINK     -> 0x0000
     *                                 ======
     *                                 0x4200 -> pd_port_config
     * ----------------------------------------------------------------------
     *  NOTE: See also parameter constants located in file "mue_pd_full.h",
     *        e.g. "mue_pd_full_port_config_...".
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
        //pd_port_config = (BITSET16)0x4200;

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_app_init_port(0x%04X)\n", \
            (unsigned int)pd_port_config);
#endif /* #ifdef MUE_APP_PRINT */

        result = mue_init_port(p_bus_ctrl, MUE_PD_FULL_PORT_CONFIG_SINK, 0x200, MUE_PD_FULL_PORT_CONFIG_FC4);

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_app_init_port(0x%04X)=%d\n", \
            (unsigned int)pd_port_config, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */


    /* ----------------------------------------------------------------------
     *  Configure MVB Process Data Port:
     *  - port_address   = 0x300    -> 0x0300
     *  - port_size      = 32 bytes -> 0x4000
     *  - port_direction = SOURCE   -> 0x8000
     *                                 ======
     *                                 0xC300 -> pd_port_config
     * ----------------------------------------------------------------------
     *  NOTE: See also parameter constants located in file "mue_pd_full.h",
     *        e.g. "mue_pd_full_port_config_...".
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
        pd_port_config = (BITSET16)0xC300;

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_app_init_port(0x%04X)\n", \
            (unsigned int)pd_port_config);
#endif /* #ifdef MUE_APP_PRINT */

        result = mue_init_port(p_bus_ctrl, MUE_PD_FULL_PORT_CONFIG_SRC, 0x300, MUE_PD_FULL_PORT_CONFIG_FC4);

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_app_init_port(0x%04X)=%d\n", \
            (unsigned int)pd_port_config, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */


    /* ----------------------------------------------------------------------
     *  Start MVB communication:
     *  - device_address = 0x010 -> 0x0010
     *  - enable MVB line A      -> 0x8000
     *  - enable MVB line B      -> 0x4000
     *  - clear bit DNR of DSW   -> 0x1000
     *                              ======
     *                              0xD010 -> sv_device_config
     * ----------------------------------------------------------------------
     *  NOTE: See also parameter constants located in file "mue_sv.h",
     *        e.g. "mue_sv_device_config_...".
     * ----------------------------------------------------------------------
     */
     mue_start_mvb_communication (p_bus_ctrl, 0x010);
#if 0
    if (MUE_RESULT_OK == result)
    {
        sv_device_config = (BITSET16)0xD010;

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_sv_put_device_config(0x%04X)\n", \
            (unsigned int)sv_device_config);
#endif /* #ifdef MUE_APP_PRINT */

        result = mue_sv_put_device_config(p_bus_ctrl, sv_device_config);

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_sv_put_device_config(0x%04X)=%d\n", \
            (unsigned int)sv_device_config, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */

#endif
    /* ----------------------------------------------------------------------
     *  Configure MVB Bus Administrator (by D2000 Tool)
     * ----------------------------------------------------------------------
     *  NOTE: The BA configuration and procedure "mue_ba_config()"
     *        are located in file "mue_ba_config.c", which will be
     *        generated by D2000 Tool.
     *        - Add file "mue_ba_config.c" to your project or include
     *          them to this file.
     *        - Enable procedure "mue_ba_config()" by pre-processor
     *          definition "MUE_BA_CONFIG_PROCEDURE".
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_ba_config()\n");
#endif /* #ifdef MUE_APP_PRINT */

        result = mue_ba_config(p_bus_ctrl);

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_ba_config()=%d\n", (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */

while(1){
    /* ----------------------------------------------------------------------
     *  Get data from MVB Process Data Port 0x200
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
        pd_port_address = (WORD16)0x200;

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_pd_full_get_port_data(0x%03X)\n", \
            (unsigned int)pd_port_address);
#endif /* #ifdef MUE_APP_PRINT */

        result =                            \
            mue_pd_full_get_port_data       \
            (                               \
                p_bus_ctrl,                 \
                pd_port_address,            \
                (BOOLEAN1)FALSE,            \
                mue_pd_full_port_size_max,  \
                &pd_port_status,            \
                &pd_port_data_get[0],       \
                &pd_port_freshness          \
            );

        if (pd_port_freshness == 0xFFFF)
            continue;
//#ifdef MUE_APP_PRINT
#if 1
        MUE_OSL_PRINTF("- mue_pd_full_get_port_data(0x%03X)=%d\n", \
            (unsigned int)pd_port_address, (unsigned int)result);
        MUE_OSL_PRINTF("  - port_status    = 0x%02X\n", \
            (unsigned int)pd_port_status);
        MUE_OSL_PRINTF("  - port_data      = 0x%02X 0x%02X\n", \
            (unsigned int)pd_port_data_get[0],                 \
            (unsigned int)pd_port_data_get[1]);
        MUE_OSL_PRINTF("  - port_freshness = %u\n", \
            (unsigned int)pd_port_freshness);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */

    {
        int i;

        printf("received data\n");
        for(i = 0; i < mue_pd_full_port_size_max;)
        {
            printf("%4d", pd_port_data_get[i++]);
            if (i % 8 == 0)
                printf("\n");
        }
         printf("\n");
    }
    cdelay (1);//sjd
    /* ----------------------------------------------------------------------
     *  Data processing:
     *  - handle  data received from MVB (i.e. from port 0x200)
     *  - prepare data to be send to MVB (i.e. to   port 0x300)
     * ----------------------------------------------------------------------
     *  This application example:
     *  - copy byte 1; during copy increment byte
     *  - copy byte 2; during copy invert    byte
     *  - copy bytes 3-31
     * ----------------------------------------------------------------------
     */
    memcpy((void*)pd_port_data_put, (void*)pd_port_data_get, \
        mue_pd_full_port_size_max);
    pd_port_data_put[0] = (WORD8)(pd_port_data_get[0] + 1);
    pd_port_data_put[1] = (WORD8)(~pd_port_data_get[1]);

    {
        int i;

        printf("send data\n");
        for(i = 0; i < mue_pd_full_port_size_max;)
        {
            printf("%4d", pd_port_data_put[i++]);
            if (i % 8 == 0)
                printf("\n");
        }
         printf("\n");
    }

    /* ----------------------------------------------------------------------
     *  Put data to MVB Process Data Port 0x300
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == result)
    {
        pd_port_address = (WORD16)0x300;

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_pd_full_put_port_data(0x%03X)\n", \
            (unsigned int)pd_port_address);
#endif /* #ifdef MUE_APP_PRINT */

        result =                            \
            mue_pd_full_put_port_data       \
            (                               \
                p_bus_ctrl,                 \
                pd_port_address,            \
                mue_pd_full_port_size_max,  \
                &pd_port_data_put[0]        \
            );

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_pd_full_put_port_data(0x%03X)=%d\n", \
            (unsigned int)pd_port_address, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */
}

    /* ----------------------------------------------------------------------
     *  Stop MVB communication
     * ----------------------------------------------------------------------
     */
     mue_stop_mvb_communication (p_bus_ctrl);
#if 0
    if (MUE_RESULT_OK == result)
    {
        sv_device_config = (BITSET16)0x0000;

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_sv_put_device_config(0x%04X)\n", \
            (unsigned int)sv_device_config);
#endif /* #ifdef MUE_APP_PRINT */

#ifdef STOP_COMMUNICATION
        result = mue_sv_put_device_config(p_bus_ctrl, sv_device_config);
#endif

#ifdef MUE_APP_PRINT
        MUE_OSL_PRINTF("- mue_sv_put_device_config(0x%04X)=%d\n", \
            (unsigned int)sv_device_config, (unsigned int)result);
#endif /* #ifdef MUE_APP_PRINT */

    } /* if (MUE_RESULT_OK == result) */

#endif
#ifdef MUE_APP_PRINT
    MUE_OSL_PRINTF("********************\n");
    MUE_OSL_PRINTF("* mue_app_main()=%1d *\n", result);
    MUE_OSL_PRINTF("********************\n");
#endif /* #ifdef MUE_APP_PRINT */


    return(result);

} /* mue_app_main */


/* --------------------------------------------------------------------------
 *  Procedure : main
 * --------------------------------------------------------------------------
 */
//int
//main (void)
//{
//    MUE_RESULT  result;

//    result = mue_app_main();

//    return((int)result);

//} /* main
