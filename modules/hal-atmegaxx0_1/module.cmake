# The module name
# Must be unique for an entire Aversive++ distribution
set(NAME hal-atmegaxx0_1)

# Modules that the current module depends on
set(DEPENDENCIES hal hdl-atmegaxx0_1)

# Startup files
set(STARTUP)

# Determines if the modules will be compiled
# and included in Aversive++ for the current MCU
# you may check some environnement variables
# like ${AVERSIVE_PLATFORM} or ${AVERSIVE_MCU}
# to determine if COMPILE_LIB should be equal to 0 or 1
set(COMPILE_LIB 0)
if(AVERSIVE_TOOLCHAIN_ATMEGAXX0_1)
  set(COMPILE_LIB 1)
endif()

if(AVERSIVE_TOOLCHAIN_ATMEGA2560)
  add_subdirectory(test)
endif()
