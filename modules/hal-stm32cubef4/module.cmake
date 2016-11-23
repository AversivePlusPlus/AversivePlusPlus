# The module name
# Must be unique for an entire Aversive++ distribution
set(NAME hal-stm32cubef4)

# Modules that the current module depends on
set(DEPENDENCIES hal stm32cube-hal-stm32f4xx)

# Startup files
set(STARTUP)

# Determines if the modules will be compiled
# and included in Aversive++ for the current MCU
# you may check some environnement variables
# like ${AVERSIVE_PLATFORM} or ${AVERSIVE_MCU}
# to determine if COMPILE_LIB should be equal to 0 or 1
set(COMPILE_LIB 0)
if(AVERSIVE_TOOLCHAIN_STM32F4)
  set(COMPILE_LIB 1)
endif()

# Test
if(AVERSIVE_TOOLCHAIN_STM32F407)
  add_subdirectory(test)
endif()

# Custom rules

## generated
add_custom_command(
  OUTPUT include/hal/stm32cubef4/traits_generated.hpp
  COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/script/traits_generated.py > ${CMAKE_CURRENT_SOURCE_DIR}/include/hal/stm32cubef4/traits_generated.hpp
  MAIN_DEPENDENCY script/traits_generated.py
)

## stm32f407xx
add_custom_command(
  OUTPUT include/hal/stm32cubef4/traits_stm32f407xx.hpp
  COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/script/traits_stm32f407xx.py > ${CMAKE_CURRENT_SOURCE_DIR}/include/hal/stm32cubef4/traits_stm32f407xx.hpp
  MAIN_DEPENDENCY script/traits_stm32f407xx.py
)

add_custom_command(
  OUTPUT src/timer_TIM1_BRK_TIM9_IRQHandler.cpp
  COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/script/interrupts.py ; mv *_IRQHandler.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/
  MAIN_DEPENDENCY script/interrupts.py
)

## Target
add_custom_target(
  hal-stm32cubef4-generated
  #ALL
  DEPENDS
  include/hal/stm32cubef4/traits_generated.hpp
  include/hal/stm32cubef4/traits_stm32f407xx.hpp
  src/timer_TIM1_BRK_TIM9_IRQHandler.cpp
)
