#ifndef MUE_CCH_H
#define MUE_CCH_H

/* ==========================================================================
 *
 *  File      : MUE_CCH.H
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
 *  Public Procedures
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Procedure : mue_cch_init
 *
 *  Purpose   : Initialises communication channel.
 *
 *  Syntax    : MUE_RESULT
 *              mue_cch_init
 *              (
 *                  UNSIGNED8   card_id
 *              );
 *
 *  Input     : card_id  - card identifier
 *
 *  Return    : result code; any MUE_RESULT
 * --------------------------------------------------------------------------
 */
extern
MUE_RESULT
mue_cch_init
(
    UNSIGNED8   card_id
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_cch_close
 *
 *  Purpose   : Closes communication channel.
 *
 *  Syntax    : MUE_RESULT
 *              mue_cch_close
 *              (
 *                  UNSIGNED8   card_id
 *              );
 *
 *  Input     : card_id  - card identifier
 *
 *  Return    : result code; any MUE_RESULT
 * --------------------------------------------------------------------------
 */
extern
MUE_RESULT
mue_cch_close
(
    UNSIGNED8   card_id
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_cch_clean_up
 *
 *  Purpose   : Performs a clean-up of the communication channel.
 *
 *  Syntax    : MUE_RESULT
 *              mue_cch_clean_up
 *              (
 *                  UNSIGNED8   card_id
 *              );
 *
 *  Input     : card_id  - card identifier
 *
 *  Return    : result code; any MUE_RESULT
 * --------------------------------------------------------------------------
 */
extern
MUE_RESULT
mue_cch_clean_up
(
    UNSIGNED8   card_id
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_cch_transmit
 *
 *  Purpose   : Transmits data packet to communication channel.
 *
 *  Syntax    : MUE_RESULT
 *              mue_cch_transmit
 *              (
 *                  UNSIGNED8   card_id,
 *                  UNSIGNED8   size,
 *                  WORD8       *p_packet
 *              );
 *
 *  Input     : card_id  - card identifier
 *              size     - size of data packet (number of bytes)
 *              p_packet - pointer to data packet
 *
 *  Return    : result code; any MUE_RESULT
 * --------------------------------------------------------------------------
 */
extern
MUE_RESULT
mue_cch_transmit
(
    UNSIGNED8   card_id,
    UNSIGNED8   size,
    WORD8       *p_packet
);


/* --------------------------------------------------------------------------
 *  Procedure : mue_cch_receive
 *
 *  Purpose   : Receives data packet from communication channel.
 *
 *  Syntax    : MUE_RESULT
 *              mue_cch_receive
 *              (
 *                  UNSIGNED8   card_id,
 *                  UNSIGNED8   size,
 *                  WORD8       *p_packet
 *              );
 *
 *  Input     : card_id  - card identifier
 *              size     - size of data packet (number of bytes)
 *
 *  Output    : p_packet - pointer to data packet
 *
 *  Return    : result code; any MUE_RESULT
 * --------------------------------------------------------------------------
 */
extern
MUE_RESULT
mue_cch_receive
(
    UNSIGNED8   card_id,
    UNSIGNED8   size,
    WORD8       *p_packet
);


#endif /* #ifndef MUE_CCH_H */
