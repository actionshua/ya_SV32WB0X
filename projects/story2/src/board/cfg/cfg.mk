NAME := cfg

$(NAME)_CFLAGS +=
$(NAME)_INCLUDES += ../../../../components/tools/utility/SSV_cJSON
$(NAME)_INCLUDES += ../../../../components/sys

$(NAME)_SOURCES :=
$(NAME)_SOURCES += sa_cfg.c
$(NAME)_SOURCES += mac_cfg.c
$(NAME)_SOURCES += user_cfg.c
