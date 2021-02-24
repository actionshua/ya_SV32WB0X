
#include "hal_dmac.h"
#include "drv_dmac.h"
#include <stdio.h>

#define DMAH_MAX_BLK_SIZE   (0xFFFUL)

#if (defined (CONFIG_OS_FREERTOS))
#include "osal/osal.h"

static OsSemaphore  gOsSemaphore;
DMAC_CH_E           gDMAC_CHANNEL_ENABLE_BITMAP;
#endif

uint32_t gDMAC_VALUE[DMAC_CH_MAX];
static int dmac_en = 0;
void
drv_dmac_init (
    void
    )
{
    if(dmac_en == 0) {
#if (defined (CONFIG_OS_FREERTOS))
        OS_STATUS OsStatus = OS_SemInit (&gOsSemaphore, DMAC_CH_MAX, DMAC_CH_MAX);
        configASSERT (OsStatus != OS_FAILED);

        gDMAC_CHANNEL_ENABLE_BITMAP = 0;
#endif

        hal_dmac_init ();
        dmac_en = 1;
    }
}

void
drv_dmac_deinit (
    void
    )
{
    if(dmac_en == 1) {
#if (defined (CONFIG_OS_FREERTOS))
        OS_STATUS OsStatus = OS_SemDelete (gOsSemaphore);
        configASSERT (OsStatus != OS_FAILED);
#endif

        hal_dmac_deinit ();
        dmac_en = 0;
    }
}

#if(CHIP_ID==6020)
static volatile int flag = 0;
static void drv_dma_burst_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type) ATTRIBUTE_SECTION_FAST;
    
static void drv_dma_burst_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type)
{
    flag = 1;
    hal_dmac_clear_int_status(ch, int_type);
}

int
drv_dmac_burst_copy (
    uint8_t                 *dst,
    uint8_t const           *src,
    uint32_t                count
    )
{
    uint32_t BLOCK_TS = 0, cnt = 0;
    uint32_t BLOCK__MAX_TS = 0xfe0;
    uint32_t BLOCK_TS_NUM = 0;
    int32_t channel;
    int i = 0;

    channel = hal_dmac_find_free_channel (DMAC_BLOCKING);
    if(channel == HAL_DMAC_CH_NOT_FOUND)
        return DRV_DMAC_CH_NOT_FOUND;

    hal_dmac_burst_enter();

    BLOCK_TS_NUM = (count >> DMAC_TR_WIDTH_32);     // DMA Block Transfer Size.
    count &= ((1UL << DMAC_TR_WIDTH_32) - 1UL); // remainder of the remaining bytes

    //
    // CPU copy the remainder of the remaining bytes.
    //
    if (count) {
        memcpy (dst + (BLOCK_TS_NUM << DMAC_TR_WIDTH_32), src, count);
    }

    hal_dmac_clear_int_status(channel, DMAC_INT_TYPE_Tfr);
    hal_dmac_register_isr(channel, DMAC_INT_TYPE_Tfr, drv_dma_burst_isr);
    
    while(BLOCK_TS_NUM > 0) {
        flag = 0;
        if(BLOCK_TS_NUM >=BLOCK__MAX_TS)
            BLOCK_TS = BLOCK__MAX_TS;
        else
            BLOCK_TS = BLOCK_TS_NUM;
        BLOCK_TS_NUM -= BLOCK_TS;
        hal_dmac_start (
            dst + (cnt*BLOCK__MAX_TS*4),
            src + (cnt*BLOCK__MAX_TS*4),
            BLOCK_TS,
            channel,
            DMAC_TR_WIDTH_32,
            DMAC_TR_WIDTH_32,
            DMAC_ADDR_INCREMENT,
            DMAC_ADDR_INCREMENT,
            DMAC_MSIZE_1,
            DMAC_MSIZE_1,
            DMAC_TT_FC_M2M_Dma,
            DMAC_CH_PRIOR_7,
            DMAC_HS_SEL_SOFTWARE,
            0,  // Assigns a hardware handshaking interface to the DST of channel if the CFGx.HS_SEL_DST field is 0; otherwise, this field is ignored.
            DMAC_HS_SEL_SOFTWARE,
            0   // Assigns a hardware handshaking interface to the SRC of channel if the CFGx.HS_SEL_SRC field is 0; otherwise, this field is ignored.
            );

        while(flag == 0);
        cnt++;
    }
    hal_dmac_burst_exit();

    return 0;
}

