#ifndef _HAL_DMAC_H_
#define _HAL_DMAC_H_

#include <attrs.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef enum {
    HAL_DMAC_CH_NOT_FOUND       = -14,       ///< Free channel was not found
    HAL_DMAC_CH_BUSY  = -2,     ///< channel is busy
    HAL_DMAC_STATUS_INVALID_PARAMETER  = -1,     ///< parameter error
    HAL_DMAC_STATUS_OK                 =  0,      /// < status ok
    HAL_DMAC_CH_FREE                 =  1,      /// < status ok
    HAL_DMAC_REG_GET_NG                 =  0xffffffff      /// < register get fail
} hal_dmac_status_t;

typedef enum _DMAC_TR_WIDTH_E {
    DMAC_TR_WIDTH_8          = 0,         ///< 8 bits (1 Bytes)
    DMAC_TR_WIDTH_16        = 1,         ///< 16 bits (2 Bytes)
    DMAC_TR_WIDTH_32        = 2         ///< 32 bits (4 Bytes)
} DMAC_TR_WIDTH_E;

typedef enum _DMAC_INC_E {
    DMAC_ADDR_INCREMENT     = 0,        ///< Address Increment
    DMAC_ADDR_DECREMENT     = 1,        ///< Address Decrement
    DMAC_ADDR_NO_CHANGE     = 2         ///< Address No change
} DMAC_INC_E;

typedef enum _DMAC_MSIZE_E {
    DMAC_MSIZE_1            = 0,        ///< Burst Transaction of Length 1
    DMAC_MSIZE_4            = 1,         ///< Burst Transaction of Length 4
} DMAC_MSIZE_E;

typedef enum _DMAC_TT_FC_E {
    DMAC_TT_FC_M2M_Dma      = 0,        ///< Memory to Memory
    DMAC_TT_FC_M2P_Dma      = 1,        ///< Memory to Peripheral
    DMAC_TT_FC_P2M_Dma      = 2,         ///< Peripheral to Memory
    DMAC_TT_FC_P2P_Dma       = 3         ///< Peripheral to Peripheral
} DMAC_TT_FC_E;

typedef enum _DMAC_CH_PRIOR_E {
    DMAC_CH_PRIOR_0         = 0,        ///< Lowest Priority
    DMAC_CH_PRIOR_1         = 1,
    DMAC_CH_PRIOR_2         = 2,
    DMAC_CH_PRIOR_3         = 3,
    DMAC_CH_PRIOR_4         = 4,
    DMAC_CH_PRIOR_5         = 5,
    DMAC_CH_PRIOR_6         = 6,
    DMAC_CH_PRIOR_7         = 7,         ///< Highest Priority
} DMAC_CH_PRIOR_E;

typedef enum _DMAC_HS_SEL_E {
    DMAC_HS_SEL_HARDWARE    = 0,        ///< Handshaking Interface Select Hardware
    DMAC_HS_SEL_SOFTWARE    = 1         ///< Handshaking Interface Select Software
} DMAC_HS_SEL_E;

