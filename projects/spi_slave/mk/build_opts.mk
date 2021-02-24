################################################################
# Build System Detail setting
################################################################
BUILD_SHOW_ILM_INFO ?= 1
BUILD_SHOW_DLM_INFO ?= 1
VERBOSE             ?= 0

CFLAGS              += 
AFLAGS              +=
INCLUDE             += -I$(PROJ_DIR)/src/board/inc
LDFLAGS             +=

BL_CUSTOM           += $(PROJ_DIR)/bootloader/custom_ota/boot_init.c
BL_CUSTOM           += $(PROJ_DIR)/bootloader/custom_ota/custom_ota.c

################################################################
# Build System Detail setting Example
################################################################
#BUILD_SHOW_ILM_INFO ?= 1
#BUILD_SHOW_DLM_INFO ?= 1
#VERBOSE             ?= 0
#
#CFLAGS              ?= -DFOO=0
#AFLAGS              ?= -DBAR=0
#INCLUDE             ?= -I$(PROJ_DIR)/src/include -I$(SDKDIR)/components/third_party/foo/include
