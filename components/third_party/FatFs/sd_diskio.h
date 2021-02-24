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
#ifndef _SD_DISKIO_H_
#define _SD_DISKIO_H_

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
 
void sd_spi_driver_init(void);

int sd_disk_initialize();
int sd_disk_status();
int sd_disk_read(uint8_t* buffer, uint32_t block_number, uint32_t count);
int sd_disk_write(uint8_t* buffer, uint32_t block_number, uint32_t count);
int sd_disk_sync();
uint32_t sd_disk_sectors();

#endif