typedef enum _DMAC_PER_E {
    DMAC_HW_HS_IF_I2S_RX    = 0,        ///< Hardware Handshaking Interface Select I2S Receiver, [0, 7] channel can use
    DMAC_HW_HS_IF_I2S_TX    = 1,        ///< Hardware Handshaking Interface Select I2S Transmitterr, [0, 7] channel can use
    DMAC_HW_HS_IF_SPI_RX    = 2,        ///< Hardware Handshaking Interface Select SPI Master Receiverr, [0, 7] channel can use
    DMAC_HW_HS_IF_SPI_TX    = 3,        ///< Hardware Handshaking Interface Select SPI Master Transmitterr, [0, 7] channel can use
    DMAC_HW_HS_IF_I2C_RX    = 4,        ///< Hardware Handshaking Interface Select I2C Master Receiverr, [0, 7] channel can use
    DMAC_HW_HS_IF_I2C_TX    = 5,         ///< Hardware Handshaking Interface Select I2C Master Transmitterr, [0, 7] channel can use
    DMAC_HW_HS_IF_SPI_S_RX    = 6,        ///< Hardware Handshaking Interface Select SPI Slave Receiverr, [0, 7] channel can use
    DMAC_HW_HS_IF_SPI_S_TX    = 7,         ///< Hardware Handshaking Interface Select SPI Slave Transmitterr, [0, 7] channel can use
    DMAC_HW_HS_IF_I2S1_RX    = 8,        ///< Hardware Handshaking Interface Select I2S1 Receiver, [8, 15] channel can use
    DMAC_HW_HS_IF_I2S1_TX    = 9,        ///< Hardware Handshaking Interface Select I2S1 Transmitterr, [8, 15] channel can use
    DMAC_HW_HS_IF_SPI1_RX    = 10,        ///< Hardware Handshaking Interface Select SPI Master1 Receiverr, [8, 15] channel can use
    DMAC_HW_HS_IF_SPI1_TX    = 11,        ///< Hardware Handshaking Interface Select SPI Master1 Transmitterr, [8, 15] channel can use
    DMAC_HW_HS_IF_I2C1_RX    = 12,        ///< Hardware Handshaking Interface Select I2C Master1 Receiverr, [8, 15] channel can use
    DMAC_HW_HS_IF_I2C1_TX    = 13,         ///< Hardware Handshaking Interface Select I2C Master1 Transmitterr, [8, 15] channel can use
    DMAC_HW_HS_IF_SPI1_S_RX    = 14,        ///< Hardware Handshaking Interface Select SPI Slave1 Receiverr, [8, 15] channel can use
    DMAC_HW_HS_IF_SPI1_S_TX    = 15,         ///< Hardware Handshaking Interface Select SPI Slave1 Transmitterr, [8, 15] channel can use
    DMAC_HW_HS_IF_SPI2_RX    = 16,        ///< Hardware Handshaking Interface Select SPI Master2 Receiverr, [8, 15] channel can use
    DMAC_HW_HS_IF_SPI2_TX    = 17,         ///< Hardware Handshaking Interface Select SPI Master2 Transmitterr, [8, 15] channel can use
} DMAC_PER_E;

typedef enum _DMAC_INT_TYPE_E {
    DMAC_INT_TYPE_Tfr       = 0,        ///< Transfer Complete Interrupt Type
    DMAC_INT_TYPE_Block   = 1,        ///< Transfer Block Complete Interrupt Type
    DMAC_INT_TYPE_Err       = 4         ///< Error Interrupt Type
} DMAC_INT_TYPE_E;

typedef enum _DMAC_CH_E {
    DMAC_CH_0               = 0x0,        ///< Channel 0,dmac1
    DMAC_CH_1               = 0x1,        ///< Channel 1,dmac1
    DMAC_CH_2               = 0x2,        ///< Channel 2,dmac1
    DMAC_CH_3               = 0x3,        ///< Channel 3,dmac1
    DMAC_CH_4               = 0x4,        ///< Channel 4,dmac1
    DMAC_CH_5               = 0x5,        ///< Channel 5,dmac1
    DMAC_CH_6               = 0x6,        ///< Channel 6,dmac1
    DMAC_CH_7               = 0x7,        ///< Channel 7,dmac1
    DMAC_CH_8               = 0x8,     ///< Channel 1,dmac2
    DMAC_CH_9               = 0x9,     ///< Channel 2,,dmac2
    DMAC_CH_10             = 0xa,     ///< Channel 3,dmac2
    DMAC_CH_11             = 0xb,     ///< Channel 4,dmac2
    DMAC_CH_12             = 0xc,     ///< Channel 5,dmac2
    DMAC_CH_13             = 0xd,     ///< Channel 6,dmac2
    DMAC_CH_14             = 0xe,     ///< Channel 7,dmac2
    DMAC_CH_15             = 0xf,     ///< Channel 8,dmac2
    DMAC_CH_MAX,                        ///< Maximum number of channels
} DMAC_CH_E;

