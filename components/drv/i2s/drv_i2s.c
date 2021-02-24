
#include "drv_i2s.h"
#if (CHIP_ID==6020)
#include "drv_pdm.h"
#include "hal_pdm.h"
#endif
#include "hal_dmac.h"
#include "attrs.h"
#include "soc_defs.h"
#include "osal.h"
#include "sys/intc.h"
#include <stdio.h>

//#define DMAC_TXBLOCK_MODE
#define DMAC_RXBLOCK_MODE

static i2s_buffer *sg_rx_buffer[DRV_I2S_MAX];
static int rx_buf_num[DRV_I2S_MAX] = {2};
static i2s_buffer *sg_tx_buffer[DRV_I2S_MAX];
static int tx_buf_num[DRV_I2S_MAX] = {2};
#if(CHIP_ID==6020)
typedef struct _i2s_lli{
#if defined (DMAC_TXBLOCK_MODE) || defined (DMAC_RXBLOCK_MODE) 
    uint32_t busy;
    uint32_t *cache;
    uint32_t backup;
#endif
    lli ll[DRV_I2S_MAX][MAX_BUF_NUM];
} i2s_lli;

static i2s_lli dma_rx;
static i2s_lli dma_tx;
static int dma_init_en = 0;
static int i2s_init_rate = 0;
static int i2s_ds_rate = 0;
static int i2s_rx_handler = 0;
#endif

static int rx_use[DRV_I2S_MAX] = {0};
static int tx_use[DRV_I2S_MAX] = {0};

typedef enum {
    DMA_TR_WAIT_STOP = -2,
    DMA_TR_BEGIN_STOP = -1,
    TR_STOP = 0,
    DMA_TR_RUN = 1,
    MCU_TR_RUN = 2,
} tr_status;

static int32_t check_chip_id(drv_i2s_port port)
{
    #if(CHIP_ID==6020)
        return DRV_I2S_STATUS_OK;
    #else
        if(port > DRV_I2S_0) {
            printf("6006 not support port: %d\n", port);
            return DRV_I2S_STATUS_ERROR;
        } else {
            return DRV_I2S_STATUS_OK;
        }
    #endif
}

static int check_i2s_port(
    drv_i2s_port port)
{
    if((port >= DRV_I2S_MAX) || (check_chip_id(port) < DRV_I2S_STATUS_OK)) {
        printf("i2s port number not support: %d\n", port);
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }
    
    return DRV_I2S_STATUS_OK;
}

static int check_data_handler(
    i2s_data_handler handler)
{
    if(handler >= MAX_HANDLER) {
        printf("i2s handler number not support: %d\n", handler);
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }

    return DRV_I2S_STATUS_OK;
}

#if(CHIP_ID==6020)

static int check_and_set_dma_rx_buf(
    drv_i2s_port port,
    int32_t *buf_num)
{
    uint32_t dma_buf_num = rx_buf_num[port], cnt = 0, check_len = 0;
    uint32_t dma_rx_addr = (uint32_t)I2S_RX_ADDR[port];

    if(port >= DRV_I2S_MAX) {
        printf("i2s port number not support: %d\n", port);
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }

    if(dma_buf_num > MAX_BUF_NUM) {
        printf("use rx buf number: %d max rx buf number: %d\n", dma_buf_num, MAX_BUF_NUM);
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }

    for(cnt = 0; cnt < dma_buf_num; cnt++) {
        check_len = (uint32_t)sg_rx_buffer[port]->ping_pong[0].buffer_len;
        if(sg_rx_buffer[port]->ping_pong[cnt].buffer == NULL) {
            printf("number: %d buffer is null, please alloc address\n", cnt);
            return DRV_I2S_STATUS_INVALID_PARAMETER;
        }
    }

    for(cnt = 0; cnt < dma_buf_num; cnt++) {
        dma_rx.ll[port][cnt].sar = dma_rx_addr;
        dma_rx.ll[port][cnt].dar = (uint32_t)sg_rx_buffer[port]->ping_pong[cnt].buffer;
        if(cnt == (dma_buf_num -1)) {
            dma_rx.ll[port][cnt].llp = (uint32_t)&dma_rx.ll[port][0];
        } else {
            dma_rx.ll[port][cnt].llp = (uint32_t)&dma_rx.ll[port][cnt+1];
        }
        if(check_len != (uint32_t)sg_rx_buffer[port]->ping_pong[cnt].buffer_len) {
            printf("dma rx buf need the same len, first buf len, %d buf len: %d\n",
                check_len,
                cnt,
                (uint32_t)sg_rx_buffer[port]->ping_pong[cnt].buffer_len);
            return DRV_I2S_STATUS_INVALID_PARAMETER;
        }
        dma_rx.ll[port][cnt].ctl2=  check_len;
    }
#ifdef DMAC_RXBLOCK_MODE
    dma_rx.cache= OS_MemAlloc(check_len);
    if(dma_rx.cache == NULL) {
        printf("dma rx cache alloc fail\n\n");
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }
    dma_rx.busy = 0;
#endif
    *buf_num = dma_buf_num;
    return (int)check_len;
}

static int check_and_set_dma_tx_buf(
    drv_i2s_port port,
    int32_t *buf_num)
{
    uint32_t dma_buf_num = tx_buf_num[port], cnt = 0, check_len = 0;
    uint32_t dma_tx_addr = (uint32_t)I2S_TX_ADDR[port];
    if(port >= DRV_I2S_MAX) {
        printf("i2s port number not support: %d\n", port);
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }
    
    if(dma_buf_num > MAX_BUF_NUM) {
        printf("use tx buf number: %d max tx buf number: %d\n", dma_buf_num, MAX_BUF_NUM);
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }

    for(cnt = 0; cnt < dma_buf_num; cnt++) {
        check_len = (uint32_t)sg_tx_buffer[port]->ping_pong[0].buffer_len;
        if(sg_tx_buffer[port]->ping_pong[cnt].buffer == NULL) {
            printf("number: %d buffer is null, please alloc address\n", cnt);
            return DRV_I2S_STATUS_INVALID_PARAMETER;
        }
    }
    
    for(cnt = 0; cnt < dma_buf_num; cnt++) {
        dma_tx.ll[port][cnt].sar = (uint32_t)sg_tx_buffer[port]->ping_pong[cnt].buffer;
        dma_tx.ll[port][cnt].dar = dma_tx_addr;
        if(cnt == (dma_buf_num -1)) {
            dma_tx.ll[port][cnt].llp = (uint32_t)&dma_tx.ll[port][0];
        } else {
            dma_tx.ll[port][cnt].llp = (uint32_t)&dma_tx.ll[port][cnt+1];
        }
        if(check_len != (uint32_t)sg_tx_buffer[port]->ping_pong[cnt].buffer_len) {
            printf("dma tx buf need the same len, first buf len, %d buf len: %d\n",
                check_len,
                cnt,
                (uint32_t)sg_tx_buffer[port]->ping_pong[cnt].buffer_len);
            return DRV_I2S_STATUS_INVALID_PARAMETER;
        }
        dma_tx.ll[port][cnt].ctl2=  check_len;
    }
#ifdef DMAC_TXBLOCK_MODE
    dma_tx.cache= OS_MemAlloc(check_len);
    if(dma_tx.cache == NULL) {
        printf("dma rx cache alloc fail\n\n");
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }
    dma_tx.busy = 0;
#endif
    *buf_num = dma_buf_num;
    return (int)check_len;
}
#endif
static void drv_i2s_mcu_stereo_tx_isr(uint32_t irq_num) ATTRIBUTE_SECTION_FAST;//release ilm;
static void drv_i2s_mcu_stereo_tx_isr(uint32_t irq_num) {

    int port = 0;
    if(irq_num == IRQ_I2S) {
        port = DRV_I2S_0;
    } else {
        port = DRV_I2S_1;
    }
    int push_buf_size = 0;
    int idx = sg_tx_buffer[port]->pingpong_idx;
    struct _i2s_buffer_st *buf = &(sg_tx_buffer[port]->ping_pong[idx]);
    if (!buf->data_ready) {
        sg_tx_buffer[port]->pingpong_idx = ((idx + 1) % tx_buf_num[port]);
        buf = &(sg_tx_buffer[port]->ping_pong[idx]);
        buf->buffer_idx = 0;
        if (!buf->data_ready) {
            sg_tx_buffer[port]->idle_cnt++;
            if (sg_tx_buffer[port]->event) {
                sg_tx_buffer[port]->event(I2S_NO_DATA, NULL);
            }
            if (sg_tx_buffer[port]->idle_cnt > 12000) {
                printf("idle too long, stop isr\n");
                intc_irq_disable(IRQ_I2S);
                if (sg_tx_buffer[port]->event) {
                    sg_tx_buffer[port]->event(I2S_DISABLE_ISR, NULL);
                }
            }
            #if(CHIP_ID==6020)
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            #else
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            #endif
            //while(1); // should turn off the i2s.
            goto NO_AUDIO;
        }
    }
    int i;
    int len = buf->buffer_len/2;
    for (i = 0; i < 4; i++) {
        if (buf->buffer_idx < (len)) {
            #if(CHIP_ID==6020)
            hal_i2s_tx(HAL_I2S_0, buf->buffer[buf->buffer_idx]);
            hal_i2s_tx(HAL_I2S_0, buf->buffer[buf->buffer_idx+1]);
            #else
            hal_i2s_tx(buf->buffer[buf->buffer_idx]);
            hal_i2s_tx(buf->buffer[buf->buffer_idx+1]);
            #endif
            if (sg_tx_buffer[port]->dup_sample > sg_tx_buffer[port]->i2s_dup_sample_idx) {
                sg_tx_buffer[port]->i2s_dup_sample_idx++;
            } else {
                buf->buffer_idx += 2;
                sg_tx_buffer[port]->i2s_dup_sample_idx = 0;
            }
        } else {
            buf->data_ready = 0; // not data available.
            buf->buffer_idx = 0;
            sg_tx_buffer[port]->pingpong_idx = ((idx + 1) % tx_buf_num[port]);
            break;
        }
    }
NO_AUDIO:
    intc_irq_clean(IRQ_I2S);
}

