TOUT := out

define inc-imm
	include $(1)
endef



define inc-module
	MYDIR := $(1)
	LIBRARY_NAME :=
	LOCAL_CFLAGS :=
	LOCAL_INC := -I$(1)
	LIBRARIES_DIR += -L$(TOUT)/$(1)
	CLEAN_RULE += clean_$(TOUT)/$(1)
	sinclude $(1)/module.mk
endef
#LIBRARIES += $(LIBRARY_NAME)
#LIB_DEP += $(TOUT)/$(1)/lib$(LIBRARY_NAME)$(LIBSUFFIX)

define foreach-dir
	$(foreach d,$(1), $(eval $(call inc-module,$(d))))
endef

#$(TOUT)/$(MYDIR):
#	@echo make dir $@
#	$(MKDIR) $$@

#-idx-shift=0x20000000

#$(TOUT)/$(MYDIR)/%.o: $(TOUT)/$(MYDIR)/%.c
#	$(Q)$(CC) $(CFLAGS) $(INC) $(LOCAL_CFLAGS) $(LOCAL_INC) -c $$< -o $$@
#	$(Q)$(SIZE) $$@

#	$(Q)$(RM) $(TOUT)/$(MYDIR)/*.o 2>/dev/null | true
#	$(Q)$(RM) $(TOUT)/$(MYDIR)/*.a 2>/dev/null | true

define build-lib-internal
$(TOUT)/$(MYDIR)/%.c: $(TOPDIR)/$(MYDIR)/%.c
	$(Q)$(MKDIR) $$(dir $$@)
	$(Q)$(CC) $(CFLAGS) $(INC) $(LOCAL_CFLAGS) $(LOCAL_INC) -E $$< -o $$@
	$(Q)$(LOCK) $(TOUT)/string_table.json
	$(Q)$(LOG) -string-table-json=$(TOUT)/string_table.json $$@ -- 2> /dev/zero
	$(Q)$(UNLOCK) $(TOUT)/string_table.json

$(TOUT)/$(MYDIR)/%.S: $(TOPDIR)/$(MYDIR)/%.S
	$(Q)$(MKDIR) $$(dir $$@)
	$(Q)$(CC) $(AFLAGS) $(INC) $(LOCAL_AFLAGS) $(LOCAL_INC) -E $$< -o $$@

$(TOUT)/$(MYDIR)/%.o: $(TOUT)/$(MYDIR)/%.c
	$(Q)$(CC) $(CFLAGS) $(INC) $(LOCAL_CFLAGS) $(LOCAL_INC) -c $$< -o $$@
	$(Q)$(SIZE) $$@

$(TOUT)/$(MYDIR)/%.o: $(TOUT)/$(MYDIR)/%.S
	$(Q)$(CC) $(AFLAGS) $(INC) $(LOCAL_AFLAGS) $(LOCAL_INC) -c $$< -o $$@
	$(Q)$(SIZE) $$@

$(TOUT)/$(MYDIR)/lib$(1)$(LIBSUFFIX): $(addprefix $(TOUT)/$(MYDIR)/,$(patsubst %.c,%.o,$(2))) $(addprefix $(TOUT)/$(MYDIR)/,$(patsubst %.S,%.o,$(3)))
	$(Q)echo "char lib_version[] = \"#VERSION_START#" $(LIB_VERSION) "#VERSION_END#\";" > $$@.c
	$(Q)$(CC) -c $$@.c -o $$@.o
	$(Q)$(AR) -rsc $$@ $$^ $$@.o

libs/lib$(1)$(LIBSUFFIX): $(TOUT)/$(MYDIR)/lib$(1)$(LIBSUFFIX)
	$(Q)$(MKDIR) $$(dir $$@)
	$(Q)$(CP) $$^ $$@

lib$(1)$(LIBSUFFIX): libs/lib$(1)$(LIBSUFFIX)


clean_$(TOUT)/$(MYDIR):
	$(Q)$(RM) $(addprefix $(TOUT)/$(MYDIR)/,$(patsubst %.c,%.o,$(2))) $(addprefix $(TOUT)/$(MYDIR)/,$(patsubst %.S,%.o,$(3))) 2>/dev/null | true
	$(Q)$(RM) $(TOUT)/$(MYDIR)/lib$(1)$(LIBSUFFIX) 2>/dev/null | true

$(eval LLNAME := $(TOUT)/$(MYDIR)/lib$(1)$(LIBSUFFIX))
LIBRARIES += $(1)
LIB_DEP += $(TOUT)/$(MYDIR)/lib$(1)$(LIBSUFFIX)
TMP_SRC += $(addprefix $(TOUT)/$(MYDIR)/,$(2)) $(addprefix $(TOUT)/$(MYDIR)/,$(3))
endef

define clear-lib-internal
endef

####$(eval $(call build-lib-internal,$(1),$(2)))
define build-lib
	$(eval $(call build-lib-internal,$(1),$(2),$(3)))
endef
