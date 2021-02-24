LIB_SRC := ieee80211_mac_repter.c

LIB_ASRC :=
LIBRARY_NAME := wifi_rept
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/bsp
LOCAL_INC += -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/netstack_wrapper
LOCAL_INC += -I$(TOPDIR)/components/net/udhcp
LOCAL_INC += -I$(TOPDIR)/components/inc/crypto
LOCAL_INC += -I$(TOPDIR)/components/crypto/pmk
LOCAL_INC += -I$(TOPDIR)/components/wpa_supplicant
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/$(LWIP_PATH)/src/include
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/$(LWIP_PATH)/src/include/ipv4
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/$(LWIP_PATH)/ports/icomm/include
LOCAL_INC += -I$(TOPDIR)/components/inc/bsp/$(CHIP_NAME)

RELEASE_SRC := 1

$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
