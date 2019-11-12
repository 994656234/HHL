#ifndef MUE_PD_FULL_H
#define MUE_PD_FULL_H

/* ==========================================================================
 *
 *  File      : MUE_PD_FULL.H
 *
 *  Purpose   : MVB UART Emulation - Process Data Interface (PD_FULL)
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


/* ==========================================================================
 *
 *  Constants
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Miscellaneous
 * --------------------------------------------------------------------------
 */
#define MUE_PD_FULL_PORT_NUMBER_MAX         4096
TCN_DECL_PUBLIC TCN_DECL_CONST WORD16       mue_pd_full_port_number_max;

#define MUE_PD_FULL_PORT_SIZE_MAX           32
TCN_DECL_PUBLIC TCN_DECL_CONST UNSIGNED8    mue_pd_full_port_size_max;


/* --------------------------------------------------------------------------
 *  Constants : MUE_PD_FULL_PORT_CONFIG_xxx, mue_pd_full_port_config_xxx
 *
 *  Purpose   : MVB process data port configuration.
 *
 *  Remarks   : - Used for parameter 'port_config' of procedure
 *                'mue_pd_full_put_port_config'.
 *              - Used for parameter 'p_port_config' of procedure
 *                'mue_pd_full_get_port_config'.
 * --------------------------------------------------------------------------
 */
#define MUE_PD_FULL_PORT_CONFIG_SINK    0x0000 /* sink port              */
#define MUE_PD_FULL_PORT_CONFIG_SRC     0x8000 /* source port              */
#define MUE_PD_FULL_PORT_CONFIG_FC_MASK 0x7000 /* mask for port size       */
#define MUE_PD_FULL_PORT_CONFIG_FC4     0x4000 /* port size 16 words       */
#define MUE_PD_FULL_PORT_CONFIG_FC3     0x3000 /* port size  8 words       */
#define MUE_PD_FULL_PORT_CONFIG_FC2     0x2000 /* port size  4 words       */
#define MUE_PD_FULL_PORT_CONFIG_FC1     0x1000 /* port size  2 words       */
#define MUE_PD_FULL_PORT_CONFIG_FC0     0x0000 /* port size  1 word        */
#define MUE_PD_FULL_PORT_CONFIG_LA_MASK 0x0FFF /* mask for logical address */

TCN_DECL_PUBLIC TCN_DECL_CONST BITSET16 mue_pd_full_port_config_src;
TCN_DECL_PUBLIC TCN_DECL_CONST BITSET16 mue_pd_full_port_config_fc_mask;
TCN_DECL_PUBLIC TCN_DECL_CONST BITSET16 mue_pd_full_port_config_fc4;
TCN_DECL_PUBLIC TCN_DECL_CONST BITSET16 mue_pd_full_port_config_fc3;
TCN_DECL_PUBLIC TCN_DECL_CONST BITSET16 mue_pd_full_port_config_fc2;
TCN_DECL_PUBLIC TCN_DECL_CONST BITSET16 mue_pd_full_port_config_fc1;
TCN_DECL_PUBLIC TCN_DECL_CONST BITSET16 mue_pd_full_port_config_fc0;
TCN_DECL_PUBLIC TCN_DECL_CONST BITSET16 mue_pd_full_port_config_la_mask;


/* --------------------------------------------------------------------------
 *  Constants : MUE_PD_FULL_PORT_STATUS_xxx, mue_pd_full_port_status_xxx
 *
 *  Purpose   : Status information related to a MVB process data port.
 *
 *  Remarks   : - Used for parameter 'port_status' of procedure
 *                'mue_pd_full_get_port_data'.
 * --------------------------------------------------------------------------
 */
#define MUE_PD_FULL_PORT_STATUS_SINK_MASK 0xC0 /* mask for sink bits     */
#define MUE_PD_FULL_PORT_STATUS_SINK_A    0x80 /* received on MVB line A */
#define MUE_PD_FULL_PORT_STATUS_SINK_B    0x40 /* received on MVB line B */

TCN_DECL_PUBLIC TCN_DECL_CONST BITSET8  mue_pd_full_port_status_sink_mask;
TCN_DECL_PUBLIC TCN_DECL_CONST BITSET8  mue_pd_full_port_status_sink_a;
TCN_DECL_PUBLIC TCN_DECL_CONST BITSET8  mue_pd_full_port_status_sink_b;


