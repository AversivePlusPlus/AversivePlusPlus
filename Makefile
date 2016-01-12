

all:
	@mkdir build/stm32f407vg -p
	@cd build/stm32f407vg && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/stm32/stm32f407vg.cmake
	@cd build/stm32f407vg && make -s
	@mkdir build/stm32f411ret -p
	@cd build/stm32f411ret && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/stm32/stm32f411ret.cmake
	@cd build/stm32f411ret && make -s
