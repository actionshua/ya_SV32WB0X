TOUT := $(OBJ_OUT)

define inc-imm
	include $(1)
endef



define inc-module
$(eval MYDIR := $(1))
LIBRARY_NAME :=
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=
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
#########################################################################################
#########################################################################################

define build-lib
ifeq ($(filter clean distclean setup list_projects sync_subprojects build-sdk update-sdk bootloader bootloader_clean flashtool flashtool_clean,$(MAKECMDGOALS)),)
-include $$(addprefix $(TOUT)/$(7)/,$$(patsubst %.cpp,%.d,$$(patsubst %.c,%.d,$(2))))
-include $$(addprefix $(TOUT)/$(7)/,$$(patsubst %.S,%.d,$(3)))
endif

$(TOUT)/$(7)/%.d: $(TOPDIR)/$(7)/%.c
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CC) $(STD_CFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -MM -MT $$(patsubst %.d,%.c,$$@) -MF $$@ $$(patsubst $(TOUT)/$(7)%,$(7)%,$$<) 2>&1 | tee -a build_error.log

$(TOUT)/$(7)/%.d: $(TOPDIR)/$(7)/%.cpp
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CC) $(STD_CPPFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -MM -MT $$(patsubst %.d,%.cpp,$$@) -MF $$@ $$(patsubst $(TOUT)/$(7)%,$(7)%,$$<) 2>&1 | tee -a build_error.log

$(TOUT)/$(7)/%.d: $(TOPDIR)/$(7)/%.S
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CC) $(DEFAULT_AFLAGS) $(OPTFLAGS) $(LOCAL_AFLAGS) $(AFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -MM -MT $$(patsubst %.d,%.S,$$@) -MF $$@ $$(patsubst $(TOUT)/$(7)%,$(7)%,$$<) 2>&1 | tee -a build_error.log

$(TOUT)/$(7)/%.c: $(TOPDIR)/$(7)/%.c
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CC) $(STD_CFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -E $$< -o $$@ 2>&1 | tee -a build_error.log
ifneq ($(strip $(SUPPORT_ILOG)), 0)
	$(Q)utils/locker.sh image/string_table.json
	$(Q)utils/icomm_log_parser -string-table-json=image/string_table.json $$@ -- 2>/dev/null
	$(Q)utils/unlocker.sh image/string_table.json
endif

$(TOUT)/$(7)/%.cpp: $(TOPDIR)/$(7)/%.cpp
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CC) $(_CPPFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -E $$< -o $$@ 2>&1 | tee -a build_error.log
ifneq ($(strip $(SUPPORT_ILOG)), 0)
	$(Q)utils/locker.sh image/string_table.json
	$(Q)utils/icomm_log_parser -string-table-json=image/string_table.json $$@ -- 2>/dev/null
	$(Q)utils/unlocker.sh image/string_table.json
endif
	
	
$(TOUT)/$(7)/%.S: $(TOPDIR)/$(7)/%.S
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CC) $(DEFAULT_AFLAGS) $(OPTFLAGS) $(LOCAL_AFLAGS) $(AFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(6) $(5) -E $$< -o $$@ 2>&1 | tee -a build_error.log

$(TOUT)/$(7)/%.o: $(TOUT)/$(7)/%.c
	$(Q)$(CC) $(STD_CFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -c $$< -o $$@ 2>&1 | tee -a build_error.log
	$(Q)$(SIZE) $$@

$(TOUT)/$(7)/%.o: $(TOUT)/$(7)/%.cpp
	$(Q)$(CC) $(_CPPFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -c $$< -o $$@ 2>&1 | tee -a build_error.log
	$(Q)$(SIZE) $$@


$(TOUT)/$(7)/%.o: $(TOUT)/$(7)/%.S
	$(Q)$(CC) $(DEFAULT_AFLAGS) $(OPTFLAGS) $(LOCAL_AFLAGS) $(AFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(6) $(5) -c $$< -o $$@ 2>&1 | tee -a build_error.log
	$(Q)$(SIZE) $$@


$(TOUT)/$(7)/lib$(1)$(LIBSUFFIX): $(addprefix $(TOUT)/$(7)/,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(2)))) $(addprefix $(TOUT)/$(7)/,$(patsubst %.S,%.o,$(3)))
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)echo "const char $(1)lib_version[] = \"#VERSION_START#" $(LIB_VERSION) "#VERSION_END#\";" > $$@.c
	$(Q)echo "const char $(1)lib_customer[] = \"#CUSTOMER_START#" $(CUSTOMER) "#CUSTOMER_END#\";" >> $$@.c
	$(Q)$(CC) -c $$@.c -o $$@.o
	$(Q)$(AR) -rsc $$@ $$^ $$@.o

libs/lib$(1)$(LIBSUFFIX): $(TOUT)/$(7)/lib$(1)$(LIBSUFFIX)
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CP) $$^ $$@

