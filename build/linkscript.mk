
ifeq ($(strip $(XIP_MODE)), 1)
LDSCRIPT_S            ?= $(PROJ_DIR)/ld/flash_xip1.lds.S
LDSCRIPT_XIP2_S       ?= $(PROJ_DIR)/ld/flash_xip2.lds.S
BOOTLOADER_LDSCRIPT_S ?= $(PROJ_DIR)/ld/boot.lds.S
PARAM_LDSCRIPT_S      ?= $(PROJ_DIR)/ld/param.lds.S
else
LDSCRIPT_S            ?= $(PROJ_DIR)/ld/sram.lds.S
endif