static void drv_i2s_mcu_mono_tx_isr(uint32_t irq_num) ATTRIBUTE_SECTION_FAST;//release ilm
static void drv_i2s_mcu_mono_tx_isr(uint32_t irq_num) {
#if defined(GPIO_DEBUG)
    drv_gpio_set_logic(GPIO_11, GPIO_LOGIC_HIGH);
    HW_IO_REG->IO_PO |= (0x1 << 11);
#endif
    int port = 0;
    if(irq_num == IRQ_I2S) {
        port = DRV_I2S_0;
    } else {
        port = DRV_I2S_1;
    }
    int push_buf_size = 0;
    int idx = sg_tx_buffer[port]->pingpong_idx;
    struct _i2s_buffer_st *buf = &(sg_tx_buffer[port]->ping_pong[idx]);
    if (!buf->data_ready) {
        sg_tx_buffer[port]->pingpong_idx = ((idx + 1) % tx_buf_num[port]);
        buf = &(sg_tx_buffer[port]->ping_pong[idx]);
        buf->buffer_idx = 0;
        if (!buf->data_ready) {
            sg_tx_buffer[port]->idle_cnt++;
            if (sg_tx_buffer[port]->event) {
                sg_tx_buffer[port]->event(I2S_NO_DATA, NULL);
            }
            if (sg_tx_buffer[port]->idle_cnt > 12000) {
                printf("idle too long, stop isr\n");
                if (sg_tx_buffer[port]->event) {
                    sg_tx_buffer[port]->event(I2S_DISABLE_ISR, NULL);
                }
                intc_irq_disable(IRQ_I2S);
            }
            //while(1); // should turn off the i2s.
            #if(CHIP_ID==6020)
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            hal_i2s_tx(HAL_I2S_0, 0);
            #else
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            hal_i2s_tx(0);
            #endif
            goto NO_AUDIO;
        }
    }
    int i;
    int len = buf->buffer_len/2;
    for (i = 0; i < 4; i++) {
        if (buf->buffer_idx < (len)) {
            #if(CHIP_ID==6020)
            hal_i2s_tx(HAL_I2S_0, buf->buffer[buf->buffer_idx]);
            hal_i2s_tx(HAL_I2S_0, buf->buffer[buf->buffer_idx]);
            #else
            hal_i2s_tx(buf->buffer[buf->buffer_idx]);
            hal_i2s_tx(buf->buffer[buf->buffer_idx]);
            #endif
            if (sg_tx_buffer[port]->dup_sample > sg_tx_buffer[port]->i2s_dup_sample_idx) {
                sg_tx_buffer[port]->i2s_dup_sample_idx++;
            } else {
                buf->buffer_idx += 1;
                sg_tx_buffer[port]->i2s_dup_sample_idx = 0;
            }
        } else {
            buf->data_ready = 0; // not data available.
            buf->buffer_idx = 0;
            sg_tx_buffer[port]->pingpong_idx = ((idx + 1) % tx_buf_num[port]);
            break;
        }
    }
NO_AUDIO:
    intc_irq_clean(IRQ_I2S);
#if defined(GPIO_DEBUG)
    HW_IO_REG->IO_PO &= ~(0x1 << 11);
    drv_gpio_set_logic(GPIO_11, GPIO_LOGIC_LOW);
#endif
}

static void drv_i2s_mcu_tx_start(
    drv_i2s_port port)
{
    if(sg_tx_buffer[port]->pingpong_idx > 2) {
        printf("if use mcu mode, use_buf_num only set 2\n");
    }

    if(port == DRV_I2S_0) {
        if (sg_tx_buffer[DRV_I2S_0]->stereo) {
            intc_register_isr(IRQ_I2S, drv_i2s_mcu_stereo_tx_isr);
        } else {
            //intc_register_isr(IRQ_I2S, drv_i2s_mcu_mono_tx_isr); //release ilm
        }
        intc_irq_enable(IRQ_I2S);
        intc_irq_set_priority(IRQ_I2S, 0);
    } else if(port == DRV_I2S_1) {
#if 0//irq so fast, task can not run
#if(CHIP_ID==6020)
         if(hal_get_pdm_rx_ch_enable_status(port) == true) {
            printf("pdm i2s2 not support tx\n");
            return;
        }
#endif
        if (sg_tx_buffer[DRV_I2S_1]->buf.stereo) {
            intc_group02_irq_enable(0x7, drv_i2s_mcu_stereo_tx_isr);
        } else {
            //intc_group02_irq_enable(0x7, drv_i2s_mcu_mono_tx_isr); //release ilm
        }
#else
        printf("tx mcu mode not support DRV_I2S_1\n");
#endif
    }
    tx_use[port] = MCU_TR_RUN;
}

static void drv_i2s_mcu_tx_stop(
    drv_i2s_port port) 
{
    #if(CHIP_ID==6020)
    hal_i2s_tx_disable(port);
    #else
    hal_i2s_tx_disable();
    #endif
    tx_use[port] = TR_STOP;
}

#if(CHIP_ID==6020)
#ifdef DMAC_TXBLOCK_MODE
static void drv_i2s_dma_tx_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type) ATTRIBUTE_SECTION_FAST;

