#include <kapi/idt.hpp>

bool setInterruptFlag(bool isEnable){
    uint64_t NowRflags;

    NowRflags = readRFLAGS();

    if(isEnable) enableInterrupt();
    else disableInterrupt();

    if(NowRflags & (1<<9)) return true;
    else return false;
}