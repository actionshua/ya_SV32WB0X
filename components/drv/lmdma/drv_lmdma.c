
#include "drv_lmdma.h"

#if (defined (CONFIG_OS_FREERTOS))
#include "osal/osal.h"

static OsSemaphore  gOsSemaphore;
LMDMA_CHAN_E        gLMDMA_CHANNEL_ENABLE_BITMAP;
#endif

void drv_lmdma_init (void)
{
#if (defined (CONFIG_OS_FREERTOS))
    OS_STATUS OsStatus = OS_SemInit (&gOsSemaphore, LMDMA_CHAN_MAX, LMDMA_CHAN_MAX);
    configASSERT (OsStatus != OS_FAILED);

    gLMDMA_CHANNEL_ENABLE_BITMAP = 0;
#endif

    hal_lmdma_init ();
}

void drv_lmdma_deinit (void)
{
#if (defined (CONFIG_OS_FREERTOS))
    OS_STATUS OsStatus = OS_SemDelete (gOsSemaphore);
    configASSERT (OsStatus != OS_FAILED);
#endif

    hal_lmdma_deinit ();
}

int32_t drv_lmdma_em2lmcpy32 (void *local_memory_address, void *external_memory_address, int32_t count, LMDMA_ISR isr)
{
    int32_t         retval;
    LMDMA_CHAN_E    channel;
    LMDMA_STATUS    status;

#if (defined (CONFIG_OS_FREERTOS))
    LMDMA_CHAN_E    i;
    OS_STATUS       OsStatus;
#endif

    //
    // count must be greater than zero.
    //
    if (count <= 0) {
        return -4;
    }

    if (!IS_LOCAL_MEMORY(local_memory_address)) {
        memcpy(local_memory_address, external_memory_address, count);
        if (isr != NULL) {
            isr(0, LMDMA_CIE);
        }
        return 0;
    }

#if (defined (CONFIG_OS_FREERTOS))
    do {
        OsStatus = OS_SemWait (gOsSemaphore, portMAX_DELAY);
        configASSERT (OsStatus != OS_FAILED);
    } while (OsStatus == OS_TIMEOUT);

    OS_EnterCritical ();
    {
        for (i = LMDMA_CHAN_0; ; i++) {
            if (i == LMDMA_CHAN_MAX) {
                i = LMDMA_CHAN_0;
            }

            if ((gLMDMA_CHANNEL_ENABLE_BITMAP & (1UL << i)) == 0) {
                gLMDMA_CHANNEL_ENABLE_BITMAP |= (1UL << i);
                channel = i;
                break;
            }
        }
    }
    OS_ExitCritical ();
#else
    channel = hal_lmdma_find_free_channel (LMDMA_BLOCKING);
#endif

    if (isr != NULL) {
        retval = hal_lmdma_register_isr (channel, LMDMA_CIE, isr);
        retval = hal_lmdma_register_isr (channel, LMDMA_EIE, isr);
    }

    retval = hal_lmdma_copy32 (
        local_memory_address,
        external_memory_address,
        count,
        channel,
        LMDMA_TDIR_EM2LM
        );
    if (retval != 0) {
        return retval;
    }

    if (isr == NULL) {
        //
        // Polling Channel Status: Wait for the DMA transfer completion
        //
        do {
            status.Reg32 = hal_lmdma_get_status (channel);
        } while (status.Bits.STAT != LMDMA_STAT_Complete);

    #if (defined (CONFIG_OS_FREERTOS))
        OS_EnterCritical ();
        {
            gLMDMA_CHANNEL_ENABLE_BITMAP &= (~(1UL << channel));
        }
        OS_ExitCritical ();

        OsStatus = OS_SemSignal (gOsSemaphore);
        configASSERT (OsStatus != OS_FAILED);
    #endif
    }

    return 0;
}

int32_t drv_lmdma_lm2emcpy32 (void *external_memory_address, void *local_memory_address, int32_t count, LMDMA_ISR isr)
{
    int32_t         retval;
    LMDMA_CHAN_E    channel;
    LMDMA_STATUS    status;

#if (defined (CONFIG_OS_FREERTOS))
    LMDMA_CHAN_E    i;
    OS_STATUS       OsStatus;
#endif

    //
    // count must be greater than zero.
    //
    if (count <= 0) {
        return -4;
    }

    if (!IS_LOCAL_MEMORY(local_memory_address)) {
        memcpy(external_memory_address, local_memory_address, count);
        if (isr != NULL) {
            isr(0, LMDMA_CIE);
        }
        return 0;
    }

#if (defined (CONFIG_OS_FREERTOS))
    do {
        OsStatus = OS_SemWait (gOsSemaphore, portMAX_DELAY);
        configASSERT (OsStatus != OS_FAILED);
    } while (OsStatus == OS_TIMEOUT);

    OS_EnterCritical ();
    {
        for (i = LMDMA_CHAN_0; ; i++) {
            if (i == LMDMA_CHAN_MAX) {
                i = LMDMA_CHAN_0;
            }

            if ((gLMDMA_CHANNEL_ENABLE_BITMAP & (1UL << i)) == 0) {
                gLMDMA_CHANNEL_ENABLE_BITMAP |= (1UL << i);
                channel = i;
                break;
            }
        }
    }
    OS_ExitCritical ();
#else
    channel = hal_lmdma_find_free_channel (LMDMA_BLOCKING);
#endif

    if (isr != NULL) {
        retval = hal_lmdma_register_isr (channel, LMDMA_CIE, isr);
        retval = hal_lmdma_register_isr (channel, LMDMA_EIE, isr);
    }

    retval =  hal_lmdma_copy32 (
        local_memory_address,
        external_memory_address,
        count,
        channel,
        LMDMA_TDIR_LM2EM
        );
    if (retval != 0) {
        return retval;
    }

    if (isr == NULL) {
        //
        // Polling Channel Status: Wait for the DMA transfer completion
        //
        do {
            status.Reg32 = hal_lmdma_get_status (channel);
        } while (status.Bits.STAT != LMDMA_STAT_Complete);

    #if (defined (CONFIG_OS_FREERTOS))
        OS_EnterCritical ();
        {
            gLMDMA_CHANNEL_ENABLE_BITMAP &= (~(1UL << channel));
        }
        OS_ExitCritical ();

        OsStatus = OS_SemSignal (gOsSemaphore);
        configASSERT (OsStatus != OS_FAILED);
    #endif
    }

    return 0;
}
