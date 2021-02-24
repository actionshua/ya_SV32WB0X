
#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"

#include "cli.h"
#include "cli_cmd.h"
#include "osal.h"
#include <drv_spimst.h>
#include "sys_clock.h"

#include "logger.h"

#define CMD_TAG       LOG_TAG_CMD
#define CMD_LOG_E(format, ...) log_e(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_W(format, ...) log_w(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_I(format, ...) log_i(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_D(format, ...) log_d(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_V(format, ...) log_v(CMD_TAG, format, ##__VA_ARGS__)

/*---------------------------------- CMDs -----------------------------------*/

//uint8_t *write_buf;
//uint8_t *read_buf;

static int csn_available(uint32_t csn) {
#if (CHIP_ID == 6006)
    if (csn < 7) return 1;
    if (csn == 9) return 1;
    if (csn == 11) return 1;
    if ((csn >= 13) && (csn <= 22)) return 1;

    return 0;
#else
    //must add csn check
    return 1;
#endif
}

static void test_spi_master_dma_transfer_common_usage(const char *cmd) {
    printf("Usage           : %s <clk_Hz> <length> <cpha> <cpol> <csn>\n", cmd);
    printf("<clk_Hz>        : SPI Clock (BUS 40MHz : 611 - 10MHz, BUS 160MHz : 2441 - 40MHz)\n");
    printf("<length>        : data length(1-4095)\n");
    printf("<cpha>          : CPHA(0, 1)\n");
    printf("<cpol>          : CPOL(0, 1)\n");
    printf("<csn>           : GPIO_15 is auto CSN, otherwise manual CSN\n");
}
static void test_spi_master_transfer_common_usage(const char *cmd) {
    printf("Usage           : %s <clk_Hz> <length> <cpha> <cpol> <csn>\n", cmd);
    printf("<clk_Hz>        : SPI Clock (BUS 40MHz : 611 - 10MHz, BUS 160MHz : 2441 - 40MHz)\n");
    printf("<length>        : data length(1-32768)\n");
    printf("<cpha>          : CPHA(0, 1)\n");
    printf("<cpol>          : CPOL(0, 1)\n");
    printf("<csn>           : GPIO_15is auto CSN, otherwise manual CSN\n");
}
static void test_spi_master_common_flash_transfer_usage(const char *cmd) {
    printf("Usage           : %s <clk_Hz> <length> <cpha> <cpol> <csn>\n", cmd);
    printf("<clk_Hz>        : SPI Clock (BUS 40MHz : 611 - 10MHz, BUS 160MHz : 2441 - 40MHz)\n");
    printf("<length>        : data length(1-Flash size)\n");
    printf("<cpha>          : CPHA(0, 1)\n");
    printf("<cpol>          : CPOL(0, 1)\n");
    printf("<csn>           : GPIO_15 is auto CSN, otherwise manual CSN\n");
    printf("<cpha> = <cpol>\n");
}

static void test_spi_master_transfer_compare_usage(const char *cmd) {
    printf("Usage           : %s <clk_Hz> <length> <cpha> <cpol> <csn>\n", cmd);
    printf("<clk_Hz>        : SPI Clock (BUS 40MHz : 611 - 10MHz, BUS 160MHz : 2441 - 40MHz)\n");
    printf("<length>        : data length (1-8190), if over 4096 must be an odd number\n");
    printf("<cpha>          : CPHA(0, 1)\n");
    printf("<cpol>          : CPOL(0, 1)\n");
    printf("<csn>           : GPIO_15 is auto CSN, otherwise manual CSN\n");
}

