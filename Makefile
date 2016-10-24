.PHONY: all update doc

export PATH:=$(PWD)/tools/bin:$(PATH)
export CONAN ?= $(PWD)/tools/bin/conan

MODULES = base container device device-2wheel device-control filter sasiae stream #feetech 
THIRDPARTY = arduino cmsis-core cmsis-stm32f4xx stm32cube-hal-stm32f4xx
TOOLCHAINS = avr generic simul stm32 switch

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
export:
	@conan export AversivePlusPlus/dev

define CONAN_EXPORT_RULE
export: export_$(1)

export_$(1):
	@cd $(2)/$(1) && $(CONAN) export AversivePlusPlus/dev
endef

$(eval $(call CONAN_EXPORT_RULE,feetech,modules))
$(foreach m,$(MODULES),$(eval $(call MAKE_RULE,$(m),modules,export)))
$(foreach m,$(THIRDPARTY),$(eval $(call CONAN_EXPORT_RULE,$(m),modules/thirdparty)))
$(foreach m,$(TOOLCHAINS),$(eval $(call CONAN_EXPORT_RULE,$(m),toolchains)))

################################
clean:
	@rm -rf build

$(foreach m,$(MODULES),$(eval $(call MAKE_RULE,$(m),modules,clean)))

mrproper:
	@rm -f *~
	@rm -f *.pyc

$(foreach m,$(MODULES),$(eval $(call MAKE_RULE,$(m),modules,mrproper)))

################################
test:
	@rm -rf build

test: test_template-project

test_template-project:
	@cd examples/template-project && $(MAKE) -s

$(foreach m,$(MODULES),$(eval $(call MAKE_RULE,$(m),modules,test)))

################################
update:
	git submodule update --init

################################
doc:
	@mkdir build -p
	@doxygen
