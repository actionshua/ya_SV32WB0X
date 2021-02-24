


LIB_SRC  :=
LIB_ASRC :=

LIBRARY_NAME := nds_port
LOCAL_CFLAGS +=
LOCAL_AFLAGS +=
LOCAL_INC += -Icomponents/bsp/soc/lowpower
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal


ifneq ($(strip $(MCU_DEF)),$(filter $(strip $(MCU_DEF)), $(_SUPPORT_MCU_DEF)))
$(error not supported MCU_DEF = $(MCU_DEF))
endif
ifeq ($(strip $(BUILD_ROM)), 0)
ifeq ($(strip $(MCU_DEF)), ANDES_D10F)

ifeq (1, 1)
LIB_ASRC   += nds32/portasm.S
LIB_SRC    += nds32/port.c
else
# TODO
# LIB_ASRC   += nds32_mpu/portasm.S
# LIB_SRC    += nds32_mpu/port.c
endif

endif
ifeq ($(strip $(MCU_DEF)), ANDES_N10)
LIB_ASRC   += nds32/portasm.S
LIB_SRC    += nds32/port.c
endif
ifeq ($(strip $(MCU_DEF)), ANDES_D10)
LIB_ASRC   += nds32/portasm.S
LIB_SRC    += nds32/port.c
endif
endif

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