static void drv_i2s_dma_tx_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type)
{
    drv_i2s_port port = DRV_I2S_MAX;
    if(ch == DMAC_CH_1) {
        port = DRV_I2S_0;
    } else if(ch == DMAC_CH_9) {
        port = DRV_I2S_1;
    } else {
        printf("i2s dma tx channel(%d) not use, please check\n", ch);
        return;
    }

    int32_t buf_num = tx_buf_num[port];
    int32_t now  = sg_tx_buffer[port]->pingpong_idx;
    int32_t next  =  (now + 1) % buf_num;

    sg_tx_buffer[port]->idle_cnt++;
    if(tx_use[port] == DMA_TR_RUN) {
        if(dma_tx.busy == 1) {
            if(sg_tx_buffer[port]->ping_pong[now].data_ready == 1) {
                dma_tx.ll[port][now].sar = (uint32_t)dma_tx.backup;
                dma_tx.ll[port][now].dar= dma_tx.ll[port][next].dar;
                dma_tx.ll[port][now].llp =  (uint32_t)&dma_tx.ll[port][next];
                dma_tx.busy = 0;
                //printf("tx free\n");
            }
            dma_tx.ll[port][now].ctl2 &= 0x0fff;
        } else
        {
            if((dma_tx.ll[port][now].ctl2&0x1000) == 0x1000) {
                if(sg_tx_buffer[port]->ping_pong[now].data_ready == 1) {
                    sg_tx_buffer[port]->ping_pong[now].data_ready = 0;
                    sg_tx_buffer[port]->idle_cnt = 0;
                    dma_tx.ll[port][now].ctl2 &= 0x0fff;
                    sg_tx_buffer[port]->pingpong_idx = next;
                    if(sg_tx_buffer[port]->ping_pong[next].data_ready == 0) {
                       if (sg_tx_buffer[port]->event) {
                            sg_tx_buffer[port]->event(I2S_NO_DATA, NULL);
                        }
                        dma_tx.backup= dma_tx.ll[port][next].sar;
                        dma_tx.ll[port][next].sar = dma_tx.ll[port][now].sar;
                        dma_tx.ll[port][next].dar= (uint32_t)dma_tx.cache;
                        dma_tx.ll[port][next].llp = (uint32_t)&dma_tx.ll[port][next];
                        dma_tx.busy = 1;
                        printf("tx busy\n");
                    }
                } else {
                    printf("tx ready not match: (%d)\n", now);
                }
            } else {
                printf("dma tx ring buf not match: (%d)\n", now);
            }
        }
    } else {
        if(tx_use[port] == DMA_TR_BEGIN_STOP) {
            hal_dmac_dst_auto_reload_disable(ch);
            for(now = 0; now < buf_num; now++) {
                dma_tx.ll[port][now].llp = 0;
            }
            tx_use[port] = DMA_TR_WAIT_STOP;
        } else if(tx_use[port] == DMA_TR_WAIT_STOP) {
            hal_i2s_tx_disable(port);
            dma_tx.busy = 0;
            OS_MemFree((void *)dma_tx.cache);
            for(now = 0; now < buf_num; now++) {
                sg_tx_buffer[port]->ping_pong[now].data_ready = 0;
            }
            tx_use[port] = TR_STOP;
        } else if(tx_use[port] == TR_STOP) {
            printf("unknown tx isr:%d\n", tx_use[port]);
        }
        sg_tx_buffer[port]->idle_cnt = 0x0;
    }
    hal_dmac_clear_int_status(ch, int_type);
}
#else
static void drv_i2s_dma_tx_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type) ATTRIBUTE_SECTION_FAST;

static void drv_i2s_dma_tx_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type)
{
    drv_i2s_port port = DRV_I2S_MAX;
    if(ch == DMAC_CH_1) {
        port = DRV_I2S_0;
    } else if(ch == DMAC_CH_9) {
        port = DRV_I2S_1;
    } else {
        printf("i2s dma tx channel(%d) not use, please check\n", ch);
        return;
    }

    int32_t buf_num = tx_buf_num[port];
    int32_t now  = sg_tx_buffer[port]->pingpong_idx;
    int32_t next  =  (now + 1) % buf_num;
    sg_tx_buffer[port]->idle_cnt = 0x0;

    if(tx_use[port] == DMA_TR_RUN) {
        for(now = 0; now < buf_num; now++) {
            if((dma_tx.ll[port][now].ctl2&0x1000) == 0x1000) {
                dma_tx.ll[port][now].ctl2 &= 0x0fff;
                if(sg_tx_buffer[port]->ping_pong[now].data_ready == 1) {
                    sg_tx_buffer[port]->ping_pong[now].data_ready = 0;
                } else {
                   if (sg_tx_buffer[port]->event) {
                        sg_tx_buffer[port]->event(I2S_NO_DATA, NULL);
                    }
                    printf("tx empty: %d\n", now);
                }
            }
        }
    } else if(tx_use[port] == DMA_TR_BEGIN_STOP) {
        for(now = 0; now < buf_num; now++) {
            dma_tx.ll[port][now].llp = 0;
        }
        tx_use[port] = DMA_TR_WAIT_STOP;
    } else if(tx_use[port] == DMA_TR_WAIT_STOP) {
        for(now = 0; now < buf_num; now++) {
            sg_tx_buffer[port]->ping_pong[now].data_ready = 0;
        }
        if(hal_dmac_get_channel_status(ch) == HAL_DMAC_STATUS_OK) {
            printf("tx already exit\n");
            hal_i2s_tx_disable(port);
            tx_use[port] = TR_STOP;
        }
    } else {
        printf("unknown tx isr:%d\n", tx_use[port]);
    }

    sg_tx_buffer[port]->pingpong_idx = next;
    hal_dmac_clear_int_status(ch, int_type);
}
#endif

static void drv_i2s_dma_tx_run(
    drv_i2s_port port,
    uint8_t *tx_data,
    uint32_t byte_size,
    DMAC_ISR tx_done_isr,
    lli *lli_addr,
    int lli_num)
{
    DMAC_CH_E ch =HAL_DMAC_CH_NOT_FOUND;
    DMAC_PER_E per = DMAC_HW_HS_IF_I2S_TX;
    uint8_t dma_size = 0x0;
    uint32_t dma_2_byte_cnt = 0x0;
    dma_size = DMAC_MSIZE_1;
    uint32_t cnt = 0;
    uint32_t dma_buf_num = tx_buf_num[port];
    
    dma_2_byte_cnt = (byte_size >> 1);
    for(cnt = 0; cnt < dma_buf_num; cnt++) {
        dma_tx.ll[port][cnt].ctl2=  dma_2_byte_cnt;
    }

    if(port == DRV_I2S_0) {
        ch = DMAC_CH_1;
        per = DMAC_HW_HS_IF_I2S_TX;
    } else if(port == DRV_I2S_1) {
        ch = DMAC_CH_9;
        per = DMAC_HW_HS_IF_I2S1_TX;
    }

    hal_dmac_register_isr(ch, DMAC_INT_TYPE_Block, tx_done_isr);
    hal_dmac_src_llp_enable(ch);
#ifdef DMAC_TXBLOCK_MODE
    hal_dmac_dst_auto_reload_enable(ch);
#endif

    //TX - Used Channel 1 or Channel 9
    hal_dmac_start_lli(
        (void *)I2S_TX_ADDR[port],
        (void *) tx_data,
        dma_2_byte_cnt,
        ch,
        DMAC_TR_WIDTH_16,
        DMAC_TR_WIDTH_16,
        DMAC_ADDR_NO_CHANGE,
        DMAC_ADDR_INCREMENT,
        dma_size,
        dma_size,
        DMAC_TT_FC_M2P_Dma,
        DMAC_CH_PRIOR_1,
        DMAC_HS_SEL_HARDWARE,
        per,
        DMAC_HS_SEL_SOFTWARE,
        0,
        lli_addr,
        lli_num
    );
}

static int drv_i2s_dma_tx_start(
    drv_i2s_port port)
{
    int32_t buf_len = 0, buf_num = 0;

    buf_len = check_and_set_dma_tx_buf(port, &buf_num);
    if(buf_len > 0) {
        printf("tx buf_len: %d buf_num: %d\n", buf_len, buf_num);
        drv_i2s_dma_tx_run(port, (uint8_t *)dma_tx.ll, buf_len, drv_i2s_dma_tx_isr, (lli *)(dma_tx.ll[port]), buf_num);
        tx_use[port] = DMA_TR_RUN;
        return DRV_I2S_STATUS_OK;
    }
    return DRV_I2S_STATUS_ERROR;
}

static void drv_i2s_dma_tx_stop(
    drv_i2s_port port)
{
    int cnt = 0;
    tx_use[port] = DMA_TR_BEGIN_STOP;
    while((tx_use[port] != TR_STOP)) {
        cnt++;
        OS_MsDelay(1);
        if(cnt >= 1000) {
            printf("i2s tx stop timeout\n");
            break;
        }
    }
}
#endif

