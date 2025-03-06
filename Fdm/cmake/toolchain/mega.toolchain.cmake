set(ARDUINO_BOARD "AVR_MEGA2560")
set(ARDUINO_MCU "atmega2560")
set(ARDUINO_F_CPU "16000000L")
set(ARDUINO_VARIANT "mega")
set(ARDUINO_AVRDUDE_PROTOCOL "wiring")
set(ARDUINO_AVRDUDE_SPEED "115200")
set(ARDUINO_USB Off)

include(${CMAKE_CURRENT_LIST_DIR}/avr.toolchain.cmake)