int test_spi_master_dma_data_loopback_transfer(int32_t argc, char *argv[]) { 
    uint32_t data_length = 0;
    uint32_t clk_Hz = 0;
    uint8_t cpha = 0;
    uint8_t cpol = 0;
    uint8_t *rx_buf;
    uint8_t *tx_buf;
    uint32_t csn = 0;

    if (argc != 6) {
        test_spi_master_dma_transfer_common_usage(argv[0]);
        return 0;
    }

    clk_Hz = strtoul(argv[1], NULL, 10);
    data_length = strtoul(argv[2], NULL, 10);
    cpha = strtoul(argv[3], NULL, 10);
    cpol = strtoul(argv[4], NULL, 10);
    csn = strtoul(argv[5], NULL, 10);

    if ((clk_Hz <= sys_bus_clock()/65534) || (clk_Hz > sys_bus_clock()/2) || (data_length < 1)|| (cpha > 1) || (cpol > 1) || (!csn_available(csn))) {
        test_spi_master_dma_transfer_common_usage(argv[0]);
        return 0;
    }

    drv_spimst_init(clk_Hz, cpha, cpol);
    rx_buf = drv_spimst_alloc_dma_buffer(data_length);
    tx_buf = drv_spimst_alloc_dma_buffer(data_length);

    int i;
    for (i = 0; i < data_length; i++) {
        tx_buf[i] = i % 256;
        rx_buf[i] = 0;
    }
    drv_spimst_set_dma_buffer(data_length, tx_buf, rx_buf);

    drv_spimst_dma_trx(tx_buf, rx_buf, data_length, csn);
    int error = 0;
    for (i = 0; i < data_length; i++) {
        if (rx_buf[i] != tx_buf[i]) {
            error = 1;
        }
    }
    drv_spimst_free_dma_buffer(tx_buf);
    drv_spimst_free_dma_buffer(rx_buf);
    drv_spimst_deinit();

    if (error) {
        printf("data compare failed!\n");
    } else {
        printf("data compare success!\n");
    }

    return 0;
}

int test_spi_master_dma_data_transfer(int32_t argc, char *argv[]) { 
    uint32_t data_length = 0;
    uint32_t clk_Hz = 0;
    uint8_t cpha = 0;
    uint8_t cpol = 0;
    uint8_t *rx_buf;
    uint8_t *tx_buf;
    uint32_t csn = 0;

    if (argc != 6) {
        test_spi_master_dma_transfer_common_usage(argv[0]);
        return 0;
    }

    clk_Hz = strtoul(argv[1], NULL, 10);
    data_length = strtoul(argv[2], NULL, 10);
    cpha = strtoul(argv[3], NULL, 10);
    cpol = strtoul(argv[4], NULL, 10);
    csn = strtoul(argv[5], NULL, 10);
    if ((clk_Hz <= sys_bus_clock()/65534) || (clk_Hz > sys_bus_clock()/2) || (data_length < 1)|| (cpha > 1) || (cpol > 1) || (!csn_available(csn))) {
        test_spi_master_dma_transfer_common_usage(argv[0]);
        return 0;
    }
    drv_spimst_init(clk_Hz, cpha, cpol);
    rx_buf = drv_spimst_alloc_dma_buffer(data_length);
    tx_buf = drv_spimst_alloc_dma_buffer(data_length);
    //drv_spimst_set_dma_buffer(data_length, tx_buf, rx_buf);


    int i;
    for (i = 0; i < data_length; i++) {
        tx_buf[i] = i % 256;
        rx_buf[i] = 0;
    }
    drv_spimst_dma_trx(tx_buf, rx_buf, data_length, csn);
    drv_spimst_free_dma_buffer(tx_buf);
    drv_spimst_free_dma_buffer(rx_buf);
    drv_spimst_deinit();

    printf("\n[SPI Master Test : PASS!]\n");
    return 0;
}

static uint8_t dma_flash_read_busy(uint8_t *tx_buf, uint8_t *rx_buf, uint32_t csn) {
    /* Set flash command : Write Enable. */
    tx_buf[0] = 0x05;
    /* Enable SPI HW. */
    drv_spimst_dma_trx(tx_buf, rx_buf, 2, csn);
    return rx_buf[1];
}

static uint8_t dma_wait_flash_busy(uint8_t *tx_buf, uint8_t *rx_buf, uint32_t csn) {
    while((dma_flash_read_busy(tx_buf, rx_buf, csn) & 0x1) != 0) {
        OS_MsDelay(500);
    }

    return 0;
}

static void dma_flash_write_enable(uint8_t *tx_buf, uint8_t *rx_buf, uint32_t csn) {
    /* Set flash command : Write Enable. */
    tx_buf[0] = 0x06;
    /* Enable SPI HW. */
    drv_spimst_dma_trx(tx_buf, rx_buf, 1, csn);
    dma_wait_flash_busy(tx_buf, rx_buf, csn);
}

