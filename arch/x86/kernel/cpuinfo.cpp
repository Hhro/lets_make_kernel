#include <kapi/const.hpp>
#include <kapi/cpuid.hpp>
#include <kapi/cpuinfo.hpp>
#include <kapi/flag.hpp>

bool CpuInfo::IsCpuidAvail() {
    bool avail;

    if (cpuid_avail() == kNotInitialized) {
        avail = IsFlagChangable(EFLAGS_ID);
        set_cpuid_avail(avail);
    }

    return cpuid_avail();
}

// Detect basic cpu information including maximum eax input value, vendor name,
// and cpu model name. This process should be performed early for
// further detection
void CpuInfo::DetectBasicInfo() {
    if (!IsCpuidAvail()) {
        return;
    }

    char cpu_vendor_id[kCpuVendorIdLen] = {0, };

    // Get maximum input eax value for basic cpuid & CPU vendor name
    // cpuid(0) => (maxmium_leaf_cnt, vndr_id[8], vndr_id[4], vndr_id[0])
    CpuidRegs regs = CpuidRegs(0, 0, 0, 0);
    cpuid(&regs);
    set_leaf_cnt(regs.eax());
    *reinterpret_cast<unsigned int*>(&cpu_vendor_id[0]) = regs.ebx();
    *reinterpret_cast<unsigned int*>(&cpu_vendor_id[4]) = regs.edx();
    *reinterpret_cast<unsigned int*>(&cpu_vendor_id[8]) = regs.ecx();
    set_cpu_vendor_id(cpu_vendor_id);

    // Get maximum input value for supported leaf 7 sub-leaves
    regs.set_regs(0x00000007, 0, 0, 0);
    cpuid(&regs);
    set_leaf_7_subleaf_cnt(regs.eax());

    // Get CPU maximum input eax value for extended cpuid
    // cpuid(0x80000000) => (maximum_extended_leaf_cnt, rsvd, rsvd, rsvd)
    regs.set_regs(0x80000000, 0, 0, 0);
    cpuid(&regs);
    set_extended_leaf_cnt(regs.eax());
}

void CpuInfo::DetectCpuFeatures() {
    if (!IsCpuidAvail()) {
        return;
    }

    // [TODO] make it concise!
    int feature_idx = 0;
    for (int leaf_idx = 0; leaf_idx < kFeatureLeafCnt; leaf_idx++) {
        u32 leaf = kFeatureLeaves[leaf_idx][0];
        u32 subleaf = kFeatureLeaves[leaf_idx][1];
        u32 feature_flag = kFeatureLeaves[leaf_idx][2];

        CpuidRegs regs = CpuidRegs(leaf, 0, subleaf, 0);
        cpuid(&regs);

        if (feature_flag & FeatureFlag::EBX) {
            set_features(regs.ebx(), feature_idx);
            feature_idx += 1;
        }

        if (feature_flag & FeatureFlag::ECX) {
            set_features(regs.ecx(), feature_idx);
            feature_idx += 1;
        }

        if (feature_flag & FeatureFlag::EDX) {
            set_features(regs.edx(), feature_idx);
            feature_idx += 1;
        }
    }
}

void CpuInfo::set_features(const u32 feature_reg, const int feature_idx) {
    bool avail = false;

    for (int bit_idx=0; bit_idx < 32; bit_idx++) {
        avail = (feature_reg & _BIT(bit_idx)) != 0;
        features_[feature_idx * 32 + bit_idx] = avail;
    }
}
