CONAN=../../tools/bin/conan
BIN=template-project

BOARD="arduino-mega2560"
#BOARD="arduino-uno"

all:
	@mkdir -p build && cd build && ../$(CONAN) install -s compiler=avr-gcc -s compiler.version=4.9 -s target=$(BOARD) .. --build
	@cd build && ../$(CONAN) build ..
