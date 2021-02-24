define link-lib

libs/lib$(1)$(LIBSUFFIX): $(7)/lib$(1)$(LIBSUFFIX)
	$(Q)$(MKDIR) $$(dir $$@)
	$(Q)$(CP) $$^ $$@

lib$(1)$(LIBSUFFIX): libs/lib$(1)$(LIBSUFFIX)


$(eval LLNAME := $(7)/lib$(1)$(LIBSUFFIX))
LIBRARIES += $(1)
LIB_DEP += $(7)/lib$(1)$(LIBSUFFIX)
LIBRARIES_DIR += -L$(7)

endef

define link-obj

libs/lib$(1)$(TARSUFFIX): $(7)/lib$(1)$(TARSUFFIX)
	$(Q)$(MKDIR) $$(dir $$@)
	$(Q)$(CP) $$^ $$@

$(TOUT)/$(7)/lib$(1)$(TARSUFFIX): $(7)/lib$(1)$(TARSUFFIX)
	$(Q)$(MKDIR) $$(dir $$@)
	$(Q)$(CP) $$^ $$@

$(TOUT)/$(7)/%.o: $(TOUT)/$(7)/lib$(1)$(TARSUFFIX)
	$(Q)$(TAR) xf $$< -C $(TOUT)/../ 2>&1 | tee -a build_error.log
	$(Q)$(SIZE) $$@

lib$(1)$(TARSUFFIX): libs/lib$(1)$(TARSUFFIX)


$(eval LLNAME := $(7)/lib$(1)$(TARSUFFIX))
LIBRARIES_DIR += -L$(7)
AR_SRC += $(addprefix $(TOUT)/$(7)/,$(patsubst %.c,%.o,$(2))) $(addprefix $(TOUT)/$(7)/,$(patsubst %.S,%.o,$(3)))
AR_LIB += $(1)

endef


###$(eval $(call link-lib-internal,$(1),$(2)))
# $(1) = LIBRARY_NAME
#x $(2) = LIB_SRC
#x $(3) = LIB_ASRC
#x $(4) = LOCAL_CFLAGS
#x $(5) = LOCAL_INC
#x $(6) = LOCAL_AFLAGS
# $(7) = MYDIR
#define build-lib
#	$(eval $(call link-lib-internal,$(1),$(2),$(3),$(4),$(5),$(6)))
#endef
