#ifndef _KAPI_X86_CPUINFO_H
#define _KAPI_X86_CPUINFO_H

#include <kapi/flag.hpp>
#include <kapi/const.hpp>

const int kNotInitialized = 0;
const int kCpuidNotAvail = -1;

class CpuInfo {
 private:
  int cpuid_level_;
  u32 extended_cpuid_level_;
  u32 features_;
 public:
  // constructor
  CpuInfo() {
      cpuid_level_ = kNotInitialized;
      extended_cpuid_level_ = kNotInitialized;
      features_ = kNotInitialized;
  }

  // methods
  static inline bool IsCpuidAvail() { IsFlagChangable(EFLAGS_ID); }
  void DetectCpuidLevel();

  // getters & setters
  void set_cpuid_level(int cpuid_level) { cpuid_level_ = cpuid_level; }
  void set_extended_cpuid_level(int extended_cpuid_level) {
      extended_cpuid_level_ = extended_cpuid_level;
  }
};

#endif  // _KAPI_X86_CPUINFO_H
