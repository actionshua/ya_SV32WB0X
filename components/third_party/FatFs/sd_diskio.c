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
/* Introduction
 * ------------
 * SD and MMC cards support a number of interfaces, but common to them all
 * is one based on SPI. This is the one I'm implmenting because it means
 * it is much more portable even though not so performant, and we already
 * have the mbed SPI Interface!
 *
 * The main reference I'm using is Chapter 7, "SPI Mode" of:
 *  http://www.sdcard.org/developers/tech/sdcard/pls/Simplified_Physical_Layer_Spec.pdf
 *
 * SPI Startup
 * -----------
 * The SD card powers up in SD mode. The SPI interface mode is selected by
 * asserting CS low and sending the reset command (CMD0). The card will
 * respond with a (R1) response.
 *
 * CMD8 is optionally sent to determine the voltage range supported, and
 * indirectly determine whether it is a version 1.x SD/non-SD card or
 * version 2.x. I'll just ignore this for now.
 *
 * ACMD41 is repeatedly issued to initialise the card, until "in idle"
 * (bit 0) of the R1 response goes to '0', indicating it is initialised.
 *
 * You should also indicate whether the host supports High Capicity cards,
 * and check whether the card is high capacity - i'll also ignore this
 *
 * SPI Protocol
 * ------------
 * The SD SPI protocol is based on transactions made up of 8-bit words, with
 * the host starting every bus transaction by asserting the CS signal low. The
 * card always responds to commands, data blocks and errors.
 *
 * The protocol supports a CRC, but by default it is off (except for the
 * first reset CMD0, where the CRC can just be pre-calculated, and CMD8)
 * I'll leave the CRC off I think!
 *
 * Standard capacity cards have variable data block sizes, whereas High
 * Capacity cards fix the size of data block to 512 bytes. I'll therefore
 * just always use the Standard Capacity cards with a block size of 512 bytes.
 * This is set with CMD16.
 *
 * You can read and write single blocks (CMD17, CMD25) or multiple blocks
 * (CMD18, CMD25). For simplicity, I'll just use single block accesses. When
 * the card gets a read command, it responds with a response token, and then
 * a data token or an error.
 *
 * SPI Command Format
 * ------------------
 * Commands are 6-bytes long, containing the command, 32-bit argument, and CRC.
 *
 * +---------------+------------+------------+-----------+----------+--------------+
 * | 01 | cmd[5:0] | arg[31:24] | arg[23:16] | arg[15:8] | arg[7:0] | crc[6:0] | 1 |
 * +---------------+------------+------------+-----------+----------+--------------+
 *
 * As I'm not using CRC, I can fix that byte to what is needed for CMD0 (0x95)
 *
 * All Application Specific commands shall be preceded with APP_CMD (CMD55).
 *
 * SPI Response Format
 * -------------------
 * The main response format (R1) is a status byte (normally zero). Key flags:
 *  idle - 1 if the card is in an idle state/initialising
 *  cmd  - 1 if an illegal command code was detected
 *
 *    +-------------------------------------------------+
 * R1 | 0 | arg | addr | seq | crc | cmd | erase | idle |
 *    +-------------------------------------------------+
 *
 * R1b is the same, except it is followed by a busy signal (zeros) until
 * the first non-zero byte when it is ready again.
 *
 * Data Response Token
 * -------------------
 * Every data block written to the card is acknowledged by a byte
 * response token
 *
 * +----------------------+
 * | xxx | 0 | status | 1 |
 * +----------------------+
 *              010 - OK!
 *              101 - CRC Error
 *              110 - Write Error
 *
 * Single Block Read and Write
 * ---------------------------
 *
 * Block transfers have a byte header, followed by the data, followed
 * by a 16-bit CRC. In our case, the data will always be 512 bytes.
 *
 * +------+---------+---------+- -  - -+---------+-----------+----------+
 * | 0xFE | data[0] | data[1] |        | data[n] | crc[15:8] | crc[7:0] |
 * +------+---------+---------+- -  - -+---------+-----------+----------+
 */
