cmake_minimum_required(VERSION 3.16.0)
#set(CMAKE_CROSS_COMPILING 1)
#set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS TRUE)
SET(CMAKE_CXX_COMPILER_WORKS TRUE)


# Build the LibOpenCM3 STM32F4 Library
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3/lib/libopencm3_stm32f4.a
    COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3 lib/stm32/f4
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3
    COMMENT "Building libopencm3.a"
)

# Create a custom target for the library
add_custom_target(
    libopencm3stm32f4
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3/lib/libopencm3_stm32f4.a
)

# Create an imported library target for the library
add_library( libopencm3 STATIC IMPORTED )

# Set the location of the imported library
set_target_properties(libopencm3 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3/lib/libopencm3_stm32f4.a)

# Define the main project
project(
	icc_surrogate
	LANGUAGES CXX C
)


# Store a list of source files to compile
set(
	APP_SRCS
		src/Acm/KeepAlive.cpp

		src/Core/Can.cpp
		src/Core/Serial.cpp
		src/Core/Timer.cpp

		src/Icc/KeepAlive.cpp

		src/Keypad/CabinTempSensor.cpp
		src/Keypad/HvacControlState.cpp
		src/Keypad/KeypadState.cpp
		src/Keypad/MediaControlState.cpp
		src/Keypad/RotaryDial.cpp

		src/SZRaize/GM/Universal.cpp

		src/Main.cpp

)

include_directories(
	# Make the LibOpenCM3 Headers Available
	${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3/include
	# Make sure the head files from the src directory are available
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set the output as an executable, of the source files
add_executable(
	icc_surrogate
	${APP_SRCS}
)

# Define STM32F4 for the build
target_compile_definitions(icc_surrogate PRIVATE STM32F4)

# Set the dependencies for the target
add_dependencies(icc_surrogate libopencm3stm32f4)

# Link the library to the target
target_link_libraries(icc_surrogate PRIVATE libopencm3)
