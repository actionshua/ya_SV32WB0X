
LIB_SRC := drv_adcbtn.c

LIB_ASRC :=
LIBRARY_NAME := adcbtn
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -Icomponents/bsp/soc/$(CHIP_NAME)/hal/adc
LOCAL_INC += -Icomponents/drv/adc

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
