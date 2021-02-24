

LIB_SRC := fota_api.c
LIB_SRC += fota_lib/src/fota_md5.c
LIB_SRC += fota_lib/src/fota_util.c
ifeq ($(strip $(TFTP_EN)),1)
LIB_SRC += fota_lib/src/fota_tftp.c
endif
ifeq ($(strip $(HTTPC_EN)),1)
LIB_SRC += fota_lib/src/fota_http.c
endif
LIB_SRC += fota_lib/src/fota_raw.c
LIB_SRC += fota_lib/src/fota_process.c
LIB_ASRC :=
LIBRARY_NAME := fota_api
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -Icomponents/tools/fota_api
LOCAL_INC += -Icomponents/tools/fota_api/fota_lib/inc
LOCAL_INC += -Icomponents/tools/fotalib/inc
LOCAL_INC += -Icomponents/drv
LOCAL_INC += -Icomponents/osal
LOCAL_INC += -Icomponents/third_party/mbedtls/include
LOCAL_INC += -Icomponents/crypto
LOCAL_INC += -Icomponents/crypto_hw
LOCAL_INC += -Icomponents/third_party/httpclient/inc
LOCAL_INC += -Icomponents/third_party/tftp
LOCAL_INC += -Icomponents/third_party/spiffs
LOCAL_INC += -Icomponents/sys
LOCAL_INC += -Icomponents/acp

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))


