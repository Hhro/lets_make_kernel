cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.10)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(lets_make_kernel
    DESCRIPTION "Lets make kernel!"
    LANGUAGES   CXX
    VERSION     0.1.0
)

if(NOT ARCH)
    set(ARCH "x86")
endif()

if(TOOLCHAIN_PATH)
    set(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_PATH})
endif()

set(TRIPLE x86_64-elf)
set(CMAKE_C_COMPILER_TARGET ${TRIPLE})
set(CMAKE_CXX_COMPILER_TARGET ${TRIPLE})

enable_language(ASM)

include_directories(include)
include(arch/${ARCH}/defconfig.cmake)

add_subdirectory("arch/${ARCH}")
add_subdirectory(kernel)

add_executable(fried.bin kernel/kernel.cpp $<TARGET_OBJECTS:boot>)

add_custom_command(OUTPUT fried.iso
    COMMAND mkdir -p ./isodir/boot/grub
    COMMAND cp fried.bin ./isodir/boot/fried.bin
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg" isodir/boot/grub/grub.cfg
    COMMAND grub-mkrescue -o fried.iso isodir
    DEPENDS fried.bin grub.cfg
)

add_custom_target(iso ALL 
    DEPENDS fried.iso
)
