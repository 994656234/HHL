/* ==========================================================================
 *
 *  File      : MUE_SV.C
 *
 *  Purpose   : MVB UART Emulation - Supervision Interface (SV)
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


/* ==========================================================================
 *
 *  Public Constants
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Miscellaneous
 * --------------------------------------------------------------------------
 */
TCN_DECL_CONST \
    WORD16 mue_sv_device_number_max = MUE_SV_DEVICE_NUMBER_MAX;


/* --------------------------------------------------------------------------
 *  Constants : mue_sv_device_config_xxx
 *
 *  Purpose   : MVB device configuration.
 *
 *  Remarks   : - See also constants 'MUE_SV_DEVICE_CONFIG_xxx'.
 *              - Used for parameter 'device_config' of procedure
 *                'mue_sv_put_device_config'.
 *              - Used for parameter 'p_device_config' of procedure
 *                'mue_sv_get_device_config'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_CONST \
    BITSET16 mue_sv_device_config_line_mask = MUE_SV_DEVICE_CONFIG_LINE_MASK;
TCN_DECL_CONST \
    BITSET16 mue_sv_device_config_line_a    = MUE_SV_DEVICE_CONFIG_LINE_A;
TCN_DECL_CONST \
    BITSET16 mue_sv_device_config_line_b    = MUE_SV_DEVICE_CONFIG_LINE_B;
TCN_DECL_CONST \
    BITSET16 mue_sv_device_config_ba_en     = MUE_SV_DEVICE_CONFIG_BA_EN;
TCN_DECL_CONST \
    BITSET16 mue_sv_device_config_led_dnr   = MUE_SV_DEVICE_CONFIG_LED_DNR;
TCN_DECL_CONST \
    BITSET16 mue_sv_device_config_da_mask   = MUE_SV_DEVICE_CONFIG_DA_MASK;


/* --------------------------------------------------------------------------
 *  Constants : mue_sv_port_status_xxx
 *
 *  Purpose   : Status information related to a MVB device status port.
 *
 *  Remarks   : - See also constants 'MUE_SV_PORT_STATUS_xxx'.
 *              - Used for parameter 'p_port_status' of procedure
 *                'mue_sv_get_device_status'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_CONST \
    BITSET8 mue_sv_port_status_sink_mask = MUE_SV_PORT_STATUS_SINK_MASK;
TCN_DECL_CONST \
    BITSET8 mue_sv_port_status_sink_a    = MUE_SV_PORT_STATUS_SINK_A;
TCN_DECL_CONST \
    BITSET8 mue_sv_port_status_sink_b    = MUE_SV_PORT_STATUS_SINK_B;
TCN_DECL_CONST \
    BITSET8 mue_sv_port_status_ba_kdl    = MUE_SV_PORT_STATUS_BA_KDL;


/* --------------------------------------------------------------------------
 *  Constants : mue_sv_frame_statistics_clr_xxx
 *
 *  Purpose   : Control clear of counters of frame statistics.
 *
 *  Remarks   : - See also constants 'MUE_SV_FRAME_STATISTICS_CLR_xxx'.
 *              - Used for parameter 'clear_control' of procedure
 *                'mue_sv_get_frame_statistics'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_CONST \
    BITSET8 mue_sv_frame_statistics_clr_fc  = \
                MUE_SV_FRAME_STATISTICS_CLR_FC;
TCN_DECL_CONST \
    BITSET8 mue_sv_frame_statistics_clr_ec  = \
                MUE_SV_FRAME_STATISTICS_CLR_EC;
TCN_DECL_CONST \
    BITSET8 mue_sv_frame_statistics_clr_eca = \
                MUE_SV_FRAME_STATISTICS_CLR_ECA;
TCN_DECL_CONST \
    BITSET8 mue_sv_frame_statistics_clr_ecb = \
                MUE_SV_FRAME_STATISTICS_CLR_ECB;


/* ==========================================================================
 *
 *  Local Constants
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Constants : mue_sv_command_xxx
 *
 *  Purpose   : Supervision commands.
 * --------------------------------------------------------------------------
 */
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_command_put_device_config = 'C'; /* 0x43 */
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_command_get_device_config = 'S'; /* 0x53 */
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_command_put_ba_config     = 'A'; /* 0x41 */
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_command_put_ba_kdl        = 'B'; /* 0x42 */
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_command_get_device_status = 'D'; /* 0x44 */
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_command_get_frame_statistics = 'y'; /* 0x79 */

