set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/boot/linker.cmake.ld)

# https://github.com/cliffordwolf/picorv32/issues/124
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -fomit-frame-pointer -fno-exceptions -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-exceptions -fno-rtti -fPIC -fno-pie -no-pie -mcmodel=kernel -mno-red-zone")

if(CMAKE_BUILD_TYPE EQUAL "RELEASE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
elseif(CMAKE_BUILD_TYPE EQUAL "DEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif()

set(LINKER_FLAGS "-z max-page-size=0x1000 -nostdlib -lgcc -T ${LINKER_SCRIPT} -mcmodel=kernel")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_CXX_FLAGS} -x assembler-with-cpp -Wa,-I -Wa,include -mcmodel=kernel")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)