cmake_minimum_required(VERSION 3.16.0)

project(
	icc_surrogate
	LANGUAGES C ASM
)

add_compile_options(
	-mthumb
	-mcpu=cortex-m3
	-fdata-sections
	-ffunction-sections
	-Wall
	-Wextra
	--specs=nano.specs
	--specs=nosys.specs
)

add_link_options(
	-mthumb
	-mcpu=cortex-m3
	-nostartfiles
	-Wl,--gc-sections
	--specs=nano.specs
	--specs=nosys.specs
)

set(MCU_VARIANT stm32f412re)
set(OPENCM3_LIB opencm3_stm32f4)
set(LIBOPENCM3_CMAKE_DIR lib/libopencm3_cmake)

add_subdirectory(${LIBOPENCM3_CMAKE_DIR} ${OPENCM3_LIB})

set(
	APP_SRCS
	${CMAKE_CURRENT_LIST_DIR}/src/main.c
)

set(
	APP_INCS
	${CMAKE_CURRENT_LIST_DIR}/src
)

add_executable(icc_surrogate ${APP_SRCS})
target_include_directories(icc_surrogate PRIVATE ${APP_INCS})
target_link_libraries(icc_surrogate PRIVATE ${OPENCM3_LIB})
target_link_options(
	icc_surrogate
	PRIVATE
	-T ${CMAKE_BINARY_DIR}/generated.${MCU_VARIANT}.ld
	-Wl,-Map=icc_surrogate.map
	-Wl,--print-memory
)
add_custom_command(
	TARGET icc_surrogate
	POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O srec icc_surrogate.elf icc_surrogate.srec
	BYPRODUCTS icc_surrogate.srec
)

