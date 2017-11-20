PACKAGE_NAME = cmake-toolchain

AVERSIVE_ROOT ?= ../AversivePlusPlus
CONAN ?= $(AVERSIVE_ROOT)/tools/bin/conan

################################
.PHONY: all export clean mrproper test

################################
all: build
	@cd build && ../$(CONAN) install .. -s target=arduino-mega2560
	@cd build && ../$(CONAN) build ..

################################
clean:
	@rm -rf build
	@cd test && make clean

mrproper: clean
	@rm -f *~
	@rm -f *.pyc

################################

export: build/exported
	@touch build/exported

build/exported: build
	@$(CONAN) export AversivePlusPlus/dev

################################

test:
	@cd test && make

################################
build:
	@mkdir $@
