cmake_minimum_required(VERSION 3.16.0)
#set(CMAKE_CROSS_COMPILING 1)
#set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS TRUE)
SET(CMAKE_CXX_COMPILER_WORKS TRUE)

project(
	icc_surrogate
	LANGUAGES CXX C
)

set(
	APP_SRCS
		src/Acm/KeepAlive.cpp
		src/Acm/KeepAlive.h

		src/Core/BitFieldMember.h
		src/Core/Can.cpp
		src/Core/Can.h
		src/Core/Timer.cpp
		src/Core/Timer.h

		src/Icc/KeepAlive.cpp
		src/Icc/KeepAlive.h

		src/Keypad/Buttons.h
		src/Keypad/CabinTempSensor.cpp
		src/Keypad/CabinTempSensor.h
		src/Keypad/HvacControlState.cpp
		src/Keypad/HvacControlState.h
		src/Keypad/KeypadState.cpp
		src/Keypad/KeypadState.h
		src/Keypad/MediaControlState.cpp
		src/Keypad/MediaControlState.h
		src/Keypad/Pins.h
		src/Keypad/RotaryDial.cpp
		src/Keypad/RotaryDial.h

		src/SZRaize/GM/Universal.cpp
		src/SZRaize/GM/Universal.h

		src/Main.cpp
		src/Main.h

)

add_executable(
		icc_surrogate
		${APP_SRCS}
)

set(MCU_VARIANT stm32f412ret6 INTERNAL)

set(OPENCM3_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/libopencm3")

include(${CMAKE_CURRENT_LIST_DIR}/cmake/opencm3_utils.cmake)

if(NOT DEFINED MCU_VARIANT)
    message(FATAL_ERROR "ERROR: MCU_VARIANT not defined")
endif()

opencm3_add_stm32_library(${MCU_VARIANT})



target_compile_definitions(icc_surrogate PUBLIC __ARM_ARCH_7EM__)

target_include_directories(
		icc_surrogate
		PRIVATE lib/Kvasir/Lib
		src
		lib/libopencm3/include
)

add_dependencies(
		icc_surrogate
		opencm3_stm32f4
)
target_link_libraries(
		icc_surrogate
		${LIBOPENCM3_STM32F4_LIBRARIES}
)
#add_bin_from_elf(
#		blink_cpp.bin
#		blink_cpp
#)
#add_stlink_upload_target(blink_cpp.bin)
