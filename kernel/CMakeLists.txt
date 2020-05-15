set(KERNEL_FOLDERS
    IRQ
    # Add folder here
)

set(KERNEL_SRCS)

file(GLOB TMP
    "*.c"
    "*.cpp"
    "*.S")
list(APPEND KERNEL_SRCS "${TMP}")

foreach(FOLDER ${KERNEL_FOLDERS})
    file(GLOB TMP
    "${FOLDER}/*.c"
    "${FOLDER}/*.cpp"
    "${FOLDER}/*.S")
    list(APPEND KERNEL_SRCS "${TMP}")
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/CMakeLists.txt)
        add_subdirectory(${FOLDER})
    endif()
endforeach()
message("${KERNEL_SRCS}")

add_library(kernel OBJECT "${CMAKE_CURRENT_SOURCE_DIR}/kernel.cpp" ${KERNEL_SRCS})