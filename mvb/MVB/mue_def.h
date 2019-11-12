#ifndef MUE_DEF_H
#define MUE_DEF_H

/* ==========================================================================
 *
 *  File      : MUE_DEF.H
 *
 *  Purpose   : MVB UART Emulation - Common Definitions
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
 *  Definitions
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Enumerated Type   : MUE_RESULT
 *
 *  Purpose           : Result of a procedure.
 * --------------------------------------------------------------------------
 */
typedef enum
{
    MUE_RESULT_OK                 = 0, /* correct termination         */
    MUE_RESULT_ERROR              = 1, /* unspecified error           */
    MUE_RESULT_INIT               = 2, /* error during initialisation */
    MUE_RESULT_CLOSE              = 3, /* error during close          */
    MUE_RESULT_CLEAN_UP           = 4, /* error during clean-up       */
    MUE_RESULT_TRANSMIT_ACCESS    = 5, /* transmit access  error      */
    MUE_RESULT_TRANSMIT_TIMEOUT   = 6, /* transmit timeout error      */
    MUE_RESULT_RECEIVE_ACCESS     = 7, /* receive  access  error      */
    MUE_RESULT_RECEIVE_TIMEOUT    = 8  /* receive  timeout error      */
}   MUE_RESULT;


#endif /* #ifndef MUE_DEF_H */
