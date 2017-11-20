.PHONY: all clean mrproper install

QMAKE ?= qmake-qt5

all: build/tinySASIAE

build/tinySASIAE: build/Makefile
	@cd build && $(MAKE) all

clean:
	@rm -rf build

mrproper: clean
	@git clean -Xdf

install: build/tinySASIAE
	@cd build && $(MAKE) install

build/Makefile: build
	@cd build && $(QMAKE) ../tinySASIAE.pro

build:
	@mkdir build