int
drv_dmac_run (
    uint8_t                 *dst,
    uint8_t const           *src,
    uint32_t                count,
    DRV_DMAC_CH_E   CH
    )
{
    uint32_t BLOCK_TS;
    int32_t channel;
    int32_t         retval;
    if(CH == DRV_DMAC_CH_AUTO) {
        channel = hal_dmac_find_free_channel (DMAC_BLOCKING);
        if(channel == HAL_DMAC_CH_NOT_FOUND)
            return DRV_DMAC_CH_NOT_FOUND;
    } else {
        channel = hal_dmac_get_channel_status(CH);
         if(channel == -1)
            return DRV_DMAC_CH_NOT_FOUND;
        if(channel == -2)
            return DRV_DMAC_CH_IS_BUSY;
        else if(channel == 0)
            channel = CH;
    }
    BLOCK_TS = (count >> DMAC_TR_WIDTH_32);     // DMA Block Transfer Size.
    count &= ((1UL << DMAC_TR_WIDTH_32) - 1UL); // remainder of the remaining bytes

    //
    // CPU copy the remainder of the remaining bytes.
    //
    if (count) {
        memcpy (dst + (BLOCK_TS << DMAC_TR_WIDTH_32), src, count);
    }

    //
    // DMA copy
    //
    if (BLOCK_TS & DMAH_MAX_BLK_SIZE) {
        hal_dmac_start (
            dst,
            src,
            BLOCK_TS,
            CH,
            DMAC_TR_WIDTH_32,
            DMAC_TR_WIDTH_32,
            DMAC_ADDR_INCREMENT,
            DMAC_ADDR_INCREMENT,
            DMAC_MSIZE_1,
            DMAC_MSIZE_1,
            DMAC_TT_FC_M2M_Dma,
            DMAC_CH_PRIOR_0,
            DMAC_HS_SEL_SOFTWARE,
            0,  // Assigns a hardware handshaking interface to the DST of channel if the CFGx.HS_SEL_DST field is 0; otherwise, this field is ignored.
            DMAC_HS_SEL_SOFTWARE,
            0   // Assigns a hardware handshaking interface to the SRC of channel if the CFGx.HS_SEL_SRC field is 0; otherwise, this field is ignored.
            );

        do {
            retval = hal_dmac_get_int_raw_status (channel, DMAC_INT_TYPE_Tfr);
            OS_TickDelay(10);
        } while (retval != 1);

        retval = hal_dmac_clear_int_status (channel, DMAC_INT_TYPE_Tfr);
        return 0;
    }

    //
    // DMA has not been started.
    //
    return -19;
}
#endif

int32_t
drv_internal_dmac_m2mcpy32 (
    uint8_t                 *DAR,
    uint8_t const           *SAR,
    uint32_t                COUNT,
    DMAC_CH_E               CH
    )
{
    uint32_t BLOCK_TS;

    BLOCK_TS = (COUNT >> DMAC_TR_WIDTH_32);     // DMA Block Transfer Size.
    COUNT &= ((1UL << DMAC_TR_WIDTH_32) - 1UL); // remainder of the remaining bytes

    //
    // CPU copy the remainder of the remaining bytes.
    //
    if (COUNT) {
        memcpy (DAR + (BLOCK_TS << DMAC_TR_WIDTH_32), SAR + (BLOCK_TS << DMAC_TR_WIDTH_32), COUNT);
    }

    //
    // DMA copy
    //
    if (BLOCK_TS & DMAH_MAX_BLK_SIZE) {
        hal_dmac_start (
            DAR,
            SAR,
            BLOCK_TS,
            CH,
            DMAC_TR_WIDTH_32,
            DMAC_TR_WIDTH_32,
            DMAC_ADDR_INCREMENT,
            DMAC_ADDR_INCREMENT,
            DMAC_MSIZE_1,
            DMAC_MSIZE_1,
            DMAC_TT_FC_M2M_Dma,
            DMAC_CH_PRIOR_0,
            DMAC_HS_SEL_SOFTWARE,
            0,  // Assigns a hardware handshaking interface to the DST of channel if the CFGx.HS_SEL_DST field is 0; otherwise, this field is ignored.
            DMAC_HS_SEL_SOFTWARE,
            0   // Assigns a hardware handshaking interface to the SRC of channel if the CFGx.HS_SEL_SRC field is 0; otherwise, this field is ignored.
            );

        return 0;
    }

    //
    // DMA has not been started.
    //
    return -19;
}

