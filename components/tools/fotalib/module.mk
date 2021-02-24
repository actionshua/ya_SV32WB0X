

LIB_SRC := ./src/fota_pp.c
LIB_SRC += ./src/fota_fs.c
LIB_SRC += ./src/fota_pp_acp.c
LIB_SRC += ./src/fota_fs_acp.c
LIB_SRC += ./src/fota_flashdrv.c
LIB_SRC += ./src/fota_common.c

LIB_ASRC :=
LIBRARY_NAME := fota_lib
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -Icomponents/tools/fota_api
LOCAL_INC += -Icomponents/tools/fotalib/inc
LOCAL_INC += -Icomponents/tools/fota_api/fota_lib/inc
LOCAL_INC += -Icomponents/drv
LOCAL_INC += -Icomponents/osal
LOCAL_INC += -Icomponents/third_party/mbedtls/include
LOCAL_INC += -Icomponents/third_party/httpclient/inc
LOCAL_INC += -Icomponents/third_party/tftp
LOCAL_INC += -Icomponents/third_party/spiffs
LOCAL_INC += -Icomponents/sys
LOCAL_INC += -Icomponents/acp

RELEASE_SRC := 1

$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))


