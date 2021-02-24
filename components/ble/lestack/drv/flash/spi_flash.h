#ifndef SPI_FLASH_H
#define SPI_FLASH_H

#include <stdint.h>

// sync mode function.
void get_device_id();
void get_status_register(uint8_t *data);

enum spi_flash_types {
    E_SPI_FLASH_GET_DEVICE_ID,
    E_SPI_FLASH_GET_STATUS_REGISTER,
};

typedef int32_t (*spi_flash_event_callback)(int32_t, int32_t);

// async mode function.
void spi_flash_init();
void spi_flash_register_event(spi_flash_event_callback cb);
int32_t spi_flash_is_exist();
int32_t spi_flash_get_status_register();

struct spi_flash_driver {
    int32_t version;
    struct flash_info {
        int32_t page_size;
        int32_t sector_size;
        int32_t block_size;
        int32_t total_size;
    } *info;
    int32_t (*init)();
    int32_t (*check_id)();
    int32_t (*get_device_id)(uint32_t *manufacturer_id, uint32_t *device_id);
    int32_t (*write_enable)();
    int32_t (*write_diable)();
    int32_t (*read_status)(uint32_t *status);
    int32_t (*write_status)(uint32_t status);
    int32_t (*chip_erase)();
    int32_t (*program)(uint8_t *src, uint32_t dest_addr, uint32_t len);
    int32_t (*bist_read)(uint32_t src_addr, uint8_t *dest, uint32_t len);
    int32_t (*power_down)();
    int32_t (*wake_up)();
};

const struct spi_flash_driver g_spi_flash_common_driver;


#endif /* end of include guard: SPI_FLASH_H */
