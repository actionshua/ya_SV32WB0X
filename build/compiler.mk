CROSS_COMPILER := nds32le-elf-

ifeq ($(strip $(BUILD_OPTION)),DEBUG)
    OPTFLAGS   := -O1
    BL_OPTFLAGS   += -O2 -std=gnu99 -fgnu89-inline
    DBGFLAGS   := -g -ggdb
else
ifeq ($(strip $(BUILD_OPTION)),PERFORMANCE)
    OPTFLAGS   := -O2
    BL_OPTFLAGS   += -O2 -std=gnu99 -fgnu89-inline
    DBGFLAGS   := -g -ggdb
else
    OPTFLAGS   := -Os1
    BL_OPTFLAGS   += -O2 -std=gnu99 -fgnu89-inline
    DBGFLAGS   := -g -ggdb
endif
endif

STD_CPPFLAGS       += -std=c++11
STD_CFLAGS         += -std=gnu99 -fgnu89-inline
DEFAULT_CFLAGS         += -fno-aggressive-loop-optimizations
ifeq ($(strip $(MCU_DEF)), ANDES_D10F)
DEFAULT_CFLAGS         += -mext-dsp \
                          -mcmodel=large
DEFAULT_AFLAGS         += -mext-dsp \
                          -mcmodel=large
#LDFLAGS                += -ldsp -nostdlib
LDFLAGS                += -ldsp
else
ifeq ($(strip $(MCU_DEF)), ANDES_D10)
DEFAULT_CFLAGS         += -mcpu=d1088 -march=v3 -mext-dsp -ldsp\
                          -mcmodel=large
DEFAULT_AFLAGS         += -mcpu=d1088 -march=v3 -mext-dsp -ldsp\
                          -mcmodel=large
LDFLAGS                += -ldsp
else
ifeq ($(strip $(MCU_DEF)), ANDES_N10)
DEFAULT_CFLAGS         += -mcpu=n10 -march=v3 \
                          -mcmodel=large
DEFAULT_AFLAGS         += -mcpu=n10 -march=v3 \
                          -mcmodel=large
else
$(error no define exist mcu!)
endif
endif
endif

ifeq ($(strip $(BUILD_OPTION)), DEBUG)
OPTFLAGS               += -fno-omit-frame-pointer \
                          -mv3push \
                          -mno-fp-as-gp
DEFAULT_AFLAGS         += -fno-omit-frame-pointer \
                          -mv3push \
                          -mno-fp-as-gp
endif

##############################################################
# Build flags
##############################################################

DEFAULT_CFLAGS         += \
                          -malign-functions -falign-functions=4 \
                          -ffunction-sections -fdata-sections -fno-builtin \
                          -Wno-attributes \
                          --short-enums \
                          -Werror \
                          -Wall \
                          -Wno-attributes \
                          -Wno-format \
                          -Wno-unused-function \
                          -Wno-unused-variable \
                          -Wno-unused-but-set-variable \
                          -DLWIP_NOASSERT \
                          -fno-delete-null-pointer-checks

DEFAULT_CFLAGS         += $(GLOBAL_DEF) $(DBGFLAGS) $(BUILD_FLAGS)
DEFAULT_CFLAGS         += -D${TARGET_DEF}
DEFAULT_AFLAGS         += $(GLOBAL_DEF) $(DBGFLAGS) $(BUILD_FLAGS)
DEFAULT_AFLAGS         += -D${TARGET_DEF}

LDFLAGS        += -Wl,--gc-sections
LDFLAGS        += -nostartfiles -Xlinker -M
LDFLAGS        += --specs=nosys.specs -Werror -mcmodel=large -g
