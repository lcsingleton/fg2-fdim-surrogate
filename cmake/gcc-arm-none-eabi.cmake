set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# This file assumes that path to the GCC toolchain is added
# to the environment(PATH) variable, so that CMake can find

find_program(CMAKE_C_COMPILER arm-none-eabi-gcc)

macro(__flag_init lang)
	set(CMAKE_EXECUTABLE_SUFFIX_${lang} ".elf")
	set(CMAKE_${lang}_FLAGS_DEBUG "-Og -g -ggdb3")
	set(CMAKE_${lang}_FLAGS_MINSIZEREL "-Os -DNDEBUG")
	set(CMAKE_${lang}_FLAGS_RELEASE "-O3 -DNDEBUG")
	set(CMAKE_${lang}_FLAGS_RELWITHDEBINFO "-O2 -g -ggdb3 -DNDEBUG")
endmacro()

__flag_init(C)
__flag_init(ASM)

