cmake_minimum_required(VERSION 3.19)
project(FG2SurrogateFDM LANGUAGES C CXX ASM)

include(cmake/toolchain/mega.toolchain.cmake)
include(cmake/lto.cmake)
include(cmake/arduino_core.cmake)
include(cmake/arduino_hex.cmake)
include(cmake/arduino_upload.cmake)

add_executable(fdm src/main.cpp)
target_link_libraries(fdm PUBLIC ArduinoCore)
target_compile_options(fdm PRIVATE
    "-Wall"
    "-Wextra"
    "-pedantic"
)
arduino_avr_hex(fdm)

set(ARDUINO_PORT "/dev/ttyACM0"
    CACHE STRING "The serial port for uploading using avrdude")
arduino_avr_upload(fdm ${ARDUINO_PORT})