/* --------------------------------------------------------------------------
 *  Constants : mue_sv_size_xxx
 *
 *  Purpose   : Supervision command sizes.
 * --------------------------------------------------------------------------
 */
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_tx_put_device_config = 3;
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_rx_put_device_config = 0;

TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_tx_get_device_config = 1;
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_rx_get_device_config = 2;

TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_tx_put_ba_config     = 3;
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_rx_put_ba_config     = 0;

TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_tx_put_ba_kdl        = 3;
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_rx_put_ba_kdl        = 0;

TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_tx_get_device_status = 3;
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_rx_get_device_status = 5;

TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_tx_get_frame_statistics = 2;
TCN_DECL_LOCAL TCN_DECL_CONST \
    WORD8 mue_sv_size_rx_get_frame_statistics = 14;


/* ==========================================================================
 *
 *  Public Procedures
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Procedure : mue_sv_put_device_config
 *
 *  Purpose   : Puts MVB device related configuration to a MVB controller.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_sv_put_device_config
 *              (
 *                  void        *p_bus_ctrl,
 *                  BITSET16    device_config
 *              );
 *
 *  Input     : p_bus_ctrl    - pointer to bus controller specific values
 *              device_config - device configuration; any combination
 *                              of constants 'MUE_SV_DEVICE_CONFIG_xxx'
 *                              or constants 'mue_sv_device_config_xxx'
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - See MVB UART Emulation command 'C'.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 *              - If the MVB interface shall be switched off for special
 *                purposes, the following sequence must be obeyed in order
 *                not to transmit undefined data to the MVB:
 *                1. Switch off Line_A and Line_B without changing device
 *                   address.
 *                2. Second, wait approximately 250ms (= time for longest
 *                   MVB telegram) until a potential transmission from the
 *                   MVB interface to MVB has finished.
 *                3. Now the device address and source port data may be
 *                   changed (and these changes will not go to the MVB!).
 * --------------------------------------------------------------------------
 *  发送字节顺序  mue_sv_command_put_device_config(1byte)  device_config(2byte)
 * 发送完毕后，重新初始化mue_cch_data_cnt(缓存中字节数)    mue_cch_data_ptr(缓存首地址)
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_sv_put_device_config
(
    void        *p_bus_ctrl,
    BITSET16    device_config
)
{
    MUE_RESULT  mue_result;

    /* ----------------------------------------------------------------------
     *  TX
     * ----------------------------------------------------------------------
     */
    mue_result = \
        mue_acc_tx_start(p_bus_ctrl, mue_sv_size_tx_put_device_config);//初始化mue_cch_data_cnt  mue_cch_data_ptr变量
    if (MUE_RESULT_OK == mue_result)
    {//向mue_cch_data_ptr缓存中写入一个字节，并mue_cch_data_cnt++
        mue_result = \
            mue_acc_tx_value8(p_bus_ctrl, mue_sv_command_put_device_config);//++ *mue_cch_data_ptr = mue_sv_command_put_device_config;
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {//向mue_cch_data_ptr缓存中写入两个字节，并mue_cch_data_cnt+=2
        mue_result = mue_acc_tx_value16(p_bus_ctrl, device_config);//++ *mue_cch_data_ptr = device_config>>8; ++ *mue_cch_data_ptr = device_config&0xff;
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {//将mue_cch_data_ptr中mue_cch_data_cnt个数据发送出去
        mue_result = mue_acc_tx_trigger(p_bus_ctrl);
    } /* if (MUE_RESULT_OK == mue_result) */

    /* ----------------------------------------------------------------------
     *  RX
     * ----------------------------------------------------------------------
     */
    /* NOTE: nothing to receive */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = \
            mue_acc_rx_wait(p_bus_ctrl, mue_sv_size_rx_put_device_config);//接收0字节，仅初始化缓存地址与当前缓存中字节数为0,
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_rx_close(p_bus_ctrl);
    } /* if (MUE_RESULT_OK == mue_result) */

    return(mue_result);

} /* mue_sv_put_device_config */


