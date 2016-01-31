.PHONY: all

include targets.mk

all: interface
interface:
install: install_interface
install_interface:

all: sasiae
sasiae:
install: install_sasiae
install_sasiae:

interface:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../..
	@cd build/$@ && make -s

stm32%:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=toolchain/stm32/$@.cmake
	@cd build/$@ && make -s

atmega%:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=toolchain/avr/$@.cmake
	@cd build/$@ && make -s

atxmega%:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=toolchain/avr/$@.cmake
	@cd build/$@ && make -s

sasiae:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=toolchain/simul/$@.cmake
	@cd build/$@ && make -s

install_%:
	@if [ -d "build/$(subst install_,,$@)" ]; then cd build/$(subst install_,,$@) && make -s install; fi
	@if [ ! -d "build/$(subst install_,,$@)" ]; then echo "ERROR ($@) : Target not built"; fi

update:
	./script/update.sh
