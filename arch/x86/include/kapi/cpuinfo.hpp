#ifndef _KAPI_X86_CPUINFO_H
#define _KAPI_X86_CPUINFO_H

#include <kapi/flag.hpp>
#include <kapi/const.hpp>
#include <kapi/cpuid.hpp>

const int kNotInitialized = 0;
const int kCpuidNotAvail = -1;
const int kCpuVendorIdLen = 16;

class CpuInfo {
 private:
  int cpuid_level_;
  char cpu_vendor_id_[16];
  u32 extended_cpuid_level_;
  u32 features_;

 public:
  // constructor
    CpuInfo() {
        cpuid_level_ = kNotInitialized;
        memset(cpu_vendor_id_, 0, 16);
        extended_cpuid_level_ = kNotInitialized;
        features_ = kNotInitialized;
    }

  // methods
    static inline bool IsCpuidAvail() { IsFlagChangable(EFLAGS_ID); }
    static inline bool IsCpuidNRAvail(u32 eax) {
        if (eax < kExtendedCpuidNR)
            return eax <= cpuid_level();
        else
            return eax <= extended_cpuid_level();
  }
  void DetectCpuidLevel();

  // getters & setters
  int cpuid_level() const { return cpuid_level_; }
  u32 extended_cpuid_level() const { return extended_cpuid_level_; }
  void set_cpuid_level(int cpuid_level) { cpuid_level_ = cpuid_level; }
  void set_cpu_vendor_id(char* cpu_vendor_id) {
      memcpy(cpu_vendor_id_, cpu_vendor_id, kCpuVendorIdLen);
  }
  void set_extended_cpuid_level(int extended_cpuid_level) {
      extended_cpuid_level_ = extended_cpuid_level;
  }
};

#endif  // _KAPI_X86_CPUINFO_H