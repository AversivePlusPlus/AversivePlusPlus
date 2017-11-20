AVERSIVEPLUSPLUS_ROOT ?= $(PWD)/../../../..
CONAN ?= $(AVERSIVEPLUSPLUS_ROOT)/tools/bin/conan

EXE=_test

SETTINGS=-s target=teensy3 -s compiler=arm-none-eabi-gcc -s compiler.version=5.4

all: build build/bin/$(EXE)
	@touch build/bin/$(EXE)

test: build build/bin/$(EXE)
#	build/bin/$(EXE)

clean:
	@rm -rf build

mrproper: clean
	@rm -f *~
	@rm -f *.pyc

build/bin/$(EXE): main.cpp build/conanbuildinfo.cmake
	@cd build && $(CONAN) build ..

build/conanbuildinfo.cmake: conanfile.py
	@cd build && $(CONAN) install .. --build $(SETTINGS)

build:
	@mkdir build

