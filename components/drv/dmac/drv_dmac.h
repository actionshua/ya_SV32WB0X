#ifndef _DRV_DMAC_H_
#define _DRV_DMAC_H_

#include <attrs.h>
#include <stdint.h>

#if(CHIP_ID==6020)
typedef enum _DRV_DMAC_CH_E {
    DRV_DMAC_CH_0               = 0x0,
    DRV_DMAC_CH_1               = 0x1,
    DRV_DMAC_CH_2               = 0x2,
    DRV_DMAC_CH_3               = 0x3,
    DRV_DMAC_CH_4               = 0x4,
    DRV_DMAC_CH_5               = 0x5,
    DRV_DMAC_CH_6               = 0x6,
    DRV_DMAC_CH_7               = 0x7,
    DRV_DMAC_CH_8               = 0x8,
    DRV_DMAC_CH_9               = 0x9,
    DRV_DMAC_CH_10             = 0xa,
    DRV_DMAC_CH_11             = 0xb,
    DRV_DMAC_CH_12             = 0xc,
    DRV_DMAC_CH_13             = 0xd,
    DRV_DMAC_CH_14             = 0xe,
    DRV_DMAC_CH_15             = 0xf,
    DRV_DMAC_CH_MAX, 
    DRV_DMAC_CH_AUTO       = 0xff,
    DRV_DMAC_CH_NOT_FOUND = -14,
    DRV_DMAC_CH_IS_BUSY       = -15
} DRV_DMAC_CH_E;
#endif

/**
 * Initialize the DMAC hardware.
 */
void
drv_dmac_init (
    void
    );

/**
 * Deinitialize the DMAC hardware.
 */
void
drv_dmac_deinit (
    void
    );

#if(CHIP_ID==6020)
/**
 * Burst copies a source buffer(flash) to a destination buffer(DLM or Bus ram).
 *
 * @param   dst                         A pointer to the destination buffer of DLM or Busram copy.
 * @param   src                         A pointer to the source buffer of the flash copy.
 * @param   count                       The number of bytes to copy from source buffer to destination buffer.
 
 * @retval   DRV_DMAC_CH_NOT_FOUND                if ch use DRV_DMAC_CH_AUTO, and not find free channel
 * @retval    0                         The operation completed successfully.
 */
int
drv_dmac_burst_copy (
    uint8_t                 *dst,
    uint8_t const           *src,
    uint32_t                count
    ) ATTRIBUTE_SECTION_FAST;

/**
 * Copies a source buffer to a destination buffer.
 *
 * If isr is NULL, then the DMAC interrupt is disabled.
 *
 * @param   dst                         A pointer to the destination buffer of the memory copy.
 * @param   src                         A pointer to the source buffer of the memory copy.
 * @param   count                       The number of bytes to copy from source buffer to destination buffer.
 *                                      Contains at least the [1, 16380] range.
 * @param   ch                          Specifies the channel number
 
 * @retval  -19                         The DMAC has not been started.
 * @retval   DRV_DMAC_CH_NOT_FOUND                if ch use DRV_DMAC_CH_AUTO, and not find free channel
 * @retval   DRV_DMAC_CH_IS_BUSY                          if ch use specifies the channel number, and it used by other user
 * @retval    0                         The operation completed successfully.
 */
int
drv_dmac_run (
    uint8_t                 *dst,
    uint8_t const           *src,
    uint32_t                count,
    DRV_DMAC_CH_E   ch
    );
#endif

/**
 * Copies a source buffer to a destination buffer.
 *
 * If isr is NULL, then the DMAC interrupt is disabled.
 *
 * @param   dst                         A pointer to the destination buffer of the memory copy.
 * @param   src                         A pointer to the source buffer of the memory copy.
 * @param   count                       The number of bytes to copy from source buffer to destination buffer.
 *                                      Contains at least the [1, 16380] range.
 *
 * @retval  -19                         The DMAC has not been started.
 * @retval   -4                         The count was not the proper size.
 * @retval   -3                         The Un-aligned address is not supported.
 * @retval    0                         The operation completed successfully.
 */
int32_t
drv_dmac_memcpy32 (
    void                    *dst,
    void const              *src,
    int32_t                 count
    );

/**
 * Fills a destination buffer with an 8-bit value.
 *
 * If isr is NULL, then the DMAC interrupt is disabled.
 *
 * @param   dst                         A pointer to the destination buffer of the memory fill.
 * @param   value                       The value with which to fill count bytes of destination buffer.
 * @param   count                       The number of bytes to fill.
 *                                      Contains at least the [1, 16380] range.
 *
 * @retval  -19                         The DMAC has not been started.
 * @retval   -4                         The count was not the proper size.
 * @retval   -3                         The Un-aligned address is not supported.
 * @retval    0                         The operation completed successfully.
 */
int32_t
drv_dmac_memset8 (
    void                    *dst,
    uint8_t                 value,
    int32_t                 count
    );

/**
 * Fills a destination buffer with a 16-bit value.
 *
 * If isr is NULL, then the DMAC interrupt is disabled.
 *
 * @param   dst                         A pointer to the destination buffer of the memory fill.
 * @param   value                       The value with which to fill count bytes of destination buffer.
 * @param   count                       The number of bytes to fill.
 *                                      Contains at least the [1, 16380] range.
 *
 * @retval  -19                         The DMAC has not been started.
 * @retval   -4                         The count was not the proper size.
 * @retval   -3                         The Un-aligned address is not supported.
 * @retval    0                         The operation completed successfully.
 */
int32_t
drv_dmac_memset16 (
    void                    *dst,
    uint16_t                value,
    int32_t                 count
    );

/**
 * Fills a destination buffer with a 32-bit value.
 *
 * If isr is NULL, then the DMAC interrupt is disabled.
 *
 * @param   dst                         A pointer to the destination buffer of the memory fill.
 * @param   value                       The value with which to fill count bytes of destination buffer.
 * @param   count                       The number of bytes to fill.
 *                                      Contains at least the [1, 16380] range.
 *
 * @retval  -19                         The DMAC has not been started.
 * @retval   -4                         The count was not the proper size.
 * @retval   -3                         The Un-aligned address is not supported.
 * @retval    0                         The operation completed successfully.
 */
int32_t
drv_dmac_memset32 (
    void                    *dst,
    uint32_t                value,
    int32_t                 count
    );

#endif  // #ifndef _DRV_DMAC_H_

