#ifndef ARCH_X86_INCLUDE_KAPI_CPU_HPP_
#define ARCH_X86_INCLUDE_KAPI_CPU_HPP_

#include <kapi/const.hpp>
#include <kapi/cpuinfo.hpp>

class Cpu{
 private:
  CpuInfo cpu_info_;
 public:
  bool HasFeature(u32 feature);
};

#endif  // ARCH_X86_INCLUDE_KAPI_CPU_HPP_