int32_t
drv_internal_dmac_m2mset8 (
    uint8_t                 *DAR,
    uint32_t                *SAR,
    uint32_t                COUNT,
    DMAC_CH_E               CH
    )
{
    uint32_t BLOCK_TS;

    BLOCK_TS = (COUNT >> DMAC_TR_WIDTH_32);     // DMA Block Transfer Size.
    COUNT &= ((1UL << DMAC_TR_WIDTH_32) - 1UL); // remainder of the remaining bytes

    *SAR &= 0xFFUL;
    *SAR |= (*SAR << 24) | (*SAR << 16) | (*SAR << 8);

    //
    // CPU copy the remainder of the remaining bytes.
    //
    if (COUNT) {
        memcpy (DAR + (BLOCK_TS << DMAC_TR_WIDTH_32), SAR, COUNT);
    }

    //
    // DMA copy
    //
    if (BLOCK_TS & DMAH_MAX_BLK_SIZE) {
        hal_dmac_start (
            DAR,
            SAR,
            BLOCK_TS,
            CH,
            DMAC_TR_WIDTH_32,
            DMAC_TR_WIDTH_32,
            DMAC_ADDR_INCREMENT,
            DMAC_ADDR_NO_CHANGE,
            DMAC_MSIZE_1,
            DMAC_MSIZE_1,
            DMAC_TT_FC_M2M_Dma,
            DMAC_CH_PRIOR_0,
            DMAC_HS_SEL_SOFTWARE,
            0,  // Assigns a hardware handshaking interface to the DST of channel if the CFGx.HS_SEL_DST field is 0; otherwise, this field is ignored.
            DMAC_HS_SEL_SOFTWARE,
            0   // Assigns a hardware handshaking interface to the SRC of channel if the CFGx.HS_SEL_SRC field is 0; otherwise, this field is ignored.
            );

        return 0;
    }

    //
    // DMA has not been started.
    //
    return -19;
}

int32_t
drv_internal_dmac_m2mset16 (
    uint8_t                 *DAR,
    uint32_t                *SAR,
    uint32_t                COUNT,
    DMAC_CH_E               CH
    )
{
    uint32_t BLOCK_TS;

    BLOCK_TS = (COUNT >> DMAC_TR_WIDTH_32);     // DMA Block Transfer Size.
    COUNT &= ((1UL << DMAC_TR_WIDTH_32) - 1UL); // remainder of the remaining bytes

    *SAR &= 0xFFFFUL;
    *SAR |= (*SAR << 16);

    //
    // CPU copy the remainder of the remaining bytes.
    //
    if (COUNT) {
        memcpy (DAR + (BLOCK_TS << DMAC_TR_WIDTH_32), SAR, COUNT);
    }

    //
    // DMA copy
    //
    if (BLOCK_TS & DMAH_MAX_BLK_SIZE) {
        hal_dmac_start (
            DAR,
            SAR,
            BLOCK_TS,
            CH,
            DMAC_TR_WIDTH_32,
            DMAC_TR_WIDTH_32,
            DMAC_ADDR_INCREMENT,
            DMAC_ADDR_NO_CHANGE,
            DMAC_MSIZE_1,
            DMAC_MSIZE_1,
            DMAC_TT_FC_M2M_Dma,
            DMAC_CH_PRIOR_0,
            DMAC_HS_SEL_SOFTWARE,
            0,  // Assigns a hardware handshaking interface to the DST of channel if the CFGx.HS_SEL_DST field is 0; otherwise, this field is ignored.
            DMAC_HS_SEL_SOFTWARE,
            0   // Assigns a hardware handshaking interface to the SRC of channel if the CFGx.HS_SEL_SRC field is 0; otherwise, this field is ignored.
            );

        return 0;
    }

    //
    // DMA has not been started.
    //
    return -19;
}

