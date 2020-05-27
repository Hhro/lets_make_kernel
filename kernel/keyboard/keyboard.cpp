#include<kapi/idt.hpp>
#include<keyboard.hpp>

bool KeyboardDevice::isOutBufferFull() { 
    if(inb(0x64) & 0x1) return true;
    return false;
}

bool KeyboardDevice::isInBufferFull() {
    if(inb(0x64) & 0x2) return true;
    return false;
}

uint8_t KeyboardDevice::GetScanCode() {
    while(isOutBufferFull() == false);

    return inb(0x60);
}

bool KeyboardDevice::waitACK(){
    bool res=false;
    uint8_t Data;

    for(int i=0; i<100; i++){
        for(int j=0; j<0xffff; j++){
            if(isOutBufferFull()) break;
        }
        Data = inb(0x60);
        
        if(Data == 0xFA){
            res = true;
            break;
        }
        else{
            writeToQueue(Data);
        }
    }
    return res;
}

bool KeyboardDevice::Activate() {
    bool BeforeInterruptStatus, res;

    BeforeInterruptStatus = setInterruptFlag(false);
    outb(0x64, 0xAE); //keyboard controller activate command
    for(int i=0; i<0xffff; i++) if(isInBufferFull()==false) break;

    outb(0x60, 0xF4); //keyboard device activate command
    res = waitACK();
    setInterruptFlag(BeforeInterruptStatus);
    return res;
}

bool KeyboardDevice::ChangeLED() {
    bool BeforeInterruptStatus, res;

    BeforeInterruptStatus = setInterruptFlag(false);

    while(isInBufferFull());
    outb(0x60, 0xED); // inform LED stuts data will send
    while(isInBufferFull());

    res = waitACK();
    if( res == false){
        setInterruptFlag(BeforeInterruptStatus);
        return false;
    }

    outb(0x60, (bCapsLock<<2 | bNumLock<<1 | bScrollLock));
    while(isInBufferFull());

    res = waitACK();
    setInterruptFlag(BeforeInterruptStatus);
    return res;
}

bool KeyboardDevice::IsUseCombinedCode(uint8_t ScanCode){
    uint8_t DownScanCode;
    bool UseCombined = false;

    DownScanCode = ScanCode & 0x7f;
    
    if(IsAlphaScanCode(DownScanCode)){
        if(bCapsLock || bShift) UseCombined = true;
        else UseCombined = false;
    }
    else if(IsNumberOrSymbolScanCode(DownScanCode)){
        if(bShift) UseCombined = true;
        else UseCombined = false;
    }
    else if(IsNumberPadScanCode(DownScanCode) && (bExtended == false)){
        if(bNumLock) UseCombined = true;
        else UseCombined = false;
    }

    return UseCombined;
}

void KeyboardDevice::UpdateCombinationStatusAndLed(uint8_t ScanCode){
    bool IsDown, LedStatusChange=false;
    uint8_t DownScanCode;

    DownScanCode = ScanCode & 0x7f;
    if(ScanCode & 0x80) IsDown = false;
    else IsDown = true;

    if( (DownScanCode == SCANCODES_LSHIFT || DownScanCode == SCANCODES_RSHIFT))
    {
        bShift = IsDown;
    }
    else if(DownScanCode == SCANCODES_NUMLOCK && IsDown){
        bNumLock ^= true;
        LedStatusChange = true;
    }
    else if(DownScanCode == SCANCODES_CAPSLOCK && IsDown){
        bCapsLock ^= true;
        LedStatusChange = true;
    }
    else if(DownScanCode == SCANCODES_SCROLLLOCK && IsDown){
        bScrollLock ^= true;
        LedStatusChange = true;
    }

    if(LedStatusChange){
        ChangeLED();
    }
    
}

bool KeyboardDevice::ConvertScanCodeToAscii(uint8_t ScanCode, uint8_t * pAscii, uint8_t *pFlag){
    bool UseCombined;
    
    if(ScanCode == 0xE0){
        bExtended = true;
        return false;
    }

    UseCombined = IsUseCombinedCode(ScanCode);
    if(UseCombined) *pAscii = asccode[ScanCode & 0x7f][0];
    else *pAscii = asccode[ScanCode & 0x7f][1];

    if(bExtended == true)
    {
        *pFlag = KEY_FLAGS_EXTENDEDKEY;
        bExtended = false;
    }
    else *pFlag = 0;

    if(ScanCode & 0x80 == 0){
        *pFlag |= KEY_FLAGS_DOWN;
    }

    return true;
}

bool KeyboardDevice::readFromKeyboard(){
    uint8_t ScanCode;

    ScanCode = GetScanCode();
    return writeToQueue(ScanCode);
}

bool KeyboardDevice::writeToQueue(uint8_t ScanCode){
    KeyboardData Data;
    bool res, BeforeInterruptState;

    res = false;

    Data.ScanCode = ScanCode;
    if(ConvertScanCodeToAscii(Data.ScanCode, &(Data.AsciiCode), &(Data.Flag)) == true){
        BeforeInterruptState = setInterruptFlag(false);
        res = KeyQueue.push(Data);
        setInterruptFlag(BeforeInterruptState);
    }

    return res; 
}

bool KeyboardDevice::readFromQueue(KeyboardData * target){
    bool res, BeforeInterruptState;

    if(KeyQueue.isEmpty()){
        return false;
    }

    BeforeInterruptState = setInterruptFlag(false);
    res = KeyQueue.pop(target);
    setInterruptFlag(BeforeInterruptState);
    return res;
}