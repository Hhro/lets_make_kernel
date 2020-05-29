#include <keyboard.hpp>
#include <stdio.hpp>

extern "C" KeyboardDevice DKeyboard;

uint8_t terminal_getchar() {
    KeyboardData KeyData;
    bool res;

    while (1) {
        res = DKeyboard.readFromQueue(&KeyData);
        if (res && (KeyData.Flag & KEY_FLAGS_DOWN) &&
            (KeyData.AsciiCode <= 0x7f)) {
            return KeyData.AsciiCode;
        }
    }
}