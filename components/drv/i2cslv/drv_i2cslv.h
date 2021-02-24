#ifndef I2CSLV
#define I2CSLV
#include "hal_i2cslv.h"
#include "drv_i2cmst.h"

#include "custom_io_hal.h"
#include "custom_io_chk.h"

#define REPEAT_CNT (200)
#define DRV_I2C_DEFAULT DRV_I2C_0

typedef int32_t (*pfun_i2c_slv_recv_isr)(hal_i2c_port port);
typedef int32_t (*pfun_i2c_slv_tx_done_isr)(hal_i2c_port port);

int8_t drv_i2c_slv_init(hal_i2c_port port, uint16_t slv_addr); 
int32_t drv_i2c_slv_send(hal_i2c_port port, uint8_t *buf, uint8_t len);
int32_t drv_i2c_slv_recv(hal_i2c_port port, uint8_t *buf, uint8_t max_len);
void drv_i2c_slv_register_recv_isr(pfun_i2c_slv_recv_isr isr);
void drv_i2c_slv_register_tx_done_isr(pfun_i2c_slv_tx_done_isr isr);

// support padmux checking feature.
#define DRV_I2C_SLV_INIT_HAL_I2C_0(slv_addr) \
    do { \
        drv_i2c_slv_init(HAL_I2C_0, slv_addr); \
        (void)PERI_IO_I2C0; \
    } while(0)

#define DRV_I2C_SLV_INIT_HAL_I2C_1(slv_addr) \
    do { \
        drv_i2c_slv_init(HAL_I2C_1, slv_addr); \
        (void)PERI_IO_I2C1; \
    } while(0)

#define DRV_I2C_SLV_INIT(I2C,slv_addr) \
    DRV_I2C_SLV_INIT_##I2C(slv_addr);


#endif /* end of include guard */

