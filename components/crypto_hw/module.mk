LIB_SRC := crypto_aes.c
LIB_SRC += crypto_gcm.c
LIB_SRC += crypto_gf128mul.c
LIB_SRC += crypto_sha1.c
LIB_SRC += crypto_sha256.c
LIB_SRC += crypto_sha512.c
LIB_SRC += crypto_trng.c
LIB_SRC += crypto_common.c

LIB_ASRC :=
LIBRARY_NAME := crypto_hw
LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS +=
LOCAL_INC += -I$(TOPDIR)/components/third_party/mbedtls/include
LOCAL_INC += -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/bsp/soc/ssv6020
LOCAL_INC += -I$(TOPDIR)/components/crypto
LOCAL_INC += -I$(TOPDIR)/components/crypto_hw
LOCAL_INC += -I$(TOPDIR)/components/osal

RELEASE_SRC := 1

$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