//#include "SDFileSystem.h"
//#include "mbed_debug.h"
#include "stdio.h"
#include "string.h"
#include "osal.h"
#include "sd_diskio.h"
#include "hal_pinmux.h"
#include "drv_pinmux.h"
#include "drv_spimst.h"
#include "ff.h"
#include "fsal_evt.h"
#include "sdc_param.h"

extern OsMutex fsalMutex;

static unsigned int _sectors;
static unsigned int _init_sck;
static unsigned int _transfer_sck;
static int cdv;
static int _is_initialized;
static unsigned int _spi_sck_speed;
static uint8_t tmp[512]; //dummy tmp_send, TODO: dynamic allocate buf or optimize spi transfer function
static OsTimer sdc_detect_timer;
static FATFS fs;
static uint8_t sdc_readonly = 0;
static gpio_logic_t last_stable_val = -1;

void (*sdc_evthandler)(SSV_FS_EVENT) = NULL;

//#define USE_GPIO
int _cmd(int cmd, int arg);
int _cmdx(int cmd, int arg);
int _cmd8();
int _cmd58();
int initialise_card();
int initialise_card_v1();
int initialise_card_v2();

int _read(uint8_t * buffer, uint32_t length);
int _write(uint8_t *buffer, uint32_t length);
uint32_t _sd_sectors();
int _write_multiple(uint8_t*buffer, uint32_t length);
	
void irq_sdc_detect(uint32_t irq_num);

static void _spi_frequency(unsigned int hz)
{
	if(_spi_sck_speed != 0)
	{
		drv_spimst_deinit_ex(SDC_SPI_MST_CHOICE);
	}
	_spi_sck_speed = hz;
	drv_spimst_init_ex(SDC_SPI_MST_CHOICE, hz, SDC_SPI_MST_PHASE, SDC_SPI_MST_POLARITY);
#if(CHIP_ID==6020)
	//Do something
#endif
	printf("set hz %d\n",hz);
}

static int32_t	_sdc_mount(void) {
    FRESULT res;

    res = f_mount(&fs, "", 1); // mount fs immediately
    if(res)
    {
        printf("f mount fail! res=%d\n", res);
    } else {
        printf("f mount ok\n");
    }

    return (int32_t)res;
}

static int32_t	_sdc_umount(void) {
    FRESULT res;

    res = f_mount(NULL, "", 0); // umount fs
    if(res)
    {
        printf("f umount fail! res=%d\n", res);
    } else {
        printf("f umount ok\n");
    }

    return (int32_t)res;
}

static void sdc_debouncing(OsTimer data)
{
	gpio_logic_t curr_val, last_val = drv_gpio_get_logic(SDC_CD_PIN);
	int stable_cnt = 0;

	do {
		curr_val = drv_gpio_get_logic(SDC_CD_PIN);
		//printf("%s: %d: %s(): curr_val=%d\n", __FILE__, __LINE__, __func__, curr_val);
		if (curr_val == last_val) {
			stable_cnt++;
		} else {
			last_val = curr_val;
			stable_cnt = 0;
		}
		OS_MsDelay(1);
	} while (stable_cnt < SDC_DEBOUNCE_CNT);

	if (curr_val == last_stable_val) {
		/* Ignore this abnormal interrupt */
		drv_gpio_register_isr(SDC_CD_PIN, irq_sdc_detect);
		return;
	} else {
		last_stable_val = curr_val;
	}

	if (curr_val == GPIO_LOGIC_HIGH) {//Unplugged
		drv_gpio_intc_trigger_mode(SDC_CD_PIN, GPIO_INTC_FALLING_EDGE);
                OS_MutexLock(fsalMutex);
                _sdc_umount();
                OS_MutexUnLock(fsalMutex);
		if (_is_initialized && sdc_evthandler) {
			sdc_evthandler(SSV_SDC_UNPLUG);
		}
                OS_MutexLock(fsalMutex);
		_is_initialized = 0;
                OS_MutexUnLock(fsalMutex);
	} else {//Plugged in
		drv_gpio_intc_trigger_mode(SDC_CD_PIN, GPIO_INTC_RISING_EDGE);
                OS_MutexLock(fsalMutex);
                _sdc_mount();
                OS_MutexUnLock(fsalMutex);
#if defined(SDC_WP_PIN)
        	//printf("%s: %d: %s(): write protect=%d\n", __FILE__, __LINE__, __func__, drv_gpio_get_logic(SDC_WP_PIN));
		if (drv_gpio_get_logic(SDC_WP_PIN) == GPIO_LOGIC_HIGH) {
			sdc_readonly = 1;
		} else {
			sdc_readonly = 0;
		}
#endif
		if (_is_initialized && sdc_evthandler) {
			sdc_evthandler(SSV_SDC_PLUGIN);
		}
	}
	drv_gpio_register_isr(SDC_CD_PIN, irq_sdc_detect);
}