/* --------------------------------------------------------------------------
 *  Procedure : mue_sv_get_device_config
 *
 *  Purpose   : Gets MVB device related configuration back from a MVB
 *              controller.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_sv_get_device_config
 *              (
 *                  void        *p_bus_ctrl,
 *                  BITSET16    *p_device_config
 *              );
 *
 *  Input     : p_bus_ctrl      - pointer to bus controller specific values
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Output    : p_device_config - pointer to buffer that receives the device
 *                                configuration; any combination of
 *                                constants 'MUE_SV_DEVICE_CONFIG_xxx' or
 *                                constants 'mue_sv_device_config_xxx'
 *
 *  Remarks   : - See MVB UART Emulation command 'S'.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_sv_get_device_config
(
    void        *p_bus_ctrl,
    BITSET16    *p_device_config
)
{
    MUE_RESULT  mue_result;

    /* ----------------------------------------------------------------------
     *  TX
     * ----------------------------------------------------------------------
     */
    mue_result = \
        mue_acc_tx_start(p_bus_ctrl, mue_sv_size_tx_get_device_config);
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = \
            mue_acc_tx_value8(p_bus_ctrl, mue_sv_command_get_device_config);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_tx_trigger(p_bus_ctrl);
    } /* if (MUE_RESULT_OK == mue_result) */

    /* ----------------------------------------------------------------------
     *  RX
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = \
            mue_acc_rx_wait(p_bus_ctrl, mue_sv_size_rx_get_device_config);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_rx_value16(p_bus_ctrl, p_device_config);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_rx_close(p_bus_ctrl);
    } /* if (MUE_RESULT_OK == mue_result) */

    return(mue_result);

} /* mue_sv_get_device_config */


/* --------------------------------------------------------------------------
 *  Procedure : mue_sv_put_ba_config
 *
 *  Purpose   : Puts one list entry of a MVB bus administrator configuration
 *              to a MVB controller.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_sv_put_ba_config
 *              (
 *                  void        *p_bus_ctrl,
 *                  WORD16      ba_list_entry
 *              );
 *
 *  Input     : p_bus_ctrl    - pointer to bus controller specific values
 *              ba_list_entry - one list entry of a bus administrator
 *                              configuration
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - See MVB UART Emulation command 'A'.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 *              - This is an optional procedure not supported by all MVB
 *                controllers.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_sv_put_ba_config
(
    void        *p_bus_ctrl,
    WORD16      ba_list_entry
)
{
    MUE_RESULT  mue_result;

    /* ----------------------------------------------------------------------
     *  TX
     * ----------------------------------------------------------------------
     */
    mue_result = mue_acc_tx_start(p_bus_ctrl, mue_sv_size_tx_put_ba_config);
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = \
            mue_acc_tx_value8(p_bus_ctrl, mue_sv_command_put_ba_config);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_tx_value16(p_bus_ctrl, ba_list_entry);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_tx_trigger(p_bus_ctrl);
    } /* if (MUE_RESULT_OK == mue_result) */

    /* ----------------------------------------------------------------------
     *  RX
     * ----------------------------------------------------------------------
     */
    /* NOTE: nothing to receive */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = \
            mue_acc_rx_wait(p_bus_ctrl, mue_sv_size_rx_put_ba_config);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_rx_close(p_bus_ctrl);
    } /* if (MUE_RESULT_OK == mue_result) */

    return(mue_result);

} /* mue_sv_put_ba_config */