int32_t
drv_internal_dmac_m2mset32 (
    uint8_t                 *DAR,
    uint32_t                *SAR,
    uint32_t                COUNT,
    DMAC_CH_E               CH
    )
{
    uint32_t BLOCK_TS;

    BLOCK_TS = (COUNT >> DMAC_TR_WIDTH_32);     // DMA Block Transfer Size.
    COUNT &= ((1UL << DMAC_TR_WIDTH_32) - 1UL); // remainder of the remaining bytes

    //
    // CPU copy the remainder of the remaining bytes.
    //
    if (COUNT) {
        memcpy (DAR + (BLOCK_TS << DMAC_TR_WIDTH_32), SAR, COUNT);
    }

    //
    // DMA copy
    //
    if (BLOCK_TS & DMAH_MAX_BLK_SIZE) {
        hal_dmac_start (
            DAR,
            SAR,
            BLOCK_TS,
            CH,
            DMAC_TR_WIDTH_32,
            DMAC_TR_WIDTH_32,
            DMAC_ADDR_INCREMENT,
            DMAC_ADDR_NO_CHANGE,
            DMAC_MSIZE_1,
            DMAC_MSIZE_1,
            DMAC_TT_FC_M2M_Dma,
            DMAC_CH_PRIOR_0,
            DMAC_HS_SEL_SOFTWARE,
            0,  // Assigns a hardware handshaking interface to the DST of channel if the CFGx.HS_SEL_DST field is 0; otherwise, this field is ignored.
            DMAC_HS_SEL_SOFTWARE,
            0   // Assigns a hardware handshaking interface to the SRC of channel if the CFGx.HS_SEL_SRC field is 0; otherwise, this field is ignored.
            );

        return 0;
    }

    //
    // DMA has not been started.
    //
    return -19;
}

int32_t
drv_dmac_memcpy32 (
    void                    *dst,
    void const              *src,
    int32_t                 count
    )
{
    int32_t         retval;
    DMAC_CH_E       channel;

#if (defined (CONFIG_OS_FREERTOS))
    DMAC_CH_E       i;
    OS_STATUS       OsStatus;
#endif

    //
    // count must be greater than zero, and less than or equal to 16380.
    //
    if ((count <= 0) || (count > 16380)) {
        return -4;
    }

    //
    // Un-aligned address is not supported.
    //
    if ((((uint32_t) dst) & ((1UL << DMAC_TR_WIDTH_32) - 1UL)) ||
        (((uint32_t) src) & ((1UL << DMAC_TR_WIDTH_32) - 1UL))) {
        return -3;
    }

#if (defined (CONFIG_OS_FREERTOS))
    do {
        OsStatus = OS_SemWait (gOsSemaphore, portMAX_DELAY);
        configASSERT (OsStatus != OS_FAILED);
    } while (OsStatus == OS_TIMEOUT);

    OS_EnterCritical ();
    {
        for (i = DMAC_CH_0; ; i++) {
            if (i == DMAC_CH_MAX) {
                i = DMAC_CH_0;
            }

            if ((gDMAC_CHANNEL_ENABLE_BITMAP & (1UL << i)) == 0) {
                gDMAC_CHANNEL_ENABLE_BITMAP |= (1UL << i);
                channel = i;
                break;
            }
        }
    }
    OS_ExitCritical ();
#else
    channel = hal_dmac_find_free_channel (DMAC_BLOCKING);
#endif

    retval = drv_internal_dmac_m2mcpy32 (dst, src, count, channel);
    if (retval != 0) {
        return retval;
    }

    //if (isr == NULL) {
        //
        // Polling completion status
        //
        do {
            retval = hal_dmac_get_int_raw_status (channel, DMAC_INT_TYPE_Tfr);
            OS_TickDelay(1);
        } while (retval != 1);

        retval = hal_dmac_clear_int_status (channel, DMAC_INT_TYPE_Tfr);

    #if (defined (CONFIG_OS_FREERTOS))
        OS_EnterCritical ();
        {
            gDMAC_CHANNEL_ENABLE_BITMAP &= (~(1UL << channel));
        }
        OS_ExitCritical ();

        OsStatus = OS_SemSignal (gOsSemaphore);
        configASSERT (OsStatus != OS_FAILED);
    #endif
    //}

    return 0;
}

