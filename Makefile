.PHONY: all

include targets.mk

all: interface
interface:
install: install_interface
install_interface:

interface:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../..
	@cd build/$@ && make -s

stm32%:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/stm32/$@.cmake
	@cd build/$@ && make -s

atmega%:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/avr/$@.cmake
	@cd build/$@ && make -s

atxmega%:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/avr/$@.cmake
	@cd build/$@ && make -s

install_%:
	@cd build/$(subst install_,,$@) && make install
