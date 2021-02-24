#ifndef I2CMST
#define I2CMST
#include "hal_i2cmst.h"

#include "custom_io_hal.h"
#include "custom_io_chk.h"

#define REPEAT_CNT (200)

typedef enum {
    DRV_I2C_0 = 0x0,
    DRV_I2C_1 = 0x1,
    DRV_I2C_MAX,
} drv_i2c_port;

/**
 * Initializes I2C registers with initial values provided from the customizer.
 * 
 * @param   frequency       I2C Clock (100 - 1000 KHz)
 *
 * @return  -1              I2C error!!
 * @return   0              The operation completed successfully.
 */
int8_t drv_i2c_mst_init(uint16_t frequency);



/**
 * Deinitialize I2C registers.
 *
 * @return  -1              I2C error!!
 * @return   0              The operation completed successfully.
 */
int8_t drv_i2c_mst_deinit(void);



/**
 * Writes the referenced data buffer to a specified slave address.
 * 
 * @param   slave_address   The I2C slave address for 7 bit.
 * @param   data            Pointer to the data buffer to be written by the master.
 * @param   length          Size of the write buffer exposed to the I2C master. 
 * @param   is_start        1 每 RESTART is issued before the data is sent.
 *                          0 每 RESTART is issued only if the transfer direction is changing from the previous command.
 * @param   is_stop         1 每 STOP is issued after the last byte data.
 *                          0 每 STOP is not issued after the last byte data.
 *
 * @return  -1              Slave has no ack. 
 * @return   0              The operation completed successfully.
 */
int8_t drv_i2c_mst_write(uint8_t slave_address, uint8_t *data, uint32_t length, uint8_t is_start, uint8_t is_stop);



/**
 * Reads data from the specified slave address and places the data in the referenced buffer.
 * 
 * @param   slave_address   The I2C slave address for 7 bit.
 * @param   data            Pointer to the data buffer to be read by the master.
 * @param   length          Size of the write buffer exposed to the I2C master.
 * @param   is_start        1 每 RESTART is issued before the data is sent.
 *                          0 每 RESTART is issued only if the transfer direction is changing from the previous command.
 * @param   is_stop         1 每 STOP is issued after the last byte data.
 *                          0 每 STOP is not issued after the last byte data.
 *
 * @return  -1              Slave has no ack. 
 * @return   0              The operation completed successfully.
 */
int8_t drv_i2c_mst_read(uint8_t slave_address, uint8_t *data, uint32_t length, uint8_t is_start, uint8_t is_stop);



/**
 * Set I2C retry wait time in us.
 * 
 * @param   wait_time_in_us       retry wait time in us.
 */
void drv_i2c_mst_retry_wait_time_us(uint32_t wait_time_in_us);



/**
 * Set I2C retry count.
 * 
 * @param   retry_count       I2C retry count.
 */
void drv_i2c_mst_retry_count(uint32_t retry_count);


//extend api for second i2c at 6020
int8_t drv_i2c_mst_init_ex(drv_i2c_port port, uint16_t frequency);
int8_t drv_i2c_mst_deinit_ex(drv_i2c_port port);
int8_t drv_i2c_mst_write_ex(drv_i2c_port port, uint8_t slave_address, uint8_t *data, uint32_t length, uint8_t is_start, uint8_t is_stop);
int8_t drv_i2c_mst_read_ex(drv_i2c_port port, uint8_t slave_address, uint8_t *data, uint32_t length, uint8_t is_start, uint8_t is_stop);
void drv_i2c_mst_retry_wait_time_us_ex(drv_i2c_port port, uint32_t wait_time_in_us);
void drv_i2c_mst_retry_count_ex(drv_i2c_port port, uint32_t retry_count);


// support padmux checking feature.
#define DRV_I2C_MST_INIT_EX_HAL_I2C_0(frequency) \
    do { \
        drv_i2c_mst_init_ex(HAL_I2C_0, frequency); \
        (void)PERI_IO_I2C0; \
    } while(0)

#define DRV_I2C_MST_INIT_EX_HAL_I2C_1(frequency) \
    do { \
        drv_i2c_mst_init_ex(HAL_I2C_1, frequency); \
        (void)PERI_IO_I2C1; \
    } while(0)

#define DRV_I2C_MST_INIT_EX(I2C,frequency) \
    DRV_I2C_MST_INIT_EX_##I2C(frequency);

#endif /* end of include guard */

