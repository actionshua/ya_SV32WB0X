LIB_SRC := umac/ssvradio.c
LIB_SRC += umac/ieee80211_mac.c
LIB_SRC += umac/wep.c
LIB_SRC += umac/wpa.c
LIB_SRC += umac/eapol.c
LIB_SRC += umac/ieee80211_mgmt.c
LIB_SRC += umac/sta_func.c
LIB_SRC += umac/softap_func.c
LIB_SRC += umac/powersave_main.c
LIB_SRC += umac/ie_parser.c
LIB_SRC += umac/mlme_action.c
LIB_SRC += umac/sae.c
LIB_SRC += umac/ccmp.c
LIB_SRC += umac/bip.c
LIB_SRC += umac/eccp_acce.c
LIB_SRC += umac/rxtask.c

PROJECT_SRC += components/softmac/umac/country_cfg.c

LIB_ASRC :=
LIBRARY_NAME := ssvradio
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/bsp
LOCAL_INC += -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/netstack_wrapper
LOCAL_INC += -I$(TOPDIR)/components/net/udhcp
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/$(LWIP_PATH)/src/include
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/$(LWIP_PATH)/src/include/ipv4
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/$(LWIP_PATH)/ports/icomm/include
LOCAL_INC += -I$(TOPDIR)/components/inc/bsp/$(CHIP_NAME)
LOCAL_INC += -I$(TOPDIR)/components/softmac/lmac/rc/minstrel
LOCAL_INC += -I$(TOPDIR)/components/softmac/lmac/rc/native_rc
LOCAL_INC += -I$(TOPDIR)/components/softmac/lmac/rc
LOCAL_INC += -I$(TOPDIR)/components/softmac/lmac/txrx
LOCAL_INC += -I$(TOPDIR)/components/softmac/umac/repeater
LOCAL_INC += -I$(TOPDIR)/components/third_party/mbedtls/include
LOCAL_INC += -I$(TOPDIR)/components/crypto
LOCAL_INC += -I$(TOPDIR)/components/crypto_hw

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
