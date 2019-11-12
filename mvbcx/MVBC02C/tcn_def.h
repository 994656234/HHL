#ifndef TCN_DEF_H
#define TCN_DEF_H

/* ==========================================================================
 *
 *  File      : TCN_DEF.H
 *
 *  Purpose   : Common Interface Definitions (constants and data types)
 *
 *  Project   : General TCN Driver Software
 *              - TCN Software Architecture (d-000487-nnnnnn)
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
 *  - TCN_LE  - required for little-endian CPU, e.g. Intel
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


/* ==========================================================================
 *
 *  Constants
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  NOTE:
 *  The obvious few that compilers may define for you.
 *  But in case they don't:
 * --------------------------------------------------------------------------
 */
#ifndef NULL
#   define NULL     (0)
#endif

#ifndef TRUE
#   define TRUE     (1==1)
#endif

#ifndef FALSE
#   define FALSE    (!TRUE)
#endif


/* ==========================================================================
 *
 *  Data Types
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Constants for basic data types (8, 16, 32 and 64 bits)
 * --------------------------------------------------------------------------
 */
#ifndef TCN_DEF_BASE_TYPE8
#   define TCN_DEF_BASE_TYPE8   char
#endif
#ifndef TCN_DEF_BASE_TYPE16
#   define TCN_DEF_BASE_TYPE16  short
#endif
#ifndef TCN_DEF_BASE_TYPE32
#   define TCN_DEF_BASE_TYPE32  long
#endif
#ifndef TCN_DEF_BASE_TYPE64
#   define TCN_DEF_BASE_TYPE64  long long
#endif

/* --------------------------------------------------------------------------
 *  Data types with less than 8-bits
 * --------------------------------------------------------------------------
 */
typedef unsigned TCN_DEF_BASE_TYPE8     BOOLEAN1;
typedef unsigned TCN_DEF_BASE_TYPE8     ANTIVALENT2;
typedef unsigned TCN_DEF_BASE_TYPE8     BCD4;
typedef unsigned TCN_DEF_BASE_TYPE8     ENUM4;

/* --------------------------------------------------------------------------
 *  8-bit data types
 * --------------------------------------------------------------------------
 */
typedef unsigned TCN_DEF_BASE_TYPE8     BITSET8;
typedef unsigned TCN_DEF_BASE_TYPE8     WORD8;
typedef unsigned TCN_DEF_BASE_TYPE8     ENUM8;
typedef unsigned TCN_DEF_BASE_TYPE8     UNSIGNED8;
typedef   signed TCN_DEF_BASE_TYPE8     INTEGER8;
typedef          TCN_DEF_BASE_TYPE8     CHARACTER8;

/* --------------------------------------------------------------------------
 *  16-bit data types
 * --------------------------------------------------------------------------
 */
typedef unsigned TCN_DEF_BASE_TYPE16    BITSET16;
typedef unsigned TCN_DEF_BASE_TYPE16    WORD16;
typedef unsigned TCN_DEF_BASE_TYPE16    ENUM16;
typedef unsigned TCN_DEF_BASE_TYPE16    UNSIGNED16;
typedef   signed TCN_DEF_BASE_TYPE16    INTEGER16;
typedef unsigned TCN_DEF_BASE_TYPE16    BIPOLAR2_16;
typedef unsigned TCN_DEF_BASE_TYPE16    UNIPOLAR2_16;
typedef unsigned TCN_DEF_BASE_TYPE16    BIPOLAR4_16;

/* --------------------------------------------------------------------------
 *  32-bit data types
 * --------------------------------------------------------------------------
 */
typedef          float                  REAL32;
typedef unsigned TCN_DEF_BASE_TYPE32    BITSET32;
typedef unsigned TCN_DEF_BASE_TYPE32    WORD32;
typedef unsigned TCN_DEF_BASE_TYPE32    ENUM32;
typedef unsigned TCN_DEF_BASE_TYPE32    UNSIGNED32;
typedef   signed TCN_DEF_BASE_TYPE32    INTEGER32;

/* --------------------------------------------------------------------------
 *  64-bit data types
 * --------------------------------------------------------------------------
 */
