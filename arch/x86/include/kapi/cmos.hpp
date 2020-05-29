#ifndef _KAPI_X86_CMOS_HPP
#define _KAPI_X86_CMOS_HPP

#include <stdint.h>

#include <kapi/const.hpp>

const uint8_t kCmosAddrPort = 0x70;
const uint8_t kCmosDataPort = 0x71;

const uint8_t kCmosNmiBitIdx = 0x7;
const uint8_t kCmosNmi = _BIT(kCmosNmiBitIdx);

const uint8_t kCmosSecReg = 0x0;
const uint8_t kCmosMinReg = 0x2;
const uint8_t kCmosHourReg = 0x4;
const uint8_t kCmosWeekDayReg = 0x6;
const uint8_t kCmosMonthDayReg = 0x8;
const uint8_t kCmosYearReg = 0x9;
const uint8_t kCmosCenturyReg = 0x32;
const uint8_t kCmosStatusAReg = 0xA;
const uint8_t kCmosStatusBReg = 0xB;

class Cmos {
   public:
    static uint8_t read_cmos(uint8_t addr, bool in_nmi) {
        uint8_t out_addr, cmos_data;

        if (in_nmi) out_addr = kCmosNmi | addr;
        outb(kCmosAddrPort, in_nmi);
        // wait_little();
        cmos_data = inb(kCmosDataPort);

        return cmos_data;
    }
};

#endif  // _KAPI_X86_CMOS_HPP