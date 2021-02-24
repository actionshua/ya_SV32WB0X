#ifndef DRV_GPIO_H
#define DRV_GPIO_H

#include "ssv_types.h"
#include "condor.h"
#include "condor_ssv_lib.h"
#include "ssv_terminal.h"

#include "regs/chip_reg.h"

#if   defined ( __CC_ARM )
#define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
#define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */
#define __STATIC_INLINE  static __inline

#elif defined ( __GNUC__ )
#define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
#define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */
#define __STATIC_INLINE  static inline

#elif defined ( __ICCARM__ )
#define __ASM            __asm                                      /*!< asm keyword for IAR Compiler          */
#define __INLINE         inline                                     /*!< inline keyword for IAR Compiler. Only available in High optimization mode! */
#define __STATIC_INLINE  static inline

#elif defined ( __TMS470__ )
#define __ASM            __asm                                      /*!< asm keyword for TI CCS Compiler       */
#define __STATIC_INLINE  static inline

#elif defined ( __TASKING__ )
#define __ASM            __asm                                      /*!< asm keyword for TASKING Compiler      */
#define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler   */
#define __STATIC_INLINE  static inline

#elif defined ( __CSMC__ )
#define __packed
#define __ASM            _asm                                      /*!< asm keyword for COSMIC Compiler      */
#define __INLINE         inline                                    /*use -pc99 on compile line !< inline keyword for COSMIC Compiler   */
#define __STATIC_INLINE  static inline

#endif

