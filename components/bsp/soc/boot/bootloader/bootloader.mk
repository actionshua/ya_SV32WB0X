BOOTLOADER_DIR := components/bsp/soc/boot/bootloader/

BOOTLOADER_SRC := 

BOOTLOADER_ASRC := ota.S

BOOTLOADER_FSRC = $(addprefix ${BOOTLOADER_DIR},${BOOTLOADER_SRC})
BOOTLOADER_FASRC = $(addprefix ${BOOTLOADER_DIR},${BOOTLOADER_ASRC})

BOOTLOADER_FOBJ = $(addprefix $(TOUT)/bl/,$(patsubst %.c,%.o,$(BOOTLOADER_SRC)))
BOOTLOADER_FAOBJ = $(addprefix $(TOUT)/bl/,$(patsubst %.S,%.o,$(BOOTLOADER_ASRC)))

LOCAL_CFLAGS :=
LOCAL_AFLAGS :=
LOCAL_BL_INC := -Icomponents/inc/bsp/$(CHIP_NAME)
LOCAL_BL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/
LOCAL_BL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/$(TARGET_DEF)
LOCAL_BL_INC += -Icomponents/bsp/soc/boot/bootloader/lib
LOCAL_BL_INC += -Icomponents/bsp/soc/boot/bootloader/tiny_printf
LOCAL_BL_INC += -Icomponents/bsp/soc/boot/bootloader/spiffs
LOCAL_BL_INC += -Icomponents/bsp/soc/boot/bootloader/libc
LOCAL_BL_INC += -Icomponents/bsp/soc/boot/bootloader/xmodem
LOCAL_BL_INC += -Icomponents/tools/toolbox

LOCAL_BL_INC += -Icomponents/drv
LOCAL_BL_INC += -Icomponents
LOCAL_BL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)
LOCAL_BL_INC += -I$(PROJ_DIR)/src/board/cfg
LOCAL_BL_INC += -I$(PROJ_DIR)/src/board/inc/custom/$(CHIP_NAME)/$(IC_PACKAGE)

BOOTLOADER_LIB = $(BOOTLOADER_DIR)libbootloader.a

$(TOUT)/bl/%.o: ${BOOTLOADER_DIR}%.c
	$(Q)echo build c $@ $<
	$(Q)if [ ! -d $(dir $@) ]; then \
		$(MKDIR) $(dir $@); \
	fi
	$(Q)$(CC) $(CFLAGS) -g -ggdb $(BL_OPTFLAGS) $(LOCAL_CFLAGS) $(DEFAULT_CFLAGS) $(INC) $(LOCAL_BL_INC) -c $< -o $@ 2>&1 | tee -a build_error.log

$(TOUT)/bl/%.o: ${BOOTLOADER_DIR}%.S
	$(Q)echo build S $@ $<
	$(Q)if [ ! -d $(dir $@) ]; then \
		$(MKDIR) $(dir $@); \
	fi
	$(Q)$(CC) $(AFLAGS) $(BL_OPTFLAGS) $(LOCAL_AFLAGS) $(DEFAULT_AFLAGS) $(INC) $(LOCAL_BL_INC) -c $< -o $@ 2>&1 | tee -a build_error.log

$(BOOTLOADER_LIB):
	$(Q)echo $@

$(IMAGE_DIR)/$(PROJECT)_bl$(ELFSUFFIX): $(BOOTLOADER_LINKSCRIPT) $(BOOTLOADER_LIB) $(BL_CUSTOM)
	$(Q)if [ ! -d $(dir $@) ]; then \
		$(MKDIR) $(dir $@); \
	fi
	$(Q)$(CC) $(CFLAGS) $(BL_OPTFLAGS) $(LOCAL_CFLAGS) $(DEFAULT_CFLAGS) -g -ggdb $(LDFLAGS) -Wl,-Map=$(IMAGE_DIR)/$(PROJECT)_bl.map $(BL_CUSTOM) $(LOCAL_BL_INC) -L$(dir $(BOOTLOADER_LIB)) -lbootloader -T $(BOOTLOADER_LINKSCRIPT) -o $@
	$(Q)$(OBJDUMP) -d $@ > $(IMAGE_DIR)/$(PROJECT)_bl.asm

CFG := $(PROJ_DIR)/src/board/cfg/sa_cfg.c
CFG += $(PROJ_DIR)/src/board/cfg/mac_cfg.c
CFG += $(PROJ_DIR)/src/board/cfg/user_cfg.c
CFG += components/bsp/soc/soc_init/soc_pad_cfg.c

$(IMAGE_DIR)/$(PROJECT)_cfg$(ELFSUFFIX): $(PARAM_LINKSCRIPT) $(CFG)
	$(Q)if [ ! -d $(dir $@) ]; then \
		$(MKDIR) $(dir $@); \
	fi
	$(Q)$(CC) $(CFLAGS) $(BL_OPTFLAGS) $(LOCAL_CFLAGS) $(DEFAULT_CFLAGS) $(LDFLAGS) -Wl,-Map=$(IMAGE_DIR)/$(PROJECT)_cfg.map $(CFG) $(LOCAL_BL_INC) -T $(PARAM_LINKSCRIPT) -o $@

#$(IMAGE_DIR)/$(PROJECT)_bl$(ELFSUFFIX): $(BOOTLOADER_LINKSCRIPT) $(BOOTLOADER_FSRC) $(OBJ_OUT)/libbootloader.a
#	$(Q)if [ ! -d $(dir $@) ]; then \
#		$(MKDIR) $(dir $@); \
#	fi
#	$(Q)$(CC) $(BL_OPTFLAGS) $(LDFLAGS) -Wl,-Map=$(IMAGE_DIR)/$(PROJECT)_bl.map $(PROJ_DIR)/bootloader/custom_ota/boot_init.c $(PROJ_DIR)/bootloader/custom_ota/custom_ota.c $(CFG) $(LOCAL_BL_INC) -L$(OBJ_OUT) -lbootloader -T $(BOOTLOADER_LINKSCRIPT) -o $@
#
#$(eval $(call build-bl-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
