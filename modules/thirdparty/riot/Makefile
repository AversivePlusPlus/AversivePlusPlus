.PHONY: all test export clean mrproper

export AVERSIVE_ROOT ?= $(PWD)/../AversivePlusPlus
export CONAN ?= $(AVERSIVE_ROOT)/tools/bin/conan

MODULES = riot stream-riot

################################
all:
	@echo "Usage: make {export,test,clean,mrpoper}"

################################
define MAKE_RULE
$(3): $(3)_$(1)

$(3)_$(1):
	@cd $(2)/$(1) && $(MAKE) -s $(3)
endef

################################
$(foreach m,$(MODULES),$(eval $(call MAKE_RULE,$(m),.,export)))

################################
clean:
	@cd test && make -s clean

$(foreach m,$(MODULES),$(eval $(call MAKE_RULE,$(m),.,clean)))

mrproper:
	@rm -f *~
	@rm -f *.pyc

$(foreach m,$(MODULES),$(eval $(call MAKE_RULE,$(m),.,mrproper)))

################################
test:
	@cd test && make -s native

