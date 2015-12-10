

all:
	@mkdir build -p
	@cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/stm32/stm32f407vg.cmake
	@cd build && make -s
