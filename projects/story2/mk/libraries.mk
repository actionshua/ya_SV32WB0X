###################################################################
# Library link
###################################################################
STATIC_LIB  += -lm
IMPORT_DIR  += $(PROJ_DIR)/src/app
ifeq ($(strip $(SETTING_MP3_DECODER)), 1)
IMPORT_DIR  += $(PROJ_DIR)/src/pvmp3_fsal 
else
ifeq ($(strip $(SETTING_MP3_DECODER)), 2)
IMPORT_DIR  += $(PROJ_DIR)/src/helix_fsal
endif
endif
###################################################################
# object link
###################################################################
PROJECT_SRC +=
PROJECT_OBJ +=

