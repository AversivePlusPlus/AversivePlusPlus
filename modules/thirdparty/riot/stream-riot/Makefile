PACKAGE_NAME = stream-riot

AVERSIVE_ROOT ?= $(PWD)/../..
CONAN ?= $(AVERSIVE_ROOT)/tools/bin/conan

################################
.PHONY: all export

################################
all:
	@echo "Usage: make {export,clean,mrpoper}"

################################
clean:
	@rm -rf build

mrproper: clean
	@rm -f *~
	@rm -f *.pyc

################################

export: build/exported
	@touch build/exported

build/exported: build conanfile.py
	@$(CONAN) export AversivePlusPlus/dev

################################
build:
	@mkdir $@