typedef enum _DMAC_BLOCKING_MODE_E {
    DMAC_NON_BLOCKING       = 0,        ///< Sets the DMAC HAL driver to operate in non-blocking mode
    DMAC_BLOCKING           = 1         ///< Sets the DMAC HAL driver to operate in blocking mode
} DMAC_BLOCKING_MODE_E;

typedef struct _lli
{
    uint32_t  sar;
    uint32_t  dar;
    uint32_t  llp;
    uint32_t  ctl1;
    uint32_t  ctl2;
} lli;

/**
 * @brief Prototype for the DMAC interrupt service routine.
 *
 * @param   CH                          Specifies the channel number.
 * @param   INT_TYPE                    Specifies the type of interrupt source.
 */
typedef void (*DMAC_ISR)(
    DMAC_CH_E  CH,
    DMAC_INT_TYPE_E INT_TYPE
    );

/**
 * @brief Enable all interrupt service routine with DMAC interrupt handler.
 *
 */
void hal_dmac_enable_all_register_isr();

/**
 * @brief Disable all interrupt service routine with DMAC interrupt handler.
 *
 */
void hal_dmac_disable_all_register_isr();

/**
 * @brief Registers an interrupt service routine to be called from the DMAC interrupt handler.
 *
 * If ISR is NULL, then the DMAC interrupt is disabled.
 *
 * @param   CH                          Specifies the channel number.
 * @param   INT_TYPE                      Specifies the type of interrupt source.
 * @param   ISR                         A pointer to an ISR function that is called when a DMAC interrupt handler occurs.
 *                                      NULL to disable interrupt.
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_register_isr(
    DMAC_CH_E CH,
    DMAC_INT_TYPE_E NT_TYPE,
    DMAC_ISR ISR) ATTRIBUTE_SECTION_FAST;

/**
 * @brief Un -registers an interrupt service routine with DMAC interrupt handler.
 *
 * If ISR is NULL, then the DMAC interrupt is disabled.
 *
 * @param   CH                          Specifies the channel number.
 * @param   INT_TYPE                      Specifies the type of interrupt source.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_un_register_isr(
    DMAC_CH_E CH,
    DMAC_INT_TYPE_E INT_TYPE);

/**
 * @brief Initialize the DMAC hardware.
 */
void hal_dmac_init();

/**
 *@brief  Deinitialize the DMAC hardware.
 */
void hal_dmac_deinit();
    
