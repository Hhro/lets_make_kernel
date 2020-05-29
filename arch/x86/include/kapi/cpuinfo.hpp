#ifndef _KAPI_X86_CPUINFO_H
#define _KAPI_X86_CPUINFO_H

#include <stdint.h>

#include <kapi/cpufeatures.hpp>
#include <kapi/cpuid.hpp>
#include <kapi/flag.hpp>
#include <kapi/string.hpp>

static const int kNotInitialized = -1;
const int kCpuVendorIdLen = 16;

class CpuInfo {
   private:
    int cpuid_avail_;

    // Cpu information has vertical structure consisting of 'leaf',
    // and 'subleaf'. To retrieve information via CPUID, one must
    // specify leaf and subleaf through 'eax' and 'ecx'.
    // Number of leaves is different between CPUs, and number of
    // subleaves is different between leaves.
    // Therefore one must check number of leaf and subleaf before
    // calling cpuid.
    // Variables below are number of leaves and subleaves.
    // Their initializations are required for detail detection.
    uint32_t leaf_cnt_;
    uint32_t extended_leaf_cnt_;
    uint32_t leaf_7_subleaf_cnt_;

    char cpu_vendor_id_[16];

    // Intel CPU architecture supports many features.
    // Since most CPUs don't cover them all, OS must check which features
    // are available on current CPU to behave efficiently with no error.
    bool features_[kFeatureCnt];

   public:
    // constructor
    CpuInfo() {
        cpuid_avail_ = kNotInitialized;
        leaf_cnt_ = kNotInitialized;
        extended_leaf_cnt_ = kNotInitialized;
        leaf_7_subleaf_cnt_ = kNotInitialized;
        memset(cpu_vendor_id_, 0, 16);
        memset(features_, 0, kFeatureCnt);
    }

    // methods
    bool IsCpuidAvail();
    bool IsIntel();
    inline bool IsCpuidNRAvail(uint32_t eax) {
        if (eax < kExtendedCpuidNR)
            return eax <= leaf_cnt();
        else
            return eax <= extended_leaf_cnt();
    }
    void DetectBasicInfo();
    void DetectCpuFeatures();
    void CollectCpuInfo();
    void SetupFeatures(const CpuidRegs* regs, const int feature_flag,
                       const int feature_idx);
    inline bool CpuHas(const uint32_t feature) const {
        return features()[feature];
    }

    // getters
    inline int cpuid_avail() const { return cpuid_avail_; }
    inline uint32_t leaf_cnt() const { return leaf_cnt_; }
    inline uint32_t extended_leaf_cnt() const { return extended_leaf_cnt_; }
    inline uint32_t leaf_7_subleaf_cnt() const { return leaf_7_subleaf_cnt_; }
    inline const char* cpu_vendor_id() const { return cpu_vendor_id_; }
    inline const bool* features() const { return features_; }

    // setters
    inline void set_cpuid_avail(const bool cpuid_avail) {
        cpuid_avail_ = cpuid_avail;
    }
    inline void set_leaf_cnt(const uint32_t leaf_cnt) { leaf_cnt_ = leaf_cnt; }
    inline void set_extended_leaf_cnt(const uint32_t extended_leaf_cnt) {
        extended_leaf_cnt_ = extended_leaf_cnt;
    }
    inline void set_leaf_7_subleaf_cnt(const uint32_t subleaf_cnt) {
        leaf_7_subleaf_cnt_ = subleaf_cnt;
    }
    inline void set_cpu_vendor_id(const char* cpu_vendor_id) {
        memcpy(cpu_vendor_id_, cpu_vendor_id, kCpuVendorIdLen);
    }
    void set_features(const uint32_t feature_reg, const int feature_idx);
};

extern CpuInfo cpu_info;

#endif  // _KAPI_X86_CPUINFO_H