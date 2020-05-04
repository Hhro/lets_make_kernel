set(KERNEL_FOLDERS
    terminal
    keyboard
)

set(KERNEL_SRCS)

foreach(FOLDER ${KERNEL_FOLDERS})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/CMakeLists.txt)
        add_subdirectory(${FOLDER})
    endif()
    if(NOT ${FOLDER} EQUAL "include")
        file(GLOB TMP
            "${FOLDER}/*.c"
            "${FOLDER}/*.cpp"
            "${FOLDER}*.S")
        list(APPEND KERNEL_SRCS "${TMP}")
    endif()
endforeach()
message("${KERNEL_SRCS}")

add_library(kernel OBJECT "${CMAKE_CURRENT_SOURCE_DIR}/kernel.cpp" ${KERNEL_SRCS})