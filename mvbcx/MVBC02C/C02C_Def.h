#ifndef     __C02C_DEF_H__
    #define     __C02C_DEF_H__

    typedef enum _E_TM_MODE
    {
        E_TM_MODE0   = 0,
        E_TM_MODE1   = 1,
        E_TM_MODE2   = 2,
        E_TM_MODE3   = 3,
        E_TM_MODE4   = 4
    } E_TM_MODE;

    /* Service Area */
    typedef enum _E_WORK_MODE
    {
        E_SOFTWARE_REST  = 0x0000,
        E_CONFIGURATION  = 0x0001,
        E_SELF_TEST      = 0x0002,
        E_FULL_OPERATION = 0x0003
        
    } E_WORK_MODE;


    #define  TM_MODE0_PORT_NUM_MAX     (64)
    #define  TM_MODE1_PORT_NUM_MAX     (64)
    #define  TM_MODE2_PORT_NUM_MAX     (256)
    #define  TM_MODE3_PORT_NUM_MAX     (1024)
    #define  TM_MODE4_PORT_NUM_MAX     (1024)

    #define  TM_MODE_DEFAULT           (E_TM_MODE2)
    #define  PORT_NUMBER_MAX           (TM_MODE2_PORT_NUM_MAX)


    /*************************** Traffic Memory Map ****************************/
    /* Memory Configuration Mode 0 */
    #define  TM_MODE0_LA_PIT_ADDR            (0x00000)          /* LA Port Index Table */
    #define  TM_MODE0_LA_DA_ADDR             (0x01000)          /* LA Data Area */
    #define  TM_MODE0_LA_FT_ADDR             (0x02000)          /* LA Force Table */
    #define  TM_MODE0_LA_PCS_ADDR            (0x03000)          /* LA PCS */
    #define  TM_MODE0_SERVICE_AREA_ADDR      (0x03C00)          /* Service Area */ 
    #define  TM_MODE0_SA_INTREG_ADDR         (0x03F00)          /* Internal Registers Offset. */        

    /* Memory Configuration Mode 1 */
    #define  TM_MODE1_LA_PIT_ADDR            (0x00000)          /* LA Port Index Table */
    #define  TM_MODE1_LA_DA_ADDR             (0x01000)          /* LA Data Area */
    #define  TM_MODE1_LA_FT_ADDR             (0x02000)          /* LA Force Table */
    #define  TM_MODE1_LA_PCS_ADDR            (0x03000)          /* LA PCS */
    #define  TM_MODE1_DA_PIT_ADDR            (0x04000)          /* DA Port Index Table */
    #define  TM_MODE1_DA_DA_ADDR             (0x05000)          /* DA Data Area */
    #define  TM_MODE1_DA_PCS_ADDR            (0x07000)          /* DA PCS */
    #define  TM_MODE1_SERVICE_AREA_ADDR      (0x07C00)          /* Service Area */ 
    #define  TM_MODE1_SA_INTREG_ADDR         (0x07F00)          /* Internal Registers Offset. */

    /* Memory Configuration Mode 2 */
    #define  TM_MODE2_LA_PIT_ADDR            (0x00000)          /* LA Port Index Table */
    #define  TM_MODE2_LA_DA_ADDR             (0x04000)          /* LA Data Area */
    #define  TM_MODE2_LA_FT_ADDR             (0x08000)          /* LA Force Table */
    #define  TM_MODE2_LA_PCS_ADDR            (0x0C000)          /* LA PCS */
    #define  TM_MODE2_DA_PIT_ADDR            (0x02000)          /* DA Port Index Table */
    #define  TM_MODE2_DA_DA_ADDR             (0x0E000)          /* DA Data Area */
    #define  TM_MODE2_DA_PCS_ADDR            (0x0F000)          /* DA PCS */
    #define  TM_MODE2_SERVICE_AREA_ADDR      (0x0FC00)          /* Service Area */ 
    #define  TM_MODE2_SA_INTREG_ADDR         (0x0FF00)          /* Internal Registers Offset. */

    /* Memory Configuration Mode 3 */
    #define  TM_MODE3_LA_PIT_ADDR            (0x00000)          /* LA Port Index Table */
    #define  TM_MODE3_LA_DA_ADDR             (0x10000)          /* LA Data Area */
    #define  TM_MODE3_LA_FT_ADDR             (0x20000)          /* LA Force Table */
    #define  TM_MODE3_LA_PCS_ADDR            (0x30000)          /* LA PCS */
    #define  TM_MODE3_DA_PIT_ADDR            (0x02000)          /* DA Port Index Table */
    #define  TM_MODE3_DA_DA_ADDR             (0x38000)          /* DA Data Area */
    #define  TM_MODE3_DA_PCS_ADDR            (0x04000)          /* DA PCS */
    #define  TM_MODE3_SERVICE_AREA_ADDR      (0x0FC00)          /* Service Area */ 
    #define  TM_MODE3_SA_INTREG_ADDR         (0x0FF00)          /* Internal Registers Offset. */

    /* Memory Configuration Mode 4 */
    #define  TM_MODE4_LA_PIT_ADDR            (0x00000)          /* LA Port Index Table */
    #define  TM_MODE4_LA_DA_ADDR             (0x10000)          /* LA Data Area */
    #define  TM_MODE4_LA_FT_ADDR             (0x20000)          /* LA Force Table */
    #define  TM_MODE4_LA_PCS_ADDR            (0x30000)          /* LA PCS */
    #define  TM_MODE4_DA_PIT_ADDR            (0x02000)          /* DA Port Index Table */
    #define  TM_MODE4_DA_DA_ADDR             (0x40000)          /* DA Data Area */
    #define  TM_MODE4_DA_PCS_ADDR            (0x38000)          /* DA PCS */
    #define  TM_MODE4_SERVICE_AREA_ADDR      (0x0FC00)          /* Service Area */ 
    #define  TM_MODE4_SA_INTREG_ADDR         (0x0FF00)          /* Internal Registers Offset. */

    /* Regist Access Define */
    #define PCS0_ADDR(base, pi)  ((pi<<3)+base)
    #define PCS1_ADDR(base, pi)  ((pi<<3)+base+2)
    #define PCS2_ADDR(base, pi)  ((pi<<3)+base+4)
    #define PCS3_ADDR(base, pi)  ((pi<<3)+base+6)

    #define  PCS0_PORT_SINK         (0x0400)
    #define  PCS0_PORT_SOURCE       (0x0800)
    #define  PCS0_PORT_SIZE2        (0x0000)
    #define  PCS0_PORT_SIZE4        (0x1000)
    #define  PCS0_PORT_SIZE8        (0x2000)
    #define  PCS0_PORT_SIZE16       (0x3000)
    #define  PCS0_PORT_SIZE32       (0x4000)

    #define LA_DA_ADDR(base, pi) ((((pi<<4) & 0xFFC0) | ((pi << 3) & 0x18)) + base)

    /* Service Area. Internal Registers Define */
    #define TM_SA_REG_OFFSET_SCR       (0x80)
    #define TM_SA_REG_OFFSET_MCR       (0x84)
    #define TM_SA_REG_OFFSET_DR        (0x88)
    #define TM_SA_REG_OFFSET_STSR      (0x8C)
    #define TM_SA_REG_OFFSET_FC        (0x90)
    #define TM_SA_REG_OFFSET_EC        (0x94)
    #define TM_SA_REG_OFFSET_MFR       (0x98)
    #define TM_SA_REG_OFFSET_MFRE      (0x9C)
    #define TM_SA_REG_OFFSET_MR        (0xA0)
    #define TM_SA_REG_OFFSET_MR2       (0xA4)
    #define TM_SA_REG_OFFSET_DPR       (0xA8)
    #define TM_SA_REG_OFFSET_DPR2      (0xAC)
    #define TM_SA_REG_OFFSET_IPR0      (0xB0)
    #define TM_SA_REG_OFFSET_IPR1      (0xB4)
    #define TM_SA_REG_OFFSET_IMR0      (0xB8)
    #define TM_SA_REG_OFFSET_IMR1      (0xBC)
    #define TM_SA_REG_OFFSET_ISR0      (0xC0)
    #define TM_SA_REG_OFFSET_ISR1      (0xC4)
    #define TM_SA_REG_OFFSET_IVR0      (0xC8)
    #define TM_SA_REG_OFFSET_IVR1      (0xCC)
    #define TM_SA_REG_OFFSET_ECA       (0xD0)
    #define TM_SA_REG_OFFSET_ECB       (0xD4)
    #define TM_SA_REG_OFFSET_DAOR      (0xD8)
    #define TM_SA_REG_OFFSET_DAOK      (0xDC)
    #define TM_SA_REG_OFFSET_TCR       (0xE0)
    #define TM_SA_REG_OFFSET_SFR       (0xE4)
    #define TM_SA_REG_OFFSET_TR1       (0xF0)
    #define TM_SA_REG_OFFSET_TR2       (0xF4)
    #define TM_SA_REG_OFFSET_TC1       (0xF8)
    #define TM_SA_REG_OFFSET_TC2       (0xFC)

    typedef struct _T_TM_ADDR_LIST{
        unsigned int  tm_mod;
        unsigned int  la_pit_addr;
        unsigned int  la_da_addr;
        unsigned int  la_ft_addr;
        unsigned int  la_pcs_addr;
        unsigned int  da_pit_addr;
        unsigned int  da_da_addr;
        unsigned int  da_pcs_addr;
        unsigned int  service_area_addr;
        unsigned int  sa_intreg_addr;
    }T_TM_ADDR_LIST;
    
#endif

