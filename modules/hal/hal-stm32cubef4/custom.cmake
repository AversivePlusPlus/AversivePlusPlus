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