lib$(1)$(LIBSUFFIX): libs/lib$(1)$(LIBSUFFIX)

clean_$(TOUT)/$(7):
	$(Q)$(RM) $(addprefix $(TOUT)/$(7)/,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(2)))) $(addprefix $(TOUT)/$(7)/,$(patsubst %.S,%.o,$(3))) 2>/dev/null | true
	$(Q)$(RM) $(addprefix $(TOUT)/$(7)/,$(patsubst %.cpp,%.d,$(patsubst %.c,%.d,$(2)))) $(addprefix $(TOUT)/$(7)/,$(patsubst %.S,%.d,$(3))) 2>/dev/null | true
	$(Q)$(RM) $(addprefix $(TOUT)/$(7)/,$(2)) $(addprefix $(TOUT)/$(7)/,$(3)) 2>/dev/null | true
	$(Q)$(RM) $(TOUT)/$(7)/lib$(1)$(LIBSUFFIX).c $(TOUT)/$(7)/lib$(1)$(LIBSUFFIX).o 2>/dev/null | true
	$(Q)$(RM) $(TOUT)/$(7)/lib$(1)$(LIBSUFFIX) 2>/dev/null | true

$(eval LLNAME := $(TOUT)/$(7)/lib$(1)$(LIBSUFFIX))
LIBRARIES += $(1)
LIB_DEP += $(TOUT)/$(7)/lib$(1)$(LIBSUFFIX)
TMP_SRC += $(addprefix $(TOUT)/$(7)/,$(2)) $(addprefix $(TOUT)/$(7)/,$(3))
endef

define build-obj
ifeq ($(filter clean distclean setup list_projects sync_subprojects build-sdk update-sdk bootloader bootloader_clean flashtool flashtool_clean,$(MAKECMDGOALS)),)
-include $$(addprefix $(TOUT)/$(7)/,$$(patsubst %.cpp,%.d,$$(patsubst %.c,%.d,$(2))))
-include $$(addprefix $(TOUT)/$(7)/,$$(patsubst %.S,%.d,$(3)))
endif

