AVERSIVEPLUSPLUS_ROOT ?= ../../../..
CONAN ?= $(AVERSIVEPLUSPLUS_ROOT)/tools/bin/conan

EXE=_test

all: build build/bin/$(EXE)
	@touch build/bin/$(EXE)

test: build build/bin/$(EXE)
	@./build/bin/$(EXE)

clean:
	@rm -rf build

mrproper: clean
	@rm -f *~
	@rm -f *.pyc

build/bin/$(EXE): main.cpp build/conanbuildinfo.cmake
	@cd build && $(CONAN) build ..

build/conanbuildinfo.cmake: conanfile.py
	@cd build && $(CONAN) install .. --build

build:
	@mkdir build

