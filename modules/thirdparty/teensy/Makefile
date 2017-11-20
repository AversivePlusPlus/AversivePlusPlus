PACKAGE_NAME = riot

AVERSIVE_ROOT ?= $(PWD)/../..
CONAN ?= $(AVERSIVE_ROOT)/tools/bin/conan

SETTINGS = -s target=teensy3 -s compiler=arm-none-eabi-gcc -s compiler.version=5.4

################################
.PHONY: all export

################################
all: compile

################################
compile: build build/conaninfo.txt cores
	@cd build && $(CONAN) build ..

cores:
	@$(CONAN) source

build/conaninfo.txt:
	@cd build && $(CONAN) install $(SETTINGS) .. --build

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
	@cd test && $(MAKE) -s clean

mrproper: clean
	@rm -f *~
	@rm -f *.pyc
	@rm -rf cores

################################

export: build/exported
	@touch build/exported

build/exported: build conanfile.py
	@$(CONAN) export AversivePlusPlus/dev

################################
build:
	@mkdir $@