/**
 * @brief Start the DMAC transfer.
 *
 * @param   DAR                         Specifies the start destination address.
 * @param   SAR                         Specifies the start source address.
 * @param   BLOCK_TS                    Specifies the block transfer size, [0, 4095]  range.
 * @param   CH                          Specifies the channel number.
 * @param   DST_TR_WIDTH                Specifies the destination transfer width.[8 or 16 or 32]bit
 * @param   SRC_TR_WIDTH                Specifies the source transfer width.[8 or 16 or 32]bit
 * @param   DINC                        Specifies the destination address increment, decrement, or no change.
 * @param   SINC                        Specifies the source address increment, decrement, or no change.
 * @param   DST_MSIZE                   Specifies the destination burst transaction length.
 * @param   SRC_MSIZE                   Specifies the source burst transaction length.
 * @param   TT_FC                       Specifies the transfer type and flow control.
 * @param   CH_PRIOR                    Specifies the channel priority.
 * @param   HS_SEL_DST                  Specifies the type of destination handshaking interface.
 * @param   DST_PER                     Specifies the hardware of destination handshaking interface.
 * @param   HS_SEL_SRC                  Specifies the type of source handshaking interface.
 * @param   SRC_PER                     Specifies the hardware of source handshaking interface.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_start(
    void *DAR,
    void const *SAR,
    uint32_t BLOCK_TS,
    DMAC_CH_E CH,
    DMAC_TR_WIDTH_E DST_TR_WIDTH,
    DMAC_TR_WIDTH_E SRC_TR_WIDTH,
    DMAC_INC_E DINC,
    DMAC_INC_E SINC,
    DMAC_MSIZE_E DST_MSIZE,
    DMAC_MSIZE_E SRC_MSIZE,
    DMAC_TT_FC_E TT_FC,
    DMAC_CH_PRIOR_E CH_PRIOR,
    DMAC_HS_SEL_E HS_SEL_DST,
    DMAC_PER_E DST_PER,
    DMAC_HS_SEL_E HS_SEL_SRC,
    DMAC_PER_E SRC_PER) ATTRIBUTE_SECTION_FAST;

/**
 * @brief Start the DMAC transfer will linked list.
 *
 * @param   DAR                         Specifies the start destination address.
 * @param   SAR                         Specifies the start source address.
 * @param   BLOCK_TS                    Specifies the block transfer size, [0, 4095]  range.
 * @param   CH                          Specifies the channel number.
 * @param   DST_TR_WIDTH                Specifies the destination transfer width.[8 or 16 or 32]bit
 * @param   SRC_TR_WIDTH                Specifies the source transfer width.[8 or 16 or 32]bit
 * @param   DINC                        Specifies the destination address increment, decrement, or no change.
 * @param   SINC                        Specifies the source address increment, decrement, or no change.
 * @param   DST_MSIZE                   Specifies the destination burst transaction length.
 * @param   SRC_MSIZE                   Specifies the source burst transaction length.
 * @param   TT_FC                       Specifies the transfer type and flow control.
 * @param   CH_PRIOR                    Specifies the channel priority.
 * @param   HS_SEL_DST                  Specifies the type of destination handshaking interface.
 * @param   DST_PER                     Specifies the hardware of destination handshaking interface.
 * @param   HS_SEL_SRC                  Specifies the type of source handshaking interface.
 * @param   SRC_PER                     Specifies the hardware of source handshaking interface.
 * @param   LLP_ADDRESS                   first linked list poniter. if address is 0, then equel hal_dmac_start function
 * @param   LLP_NUMBER                    linked list number. if number is  0, then equel hal_dmac_start function
 * ex: LLP_NUMBER = 2
 * settting lli[0].sar = your first source address,  li[1].sar = your second source address
 * settting lli[0].dar = your first dest address,  li[1].dar = your second dest address
 * settting lli[0].llp = &lli[1](you need linked second lli address)  li[1].llp = 0 (end of linked list)
 * settting lli[0].ctl2 = you need first linked list transfer size  lli[1].ctl2 = you need second linked list transfer size
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_start_lli(
    void *DAR,
    void const *SAR,
    uint32_t BLOCK_TS,
    DMAC_CH_E CH,
    DMAC_TR_WIDTH_E DST_TR_WIDTH,
    DMAC_TR_WIDTH_E SRC_TR_WIDTH,
    DMAC_INC_E DINC,
    DMAC_INC_E SINC,
    DMAC_MSIZE_E DST_MSIZE,
    DMAC_MSIZE_E SRC_MSIZE,
    DMAC_TT_FC_E TT_FC,
    DMAC_CH_PRIOR_E CH_PRIOR,
    DMAC_HS_SEL_E HS_SEL_DST,
    DMAC_PER_E DST_PER,
    DMAC_HS_SEL_E HS_SEL_SRC,
    DMAC_PER_E SRC_PER,
    lli* LLP_ADDRESS,
    uint32_t LLP_NUMBER);

/**
 * @brief Stop the DMAC transfer.
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_stop(
    DMAC_CH_E CH);

/**
 * @brief This service finds a free DMAC channel.
 *
 * @param   BLOCKING_MODE               Sets the DMAC HAL driver to operate in blocking or non-blocking mode.
 *
  * @return
 *     - DMAC_CH_NOT_FOUND
 *     - Returns the free channel number.
 */
DMAC_CH_E hal_dmac_find_free_channel(
    DMAC_BLOCKING_MODE_E BLOCKING_MODE) ATTRIBUTE_SECTION_FAST;

