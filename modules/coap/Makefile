PACKAGE_NAME = coap--

AVERSIVE_ROOT ?= $(PWD)/../..
CONAN ?= $(AVERSIVE_ROOT)/tools/bin/conan

################################
.PHONY: arduino_package test all export

################################
all: build
	@cd build && $(CONAN) install .. --build
	@cd build && $(CONAN) build ..

################################
TESTS = .

test: export

define TEST_RULE
test: test_$(1)

test_$(1):
	@cd test/$(1) && $(MAKE) -s test
endef

$(foreach t,$(TESTS),$(eval $(call TEST_RULE,$(t))))

################################
clean:
	@rm -rf build

define CLEAN_RULE
clean: clean_$(1)

clean_$(1):
	@cd test/$(1) && $(MAKE) -s clean
endef

$(foreach t,$(TESTS),$(eval $(call CLEAN_RULE,$(t))))

mrproper: clean
	@rm -f *~
	@rm -f *.pyc

define MRPROPER_RULE
mrproper: mrproper_$(1)

mrproper_$(1):
	@cd test/$(1) && $(MAKE) -s mrproper
endef

$(foreach t,$(TESTS),$(eval $(call MRPROPER_RULE,$(t))))

################################
SOURCES = $(find include/ -name "*.hpp")

export: build/exported
	@touch build/exported

build/exported: build $(SOURCES)
	@$(CONAN) export AversivePlusPlus/dev

################################
build:
	@mkdir $@

