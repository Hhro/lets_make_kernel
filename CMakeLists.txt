cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.10)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(lets_make_kernel
    DESCRIPTION "Lets make kernel!"
    LANGUAGES   CXX
    VERSION     0.1.1
)

enable_testing()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(NOT ARCH)
    set(ARCH "x86")
endif()

if(TOOLCHAIN_PATH)
    set(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_PATH})
endif()

set(TRIPLE x86_64-elf)
set(CMAKE_C_COMPILER_TARGET ${TRIPLE})
set(CMAKE_CXX_COMPILER_TARGET ${TRIPLE})
set(CMAKE_ASM_COMPILER_TARGET ${TRIPLE})

enable_language(ASM)

include_directories(include)
include(arch/${ARCH}/defconfig.cmake)

add_subdirectory("arch/${ARCH}")
add_subdirectory(kernel)
add_subdirectory(lib)

add_dependencies(kernel arch)
add_dependencies(lib kernel)

add_executable(fried.bin $<TARGET_OBJECTS:arch> $<TARGET_OBJECTS:kernel> $<TARGET_OBJECTS:lib>)

add_custom_command(OUTPUT fried.iso
    COMMAND mkdir -p ./isodir/boot/grub
    COMMAND cp fried.bin ./isodir/boot/fried.bin
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg" isodir/boot/grub/grub.cfg
    COMMAND grub-mkrescue -o fried.iso isodir
    DEPENDS fried.bin grub.cfg
)

file(GLOB_RECURSE test_SRC
    "test/*.test.cpp"
)

add_custom_target(run-iso
    COMMAND qemu-system-x86_64 -cpu Broadwell -cdrom ./fried.iso -curses 
    DEPENDS fried.iso
)

add_custom_target(debug-iso
    COMMAND qemu-system-x86_64 -cpu Broadwell -cdrom ./fried.iso -curses -s -S 
    DEPENDS fried.iso
)

add_custom_target(iso ALL 
    DEPENDS fried.iso
)

set_target_properties(arch_test PROPERTIES COMPILE_DEFINITIONS "TEST")
set_target_properties(kernel_test PROPERTIES COMPILE_DEFINITIONS "TEST")
set_target_properties(lib_test PROPERTIES COMPILE_DEFINITIONS "TEST")

foreach(test ${test_SRC})
    get_filename_component(test_name ${test} NAME_WE)
    message(${test}, ${test_name})
    add_executable("${test_name}.test" EXCLUDE_FROM_ALL $<TARGET_OBJECTS:arch_test> $<TARGET_OBJECTS:kernel_test> $<TARGET_OBJECTS:lib_test> ${test})
    set_target_properties("${test_name}.test" PROPERTIES COMPILE_DEFINITIONS "TEST")
    add_custom_command(OUTPUT "${test_name}.test.iso"
        COMMAND mkdir -p ./isodir/boot/grub
        COMMAND cp "${test_name}.test" "./isodir/boot/fried.bin"
        COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/test/grub.cfg" isodir/boot/grub/grub.cfg
        COMMAND grub-mkrescue -o "${test_name}.test.iso" isodir
        DEPENDS "${test_name}.test" grub.cfg 
    )
    list(APPEND test_iso_files "${test_name}.test.iso")
    
    add_test(NAME "${test_name}"
        COMMAND "./test.sh" "${test_name}.test.iso" )
    set_tests_properties("${test_name}" PROPERTIES FIXTURES_REQUIRED test_fixture)
    
endforeach()

add_custom_command(OUTPUT "test.sh"
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/test/test.sh" "${CMAKE_BINARY_DIR}"
    COMMAND chmod +x "${CMAKE_BINARY_DIR}/test.sh"
    DEPENDS "./test/test.sh"
    )

add_custom_target(test_iso DEPENDS ${test_iso_files} "test.sh")
add_test(NAME "build_test_iso"
        COMMAND
         "${CMAKE_COMMAND}"
         --build "${CMAKE_BINARY_DIR}"
         --config "$<CONFIG>"
         --target test_iso
       )
set_tests_properties("build_test_iso" PROPERTIES FIXTURES_SETUP test_fixture)