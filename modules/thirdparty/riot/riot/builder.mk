APPLICATION = riot
BOARD ?= native
RIOTBASE ?= $(CURDIR)/RIOT
QUIET ?= 1

OUT ?= "out.txt"

USEMODULE += $(MODULES)

FEATURES_REQUIRED += cpp
USEMODULE += cpp11-compat

include $(RIOTBASE)/Makefile.include

INFOS  = BOARD
INFOS += MCU
INFOS += INCLUDES
INFOS += CFLAGS
INFOS += CXXFLAGS
INFOS += LINKFLAGS
INFOS += USEMODULE
INFOS += STARTUP

CXXFLAGS = $(filter-out $(CXXUWFLAGS), $(CFLAGS)) $(CXXEXFLAGS)
STARTUP = $(subst $(PWD),".",$(UNDEF))

define PRINT_RULE
print_$(1):
	@echo $($(1)) > $(OUT)
endef

$(foreach i,$(INFOS),$(eval $(call PRINT_RULE,$(i))))