void irq_sdc_detect(uint32_t irq_num)
{
	drv_gpio_register_isr(SDC_CD_PIN, NULL);

	OS_TimerStop(sdc_detect_timer);
	OS_TimerStart(sdc_detect_timer);

	drv_gpio_intc_clear(irq_num);
}

#ifdef USE_GPIO
inline void _spi_speed_delay(unsigned int delay)
{
	//OS_MsDelay(delay);
	OS_UsDelay(delay);
}

static unsigned char _spi_write(unsigned char value)
{
	uint8_t i=8;
	while(i--)
	{
		if(value & 0x80)
			SPI_MOSI_H();
		else
			SPI_MOSI_L();
		SPI_SCK_L();
		_spi_speed_delay(_spi_sck_speed);
		SPI_SCK_H();
		_spi_speed_delay(_spi_sck_speed);
		value <<= 1;
		if(SPI_MISO_Read())
		{
			value |= 0x01;
		}
	}
	SPI_SCK_L();
	return value;
}


static void drv_init()
{
	//clk
	drv_gpio_set_mode(GPIO_08, PIN_MODE_GPIO);
	drv_gpio_set_dir(GPIO_08, GPIO_DIR_OUT);

	//cs
	drv_gpio_set_mode(GPIO_11, PIN_MODE_GPIO);
	drv_gpio_set_dir(GPIO_11, GPIO_DIR_OUT);


	//MISO
	drv_gpio_set_mode(GPIO_10, PIN_MODE_GPIO);
	drv_gpio_set_dir(GPIO_10, GPIO_DIR_IN);

	//MOSI
	drv_gpio_set_mode(GPIO_12, PIN_MODE_GPIO);
	drv_gpio_set_dir(GPIO_12, GPIO_DIR_OUT);

#if defined(SDC_WP_PIN)
	drv_gpio_set_mode(SDC_WP_PIN, PIN_MODE_GPIO);
	drv_gpio_set_dir(SDC_WP_PIN, GPIO_DIR_IN);
	drv_gpio_set_pull(SDC_WP_PIN, GPIO_PULL_UP);
#endif

	//Set card detect GPIO
	drv_gpio_set_mode(SDC_CD_PIN, PIN_MODE_GPIO);
	drv_gpio_set_dir(SDC_CD_PIN, GPIO_DIR_IN);
	drv_gpio_set_pull(SDC_CD_PIN, GPIO_PULL_UP);
	if (drv_gpio_get_logic(SDC_CD_PIN) == GPIO_LOGIC_HIGH) {//No card plugged in, so detect card plugging
        	//printf("%s: %d: %s(): set FALLING_EDGE\n", __FILE__, __LINE__, __func__);
		drv_gpio_intc_trigger_mode(SDC_CD_PIN, GPIO_INTC_FALLING_EDGE);
	} else {//One card already plugged in, so detect card removing
        	//printf("%s: %d: %s(): set LOW_LEVEL\n", __FILE__, __LINE__, __func__);
		drv_gpio_intc_trigger_mode(SDC_CD_PIN, GPIO_INTC_LOW_LEVEL);/* Set low level trigger for the first mount */
	}
	OS_TimerCreate(&sdc_detect_timer,SDC_DEBOUNCE_TIME,0,0,sdc_debouncing);
	drv_gpio_register_isr(SDC_CD_PIN, irq_sdc_detect);
}