typedef unsigned TCN_DEF_BASE_TYPE64    BITSET64;
typedef unsigned TCN_DEF_BASE_TYPE64    WORD64;
typedef unsigned TCN_DEF_BASE_TYPE64    ENUM64;
typedef unsigned TCN_DEF_BASE_TYPE64    UNSIGNED64;
typedef   signed TCN_DEF_BASE_TYPE64    INTEGER64;

/* --------------------------------------------------------------------------
 *  Structured data types
 * --------------------------------------------------------------------------
 */
#define TCN_SIZEOF_STRUCT_BITSET256 32
typedef struct
{
    BITSET8     byte[32];
}   BITSET256;

#define TCN_SIZEOF_STRUCT_TIMEDATE48 8
typedef struct
{
    UNSIGNED32  seconds;
    UNSIGNED16  ticks;
}   TIMEDATE48;

#define TCN_SIZEOF_STRUCT_STRING32 32
typedef struct
{
    CHARACTER8  character[32];
}   STRING32;

/* --------------------------------------------------------------------------
 *  Special data type - BITFIELD16
 *  NOTE:
 *  16-bit data type used to build structured types like DS_NAME,
 *  PV_NAME, SV_MVB_DEVICE_STATUS.
 *  This will result in structured types, which size are multiplies
 *  of 16-bits.
 * --------------------------------------------------------------------------
 */
#ifndef TCN_DEF_BITFIELD16
#   define TCN_DEF_BITFIELD16   UNSIGNED16
#endif
typedef TCN_DEF_BITFIELD16      BITFIELD16;


/* ==========================================================================
 *
 *  Macros
 *
 * ==========================================================================
 */

/* --------------------------------------------------------------------------
 *  Macros for declaration of variables and procedures.
 *  NOTE:
 *  extern "C" is used in mixed C/C++ headers to force C linkage on an
 *  external definition.
 * --------------------------------------------------------------------------
 */
#define TCN_DECL_LOCAL      static

#ifdef __cplusplus
#   define TCN_DECL_PUBLIC  extern "C"
#else
#   define TCN_DECL_PUBLIC  extern
#endif

#define TCN_DECL_CONST      const

#define TCN_DECL_VOLATILE   volatile

/* --------------------------------------------------------------------------
 *  Allow creation of procedure-like macros that are a single statement,
 *  and must be followed by a semi-colon.
 * --------------------------------------------------------------------------
 */
#define TCN_MACRO_START         do {
#define TCN_MACRO_END           } while (0)

#define TCN_EMPTY_STATEMENT     TCN_MACRO_START TCN_MACRO_END

#define TCN_UNUSED_PARAMETER(_type_, _name_)    \
    TCN_MACRO_START                             \
        _type_ __tmp1 = (_name_);               \
        _type_ __tmp2 = __tmp1;                 \
        __tmp1 = __tmp2;                        \
    TCN_MACRO_END

/* --------------------------------------------------------------------------
 *  Endian conversion macros
 * --------------------------------------------------------------------------
 */
#define TCN_MACRO_SWAP16(_address_)                                         \
    TCN_MACRO_START                                                         \
        WORD16      _value = *(WORD16*)(_address_);                         \
        WORD8       *_to   = (WORD8*)(_address_);                           \
        WORD8       *_from = (WORD8*)(&_value);                             \
                                                                            \
        _to[0] = _from[1];                                                  \
        _to[1] = _from[0];                                                  \
    TCN_MACRO_END

#define TCN_MACRO_SWAP32(_address_)                                         \
    TCN_MACRO_START                                                         \
        WORD32      _value = *(WORD32*)(_address_);                         \
        WORD8       *_to   = (WORD8*)(_address_);                           \
        WORD8       *_from = (WORD8*)(&_value);                             \
                                                                            \
        _to[0] = _from[3];                                                  \
        _to[1] = _from[2];                                                  \
        _to[2] = _from[1];                                                  \
        _to[3] = _from[0];                                                  \
    TCN_MACRO_END

