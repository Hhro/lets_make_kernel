#include <kapi/idt.hpp>
#include <kapi/io.hpp>
#include <keyboard.hpp>
#include <queue.hpp>

uint8_t asccode[KEY_MAPPINGTABLEMAXCOUNT][2] = {
    /*  0   */ {KEY_NONE, KEY_NONE},
    /*  1   */ {KEY_ESC, KEY_ESC},
    /*  2   */ {'1', '!'},
    /*  3   */ {'2', '@'},
    /*  4   */ {'3', '#'},
    /*  5   */ {'4', '$'},
    /*  6   */ {'5', '%'},
    /*  7   */ {'6', '^'},
    /*  8   */ {'7', '&'},
    /*  9   */ {'8', '*'},
    /*  10  */ {'9', '('},
    /*  11  */ {'0', ')'},
    /*  12  */ {'-', '_'},
    /*  13  */ {'=', '+'},
    /*  14  */ {KEY_BACKSPACE, KEY_BACKSPACE},
    /*  15  */ {KEY_TAB, KEY_TAB},
    /*  16  */ {'q', 'Q'},
    /*  17  */ {'w', 'W'},
    /*  18  */ {'e', 'E'},
    /*  19  */ {'r', 'R'},
    /*  20  */ {'t', 'T'},
    /*  21  */ {'y', 'Y'},
    /*  22  */ {'u', 'U'},
    /*  23  */ {'i', 'I'},
    /*  24  */ {'o', 'O'},
    /*  25  */ {'p', 'P'},
    /*  26  */ {'[', '{'},
    /*  27  */ {']', '}'},
    /*  28  */ {'\n', '\n'},
    /*  29  */ {KEY_CTRL, KEY_CTRL},
    /*  30  */ {'a', 'A'},
    /*  31  */ {'s', 'S'},
    /*  32  */ {'d', 'D'},
    /*  33  */ {'f', 'F'},
    /*  34  */ {'g', 'G'},
    /*  35  */ {'h', 'H'},
    /*  36  */ {'j', 'J'},
    /*  37  */ {'k', 'K'},
    /*  38  */ {'l', 'L'},
    /*  39  */ {';', ':'},
    /*  40  */ {'\'', '\"'},
    /*  41  */ {'`', '~'},
    /*  42  */ {KEY_LSHIFT, KEY_LSHIFT},
    /*  43  */ {'\\', '|'},
    /*  44  */ {'z', 'Z'},
    /*  45  */ {'x', 'X'},
    /*  46  */ {'c', 'C'},
    /*  47  */ {'v', 'V'},
    /*  48  */ {'b', 'B'},
    /*  49  */ {'n', 'N'},
    /*  50  */ {'m', 'M'},
    /*  51  */ {',', '<'},
    /*  52  */ {'.', '>'},
    /*  53  */ {'/', '?'},
    /*  54  */ {KEY_RSHIFT, KEY_RSHIFT},
    /*  55  */ {'*', '*'},
    /*  56  */ {KEY_LALT, KEY_LALT},
    /*  57  */ {' ', ' '},
    /*  58  */ {KEY_CAPSLOCK, KEY_CAPSLOCK},
    /*  59  */ {KEY_F1, KEY_F1},
    /*  60  */ {KEY_F2, KEY_F2},
    /*  61  */ {KEY_F3, KEY_F3},
    /*  62  */ {KEY_F4, KEY_F4},
    /*  63  */ {KEY_F5, KEY_F5},
    /*  64  */ {KEY_F6, KEY_F6},
    /*  65  */ {KEY_F7, KEY_F7},
    /*  66  */ {KEY_F8, KEY_F8},
    /*  67  */ {KEY_F9, KEY_F9},
    /*  68  */ {KEY_F10, KEY_F10},
    /*  69  */ {KEY_NUMLOCK, KEY_NUMLOCK},
    /*  70  */ {KEY_SCROLLLOCK, KEY_SCROLLLOCK},

    /*  71  */ {KEY_HOME, '7'},
    /*  72  */ {KEY_UP, '8'},
    /*  73  */ {KEY_PAGEUP, '9'},
    /*  74  */ {'-', '-'},
    /*  75  */ {KEY_LEFT, '4'},
    /*  76  */ {KEY_CENTER, '5'},
    /*  77  */ {KEY_RIGHT, '6'},
    /*  78  */ {'+', '+'},
    /*  79  */ {KEY_END, '1'},
    /*  80  */ {KEY_DOWN, '2'},
    /*  81  */ {KEY_PAGEDOWN, '3'},
    /*  82  */ {KEY_INS, '0'},
    /*  83  */ {KEY_DEL, '.'},
    /*  84  */ {KEY_NONE, KEY_NONE},
    /*  85  */ {KEY_NONE, KEY_NONE},
    /*  86  */ {KEY_NONE, KEY_NONE},
    /*  87  */ {KEY_F11, KEY_F11},
    /*  88  */ {KEY_F12, KEY_F12}};

bool KeyboardDevice::isOutBufferFull() {
  if (inb(0x64) & 0x1) return true;
  return false;
}

bool KeyboardDevice::isInBufferFull() {
  if (inb(0x64) & 0x2) return true;
  return false;
}