/**
 * @brief This service get specifies  channel status.
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_CH_BUSY
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_get_channel_status (
    DMAC_CH_E CH);
    
/**
 * @brief This service reads the DMAC interrupt raw status value.
 *
 * @param   CH                          Specifies the channel number.
 * @param   INT_TYPE                 Specifies the type of interrupt source.
 *
 *     - HAL_DMAC_CH_BUSY
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HHAL_DMAC_CH_FREE
 */
int32_t hal_dmac_get_int_raw_status (
    DMAC_CH_E CH,
    DMAC_INT_TYPE_E INT_TYPE);

/**
 * @brief This service clears the status that indicates the DMAC interrupt source.
 *
 * @param   CH                          Specifies the channel number.
 * @param   INT_TYPE                    Specifies the type of interrupt source.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_clear_int_status (
    DMAC_CH_E CH,
    DMAC_INT_TYPE_E INT_TYPE) ATTRIBUTE_SECTION_FAST;

/**
 * @brief sar register get with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_REG_GET_NG
 *     - register value
 */
uint32_t hal_dmac_sar_get(
    DMAC_CH_E CH);

/**
 * @brief Sar register set with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   SAR                        Set the sar register value
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_sar_set(
    DMAC_CH_E CH, 
    uint32_t SAR);

/**
 * @brief Dar register get with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_REG_GET_NG
 *     - register value
 */
uint32_t hal_dmac_dar_get(
    DMAC_CH_E CH);

/**
 * @brief Dar register set with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   DAR                       Set the dar register value
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_dar_set(
    DMAC_CH_E CH, 
    uint32_t DAR);

/**
 * @brief Get linked list pointer address value with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_REG_GET_NG
 *     - register value
 */
uint32_t hal_dmac_llp_get(
    DMAC_CH_E CH);

/**
 * @brief Set linked list pointer address value with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   LLP                          Set the linked list pointer with address pointer
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_llp_set(
    DMAC_CH_E CH, 
    uint32_t LLP);

/**
 * @brief Ctl1 register get with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_REG_GET_NG
 *     - register value
 */
uint32_t hal_dmac_ctl1_get(
    DMAC_CH_E CH);

/**
 * @brief Ctl1 register set with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   CTL1                      Set the ctl1 register value
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_ctl1_set(
    DMAC_CH_E CH, 
    uint32_t CTL1);

/**
 * @brief Ctl2 register get with DMAC
 *
 * @param   CH                          Specifies the channel number.
  *
 * @return
 *     - HAL_DMAC_REG_GET_NG
 *     - register value
 */
uint32_t hal_dmac_ctl2_get(
    DMAC_CH_E CH);

/**
 * @brief Ctl2 register set with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   CTL2                      Set the ctl2 register value
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_ctl2_set(
    DMAC_CH_E CH, 
    uint32_t CFG1);

/**
 * @brief Cfg1 register get with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_REG_GET_NG
 *     - register value
 */
uint32_t hal_dmac_cfg1_get(
    DMAC_CH_E CH);

/**
 * @brief Cfg1 register set with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   CFG1                      Set the cfg1 register value
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_cfg1_set(
    DMAC_CH_E CH,
    uint32_t CFG1);

/**
 * @brief Cfg2 register get with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_REG_GET_NG
 *     - register value
 */
uint32_t hal_dmac_cfg2_get(
    DMAC_CH_E CH);

