set(ARCH_FOLDERS
    boot
    # Add folder here
    )

set(ARCH_SRCS)

file(GLOB TMP
"*.c"
"*.cpp"
"*.S")
list(APPEND ARCH_SRCS "${TMP}")

foreach(FOLDER ${ARCH_FOLDERS})
    file(GLOB TMP
    "${FOLDER}/*.c"
    "${FOLDER}/*.cpp"
    "${FOLDER}/*.S")
    list(APPEND ARCH_SRCS "${TMP}")
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/CMakeLists.txt)
        add_subdirectory(${FOLDER})
    endif()
endforeach()

message("${ARCH_SRCS}")
add_library(arch OBJECT "${ARCH_SRCS}")