uint8_t KeyboardDevice::GetScanCode() {
  while (isOutBufferFull() == false)
    ;

  return inb(0x60);
}

bool KeyboardDevice::waitACK() {
  bool res = false;
  uint8_t Data;

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 0xffff; j++) {
      if (isOutBufferFull()) break;
    }
    Data = inb(0x60);

    if (Data == 0xFA) {
      res = true;
      break;
    } else {
      writeToQueue(Data);
    }
  }
  return res;
}

bool KeyboardDevice::Activate() {
  bool BeforeInterruptStatus, res;

  BeforeInterruptStatus = setInterruptFlag(false);
  outb(0x64, 0xAE);  // keyboard controller activate command
  for (int i = 0; i < 0xffff; i++)
    if (isInBufferFull() == false) break;

  outb(0x60, 0xF4);  // keyboard device activate command
  res = waitACK();
  setInterruptFlag(BeforeInterruptStatus);
  return res;
}

bool KeyboardDevice::ChangeLED() {
  bool BeforeInterruptStatus, res;

  BeforeInterruptStatus = setInterruptFlag(false);

  while (isInBufferFull())
    ;
  outb(0x60, 0xED);  // inform LED stuts data will send
  while (isInBufferFull())
    ;

  res = waitACK();
  if (res == false) {
    setInterruptFlag(BeforeInterruptStatus);
    return false;
  }

  outb(0x60, (bCapsLock << 2 | bNumLock << 1 | bScrollLock));
  while (isInBufferFull())
    ;

  res = waitACK();
  setInterruptFlag(BeforeInterruptStatus);
  return res;
}

bool KeyboardDevice::IsUseCombinedCode(uint8_t ScanCode) {
  uint8_t DownScanCode;
  bool UseCombined = false;

  DownScanCode = (ScanCode & 0x7f);

  if (IsAlphaScanCode(DownScanCode)) {
    if (bCapsLock || bShift)
      UseCombined = true;
    else
      UseCombined = false;
  } else if (IsNumberOrSymbolScanCode(DownScanCode)) {
    if (bShift)
      UseCombined = true;
    else
      UseCombined = false;
  } else if (IsNumberPadScanCode(DownScanCode) && (bExtended == false)) {
    if (bNumLock)
      UseCombined = true;
    else
      UseCombined = false;
  }

  return UseCombined;
}

void KeyboardDevice::UpdateCombinationStatusAndLed(uint8_t ScanCode) {
  bool IsDown, LedStatusChange = false;
  uint8_t DownScanCode;

  DownScanCode = ScanCode & 0x7f;
  if (ScanCode & 0x80)
    IsDown = false;
  else
    IsDown = true;

  if ((DownScanCode == SCANCODES_LSHIFT || DownScanCode == SCANCODES_RSHIFT)) {
    bShift = IsDown;
  } else if (DownScanCode == SCANCODES_NUMLOCK && IsDown) {
    bNumLock ^= true;
    LedStatusChange = true;
  } else if (DownScanCode == SCANCODES_CAPSLOCK && IsDown) {
    bCapsLock ^= true;
    LedStatusChange = true;
  } else if (DownScanCode == SCANCODES_SCROLLLOCK && IsDown) {
    bScrollLock ^= true;
    LedStatusChange = true;
  }

  if (LedStatusChange) {
    ChangeLED();
  }
}

bool KeyboardDevice::ConvertScanCodeToAscii(uint8_t ScanCode, uint8_t *pAscii,
                                            uint8_t *pFlag) {
  bool UseCombined;

  if (ScanCode == 0xE0) {
    bExtended = true;
    return false;
  }

  UseCombined = IsUseCombinedCode(ScanCode);
  if (UseCombined)
    *pAscii = asccode[ScanCode & 0x7f][1];
  else
    *pAscii = asccode[ScanCode & 0x7f][0];

  if (bExtended == true) {
    *pFlag = KEY_FLAGS_EXTENDEDKEY;
    bExtended = false;
  } else
    *pFlag = 0;

  if ((ScanCode & 0x80) == 0) {
    *pFlag |= KEY_FLAGS_DOWN;
  }

  UpdateCombinationStatusAndLed(ScanCode);
  return true;
}

bool KeyboardDevice::readFromKeyboard() {
  uint8_t ScanCode;

  ScanCode = GetScanCode();
  return writeToQueue(ScanCode);
}

bool KeyboardDevice::writeToQueue(uint8_t ScanCode) {
  KeyboardData Data;
  bool res, BeforeInterruptState;

  res = false;

  Data.ScanCode = ScanCode;
  if (ConvertScanCodeToAscii(Data.ScanCode, &(Data.AsciiCode), &(Data.Flag)) ==
      true) {
    BeforeInterruptState = setInterruptFlag(false);
    res = KeyQueue.push(Data);
    setInterruptFlag(BeforeInterruptState);
  }

  return res;
}

bool KeyboardDevice::readFromQueue(KeyboardData *target) {
  bool res, BeforeInterruptState;

  if (KeyQueue.isEmpty()) {
    return false;
  }

  BeforeInterruptState = setInterruptFlag(false);
  res = KeyQueue.pop(target);
  setInterruptFlag(BeforeInterruptState);
  return res;
}

KeyboardDevice DKeyboard;