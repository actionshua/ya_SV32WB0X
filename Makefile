##############################################################
# Make utility.
##############################################################
include utils/third_party/gmsl/gmsl
unit_conv = $(if $(filter %m %M,$(1)),$(call multiply,$(call substr,$(1),1,$(call dec,$(call strlen,$(1)))),1048576),$(if $(filter %k %K,$(1)),$(call multiply,$(call substr,$(1),1,$(call dec,$(call strlen,$(1)))),1024),$(1)))

##############################################################
# Make version check.
##############################################################
ifeq (3.82,$(firstword $(sort $(MAKE_VERSION) 3.82)))


##############################################################
# Global Variables
##############################################################
TOPDIR          := $(shell pwd)
TOPOUT			:= out
BUILD			:= $(TOPDIR)/build
TARGET_CHIP 	?= turismo
OS 				:= freertos
BUILD_ROM		?= 0
SDKDIR			?= $(TOPDIR)
FLASH_CTRL 		?= 1
SDK_VERSION_OBJ	:= version.o
GEN_IMAGE_FOTA 	:= ./utils/combo.sh
#CUSTOMER		?= none

PRE_BUILD_CMD   :=
POST_BUILD_CMD  :=

BUILD_MODE		?= release

BUILD_ENV		:= $(shell uname)
HOST_ARCH		:= $(shell uname -m)
REDIRECT_BUILDLOG ?= 1

IN_PROJ			?= 0
OBJ_OUT			?= out

SHELL=/bin/bash -o pipefail


export TOPDIR TOPOUT BUILD


# config will include project.mk
include $(BUILD)/empty_config.mk

# select project.
ifeq ($(strip $(IN_PROJ)), 0)
sinclude $(BUILD)/project_cfg.mk
endif

# do board configure.
sinclude $(PROJ_DIR)/mk/board.mk
include $(BUILD)/target_def.mk
include $(BUILD)/xtal.mk
include $(BUILD)/default_config.mk

# do feature configure
sinclude $(PROJ_DIR)/mk/feature.mk
include $(BUILD)/convert_to_chip_default.mk
ifeq ($(origin PROJ_DIR),undefined)
ifeq ($(origin p),undefined)
$(error please use make setup p=<project_name>)
endif
else
include $(BUILD)/feature_check.mk
endif
sinclude $(PROJ_DIR)/mk/libraries.mk
# do extra option
sinclude $(PROJ_DIR)/mk/build_opts.mk

include $(BUILD)/include.mk
include $(BUILD)/feature_flags.mk
include $(BUILD)/compiler.mk
include $(BUILD)/libraries.mk
include $(BUILD)/linkscript.mk
include $(BUILD)/config.mk
include $(BUILD)/build_rules.mk
include $(BUILD)/link_macro.mk
include $(BUILD)/global_def.mk

#CFLAGS += -DCUSTOMER="$(CUSTOMER)"
##############################################################
# ROM Variables
##############################################################

##############################################################
# Local Variables
##############################################################
IMAGE_DIR       ?= $(TOPDIR)/image
IMAGE_NAME		:= $(IMAGE_DIR)/$(PROJECT)
LOG_TABLE		:= $(IMAGE_DIR)/$(PROJECT).json
IMAGE_XIP1      := $(IMAGE_DIR)/$(PROJECT)_xip1.bin
IMAGE_XIP2      :=
ELF_CFG         := $(IMAGE_DIR)/$(PROJECT)_cfg$(ELFSUFFIX)
ELF_BL          := $(IMAGE_DIR)/$(PROJECT)_bl$(ELFSUFFIX)
ELF_XIP1        := $(IMAGE_DIR)/$(PROJECT)_xip1$(ELFSUFFIX)
ELF_XIP2        :=
ifeq ($(strip $(FOTA_OPTION)),2)
IMAGE_XIP2      := $(IMAGE_DIR)/$(PROJECT)_xip2.bin
ELF_XIP2        := $(IMAGE_DIR)/$(PROJECT)_xip2$(ELFSUFFIX)
endif
IMAGE_ASM       := $(IMAGE_DIR)/$(PROJECT)_xip1.asm
IMAGE_INI       := $(IMAGE_DIR)/$(PROJECT).ini
IMAGE_BL_HDR    := $(IMAGE_DIR)/$(PROJECT)_bl_hdr.bin
IMAGE_BL        := $(IMAGE_DIR)/$(PROJECT)_bl.bin
IMAGE_SA        := $(IMAGE_DIR)/$(PROJECT)_sa.bin
IMAGE_MAC       := $(IMAGE_DIR)/$(PROJECT)_mac.bin
IMAGE_PAD       := $(IMAGE_DIR)/$(PROJECT)_pad.bin
IMAGE_INFO      := $(IMAGE_DIR)/$(PROJECT)_info.bin
IMAGE_USER      := $(IMAGE_DIR)/$(PROJECT)_user.bin
IMAGE_ALL       := $(IMAGE_DIR)/$(PROJECT)_all.bin
IMAGE_FS        :=
#IMAGE_FS        := $(IMAGE_DIR)/$(PROJECT)_fs.bin
IMAGE_DUMMY     := $(IMAGE_DIR)/$(PROJECT)_dummy.bin
IMAGE_MAP		:= $(IMAGE_DIR)/$(PROJECT)_xip1.map
IMAGE_MAP_XIP2  := $(IMAGE_DIR)/$(PROJECT)_xip2.map

