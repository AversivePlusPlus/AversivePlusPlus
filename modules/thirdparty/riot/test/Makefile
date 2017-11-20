CONAN ?= $(PWD)/../../AversivePlusPlus/tools/bin/conan
BIN=riot-test

SETTINGS_AVR_CC=-s compiler=avr-gcc -s compiler.version=4.9
SETTINGS_NATIVE_CC=
SETTINGS_ARM_CC=-s compiler=arm-none-eabi-gcc -s compiler.version=5.4

SETTINGS_ADM2560=$(SETTINGS_AVR_CC) -s target=arduino-mega2560
SETTINGS_NATIVE=$(SETTINGS_NATIVE_CC) -s target=native32
SETTINGS_SAMR21=$(SETTINGS_ARM_CC) -s target=samr21-xpro

.PHONY: all adm2560 native samr21 compile clean

all:
	@echo "make {native,adm2560,samr21,clean}"

adm2560: export SETTINGS=$(SETTINGS_ADM2560)
adm2560: compile

native: export SETTINGS=$(SETTINGS_NATIVE)
native: compile

samr21: export SETTINGS=$(SETTINGS_SAMR21)
samr21: compile

compile: build build/install
	@cd build && $(CONAN) build ..

build/install:
	@cd build && $(CONAN) install $(SETTINGS) .. --build
	@touch build/install

build:
	@mkdir build

clean:
	@rm -rf build
