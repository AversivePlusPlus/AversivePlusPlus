AVERSIVEPLUSPLUS_ROOT ?= $(PWD)/../..
CONAN ?= $(AVERSIVEPLUSPLUS_ROOT)/tools/bin/conan

all: build
	@cd build && $(CONAN) install .. --build=missing
	@cd build && $(CONAN) build ..

build:
	@mkdir -p build