/* ==========================================================================
 *
 *  Procedures
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Procedure : mue_pd_full_put_port_config
 *
 *  Purpose   : Puts configuration related to a MVB process data port to the
 *              traffic store of a MVB controller (PD_FULL).
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_pd_full_put_port_config
 *              (
 *                  void        *p_bus_ctrl,
 *                  BITSET16    port_config
 *              );
 *
 *  Input     : p_bus_ctrl  - pointer to bus controller specific values
 *              port_config - port configuration; any combination of
 *                            constants 'MUE_PD_FULL_PORT_CONFIG_xxx' or
 *                            constants 'mue_pd_full_port_config_xxx'
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - See MVB UART Emulation command 'H'.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 *              - A MVB process data port is identified by its logical
 *                address, which is part of parameter 'port_config'
 *                (see also constant 'MUE_PD_FULL_PORT_CONFIG_LA_MASK').
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_pd_full_put_port_config
(
    void        *p_bus_ctrl,
    BITSET16    port_config
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_pd_full_get_port_config
 *
 *  Purpose   : Gets configuration related to a MVB process data port
 *              back from the traffic store of a MVB controller (PD_FULL).
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_pd_full_get_port_config
 *              (
 *                  void        *p_bus_ctrl,
 *                  WORD16      port_address,
 *                  BITSET16    *p_port_config
 *              );
 *
 *  Input     : p_bus_ctrl    - pointer to bus controller specific values
 *              port_address  - port identifier (12-bit logical address)
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Output    : p_port_config - pointer to buffer that receives the port
 *                              configuration; any combination of
 *                              constants 'MUE_PD_FULL_PORT_CONFIG_xxx' or
 *                              constants 'mue_pd_full_port_config_xxx'
 *
 *  Remarks   : - See MVB UART Emulation command 'I'.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 *              - A MVB process data port is identified by its logical
 *                address (see parameter 'port_address').
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_pd_full_get_port_config
(
    void        *p_bus_ctrl,
    WORD16      port_address,
    BITSET16    *p_port_config
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_pd_full_put_port_data
 *
 *  Purpose   : Puts data related to a MVB process data port to the traffic
 *              store of a MVB controller (PD_FULL).
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_pd_full_put_port_data
 *              (
 *                  void        *p_bus_ctrl,
 *                  WORD16      port_address,
 *                  UNSIGNED8   port_size,
 *                  void        *p_port_data
 *              );
 *
 *  Input     : p_bus_ctrl   - pointer to bus controller specific values
 *              port_address - port identifier (12-bit logical address)
 *              port_size    - size of the port (2, 4, 8, 16 or 32 bytes)
 *              p_port_data  - pointer to buffer that contains the data
 *                             related to a MVB process data port;
 *                             up to 32 bytes, which is the largest size
 *                             of a port
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - See MVB UART Emulation command 'P'.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 *              - A MVB process data port is identified by its logical
 *                address (see parameter 'port_address').
 *              - The size of a MVB process data port may have 2, 4, 8, 16
 *                or 32 bytes (see parameter 'p_port_data').
 *              - The MVB UART Emulation handles the data of a MVB process
 *                data port (parameter 'p_port_data') as an array of WORD16.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_pd_full_put_port_data
(
    void        *p_bus_ctrl,
    WORD16      port_address,
    UNSIGNED8   port_size,
    void        *p_port_data
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_pd_full_get_port_data
 *
 *  Purpose   : Gets data related to a MVB process data port from the
 *              traffic store of a MVB controller (PD_FULL).
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_pd_full_get_port_data
 *              (
 *                  void        *p_bus_ctrl,
 *                  WORD16      port_address,
 *                  BOOLEAN1    check_received,
 *                  UNSIGNED8   port_size,
 *                  BITSET8     *p_port_status,
 *                  void        *p_port_data,
 *                  UNSIGNED16  *p_port_freshness
 *              );
 *
 *  Input     : p_bus_ctrl       - pointer to bus controller specific values
 *              port_address     - port identifier (12-bit logical address)
 *              check_received   - check if new data was received from MVB
 *                                 since last get (TRUE or FALSE)
 *              port_size        - size of the port (2, 4, 8, 16 or 32 bytes)
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Output    : p_port_status    - pointer to buffer that receives the
 *                                 status information releated to a MVB
 *                                 process data port;
 *                                 any combination of
 *                                 constants 'MUE_PD_FULL_PORT_STATUS_xxx' or
 *                                 constants 'mue_pd_full_port_status_xxx'
 *              p_port_data      - pointer to buffer that receives the data
 *                                 related to a MVB process data port;
 *                                 up to 32 bytes, which is the largest size
 *                                 of a port
 *              p_port_freshness - pointer to buffer that receives the
 *                                 freshness timer related to a MVB process
 *                                 data port (or NULL)
 *
 *  Remarks   : - See MVB UART Emulation command 'G'.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 *              - A MVB process data port is identified by its logical
 *                address (see parameter 'port_address').
 *              - If parameter 'check_received' is FALSE, then the
 *                parameters 'p_port_data' and 'p_port_freshness'
 *                will return always a value.
 *                Otherwise it depends on the value of parameter
 *                'p_port_status' (bits SINK_A, SINK_B).
 *              - The size of a MVB process data port may have 2, 4, 8, 16
 *                or 32 bytes (see parameter 'p_port_data').
 *              - The MVB UART Emulation handles the data of a MVB process
 *                data port (parameter 'p_port_data') as an array of WORD16.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_pd_full_get_port_data
(
    void        *p_bus_ctrl,
    WORD16      port_address,
    BOOLEAN1    check_received,
    UNSIGNED8   port_size,
    BITSET8     *p_port_status,
    void        *p_port_data,
    UNSIGNED16  *p_port_freshness
);


#endif /* #ifndef MUE_PD_FULL_H */