/* --------------------------------------------------------------------------
 *  Procedure : mue_sv_get_ba_kdl_capability
 *
 *  Purpose   : Retrieves the BA-KDL capability from the MVB controller
 *              (BA = Bus Administrator, KDL = known device list).
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_sv_get_ba_kdl_capability
 *              (
 *                  void        *p_bus_ctrl,
 *                  BITSET8     *p_ba_kdl_capability
 *              );
 *
 *  Input     : p_bus_ctrl          - pointer to bus controller specific
 *                                    values
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Output    : p_ba_kdl_capability - pointer to buffer that receives
 *                                    the BA-KDL capability information
 *                                    -> == 0x00 -> BA-KDL capability = no
 *                                    -> != 0x00 -> BA-KDL capability = yes
 *
 *  Remarks   : - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_sv_get_ba_kdl_capability
(
    void        *p_bus_ctrl,
    BITSET8     *p_ba_kdl_capability
)
{
    MUE_RESULT  mue_result;
    BITSET16    mue_device_config;
    WORD16      own_device_address;
    BITSET8     dsw_port_status;
    BITSET16    dsw_device_status;
    UNSIGNED16  dsw_freshness;

    *p_ba_kdl_capability = 0;

    mue_result = mue_sv_get_device_config(p_bus_ctrl, &mue_device_config);
    if (MUE_RESULT_OK == mue_result)
    {
        own_device_address = \
            (WORD16)(mue_device_config & mue_sv_device_config_da_mask);
        mue_result =                    \
            mue_sv_get_device_status    \
            (                           \
                p_bus_ctrl,             \
                own_device_address,     \
                FALSE,                  \
                &dsw_port_status,       \
                &dsw_device_status,     \
                &dsw_freshness          \
            );
        if (MUE_RESULT_OK == mue_result)
        {
            if (mue_sv_port_status_ba_kdl == \
                (dsw_port_status & mue_sv_port_status_ba_kdl))
            {
                *p_ba_kdl_capability = 1;
            } /* if (mue_sv_port_status_ba_kdl == (...)) */
        } /* if (MUE_RESULT_OK == mue_result) */
    } /* if (MUE_RESULT_OK == mue_result) */

    return(mue_result);

} /* mue_sv_get_ba_kdl_capability */


/* --------------------------------------------------------------------------
 *  Procedure : mue_sv_put_ba_kdl
 *
 *  Purpose   : Puts one KDL entry (KDL = known device list) of a MVB bus
 *              administrator configuration to a MVB controller.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_sv_put_ba_kdl
 *              (
 *                  void        *p_bus_ctrl,
 *                  WORD16      ba_kdl_entry
 *              );
 *
 *  Input     : p_bus_ctrl    - pointer to bus controller specific values
 *              ba_kdl_entry  - one KDL entry (KDL = known device list)
 *                              of a bus administrator configuration
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - See MVB UART Emulation command 'B'.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 *              - This is an optional procedure not supported by all MVB
 *                controllers.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_sv_put_ba_kdl
(
    void        *p_bus_ctrl,
    WORD16      ba_kdl_entry
)
{
    MUE_RESULT  mue_result;

    /* ----------------------------------------------------------------------
     *  TX
     * ----------------------------------------------------------------------
     */
    mue_result = mue_acc_tx_start(p_bus_ctrl, mue_sv_size_tx_put_ba_kdl);
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = \
            mue_acc_tx_value8(p_bus_ctrl, mue_sv_command_put_ba_kdl);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_tx_value16(p_bus_ctrl, ba_kdl_entry);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_tx_trigger(p_bus_ctrl);
    } /* if (MUE_RESULT_OK == mue_result) */

    /* ----------------------------------------------------------------------
     *  RX
     * ----------------------------------------------------------------------
     */
    /* NOTE: nothing to receive */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = \
            mue_acc_rx_wait(p_bus_ctrl, mue_sv_size_rx_put_ba_kdl);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_rx_close(p_bus_ctrl);
    } /* if (MUE_RESULT_OK == mue_result) */

    return(mue_result);

} /* mue_sv_put_ba_kdl */


