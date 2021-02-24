LOCAL_VAR := 

LIB_SRC := acoustic_alg.c

LIB_ASRC :=
LIBRARY_NAME := acoustic_alg
LOCAL_CFLAGS += -ffunction-sections -fdata-sections
LOCAL_AFLAGS += -ffunction-sections -fdata-sections
LOCAL_INC :=
LOCAL_INC += -Icomponents/third_party/acoustic_algorithm
RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
