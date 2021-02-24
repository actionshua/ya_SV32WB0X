/**
 * @file disp_spi.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include <string.h>

#include "spi_lcm_hw.h"
#include "pinmux/drv_pinmux.h"
#include "gpio/drv_gpio.h"
#include <hal_dmac.h>
#include <drv_spimst.h>

#include <attrs.h>
#include <osal.h>
#include <stdio.h>

#define LOCAL_SIGNAL_DEBUG 0
#define LOCAL_DEBUG_PIN         (GPIO_17)

#define REG32(reg)		(  *( (volatile uint32_t *) (reg) ) )
#define M_LCD_SPI   M_LCM_SPI_MASTER
#define SPI_MXT		(4095)
static void (*sg_done_cb)(void *) = NULL;
static void *sg_param = NULL;
void spi_lcm_hw_send_colors(uint8_t * data, uint16_t length) ATTRIBUTE_SECTION_FAST;
static uint32_t g_max_length = 0;
uint16_t dummy_read_buffer[SPI_MXT]; // TODO: remove it.

spi_lcm_hal_t *g_spi_lcm_hal = NULL;

#define NON_RET
#define CHECK_SPI_LCM(FAILED_RET) \
    do { \
        if (!g_spi_lcm_hal) { \
            printf("[%s] lcm not selected. at %d\n", __func__, __LINE__); \
            return FAILED_RET; \
        } \
    } while(0)

#if (M_LCM_SPI_ASYNC == 1)
static volatile int sg_spi_busy = 0; // TODO: remove it.

static void spi_dma_done(DMAC_CH_E CH, DMAC_INT_TYPE_E INT_TYPE)
{
    hal_dmac_clear_int_status(CH, INT_TYPE);
    while(hal_spimst_get_status(M_LCD_SPI, SPI_MST_TRX_BUSY));
    //lv_disp_flush_ready(g_now_disp);
    sg_spi_busy = 0;
    if (sg_done_cb) {
        sg_done_cb(sg_param);
    }
}
#endif

void spi_lcm_hw_setpin_reset(gpio_logic_t logic) {
    drv_gpio_set_logic(M_LCM_RESET_PIN, logic);
}

void spi_lcm_hw_init(void) {

    uint8_t *tx_buf,*rx_buf;

    CHECK_SPI_LCM(NON_RET);

    drv_spimst_init_ex(M_LCD_SPI, g_spi_lcm_hal->spi_clock(), 0, 0);

    drv_gpio_set_mode(M_LCM_RESET_PIN, PIN_MODE_GPIO);
    drv_gpio_set_dir(M_LCM_RESET_PIN, GPIO_DIR_OUT);

    drv_gpio_set_mode(M_LCM_DC_PIN, PIN_MODE_GPIO);
    drv_gpio_set_dir(M_LCM_DC_PIN, GPIO_DIR_OUT);

#if LOCAL_SIGNAL_DEBUG
    drv_gpio_set_mode(LOCAL_DEBUG_PIN, PIN_MODE_GPIO);
    drv_gpio_set_dir(LOCAL_DEBUG_PIN, GPIO_DIR_OUT);
#endif

    //g_spi_lcm_hal->reset();
    //spi_lcm_hw_setpin_reset(GPIO_LOGIC_HIGH);
    //OS_MsDelay(120);
    //spi_lcm_hw_setpin_reset(GPIO_LOGIC_LOW);
    //OS_MsDelay(120);
    //spi_lcm_hw_setpin_reset(GPIO_LOGIC_HIGH);
    //OS_MsDelay(140);
}

//void set_backlight(uint8_t percent) {
//    (void) percent;
//}


void spi_lcm_acquire_bus() {
    //drv_gpio_set_logic(CS_PIN, GPIO_LOGIC_LOW);
}

void spi_lcm_release_bus() {
    //drv_gpio_set_logic(CS_PIN, GPIO_LOGIC_HIGH);
}

//void write_index(uint16_t index) {//no need
//    (void) index;
//}

void spi_lcm_hw_write_data( uint16_t data) {

#if LOCAL_SIGNAL_DEBUG
    drv_gpio_set_logic(LOCAL_DEBUG_PIN, GPIO_LOGIC_LOW);
#endif
    while(hal_spimst_get_status(M_LCD_SPI, SPI_MST_TRX_BUSY));
    drv_gpio_set_logic(M_LCM_DC_PIN, GPIO_LOGIC_HIGH);

    data = (data&0xFF)<<8 | (data&0xFF00)>>8;
    //drv_spimst_trx_ex(M_LCD_SPI, &data, dummy_read_buffer, sizeof(uint16_t),CS_PIN);
    drv_spimst_transfer(M_LCD_SPI, (void *)&data, (void *)dummy_read_buffer, sizeof(uint16_t));

#if LOCAL_SIGNAL_DEBUG
    drv_gpio_set_logic(LOCAL_DEBUG_PIN, GPIO_LOGIC_HIGH);
#endif
    return;
}

void spi_lcm_hw_write_cmd( uint8_t cmd) {
#if LOCAL_SIGNAL_DEBUG
    drv_gpio_set_logic(LOCAL_DEBUG_PIN, GPIO_LOGIC_LOW);
#endif
    while(hal_spimst_get_status(M_LCD_SPI, SPI_MST_TRX_BUSY));
    drv_gpio_set_logic(M_LCM_DC_PIN, GPIO_LOGIC_LOW);

    //drv_spimst_trx_ex(M_LCD_SPI, &cmd, dummy_read_buffer, sizeof(uint8_t),CS_PIN);
    drv_spimst_transfer(M_LCD_SPI, &cmd, (void *)dummy_read_buffer, sizeof(uint8_t));
#if LOCAL_SIGNAL_DEBUG
    drv_gpio_set_logic(LOCAL_DEBUG_PIN, GPIO_LOGIC_HIGH);
#endif

}

void spi_lcm_hw_write_data_byte(uint8_t byte) {

    uint8_t dummy_read;
#if LOCAL_SIGNAL_DEBUG
    drv_gpio_set_logic(LOCAL_DEBUG_PIN, GPIO_LOGIC_LOW);
#endif
    while(hal_spimst_get_status(M_LCD_SPI, SPI_MST_TRX_BUSY));
    drv_gpio_set_logic(M_LCM_DC_PIN, GPIO_LOGIC_HIGH);
    //drv_spimst_trx_ex(M_LCD_SPI, &byte, dummy_read_buffer, sizeof(uint8_t),CS_PIN);
    drv_spimst_transfer(M_LCD_SPI, &byte, (void *)dummy_read_buffer, sizeof(uint8_t));
#if LOCAL_SIGNAL_DEBUG
    drv_gpio_set_logic(LOCAL_DEBUG_PIN, GPIO_LOGIC_HIGH);
#endif
}
void spi_lcm_hw_write_buf(uint8_t *buf, uint32_t cnt, void (*done_cb)(void *), void *param) {
    while(hal_spimst_get_status(M_LCD_SPI, SPI_MST_TRX_BUSY));
    drv_gpio_set_logic(M_LCM_DC_PIN, GPIO_LOGIC_HIGH);
#if (M_LCM_SPI_ASYNC == 1)
    sg_done_cb = done_cb;
    sg_param = param;
#endif
    spi_lcm_hw_send_colors(buf, cnt);
#if (M_LCM_SPI_ASYNC == 1)
#else
    if (done_cb) {
        done_cb(param);
    }
#endif
}

int spi_lcm_is_busy() ATTRIBUTE_SECTION_FAST;
int spi_lcm_is_busy() {
    //return hal_spimst_get_status(M_LCD_SPI, SPI_MST_TRX_BUSY);
#if (M_LCM_SPI_ASYNC == 1)
    return sg_spi_busy;
#else
    return false;
#endif
}


//void disp_spi_send_data(uint8_t * data, uint16_t length) ATTRIBUTE_SECTION_FAST;
//void disp_spi_send_data(uint8_t * data, uint16_t length)                                                                                                 
//{
//    int cnt = length;
//    int send_cnt;
//    int buffer_index = 0;
//    while(1)
//    {
//        if(cnt > SPI_MXT)
//        {
//            send_cnt = SPI_MXT;
//            cnt -= SPI_MXT;
//        }
//        else if(cnt >0)
//        {
//            send_cnt = cnt;
//            cnt = 0;
//        }
//        else
//        {
//            break;
//        }
//        drv_spimst_dma_tx(M_LCD_SPI, data + buffer_index, sizeof(uint8_t) *send_cnt, NULL);
//        buffer_index += sizeof(uint8_t) *send_cnt;
//    }
//}

void spi_lcm_hw_send_colors(uint8_t * data, uint16_t length)
{
    int cnt = length;
    int send_cnt;
    int buffer_index = 0;

#if (M_LCM_SPI_ASYNC == 1)
    sg_spi_busy = 1;
#endif

    if (length > 4095) {
#if (M_LCM_SPI_ASYNC == 1)
        drv_spimst_dma_long_tx(M_LCD_SPI, data + buffer_index, sizeof(uint8_t) * cnt, spi_dma_done);
#else
        drv_spimst_dma_long_tx(M_LCD_SPI, data + buffer_index, sizeof(uint8_t) * cnt, NULL);
#endif
    } else {
#if (M_LCM_SPI_ASYNC == 1)
        drv_spimst_dma_tx(M_LCD_SPI, data + buffer_index, sizeof(uint8_t) * cnt, spi_dma_done);
#else
        drv_spimst_dma_tx(M_LCD_SPI, data + buffer_index, sizeof(uint8_t) * cnt, NULL);
#endif
    }
}
