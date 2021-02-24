#ifndef HAL_I2CSLV
#define HAL_I2CSLV

#include "hal_i2cmst.h"

typedef void (*pfun_cb) (void);
typedef void (*pfun_cb2) (uint32_t *);
typedef int32_t (*pfun_i2c_slv_tx_empty_isr)(hal_i2c_port port);
typedef int32_t (*pfun_i2c_slv_read_request_isr)(hal_i2c_port port);
typedef int32_t (*pfun_i2c_slv_master_stop_receive_isr)(hal_i2c_port port);
typedef int32_t (*pfun_i2c_slv_master_abort_receive_isr)(hal_i2c_port port);
typedef int32_t (*pfun_i2c_slv_rx_threshold_isr)(hal_i2c_port port);
typedef int32_t (*pfun_i2c_slv_stop_detect_isr)(hal_i2c_port port);


int8_t hal_i2c_slv_enable(hal_i2c_port port);
int8_t hal_i2c_slv_disable(hal_i2c_port port);

int8_t hal_i2c_slv_init(hal_i2c_port port, uint16_t slv_addr);
int8_t hal_i2c_slv_deinit(hal_i2c_port port);

void hal_i2c_slv_register_tx_empty_isr(pfun_i2c_slv_tx_empty_isr isr);
void hal_i2c_slv_register_read_request_isr(pfun_i2c_slv_read_request_isr isr);
void hal_i2c_slv_register_master_stop_receive_isr(pfun_i2c_slv_master_stop_receive_isr isr);
void hal_i2c_slv_register_master_abort_receive_isr(pfun_i2c_slv_master_abort_receive_isr isr);
void hal_i2c_slv_register_rx_threshold_isr(pfun_i2c_slv_rx_threshold_isr isr);
void hal_i2c_slv_register_stop_detect_isr(pfun_i2c_slv_stop_detect_isr isr);

int32_t hal_i2c_slv_get_interrupt_status(hal_i2c_port port);
int32_t hal_i2c_slv_enable_interrupt(hal_i2c_port port, ENUM_I2C_MST_INT_STATUS_T bit, uint8_t enable);

int32_t hal_i2c_slv_write_fifo(hal_i2c_port port, uint8_t data);
int32_t hal_i2c_slv_read_fifo(hal_i2c_port port);
#endif /* end of include guard */