$(TOUT)/$(7)/%.d: $(TOUT)/$(7)/%.c
	$(Q)$(CC) $(STD_CFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -MM -MT $$(patsubst %.d,%.c,$$@) -MF $$@ $$(patsubst $(TOUT)/$(7)%,$(7)%,$$<) 2>&1 | tee -a build_error.log

$(TOUT)/$(7)/%.d: $(TOUT)/$(7)/%.cpp
	$(Q)$(CC) $(STD_CPPFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -MM -MT $$(patsubst %.d,%.cpp,$$@) -MF $$@ $$(patsubst $(TOUT)/$(7)%,$(7)%,$$<) 2>&1 | tee -a build_error.log


$(TOUT)/$(7)/%.d: $(TOUT)/$(7)/%.S
	$(Q)$(CC) $(DEFAULT_AFLAGS) $(OPTFLAGS) $(LOCAL_AFLAGS) $(AFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -MM -MT $$(patsubst %.d,%.S,$$@) -MF $$@ $$(patsubst $(TOUT)/$(7)%,$(7)%,$$<) 2>&1 | tee -a build_error.log

$(TOUT)/$(7)/%.c: $(TOPDIR)/$(7)/%.c
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CC) $(STD_CFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -E $$< -o $$@ 2>&1 | tee -a build_error.log

$(TOUT)/$(7)/%.c: $(TOPDIR)/$(7)/%.cpp
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CC) $(STD_CPPFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -E $$< -o $$@ 2>&1 | tee -a build_error.log

$(TOUT)/$(7)/%.S: $(TOPDIR)/$(7)/%.S
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CC) $(DEFAULT_AFLAGS) $(OPTFLAGS) $(LOCAL_AFLAGS) $(AFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(6) $(5) -E $$< -o $$@ 2>&1 | tee -a build_error.log

$(TOUT)/$(7)/%.o: $(TOUT)/$(7)/%.c
	$(Q)$(CC) $(STD_CFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -c $$< -o $$@ 2>&1 | tee -a build_error.log
	$(Q)$(SIZE) $$@

$(TOUT)/$(7)/%.o: $(TOUT)/$(7)/%.cpp
	$(Q)$(CC) $(STD_CPPFLAGS) $(DEFAULT_CFLAGS) $(OPTFLAGS) $(LOCAL_CFLAGS) $(CFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(4) $(5) -c $$< -o $$@ 2>&1 | tee -a build_error.log
	$(Q)$(SIZE) $$@

$(TOUT)/$(7)/%.o: $(TOUT)/$(7)/%.S
	$(Q)$(CC) $(DEFAULT_AFLAGS) $(OPTFLAGS) $(LOCAL_AFLAGS) $(AFLAGS) $(INCLUDE) $(LOCAL_INC) $(INC) $(6) $(5) -c $$< -o $$@ 2>&1 | tee -a build_error.log
	$(Q)$(SIZE) $$@

$(TOUT)/$(7)/lib$(1)$(TARSUFFIX): $(addprefix $(TOUT)/$(7)/,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(2)))) $(addprefix $(TOUT)/$(7)/,$(patsubst %.S,%.o,$(3)))
	$(Q)echo "const char $(1)lib_version[] = \"#VERSION_START#" $(LIB_VERSION) "#VERSION_END#\";" > $$@.c
	$(Q)echo "const char $(1)lib_customer[] = \"#CUSTOMER_START#" $(CUSTOMER) "#CUSTOMER_END#\";" >> $$@.c
	$(Q)$(CC) -c $$@.c -o $$@.o
	$(Q)$(STRIP) -d $$^
	$(Q)$(TAR) cf $$@ $$^ $$@.o

libs/lib$(1)$(TARSUFFIX): $(TOUT)/$(7)/lib$(1)$(TARSUFFIX)
	$(Q)if [ ! -d $$(dir $$@) ]; then \
		$(MKDIR) $$(dir $$@); \
	fi
	$(Q)$(CP) $$^ $$@

lib$(1)$(TARSUFFIX): libs/lib$(1)$(TARSUFFIX)

clean_$(TOUT)/$(7):
	$(Q)$(RM) $(addprefix $(TOUT)/$(7)/,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(2)))) $(addprefix $(TOUT)/$(7)/,$(patsubst %.S,%.o,$(3))) 2>/dev/null | true
	$(Q)$(RM) $(addprefix $(TOUT)/$(7)/,$(patsubst %.cpp,%.d,$(patsubst %.c,%.d,$(2)))) $(addprefix $(TOUT)/$(7)/,$(patsubst %.S,%.d,$(3))) 2>/dev/null | true
	$(Q)$(RM) $(addprefix $(TOUT)/$(7)/,$(2)) $(addprefix $(TOUT)/$(7)/,$(3)) 2>/dev/null | true
	$(Q)$(RM) $(TOUT)/$(7)/lib$(1)$(TARUFFIX).c $(TOUT)/$(7)/lib$(1)$(TARSUFFIX).o 2>/dev/null | true
	$(Q)$(RM) $(TOUT)/$(7)/lib$(1)$(TARSUFFIX) 2>/dev/null | true

$(eval LLNAME := $(TOUT)/$(7)/lib$(1)$(TARSUFFIX))
AR_SRC += $(addprefix $(TOUT)/$(7)/,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(2)))) $(addprefix $(TOUT)/$(7)/,$(patsubst %.S,%.o,$(3)))
BOBJ_SRC += $(addprefix $(7)/,$(2)) $(addprefix $(7)/,$(3))
AR_LIB += $(1)
LIB_DEP += $(TOUT)/$(7)/lib$(1)$(TARSUFFIX)
TMP_SRC += $(addprefix $(TOUT)/$(7)/,$(2)) $(addprefix $(TOUT)/$(7)/,$(3))
endef

define clear-lib-internal
endef

###$(eval $(call build-lib-internal,$(1),$(2)))
# $(1) = LIBRARY_NAME
# $(2) = LIB_SRC
# $(3) = LIB_ASRC
# $(4) = LOCAL_CFLAGS
# $(5) = LOCAL_INC
# $(6) = LOCAL_AFLAGS
# $(7) = MYDIR
#define build-lib
#	$(eval $(call build-lib-internal,$(1),$(2),$(3),$(4),$(5),$(6)))
#endef