#if(CHIP_ID==6020)
//static void drv_i2s2_mcu_rx_isr() ATTRIBUTE_SECTION_FAST;//release ilm
static void drv_i2s2_mcu_rx_isr() {
    int push_buf_size = 0;
    int trash = 0;
    int idx = sg_rx_buffer[DRV_I2S_1]->pingpong_idx;
    struct _i2s_buffer_st *buf = &(sg_rx_buffer[DRV_I2S_1]->ping_pong[idx]);
    if (buf->data_ready) {
        sg_rx_buffer[DRV_I2S_1]->pingpong_idx = ((idx + 1) % rx_buf_num[1]);
        buf = &(sg_rx_buffer[DRV_I2S_1]->ping_pong[idx]);
        if (buf->data_ready) {
            trash = hal_i2s_rx(HAL_I2S_1);
            trash = hal_i2s_rx(HAL_I2S_1);
            trash = hal_i2s_rx(HAL_I2S_1);
            trash = hal_i2s_rx(HAL_I2S_1);
            trash = hal_i2s_rx(HAL_I2S_1);
            trash = hal_i2s_rx(HAL_I2S_1);
            trash = hal_i2s_rx(HAL_I2S_1);
            trash = hal_i2s_rx(HAL_I2S_1);

            hal_i2s_tx(HAL_I2S_1, trash);
            hal_i2s_tx(HAL_I2S_1, trash);
            hal_i2s_tx(HAL_I2S_1, trash);
            hal_i2s_tx(HAL_I2S_1, trash);
            hal_i2s_tx(HAL_I2S_1, trash);
            hal_i2s_tx(HAL_I2S_1, trash);
            hal_i2s_tx(HAL_I2S_1, trash);
            hal_i2s_tx(HAL_I2S_1, trash);
            sg_rx_buffer[DRV_I2S_1]->idle_cnt++;
            if (sg_rx_buffer[DRV_I2S_1]->event) {
                sg_rx_buffer[DRV_I2S_1]->event(I2S_BUFFER_FULL, NULL);
            }
            if (sg_rx_buffer[DRV_I2S_1]->idle_cnt > 12000) {
                printf("idle too long\n");
                sg_rx_buffer[DRV_I2S_1]->idle_cnt = 0;
            }
            goto BUF_FULL;
        }
    }
    int i;
    for (i = 0; i < 4; i++) {
        trash = hal_i2s_rx(HAL_I2S_1);
        trash = hal_i2s_rx(HAL_I2S_1);

        hal_i2s_tx(HAL_I2S_1, trash); // loopback
        hal_i2s_tx(HAL_I2S_1, trash);

        if (sg_rx_buffer[DRV_I2S_1]->dup_sample > sg_rx_buffer[DRV_I2S_1]->i2s_dup_sample_idx) {
            sg_rx_buffer[DRV_I2S_1]->i2s_dup_sample_idx++;
        } else {
            sg_rx_buffer[DRV_I2S_1]->i2s_dup_sample_idx = 0;
            buf->buffer[buf->buffer_idx++] = trash;
            if (buf->buffer_len/2 == buf->buffer_idx) {
                buf->data_ready = 1;
                buf->buffer_idx = 0;
                sg_rx_buffer[DRV_I2S_1]->pingpong_idx = ((sg_rx_buffer[DRV_I2S_1]->pingpong_idx + 1) % rx_buf_num[1]);
                break;
            }
        }
    }
BUF_FULL:
    intc_irq_clean(IRQ_I2S);
}
#endif

static void drv_i2s1_mcu_rx_isr(uint32_t irq_num) ATTRIBUTE_SECTION_FAST;//release ilm
static void drv_i2s1_mcu_rx_isr(uint32_t irq_num) {
    int push_buf_size = 0;
    int trash = 0;
    int idx = sg_rx_buffer[DRV_I2S_0]->pingpong_idx;
    struct _i2s_buffer_st *buf = &(sg_rx_buffer[DRV_I2S_0]->ping_pong[idx]);
    if (buf->data_ready) {
        sg_rx_buffer[DRV_I2S_0]->pingpong_idx = ((idx + 1) % rx_buf_num[0]);
        buf = &(sg_rx_buffer[DRV_I2S_0]->ping_pong[idx]);
        if (buf->data_ready) {
            #if(CHIP_ID==6020)
            trash = hal_i2s_rx(HAL_I2S_0);
            trash = hal_i2s_rx(HAL_I2S_0);
            trash = hal_i2s_rx(HAL_I2S_0);
            trash = hal_i2s_rx(HAL_I2S_0);
            trash = hal_i2s_rx(HAL_I2S_0);
            trash = hal_i2s_rx(HAL_I2S_0);
            trash = hal_i2s_rx(HAL_I2S_0);
            trash = hal_i2s_rx(HAL_I2S_0);

            hal_i2s_tx(HAL_I2S_0, trash);
            hal_i2s_tx(HAL_I2S_0, trash);
            hal_i2s_tx(HAL_I2S_0, trash);
            hal_i2s_tx(HAL_I2S_0, trash);
            hal_i2s_tx(HAL_I2S_0, trash);
            hal_i2s_tx(HAL_I2S_0, trash);
            hal_i2s_tx(HAL_I2S_0, trash);
            hal_i2s_tx(HAL_I2S_0, trash);
            #else
            trash = hal_i2s_rx();
            trash = hal_i2s_rx();
            trash = hal_i2s_rx();
            trash = hal_i2s_rx();
            trash = hal_i2s_rx();
            trash = hal_i2s_rx();
            trash = hal_i2s_rx();
            trash = hal_i2s_rx();

            hal_i2s_tx(trash);
            hal_i2s_tx(trash);
            hal_i2s_tx(trash);
            hal_i2s_tx(trash);
            hal_i2s_tx(trash);
            hal_i2s_tx(trash);
            hal_i2s_tx(trash);
            hal_i2s_tx(trash);
            #endif
            sg_rx_buffer[DRV_I2S_0]->idle_cnt++;
            if (sg_rx_buffer[DRV_I2S_0]->event) {
                sg_rx_buffer[DRV_I2S_0]->event(I2S_BUFFER_FULL, NULL);
            }
            if (sg_rx_buffer[DRV_I2S_0]->idle_cnt > 12000) {
                printf("idle too long\n");
                sg_rx_buffer[DRV_I2S_0]->idle_cnt = 0;
            }
            goto BUF_FULL;
        }
    }
    int i;
    for (i = 0; i < 4; i++) {
        #if(CHIP_ID==6020)
        trash = hal_i2s_rx(HAL_I2S_0);
        trash = hal_i2s_rx(HAL_I2S_0);

        hal_i2s_tx(HAL_I2S_0, trash); // loopback
        hal_i2s_tx(HAL_I2S_0, trash);
        #else
        trash = hal_i2s_rx();
        trash = hal_i2s_rx();

        hal_i2s_tx(trash); // loopback
        hal_i2s_tx(trash);
        #endif
        if (sg_rx_buffer[DRV_I2S_0]->dup_sample > sg_rx_buffer[DRV_I2S_0]->i2s_dup_sample_idx) {
            sg_rx_buffer[DRV_I2S_0]->i2s_dup_sample_idx++;
        } else {
            sg_rx_buffer[DRV_I2S_0]->i2s_dup_sample_idx = 0;
            buf->buffer[buf->buffer_idx++] = trash;
            if (buf->buffer_len/2 == buf->buffer_idx) {
                buf->data_ready = 1;
                buf->buffer_idx = 0;
                
                sg_rx_buffer[DRV_I2S_0]->pingpong_idx = ((sg_rx_buffer[DRV_I2S_0]->pingpong_idx + 1) % rx_buf_num[0]);
                break;
            }
        }
    }
BUF_FULL:
    intc_irq_clean(IRQ_I2S);
}

