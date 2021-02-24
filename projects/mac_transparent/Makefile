Q        := @

ROOTDIR  := ../../
CURDIR   := $(shell pwd)
OUT      := $(CURDIR)/out
IMAGE    := $(CURDIR)/image
PROJECT  := $(shell basename $(CURDIR))
PROJ_DIR := $(subst $(realpath $(ROOTDIR))/,,$(realpath .))

all:
	$(Q)mkdir -p out
	$(Q)mkdir -p image
	$(Q)echo MAKEFLAGS = $(MAKEFLAGS)
	$(Q)$(MAKE) -C $(ROOTDIR) OBJ_OUT=$(OUT) IMAGE_DIR=$(IMAGE) IMAGE=$(IMAGE) PROJECT=$(PROJECT) PROJ_DIR=$(PROJ_DIR) IN_PROJ=1

burn:
	$(Q)$(MAKE) -C $(ROOTDIR) OBJ_OUT=$(OUT) IMAGE_DIR=$(IMAGE) IMAGE=$(IMAGE) PROJECT=$(PROJECT) PROJ_DIR=$(PROJ_DIR) IN_PROJ=1 burn

burn_bl:
	$(Q)$(MAKE) -C $(ROOTDIR) OBJ_OUT=$(OUT) IMAGE_DIR=$(IMAGE) IMAGE=$(IMAGE) PROJECT=$(PROJECT) PROJ_DIR=$(PROJ_DIR) IN_PROJ=1 burn_bl

burn_fs:
	$(Q)$(MAKE) -C $(ROOTDIR) OBJ_OUT=$(OUT) IMAGE_DIR=$(IMAGE) IMAGE=$(IMAGE) PROJECT=$(PROJECT) PROJ_DIR=$(PROJ_DIR) IN_PROJ=1 burn_fs

clean:
	$(Q)rm -rf $(OUT) $(IMAGE)
	$(Q)echo clean $(PROJECT)
