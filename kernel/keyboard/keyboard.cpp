#include <stddef.h>
#include <stdint.h>

#include "io.h"
#include "keyboard.h"

bool is_outputbuffer_full(void) {
    if (inport_byte(0x64) & 1)
        return true;
    return false;
}

bool is_inputbuffer_full(void) {
    if (inport_byte(0x64) & 2)
        return true;
    return false;
}

bool activate_keyboard(void) {
    outport_byte(0x64, 0xAE);

    for (int i = 0; i < 0xFFFF; i++) {
        if (!is_inputbuffer_full())
            break;
    }
    outport_byte(0x60, 0xF4);

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 0xFFFF; j++) {
            if (is_outputbuffer_full())
                break;
        }
        if (inport_byte(0x60) == 0xFA)
            return true;
    }

    return false;
}

uint8_t get_keyboard_scancode(void) {
    while (!is_outputbuffer_full()) {}
    return inport_byte(0x60);
}