# Enter CMake cross-compilation mode
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# User settings with sensible defaults
set(ARDUINO_PATH "C:\\Program Files (x86)\\Arduino" CACHE PATH
    "Path of the Arduino packages folder, e.g. ~/.arduino15/packages/arduino.")
set(ARDUINO_CORE_VERSION "1.8.6" CACHE STRING
    "Version of arduino/ArduinoCore-AVR")
set(AVR_GCC_VERSION "7.3.0-atmel3.6.1-arduino7" CACHE STRING
    "Full version string of the GCC release shipped with the Arduino core.")
set(AVRDUDE_VERSION "6.3.0-arduino17" CACHE STRING
    "Full version string of the avrdude release shipped with the Arduino core.")
set(ARDUINO_VERSION "10815" CACHE STRING
    "Arduino IDE version (used for the macro with the same name)")

# Derived paths
set(ARDUINO_AVR_PATH ${ARDUINO_PATH}/hardware/arduino/avr)
set(ARDUINO_CORE_PATH ${ARDUINO_AVR_PATH}/cores/arduino)
set(ARDUINO_TOOLS_PATH ${ARDUINO_PATH}/hardware/tools/avr/bin)
set(ARDUINO_AVRDUDE_PATH ${ARDUINO_PATH}/hardware/tools/avr)
set(ARDUINO_AVRDUDE_CONF ${ARDUINO_AVRDUDE_PATH}/etc/avrdude.conf)

# Toolchain paths
set(CMAKE_C_COMPILER ${ARDUINO_TOOLS_PATH}/bin/avr-gcc.exe CACHE FILEPATH
    "Path to avr-gcc" FORCE)
set(CMAKE_CXX_COMPILER ${ARDUINO_TOOLS_PATH}/bin/avr-g++.exe CACHE FILEPATH
    "Path to avr-g++" FORCE)
set(CMAKE_OBJCOPY ${ARDUINO_TOOLS_PATH}/bin/avr-objcopy.exe CACHE FILEPATH
    "Path to avr-objcopy" FORCE)
set(CMAKE_SIZE ${ARDUINO_TOOLS_PATH}/bin/avr-size.exe CACHE FILEPATH
    "Path to avr-size" FORCE)
set(ARDUINO_AVRDUDE ${ARDUINO_AVRDUDE_PATH}/bin/avrdude.exe CACHE FILEPATH
    "Path to avrdude" FORCE)

# Only look libraries etc. in the sysroot, but never look there for programs
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
