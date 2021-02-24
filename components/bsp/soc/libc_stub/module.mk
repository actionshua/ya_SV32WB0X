LIB_SRC      := libc_patch.c
LIB_SRC      += printf_patch.c

LIB_ASRC     := _sbrk.S
LIBRARY_NAME := libc_stub
LOCAL_CFLAGS := 
LOCAL_AFLAGS := 
LOCAL_INC    := -Icomponents/drv
LOCAL_INC    += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/uart
LOCAL_INC    += -Icomponents/tools/toolbox

RELEASE_SRC  := 2

$(eval $(call build-obj,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
