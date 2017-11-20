cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0011 NEW)

set(AVERSIVE_TOOLCHAIN_STM32F4 1 CACHE STRING "")
set(AVERSIVE_TOOLCHAIN_CORTEXM4 1 CACHE STRING "")

include("${CMAKE_CURRENT_LIST_DIR}/stm32.cmake")

set(STM32F4_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -Wdouble-promotion -ffunction-sections -fdata-sections -DSTM32F40_41xxx -DDEBUG -DUSART_DEBUG=USART1 -DHSE_VALUE=8000000")
set(STM32F4_FLAGS "${STM32F4_FLAGS} -DAVERSIVE_TOOLCHAIN_STM32F4")
set(STM32F4_FLAGS "${STM32F4_FLAGS} -DAVERSIVE_TOOLCHAIN_CORTEXM4")

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${STM32F4_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STM32F4_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${STM32F4_FLAGS}")

unset(STM32F4_FLAGS)
