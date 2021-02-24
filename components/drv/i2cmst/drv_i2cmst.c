#include <stdio.h>
#include <stdint.h>
#include "hal_i2cmst.h"
#include "drv_i2cmst.h"
#include "attrs.h"
#include "osal.h"
#include "soc_defs.h"
#include "soc_types.h"

#include "logger.h"

#define I2CMST_TAG       LOG_TAG_DRV_I2CMST
#define I2CMST_LOG_E(format, ...) log_e(I2CMST_TAG, format, ##__VA_ARGS__)
#define I2CMST_LOG_W(format, ...) log_w(I2CMST_TAG, format, ##__VA_ARGS__)
#define I2CMST_LOG_I(format, ...) log_i(I2CMST_TAG, format, ##__VA_ARGS__)
#define I2CMST_LOG_D(format, ...) log_d(I2CMST_TAG, format, ##__VA_ARGS__)
#define I2CMST_LOG_V(format, ...) log_v(I2CMST_TAG, format, ##__VA_ARGS__)

#define DRV_I2C_DEFAULT DRV_I2C_0

uint32_t gWaitTimeInUs = 0;
uint32_t gRetryCount = 200;

int8_t drv_i2c_mst_init(uint16_t frequency) 
{

    return drv_i2c_mst_init_ex(DRV_I2C_DEFAULT, frequency);
}

int8_t drv_i2c_mst_deinit(void) 
{

    return drv_i2c_mst_deinit_ex(DRV_I2C_DEFAULT);
}


int8_t drv_i2c_mst_write(uint8_t slave_address, uint8_t *data, uint32_t length, uint8_t is_start, uint8_t is_stop) 
{
    
    return drv_i2c_mst_write_ex(DRV_I2C_DEFAULT, slave_address, data, length, is_start, is_stop);
}

int8_t drv_i2c_mst_read(uint8_t slave_address, uint8_t *data, uint32_t length, uint8_t is_start, uint8_t is_stop) 
{

    return drv_i2c_mst_read_ex(DRV_I2C_DEFAULT, slave_address, data, length, is_start, is_stop);
}


void drv_i2c_mst_retry_wait_time_us(uint32_t wait_time_in_us)
{

    return drv_i2c_mst_retry_wait_time_us_ex(DRV_I2C_DEFAULT, wait_time_in_us);
}


void drv_i2c_mst_retry_count(uint32_t retry_count) 
{

    return drv_i2c_mst_retry_count_ex(DRV_I2C_DEFAULT, retry_count);
}


//6020 api

int8_t drv_i2c_mst_init_ex(drv_i2c_port port, uint16_t frequency)
{

    int8_t ret = 0;
#if (CHIP_ID == 6006)    
    ret = hal_i2c_mst_init(frequency);
#else
    ret = hal_i2c_mst_init(port, frequency);
#endif
    return ret;    
}

int8_t drv_i2c_mst_deinit_ex(drv_i2c_port port)
{

    int8_t ret = 0;
#if (CHIP_ID == 6006)    
    ret = hal_i2c_mst_deinit();
#else
    ret = hal_i2c_mst_deinit(port);
#endif
    return ret;    
}

int8_t drv_i2c_mst_write_ex(drv_i2c_port port, uint8_t slave_address, uint8_t *data, uint32_t length, uint8_t is_start, uint8_t is_stop)
{

    int8_t ret = 0;
    int32_t repeat_num = 0;

    REPEAT:
    OS_UsDelay(gWaitTimeInUs);
#if (CHIP_ID == 6006)        
    ret = hal_i2c_mst_write_byte(slave_address, data, length, is_start, is_stop);
#else
    ret = hal_i2c_mst_write_byte(port, slave_address, data, length, is_start, is_stop);
#endif

#if (CHIP_ID == 6006)     
    if(0x1 ==  hal_i2c_mst_get_noack_abort_status(ABRT_7B_ADDR_NOACK))	
#else
    if(0x1 ==  hal_i2c_mst_get_noack_abort_status(port, ABRT_7B_ADDR_NOACK))	
#endif
    {        
        repeat_num++;
        if(repeat_num > gRetryCount) {
            ret = -1;
            I2CMST_LOG_E("[%s]:NACK REPEAT_ERROR\n", __FUNCTION__, __LINE__);
            goto FUN_FAIL;
        }
		goto REPEAT;
	}
    
    return ret;

   FUN_FAIL:
    return ret;        
}

int8_t drv_i2c_mst_read_ex(drv_i2c_port port, uint8_t slave_address, uint8_t *data, uint32_t length, uint8_t is_start, uint8_t is_stop)
{
   
    int8_t ret = 0;
    int32_t repeat_num = 0;

    REPEAT:
	OS_UsDelay(gWaitTimeInUs);
#if (CHIP_ID == 6006)        
    ret = hal_i2c_mst_read_byte(slave_address, data, length, is_start, is_stop);
#else
    ret = hal_i2c_mst_read_byte(port, slave_address, data, length, is_start, is_stop);
#endif

#if (CHIP_ID == 6006)        
    if(0x1 ==  hal_i2c_mst_get_noack_abort_status(ABRT_7B_ADDR_NOACK))	
#else
    if(0x1 ==  hal_i2c_mst_get_noack_abort_status(port, ABRT_7B_ADDR_NOACK))	
#endif
    {        
        repeat_num++;
        if(repeat_num > gRetryCount) {
            ret = -1;
            I2CMST_LOG_E("[%s]:NACK REPEAT_ERROR\n", __FUNCTION__, __LINE__);
            goto FUN_FAIL;
        }
		goto REPEAT;
	}
    
    return ret;

   FUN_FAIL:
    return ret;    
}

void drv_i2c_mst_retry_wait_time_us_ex(drv_i2c_port port, uint32_t wait_time_in_us)
{
    gWaitTimeInUs = wait_time_in_us;
}

void drv_i2c_mst_retry_count_ex(drv_i2c_port port , uint32_t retry_count)
{
    gRetryCount = retry_count;    
}

