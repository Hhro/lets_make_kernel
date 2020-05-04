set(ARCH_FOLDERS
    asm
    boot
    descriptors
    )

set(ARCH_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/boot/boot.S")

foreach(FOLDER ${ARCH_FOLDERS})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/CMakeLists.txt)
        add_subdirectory(${FOLDER})
    endif()
    if(NOT ${FOLDER} EQUAL "include")
        file(GLOB TMP
        "${FOLDER}/*.c"
        "${FOLDER}/*.cpp"
        "${FOLDER}/*.S")
        list(APPEND ARCH_SRCS "${TMP}")
    endif()
endforeach()

message("${ARCH_SRCS}")
add_library(arch OBJECT "${ARCH_SRCS}")