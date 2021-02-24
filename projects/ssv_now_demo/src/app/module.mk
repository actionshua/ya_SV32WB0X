
LIB_SRC := main.c
LIB_SRC += custom_cmd.c

LIB_ASRC :=
LIBRARY_NAME := application
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/softmac
LOCAL_INC += -I$(TOPDIR)/components/iotapi
LOCAL_INC += -I$(TOPDIR)/components/netstack_wrapper
#LOCAL_INC += -I$(TOPDIR)/components/third_party/fdk_aac_dec_andes/include
#LOCAL_INC += -I$(TOPDIR)/components/third_party/fdk_aac_dec_andes/libAACdec/include
#LOCAL_INC += -I$(TOPDIR)/components/third_party/fdk_aac_dec_andes/libSYS/include

LOCAL_INC += -Icomponents/netstack_wrapper
LOCAL_INC += -Icomponents/net/tcpip/lwip-1.4.0/src/include
LOCAL_INC += -Icomponents/net/tcpip/lwip-1.4.0/ports/icomm/include
LOCAL_INC += -Icomponents/net/tcpip/lwip-1.4.0/src/include/ipv4

LOCAL_INC += -Icomponents/bsp/soc/lowpower

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