static void drv_i2s_mcu_rx_start(
    drv_i2s_port port) 
{
#if(CHIP_ID==6020)
    if(port == DRV_I2S_0) {
        intc_register_isr(IRQ_I2S, drv_i2s1_mcu_rx_isr);
        intc_irq_enable(IRQ_I2S);
        intc_irq_set_priority(IRQ_I2S, 0);
    } else if(port == DRV_I2S_1) {
        //intc_group02_irq_enable(0x7, drv_i2s2_mcu_rx_isr);
    }
#else
        intc_register_isr(IRQ_I2S, drv_i2s1_mcu_rx_isr);
        intc_irq_enable(IRQ_I2S);
        intc_irq_set_priority(IRQ_I2S, 0);
#endif
    rx_use[port] = MCU_TR_RUN;
}

static void drv_i2s_mcu_rx_stop(
    drv_i2s_port port)
{
    #if(CHIP_ID==6020)
    hal_i2s_rx_disable(port);
    #else
    hal_i2s_rx_disable();
    #endif
    if(port == DRV_I2S_0) {
        intc_irq_disable(IRQ_I2S);
    } else if(port == DRV_I2S_1) {
        intc_group02_irq_disable(0x7);
    }
    rx_use[port] = TR_STOP;
}
#if(CHIP_ID==6020)
#ifdef DMAC_RXBLOCK_MODE
static void drv_i2s_dma_rx_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type) ATTRIBUTE_SECTION_FAST;

static void drv_i2s_dma_rx_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type) 
{
    int i = 0;
    drv_i2s_port port = DRV_I2S_MAX;
    if(ch == DMAC_CH_0) {
        port = DRV_I2S_0;
    } else if(ch == DMAC_CH_8) {
        port = DRV_I2S_1;
    } else {
        printf("i2s dma rx channel(%d) not use, please check\n", port);
        return;
    }
    int32_t buf_num = rx_buf_num[port];
    int32_t now = sg_rx_buffer[port]->pingpong_idx;
    int32_t next = (now + 1) % buf_num;

    sg_rx_buffer[port]->idle_cnt++;
    if(rx_use[port] == DMA_TR_RUN) {
        if(dma_rx.busy == 1) {
            if(sg_rx_buffer[port]->ping_pong[now].data_ready == 0) {
                dma_rx.ll[port][now].dar = (uint32_t)dma_rx.backup;
                dma_rx.ll[port][now].llp =  (uint32_t)&dma_rx.ll[port][next];
                dma_rx.busy = 0;
                //printf("clear full\n");
            }
            dma_rx.ll[port][now].ctl2 &= 0x0fff;
        } else
        {
            if((dma_rx.ll[port][now].ctl2&0x1000) == 0x1000) {
                if(sg_rx_buffer[port]->ping_pong[now].data_ready == 0) {
                    sg_rx_buffer[port]->ping_pong[now].data_ready = 1;
                    sg_rx_buffer[port]->idle_cnt = 0;
                    dma_rx.ll[port][now].ctl2 &= 0x0fff;
                    sg_rx_buffer[port]->pingpong_idx = next;
                    //check next buf is free
                    if(sg_rx_buffer[port]->ping_pong[next].data_ready == 1) {
                       if (sg_rx_buffer[port]->event) {
                            sg_rx_buffer[port]->event(I2S_BUFFER_FULL, NULL);
                        }
                        dma_rx.backup= dma_rx.ll[port][next].dar;
                        dma_rx.ll[port][next].dar = (uint32_t)dma_rx.cache;
                        dma_rx.ll[port][next].llp = (uint32_t)&dma_rx.ll[port][next];
                        dma_rx.busy = 1;
                        printf("r\n");
                    }
                } else {
                    printf("rx ready not match: (%d)\n", now);
                }
            } else {
                printf("dma rx ring buf not match\n");
            }
        }
    } else {
        if(rx_use[port] == DMA_TR_BEGIN_STOP) {
            hal_dmac_src_auto_reload_disable(ch);
            for(now = 0; now < buf_num; now++) {
                dma_rx.ll[port][now].llp = 0;
            }  
            rx_use[port] = DMA_TR_WAIT_STOP;
        } else if(rx_use[port] == DMA_TR_WAIT_STOP) {
            hal_i2s_rx_disable(port);       
            dma_rx.busy = 0;
            OS_MemFree((void *)dma_rx.cache);
            rx_use[port] = TR_STOP;
        } else {
            printf("unknown rx isr:%d\n", rx_use[port]);
        }
        sg_rx_buffer[port]->idle_cnt = 0x0;
    }
    hal_dmac_clear_int_status(ch, int_type);
}
#else
static void drv_i2s_dma_rx_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type) ATTRIBUTE_SECTION_FAST;

static void drv_i2s_dma_rx_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type) 
{
    int i = 0;
    drv_i2s_port port = DRV_I2S_MAX;
    if(ch == DMAC_CH_0) {
        port = DRV_I2S_0;
    } else if(ch == DMAC_CH_8) {
        port = DRV_I2S_1;
    } else {
        printf("i2s dma rx channel(%d) not use, please check\n", port);
        return;
    }

    int32_t check = 0;
    int32_t buf_num = rx_buf_num[port];
    int32_t now = sg_rx_buffer[port]->pingpong_idx;
    int32_t next = (now + 1) % buf_num;
    sg_rx_buffer[port]->idle_cnt = 0x0;

    if(rx_use[port] == DMA_TR_RUN) {
        for(now = 0; now < buf_num; now++) {
            if((dma_rx.ll[port][now].ctl2&0x1000) == 0x1000) {
                dma_rx.ll[port][now].ctl2 &= 0x0fff;
                if(sg_rx_buffer[port]->ping_pong[now].data_ready == 0) {
                    sg_rx_buffer[port]->ping_pong[now].data_ready = 1;
                } else {
                   if (sg_rx_buffer[port]->event) {
                        sg_rx_buffer[port]->event(I2S_BUFFER_FULL, NULL);
                    }
                    printf("rx busy, maybe overwrite: %d\n", now);
                    check = 1;
                }
            }
        }
        if(check == 1) {
            printf("#\n");
        }
    } else if(rx_use[port] == DMA_TR_BEGIN_STOP) {
        for(now = 0; now < buf_num; now++) {
            dma_rx.ll[port][now].llp = 0;
        }
        rx_use[port] = DMA_TR_WAIT_STOP;
    } else if(rx_use[port] == DMA_TR_WAIT_STOP) {
        for(now = 0; now < buf_num; now++) {
            sg_rx_buffer[port]->ping_pong[now].data_ready = 0;
        }
        if(hal_dmac_get_channel_status(ch) == HAL_DMAC_STATUS_OK) {
            printf("rx already exit\n");
            rx_use[port] = TR_STOP;
            hal_i2s_rx_disable(port);
        }
    } else {
        printf("unknown rx isr:%d\n", rx_use[port]);
    }

    sg_rx_buffer[port]->pingpong_idx = next;
    hal_dmac_clear_int_status(ch, int_type);
}
#endif

static void drv_i2s_dma_rx_run(
    drv_i2s_port port,
    uint8_t *rx_data,
    uint32_t byte_size,
    DMAC_ISR rx_done_isr,
    lli *lli_addr,
    int lli_num) 
{
    DMAC_CH_E ch =HAL_DMAC_CH_NOT_FOUND;
    DMAC_PER_E per = DMAC_HW_HS_IF_I2S_RX;
    DMAC_TR_WIDTH_E width = DMAC_TR_WIDTH_16;
    uint8_t dma_size = 0x0;
    uint32_t cnt = 0;
    uint32_t dma_byte_cnt = (byte_size >> 1);
    uint32_t dma_buf_num = rx_buf_num[port];

    dma_size = DMAC_MSIZE_1;
    if(hal_get_pdm_rx_ch_enable_status(port) == true) {
        if (sg_rx_buffer[port]->stereo) {
            dma_byte_cnt = (byte_size >> 2);
            width = DMAC_TR_WIDTH_32;
        }
    }

    for(cnt = 0; cnt < dma_buf_num; cnt++) {
        dma_rx.ll[port][cnt].ctl2=  dma_byte_cnt;
    }

    if(port == DRV_I2S_0) {
        ch = DMAC_CH_0;
        per = DMAC_HW_HS_IF_I2S_RX;
    } else if(port == DRV_I2S_1) {
        ch = DMAC_CH_8;
        per = DMAC_HW_HS_IF_I2S1_RX;
    }
    hal_dmac_register_isr(ch, DMAC_INT_TYPE_Block, rx_done_isr);
    hal_dmac_dst_llp_enable(ch);
#ifdef DMAC_RXBLOCK_MODE
    hal_dmac_src_auto_reload_enable(ch);
#endif
    //TX - Used Channel 0 or Channel 8
    hal_dmac_start_lli(
        (void *) rx_data,
        (void *) I2S_RX_ADDR[port],
        dma_byte_cnt,
        ch,
        width,
        width,
        DMAC_ADDR_INCREMENT,
        DMAC_ADDR_NO_CHANGE,
        dma_size,
        dma_size,
        DMAC_TT_FC_P2M_Dma,
        DMAC_CH_PRIOR_7,
        DMAC_HS_SEL_SOFTWARE,
        0,
        DMAC_HS_SEL_HARDWARE,
        per,
        lli_addr,
        lli_num
    );
}