/* --------------------------------------------------------------------------
 *  Procedure : mue_sv_ba_config
 *
 *  Purpose   : Configures the MVB bus administrator of a MVB controller.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_sv_ba_config
 *              (
 *                  void                    *p_bus_ctrl,
 *                  TCN_DECL_CONST WORD16   *p_ba_cfg_pl,
 *                  UNSIGNED16              ba_pl_cfg_cnt,
 *                  TCN_DECL_CONST WORD16   *p_ba_cfg_kdl,
 *                  UNSIGNED16              ba_kdl_cfg_cnt
 *              );
 *
 *  Input     : p_bus_ctrl    - pointer to bus controller specific values
 *              p_ba_cfg_pl   - pointer to buffer that contains
 *                              the Periodic_List
 *              ba_pl_cfg_cnt - number of entries in Periodic_List
 *              p_ba_cfg_kdl  - pointer to buffer that contains
 *                              the Known_Devices_List (NULL = not used)
 *              ba_pl_cfg_cnt - number of entries in Known_Devices_List
 *                              (0 = not used)
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - A MVB controller is identified by 'p_bus_ctrl'.
 *              - This is an optional procedure not supported by all MVB
 *                controllers.
 *              - This procedure combines the following procedures
 *                to configure the MVB bus administrator (BA) of
 *                a MVB controller:
 *                  - mue_sv_get_device_config()
 *                  - mue_sv_put_ba_config()
 *                  - mue_sv_get_ba_kdl_capability()
 *                  - mue_sv_put_ba_kdl()
 *                  - mue_sv_put_device_config()
 *              - This procedure requires an configured and enabled
 *                MVB controller, i.e. procedure "mue_sv_put_device_config()"
 *                has been executed setting at least one MVB line.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_sv_ba_config
(
    void                    *p_bus_ctrl,
    TCN_DECL_CONST WORD16   *p_ba_cfg_pl,
    UNSIGNED16              ba_pl_cfg_cnt,
    TCN_DECL_CONST WORD16   *p_ba_cfg_kdl,
    UNSIGNED16              ba_kdl_cfg_cnt
)
{
    MUE_RESULT  mue_result;
    BITSET16    sv_device_config;
    UNSIGNED16  own_device_address __attribute__((unused));
    /* Periodic_List */
    UNSIGNED16  ba_pl_idx;
    UNSIGNED16  ba_pl_idx_max;
    WORD16      ba_pl_entry;
    /* Known_Devices_List */
    UNSIGNED8   ba_kdl_do_config __attribute__((unused));
    BITSET8     ba_kdl_capability __attribute__((unused));
    UNSIGNED16  ba_kdl_idx __attribute__((unused));
    UNSIGNED16  ba_kdl_idx_max __attribute__((unused));
    WORD16      ba_kdl_entry __attribute__((unused));

    /* ----------------------------------------------------------------------
     *  Get own Device_Address; check if device is active
     * ----------------------------------------------------------------------
     */
    sv_device_config = 0x0000;
    own_device_address = 0;
    mue_result = mue_sv_get_device_config(p_bus_ctrl, &sv_device_config);
    if (MUE_RESULT_OK == mue_result)
    {
        own_device_address = (UNSIGNED16) \
            (sv_device_config & mue_sv_device_config_da_mask);
        if (0 == (sv_device_config & mue_sv_device_config_line_mask))
        {
            mue_result = MUE_RESULT_INIT;
        } /* if (0 == (...)) */
        else if (0 != (sv_device_config & mue_sv_device_config_ba_en))
        {
            mue_result = MUE_RESULT_INIT;
        } /* else if (0 != (...)) */
    } /* if (MUE_RESULT_OK == mue_result) */

    /* ----------------------------------------------------------------------
     *  Periodic_List
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == mue_result)
    {
        ba_pl_idx_max = ba_pl_cfg_cnt;
        for (ba_pl_idx=0; ba_pl_idx<ba_pl_idx_max; ba_pl_idx++)
        {
            ba_pl_entry = p_ba_cfg_pl[ba_pl_idx];
            mue_result = mue_sv_put_ba_config(p_bus_ctrl, ba_pl_entry);
            if (MUE_RESULT_OK != mue_result)
            {
                break;
            } /* if (MUE_RESULT_OK != mue_result) */
        } /* for (ba_pl_idx=0; ba_pl_idx<ba_pl_idx_max; ba_pl_idx++) */
    } /* if (MUE_RESULT_OK == mue_result) */

    /* ----------------------------------------------------------------------
     *  Known_Devices_List
     * ----------------------------------------------------------------------
     */
    
    /* ----------------------------------------------------------------------
     *  Enable BA
     * ----------------------------------------------------------------------
     */
    sv_device_config |= mue_sv_device_config_ba_en;
    mue_result = mue_sv_put_device_config(p_bus_ctrl, sv_device_config);

    return(mue_result);

} /* mue_sv_ba_config */