#else
extern int8_t drv_spimst_trx_ex(drv_spimst_port port, uint8_t *write_data, uint8_t *read_data, uint32_t length, uint32_t csn);
static unsigned char _spi_write(unsigned char value)
{
	unsigned char ret_value;
        int8_t ret;
#if(CHIP_ID==6006)
	ret = drv_spimst_trx_ex(SDC_SPI_MST_CHOICE, &value, &ret_value, sizeof(char), SDC_CSN_PIN);
#elif(CHIP_ID==6020)
	ret = drv_spimst_trx_ex(SDC_SPI_MST_CHOICE, &value, &ret_value, sizeof(char), SDC_CSN_PIN);
#else
	#error not support CHIP_ID
#endif
	if (ret != 0) {
		printf("%s: %d: %s():ret=%d\n", __FILE__, __LINE__, __func__, ret);
	}

	return ret_value;
}

static void drv_init()
{
	//spi ex cs test pin
	drv_gpio_set_mode(SDC_CSN_PIN, PIN_MODE_GPIO);
	drv_gpio_set_dir(SDC_CSN_PIN, GPIO_DIR_OUT);
	//drv_pinmux_manual_function_select_enable(SEL_SPI_MST);

#if defined(SDC_WP_PIN)
	drv_gpio_set_mode(SDC_WP_PIN, PIN_MODE_GPIO);
	drv_gpio_set_dir(SDC_WP_PIN, GPIO_DIR_IN);
	drv_gpio_set_pull(SDC_WP_PIN, GPIO_PULL_UP);
#endif

	//Set card detect GPIO
	drv_gpio_set_mode(SDC_CD_PIN, PIN_MODE_GPIO);
	drv_gpio_set_dir(SDC_CD_PIN, GPIO_DIR_IN);
	drv_gpio_set_pull(SDC_CD_PIN, GPIO_PULL_UP);
	if (drv_gpio_get_logic(SDC_CD_PIN) == GPIO_LOGIC_HIGH) {//No card plugged in, so detect card plugging
        	//printf("%s: %d: %s(): set FALLING_EDGE\n", __FILE__, __LINE__, __func__);
		drv_gpio_intc_trigger_mode(SDC_CD_PIN, GPIO_INTC_FALLING_EDGE);
	} else {//One card already plugged in, so detect card removing
        	//printf("%s: %d: %s(): set LOW_LEVEL\n", __FILE__, __LINE__, __func__);
		drv_gpio_intc_trigger_mode(SDC_CD_PIN, GPIO_INTC_LOW_LEVEL);/* Set low level trigger for the first mount */
	}
	OS_TimerCreate(&sdc_detect_timer,1,0,0,sdc_debouncing);
	//OS_TimerStart(sdc_detect_timer);
	drv_gpio_register_isr(SDC_CD_PIN, irq_sdc_detect);

}

#endif


#define SD_COMMAND_TIMEOUT 10000
#define SD_INIT_V2_TIMEOUT 100

void sd_spi_driver_init(void)
{
	drv_init();

	SPI_CS_H();
	_is_initialized = 0;
	_init_sck = 400*1000;//400k
	_transfer_sck = 40*1000*1000;//40M

/*
        *(unsigned int *)(0xc0000700) = 0x464000;
        *(unsigned int *)(0xc0000760) = 0x4000;
        *(unsigned int *)(0xc0000754) = 0x20000;
        *(unsigned int *)(0xc0000758) = 0x40000;
        *(unsigned int *)(0xc000075c) = 0x400000;
*/
}

#define R1_IDLE_STATE           (1 << 0)
#define R1_ERASE_RESET          (1 << 1)
#define R1_ILLEGAL_COMMAND      (1 << 2)
#define R1_COM_CRC_ERROR        (1 << 3)
#define R1_ERASE_SEQUENCE_ERROR (1 << 4)
#define R1_ADDRESS_ERROR        (1 << 5)
#define R1_PARAMETER_ERROR      (1 << 6)

