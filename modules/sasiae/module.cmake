# The module name
# Must be unique for an entire Aversive++ distribution
set(NAME sasiae)

# Modules that the current module depends on
set(DEPENDENCIES base container device stream)

# Startup files
set(STARTUP)

# Determines if the modules will be compiled
# and included in Aversive++ for the current MCU
# you may check some environnement variables
# like ${AVERSIVE_PLATFORM} or ${AVERSIVE_MCU}
# to determine if COMPILE_LIB should be equal to 0 or 1
set(COMPILE_LIB 0)

if(AVERSIVE_TOOLCHAIN_SASIAE)
  find_package(Qt5 COMPONENTS Core)
  include_directories(${Qt5Core_INCLUDE_DIRS})
  set(COMPILE_LIB 1)
  add_subdirectory(test)
endif()