/* --------------------------------------------------------------------------
 *  Procedure : mue_sv_get_device_status
 *
 *  Purpose   : Gets the device status related to a MVB device from the
 *              traffic store of a MVB controller.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_sv_get_device_status
 *              (
 *                  void        *p_bus_ctrl,
 *                  WORD16      device_address,
 *                  BOOLEAN1    check_received,
 *                  BITSET8     *p_port_status,
 *                  BITSET16    *p_device_status,
 *                  UNSIGNED16  *p_freshness
 *              );
 *
 *  Input     : p_bus_ctrl      - pointer to bus controller specific values
 *              device_address  - device identifier (12-bit device address)
 *              check_received  - check if new data was received from MVB
 *                                since last get (TRUE or FALSE)
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Output    : p_port_status   - pointer to buffer that receives the
 *                                status information related to a MVB
 *                                device status port;
 *                                any combination of constants
 *                                'MUE_SV_PORT_STATUS_xxx' or constants
 *                                'mue_sv_port_status_xxx'
 *              p_device_status - pointer to buffer that receives the data
 *                                related to a MVB device status port;
 *                                any combination of bit constants
 *                                'MUE_SV_DEVICE_STATUS_BIT_xxx'
 *              p_freshness     - pointer to buffer that receives the
 *                                freshness timer related to a MVB device
 *                                status port (or NULL)
 *
 *  Remarks   : - See MVB UART Emulation command 'D'.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 *              - If parameter 'check_received' is FALSE, then the
 *                parameters 'p_device_status' (and 'p_freshness') will
 *                return always a value. Otherwise it depends on the value
 *                of parameter 'p_port_status' (bits SINK_A, SINK_B).
 *              - This is an optional procedure supported only by MVB
 *                controllers with MVB UART Emulation 'MDFULL'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_sv_get_device_status
(
    void        *p_bus_ctrl,
    WORD16      device_address,
    BOOLEAN1    check_received,
    BITSET8     *p_port_status,
    BITSET16    *p_device_status,
    UNSIGNED16  *p_freshness
)
{
    MUE_RESULT  mue_result;

    /* ----------------------------------------------------------------------
     *  TX
     * ----------------------------------------------------------------------
     */
    mue_result = \
        mue_acc_tx_start(p_bus_ctrl, mue_sv_size_tx_get_device_status);
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = \
            mue_acc_tx_value8(p_bus_ctrl, mue_sv_command_get_device_status);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_tx_value16(p_bus_ctrl, device_address);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_tx_trigger(p_bus_ctrl);
    } /* if (MUE_RESULT_OK == mue_result) */

    /* ----------------------------------------------------------------------
     *  RX
     * ----------------------------------------------------------------------
     */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = \
            mue_acc_rx_wait(p_bus_ctrl, mue_sv_size_rx_get_device_status);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_rx_value8(p_bus_ctrl, p_port_status);
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        if ((TRUE == check_received) && \
            (0x00 == (*p_port_status & mue_sv_port_status_sink_mask)))
        {
            mue_result = mue_acc_rx_ignore(p_bus_ctrl, 4);
        } /* ((TRUE == check_received) && (...)) */
        else
        {
            mue_result = mue_acc_rx_value16(p_bus_ctrl, p_device_status);
            if (MUE_RESULT_OK == mue_result)
            {
                if (NULL != p_freshness)
                {
                    mue_result = mue_acc_rx_value16(p_bus_ctrl, p_freshness);
                } /* if (NULL != p_freshness) */
                else
                {
                    mue_result = mue_acc_rx_ignore(p_bus_ctrl, 2);
                } /* else */
            } /* if (MUE_RESULT_OK == mue_result) */
        } /* else */
    } /* if (MUE_RESULT_OK == mue_result) */
    if (MUE_RESULT_OK == mue_result)
    {
        mue_result = mue_acc_rx_close(p_bus_ctrl);
    } /* if (MUE_RESULT_OK == mue_result) */

    return(mue_result);

} /* mue_sv_get_device_status */