// Types
//  - v1.x Standard Capacity
//  - v2.x Standard Capacity
//  - v2.x High Capacity
//  - Not recognised as an SD Card
#define SDCARD_FAIL 0
#define SDCARD_V1   1
#define SDCARD_V2   2
#define SDCARD_V2HC 3

int initialise_card() {
    // Set to SCK for initialisation, and clock card with cs = 1
    _spi_frequency(_init_sck);
    SPI_CS_H();
    for (int i = 0; i < 16; i++) {
        _spi_write(0xFF);
    }

    // send CMD0, should return with all zeros except IDLE STATE set (bit 0)
    if (_cmd(0, 0) != R1_IDLE_STATE) {
        printf("No disk, or could not put SD card in to SPI idle state\n");
        return SDCARD_FAIL;
    }

    // send CMD8 to determine whther it is ver 2.x
    int r = _cmd8();
    if (r == R1_IDLE_STATE) {
        return initialise_card_v2();
    } else if (r == (R1_IDLE_STATE | R1_ILLEGAL_COMMAND)) {
        return initialise_card_v1();
    } else {
        printf("Not in idle state after sending CMD8 (not an SD card?)\n");
        return SDCARD_FAIL;
    }
}

int initialise_card_v1() {
    for (int i = 0; i < SD_COMMAND_TIMEOUT; i++) {
        _cmd(55, 0);
        if (_cmd(41, 0) == 0) {
            cdv = 512;
            printf("\n\rInit: SDCARD_V1\n\r");
            return SDCARD_V1;
        }
    }

    printf("Timeout waiting for v1.x card\n");
    return SDCARD_FAIL;
}

int initialise_card_v2() {
    for (int i = 0; i < SD_INIT_V2_TIMEOUT; i++) {
        OS_MsDelay(50);
        _cmd58();
        _cmd(55, 0);
        if (_cmd(41, 0x40000000) == 0) {
            _cmd58();
            printf("\n\rInit: SDCARD_V2\n\r");
            cdv = 1;
            return SDCARD_V2;
        }
    }

    printf("Timeout waiting for v2.x card\n");
    return SDCARD_FAIL;
}

int sd_disk_initialize() {
    if (_is_initialized) {
        printf("already initialized\n");
        return 0;
    }
    memset(tmp, 0xff, sizeof(tmp));

    _is_initialized = initialise_card();
    if (_is_initialized == 0) {
        printf("Fail to initialize card\n");
        return 1;
    }
    //OS_MsDelay(500);
    printf("init card = %d\n", _is_initialized);
    _sectors = _sd_sectors();

    // Set block length to 512 (CMD16)
    if (_cmd(16, 512) != 0) {
        printf("Set 512-byte block timed out\n");
        return 1;
    }

    // Set SCK for data transfer
    _spi_frequency(_transfer_sck);
    return 0;
}

#if 0
int sd_disk_write(const uint8_t* buffer, uint32_t block_number, uint32_t count) {
    if (!_is_initialized) {
        return -1;
    }

    for (uint32_t b = block_number; b < block_number + count; b++) {
        // set write address for single block (CMD24)
        if (_cmd(24, b * cdv) != 0) {
            return 1;
        }
        
        // send the data block
        _write(buffer, 512);
        buffer += 512;
    }
    
    return 0;
}
#else
int sd_disk_write(uint8_t* buffer, uint32_t block_number, uint32_t count) {
	uint32_t b = block_number;

	if (!_is_initialized) {
        return -1;
    }

	if (_cmd(25, b * cdv) != 0) {
		return 1;
	}

	SPI_CS_L();


    for (uint32_t b = block_number; b < block_number + count; b++) {
        _spi_write(0xFC);
        // send the data block
        _write_multiple(buffer, 512);
        buffer += 512;
    }

	SPI_CS_L();
	//Stop Tran Taken
	_spi_write(0xFD);

	 // write the checksum
	_spi_write(0xFF);
	_spi_write(0xFF);

	// wait for write to finish
	while (_spi_write(0xFF) == 0);
	SPI_CS_H();

    return 0;
}

