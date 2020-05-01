#include <kapi/const.hpp>
#include <kapi/cpuid.hpp>
#include <kapi/cpuinfo.hpp>
#include <kapi/flag.hpp>

// Detect basic cpu information including maximum eax input value, vendor name,
// and cpu model name. This process should be performed early for
// further detection.
void CpuInfo::DetectCpuidLevel() {
    if (!IsCpuidAvail()) {
        set_cpuid_level(kCpuidNotAvail);
        return;
    }

    char cpu_vendor_id[kCpuVendorIdLen] = {0, };

    // Get maximum input eax value for basic cpuid & CPU vendor name
    // cpuid(0) => (maxmium_cpuid_level, vndr_id[8], vndr_id[4], vndr_id[0])
    CpuidRegs regs = CpuidRegs(0, 0, 0, 0);
    cpuid(&regs);
    set_cpuid_level(regs.eax());
    *reinterpret_cast<unsigned int*>(&cpu_vendor_id[0]) = regs.edx();
    *reinterpret_cast<unsigned int*>(&cpu_vendor_id[4]) = regs.ecx();
    *reinterpret_cast<unsigned int*>(&cpu_vendor_id[8]) = regs.ebx();
    set_cpu_vendor_id(cpu_vendor_id);

    // Get CPU maximum input eax value for extended cpuid & C
    // cpuid(0x80000000) => (maximum_extended_cpuid_level, rsvd, rsvd, rsvd)
    regs.set_regs(0x80000000, 0, 0, 0);
    cpuid(&regs);
    set_extended_cpuid_level(regs.eax());
}
