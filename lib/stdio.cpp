#include<stdio.hpp>
#include<keyboard.hpp>

extern "C" KeyboardDevice DKeyboard;

uint8_t getChar(){
    KeyboardData KeyData;
    bool res;

    while(1) {
        res = DKeyboard.readFromQueue(&KeyData);
        if(res && (KeyData.Flag & KEY_FLAGS_DOWN)){
            return KeyData.AsciiCode;
        }
    }
}