MKFS            := $(TOPDIR)/utils/mkspiffs/mkspiffs

##############################################################
# init Variables
##############################################################
LIB_DEP          :=
AR_SRC           :=
AR_LIB           :=
LIBRARIES         =
LIBRARIES_DIR     =
BL_LIBRARIES      =
BL_LIBRARIES_DIR  =
CLEAN_RULE       :=
TMP_SRC          :=

##############################################################
# Source directories to Make
##############################################################
SRC_DIRS +=  $(sort $(IMPORT_DIR)) $(CFG_DIR)

#$(call foreach-dir,$(SRC_DIRS))
#$(foreach _d,$(SRC_DIRS),$(eval $(call inc-module,$(_d))))

.PHONY: all clean list_projects setup sync_subprojects  flashtool_clean
.SECONDARY: main-build

ifeq ($(origin PROJECT), undefined)
all: list_projects
	$(Q)echo $(BUILD)/project_cfg.mk not found; \
	please find project use \"make list_projects\", set project use \"make setup p=PROJECT_NAME\";
else
all: pre-build main-build 
endif


ifeq ($(strip $(IN_PROJ)), 0)
pre-build:
	$(Q)$(PRE_BUILD_CMD)
	$(Q)$(CHMOD) $(UNLOCK)
	$(Q)echo static lib:
	$(Q)echo $(STATIC_LIB)
	$(Q)echo > build_error.log
	$(Q)$(CHMOD) $(TOPDIR)/utils/*
	$(Q)$(GEN_VERSION)
	$(Q)$(UNLOCK) $(IMAGE_DIR)/string_table.json;
	$(Q)if [ -f $(BUILD)/project_cfg.mk ]; then \
		$(UNLOCK) $(TOPOUT)/string_table.json; \
		$(CHMOD) $(TOPDIR)/utils/*; \
	else \
		echo $(BUILD)/project_cfg.mk not found; \
		echo please find project use \"make list_projects\", set project use \"make setup p=PROJECT_NAME\"; \
		$(MAKE) list_projects; \
	fi
else
pre-build:
	$(Q)$(PRE_BUILD_CMD)
	$(Q)$(CHMOD) $(UNLOCK)
	$(Q)echo static lib:
	$(Q)echo $(STATIC_LIB)
	$(Q)echo > build_error.log
	$(Q)$(UNLOCK) $(TOPOUT)/string_table.json
	$(Q)$(CHMOD) $(TOPDIR)/utils/*
	$(GEN_VERSION)

endif

post-build:
	@echo build end
ifeq ($(strip $(BUILD_SHOW_ILM_INFO)), 1)
	$(Q)echo ILM remain: $$( grep ilm_remain $(IMAGE_MAP) | head -n 1 | awk --non-decimal-data '{printf "%d",$$1}' )
ifeq ($(strip $(CHIP_ID)),6020)
ifneq ($(strip $(CHIP_SUB_ID)),0)
	$(Q)echo BUS SRAM remain: $$( grep bus_ram_remain $(IMAGE_MAP) | head -n 1 | awk --non-decimal-data '{printf "%d",$$1}' )
endif
endif
endif
ifeq ($(strip $(BUILD_SHOW_DLM_INFO)), 1)
ifneq ($(strip $(SETTING_SRAM_OPTION)),0)
	$(Q)echo DLM remain: $$( grep dlm_remain $(IMAGE_MAP) | head -n 1 | awk --non-decimal-data '{printf "%d",$$1}' )
else
	$(Q)echo SRAM remain: $$( grep dlm_remain $(IMAGE_MAP) | head -n 1 | awk --non-decimal-data '{printf "%d",$$1}' )
endif
endif
ifeq ($(strip $(ROM_MODE)), 1)
ifeq ($(strip $(FLASH_ROM)), 1)
	@if [ -f "$(IMAGE_DIR)/$(PROJECT).bin" ]; then \
		export project_size=$$(stat -c%s $(IMAGE_DIR)/$(PROJECT).bin); \
		export zero_pad_size=$$(printf "%d %d" 0x100000 $$project_size | awk '{print $$1 - $$2}'); \
		dd if=/dev/zero of=$(IMAGE_DIR)/zero_pad.bin bs=1 count=$$zero_pad_size; \
		mv -f $(IMAGE_DIR)/$(PROJECT).bin $(IMAGE_DIR)/$(PROJECT).bin.tmp; \
		cat $(IMAGE_DIR)/$(PROJECT).bin.tmp $(IMAGE_DIR)/zero_pad.bin rom_symbol/$(ROM_VERSION)/rom.bin > $(IMAGE_DIR)/$(PROJECT).bin; \
		rm -f $(IMAGE_DIR)/zero_pad.bin; \
		rm -f $(IMAGE_DIR)/$(PROJECT).bin.tmp; \
	fi
endif
endif
	$(POST_BUILD_CMD)

ALL_IMAGE = $(IMAGE_XIP1) $(IMAGE_XIP2) $(IMAGE_ASM) $(IMAGE_INI) $(IMAGE_BL) $(IMAGE_SA) $(IMAGE_MAC) $(IMAGE_PAD) $(IMAGE_INFO) $(IMAGE_USER) $(IMAGE_ALL) $(IMAGE_FS)

ifeq ($(strip $(PROJECT)), )
main-build:
	$(Q)$(MAKE) --no-print-directory post-build
else
main-build: $(ALL_IMAGE)
	@echo "# linking with libraries $(LINK_LIBRARIES)"
	@echo "# linking with libraries flags $(LIBRARIES_DIR)"
	@echo "# making $(PROJECT) completed" "($(shell date))"
	$(Q)$(MAKE) --no-print-directory post-build
endif

sinclude build/sdk.mk
include build/docs.mk

$(call foreach-dir, $(SRC_DIRS))
LINK_LIBRARIES := $(addprefix -l,$(LIBRARIES))


LINKSCRIPT := $(OBJ_OUT)/linkscript.lds
LINKSCRIPT_XIP2 := $(OBJ_OUT)/linkscript_xip2.lds
BOOTLOADER_LINKSCRIPT := $(OBJ_OUT)/bootloader_linkscript.lds
PARAM_LINKSCRIPT := $(OBJ_OUT)/param_linkscript.lds

include components/bsp/soc/boot/bootloader/bootloader.mk

##############################################################
# target
##############################################################


ifeq ($(strip $(ROM_MODE)), 1)
sinclude rom_symbol/$(ROM_VERSION)/rom_dlm_size.mk
$(PARAM_LINKSCRIPT): $(PARAM_LDSCRIPT_S)
	$(Q)$(CC) -E -P $< $(INCLUDE) -Irom_symbol/$(ROM_VERSION) $(LOCAL_INC) $(INC) $(DEFAULT_CFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) -DROM_MODE=$(strip $(ROM_MODE)) -DROM_DLM_SIZE=$(strip $(ROM_DLM_SIZE)) -o $@

$(BOOTLOADER_LINKSCRIPT): $(BOOTLOADER_LDSCRIPT_S)
	$(Q)$(CC) -E -P $< $(INCLUDE) -Irom_symbol/$(ROM_VERSION) $(LOCAL_INC) $(INC) $(DEFAULT_CFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) -DROM_MODE=$(strip $(ROM_MODE)) -DROM_DLM_SIZE=$(strip $(ROM_DLM_SIZE)) -o $@

$(LINKSCRIPT): $(LDSCRIPT_S)
	$(Q)$(CC) -E -P $< $(INC) -Irom_symbol/$(ROM_VERSION) $(DEFAULT_CFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) -DROM_MODE=$(strip $(ROM_MODE)) -DROM_DLM_SIZE=$(strip $(ROM_DLM_SIZE)) -o $@

$(LINKSCRIPT_XIP2): $(LDSCRIPT_XIP2_S)
	$(Q)$(CC) -E -P $< $(INC) -Irom_symbol/$(ROM_VERSION) $(DEFAULT_CFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) -DROM_MODE=$(strip $(ROM_MODE)) -DROM_DLM_SIZE=$(strip $(ROM_DLM_SIZE)) -o $@
else
$(PARAM_LINKSCRIPT): $(PARAM_LDSCRIPT_S)
	$(Q)$(CC) -E -P $< $(INCLUDE) $(LOCAL_INC) $(INC) $(DEFAULT_CFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) -o $@

$(BOOTLOADER_LINKSCRIPT): $(BOOTLOADER_LDSCRIPT_S)
	$(Q)$(CC) -E -P $< $(INCLUDE) -Irom_symbol/$(ROM_VERSION) $(LOCAL_INC) $(INC) $(DEFAULT_CFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) -o $@

$(LINKSCRIPT): $(LDSCRIPT_S)
	$(Q)$(CC) -E -P $< $(INC) -DROM_MODE=$(strip $(ROM_MODE)) $(DEFAULT_CFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) -o $@

$(LINKSCRIPT_XIP2): $(LDSCRIPT_XIP2_S)
	$(Q)$(CC) -E -P $< $(INC) -DROM_MODE=$(strip $(ROM_MODE)) $(DEFAULT_CFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) -o $@
endif

#$(IMAGE_DIR):
#	$(Q)$(MKDIR) $@
#
$(SDK_VERSION_OBJ):

PROJECT_SRC_O = $(patsubst %.c,%.o,$(PROJECT_SRC))

$(PROJECT_SRC_O): $(PROJECT_SRC)
	$(Q)$(CC) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(CFLAGS) $(INCLUDE) $(INC) -c $< -o $@

ifeq ($(strip $(FOTA_OPTION)),2)
$(ELF_XIP2): $(LIB_DEP) $(LINKSCRIPT_XIP2) $(PROJECT_SRC) $(PROJECT_SRC_O) $(SDK_VERSION_OBJ) $(AR_SRC)
	$(Q)if [ ! -d $(IMAGE_DIR) ]; then \
		$(MKDIR) $(IMAGE_DIR); \
	fi
	$(Q)$(CC) $(AR_SRC) $(LIBRARIES_DIR) $(LDFLAGS_PRE) $(PROJECT_SRC_O) $(PROJECT_OBJ) -Wl,--start-group $(LINK_LIBRARIES) $(STATIC_LIB) -Wl,--end-group $(INCLUDE) $(LOCAL_INC) $(INC) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(LDFLAGS) -Xlinker -Map=$(IMAGE_MAP_XIP2) -T $(LINKSCRIPT_XIP2) -o $@ $(SDK_VERSION_OBJ)
endif

$(ELF_XIP1): $(LIB_DEP) $(LINKSCRIPT) $(PROJECT_SRC) $(PROJECT_SRC_O) $(SDK_VERSION_OBJ) $(AR_SRC)
	$(Q)if [ ! -d $(IMAGE_DIR) ]; then \
		$(MKDIR) $(IMAGE_DIR); \
	fi
	$(Q)$(CC) $(AR_SRC) $(LIBRARIES_DIR) $(LDFLAGS_PRE) $(PROJECT_SRC_O) $(PROJECT_OBJ) -Wl,--start-group $(LINK_LIBRARIES) $(STATIC_LIB) -Wl,--end-group $(INCLUDE) $(LOCAL_INC) $(INC) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(LDFLAGS) -Xlinker -Map=$(IMAGE_MAP) -T $(LINKSCRIPT) -o $@ $(SDK_VERSION_OBJ)

#$(IMAGE_DIR)/$(PROJECT)$(ELFSUFFIX): $(LIB_DEP) $(LINKSCRIPT) $(PROJECT_SRC) $(SDK_VERSION_OBJ) $(AR_SRC)
#	$(Q)if [ ! -d $(IMAGE_DIR) ]; then \
#		$(MKDIR) $(IMAGE_DIR); \
#	fi
#	$(Q)for SRC in $(PROJECT_SRC); \
#	do \
#		cd ${CURDIR}/`dirname $$SRC` && $(CC) $(CFLAGS) $(OPTFLAGS) $(INC) -c `basename $$SRC`; \
#	done
#	$(info AR_LIB=$(AR_LIB))
#	$(info AR_SRC=$(AR_SRC))
#	$(Q)$(CC) $(AR_SRC) $(LIBRARIES_DIR) $(LDFLAGS_PRE) $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(PROJECT_SRC))) $(PROJECT_OBJ) -Wl,--start-group $(LINK_LIBRARIES) $(STATIC_LIB) -Wl,--end-group $(INC) $(CFLAGS) $(OPTFLAGS) $(LDFLAGS) -Xlinker -Map=$(IMAGE_DIR)/$(PROJECT).map -T $(LINKSCRIPT) -o $@ $(SDK_VERSION_OBJ)

ifeq ($(strip $(FLASH_MODE)), 1)
ifeq ($(strip $(CHIP_ID)),6006)
ifeq ($(filter FPGAv2 ASIC,$(TARGET_DEF)),)

$(IMAGE_XIP1): $(ELF_XIP1)
	$(Q)$(OBJCOPY) -O binary $< $@

ifeq ($(strip $(FOTA_OPTION)),2)
$(IMAGE_XIP2): $(ELF_XIP2)
	$(Q)$(OBJCOPY) -O binary $< $@
endif

else
$(IMAGE_DIR)/$(PROJECT).bin: $(IMAGE_DIR)/$(PROJECT)$(ELFSUFFIX) utils/flash_header
	$(OBJCOPY) -O binary $< $@.tmp
	utils/test_flash_bin.sh $< $@.tmp $@
endif
else
#6020
$(IMAGE_XIP1): $(ELF_XIP1)
	$(Q)$(OBJCOPY) -O binary $< $@

ifeq ($(strip $(FOTA_OPTION)),2)
$(IMAGE_XIP2): $(ELF_XIP2)
	$(Q)$(OBJCOPY) -O binary $< $@
endif
endif
else
$(IMAGE_DIR)/$(PROJECT).bin: $(IMAGE_DIR)/$(PROJECT)$(ELFSUFFIX)
	$(Q)$(OBJCOPY) -O binary $< $@
	md5sum $@ | awk '{print $$1}' > $(IMAGE_DIR)/$(PROJECT).md5
endif

$(call assert,$(call eq,0,$(call modulo, $(SETTING_PARTITION_USER_RAW_SIZE),4096)), "the SETTING_PARTITION_USER_RAW_SIZE = $(SETTING_PARTITION_USER_RAW_SIZE) but must set 4096's multiple")
$(call assert,$(call eq,0,$(call modulo, $(SETTING_PARTITION_MAIN_SIZE),4096)), "the SETTING_PARTITION_MAIN_SIZE = $(SETTING_PARTITION_MAIN_SIZE) but must set 4096's multiple")

# aMH todo, if A/B partition, this count is 2, if filesystem ota, this count is 1.

ifeq ($(strip $(FOTA_OPTION)),2)
SKIP_MAIN_COUNT=2
else
SKIP_MAIN_COUNT=1
endif

FLASH_FS_ADDR=$(call plus, $(call multiply, $(SETTING_PARTITION_MAIN_SIZE), $(SKIP_MAIN_COUNT)), $(call plus, $(call multiply, 9, 4096), $(SETTING_PARTITION_USER_RAW_SIZE)))
FLASH_TOTAL_SIZE=$(SETTING_FLASH_TOTAL_SIZE)

$(IMAGE_ALL) : $(IMAGE_BL_HDR) $(IMAGE_BL) $(IMAGE_DUMMY) $(IMAGE_SA) $(IMAGE_MAC) $(IMAGE_PAD) $(IMAGE_INFO) $(IMAGE_USER) $(IMAGE_XIP1)
	$(Q)cat $^ > $@
ifeq ($(strip $(FOTA_OPTION)),2)
	$(GEN_IMAGE_FOTA) $(IMAGE_XIP1) $(IMAGE_XIP2)
else
	$(GEN_IMAGE_FOTA) $(IMAGE_XIP1)
endif


$(IMAGE_INI): $(ELF_BL) $(ELF_CFG)
	$(Q)echo "[INFO]" > $@
	$(Q)echo "chip_name=6166" >> $@
	$(Q)echo "" >> $@
	$(Q)echo "[PARTITION0]" >> $@
	$(Q)echo "bin_file=$(notdir $(PROJECT)_bl.bin)" >> $@
	$(Q)echo "start_address=0x0" >> $@
	$(Q)echo "" >> $@
	$(Q)echo "[PARTITION1]" >> $@
	$(Q)echo "bin_file=$(notdir $(PROJECT)_dummy.bin)" >> $@
	$(Q)echo "start_address=0x4000" >> $@
	$(Q)echo "" >> $@
	$(Q)echo "[PARTITION2]" >> $@
	$(Q)echo "bin_file=$(notdir $(PROJECT)_sa.bin)" >> $@
	$(Q)echo "start_address=0x5000" >> $@
	$(Q)echo "" >> $@
	$(Q)echo "[PARTITION3]" >> $@
	$(Q)echo "bin_file=$(notdir $(PROJECT)_mac.bin)" >> $@
	$(Q)echo "start_address=0x6000" >> $@
	$(Q)echo "" >> $@
	$(Q)echo "[PARTITION4]" >> $@
	$(Q)echo "bin_file=$(notdir $(PROJECT)_pad.bin)" >> $@
	$(Q)echo "start_address=0x7000" >> $@
	$(Q)echo "" >> $@
	$(Q)echo "[PARTITION5]" >> $@
	$(Q)echo "bin_file=$(notdir $(PROJECT)_info.bin)" >> $@
	$(Q)echo "start_address=0x8000" >> $@
	$(Q)echo "" >> $@
	$(Q)echo "[PARTITION6]" >> $@
	$(Q)echo "bin_file=$(notdir $(PROJECT)_user.bin)" >> $@
	$(Q)echo "start_address=0x9000" >> $@
	$(Q)echo "" >> $@
	$(Q)echo "[PARTITION7]" >> $@
	$(Q)echo "bin_file=$(notdir $(PROJECT)_xip1.bin)" >> $@
	$(Q)echo "start_address=0x$(call dec2hex, $(call plus, $(call multiply, 9, 4096), $(SETTING_PARTITION_USER_RAW_SIZE)))" >> $@
	$(Q)echo "" >> $@
	$(Q)echo "[PARTITION8]" >> $@
	$(Q)echo "bin_file=$(notdir $(PROJECT)_fs.bin)" >> $@
	$(Q)echo $(FLASH_FS_ADDR) | awk '{printf("start_address=0x%08x",$$0)}' >> $@
	$(Q)echo "" >> $@

#$(IMAGE_DIR)/$(PROJECT)_bl$(ELFSUFFIX): $(BOOTLOADER_LINKSCRIPT) $(LIB_DEP) $(BOOTLOADER_FSRC) $(OBJ_OUT)/libbootloader.a
#	$(Q)if [ ! -d $(IMAGE_DIR) ]; then \
#		$(MKDIR) $(IMAGE_DIR); \
#	fi
#	$(info AR_LIB=$(AR_LIB))
#	$(info AR_SRC=$(AR_SRC))
#	$(info BOOTLOADER_SRC=$(BOOTLOADER_SRC))
#	$(info BOOTLOADER_LIB=$(BOOTLOADER_LIB))
#	$(Q)$(CC) $(BOOTLOADER_LIB) $(LIBRARIES_DIR) $(LDFLAGS_PRE) $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(BOOTLOADER_SRC))) $(PROJECT_OBJ) -Wl,--start-group $(LINK_LIBRARIES) $(STATIC_LIB) -Wl,--end-group $(INC) $(CFLAGS) $(BL_OPTFLAGS) $(LDFLAGS) -Xlinker -Map=$(IMAGE_DIR)/$(PROJECT).map -T $(BOOTLOADER_LINKSCRIPT) -o $@

burn_bl: $(IMAGE_BL)
ifeq ($(strip $(SECURE_ROM)),1)
	$(IMAGE_DIR)/SPI_burn --addr 0x40 -s --chip $(CHIP_ID) --image $(IMAGE_DIR)/$(PROJECT)_bl.bin
else
	$(IMAGE_DIR)/SPI_burn -s --chip $(CHIP_ID) --image $(IMAGE_DIR)/$(PROJECT)_bl.bin
endif

burn_fs: $(IMAGE_FS)
	$(IMAGE_DIR)/SPI_burn --addr 0x$(call dec2hex, $(FLASH_FS_ADDR)) --chip $(CHIP_ID) --image $(IMAGE_DIR)/$(PROJECT)_fs.bin

burn: $(IMAGE_ALL)
	$(IMAGE_DIR)/SPI_burn -s --chip $(CHIP_ID) --image $(IMAGE_ALL)

burn_mac: $(IMAGE_MAC)
	$(IMAGE_DIR)/SPI_burn -s --addr 0x6000 --chip $(CHIP_ID) --image $<

burn_xip1: $(IMAGE_XIP1)
	$(IMAGE_DIR)/SPI_burn -s --chip $(CHIP_ID) --addr 0x$(call dec2hex, $(call plus, $(call multiply, 9, 4096), $(SETTING_PARTITION_USER_RAW_SIZE))) --image $(IMAGE_XIP1)

$(IMAGE_SA): $(ELF_CFG)
	$(Q)$(OBJCOPY) -j .sa_mp_data_section -O binary $< $@

$(IMAGE_MAC): $(ELF_CFG)
	$(Q)$(OBJCOPY) -j .cfg_mac_data_section -O binary $< $@

$(IMAGE_PAD): $(ELF_CFG)
	$(Q)$(OBJCOPY) -j .cfg_pad_data_section -O binary $< $@

$(IMAGE_INFO): $(ELF_CFG)
	$(Q)$(OBJCOPY) -j .boot_info_section -O binary $< $@

$(IMAGE_USER): $(ELF_CFG)
	$(Q)$(OBJCOPY) -j .user_data_section -O binary $< $@

$(IMAGE_DUMMY): utils/dummy_4k.bin $(IMAGE_INI)
	$(Q)$(CP) $< $@

$(IMAGE_BL_HDR): $(IMAGE_BL)
ifeq ($(strip $(SECURE_BOOT)),1)
	$(Q)./utils/sign_tool.sh $< $@
else
ifeq ($(CHIP_NAME),ssv6020B)
	dd if=/dev/zero of=$@ count=1 bs=64
else
	rm -f $@
	touch $@
endif
endif

$(IMAGE_BL): $(ELF_BL)
	$(Q)$(OBJCOPY) -O binary $< $@

$(IMAGE_ASM): $(ELF_XIP1)
	$(Q)$(OBJDUMP) -d $< -S > $@

unexport CFLAGS
unexport LDFLAGS
unexport CC
$(MKFS):
	$(Q)$(MAKE) -C utils/mkspiffs clean
	$(Q)$(MAKE) -C utils/mkspiffs CC=gcc

$(IMAGE_FS): $(MKFS)
	$(Q)if [ ! -d $(PROJ_DIR)/fs ]; then \
		$(MKDIR) $(PROJ_DIR)/fs; \
	fi
	$< -s $$(($(FLASH_TOTAL_SIZE)-$(FLASH_FS_ADDR))) -c $(PROJ_DIR)/fs $@;

utils/flash_header: utils/flash_header.c
	@echo "$(Q)gcc $< -o $@"
	@echo "$(BUILD_ENV)"
	$(Q)gcc $< -o $@

all_libs: $(addsuffix .a, $(addprefix lib, $(LIBRARIES)))
	$(Q)$(SIZE) $(addsuffix .a, $(addprefix libs/lib, $(LIBRARIES)))

clean:
	$(Q)$(RM) -f utils/flash_header utils/SPI_burn utils/USB_burn utils/*.so utils/*.dll
	$(Q)$(RM) -f $(LOG_TABLE) 2> /dev/null | true
	$(Q)$(RM) -Rf $(TOPDIR)/out 2> /dev/null | true
	$(Q)$(RM) -f $(patsubst %.S,%.o,$(patsubst %.c,%.o,${PROJECT_SRC}))
	$(Q)$(RM) -f $(ALL_IMAGE)
	$(Q)$(RM) -f image/string_table.json
	$(Q)$(RM) -f $(IMAGE_DIR)/ssv_desc.h
	@echo "clean all completed" "($(shell date))"
#$(Q)$(RM) -Rf $(IMAGE_DIR) 2> /dev/null | true
	
distclean: flashtool_clean
	make bootloader_clean
	make clean
	$(Q)$(RM) -f $(BUILD)/project_cfg.mk
	@echo "distclean all completed" "($(shell date))"
	
#bootloader:
#	@if [ -f "$(PROJ_DIR)/src/bootloader/bootloader.mk" ]; then \
#		echo "build bootloader"; \
#		make -f $(PROJ_DIR)/src/bootloader/bootloader.mk; \
#		mkdir -p $(IMAGE_DIR) && cp -f $(PROJ_DIR)/src/bootloader/bootloader.elf $(PROJ_DIR)/src/bootloader/bootloader.bin $(PROJ_DIR)/src/bootloader/bootloader.map $(PROJ_DIR)/src/bootloader/bootloader.asm $(IMAGE_DIR)/; \
#		echo bootloader size $$(stat -c%s $(IMAGE_DIR)/bootloader.bin); \
#	else \
#		echo "bootloader.mk not found"; \
#	fi
#
#bootloader_clean:
#	@if [ -f "$(PROJ_DIR)/src/bootloader/bootloader.mk" ]; then \
#		echo "clean bootloader"; \
#		make -f $(PROJ_DIR)/src/bootloader/bootloader.mk clean; \
#		rm -f $(IMAGE_DIR)/bootloader.elf $(IMAGE_DIR)/bootloader.bin $(IMAGE_DIR)/bootloader.map $(IMAGE_DIR)/bootloader.asm; \
#	else \
#		echo "bootloader.mk not found"; \
#	fi
	
flashtool:
ifeq ($(strip $(BUILD_ENV)), Linux)
	@cd $(TOPDIR)/utils/src-SPI_burn; \
	rm -f *.o; \
	make EXTRA_CFLAGS+=-DLINUX EXTRA_CFLAGS+=-DFLASH_CTL_v2 EXTRA_CFLAGS+=-DSPI_BURN --makefile=Makefile_SPIburn_linux; \
	mkdir -p $(IMAGE_DIR); \
	cp -f SPI_burn $(IMAGE_DIR)/;
ifeq ($(strip $(HOST_ARCH)), x86_64)
	#rm -f *.o; \
	#make EXTRA_CFLAGS+=-DLINUX EXTRA_CFLAGS+=-DFLASH_CTL_v2 EXTRA_CFLAGS+=-DUSB_BURN --makefile=Makefile_USBburn_linux; \
	#cp -f USB_burn linux_x64/*.so $(IMAGE_DIR)/;
else
	#rm -f *.o; \
	#make EXTRA_CFLAGS+=-DLINUX EXTRA_CFLAGS+=-DFLASH_CTL_v2 EXTRA_CFLAGS+=-DUSB_BURN --makefile=Makefile_USBburn_linux; \
	#cp -f USB_burn linux_x86/*.so $(IMAGE_DIR)/;
endif
	echo "done"
else
	cd $(TOPDIR)/utils/src-SPI_burn; \
	rm -f *.o; \
	make EXTRA_CFLAGS+=-DFLASH_CTL_v2 EXTRA_CFLAGS+=-DSPI_BURN --makefile=Makefile_SPIburn_win; \
	mkdir -p $(IMAGE_DIR); \
	cp -f SPI_burn $(IMAGE_DIR)/; \
	rm -f *.o; \
	make EXTRA_CFLAGS+=-DFLASH_CTL_v2 EXTRA_CFLAGS+=-DUSB_BURN --makefile=Makefile_USBburn_win; \
	cp -f USB_burn cygwin/*.dll $(IMAGE_DIR)/; \
	echo "build done"
endif

flashtool_clean:
ifeq ($(strip $(BUILD_ENV)), Linux)
	@cd $(TOPDIR)/utils/src-SPI_burn; \
	make EXTRA_CFLAGS+=-DLINUX EXTRA_CFLAGS+=-DFLASH_CTL_v2 EXTRA_CFLAGS+=-DSPI_BURN --makefile=Makefile_SPIburn_linux clean; \
	#make EXTRA_CFLAGS+=-DLINUX EXTRA_CFLAGS+=-DFLASH_CTL_v2 EXTRA_CFLAGS+=-DUSB_BURN --makefile=utils/src-SPI_burn/Makefile_USBburn_linux clean; \
	echo "clean done"
else
	@cd $(TOPDIR)/utils/src-SPI_burn; \
	make EXTRA_CFLAGS+=-DFLASH_CTL_v2 EXTRA_CFLAGS+=-DSPI_BURN --makefile=Makefile_SPIburn_win clean; \
	make EXTRA_CFLAGS+=-DFLASH_CTL_v2 EXTRA_CFLAGS+=-DUSB_BURN --makefile=Makefile_USBburn_win clean; \
	echo "clean done"
endif

	
.SECONDARY: $(TMP_SRC)
#
#_link: $(LDSCRIPT) $(SRC_DIRS)
#	@echo "# link ...\n" $(shell cat .build)
#	@$(CC) $(CFLAGS) $(LDFLAGS) $(shell cat .build) -Wl,--start-group $(LIB_OBJS) -Wl,--end-group \
#            -Xlinker -Map=$(IMAGE_NAME).map \
#            -o $(IMAGE_NAME).axf
#	@$(OBJCOPY) -O binary $(IMAGE_NAME).axf $(IMAGE_NAME).bin
#	@$(OBJDUMP) -d $(IMAGE_NAME).axf -S > $(IMAGE_NAME).asm
#	@$(SIZE)    -d $(IMAGE_NAME).axf
#
#$(LDSCRIPT): $(LDSCRIPT_S)
#	@echo "# build ld ...\n $<"
#	@$(CC) $(CFLAGS) -E -P $< -o $(LDSCRIPT)
#	@cat $(ICMD_SYMBOLS) >> $(LDSCRIPT)
#
#target_check:
#	@if [ "$(PROJECT)" = "" ]; then \
#	    echo "! no project specified"; \
#	    exit 0; \
#	fi
#	@$(RM) -rf .build
#	@echo "# make project $(PROJECT)"
#	@if ! [ -d $(IMAGE_DIR) ]; then mkdir $(IMAGE_DIR); fi
#
#clean: _clean
#	@echo "# clean ..."
#	@$(RM) $(LDSCRIPT)

#.DEFAULT_GOAL =

##############################################################
# Make rules
##############################################################
include $(BUILD)/rules.mk
include $(BUILD)/tool.mk

else
$(info Please use 3.82 or higher version)

all: utils/make
	@utils/make
	@echo "\033[0;31m"
	@echo Please update the make tool to 3.82
	@echo You can use this command
	@echo cd utils \&\& sudo make install
	@echo "\033[0m"

utils/make:
	@cd utils && third_party/make-3.82/configure
	@$(MAKE) -C utils
	@utils/make --version
	@echo "\033[0;31m"
	@echo Please update the make tool to 3.82
	@echo You can use this command
	@echo cd utils \&\& sudo make install
	@echo "\033[0m"

setup: utils/make
	@utils/make $(MAKECMDGOALS) p=$(p)
	@echo "\033[0;31m"
	@echo Please update the make tool to 3.82
	@echo You can use this command
	@echo cd utils \&\& sudo make install
	@echo "\033[0m"

clean: utils/make
	@utils/make $(MAKECMDGOALS)
	@echo "\033[0;31m"
	@echo Please update the make tool to 3.82
	@echo You can use this command
	@echo cd utils \&\& sudo make install
	@echo "\033[0m"

.DEFAULT_GOAL = all
#.PHONY: all

endif

