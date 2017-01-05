PACKAGE_NAME = device

CONAN ?= ../../tools/bin/conan

################################
.PHONY: arduino_package test all export

################################
all:
	@echo "Usage: make {export,arduino_package,test,clean,mrpoper}"

################################
TESTS = 

test: export

define TEST_RULE
test: test_$(1)

test_$(1):
	@cd test/$(1) && $(MAKE) -s test
endef

$(foreach t,$(TESTS),$(eval $(call TEST_RULE,$(t))))

################################
clean:
	@rm -rf build

define CLEAN_RULE
clean: clean_$(1)

clean_$(1):
	@cd test/$(1) && $(MAKE) -s clean
endef

$(foreach t,$(TESTS),$(eval $(call CLEAN_RULE,$(t))))

mrproper: clean
	@rm -f *~
	@rm -f *.pyc

define MRPROPER_RULE
mrproper: mrproper_$(1)

mrproper_$(1):
	@cd test/$(1) && $(MAKE) -s mrproper
endef

$(foreach t,$(TESTS),$(eval $(call MRPROPER_RULE,$(t))))

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

