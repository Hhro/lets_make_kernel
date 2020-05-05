set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/boot/linker.ld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -fno-exceptions -fno-rtti -fPIC -fPIE -no-pie")

if(CMAKE_BUILD_TYPE EQUAL "RELEASE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
elseif(CMAKE_BUILD_TYPE EQUAL "DEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

set(LINKER_FLAGS "-z max-page-size=0x1000 -nostdlib -lgcc -T ${LINKER_SCRIPT}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_CXX_FLAGS} -x assembler-with-cpp -Wa,-I -Wa,include")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)