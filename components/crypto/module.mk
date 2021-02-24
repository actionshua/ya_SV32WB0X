LIB_SRC := aes-wrap.c
LIB_SRC += aes-unwrap.c
LIB_SRC += aes-omac1.c
LIB_SRC += sha1-prf.c
LIB_SRC += sha256-prf.c

LIB_SRC += cipher_wrap.c
LIB_SRC += cipher.c
LIB_SRC += ecp.c
LIB_SRC += ecp_curves.c
LIB_SRC += bignum.c
LIB_SRC += cmac.c
LIB_SRC += hmac.c
LIB_SRC += aes.c
LIB_SRC += pkcs5.c
LIB_SRC += platform_util.c
LIB_SRC += arc4.c
LIB_SRC += md.c
LIB_SRC += md5.c
LIB_SRC += md_wrap.c
LIB_SRC += sha1.c
LIB_SRC += sha256.c
ifeq ($(strip $(MBEDTLS_EN)),1)
LIB_SRC += sha512.c
LIB_SRC += chacha20.c
LIB_SRC += ripemd160.c
LIB_SRC += md2.c
LIB_SRC += md4.c
LIB_SRC += crypto_wrap.c
endif

LIB_ASRC :=
LIBRARY_NAME := crypto
LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS +=
LOCAL_INC += -I$(TOPDIR)/components/third_party/mbedtls/include
LOCAL_INC += -I$(TOPDIR)/components/crypto
LOCAL_INC += -I$(TOPDIR)/components/crypto_hw
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos/kernel/Source/include
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos/nds32
LOCAL_INC += -I$(TOPDIR)/components/tools/toolbox
RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
