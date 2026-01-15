cmake_minimum_required(VERSION 3.16.0)

# Configure for ARM cross-compilation
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Specify the cross compiler
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

# Skip compiler tests since we're cross-compiling
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Define the main project
project(
	icc_surrogate
	LANGUAGES CXX C
)

# Require C++17 for fold expressions and other modern C++ features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ARM Cortex-M4 specific flags for STM32F412
set(DEVICE "stm32f412ret6")
set(OPENCM3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3")
set(LDSCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3/lib/stm32/f4/stm32f412ret6.ld")

set(ARCH_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARCH_FLAGS} -fno-common -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARCH_FLAGS} -fno-common -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ARCH_FLAGS} -L${OPENCM3_DIR}/lib -T${LDSCRIPT} --specs=nosys.specs --specs=nano.specs -Wl,--gc-sections,--no-wchar-size-warning,-Map=output.map,-z,noexecstack")


# Build the LibOpenCM3 STM32F4 Library
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3/lib/libopencm3_stm32f4.a ${LDSCRIPT}
    COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3 lib/stm32/f4
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3
    COMMENT "Building libopencm3.a and generating linker script"
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


# Link the library to the target
target_link_libraries(icc_surrogate PRIVATE libopencm3)
