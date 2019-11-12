#ifndef MUE_ACC_H
#define MUE_ACC_H

/* ==========================================================================
 *
 *  File      : MUE_ACC.H
 *
 *  Purpose   : MVB UART Emulation - Access Interface
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
 *  Procedures - General
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_init
 *
 *  Purpose   : Initialises the access to the UART (check for availability).
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_init
 *              (
 *                  void        *p_bus_ctrl
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_init
(
    void        *p_bus_ctrl
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_close
 *
 *  Purpose   : Closes the access to the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_close
 *              (
 *                  void        *p_bus_ctrl
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_close
(
    void        *p_bus_ctrl
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_clean_up
 *
 *  Purpose   : Perform a clean-up of the UART communication
 *              (synchronise access protocol of the MVB UART Emulation).
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_clean_up
 *              (
 *                  void        *p_bus_ctrl
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - If a process using the MVB UART Emulation was interrupted
 *                the access protocol of the MVB UART Emulation remains in
 *                one of the following three states (Sx):
 *                S1: The MVB UART Emulation is ready to receive a new
 *                    command character -> nothing must be done
 *                    * any transmitted data bytes with value 0x00 (see
 *                      state S2) will be ignored
 *                S2: A MVB UART Emulation command is still in progress and
 *                    requests more data bytes (in minimum the command
 *                    character was sent) -> synchronisation is necessary
 *                    * transmits 34 data bytes with value 0x00 (command 'P'
 *                      requests the max. number of data bytes; PD_16=33,
 *                      PD_16F=33, PD_FULL=34, i.e. 34 data bytes); after
 *                      this the MVB UART Emulation may enter the state S3
 *                S3: A MVB UART Emulation command is still in progress and
 *                    transmits more data bytes -> synchronisation is
 *                    necessary (Parallel Host Interface only)
 *                    * transmit any command character which flushes the
 *                      transmit queue of the MVB UART Emulation
 *                    or (alternative)
 *                    * receive until nothing left (command 'G' transmits
 *                      the max. number of data bytes; PD_16=33, PD_16F=35,
 *                      PD_FULL=35, i.e. 35 data bytes)
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_clean_up
(
    void        *p_bus_ctrl
);


/* ==========================================================================
 *
 *  Procedures - Transmit (TX)
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_tx_start
 *
 *  Purpose   : Starts a transmission over the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_tx_start
 *              (
 *                  void        *p_bus_ctrl,
 *                  UNSIGNED16  size
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *              size       - number of bytes to transmit over the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_tx_start
(
    void        *p_bus_ctrl,
    UNSIGNED16  size
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_tx_value8
 *
 *  Purpose   : Transmits a 8-bit value over the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_tx_value8
 *              (
 *                  void        *p_bus_ctrl,
 *                  WORD8       value8
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *              value8     - 8-bit value to transmit over the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - Used for general parameters.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_tx_value8
(
    void        *p_bus_ctrl,
    WORD8       value8
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_tx_value16
 *
 *  Purpose   : Transmits a 16-bit value over the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_tx_value16
 *              (
 *                  void        *p_bus_ctrl,
 *                  WORD16      value16
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *              value16    - 16-bit value to transmit over the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - Used for general parameters.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_tx_value16
(
    void        *p_bus_ctrl,
    WORD16      value16
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_tx_array
 *
 *  Purpose   : Transmits data of a buffer over the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_tx_array
 *              (
 *                  void        *p_bus_ctrl,
 *                  UNSIGNED16  size,
 *                  void        *p_buffer
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *              size       - size of the buffer (number of bytes to
 *                           transmit over the UART)
 *              p_buffer   - pointer to buffer that contains data
 *                           to transmit over the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - Used for data related to a MVB process data port
 *                (size = 2, 4, 8, 16 or 32 bytes).
 *              - Used for data related to a MVB message data frame
 *                (size = 32 bytes).
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_tx_array
(
    void        *p_bus_ctrl,
    UNSIGNED16  size,
    void        *p_buffer
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_tx_fill
 *
 *  Purpose   : Transmits fill bytes over the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_tx_fill
 *              (
 *                  void        *p_bus_ctrl,
 *                  UNSIGNED16  size
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *              size       - number of fill bytes to transmit over the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - Used for fill bytes related to a MVB process data port
 *                (size = 0, 16, 24, 28 or 30 bytes).
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_tx_fill
(
    void        *p_bus_ctrl,
    UNSIGNED16  size
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_tx_trigger
 *
 *  Purpose   : Triggers a transmission over the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_tx_trigger
 *              (
 *                  void        *p_bus_ctrl
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_tx_trigger
(
    void        *p_bus_ctrl
);


/* ==========================================================================
 *
 *  Procedures - Receive (RX)
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_rx_wait
 *
 *  Purpose   : Waits, until something to receive from the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_rx_wait
 *              (
 *                  void        *p_bus_ctrl,
 *                  UNSIGNED16  size
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *              size       - number of bytes to receive from the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_rx_wait
(
    void        *p_bus_ctrl,
    UNSIGNED16  size
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_rx_value8
 *
 *  Purpose   : Receives a 8-bit value from the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_rx_value8
 *              (
 *                  void        *p_bus_ctrl,
 *                  WORD8       *p_value8
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *
 *  Output    : p_value8   - pointer to buffer that receives a 8-bit value
 *                           from the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - Used for general parameters.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_rx_value8
(
    void        *p_bus_ctrl,
    WORD8       *p_value8
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_rx_value16
 *
 *  Purpose   : Receives a 16-bit value from the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_rx_value16
 *              (
 *                  void        *p_bus_ctrl,
 *                  WORD16      *p_value16
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *
 *  Output    : p_value16  - pointer to buffer that receives a 16-bit value
 *                             from the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - Used for general parameters.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_rx_value16
(
    void        *p_bus_ctrl,
    WORD16      *p_value16
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_rx_array
 *
 *  Purpose   : Receives data into a buffer from the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_rx_array
 *              (
 *                  void        *p_bus_ctrl,
 *                  UNSIGNED16  size,
 *                  void        *p_buffer
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *              size       - size of the buffer (number of bytes to receive
 *                           from the UART)
 *
 *  Output    : p_buffer   - pointer to buffer that receives data from
 *                           the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - Used for data related to a MVB process data port
 *                (size = 2, 4, 8, 16 or 32 bytes).
 *              - Used for data related to a MVB message data frame
 *                (size = 32 bytes).
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_rx_array
(
    void        *p_bus_ctrl,
    UNSIGNED16  size,
    void        *p_buffer
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_rx_fill
 *
 *  Purpose   : Receives fill bytes from the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_rx_fill
 *              (
 *                  void        *p_bus_ctrl,
 *                  UNSIGNED16  size
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *              size       - number of fill bytes to receive from the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - Used for fill bytes related to a MVB process data port
 *                (size = 0, 16, 24, 28 or 30 bytes).
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_rx_fill
(
    void        *p_bus_ctrl,
    UNSIGNED16  size
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_rx_ignore
 *
 *  Purpose   : Ignore surplus data (fill bytes) from the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_rx_ignore
 *              (
 *                  void        *p_bus_ctrl,
 *                  UNSIGNED16  size
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *              size       - number of fill bytes to ignore from the UART
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - Used for surplus bytes related to a MVB device status or
 *                a MVB process data port.
 *              - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_rx_ignore
(
    void        *p_bus_ctrl,
    UNSIGNED16  size
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_acc_rx_close
 *
 *  Purpose   : Closes a receive block from the UART.
 *
 *  Syntax    : TCN_DECL_PUBLIC
 *              MUE_RESULT
 *              mue_acc_rx_close
 *              (
 *                  void        *p_bus_ctrl
 *              );
 *
 *  Input     : p_bus_ctrl - pointer to bus controller specific values
 *
 *  Return    : result code; any MUE_RESULT
 *
 *  Remarks   : - A MVB controller is identified by 'p_bus_ctrl'.
 * --------------------------------------------------------------------------
 */
TCN_DECL_PUBLIC
MUE_RESULT
mue_acc_rx_close
(
    void        *p_bus_ctrl
);


#endif /* #ifndef MUE_ACC_H */
