PACKAGE_NAME = base

CONAN ?= ../../tools/bin/conan

################################
.PHONY: arduino_package test all export

################################
all:
	@echo "Usage: make {export,arduino_package,test,clean,mrpoper}"

################################
clean:
	@rm -rf build
	@cd test/test     && $(MAKE) -s clean
	@cd test/integer  && $(MAKE) -s clean
	@cd test/array    && $(MAKE) -s clean
	@cd test/pair     && $(MAKE) -s clean
	@cd test/bool_ref && $(MAKE) -s clean

mrproper: clean
	@rm -f *~
	@rm -f *.pyc
	@cd test/test     && $(MAKE) -s mrproper
	@cd test/integer  && $(MAKE) -s mrproper
	@cd test/array    && $(MAKE) -s mrproper
	@cd test/pair     && $(MAKE) -s mrproper
	@cd test/bool_ref && $(MAKE) -s mrproper

################################
SOURCES = $(wildcard include/$(PACKAGE_NAME)/*.hpp)

export: build/exported
	@touch build/exported

build/exported: build $(SOURCES)
	@$(CONAN) export AversivePlusPlus/dev

################################
arduino_package: build/${PACKAGE_NAME}.zip

build/${PACKAGE_NAME}.zip: build/arduino/${PACKAGE_NAME}.h
	@cd build/arduino && zip ${PACKAGE_NAME}.zip . -r && mv ${PACKAGE_NAME}.zip ..

build/arduino/${PACKAGE_NAME}.h: build/arduino
	@cp -r include/* $<
	@cp pro/arduino/aversive_${PACKAGE_NAME}.h $<

build/arduino: build
	@mkdir $@

################################
build:
	@mkdir $@

################################
test: export
	@cd test/test     && $(MAKE) -s test
	@cd test/integer  && $(MAKE) -s test
	@cd test/array    && $(MAKE) -s test
	@cd test/pair     && $(MAKE) -s test
	@cd test/bool_ref && $(MAKE) -s test
