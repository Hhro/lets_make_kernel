set(LIB_FOLDERS
    # Add folder here
    )

set(LIB_SRCS)

file(GLOB TMP
"*.c"
"*.cpp"
"*.S")
list(APPEND LIB_SRCS "${TMP}")

foreach(FOLDER ${LIB_FOLDERS})
    file(GLOB TMP
    "${FOLDER}/*.c"
    "${FOLDER}/*.cpp"
    "${FOLDER}/*.S")
    list(APPEND LIB_SRCS "${TMP}")
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/CMakeLists.txt)
        add_subdirectory(${FOLDER})
    endif()
endforeach()

message("${LIB_SRCS}")
add_library(lib OBJECT "${LIB_SRCS}")
add_library(lib_test OBJECT EXCLUDE_FROM_ALL "${LIB_SRCS}")