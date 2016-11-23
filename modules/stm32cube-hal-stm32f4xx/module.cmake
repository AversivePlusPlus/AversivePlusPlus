# The module name
# Must be unique for an entire Aversive++ distribution
set(NAME stm32cube-hal-stm32f4xx)

# Modules that the current module depends on
set(DEPENDENCIES cmsis-stm32f4xx)

# Startup files
set(STARTUP
  startup/system_stm32f4xx.c
  )

# Determines if the modules will be compiled
# and included in Aversive++ for the current MCU
# you may check some environnement variables
# like ${AVERSIVE_PLATFORM} or ${AVERSIVE_MCU}
# to determine if COMPILE_LIB should be equal to 0 or 1
set(COMPILE_LIB 0)
if(AVERSIVE_TOOLCHAIN_STM32)
  set(COMPILE_LIB 1)
endif()