#endif




int sd_disk_read_single(uint8_t* buffer, uint32_t block_number, uint32_t count) {
    if (!_is_initialized) {
        return -1;
    }
	
    for (uint32_t b = block_number; b < block_number + count; b++) {
        // set read address for single block (CMD17)
        if (_cmd(17, b * cdv) != 0) {
            return 1;
        }
        
        // receive the data
        _read(buffer, 512);
        buffer += 512;
    }

    return 0;
}

int sd_disk_read_multiple(uint8_t* buffer, uint32_t block_number, uint32_t count) {
    if (!_is_initialized) {
        return -1;
    }

	if (_cmd(18, block_number * cdv) != 0) {
		return 1;
	}

	
	  // read until start byte (0xFF)
	SPI_CS_L();
//	while (_spi_write(0xFF) != 0xFE);
	
    for (uint32_t b = block_number; b < block_number + count; b++) {

        // receive the data
        _read(buffer, 512);
        buffer += 512;
    }
	   
	if (_cmd(12, 0) != 0) {
		   return 1;
	   }

    return 0;
}


int sd_disk_read(uint8_t* buffer, uint32_t block_number, uint32_t count)
{
	if(count == 1)
		return sd_disk_read_single(buffer, block_number, count);
	else
		return sd_disk_read_multiple(buffer, block_number, count);
}


int sd_disk_status() {
    // FATFileSystem::disk_status() returns 0 when initialized
    if (_is_initialized) {
        return 0;
    } else {
        return 1;
    }
}

int sd_disk_sync() { return 0; }
uint32_t sd_disk_sectors() { return _sectors; }


// PRIVATE FUNCTIONS
int _cmd(int cmd, int arg) {
    SPI_CS_L();

    // send a command
    _spi_write(0x40 | cmd);
    _spi_write(arg >> 24);
    _spi_write(arg >> 16);
    _spi_write(arg >> 8);
    _spi_write(arg >> 0);
	_spi_write(0x95);

	if(cmd == 12)
	{
		_spi_write(0xFF);//Skip a stuff byte when stop reading
	}	

    // wait for the repsonse (response[7] == 0)
    for (int i = 0; i < SD_COMMAND_TIMEOUT; i++) {
        int response = _spi_write(0xFF);
        if (!(response & 0x80)) {
            SPI_CS_H();
            _spi_write(0xFF);
            return response;
        }
    }
    SPI_CS_H();
    _spi_write(0xFF);
    return -1; // timeout
}
int _cmdx(int cmd, int arg) {
    SPI_CS_L();

    // send a command
    _spi_write(0x40 | cmd);
    _spi_write(arg >> 24);
    _spi_write(arg >> 16);
    _spi_write(arg >> 8);
    _spi_write(arg >> 0);
    _spi_write(0x95);

    // wait for the repsonse (response[7] == 0)
    for (int i = 0; i < SD_COMMAND_TIMEOUT; i++) {
        int response = _spi_write(0xFF);
        if (!(response & 0x80)) {
            return response;
        }
    }
    SPI_CS_H();
    _spi_write(0xFF);
    return -1; // timeout
}


int _cmd58() {
    SPI_CS_L();
    int arg = 0;

    // send a command
    _spi_write(0x40 | 58);
    _spi_write(arg >> 24);
    _spi_write(arg >> 16);
    _spi_write(arg >> 8);
    _spi_write(arg >> 0);
    _spi_write(0x95);

    // wait for the repsonse (response[7] == 0)
    for (int i = 0; i < SD_COMMAND_TIMEOUT; i++) {
        int response = _spi_write(0xFF);
        if (!(response & 0x80)) {
            int ocr = _spi_write(0xFF) << 24;
            ocr |= _spi_write(0xFF) << 16;
            ocr |= _spi_write(0xFF) << 8;
            ocr |= _spi_write(0xFF) << 0;
            SPI_CS_H();
            _spi_write(0xFF);
            return response;
        }
    }
    SPI_CS_H();
    _spi_write(0xFF);
    return -1; // timeout
}

