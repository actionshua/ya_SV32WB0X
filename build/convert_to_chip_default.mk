

ifeq ($(strip $(SETTING_FLASH_TOTAL_SIZE)),defined_by_chip)
SETTING_FLASH_TOTAL_SIZE:=$(CHIP_DEFAULT_FLASH_TOTAL_SIZE)
endif

ifeq ($(strip $(SYS_MCU_MAX_CLK)),defined_by_chip)
SYS_MCU_MAX_CLK:=$(CHIP_MAX_SPEED)
endif

ifeq ($(strip $(UART_IO_NUM)),defined_by_chip)
UART_IO_NUM:=$(CHIP_UART_IO_NUM)
endif