#define TCN_MACRO_SWAP64(_address_)                                         \
    TCN_MACRO_START                                                         \
        WORD64      _value = *(WORD64*)(_address_);                         \
        WORD8       *_to   = (WORD8*)(_address_);                           \
        WORD8       *_from = (WORD8*)(&_value);                             \
                                                                            \
        _to[0] = _from[7];                                                  \
        _to[1] = _from[6];                                                  \
        _to[2] = _from[5];                                                  \
        _to[3] = _from[4];                                                  \
        _to[4] = _from[3];                                                  \
        _to[5] = _from[2];                                                  \
        _to[6] = _from[1];                                                  \
        _to[7] = _from[0];                                                  \
    TCN_MACRO_END

#ifdef TCN_LE
#   define TCN_MACRO_CONVERT_CPU_TO_BE16(_x_)   TCN_MACRO_SWAP16((_x_))
#   define TCN_MACRO_CONVERT_CPU_TO_BE32(_x_)   TCN_MACRO_SWAP32((_x_))
#   define TCN_MACRO_CONVERT_CPU_TO_BE64(_x_)   TCN_MACRO_SWAP64((_x_))
#   define TCN_MACRO_CONVERT_BE16_TO_CPU(_x_)   TCN_MACRO_SWAP16((_x_))
#   define TCN_MACRO_CONVERT_BE32_TO_CPU(_x_)   TCN_MACRO_SWAP32((_x_))
#   define TCN_MACRO_CONVERT_BE64_TO_CPU(_x_)   TCN_MACRO_SWAP64((_x_))

#   define TCN_MACRO_CONVERT_CPU_TO_LE16(_x_)
#   define TCN_MACRO_CONVERT_CPU_TO_LE32(_x_)
#   define TCN_MACRO_CONVERT_CPU_TO_LE64(_x_)
#   define TCN_MACRO_CONVERT_LE16_TO_CPU(_x_)
#   define TCN_MACRO_CONVERT_LE32_TO_CPU(_x_)
#   define TCN_MACRO_CONVERT_LE64_TO_CPU(_x_)
#else /* #ifdef TCN_LE */
#   define TCN_MACRO_CONVERT_CPU_TO_BE16(_x_)
#   define TCN_MACRO_CONVERT_CPU_TO_BE32(_x_)
#   define TCN_MACRO_CONVERT_CPU_TO_BE64(_x_)
#   define TCN_MACRO_CONVERT_BE16_TO_CPU(_x_)
#   define TCN_MACRO_CONVERT_BE32_TO_CPU(_x_)
#   define TCN_MACRO_CONVERT_BE64_TO_CPU(_x_)

#   define TCN_MACRO_CONVERT_CPU_TO_LE16(_x_)   TCN_MACRO_SWAP16((_x_))
#   define TCN_MACRO_CONVERT_CPU_TO_LE32(_x_)   TCN_MACRO_SWAP32((_x_))
#   define TCN_MACRO_CONVERT_CPU_TO_LE64(_x_)   TCN_MACRO_SWAP64((_x_))
#   define TCN_MACRO_CONVERT_LE16_TO_CPU(_x_)   TCN_MACRO_SWAP16((_x_))
#   define TCN_MACRO_CONVERT_LE32_TO_CPU(_x_)   TCN_MACRO_SWAP32((_x_))
#   define TCN_MACRO_CONVERT_LE64_TO_CPU(_x_)   TCN_MACRO_SWAP64((_x_))
#endif /* #else */

   //============================================
    typedef enum
    {
        MUE_RESULT_OK                 = 0,      /* correct termination         */
        MUE_RESULT_ERROR              = 1,      /* unspecified error           */
        MUE_RESULT_INIT               = 2,      /* error during initialisation */
        MUE_RESULT_CLOSE              = 3,      /* error during close          */
        MUE_RESULT_CLEAN_UP           = 4,      /* error during clean-up       */
        MUE_RESULT_TRANSMIT_ACCESS    = 5,      /* transmit access  error      */
        MUE_RESULT_TRANSMIT_TIMEOUT   = 6,      /* transmit timeout error      */
        MUE_RESULT_RECEIVE_ACCESS     = 7,      /* receive  access  error      */
        MUE_RESULT_RECEIVE_TIMEOUT    = 8       /* receive  timeout error      */
    }   MUE_RESULT;
    //============================================
        
        
#endif /* #ifndef TCN_DEF_H */
