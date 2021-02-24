#LIB_SRC := cache.c
LIB_SRC := bsp.c
LIB_SRC += nmi.c
LIB_SRC += pfm.c
LIB_SRC += crtbegin.c
LIB_SRC += crtend.c

#LIB_ASRC := start.S
LIB_ASRC := vector_32ivic.S
LIBRARY_NAME := boot
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
