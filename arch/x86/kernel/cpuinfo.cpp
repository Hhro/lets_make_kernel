#include <kapi/const.hpp>
#include <kapi/cpuid.hpp>
#include <kapi/cpuinfo.hpp>
#include <kapi/flag.hpp>

// For both basic and extended, detect maximum input
// value of EAX for cpuid.
// This process must be performed early for further detection.
void CpuInfo::DetectCpuidLevel() {
    if (!IsCpuidAvail()) {
        set_cpuid_level(kCpuidNotAvail);
        return;
    }

    CpuidRegs regs = CpuidRegs(0, 0, 0, 0);
    cpuid(&regs);
    set_cpuid_level(regs.eax);

    regs.set_regs(0x80000000, 0, 0, 0);
    cpuid(&regs);
    set_extended_cpuid_level(regs.eax);
}