int _cmd8() {
    SPI_CS_L();

    // send a command
    _spi_write(0x40 | 8); // CMD8
    _spi_write(0x00);     // reserved
    _spi_write(0x00);     // reserved
    _spi_write(0x01);     // 3.3v
    _spi_write(0xAA);     // check pattern
    _spi_write(0x87);     // crc

    // wait for the repsonse (response[7] == 0)
    for (int i = 0; i < SD_COMMAND_TIMEOUT * 1000; i++) {
        char response[5];
        response[0] = _spi_write(0xFF);
        if (!(response[0] & 0x80)) {
            for (int j = 1; j < 5; j++) {
                response[i] = _spi_write(0xFF);
            }
            SPI_CS_H();
            _spi_write(0xFF);
            return response[0];
        }
    }
    SPI_CS_H();
    _spi_write(0xFF);
    return -1; // timeout
}


int _read(uint8_t *buffer, uint32_t length) {
    int8_t ret;
    int timeout_cnt = SD_COMMAND_TIMEOUT;
    SPI_CS_L();

    // read until start byte (0xFE)
    while (_spi_write(0xFF) != 0xFE) {
        if (--timeout_cnt == 0) {
            ret = -1;
            return ret;
        }
    }

//This must be used, otherwise the initialization may be wrong.
    // read data
	if(length != 512 )//for csd read
	{
	    for (uint32_t i = 0; i < length; i++) {
	        buffer[i] = _spi_write(0xFF);
	   }
	}
	else
	{
#if(CHIP_ID==6006)
		ret = drv_spimst_trx_ex(SDC_SPI_MST_CHOICE, &tmp[0], &buffer[0], length, SDC_CSN_PIN);
#elif(CHIP_ID==6020)
		ret = drv_spimst_trx_ex(SDC_SPI_MST_CHOICE, &tmp[0], &buffer[0], length, SDC_CSN_PIN);
#else
		#error not support CHIP_ID
#endif
		if (ret != 0) {
			printf("%s: %d: %s():ret=%d\n", __FILE__, __LINE__, __func__, ret);
		}
	}
    _spi_write(0xFF); // checksum
    _spi_write(0xFF);

    SPI_CS_H();
    _spi_write(0xFF);
    return 0;
}

int _write(uint8_t*buffer, uint32_t length) {
    int8_t ret;
    SPI_CS_L();

    // indicate start of block
    _spi_write(0xFE);

    // write the data
    #if 0
    for (uint32_t i = 0; i < length; i++) {
        _spi_write(buffer[i]);
    }
	#endif
#if(CHIP_ID==6006)
	ret = drv_spimst_trx_ex(SDC_SPI_MST_CHOICE, &buffer[0], &tmp[0], length, SDC_CSN_PIN);
#elif(CHIP_ID==6020)
	ret = drv_spimst_trx_ex(SDC_SPI_MST_CHOICE, &buffer[0], &tmp[0], length, SDC_CSN_PIN);
#else
	#error not support CHIP_ID
#endif
	if (ret != 0) {
		printf("%s: %d: %s():ret=%d\n", __FILE__, __LINE__, __func__, ret);
	}

    // write the checksum
    _spi_write(0xFF);
    _spi_write(0xFF);

    // check the response token
    if ((_spi_write(0xFF) & 0x1F) != 0x05) {
        SPI_CS_H();
        _spi_write(0xFF);
        return 1;
    }

    // wait for write to finish
    while (_spi_write(0xFF) == 0);

    SPI_CS_H();
    _spi_write(0xFF);
    return 0;
}

