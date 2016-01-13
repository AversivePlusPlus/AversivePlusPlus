.PHONY: all

include targets.mk
all: interface

interface:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../..
	@cd build/$@ && make -s

stm32%:
	@mkdir build/$@ -p
	@cd build/$@ && cmake ../.. -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/stm32/$@.cmake
	@cd build/$@ && make -s
