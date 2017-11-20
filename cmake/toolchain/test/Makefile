AVERSIVEPLUSPLUS_ROOT ?= $(PWD)/../../AversivePlusPlus
CONAN ?= $(AVERSIVEPLUSPLUS_ROOT)/tools/bin/conan

EXE=_test

TARGET ?= native
SETTINGS ?=

all: arduino-mega2560 arduino-uno atmega2560 atmega328p
all: stm32f407vg stm32f4discovery stm32f3discovery stm32f0discovery
all: samr21-xpro saml21-xpro

arduino-mega2560 arduino-uno atmega2560 atmega328p:
	make TARGET=$@ SETTINGS="-s compiler=avr-gcc -s compiler.version=4.8" compile

stm32f407vg stm32f4discovery stm32f3discovery stm32f0discovery:
	make TARGET=$@ SETTINGS="-s compiler=arm-none-eabi-gcc -s compiler.version=5.4" compile

samr21-xpro saml21-xpro:
	make TARGET=$@ SETTINGS="-s compiler=arm-none-eabi-gcc -s compiler.version=5.4" compile

compile: build build/$(TARGET) build/$(TARGET)/bin/$(EXE)
	@touch build/$(TARGET)/bin/$(EXE)

clean:
	@rm -rf build

mrproper: clean
	@rm -f *~
	@rm -f *.pyc

build/$(TARGET)/bin/$(EXE): main.cpp build/$(TARGET)/conanbuildinfo.cmake
	@cd build/$(TARGET) && $(CONAN) build ../..

build/$(TARGET)/conanbuildinfo.cmake: conanfile.py
	@cd build/$(TARGET) && $(CONAN) install ../.. --build $(SETTINGS) -s target=$(TARGET)

build:
	@mkdir build

build/$(TARGET):
	@mkdir $@