static int drv_i2s_dma_rx_start(
    drv_i2s_port port) 
{
    int32_t buf_len = 0, buf_num = 0;

    buf_len = check_and_set_dma_rx_buf(port, &buf_num);
    if(buf_len > 0) {
        printf("rx buf_len: %d buf_num: %d\n", buf_len, buf_num);
        drv_i2s_dma_rx_run(port, (uint8_t *)dma_rx.ll, buf_len, drv_i2s_dma_rx_isr, (lli *)(dma_rx.ll[port]), buf_num);
        rx_use[port] = DMA_TR_RUN;
        return DRV_I2S_STATUS_OK;
    }
    return DRV_I2S_STATUS_ERROR;
}

static void drv_i2s_dma_rx_stop(
    drv_i2s_port port)
{
    int cnt = 0;
    rx_use[port] = DMA_TR_BEGIN_STOP;
    while((rx_use[port] != TR_STOP)) {
        cnt++;
        OS_MsDelay(1);
        if(cnt >= 1000) {
            printf("i2s tx stop timeout\n");
            break;
        }
    }
}
#endif

//static void drv_i2s_loopback_mcu_trx_isr(uint32_t irq_num) ATTRIBUTE_SECTION_FAST;//release ilm
static void drv_i2s_loopback_mcu_trx_isr(uint32_t irq_num) 
{
#if(CHIP_ID==6020)
    int port = 0;
    if(irq_num == IRQ_I2S) {
        port = DRV_I2S_0;
    } else {
        port = DRV_I2S_1;
    }
    if(hal_get_pdm_rx_ch_enable_status(port) == true) {
        uint32_t data = hal_i2s_rx(port);
        hal_i2s_tx(port, (data &0xfffff));
        hal_i2s_tx(port, ((data >> 16)&0xfffff));
        data = hal_i2s_rx(port);
        hal_i2s_tx(port, data &0xfffff);
        hal_i2s_tx(port, ((data >> 16)&0xfffff));
        data = hal_i2s_rx(port);
        hal_i2s_tx(port, data &0xfffff);
        hal_i2s_tx(port, ((data >> 16)&0xfffff));
        data = hal_i2s_rx(port);
        hal_i2s_tx(port, data &0xfffff);
        hal_i2s_tx(port, ((data >> 16)&0xfffff));
    } else {
        hal_i2s_tx(port, hal_i2s_rx(port));
        hal_i2s_tx(port, hal_i2s_rx(port));
        hal_i2s_tx(port, hal_i2s_rx(port));
        hal_i2s_tx(port, hal_i2s_rx(port));
        hal_i2s_tx(port, hal_i2s_rx(port));
        hal_i2s_tx(port, hal_i2s_rx(port));
        hal_i2s_tx(port, hal_i2s_rx(port));
        hal_i2s_tx(port, hal_i2s_rx(port));
    }
    if(port == DRV_I2S_0)
        intc_irq_clean(IRQ_I2S);
#else
    hal_i2s_tx(hal_i2s_rx());
    hal_i2s_tx(hal_i2s_rx());
    hal_i2s_tx(hal_i2s_rx());
    hal_i2s_tx(hal_i2s_rx());
    hal_i2s_tx(hal_i2s_rx());
    hal_i2s_tx(hal_i2s_rx());
    hal_i2s_tx(hal_i2s_rx());
    hal_i2s_tx(hal_i2s_rx());
    intc_irq_clean(IRQ_I2S);
#endif
}

static void drv_i2s_loopback_mcu_trx_start(
    drv_i2s_port port)
{
    if(port == DRV_I2S_0) {
        intc_register_isr(IRQ_I2S, drv_i2s_loopback_mcu_trx_isr);
        intc_irq_enable(IRQ_I2S);
        intc_irq_set_priority(IRQ_I2S, 0);
    } else if(port == DRV_I2S_1) {
#if(CHIP_ID==6020)
        if(hal_get_pdm_rx_ch_enable_status(port) == true) {
            printf("pdm i2s2 not support loopback\n");
        }
#endif
        intc_group02_irq_enable(0x7, drv_i2s_loopback_mcu_trx_isr);
    }
    rx_use[port] = tx_use[port] = MCU_TR_RUN;
}

static void drv_i2s_loopback_mcu_trx_stop(
    drv_i2s_port port)
{
    #if(CHIP_ID==6020)
    hal_i2s_tx_disable(port);
    hal_i2s_rx_disable(port);
    #else
    hal_i2s_tx_disable();
    hal_i2s_rx_disable();
    #endif
    if(port == DRV_I2S_0) {
        intc_irq_disable(IRQ_I2S);
    } else if(port == DRV_I2S_1) {
        intc_group02_irq_disable(0x7);
    }
    rx_use[port] = tx_use[port] = TR_STOP;
}

#if(CHIP_ID==6020)

static void drv_i2s_loopback_dma_trx_isr(
    DMAC_CH_E ch,
    DMAC_INT_TYPE_E int_type) 
{
    drv_i2s_port port = DRV_I2S_MAX;
    if(ch == DMAC_CH_1) {
        port = DRV_I2S_0;
    } else if(ch == DMAC_CH_9) {
        port = DRV_I2S_1;
    } else {
        printf("i2s dma tx channel(%d) not use, please check\n", ch);
        return;
    }

    if(tx_use[port] == DMA_TR_BEGIN_STOP) {
        hal_dmac_dst_auto_reload_disable(ch);
        tx_use[port] = rx_use[port] =DMA_TR_WAIT_STOP;
    } else if(tx_use[port] == DMA_TR_WAIT_STOP) {
        hal_i2s_rx_disable(port);
        hal_i2s_tx_disable(port);
        tx_use[port] = rx_use[port] = TR_STOP;
    } else if(tx_use[port] == TR_STOP) {
        printf("unknown loop isr:%d %d\n", rx_use[port], tx_use[port]);
    }
    hal_dmac_clear_int_status(ch, int_type);
}

static void drv_i2s_loopback_dma_trx_run(
    drv_i2s_port port,
    DMAC_ISR rx_done_isr) 
{
    DMAC_CH_E ch =HAL_DMAC_CH_NOT_FOUND;
    DMAC_PER_E per_src = DMAC_HW_HS_IF_I2S_RX;
    DMAC_PER_E per_dst = DMAC_HW_HS_IF_I2S_TX;
    DMAC_TR_WIDTH_E width_src = DMAC_TR_WIDTH_16;
    DMAC_TR_WIDTH_E width_dst = DMAC_TR_WIDTH_16;
    if(hal_get_pdm_rx_ch_enable_status(port) == true) {
        if (sg_rx_buffer[port]->stereo) {
            width_src = DMAC_TR_WIDTH_32;
        }
    }
    if(port == DRV_I2S_0) {
        ch = DMAC_CH_1;
        per_src = DMAC_HW_HS_IF_I2S_RX;
        per_dst = DMAC_HW_HS_IF_I2S_TX;
    } else if(port == DRV_I2S_1) {
        ch = DMAC_CH_9;
        per_src = DMAC_HW_HS_IF_I2S1_RX;
        per_dst = DMAC_HW_HS_IF_I2S1_TX;
        if(hal_get_pdm_rx_ch_enable_status(port) == true) {
            printf("pdm i2s2 not support loopback\n");
        }
    }
    hal_dmac_register_isr(ch, DMAC_INT_TYPE_Block, rx_done_isr);
    hal_dmac_dst_auto_reload_enable(ch);

    //TRX - Used Channel 1 or Channel 9
    hal_dmac_start(
        (void *)I2S_TX_ADDR[port],
        (void *)I2S_RX_ADDR[port],
        4095,
        ch,
        width_dst,
        width_src,
        DMAC_ADDR_NO_CHANGE,
        DMAC_ADDR_NO_CHANGE,
        DMAC_MSIZE_1,
        DMAC_MSIZE_1,
        DMAC_TT_FC_P2P_Dma,
        DMAC_CH_PRIOR_7,
        DMAC_HS_SEL_HARDWARE,
        per_dst,
        DMAC_HS_SEL_HARDWARE,
        per_src
    );
}

