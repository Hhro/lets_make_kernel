set(ARCH_LIBS
    boot
)

foreach(LIBS ${ARCH_LIBS})
    add_subdirectory(${LIBS})
    target_include_directories(${LIBS}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endforeach()

