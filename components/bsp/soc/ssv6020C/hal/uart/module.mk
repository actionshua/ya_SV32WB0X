
LIB_SRC := hal_uart.c

LIB_ASRC :=
LIBRARY_NAME := hal_uart
LOCAL_CFLAGS := -Icomponents/bsp/soc/lowpower
LOCAL_AFLAGS :=

RELEASE_SRC := 1

$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