static void drv_i2s_loopback_dma_trx_start(
    drv_i2s_port port)
{
    drv_i2s_loopback_dma_trx_run(port, drv_i2s_loopback_dma_trx_isr);
    rx_use[port] = tx_use[port] = DMA_TR_RUN;
}

static void drv_i2s_loopback_dma_trx_stop(
    drv_i2s_port port)
{
    rx_use[port] = tx_use[port] = DMA_TR_BEGIN_STOP;
}
#endif

void drv_i2s_set_buffer(
    i2s_buffer *buf) {
    drv_i2s_set_buffer_ex(DRV_I2S_0, buf, 2, buf, 2);
}

drv_i2s_status_t drv_i2s_init(
    i2s_mode_t              mode,
    sample_rate_t           sample_rate,
    bit_resolution_t        resolution)
{  
    drv_i2s_init_ex(DRV_I2S_0,mode,sample_rate,resolution);
    return DRV_I2S_STATUS_OK;
}

void drv_i2s_tx_start()
{
    drv_i2s_tx_start_ex(DRV_I2S_0, MCU_MODE);
}

void drv_i2s_tx_stop()
{
    drv_i2s_tx_stop_ex(DRV_I2S_0);
}

void drv_i2s_rx_start()
{
    drv_i2s_rx_start_ex(DRV_I2S_0, DRV_SampleRate_mormal,MCU_MODE);
}

void drv_i2s_rx_stop()
{
    drv_i2s_rx_stop_ex(DRV_I2S_0);
}

void drv_i2s_loopback_start()
{
    drv_i2s_loopback_start_ex(DRV_I2S_0, MCU_MODE);
}

void drv_i2s_loopback_stop()
{
    drv_i2s_loopback_stop_ex(DRV_I2S_0);
}

drv_i2s_status_t drv_i2s_set_buffer_ex(
    drv_i2s_port port,
    i2s_buffer *rx,
    int rx_num,
    i2s_buffer *tx,
    int tx_num)
{
    if(check_i2s_port(port) < 0 || ((rx == NULL)&&(tx == NULL)))
        return DRV_I2S_STATUS_INVALID_PARAMETER;

    if(rx != NULL) {
        sg_rx_buffer[port] = rx;
        rx_buf_num[port] =rx_num;
    }

    if(tx != NULL) {
        sg_tx_buffer[port] = tx;
        tx_buf_num[port] =tx_num;
    }

    return DRV_I2S_STATUS_OK;
}

drv_i2s_status_t drv_i2s_init_ex(
    drv_i2s_port port,
    i2s_mode_t mode,
    drv_sample_rate_t sample_rate,
    bit_resolution_t resolution)
{
    uint32_t rx_re_enable = 0;
    uint16_t i2s_bclk_divider = 0, i2s_bclk_divider2 = 0;
    enum i2s_mclk_option i2s_mclk_divider;
    lr_cnt_t                lr_cnt;

    switch(sample_rate) {
        case DRV_SampleRate_11025HZ:
            #if(CHIP_ID==6020)
            i2s_bclk_divider = 0x10;
            i2s_mclk_divider = mclk_11MHz;
            i2s_bclk_divider2 = 0x0;
            #else
            i2s_bclk_divider = 0x44;
            i2s_mclk_divider = mclk_24MHz;
            #endif
            lr_cnt = lr_cnt_32;
            break;
        case DRV_SampleRate_22050HZ:
            #if(CHIP_ID==6020)
            i2s_bclk_divider = 0x8;
            i2s_bclk_divider2 = 0x0;
            //i2s_bclk_divider = 0x7;
            //i2s_bclk_divider2 = 0xFD70;
            i2s_mclk_divider = mclk_11MHz;
            #else
            i2s_bclk_divider = 0x22;
            i2s_mclk_divider = mclk_24MHz;
            #endif
            lr_cnt = lr_cnt_32;
            break;
        case DRV_SampleRate_44100HZ:
            #if(CHIP_ID==6020)
            i2s_bclk_divider = 0x4;
            i2s_bclk_divider2 = 0x0;
            //i2s_bclk_divider = 0x4;
            //i2s_bclk_divider2 = 0xc8b;
            i2s_mclk_divider = mclk_11MHz;
            #else
            i2s_bclk_divider = 0x11;
            i2s_mclk_divider = mclk_24MHz;
            #endif
            lr_cnt = lr_cnt_32;
            break;
        case DRV_SampleRate_8000HZ:
            #if(CHIP_ID==6020)
            i2s_bclk_divider = 0x2A;
            i2s_bclk_divider2 = 0x0;
            //i2s_bclk_divider = 0x29;
            //i2s_bclk_divider2 = 0x9990;
            i2s_mclk_divider = mclk_16MHz;
            #else
            i2s_bclk_divider = 0x7e;
            i2s_mclk_divider = mclk_24MHz;
            #endif
            lr_cnt = lr_cnt_24;
            break;
        case DRV_SampleRate_16000HZ:
            #if(CHIP_ID==6020)
            i2s_bclk_divider = 0x15;
            i2s_bclk_divider2 = 0x0;
            //i2s_bclk_divider = 0x14;
            //i2s_bclk_divider2 = 0xD47A;
            i2s_mclk_divider = mclk_16MHz;
            #else
            i2s_bclk_divider = 0x3f;
            i2s_mclk_divider = mclk_24MHz;
            #endif
            lr_cnt = lr_cnt_24;
            break;
        case DRV_SampleRate_24000HZ:
            #if(CHIP_ID==6020)
            i2s_bclk_divider = 0xe;
            i2s_bclk_divider2 = 0x0;
            i2s_mclk_divider = mclk_16MHz;
            #else
            i2s_bclk_divider = 0x21;
            i2s_mclk_divider = mclk_24MHz;
            #endif
            lr_cnt = lr_cnt_24;
            break;
        case DRV_SampleRate_48000HZ:
        default:
            #if(CHIP_ID==6020)
            i2s_bclk_divider = 0x7;
            i2s_bclk_divider2 = 0x0;
            //i2s_bclk_divider = 0x6;
            //i2s_bclk_divider2 = 0xffa4;
            i2s_mclk_divider = mclk_16MHz;
            #else
            i2s_bclk_divider = 0x15;
            i2s_mclk_divider = mclk_24MHz;
            #endif
            lr_cnt = lr_cnt_24;
            break;
    }
    #if(CHIP_ID==6020)
    if((tx_use[port] != TR_STOP) || 
        ((rx_use[port] != TR_STOP) && (i2s_init_rate == sample_rate))) {
        printf("this port already init\n");
        return DRV_I2S_STATUS_OK;
    }
    if(dma_init_en == 0) {
        hal_dmac_init();
        dma_init_en = 1;
    }
    if((rx_use[port] != TR_STOP) && (i2s_init_rate != sample_rate)) {
        drv_i2s_rx_stop_ex(port);
        rx_re_enable = 1;
    }
    i2s_init_rate = sample_rate;
	hal_i2s_enable_clock();
    hal_pdm_rx_ch_disable(port);
    hal_pdm_tx_ch_disable();
    hal_i2s_disable(port);
    hal_i2s_tx_disable(port);
    hal_i2s_rx_disable(port);
    hal_i2s_set_intr_mask(port, I2S_TX_FIFO_LOW);
    hal_i2s_set_tx_fifo_threshold(port, 0x07);
    hal_i2s_set_intr_mask(port, I2S_RX_FIFO_AVAILABLE);
    hal_i2s_set_rx_fifo_threshold(port, 0x07);
    hal_i2s_set_word_select_width(port, lr_cnt, resolution, resolution);
    if(mode_master == mode) {
        #if(CHIP_ID==6020)
        hal_i2s_exclk_enable(port, I2S_NORMAL, i2s_bclk_divider, i2s_bclk_divider2, i2s_mclk_divider);
        #else
        hal_i2s_clk_enable(port, i2s_bclk_divider, i2s_mclk_divider);
        #endif
    } else {
        hal_i2s_clk_disable(port);
    }
    hal_i2s_enable(port);
    #else
    hal_i2s_disable();
    hal_i2s_tx_disable();
    hal_i2s_rx_disable();
    hal_i2s_set_intr_mask(I2S_TX_FIFO_LOW);
    hal_i2s_set_tx_fifo_threshold(0x07);
    hal_i2s_set_intr_mask(I2S_RX_FIFO_AVAILABLE);
    hal_i2s_set_rx_fifo_threshold(0x07);
    hal_i2s_set_word_select_width(lr_cnt, resolution, resolution);
    if(mode_master == mode) {
        hal_i2s_clk_enable(i2s_bclk_divider, i2s_mclk_divider);
    } else {
        hal_i2s_clk_disable();
    }
    hal_i2s_enable();
    #endif
    if(rx_re_enable == 1) {
        drv_i2s_rx_start_ex(port, i2s_ds_rate, i2s_rx_handler);
        tx_use[port] = TR_STOP;
    } else {
        rx_use[port] = tx_use[port] = TR_STOP;
    }
    return DRV_I2S_STATUS_OK;
}

