/* mbed Microcontroller Library
 * Copyright (c) 2006-2012 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef _NAND_FLASH_H_
#define _NAND_FLASH_H_

//#include "mbed.h"
//#include "FATFileSystem.h"
#include <stdint.h>
#include <gpio/drv_gpio.h>
//#include "spimst/drv_spimst.h"

//#define SPI_CS_H()			drv_gpio_set_logic(GPIO_13, GPIO_LOGIC_HIGH)
//#define SPI_CS_L()			drv_gpio_set_logic(GPIO_13, GPIO_LOGIC_LOW)

//#define SPI_CS_H()			drv_gpio_set_logic(GPIO_11, GPIO_LOGIC_HIGH)
//#define SPI_CS_L()			drv_gpio_set_logic(GPIO_11, GPIO_LOGIC_LOW)

#define SPI_CS_H()			
#define SPI_CS_L()


#define SPI_MOSI_H()		drv_gpio_set_logic(GPIO_12, GPIO_LOGIC_HIGH)
#define SPI_MOSI_L()		drv_gpio_set_logic(GPIO_12, GPIO_LOGIC_LOW)

#define SPI_SCK_H()			drv_gpio_set_logic(GPIO_08, GPIO_LOGIC_HIGH)
#define SPI_SCK_L()			drv_gpio_set_logic(GPIO_08, GPIO_LOGIC_LOW)

#define SPI_MISO_Read()		drv_gpio_get_logic(GPIO_10)

/** Access the filesystem on an SD Card using SPI
 *
 * @code
 * #include "mbed.h"
 * #include "SDFileSystem.h"
 *
 * SDFileSystem sd(p5, p6, p7, p12, "sd"); // mosi, miso, sclk, cs
 *
 * int main() {
 *     FILE *fp = fopen("/sd/myfile.txt", "w");
 *     fprintf(fp, "Hello World!\n");
 *     fclose(fp);
 * }
 */


#define SPI_FLASH_PageSize        2048
#define Dummy_Byte                0xA5


#define SPI_FLASH_CS_LOW()        drv_gpio_set_logic(GPIO_11, GPIO_LOGIC_LOW)
#define SPI_FLASH_CS_HIGH()       drv_gpio_set_logic(GPIO_11, GPIO_LOGIC_HIGH)

    

#define STATUS_BLOCK_LOCK_BRWD		(1<<7)
#define STATUS_BLOCK_LOCK_NON		(1<<6)
#define STATUS_BLOCK_LOCK_BP2		(1<<5)
#define STATUS_BLOCK_LOCK_BP1		(1<<4)
#define STATUS_BLOCK_LOCK_BP0		(1<<3)
#define STATUS_BLOCK_LOCK_INV		(1<<2)
#define STATUS_BLOCK_LOCK_CMP		(1<<1)
#define STATUS_BLOCK_LOCK_NON		(1<<0)

#define STATUS_OTP_PRT		(1<<7)
#define STATUS_OTP_EN		(1<<6)
#define STATUS_OTP_NON		(1<<5)
#define STATUS_OTP_ECC_EN	(1<<4)
#define STATUS_OTP_NON		(1<<3)
#define STATUS_OTP_NON		(1<<2)
#define STATUS_OTP_NON		(1<<1)
#define STATUS_OTP_QE		(1<<0)

#define STATUS_ST_NON		(1<<7)
#define STATUS_ST_NON		(1<<6)
#define STATUS_ST_ECCS1		(1<<5)
#define STATUS_ST_ECCS0		(1<<4)
#define STATUS_ST_P_FAIL	(1<<3)
#define STATUS_ST_E_FAIL	(1<<2)
#define STATUS_ST_WEL		(1<<1)
#define STATUS_ST_OIP		(1<<0)



#define WriteEnable               0x06       //Ð´Ê¹ÄÜ£¬ÉèÖÃ×´Ì¬¼Ä´æÆ÷
#define WriteDisable              0x04       //Ð´½ûÖ¹
#define ReadStatusRegister        0x0F       //¶Á×´Ì¬¼Ä´æÆ÷
#define WriteStatusRegister       0x1F       //Ð´×´Ì¬¼Ä´æÆ÷

//read data
#define PageToCache					0x13
#define CacheOutput					0x0B

//write data
#define Page_Program              0x02       //Ò³Ãæ±à³Ì--Ð´Êý¾Ý
#define Page_Program_Exe			0x10

#define BlockErace                0xD8       //¿é²Á³ý

#define ReadDeviceID              0x9F      //ÍË³öµôµçÄ£Ê½¡¢Éè±¸IDÐÅÏ¢


void SPI_FLASH_Init(void);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WriteDisable(void);
//read register
uint8_t SPI_Flash_ReadStatusRegister(void);
uint8_t SPI_Flash_ReadOtpRegister();
uint8_t SPI_Flash_ReadBlockLockRegister();
uint8_t SPI_FLASH_WaitForFlag(uint8_t flag,uint8_t expect_flag);

//write register
void SPI_Flash_WriteStatusRegister(uint8_t Byte);
void SPI_Flash_WriteOtpRegister(uint8_t Byte);
void SPI_Flash_WriteBlockLockRegister(uint8_t Byte);

//byte opt
uint8_t SPI_FLASH_ReceiveByte(void);
uint8_t SPI_FLASH_SendByte(uint8_t byte);

//read
uint32_t SPI_FLASH_PageRead(uint8_t *pBuffer, uint32_t ReadAddr);

//erase
uint8_t SPI_FLASH_BulkErase(uint32_t BlockAddr);
uint8_t SPI_FLASH_ReadDeviceID(void);

//write
uint8_t SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr);

void sd_spi_driver_init(void);

int sd_disk_initialize();
int sd_disk_status();
int sd_disk_read(uint8_t* buffer, uint32_t block_number, uint32_t count);
int sd_disk_write(const uint8_t* buffer, uint32_t block_number, uint32_t count);
int sd_disk_sync();
uint32_t sd_disk_sectors();



#endif