#ifdef __cplusplus
extern "C" {
#endif

    enum PIN_MODE
    {
        PIN_MODE_DEFAULT        = 0,        /**< Set Pin to default */
        PIN_MODE_GPIO           = 10,       /**< Gpio mode */
        PIN_MODE_PERIPHERAL     = 2,        /**< default Peripheral select mode */
        PIN_MODE_PERIPHERAL_EX  = 3,        /**< default Peripheral select exchange mode */
        PIN_MODE_PWM            = 4,        /**< special peripheral */
        PIN_MODE_ZSTATE         = 15,       /**< ZState */
    };


#define GPIO_MAX_PIN    (20)

    enum PIN_NAME
    {
        PIN_INT1            = 0,
        PIN_INT0            = 1,
        PIN_CMIF0           = 2,
        PIN_CMIF1           = 3,
        PIN_CMIF2           = 4,
        PIN_CMIF3           = 5,
        PIN_SPIFLASH_MISO   = 6,
        PIN_SPIFLASH_CLK    = 7,
        PIN_SPIFLASH_HOLD   = 8,
        PIN_I2C_SDA         = 9,
        PIN_I2C_SCL         = 10,
        PIN_I2C_SLAVE_SDA   = 11,
        PIN_I2C_SLAVE_SCL   = 12,
        PIN_UART_2W_TXD     = 13,
        PIN_UART_2W_RXD     = 14,
        PIN_SPIFLASH_CS     = 15,
        PIN_SPIFLASH_MOSI   = 16,
        PIN_SPIFLASH_WP     = 17,
        PIN_DBG_TX          = 18,
        PIN_DBG_RX          = 19,
    };

    enum PIN_IO
    {
        // i2c 0 master
        PIN_I2C_0_SCL       =  0,                      /**< IO pin setup to I2C 0 SCL */
        PIN_I2C_0_SDA       =  1,                      /**< IO pin setup to I2C 0 SDA */
        // uart 0
        PIN_UART_0_CTS      =  4,                      /**< IO pin setup to UART 0 CTS */
        PIN_UART_0_RXD      =  5,                      /**< IO pin setup to UART 0 RXD */
        PIN_UART_0_TXD      =  6,                      /**< IO pin setup to UART 0 TXD */
        PIN_UART_0_RTS      =  7,                      /**< IO pin setup to UART 0 RTS */
        // uart 1
        PIN_UART_1_RXD	    =  9,                      /**< IO pin setup to UART 1 RXD */
        // CSN_FLS
        PIN_CSN_FLS	        = 10,                      /**< IO pin setup to Flash CSN */
        // SPI
        PIN_SPI_NC	        = 11,                      /**< IO pin setup to SPI NC */
        PIN_SPI_CLK	        = 12,                      /**< IO pin setup to SPI CLK */
        PIN_SPI_MOSI	    = 13,                      /**< IO pin setup to SPI MOSI */
        PIN_SPI_WP	        = 14,                      /**< IO pin setup to SPI WP */
        PIN_SPI_MISO	    = 15,                      /**< IO pin setup to SPI MISO */

        // uart 1
        PIN_UART_1_TXD	    = 16,                      /**< IO pin setup to UART 1 TX */

        // SPI 0
        PIN_SPI_0_M_CSN	    = 18,                      /**< IO pin setup to SPI 0 Master Chip Select N */
        PIN_SPI_0_M_CLK	    = 19,                      /**< IO pin setup to SPI 0 Master Clock */
        PIN_SPI_0_M_MOSI	= 20,                      /**< IO pin setup to SPI 0 Master MOSI */
        PIN_SPI_0_M_MISO	= 21,                      /**< IO pin setup to SPI 0 Master MISO */
        // LED
        PIN_LED	            = 26,                      /**< IO pin setup to LED */

        PIN_IO_MAX,
    };

    enum GPIO_DIR
    {
        GPIO_DIR_IN,
        GPIO_DIR_OUT,
        GPIO_DIR_MAX,
    };

    enum GPIO_CFG
    {
        GPIO_CFG_PULL_UP,
        GPIO_CFG_PULL_DOWN,
        GPIO_CFG_PULL_NONE,
    };

    enum GPIO_LOGIC
    {
        GPIO_LOGIC_LOW    = 0,
        GPIO_LOGIC_HIGH   = 1,
    };

    /*
    volatile uint32_t * const g_gpio_cfg_arr[] = {
        (volatile uint32_t *)0x00c01100, //int1
        (volatile uint32_t *)0x00c01104, //int0
        (volatile uint32_t *)0x00c01108, //cmif0
        (volatile uint32_t *)0x00c0110c, //cmif1
        (volatile uint32_t *)0x00c01110, //cmif2
        (volatile uint32_t *)0x00c01114, //cmif3
        (volatile uint32_t *)0x00c01124, //i2c0
        (volatile uint32_t *)0x00c01128, //i2c1
        (volatile uint32_t *)0x00c01134, //uart0
        (volatile uint32_t *)0x00c01138, //uart1
        (volatile uint32_t *)0x00c01148, //dbg1
        (volatile uint32_t *)0x00c0114c, //dbg0
    };
     */

     /**
      * @brief setup gpio mode.
      *
      * setup gpio mode.
      *
      * @param pin pin number.
      * @param mode set the pin mode.
      *
      */
    SSV_API void __STATIC_INLINE set_gpio_mode(u8 pin, enum PIN_MODE mode)
    {
        ASSERT(pin < GPIO_MAX_PIN); /* aMH TODO: not implement pwm mode. must remove in the future. */
        ASSERT(mode <= PIN_MODE_ZSTATE); /* aMH TODO: not implement pwm mode. must remove in the future. */
        if (mode == PIN_MODE_ZSTATE)
        {
            //mode = PIN_MODE_GPIO;
            CONDOR_GPIO_REG->PAD_IO[pin] = PIN_MODE_GPIO;
        } else
        //if ((mode == PIN_MODE_GPIO) || (mode == PIN_MODE_PWM) || (mode == PIN_MODE_PERIPHERAL) || (mode == PIN_MODE_DEFAULT))
        {

            //CONDOR_GPIO_REG->PAD_IO_b[pin].SEL_I = mode;
            //CONDOR_GPIO_REG->PAD_IO_b[pin].PAD_IO_00_SEL_OE = 0;
            //CONDOR_GPIO_REG->PAD_IO[pin] = PIN_MODE_GPIO << GPIO_REG_PAD_IO_SEL_I_Pos;
            //*g_gpio_cfg_arr[pin] = 0xa0a0;
            CONDOR_GPIO_REG->PAD_IO_b[pin].SEL = mode;
        }
        //if (mode == PIN_MODE_ZSTATE)
        {
            //CONDOR_GPIO_REG->PAD_IO[pin] = PIN_MODE_GPIO << GPIO_REG_PAD_IO_SEL_Pos;
            /*
            CONDOR_GPIO_REG->PAD_IO_b[pin].SEL = PIN_MODE_GPIO;
            CONDOR_GPIO_REG->PAD_IO_b[pin].OE = 0;
            CONDOR_GPIO_REG->PAD_IO_b[pin].PUE = 0;
            CONDOR_GPIO_REG->PAD_IO_b[pin].PDE = 0;
            CONDOR_GPIO_REG->PAD_IO_b[pin].IE = 0;
            CONDOR_GPIO_REG->PAD_IO_b[pin].DS = 0;
             */
            //*g_gpio_cfg_arr[pin] = 0xf0f0;
            //CONDOR_GPIO_REG->PAD_IO[pin] = PIN_MODE_ZSTATE << GPIO_REG_PAD_IO_SEL_O_Pos;
            //CONDOR_GPIO_REG_ALL->PAD_SEP_OES &= ~(0x01 << pin);
            //CONDOR_GPIO_REG_ALL->PAD_SEP_PUES &= ~(0x01 << pin);
            //CONDOR_GPIO_REG_ALL->PAD_SEP_PDES &= ~(0x01 << pin);
        }
    }

    /**
     * @brief set io pin to peripheral.
     *
     * set io pin to peripheral
     *
     * @param pin pin number.
     * @param mode peripheral.
     * @warning the pin cannot assign multi-mode.
     *
     */
    SSV_API void __STATIC_INLINE set_gpio_io(u8 pin, enum PIN_IO mode)
    {
        // aMH Todo: PAD_IO modify this code to only one access.
        //ASSERT(mode < PIN_IO_MAX);  /* This must one of peripheral */
        // aMH todo : need implement.
        ASSERT(false); // wait for new design.
        //CONDOR_GPIO_REG->PAD_IO_b[pin].SEL_I = CONDOR_GPIO_REG->PAD_IO_b[pin].SEL_O = 0x01;
        //CONDOR_GPIO_REG->PAD_IO_b[pin].PAD_IO_00_SEL_OE = 1;
        //CONDOR_GPIO_REG_ALL->PAD_SEP_IES |= (0x01 << pin);
        //CONDOR_GPIO_EX->FUNC_PIN[mode] = 0x01 << pin;
    }

    /**
     * @brief set gpio direction.
     *
     * set gpio direction.
     *
     * @param pin pin number.
     * @param dir the gpio direction.
     *
     */
    SSV_API void __STATIC_INLINE set_gpio_dir(u8 pin, enum GPIO_DIR dir)
    {
        ASSERT(dir < GPIO_DIR_MAX);
        if (dir == GPIO_DIR_IN)
        {
            CONDOR_GPIO_REG->PAD_IO_b[pin].IE = 1;
            CONDOR_GPIO_REG->PAD_IO_b[pin].OE = 0;
            //CONDOR_GPIO_REG_ALL->PAD_SEP_OES &= ~(0x01 << pin);
            //CONDOR_GPIO_REG_ALL->PAD_SEP_IES |= (0x01 << pin);
        }
        else
        {
            CONDOR_GPIO_REG->PAD_IO_b[pin].OE = 1;
            //CONDOR_GPIO_REG_ALL->PAD_SEP_OES |= (0x01 << pin);
            ///* aMH TODO: check does it always input? */
            //CONDOR_GPIO_REG_ALL->PAD_SEP_IES |= (0x01 << pin);
        }
    }

    /**
     * @brief setup gpio input pull down or pull up or none.
     *
     * setup gpio input pull down or pull up or none.
     *
     * @param pin pin number
     * @param cfg GPIO input status.
     *
     */
    SSV_API void __STATIC_INLINE set_gpio_cfg(u8 pin, enum GPIO_CFG cfg)
    {
        if (cfg == GPIO_CFG_PULL_UP)
        {
            CONDOR_GPIO_REG->PAD_IO_b[pin].PDE = 0;
            CONDOR_GPIO_REG->PAD_IO_b[pin].PUE = 1;
            //CONDOR_GPIO_REG_ALL->PAD_SEP_PDES &= ~(0x01 << pin);
            //CONDOR_GPIO_REG_ALL->PAD_SEP_PUES |= 0x01 << pin;
        } else if (cfg == GPIO_CFG_PULL_DOWN)
        {
            CONDOR_GPIO_REG->PAD_IO_b[pin].PUE = 0;
            CONDOR_GPIO_REG->PAD_IO_b[pin].PDE = 1;
            //CONDOR_GPIO_REG_ALL->PAD_SEP_PUES &= ~(0x01 << pin);
            //CONDOR_GPIO_REG_ALL->PAD_SEP_PDES |= 0x01 << pin;
        } else if (cfg == GPIO_CFG_PULL_NONE)
        {
            CONDOR_GPIO_REG->PAD_IO_b[pin].PUE = 0;
            CONDOR_GPIO_REG->PAD_IO_b[pin].PDE = 0;
            //CONDOR_GPIO_REG_ALL->PAD_SEP_PUES &= ~(0x01 << pin);
            //CONDOR_GPIO_REG_ALL->PAD_SEP_PDES &= ~(0x01 << pin);
        }
    }

    /**
     * @brief gpio output logic
     *
     * setup the gpio output is high or low.
     *
     * @param pin pin number
     * @param logic high or log.
     *
     */
    SSV_API void __STATIC_INLINE set_gpio(u8 pin, enum GPIO_LOGIC logic)
    {
        if (logic == GPIO_LOGIC_LOW)
        {
            CONDOR_CSR_PAD_MUX_REG->PAD_MUX_OD_GROUP &= ~(0x01 << pin);
            //CONDOR_GPIO_REG_ALL->PAD_SEP_ODS &= ~(0x01 << pin);
        } else
        {
            CONDOR_CSR_PAD_MUX_REG->PAD_MUX_OD_GROUP |= (0x01 << pin);
            //CONDOR_GPIO_REG_ALL->PAD_SEP_ODS |= 0x01 << pin;
        }
    }

    /**
     * @brief get gpio status.
     *
     * get gpio logic.
     *
     * @param pin pin number
     * @return the pin logic.
     *
     */
    SSV_API enum GPIO_LOGIC __STATIC_INLINE get_gpio(u8 pin)
    {
        return (CONDOR_CSR_PAD_MUX_REG->PAD_MUX_ID_GROUP & 0x01 << pin) != 0?GPIO_LOGIC_HIGH:GPIO_LOGIC_LOW;
    }


    extern SSV_API void reset_gpio_exchange();

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: DRV_GPIO_H */