drv_i2s_status_t drv_i2s_tx_start_ex(
    drv_i2s_port port,
     i2s_data_handler handler)
{
    if(check_i2s_port(port) < 0 ||
        check_data_handler(handler) < 0)
        return DRV_I2S_STATUS_INVALID_PARAMETER;

#if(CHIP_ID==6020)
    hal_i2s_tx_enable(port);
#else
    hal_i2s_tx_enable();
#endif

#if(CHIP_ID==6020)
    if(handler == DMAC_MODE &&
        tx_use[port] == TR_STOP) {
        drv_i2s_dma_tx_start(port);
    } else
#endif
    if (handler == MCU_MODE &&
        tx_use[port] == TR_STOP &&
        rx_use[port] == TR_STOP) {
        drv_i2s_mcu_tx_start(port);
    } else {
        printf("tx start fail(%d)\n", tx_use[port]);
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }

    return DRV_I2S_STATUS_OK;
}

drv_i2s_status_t drv_i2s_tx_stop_ex(
    drv_i2s_port port)
{
    if(check_i2s_port(port) < 0)
        return DRV_I2S_STATUS_INVALID_PARAMETER;

#if(CHIP_ID==6020)
    if(tx_use[port] == DMA_TR_RUN) {
        drv_i2s_dma_tx_stop(port);
    } else
#endif
    if (tx_use[port] == MCU_TR_RUN) {
        drv_i2s_mcu_tx_stop(port);
    if(port == DRV_I2S_0) {
        intc_irq_disable(IRQ_I2S);
    } else if(port == DRV_I2S_1) {
        intc_group02_irq_disable(0x7);
    }
    } else {
        printf("tx stop fail(%d)\n", tx_use[port]);
        return DRV_I2S_STATUS_ERROR;
    }

    return DRV_I2S_STATUS_OK;
}

drv_i2s_status_t drv_i2s_rx_start_ex(
    drv_i2s_port port,
    drv_sample_rate_t rate,
     i2s_data_handler handler)
{
    if(check_i2s_port(port) < 0 ||
        check_data_handler(handler) < 0)
        return DRV_I2S_STATUS_INVALID_PARAMETER;

#if ((CHIP_ID==6020) && (CHIP_SUB_ID != 0))
#ifdef I2S_SUPPORT_DS
    i2s_ds_rate = 0;
    if(hal_get_pdm_rx_ch_enable_status(port) == true) {
        printf("do nothing\n");
    } else {
        pdm_downsampler_disable(port);
        if(rate != DRV_SampleRate_mormal) {
            i2s_ds_rate = rate;
            i2s_rx_handler = handler;
            printf("origin: %d dest: %d\n", i2s_init_rate, i2s_ds_rate);
            pdm_downsampler_enable(port, i2s_init_rate, i2s_ds_rate);
        }
        hal_pdm_rx_data_bit_align(port, 0);//real chip need
    }
#endif
#endif

    #if(CHIP_ID==6020)
    hal_i2s_rx_enable(port);
    #else
    hal_i2s_rx_enable();
    #endif

#if(CHIP_ID==6020)
    if(handler == DMAC_MODE &&
        rx_use[port] == TR_STOP) {
        drv_i2s_dma_rx_start(port);
    } else
#endif
    if (handler == MCU_MODE &&
        rx_use[port] == TR_STOP &&
        tx_use[port] == TR_STOP) {
        drv_i2s_mcu_rx_start(port);
    } else {
        printf("rx start fail(%d)\n", rx_use[port]);
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }

    return DRV_I2S_STATUS_OK;
}

drv_i2s_status_t drv_i2s_rx_stop_ex(
    drv_i2s_port port)
{
    if(check_i2s_port(port) < 0)
        return DRV_I2S_STATUS_INVALID_PARAMETER;

#if(CHIP_ID==6020)
    if(rx_use[port] == DMA_TR_RUN) {
        drv_i2s_dma_rx_stop(port);
    } else
#endif
    if (rx_use[port] == MCU_TR_RUN) {
        drv_i2s_mcu_rx_stop(port);
    } else {
        printf("rx stop fail(%d)\n", rx_use[port]);
        return DRV_I2S_STATUS_ERROR;
    }

    return DRV_I2S_STATUS_OK;
}

drv_i2s_status_t drv_i2s_loopback_start_ex(
    drv_i2s_port port,
    i2s_data_handler handler) 
{
    if(check_i2s_port(port) < 0 || 
        check_data_handler(handler) < 0)
        return DRV_I2S_STATUS_INVALID_PARAMETER;

    #if(CHIP_ID==6020)
    hal_i2s_tx_enable(port);
    hal_i2s_rx_enable(port);
    #else
    hal_i2s_tx_enable();
    hal_i2s_rx_enable();
    #endif

#if(CHIP_ID==6020)
    if(handler == DMAC_MODE &&
        rx_use[port] == TR_STOP && 
        tx_use[port] == TR_STOP) {
        drv_i2s_loopback_dma_trx_start(port);
    } else
#endif
    if (handler == MCU_MODE && 
        rx_use[port] == TR_STOP && 
        tx_use[port] == TR_STOP) {
        drv_i2s_loopback_mcu_trx_start(port);
    } else {
        printf("loopback start fail(%d %d)\n", rx_use[port], tx_use[port]);
        return DRV_I2S_STATUS_INVALID_PARAMETER;
    }

    return DRV_I2S_STATUS_OK;
}

drv_i2s_status_t drv_i2s_loopback_stop_ex(
    drv_i2s_port port) 
{
    if(check_i2s_port(port) < 0)
        return DRV_I2S_STATUS_INVALID_PARAMETER;

#if(CHIP_ID==6020)
    if(rx_use[port] == DMA_TR_RUN 
        && tx_use[port] == DMA_TR_RUN) {
        drv_i2s_loopback_dma_trx_stop(port);
    } else
#endif
    if (rx_use[port] == MCU_TR_RUN 
        && tx_use[port] == MCU_TR_RUN) {
        drv_i2s_loopback_mcu_trx_stop(port);
    } else {
        printf("loopback stop fail(%d %d)\n", rx_use[port], tx_use[port]);
        return DRV_I2S_STATUS_ERROR;
    }

    return DRV_I2S_STATUS_OK;
}

