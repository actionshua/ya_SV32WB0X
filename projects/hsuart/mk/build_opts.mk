################################################################
# Build System Detail setting
################################################################
BUILD_SHOW_ILM_INFO ?= 1
BUILD_SHOW_DLM_INFO ?= 1
VERBOSE             ?= 0

ifeq ($(strip $(BLE_EN)),1)
CFLAGS              += -D__HEAP_SIZE=4096 -DM_LOG_REPORT=LOG_INFO -DHW_ANCHOR_TEST -DHCI_DEBUG -DLOW_POWER_SUPPORT -DHCI -DHEAP_NV_DATA=1 -DNV_SIZE=8 -DMCU=N7 -DBLE_CTRL_ONLY
endif

AFLAGS              +=
INCLUDE             += -I$(PROJ_DIR)/src/board/inc
ifeq ($(strip $(SUPPORT_CXX)),1)
LDFLAGS             += -lstdc++ -lm
endif

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
