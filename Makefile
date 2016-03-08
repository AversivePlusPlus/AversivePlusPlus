.PHONY: all

include targets.mk

build/%:
	@mkdir $@ -p

interface: build/interface
	@cd build/$@ && cmake ../..
	@cd build/$@ && make -s

stm32%: build/stm32%
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=toolchain/stm32/$@.cmake
	@cd build/$@ && make -s

atmega%: build/atmega%
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=toolchain/avr/$@.cmake
	@cd build/$@ && make -s

atxmega%: build/atxmega%
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=toolchain/avr/$@.cmake
	@cd build/$@ && make -s

sasiae: build/sasiae
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=toolchain/simul/$@.cmake
	@cd build/$@ && make -s

install_%: %
	@cd build/$(subst install_,,$@) && make -s install

package_%: %
	@cd build/$(subst package_,,$@) && make -s package

update:
	./script/update.sh

doc:
	@mkdir build -p
	doxygen