int test_spi_master_dma_flash_transfer(int32_t argc, char *argv[]) {
    uint8_t ret = 0x0; 
    uint32_t i = 0;
    uint32_t data_length = 0;
    uint32_t clk_Hz = 0;
    uint8_t cpha = 0;
    uint8_t cpol = 0;
    uint32_t csn;
    uint8_t *rx_buf;
    uint8_t *tx_buf;

    if (argc != 6) {
        test_spi_master_common_flash_transfer_usage(argv[0]);
        return 0;
    }

    clk_Hz = strtoul(argv[1], NULL, 10);
    data_length = strtoul(argv[2], NULL, 10);
    cpha = strtoul(argv[3], NULL, 10);
    cpol = strtoul(argv[4], NULL, 10);
    csn = strtoul(argv[5], NULL, 10);
    if ((clk_Hz <= sys_bus_clock()/65534) || (clk_Hz > sys_bus_clock()/2) || (data_length < 1)|| (cpha > 1) || (cpol > 1) || (cpha != cpol) || (!csn_available(csn))) {
        test_spi_master_common_flash_transfer_usage(argv[0]);
        return 0;
    }
    drv_spimst_init(clk_Hz, cpha, cpol);
    rx_buf = drv_spimst_alloc_dma_buffer(256+4); // max page write 256.
    tx_buf = drv_spimst_alloc_dma_buffer(256+4);
    //drv_spimst_set_dma_buffer(256+4, tx_buf, rx_buf);

    /* Set flash command : Read Manufacturer/Device ID. */
    tx_buf[0] = 0x90;
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    /* Enable SPI HW. */
    // get Manufacturer ID, Device ID.
    drv_spimst_dma_trx(tx_buf, rx_buf, 6, csn); /* The size "+2" is for manufacturer ID and device ID. */

    printf("======================================\n");
    printf("Manufacturer ID:  0x%02x\n", rx_buf[4]);
    printf("Device ID:  0x%02x\n", rx_buf[5]);

    printf("before write enable status: %xh\n", dma_flash_read_busy(tx_buf, rx_buf, csn));
    dma_flash_write_enable(tx_buf, rx_buf, csn);
    printf("after write enable status: %xh\n", dma_flash_read_busy(tx_buf, rx_buf, csn));

    /* Set flash command : chip Erase. */
    tx_buf[0] = 0x60;
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    /* Enable SPI HW. */
    drv_spimst_dma_trx(tx_buf, rx_buf, 1, csn);
    printf("after chip erase status: %xh\n", dma_flash_read_busy(tx_buf, rx_buf, csn));

    dma_wait_flash_busy(tx_buf, rx_buf, csn);

    int j;
    printf("Write to Flash:\n");
    printf("============================================================\n");
    for (j = 0; j < data_length; j+=256) {
        int len = ((data_length-j)>256)?256:(data_length-j);
        dma_flash_write_enable(tx_buf, rx_buf, csn);

        int i;
        for (i = 0; i < len; i++) {
            tx_buf[4+i] = OS_Random();
            printf("%08xh", tx_buf[4+i]);
            if (((i+1)%16)==0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
        /* Set flash command : Page Program. */
        tx_buf[0] = 0x02;
        tx_buf[1] = ((j>>16) & 0xFF);
        tx_buf[2] = ((j>>8) & 0xFF);
        tx_buf[3] = (j&0xFF);
        /* Enable SPI HW. */
        ret = drv_spimst_dma_trx(tx_buf, rx_buf, len+4, csn);
        dma_wait_flash_busy(tx_buf, rx_buf, csn);
    }
    printf("\n============================================================\n");


    printf("Read from Flash:\n");
    printf("============================================================\n");
    for (j = 0; j < data_length; j+=256) {
        int len = ((data_length-j)>256)?256:(data_length-j);
        int i;
        for (i = 0; i < len; i++) {
            rx_buf[4+i] = OS_Random();
        }

        /* Set flash command : Read. */
        tx_buf[0] = 0x03;
        tx_buf[1] = ((j>>16) & 0xFF);
        tx_buf[2] = ((j>>8) & 0xFF);
        tx_buf[3] = (j&0xFF);
        /* Enable SPI HW. */
        drv_spimst_dma_trx(tx_buf, rx_buf, len+4, csn);
        for (i = 0; i < len; i++) {
            printf("%08xh", rx_buf[4+i]);
            if (((i+1)%16)==0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
    }
    printf("\n============================================================\n");
    drv_spimst_free_dma_buffer(tx_buf);
    drv_spimst_free_dma_buffer(rx_buf);
    drv_spimst_deinit();

    return 0;
}

static uint8_t flash_read_busy(uint8_t *tx_buf, uint8_t *rx_buf, uint32_t csn) {
    /* Set flash command : Write Enable. */
    tx_buf[0] = 0x05;
    /* Enable SPI HW. */
    drv_spimst_trx(tx_buf, rx_buf, 2, csn);
    return rx_buf[1];
}

static void wait_flash_busy(uint8_t *tx_buf, uint8_t *rx_buf, uint32_t csn) {
    while((flash_read_busy(tx_buf, rx_buf, csn) & 0x1) != 0) {
        OS_MsDelay(500);
    }
}

static void flash_write_enable(uint8_t *tx_buf, uint8_t *rx_buf, uint32_t csn) {
    /* Set flash command : Write Enable. */
    tx_buf[0] = 0x06;
    /* Enable SPI HW. */
    drv_spimst_trx(tx_buf, rx_buf, 1, csn);
    wait_flash_busy(tx_buf, rx_buf, csn);
}

int test_spi_master_flash_transfer(int32_t argc, char *argv[]) {
    uint8_t ret = 0x0; 
    uint32_t i = 0;
    uint32_t data_length = 0;
    uint32_t clk_Hz = 0;
    uint8_t cpha = 0;
    uint8_t cpol = 0;
    uint32_t csn;
    uint8_t *rx_buf;
    uint8_t *tx_buf;

    if (argc != 6) {
        test_spi_master_common_flash_transfer_usage(argv[0]);
        return 0;
    }

    clk_Hz = strtoul(argv[1], NULL, 10);
    data_length = strtoul(argv[2], NULL, 10);
    cpha = strtoul(argv[3], NULL, 10);
    cpol = strtoul(argv[4], NULL, 10);
    csn = strtoul(argv[5], NULL, 10);
    if ((clk_Hz <= sys_bus_clock()/65534) || (clk_Hz > sys_bus_clock()/2) || (data_length < 1)|| (cpha > 1) || (cpol > 1) || (cpha != cpol) || (!csn_available(csn))) {
        test_spi_master_common_flash_transfer_usage(argv[0]);
        return 0;
    }
    drv_spimst_init(clk_Hz, cpha, cpol);
    rx_buf = OS_MemAlloc(256+4);
    tx_buf = OS_MemAlloc(256+4);

    /* Set flash command : Read Manufacturer/Device ID. */
    tx_buf[0] = 0x90;
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    /* Enable SPI HW. */
    // get Manufacturer ID, Device ID.
    drv_spimst_trx(tx_buf, rx_buf, 6, csn); /* The size "+2" is for manufacturer ID and device ID. */

    printf("======================================\n");
    printf("Manufacturer ID:  0x%02x\n", rx_buf[4]);
    printf("Device ID:  0x%02x\n", rx_buf[5]);

    printf("before write enable status: %xh\n", flash_read_busy(tx_buf, rx_buf, csn));
    flash_write_enable(tx_buf, rx_buf, csn);
    printf("after write enable status: %xh\n", flash_read_busy(tx_buf, rx_buf, csn));

    /* Set flash command : Chip Erase. */
    tx_buf[0] = 0x60;
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    /* Enable SPI HW. */
    drv_spimst_trx(tx_buf, rx_buf, 1, csn);
    printf("after chip erase status: %xh\n", flash_read_busy(tx_buf, rx_buf, csn));

    wait_flash_busy(tx_buf, rx_buf, csn);

    int j;
    printf("Write to Flash:\n");
    printf("============================================================\n");
    for (j = 0; j < data_length; j+=256) {
        int len = ((data_length-j)>256)?256:(data_length-j);
        flash_write_enable(tx_buf, rx_buf, csn);

        int i;
        for (i = 0; i < len; i++) {
            tx_buf[4+i] = OS_Random();
            printf("%08xh", tx_buf[4+i]);
            if (((i+1)%16)==0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
        /* Set flash command : Page Program. */
        tx_buf[0] = 0x02;
        tx_buf[1] = ((j>>16) & 0xFF);
        tx_buf[2] = ((j>>8) & 0xFF);
        tx_buf[3] = (j&0xFF);
        /* Enable SPI HW. */
        ret = drv_spimst_trx(tx_buf, rx_buf, len+4, csn);
        wait_flash_busy(tx_buf, rx_buf, csn);
    }
    printf("\n============================================================\n");


    printf("Read from Flash:\n");
    printf("============================================================\n");
    for (j = 0; j < data_length; j+=256) {
        int len = ((data_length-j)>256)?256:(data_length-j);
        int i;
        for (i = 0; i < len; i++) {
            rx_buf[4+i] = OS_Random();
        }

        /* Set flash command : Read. */
        tx_buf[0] = 0x03;
        tx_buf[1] = ((j>>16) & 0xFF);
        tx_buf[2] = ((j>>8) & 0xFF);
        tx_buf[3] = (j&0xFF);
        /* Enable SPI HW. */
        drv_spimst_trx(tx_buf, rx_buf, len+4, csn);
        for (i = 0; i < len; i++) {
            printf("%08xh", rx_buf[4+i]);
            if (((i+1)%16)==0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
    }
    printf("\n============================================================\n");
    OS_MemFree(tx_buf);
    OS_MemFree(rx_buf);
    drv_spimst_deinit();
    return 0;
}

//////////////////////



int test_spi_master_data_transfer(int32_t argc, char *argv[]) { 
    uint8_t ret = 0x0; 
    uint32_t i = 0;
    uint8_t *spi_rx_buf;
    uint8_t *spi_tx_buf;
    uint32_t data_length = 0;
    uint32_t clk_Hz = 0;
    uint8_t cpha = 0;
    uint8_t cpol = 0;
    uint8_t csn = 0;

    if (argc != 6) {
        test_spi_master_transfer_common_usage(argv[0]);
        return 0;
    }

    clk_Hz = strtoul(argv[1], NULL, 10);
    data_length = strtoul(argv[2], NULL, 10);
    cpha = strtoul(argv[3], NULL, 10);
    cpol = strtoul(argv[4], NULL, 10);
    csn = strtoul(argv[5], NULL, 10);
    if ((clk_Hz <= sys_bus_clock()/65534) || (clk_Hz > sys_bus_clock()/2) || (data_length < 1)|| (cpha > 1) || (cpol > 1) || (!csn_available(csn))) {
        test_spi_master_transfer_common_usage(argv[0]);
        return 0;
    }
    /* Initialize tx/rx buffer. */
    spi_tx_buf = OS_MemAlloc(data_length);
    spi_rx_buf = OS_MemAlloc(data_length);
    for(i = 0; i < data_length; i ++) {
        spi_tx_buf[i] = i%256;
        spi_rx_buf[i] = 0;
    }

    /* Initialize SPI HW. */
    drv_spimst_init(clk_Hz, cpha, cpol);

    /* Start SPI operation. */
    ret = drv_spimst_trx(spi_tx_buf, spi_rx_buf, data_length, csn);
    OS_MemFree(spi_tx_buf);
    OS_MemFree(spi_rx_buf);

    printf("\n[SPI Master Test : PASS!]\n");

    return 0;
}
int test_spi_master_data_loopback_transfer(int32_t argc, char *argv[]) { 
    uint32_t data_length = 0;
    uint32_t clk_Hz = 0;
    uint8_t cpha = 0;
    uint8_t cpol = 0;
    uint8_t *spi_rx_buf;
    uint8_t *spi_tx_buf;
    uint32_t csn = 0;

    if (argc != 6) {
        test_spi_master_transfer_common_usage(argv[0]);
        return 0;
    }

    clk_Hz = strtoul(argv[1], NULL, 10);
    data_length = strtoul(argv[2], NULL, 10);
    cpha = strtoul(argv[3], NULL, 10);
    cpol = strtoul(argv[4], NULL, 10);
    csn = strtoul(argv[5], NULL, 10);
    if ((clk_Hz <= sys_bus_clock()/65534) || (clk_Hz > sys_bus_clock()/2) || (data_length < 1)|| (cpha > 1) || (cpol > 1) || (!csn_available(csn))) {
        test_spi_master_transfer_common_usage(argv[0]);
        return 0;
    }
    drv_spimst_init(clk_Hz, cpha, cpol);
    spi_tx_buf = OS_MemAlloc(data_length);
    spi_rx_buf = OS_MemAlloc(data_length);

    int i;
    for (i = 0; i < data_length; i++) {
        spi_tx_buf[i] = i % 256;
        spi_rx_buf[i] = 0;
    }

    drv_spimst_trx(spi_tx_buf, spi_rx_buf, data_length, csn);
    int error = 0;
    for (i = 0; i < data_length; i++) {
        if (spi_rx_buf[i] != spi_tx_buf[i]) {
            error = 1;
        }
    }
    OS_MemFree(spi_tx_buf);
    OS_MemFree(spi_rx_buf);
    drv_spimst_deinit();

    if (error) {
        printf("data compare failed!\n");
    } else {
        printf("data compare success!\n");
    }

    return 0;
}

int test_spi_master_dma_data_transfer_compare(int32_t argc, char *argv[]) { 
    uint32_t data_length = 0;
    uint32_t clk_Hz = 0;
    uint8_t cpha = 0;
    uint8_t cpol = 0;
    uint8_t *spi_rx_buf;
    uint8_t *spi_tx_buf;
    uint32_t csn = 13;

    uint8_t * rx_total_data;
    if (argc != 6) {
        test_spi_master_dma_transfer_common_usage(argv[0]);
        return 0;
    }

    clk_Hz = strtoul(argv[1], NULL, 10);
    data_length = strtoul(argv[2], NULL, 10);
   
    cpha = strtoul(argv[3], NULL, 10);
    cpol = strtoul(argv[4], NULL, 10);
    csn = strtoul(argv[5], NULL, 10);
    
    if ((clk_Hz <= sys_bus_clock()/65534) || (clk_Hz > sys_bus_clock()/2) || (data_length < 1)|| (cpha > 1) || (cpol > 1)) {
        test_spi_master_transfer_compare_usage(argv[0]);
        return 0;
    }
    drv_spimst_init(clk_Hz, cpha, cpol);
  
    spi_tx_buf = drv_spimst_alloc_dma_buffer(data_length);
    spi_rx_buf = drv_spimst_alloc_dma_buffer(data_length);

    drv_spimst_set_dma_buffer(data_length, spi_tx_buf, spi_rx_buf);
    
    int i;
    for (i = 0; i < data_length; i++) {

            spi_tx_buf[i] = i % 256;

        spi_rx_buf[i] = 0;
    }

    drv_spimst_dma_trx(spi_tx_buf, spi_rx_buf, data_length, csn);


    int error = 0;
    for (i = 0; i < data_length; i++) {
        if (spi_rx_buf[i] != spi_tx_buf[i]) {
            error ++;
        }
    }

    if( error >= 1)
    {
        printf("MASTER RX NOT Match!!!\n");
        printf("Error ratio is %d percent (%d/%d)\n", error*100/(data_length) , error, data_length);
    }
    else
    {
        printf("MASTER RX Match!!!\n");
    }


    drv_spimst_free_dma_buffer(spi_tx_buf);
    drv_spimst_free_dma_buffer(spi_rx_buf);
    drv_spimst_deinit();


    return 0;
}


int test_spi_master_dma_data_transfer_random(int32_t argc, char *argv[]) { 
    uint32_t data_length = 0;
    uint32_t clk_Hz = 0;
    uint8_t cpha = 0;
    uint8_t cpol = 0;
    uint8_t *spi_rx_buf;
    uint8_t *spi_tx_buf;
    uint32_t csn = 13;

    uint8_t * rx_total_data;
    if (argc != 6) {
        test_spi_master_dma_transfer_common_usage(argv[0]);
        return 0;
    }

    clk_Hz = strtoul(argv[1], NULL, 10);
    data_length = strtoul(argv[2], NULL, 10);
   
    cpha = strtoul(argv[3], NULL, 10);
    cpol = strtoul(argv[4], NULL, 10);
    csn = strtoul(argv[5], NULL, 10);
    
    if ((clk_Hz <= sys_bus_clock()/65534) || (clk_Hz > sys_bus_clock()/2) || (data_length < 1)|| (cpha > 1) || (cpol > 1)) {
        test_spi_master_transfer_compare_usage(argv[0]);
        return 0;
    }
    drv_spimst_init(clk_Hz, cpha, cpol);
   
    spi_tx_buf = drv_spimst_alloc_dma_buffer(data_length);
    spi_rx_buf = drv_spimst_alloc_dma_buffer(data_length);

    rx_total_data = OS_MemAlloc(data_length);
    drv_spimst_set_dma_buffer(data_length, spi_tx_buf, spi_rx_buf);

    printf("SPI Master TX Data to Slave:\n");
    printf("===============================================");
    int i;
    for (i = 0; i < data_length; i++) 
    {
        //fill random
        spi_tx_buf[i] = OS_Random();
        
        if(i%16 == 0)
                printf("\n");        
        printf("%02X  ", spi_tx_buf[i]);
    }
    printf("\n===============================================\n");

    drv_spimst_dma_trx(spi_tx_buf, spi_rx_buf, data_length, csn);

/*    
    memcpy(rx_total_data+i*data_length, rx_buf, data_length);
    int error = 0;
    for (i = 0; i < data_length; i++) {
        if (rx_total_data[i] != tx_buf[i%data_length]) {
            //printf("[%d] rx:%x != tx:%x [%d]\n", i, rx_total_data[i], tx_buf[i%data_length], i%data_length);
            error ++;
        }
    }

    if( error >= 1)
    {
        printf("MASTER RX NOT Match!!!\n");
        printf("Error ratio is %d percent (%d/%d)\n", error*100/(data_length) , error, data_length);
    }
    else
    {
        printf("MASTER RX Match!!!\n");
    }
*/

    printf("\nSPI Master RX Data from Slave:\n");
    printf("===============================================");
    for (i = 0; i < data_length; i++) 
    {     
        if(i%16 == 0)
                printf("\n");        
        printf("%02X  ", spi_rx_buf[i]);        
    }
    printf("\n===============================================\n");
    
    OS_MemFree(rx_total_data);
    drv_spimst_free_dma_buffer(spi_tx_buf);
    drv_spimst_free_dma_buffer(spi_rx_buf);
    drv_spimst_deinit();


    return 0;
}


int test_spi_master_trx_checksum(int32_t argc, char *argv[]) { 
    uint32_t data_length = 0;
    uint32_t clk_Hz = 0;
    uint8_t cpha = 0;
    uint8_t cpol = 0;
    uint8_t *spi_rx_buf;
    uint8_t *spi_tx_buf;
    uint32_t csn = 13;
    uint32_t tx_checksum = 0;
    uint32_t rx_checksum = 0;
    uint8_t use_dma = 1;

    if (argc < 6) {
        test_spi_master_dma_transfer_common_usage(argv[0]);
        return 0;
    }

    clk_Hz = strtoul(argv[1], NULL, 10);
    data_length = strtoul(argv[2], NULL, 10);
   
    cpha = strtoul(argv[3], NULL, 10);
    cpol = strtoul(argv[4], NULL, 10);
    csn = strtoul(argv[5], NULL, 10);
    
    use_dma = strtoul(argv[6], NULL, 10);

    if (argc > 6)
        if ((clk_Hz <= sys_bus_clock()/65534) || (clk_Hz > sys_bus_clock()/2) || (data_length < 1)|| (cpha > 1) || (cpol > 1)) {
        test_spi_master_transfer_compare_usage(argv[0]);
        return 0;
    }
    drv_spimst_init(clk_Hz, cpha, cpol);
   
    spi_tx_buf = drv_spimst_alloc_dma_buffer(data_length);
    spi_rx_buf = drv_spimst_alloc_dma_buffer(data_length);

    int i;
    for (i = 0; i < data_length-4; i++) 
    {
        //fill random
        spi_tx_buf[i] = OS_Random();
        tx_checksum += spi_tx_buf[i];

    }
    
    printf("Master TX Checksum = 0x%x\n", tx_checksum);
    spi_tx_buf[data_length-4] = (tx_checksum>>0)&0xff;
    spi_tx_buf[data_length-3] = (tx_checksum>>8)&0xff;
    spi_tx_buf[data_length-2] = (tx_checksum>>16)&0xff;
    spi_tx_buf[data_length-1] = (tx_checksum>>24)&0xff;
    
    //transmit with dma or mcu
    if( use_dma ) 
        drv_spimst_dma_trx(spi_tx_buf, spi_rx_buf, data_length, csn);
    else
        drv_spimst_trx(spi_tx_buf, spi_rx_buf, data_length, csn);


    for (i = 0; i < data_length-4; i++) 
    {     
        rx_checksum += spi_rx_buf[i];   
    }

    uint32_t checksum = (spi_rx_buf[data_length-4]<<0) |
                        (spi_rx_buf[data_length-3]<<8) |
                        (spi_rx_buf[data_length-2]<<16)|
                        (spi_rx_buf[data_length-1]<<24);

    if(checksum == rx_checksum)
        printf("Master RX Checksum MATCH (0x%x)\n", rx_checksum);
    else
        printf("Master RX Checksum Not MATCH (0x%x vs 0x%x)\n", checksum, rx_checksum);
        
    drv_spimst_free_dma_buffer(spi_tx_buf);
    drv_spimst_free_dma_buffer(spi_rx_buf);
    drv_spimst_deinit();


    return 0;
}


int Cmd_help (int32_t argc, char *argv[])
{
    printf ("\n*************************************************************************\n");
    printf ("SPI Master PINOUT : \n");
    printf ("SPI Master 0\n");
    printf ("                   GPIO_18 : SPI_M_CLK\n");
    printf ("                   GPIO_17 : SPI_M_MISO\n");
    printf ("                   GPIO_16 : SPI_M_MOSI\n");
    printf ("                   GPIO_15 : SPI_M_CS\n");
    printf ("SPI Master 1\n");
    printf ("                   GPIO_22 : SPI_M_CLK\n");
    printf ("                   GPIO_21 : SPI_M_MISO\n");
    printf ("                   GPIO_20 : SPI_M_MOSI\n");
    printf ("                   GPIO_19 : SPI_M_CS\n");
    printf ("SPI Master 2\n");
    printf ("                   GPIO_32 : SPI_M_CLK\n");
    printf ("                   GPIO_31 : SPI_M_MISO\n");
    printf ("                   GPIO_30 : SPI_M_MOSI\n");
    printf ("                   GPIO_29 : SPI_M_CS\n");    
    printf ("\n*************************************************************************\n");

    return 0;
}



/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "help"                      , Cmd_help                                   , "SPI Master test help"                                            } ,
    { "spi_dma_transfer"          , test_spi_master_dma_data_transfer          , "spi_dma_transfer <clk_Hz> <length> <cpha> <cpol> <csn>"          } ,
    { "spi_dma_flash_transfer"    , test_spi_master_dma_flash_transfer         , "spi_dma_flash_transfer <clk_Hz> <length> <cpha> <cpol> <csn>"    } ,
    { "spi_dma_loopback_transfer" , test_spi_master_dma_data_loopback_transfer , "spi_dma_loopback_transfer <clk_Hz> <length> <cpha> <cpol> <csn>" } ,
    { "spi_transfer"              , test_spi_master_data_transfer              , "spi_transfer <clk_Hz> <length> <cpha> <cpol> <csn>"              } ,
    { "spi_flash_transfer"        , test_spi_master_flash_transfer             , "spi_flash_transfer <clk_Hz> <length> <cpha> <cpol> <csn>"        } ,
    { "spi_loopback_transfer"     , test_spi_master_data_loopback_transfer     , "spi_loopback_transfer <clk_Hz> <length> <cpha> <cpol> <csn>"     } ,

    //compare
    { "spi_dma_transfer_compare"     , test_spi_master_dma_data_transfer_compare     , "spi_dma_transfer_compare <clk_Hz> <length> <cpha> <cpol> <csn>"     } ,
    { "spi_dma_transfer_random"     , test_spi_master_dma_data_transfer_random     , "spi_dma_transfer_random <clk_Hz> <length> <cpha> <cpol> <csn>"     } ,


    //send random data with checksum
    { "spi_master_trx_crc"     , test_spi_master_trx_checksum     , "spi_master_trx_crc <clk_Hz> <length> <cpha> <cpol> <csn>"     } ,
    
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


