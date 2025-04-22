cmake_minimum_required(VERSION 3.16.0)

project(
	icc_surrogate
	LANGUAGES CXX C ASM
)

include(cmake/libopencm3.cmake)
#include(cmake/kvasir.cmake)

set(
	APP_SRCS
		src/Main.cpp
		src/Main.h

		src/Core/BitFieldMember.h
		src/Core/Can.h
		src/Core/Registers.h
		src/Core/Timer.cpp
		src/Core/Timer.h

		src/Icc/KeepAlive.h

		src/Keypad/Buttons.h
		src/Keypad/HvacStatus.h
		src/Keypad/KeypadStatus.h
		src/Keypad/KeypadStatus.cpp
		src/Keypad/Pins.h

		src/SZRaize/GM/Universal.cpp
		src/SZRaize/GM/Universal.h
)

add_executable(
		icc_surrogate
		${APP_SRCS}
)

target_include_directories(
		icc_surrogate
		PRIVATE lib/Kvasir/Lib
)

add_dependencies(
		icc_surrogate
		libopencm3
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
