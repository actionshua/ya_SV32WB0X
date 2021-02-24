LVGL_DIR := $(MYDIR)/lv_sim_eclipse_sdl

CFLAGS_KEEP := $(CFLAGS)

include $(LVGL_DIR)/lvgl/src/lv_core/lv_core.mk
LITTLEVGL_CSRCS := $(addprefix lv_sim_eclipse_sdl/lvgl/src/lv_core/, $(CSRCS))
CSRCS:=
include $(LVGL_DIR)/lvgl/src/lv_hal/lv_hal.mk
LITTLEVGL_CSRCS += $(addprefix lv_sim_eclipse_sdl/lvgl/src/lv_hal/, $(CSRCS))
CSRCS:=
include $(LVGL_DIR)/lvgl/src/lv_objx/lv_objx.mk
LITTLEVGL_CSRCS += $(addprefix lv_sim_eclipse_sdl/lvgl/src/lv_objx/, $(CSRCS))
CSRCS:=
include $(LVGL_DIR)/lvgl/src/lv_font/lv_font.mk
LITTLEVGL_CSRCS += $(addprefix lv_sim_eclipse_sdl/lvgl/src/lv_font/, $(CSRCS))
CSRCS:=
include $(LVGL_DIR)/lvgl/src/lv_misc/lv_misc.mk
LITTLEVGL_CSRCS += $(addprefix lv_sim_eclipse_sdl/lvgl/src/lv_misc/, $(CSRCS))
CSRCS:=
include $(LVGL_DIR)/lvgl/src/lv_themes/lv_themes.mk
LITTLEVGL_CSRCS += $(addprefix lv_sim_eclipse_sdl/lvgl/src/lv_themes/, $(CSRCS))
CSRCS:=
include $(LVGL_DIR)/lvgl/src/lv_draw/lv_draw.mk
LITTLEVGL_CSRCS += $(addprefix lv_sim_eclipse_sdl/lvgl/src/lv_draw/, $(CSRCS))
CSRCS:=

CFLAGS := $(CFLAGS_KEEP)
#LVGL_DIR := $(TOPDIR)/components/third_party/lvgl/lv_examples
#include $(LVGL_DIR)/lv_examples/lv_examples.mk
LIB_SRC := $(LITTLEVGL_CSRCS)
LIB_SRC += lvgl_sv6020_drivers/lvgl_driver.c
LIB_SRC += lvgl_sv6020_drivers/lvgl_tft/disp_driver.c
#LIB_SRC += lvgl_sv6020_drivers/lvgl_tft/disp_spi.c
#LIB_SRC += lvgl_sv6020_drivers/lvgl_touch/touch_driver.c
#LIB_SRC += lvgl_sv6020_drivers/lvgl_touch/tp_spi.c

# lcm
#LIB_SRC += lvgl_sv6020_drivers/lvgl_tft/ili9341.c
#LIB_SRC += lvgl_sv6020_drivers/lvgl_tft/gc9306.c

# touch
#LIB_SRC += lvgl_sv6020_drivers/lvgl_touch/xpt2046.c

LIB_SRC += lv_sim_eclipse_sdl/lv_examples/lv_apps/sysmon/sysmon.c
LIB_SRC += lv_sim_eclipse_sdl/lv_examples/lv_apps/demo/demo.c
LIB_SRC += lv_sim_eclipse_sdl/lv_examples/lv_apps/demo/img_bubble_pattern.c
LIB_SRC += lv_sim_eclipse_sdl/lv_examples/lv_apps/benchmark/benchmark_bg.c
LIB_SRC += lv_sim_eclipse_sdl/lv_examples/lv_apps/benchmark/benchmark.c

LIB_SRC += gui_task.c
LIB_SRC += terminal/terminal.c

LIB_ASRC :=
LIBRARY_NAME := lvgl_v6
LOCAL_CFLAGS += -Wno-unused-value -Wno-address -DGFX_USE_OS_FREERTOS=TRUE -DGFX_NO_INLINE -Wno-error $(CFLAGS) -DLV_CONF_INCLUDE_SIMPLE -DLV_USE_ANIMATION=1 -DLV_DEMO_WALLPAPER=1
#LOCAL_CFLAGS += -Wno-unused-value -Wno-address -DGFX_USE_OS_FREERTOS=TRUE -DGFX_NO_INLINE -Wno-error $(CFLAGS) -DLV_CONF_INCLUDE_SIMPLE
#LOCAL_CFLAGS += -Wno-unused-value -Wno-address -DGFX_USE_OS_FREERTOS=TRUE -DGFX_NO_INLINE -Wno-error $(CFLAGS) -DLV_CONF_INCLUDE_SIMPLE -DLV_DEMO_SLIDE_SHOW
LOCAL_AFLAGS +=

LOCAL_INC := -I$(MYDIR)
LOCAL_INC += -I$(LVGL_DIR)
LOCAL_INC += -I$(LVGL_DIR)/lvgl
LOCAL_INC += -I$(MYDIR)/lvgl_sv6020_drivers
LOCAL_INC += -I$(MYDIR)/lvgl_sv6020_drivers/lvgl_tft
LOCAL_INC += -I$(LVGL_DIR)/lv_examples
LOCAL_INC += -Icomponents/drivers/spi_lcm
LOCAL_INC += -I$(PROJ_DIR)/src/board/param


#$(error $(LIB_SRC))
RELEASE_SRC := 3
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
