#ifndef _KAPI_X86_CMOS_HPP
#define _KAPI_X86_CMOS_HPP

#include <stdint.h>

#include <kapi/asm-generic.hpp>
#include <kapi/const.hpp>
#include <kapi/io.hpp>

// CMOS port number
const uint8_t kCmosAddrPort = 0x70;
const uint8_t kCmosDataPort = 0x71;

// CMOS NMI flag
// 'outb(0x70, (no_nmi << 7) | addr)' disables NMI.
const uint8_t kCmosNoNmiBitIdx = 0x7;
const uint8_t kCmosNoNmi = _BIT(kCmosNoNmiBitIdx);

// CMOS RTC registers
// Note:
//  A. RTC day of week register is unreliable. Avoid using it.
//  B. RTC status register A - Update in progress flag
//  C. RTC status register B - Format of data(BCD/binary) & time(24h/12h)
const uint8_t kCmosSecReg = 0x0;
const uint8_t kCmosMinReg = 0x2;
const uint8_t kCmosHourReg = 0x4;
const uint8_t kCmosDayOfWeekReg = 0x6;
const uint8_t kCmosDayOfMonthReg = 0x7;
const uint8_t kCmosMonthReg = 0x8;
const uint8_t kCmosYearReg = 0x9;
const uint8_t kCmosCenturyReg = 0x32;
const uint8_t kCmosStatusAReg = 0xA;
const uint8_t kCmosStatusBReg = 0xB;

class Cmos {
   public:
    static uint8_t read_cmos(uint8_t addr, bool no_nmi) {
        uint8_t out_addr, cmos_data;

        if (no_nmi) out_addr = kCmosNoNmi | addr;
        outb(kCmosAddrPort, out_addr);
        wait_little();
        cmos_data = inb(kCmosDataPort);

        return cmos_data;
    }
};

#endif  // _KAPI_X86_CMOS_HPP