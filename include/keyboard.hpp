#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <stdint.h>

#include <queue.hpp>

#define KEY_MAPPINGTABLEMAXCOUNT 89
#define KEY_NONE 0x00
#define KEY_ENTER '\n'
#define KEY_TAB '\t'
#define KEY_ESC 0x1B
#define KEY_BACKSPACE 0x08

#define KEY_CTRL 0x81
#define KEY_LSHIFT 0x82
#define KEY_RSHIFT 0x83
#define KEY_PRINTSCREEN 0x84
#define KEY_LALT 0x85
#define KEY_CAPSLOCK 0x86
#define KEY_F1 0x87
#define KEY_F2 0x88
#define KEY_F3 0x89
#define KEY_F4 0x8A
#define KEY_F5 0x8B
#define KEY_F6 0x8C
#define KEY_F7 0x8D
#define KEY_F8 0x8E
#define KEY_F9 0x8F
#define KEY_F10 0x90
#define KEY_NUMLOCK 0x91
#define KEY_SCROLLLOCK 0x92
#define KEY_HOME 0x93
#define KEY_UP 0x94
#define KEY_PAGEUP 0x95
#define KEY_LEFT 0x96
#define KEY_CENTER 0x97
#define KEY_RIGHT 0x98
#define KEY_END 0x99
#define KEY_DOWN 0x9A
#define KEY_PAGEDOWN 0x9B
#define KEY_INS 0x9C
#define KEY_DEL 0x9D
#define KEY_F11 0x9E
#define KEY_F12 0x9F
#define KEY_PAUSE 0xA0

#define KEY_FLAGS_UP 0x00
#define KEY_FLAGS_DOWN 0x01
#define KEY_FLAGS_EXTENDEDKEY 0x02

#define SCANCODES_RSHIFT 0x36
#define SCANCODES_LSHIFT 0x2a
#define SCANCODES_CAPSLOCK 0x3a
#define SCANCODES_NUMLOCK 0x45
#define SCANCODES_SCROLLLOCK 0x46

extern uint8_t asccode[KEY_MAPPINGTABLEMAXCOUNT][2];

class KeyboardData {
   public:
    uint8_t AsciiCode;
    uint8_t ScanCode;
    uint8_t Flag;
};

class KeyboardDevice {
   private:
    bool bCapsLock;
    bool bShift;
    bool bExtended;
    bool bNumLock;
    bool bScrollLock;
    Queue<KeyboardData> KeyQueue;

    bool waitACK();
    inline bool IsNumberPadScanCode(uint8_t ScanCode) {
        if ((71 <= ScanCode) && (ScanCode <= 83)) return true;
        return false;
    }

    inline bool IsAlphaScanCode(uint8_t ScanCode) {
        if (('a' <= asccode[ScanCode][0]) && (asccode[ScanCode][0] <= 'z'))
            return true;
        return false;
    }

    inline bool IsNumberOrSymbolScanCode(uint8_t ScanCode) {
        if ((2 <= ScanCode) && (ScanCode <= 53) &&
            (IsAlphaScanCode(ScanCode) == false) &&
            (0x20 <= asccode[ScanCode][0]) && (asccode[ScanCode][0] <= 0x7f))
            return true;
        return false;
    }

   public:
    KeyboardDevice() {
        bCapsLock = false;
        bShift = false;
        bExtended = false;
        bNumLock = false;
        bScrollLock = false;
    }

    bool isOutBufferFull();
    bool isInBufferFull();
    uint8_t GetScanCode();
    bool Activate();
    bool ChangeLED();
    bool IsUseCombinedCode(uint8_t ScanCode);
    void UpdateCombinationStatusAndLed(uint8_t ScanCode);
    bool ConvertScanCodeToAscii(uint8_t ScanCode, uint8_t *pAscii,
                                uint8_t *pFlag);
    bool readFromKeyboard();
    bool writeToQueue(uint8_t ScanCode);
    bool readFromQueue(KeyboardData *target);
};

#endif