int _write_multiple(uint8_t*buffer, uint32_t length) {
    int8_t ret;
    SPI_CS_L();

    // write the data
    #if 0
    for (uint32_t i = 0; i < length; i++) {
        _spi_write(buffer[i]);
    }
	#endif
#if(CHIP_ID==6006)
	ret = drv_spimst_trx_ex(SDC_SPI_MST_CHOICE, &buffer[0], tmp, length, SDC_CSN_PIN);
#elif(CHIP_ID==6020)
	ret = drv_spimst_trx_ex(SDC_SPI_MST_CHOICE, &buffer[0], tmp, length, SDC_CSN_PIN);
#else
	#error not support CHIP_ID
#endif
	if (ret != 0) {
		printf("%s: %d: %s():ret=%d\n", __FILE__, __LINE__, __func__, ret);
	}

    // write the checksum
    _spi_write(0xFF);
    _spi_write(0xFF);

    // check the response token
    if ((_spi_write(0xFF) & 0x1F) != 0x05) {
        SPI_CS_H();
        _spi_write(0xFF);
        return 1;
    }

    // wait for write to finish
    while (_spi_write(0xFF) == 0);

    SPI_CS_H();
    _spi_write(0xFF);
    return 0;
}


static uint32_t ext_bits(unsigned char *data, int msb, int lsb) {
    uint32_t bits = 0;
    uint32_t size = 1 + msb - lsb;
    for (uint32_t i = 0; i < size; i++) {
        uint32_t position = lsb + i;
        uint32_t byte = 15 - (position >> 3);
        uint32_t bit = position & 0x7;
        uint32_t value = (data[byte] >> bit) & 1;
        bits |= value << i;
    }
    return bits;
}

unsigned transfer_rate_unit[] = { 
    100 * 1000,         //100Kbps
    1000 * 1000,        //1Mbps
    10 * 1000 * 1000,   //10Mbps
    100 * 1000 * 1000   //100Mbps
};

float time_value[] = {0, 1, 1.2, 1.3, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 7.0, 8.0};

uint32_t _sd_sectors() {
    uint32_t c_size, c_size_mult, read_bl_len;
    uint32_t block_len, mult, blocknr, capacity;
    uint32_t hc_c_size, tran_speed, max_tran_speed, time_value_t;
    uint32_t blocks = 0;
	
    // CMD9, Response R2 (R1 byte + 16-byte block read)
    if (_cmdx(9, 0) != 0) {
        printf("Didn't get a response from the disk\n");
        return 0;
    }

    uint8_t csd[16];
    if (_read(csd, 16) != 0) {
        printf("Couldn't read csd response from disk\n");
        return 0;
    }

    // csd_structure : csd[127:126]
    // c_size        : csd[73:62]
    // c_size_mult   : csd[49:47]
    // read_bl_len   : csd[83:80] - the *maximum* read block length

    int csd_structure = ext_bits(csd, 127, 126);
    tran_speed = ext_bits(csd, 103, 96);
    time_value_t = ((tran_speed >> 3) & 0xf);
    max_tran_speed = time_value[time_value_t] * transfer_rate_unit[(tran_speed & 0x7)];
    if (time_value_t > 1)
        time_value_t -= 1;//slower trans speed is more robust.
    _transfer_sck =  time_value[time_value_t] * transfer_rate_unit[(tran_speed & 0x7)];
    printf("max_tran_speed: %d, _transfer_sck: %d\n", max_tran_speed, _transfer_sck);
    
    switch (csd_structure) {
        case 0:
            cdv = 512; //fixed to 512 bytes
            c_size = ext_bits(csd, 73, 62);
            c_size_mult = ext_bits(csd, 49, 47);
            read_bl_len = ext_bits(csd, 83, 80);//can be ignore by cmd16(set block len)

            block_len = 1 << read_bl_len;
            mult = 1 << (c_size_mult + 2);
            blocknr = (c_size + 1) * mult;
            capacity = blocknr * block_len;
            blocks = capacity / 512;
            printf("\n\rSDCard\n\rc_size: %d \n\rcapacity: %ld \n\rsectors: %lld\n\r", c_size, capacity, blocks);
            break;

        case 1:
            cdv = 1;
            c_size = ext_bits(csd, 69, 48);
            capacity = (c_size + 1) / 2; //in MB, formula: (c_size+1)*512KBytes
            
            printf("\n\rSDHC Card\ncapacity: %d MBytes, sectors: %d\n", capacity, capacity * 2048);
            
            
            break;

        default:
            printf("CSD struct unsupported\r\n");
            return 0;
    };
    return blocks;
}
