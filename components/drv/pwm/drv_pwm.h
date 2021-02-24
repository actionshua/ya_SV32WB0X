#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#include <hal_pwm.h>

#include "custom_io_hal.h"
#include "custom_io_chk.h"

/**
 * Initilize PWM to ready operations.
 * 
 * @param   pwm_id
 *              0x00 - PWM_0.
 *              0x01 - PWM_1.
 *              0x02 - PWM_2.
 *              0x03 - PWM_3.
 *              0x04 - PWM_4. 
 *              0x05 - PWM_5.
 *              0x06 - PWM_6.
 *              0x07 - PWM_7.
 * @return  -1              The operation error.
 * @return   0              The operation completed successfully.
 */
int8_t drv_pwm_init(uint8_t pwm_id);



/**
 * Deinitialize all PWM to disable operations
 * 
 * @return  -1              The operation error.
 * @return   0              The operation completed successfully.
 */
int8_t drv_pwm_deinit(void);



/**
 * Saves PWM setting configuration.
 * 
 * @param   pwm_id
 *              0x00 - PWM_0.
 *              0x01 - PWM_1.
 *              0x02 - PWM_2.
 *              0x03 - PWM_3.
 *              0x04 - PWM_4.
 *              0x05 - PWM_5.
 *              0x06 - PWM_6.
 *              0x07 - PWM_7.
 * @param   freq_hz         freq_hz range (10 ~ 80000000 - PWM_CLK=160MHz).
 * @param   duty            range 0 ~ 4096
 * @param   is_invert       invert the waveform
 *
 * @return  -1              The operation error.
 * @return   0              The operation completed successfully.
 */
int8_t drv_pwm_config(uint8_t pwm_id, uint32_t freq_hz, uint32_t duty, uint8_t is_invert);


/**
 * Enables the PWM to start operation
 *
 * @param       pwm_id
 *              0x00 - PWM_0.
 *              0x01 - PWM_1.
 *              0x02 - PWM_2.
 *              0x03 - PWM_3.
 *              0x04 - PWM_4. 
 *              0x05 - PWM_5.
 *              0x06 - PWM_6.
 *              0x07 - PWM_7.
 * @return  -1              The operation error.
 * @return   0              The operation completed successfully.
 */
int8_t drv_pwm_enable(uint8_t pwm_id);



/**
 * Disables the PWM to stop operation
 *
 * @param   pwm_id
 *              0x00 - PWM_0.
 *              0x01 - PWM_1.
 *              0x02 - PWM_2.
 *              0x03 - PWM_3.
 *              0x04 - PWM_4. 
 *              0x05 - PWM_5.
 *              0x06 - PWM_6.
 *              0x07 - PWM_7.
 * @return  -1              The operation error.
 * @return   0              The operation completed successfully.
 */
int8_t drv_pwm_disable(uint8_t pwm_id);

/**
 * Force the PWM to logic
 *
 * @param   pwm_id
 *              0x00 - PWM_0.
 *              0x01 - PWM_1.
 *              0x02 - PWM_2.
 *              0x03 - PWM_3.
 *              0x04 - PWM_4. 
 *              0x05 - PWM_5.
 *              0x06 - PWM_6.
 *              0x07 - PWM_7.
 * @param   logic
 *              0 to low, 1 to high
 */

int8_t drv_pwm_enable_all(void);

/**
 * Enable the all PWMs at the same time
 *
 */

void drv_pwm_set_logic(uint8_t pwm_id, uint8_t logic);

// support padmux checking feature.
#define DRV_PWM_INIT_HAL_PWM_0() \
    do { \
        drv_pwm_init(HAL_PWM_0); \
        (void)PERI_IO_PWM0; \
    } while(0)

#define DRV_PWM_INIT_HAL_PWM_1() \
    do { \
        drv_pwm_init(HAL_PWM_1); \
        (void)PERI_IO_PWM1; \
    } while(0)

#define DRV_PWM_INIT_HAL_PWM_2() \
    do { \
        drv_pwm_init(HAL_PWM_2); \
        (void)PERI_IO_PWM2; \
    } while(0)

#define DRV_PWM_INIT_HAL_PWM_3() \
    do { \
        drv_pwm_init(HAL_PWM_3); \
        (void)PERI_IO_PWM3; \
    } while(0)

#define DRV_PWM_INIT_HAL_PWM_4() \
    do { \
        drv_pwm_init(HAL_PWM_4); \
        (void)PERI_IO_PWM4; \
    } while(0)

#define DRV_PWM_INIT_HAL_PWM_5() \
    do { \
        drv_pwm_init(HAL_PWM_5); \
        (void)PERI_IO_PWM5; \
    } while(0)

#define DRV_PWM_INIT_HAL_PWM_6() \
    do { \
        drv_pwm_init(HAL_PWM_6); \
        (void)PERI_IO_PWM6; \
    } while(0)

#define DRV_PWM_INIT_HAL_PWM_7() \
    do { \
        drv_pwm_init(HAL_PWM_7); \
        (void)PERI_IO_PWM7; \
    } while(0)

#define DRV_PWM_INIT(PWM) \
    DRV_PWM_INIT_##PWM();

#endif  // __DRV_PINMUX_H__

