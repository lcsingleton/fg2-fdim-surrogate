# STM32F412RET6
add_definitions(-DSTM32F4)
set(STM32F4_FLAGS "-Os -g -mcpu=cortex-m3 -mthumb -msoft-float -MD -specs=nano.specs -u _printf_float -specs=nosys.specs")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${STM32F4_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STM32F4_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --static -nostartfiles -MD T '${CMAKE_SOURCE_DIR}/lib/stm32f412ret6.ld'")

# Used in top CMakeLists.txt
set(LIBOPENCM3_STM32F4_LIBRARIES opencm3_stm32f4)
# Used in libopencm3.cmake
set(LIBOPENCM3_TARGETS "lib/stm32/f4")
