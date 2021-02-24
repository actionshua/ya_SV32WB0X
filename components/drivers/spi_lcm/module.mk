
LIB_SRC := spi_lcm_hw.c
LIB_SRC += spi_lcm.c
LIB_SRC += gc9306/gc9306.c
LIB_SRC += ili9341/ili9341.c

LIB_ASRC :=
LIBRARY_NAME := spi_lcm
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(PROJ_DIR)/src/board/param
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/spimst
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/dmac
LOCAL_INC += -Icomponents/drv/spimst
LOCAL_INC += -Icomponents/drv/dmac
LOCAL_INC += -I$(MYDIR)
LOCAL_INC += -I$(MYDIR)/gc9306

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