int32_t
drv_dmac_memset8 (
    void                    *dst,
    uint8_t                 value,
    int32_t                 count
    )
{
    int32_t         retval;
    DMAC_CH_E       channel;

#if (defined (CONFIG_OS_FREERTOS))
    DMAC_CH_E       i;
    OS_STATUS       OsStatus;
#endif

    //
    // count must be greater than zero, and less than or equal to 16380.
    //
    if ((count <= 0) || (count > 16380)) {
        return -4;
    }

    //
    // Un-aligned address is not supported.
    //
    if ((((uint32_t) dst) & ((1UL << DMAC_TR_WIDTH_32) - 1UL)) ||
        (((uint32_t) gDMAC_VALUE) & ((1UL << DMAC_TR_WIDTH_32) - 1UL))) {
        return -3;
    }

#if (defined (CONFIG_OS_FREERTOS))
    do {
        OsStatus = OS_SemWait (gOsSemaphore, portMAX_DELAY);
        configASSERT (OsStatus != OS_FAILED);
    } while (OsStatus == OS_TIMEOUT);

    OS_EnterCritical ();
    {
        for (i = DMAC_CH_0; ; i++) {
            if (i == DMAC_CH_MAX) {
                i = DMAC_CH_0;
            }

            if ((gDMAC_CHANNEL_ENABLE_BITMAP & (1UL << i)) == 0) {
                gDMAC_CHANNEL_ENABLE_BITMAP |= (1UL << i);
                channel = i;
                break;
            }
        }
    }
    OS_ExitCritical ();
#else
    channel = hal_dmac_find_free_channel (DMAC_BLOCKING);
#endif

    gDMAC_VALUE[channel] = value;

    retval = drv_internal_dmac_m2mset8 (dst, &gDMAC_VALUE[channel], count, channel);
    if (retval != 0) {
        return retval;
    }

    //if (isr == NULL) {
        //
        // Polling completion status
        //
        do {
            retval = hal_dmac_get_int_raw_status (channel, DMAC_INT_TYPE_Tfr);
            OS_TickDelay(1);
        } while (retval != 1);

        retval = hal_dmac_clear_int_status (channel, DMAC_INT_TYPE_Tfr);

    #if (defined (CONFIG_OS_FREERTOS))
        OS_EnterCritical ();
        {
            gDMAC_CHANNEL_ENABLE_BITMAP &= (~(1UL << channel));
        }
        OS_ExitCritical ();

        OsStatus = OS_SemSignal (gOsSemaphore);
        configASSERT (OsStatus != OS_FAILED);
    #endif
    //}

    return 0;
}

