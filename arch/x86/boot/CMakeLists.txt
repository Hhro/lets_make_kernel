set(boot_SRCS
    boot.S
)

add_library(boot
    OBJECT
    ${boot_SRCS}
)