/**
 * @brief Cfg2 register set with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   CFG2                      Set the cfg2 register value
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_cfg2_set(
    DMAC_CH_E CH, 
    uint32_t CFG2);

/**
 * @brief Source address enable auto reload with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_src_auto_reload_enable(
    DMAC_CH_E CH);

/**
 * @brief Source address disable auto reload with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
 
int32_t hal_dmac_src_auto_reload_disable(
    DMAC_CH_E CH);

/**
 * @brief Destination address enable auto reload with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_dst_auto_reload_enable(
    DMAC_CH_E CH);

/**
 * @brief Destination address disable auto reload with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_dst_auto_reload_disable(
    DMAC_CH_E CH);

/**
 * @brief Source address enable linked list pointer with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_src_llp_enable(
    DMAC_CH_E CH);

/**
 * @brief Source address disable linked list pointer with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_src_llp_disable(
    DMAC_CH_E CH);

/**
 * @brief Destination address enable linked list pointer with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_dst_llp_enable(
    DMAC_CH_E CH);

/**
 * @brief Destination address disable linked list pointer with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_dst_llp_disable(
    DMAC_CH_E CH);

/**
 * @brief Source address enable gatter with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_src_gatter_enable(
    DMAC_CH_E CH);

/**
 * @brief Source address disable gatter with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_src_gatter_disable(
    DMAC_CH_E CH);

/**
 * @brief Source address  gatter parameter get with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   CNT                        Get gatter parameter with count number, [1, 4095] range.
 * @param   JUMP                     Get gatter parameter with jump number, [1, 1048575] range.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_src_gatter_get(
    DMAC_CH_E CH,
    uint32_t *CNT,
    uint32_t *JUMP);

/**
 * @brief Source address  gatter parameter set with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   CNT                        Set gatter parameter with count number, [1, 4095] range.
 * @param   JUMP                     Set gatter parameter with jump number, [1, 1048575] range.
 * ex: CNT = 2, JUMP = 1
 * src address                                dst address
 * |--------------                |----------
 * |1 |2|3|4|5|6|...                 |1 |2|4|5|... 
 * |--------------                |----------
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_src_gatter_set(
    DMAC_CH_E CH,
    uint32_t CNT,
    uint32_t JUMP);

/**
 * @brief Destination address enable scatter with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_dst_scatter_enable(
    DMAC_CH_E CH);

/**
 * @brief Destination address disable scatter with DMAC
 *
 * @param   CH                          Specifies the channel number.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_dst_scatter_disable(
    DMAC_CH_E CH);

/**
 * @brief Destination address  scatter parameter get with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   CNT                        Get scatter parameter with count number, [1, 4095] range.
 * @param   JUMP                     Get scatter parameter with jump number, [1, 1048575] range.
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_dst_scatter_get(
    DMAC_CH_E CH, 
    uint32_t *CNT, 
    uint32_t *JUMP);

/**
 * @brief Destination address  scatter parameter set with DMAC
 *
 * @param   CH                          Specifies the channel number.
 * @param   CNT                        Set scatter parameter with count number, [1, 4095] range.
 * @param   JUMP                     Set scatter parameter with jump number, [1, 1048575] range.
 * ex: CNT = 2, JUMP = 1
 * src address                                dst address
 * |--------------                |------------------
 * |1 |2|3|4|5|6|...                 |1 |2|X |3|4|X|5|6|X|...
 * |--------------                |------------------
 *
 * @return
 *     - HAL_DMAC_STATUS_INVALID_PARAMETER
 *     - HAL_DMAC_STATUS_OK
 */
int32_t hal_dmac_dst_scatter_set(
    DMAC_CH_E CH, 
    uint32_t CNT, 
    uint32_t JUMP);

/**
 * @brief special mode with burst copy, before use busrt copy need use thie api
 *
 */
void hal_dmac_burst_enter() ATTRIBUTE_SECTION_FAST;

/**
 * @brief special mode with burst copy, after use busrt copy need use thie api
 *
 */
void hal_dmac_burst_exit() ATTRIBUTE_SECTION_FAST;

int32_t hal_dmac_start_long_data(
    lli* llp_ptr,
    uint32_t llp_len,
    void *dar,
    void const *sar,
    uint32_t  data_length,
    DMAC_INC_E dinc,
    DMAC_INC_E sinc,
    DMAC_MSIZE_E dst_msize,
    DMAC_MSIZE_E src_msize,
    DMAC_TT_FC_E tt_fc,

    DMAC_CH_E ch,
    DMAC_CH_PRIOR_E ch_prior,
    DMAC_HS_SEL_E hs_sel_dst,
    DMAC_PER_E dst_per,
    DMAC_HS_SEL_E hs_sel_src,
    DMAC_PER_E src_per);
#endif  // #ifndef _HAL_DMAC_H_