int32_t
drv_dmac_memset16 (
    void                    *dst,
    uint16_t                value,
    int32_t                 count
    )
{
    int32_t         retval;
    DMAC_CH_E       channel;

#if (defined (CONFIG_OS_FREERTOS))
    DMAC_CH_E       i;
    OS_STATUS       OsStatus;
#endif

    //
    // count must be greater than zero, and less than or equal to 16380.
    //
    if ((count <= 0) || (count > 16380)) {
        return -4;
    }

    //
    // Un-aligned address is not supported.
    //
    if ((((uint32_t) dst) & ((1UL << DMAC_TR_WIDTH_32) - 1UL)) ||
        (((uint32_t) gDMAC_VALUE) & ((1UL << DMAC_TR_WIDTH_32) - 1UL))) {
        return -3;
    }

#if (defined (CONFIG_OS_FREERTOS))
    do {
        OsStatus = OS_SemWait (gOsSemaphore, portMAX_DELAY);
        configASSERT (OsStatus != OS_FAILED);
    } while (OsStatus == OS_TIMEOUT);

    OS_EnterCritical ();
    {
        for (i = DMAC_CH_0; ; i++) {
            if (i == DMAC_CH_MAX) {
                i = DMAC_CH_0;
            }

            if ((gDMAC_CHANNEL_ENABLE_BITMAP & (1UL << i)) == 0) {
                gDMAC_CHANNEL_ENABLE_BITMAP |= (1UL << i);
                channel = i;
                break;
            }
        }
    }
    OS_ExitCritical ();
#else
    channel = hal_dmac_find_free_channel (DMAC_BLOCKING);
#endif

    gDMAC_VALUE[channel] = value;

    retval = drv_internal_dmac_m2mset16 (dst, &gDMAC_VALUE[channel], count, channel);
    if (retval != 0) {
        return retval;
    }

    //if (isr == NULL) {
        //
        // Polling completion status
        //
        do {
            retval = hal_dmac_get_int_raw_status (channel, DMAC_INT_TYPE_Tfr);
            OS_TickDelay(1);
        } while (retval != 1);

        retval = hal_dmac_clear_int_status (channel, DMAC_INT_TYPE_Tfr);

    #if (defined (CONFIG_OS_FREERTOS))
        OS_EnterCritical ();
        {
            gDMAC_CHANNEL_ENABLE_BITMAP &= (~(1UL << channel));
        }
        OS_ExitCritical ();

        OsStatus = OS_SemSignal (gOsSemaphore);
        configASSERT (OsStatus != OS_FAILED);
    #endif
    //}

    return 0;
}

int32_t
drv_dmac_memset32 (
    void                    *dst,
    uint32_t                value,
    int32_t                 count
    )
{
    int32_t         retval;
    DMAC_CH_E       channel;

#if (defined (CONFIG_OS_FREERTOS))
    DMAC_CH_E       i;
    OS_STATUS       OsStatus;
#endif

    //
    // count must be greater than zero, and less than or equal to 16380.
    //
    if ((count <= 0) || (count > 16380)) {
        return -4;
    }

    //
    // Un-aligned address is not supported.
    //
    if ((((uint32_t) dst) & ((1UL << DMAC_TR_WIDTH_32) - 1UL)) ||
        (((uint32_t) gDMAC_VALUE) & ((1UL << DMAC_TR_WIDTH_32) - 1UL))) {
        return -3;
    }

#if (defined (CONFIG_OS_FREERTOS))
    do {
        OsStatus = OS_SemWait (gOsSemaphore, portMAX_DELAY);
        configASSERT (OsStatus != OS_FAILED);
    } while (OsStatus == OS_TIMEOUT);

    OS_EnterCritical ();
    {
        for (i = DMAC_CH_0; ; i++) {
            if (i == DMAC_CH_MAX) {
                i = DMAC_CH_0;
            }

            if ((gDMAC_CHANNEL_ENABLE_BITMAP & (1UL << i)) == 0) {
                gDMAC_CHANNEL_ENABLE_BITMAP |= (1UL << i);
                channel = i;
                break;
            }
        }
    }
    OS_ExitCritical ();
#else
    channel = hal_dmac_find_free_channel (DMAC_BLOCKING);
#endif

    gDMAC_VALUE[channel] = value;

    retval = drv_internal_dmac_m2mset32 (dst, &gDMAC_VALUE[channel], count, channel);
    if (retval != 0) {
        return retval;
    }

    //if (isr == NULL) {
        //
        // Polling completion status
        //
        do {
            retval = hal_dmac_get_int_raw_status (channel, DMAC_INT_TYPE_Tfr);
            OS_TickDelay(1);
        } while (retval != 1);

        retval = hal_dmac_clear_int_status (channel, DMAC_INT_TYPE_Tfr);

    #if (defined (CONFIG_OS_FREERTOS))
        OS_EnterCritical ();
        {
            gDMAC_CHANNEL_ENABLE_BITMAP &= (~(1UL << channel));
        }
        OS_ExitCritical ();

        OsStatus = OS_SemSignal (gOsSemaphore);
        configASSERT (OsStatus != OS_FAILED);
    #endif
    //}

    return 0;
}

