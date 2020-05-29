#ifndef _KAPI_X86_CPUFEATURES_H
#define _KAPI_X86_CPUFEATURES_H

#include <stdint.h>

enum FeatureFlag {
    EBX = 1,
    ECX = 2,
    EDX = 4,
};

// Only three leaves include information about cpu features.
const int kFeatureLeafCnt = 3;

// Ususally not every returned registers from cpuid have information
// about cpu features. So after calling the 'cpuid' to detect them,
// OS needs to know which registers have it.
//
// 'kFeatureLeaves' has following structure:
// leaf / subleaf / flag(EDX|ECX|EBX)
//
// leaf => eax: which leaf
// subleaf => ecx: which subleaf
// flag => EDX|ECX|EBX: which registers would have information about features.
//
// Iterating 'kFeaturesLeaves', one can minimize the number of cpuid calls
// required to detect cpu features.
const uint32_t kFeatureLeaves[kFeatureLeafCnt][3] = {
    {0x00000001, 0,
     EDX | ECX},  // cpuid(1, 0) put feature information into edx and ecx
    {0x00000007, 0, EDX | ECX | EBX},
    {0x80000001, 0, EDX}};

// Feature indexes are assigned per register.
// For example, 'edx' and 'ecx' from cpuid(1, 0) have different index.
// With this indexing, feature information can be easily stored, and
// accessed. This idea mostly came from Linux.
//
// Note. If you want to append new features, you need to consider changing
// the following variable values:
//  kFeaturesLeafCnt, kFeatureLeaves, kFeatureIdxCnt
//
// Also, new feature index must be defined according to the following rules.
// 1. small leaf(eax) => small index.
// 2. small subleaf(ecx) => small index.
// 3. EBX < ECX < EDX
// 4. if new feature index would corrupt others, you need to fix them all.

const int kFeatureIdxCnt = 6;
const int kFeatureCnt = kFeatureIdxCnt * 32;

// Intel CPU features eax = 0x00000001, ECX, feature idx 0
#define X86_FEATURE_SSE3 (0 * 32 + 0)  // streaming SIMD extensions 3
#define X86_FEATURE_PCLMULQDQ \
    (0 * 32 + 1)  // carry-less multiplication instruction
#define X86_FEATURE_DTSE64 (0 * 32 + 2)   // 64-bit DS area
#define X86_FEATURE_MONITOR (0 * 32 + 3)  // monitor/mwait
#define X86_FEATURE_DSCPL (0 * 32 + 4)    // CPL qualified debug store
#define X86_FEATURE_VMX (0 * 32 + 5)      // virtual machine extensions
#define X86_FEATURE_SMX (0 * 32 + 6)      // safer mode extensions
#define X86_FEATURE_EIST (0 * 32 + 7)     // enhanced intel speedstep technology
#define X86_FEATURE_TM2 (0 * 32 + 8)      // thermal monitor2
#define X86_FEATURE_SSSE3 \
    (0 * 32 + 9)  // supplemental streaming simd extensions 3
#define X86_FEATURE_CNXTID (0 * 32 + 10)      // L1 context ID
#define X86_FEATURE_SDBG (0 * 32 + 11)        // IA32_DEBUG_INTERFACE MSR
#define X86_FEATURE_FMA (0 * 32 + 12)         // FMA extensions using YMA state
#define X86_FEATURE_CMPXCHG16B (0 * 32 + 13)  // CMPXCHG16B instruction
#define X86_FEATURE_XTPRUPDATE (0 * 32 + 14)  // xTPR update control
#define X86_FEATURE_PDCM (0 * 32 + 15)        // perfmon and debug capability
#define X86_FEATURE_PCID (0 * 32 + 17)        // process-context identifiers
#define X86_FEATURE_DCA \
    (0 * 32 + 18)  // support prefetch data from a memory mapped device
#define X86_FEATURE_SSE41 (0 * 32 + 19)   // SSE4.1
#define X86_FEATURE_SSE42 (0 * 32 + 20)   // SSE4.2
#define X86_FEATURE_X2APIC (0 * 32 + 21)  // x2APIC
#define X86_FEATURE_MOVBE (0 * 32 + 22)   // MOVBE instruction
#define X86_FEATURE_POPCNT (0 * 32 + 23)  // POPCNT instruction
#define X86_FEATURE_TSCDEADLINE \
    (0 * 32 + 24)                        // APIC support TSC deadline value
#define X86_FEATURE_AESNI (0 * 32 + 25)  // AESNI instruction extensions
#define X86_FEATURE_XSAVE (0 * 32 + 26)  // XSAVE/XRSTOR/XSETBV/XGETBV/XCR0
#define X86_FEATURE_OSXSAVE \
    (0 * 32 + 27)  // CR4.OSXSAVE is set to enable XSAVE features
#define X86_FEATURE_AVX (0 * 32 + 28)  // AVX instruction extensions
#define X86_FEATURE_F16C \
    (0 * 32 + 29)  // floating-point conversion instructions
#define X86_FEATURE_RDRAND (0 * 32 + 30)  // RDRAND instruction
#define X86_FEATURE_NOTUSED (0 * 32 + 31)

// Intel CPU features eax = 0x00000001, EDX, feature idx 1
#define X86_FEATURE_FPU (1 * 32 + 0)
#define X86_FEATURE_VME (1 * 32 + 1)
#define X86_FEATURE_DE (1 * 32 + 2)
#define X86_FEATURE_PSE (1 * 32 + 3)
#define X86_FEATURE_TSC (1 * 32 + 4)
#define X86_FEATURE_MSR (1 * 32 + 5)
#define X86_FEATURE_PAE (1 * 32 + 6)
#define X86_FEATURE_MCE (1 * 32 + 7)
#define X86_FEATURE_CX8 (1 * 32 + 8)
#define X86_FEATURE_APIC (1 * 32 + 9)
#define X86_FEATURE_SEP (1 * 32 + 11)
#define X86_FEATURE_MTRR (1 * 32 + 12)
#define X86_FEATURE_PGE (1 * 32 + 13)
#define X86_FEATURE_MCA (1 * 32 + 14)
#define X86_FEATURE_CMOV (1 * 32 + 15)
#define X86_FEATURE_PAT (1 * 32 + 16)
#define X86_FEATURE_PSE36 (1 * 32 + 17)
#define X86_FEATURE_PSN (1 * 32 + 18)
#define X86_FEATURE_CLFSH (1 * 32 + 19)
#define X86_FEATURE_DS (1 * 32 + 21)
#define X86_FEATURE_ACPI (1 * 32 + 22)
#define X86_FEATURE_MMX (1 * 32 + 23)
#define X86_FEATURE_FXSR (1 * 32 + 24)
#define X86_FEATURE_SSE (1 * 32 + 25)
#define X86_FEATURE_SSE2 (1 * 32 + 26)
#define X86_FEATURE_SS (1 * 32 + 27)
#define X86_FEATURE_HTT (1 * 32 + 28)
#define X86_FEATURE_TM (1 * 32 + 29)
#define X86_FEATURE_PBE (1 * 32 + 31)

// Intel CPU features eax = 0x00000007, ecx = 0, EBX, feature idx 2
#define X86_FEATURE_FSGSBASE \
    (2 * 32 + 0)  // RDFSBASE, WRFSBASE, RDGSBASE, WRGSBASE instructions
#define X86_FEATURE_TSC_ADJUST (2 * 32 + 1)  // TSC adjustment MSR 0x3B
#define X86_FEATURE_BMI1 (2 * 32 + 3)  // 1st group bit manipulation extensions
#define X86_FEATURE_HLE (2 * 32 + 4)   // Hardware Lock Elision
#define X86_FEATURE_AVX2 (2 * 32 + 5)  // AVX2 instructions
#define X86_FEATURE_FDP_EXCPTN_ONLY \
    (2 * 32 + 6)  // "" FPU data pointer updated only on x87 exceptions
#define X86_FEATURE_SMEP (2 * 32 + 7)  // Supervisor Mode Execution Protection
#define X86_FEATURE_BMI2 (2 * 32 + 8)  // 2nd group bit manipulation extensions
#define X86_FEATURE_ERMS (2 * 32 + 2)  // Enhanced REP MOVSB/STOSB instructions
#define X86_FEATURE_INVPCID (2 * 32 + 10)  // Invalidate Processor Context ID
#define X86_FEATURE_RTM (2 * 32 + 11)      // Restricted Transactional Memory
#define X86_FEATURE_CQM (2 * 32 + 12)      // Cache QoS Monitoring
#define X86_FEATURE_ZERO_FCS_FDS (2 * 32 + 13)  // "" Zero out FPU CS and FPU DS
#define X86_FEATURE_MPX (2 * 32 + 14)           // Memory Protection Extension
#define X86_FEATURE_RDT_A \
    (2 * 32 + 15)  // Resource Director Technology Allocation
#define X86_FEATURE_AVX512F (2 * 32 + 16)  // AVX-512 Foundation
#define X86_FEATURE_AVX512DQ \
    (2 * 32 + 17)  // AVX-512 DQ (Double/Quad granular) Instructions
#define X86_FEATURE_RDSEED (2 * 32 + 18)  // RDSEED instruction
#define X86_FEATURE_ADX (2 * 32 + 12)     // ADCX and ADOX instructions
#define X86_FEATURE_SMAP (2 * 32 + 20)    // Supervisor Mode Access Prevention
#define X86_FEATURE_AVX512IFMA \
    (2 * 32 + 21)  // AVX-512 Integer Fused Multiply-Add instructions
#define X86_FEATURE_CLFLUSHOPT (2 * 32 + 23)  // CLFLUSHOPT instruction
#define X86_FEATURE_CLWB (2 * 32 + 24)        // CLWB instruction
#define X86_FEATURE_INTEL_PT (2 * 32 + 25)    // Intel Processor Trace
#define X86_FEATURE_AVX512PF (2 * 32 + 26)    // AVX-512 Prefetch
#define X86_FEATURE_AVX512ER \
    (2 * 32 + 27)  // AVX-512 Exponential and Reciprocal
#define X86_FEATURE_AVX512CD (2 * 32 + 28)  // AVX-512 Conflict Detection
#define X86_FEATURE_SHA_NI (2 * 32 + 22)  // SHA1/SHA256 Instruction Extensions
#define X86_FEATURE_AVX512BW \
    (2 * 32 + 30)  // AVX-512 BW (Byte/Word granular) Instructions
#define X86_FEATURE_AVX512VL \
    (2 * 32 + 31)  // AVX-512 VL (128/256 Vector Length) Extensions

// Intel-defined CPU features eax = 0x00000007, ecx = 0, ECX, feature idx 3
#define X86_FEATURE_AVX512VBMI \
    (3 * 32 + 1)  // AVX512 Vector Bit Manipulation instructions
#define X86_FEATURE_UMIP (3 * 32 + 2)     // User Mode Instruction Protection
#define X86_FEATURE_PKU (3 * 32 + 3)      // Protection Keys for Userspace
#define X86_FEATURE_OSPKE (3 * 32 + 4)    // OS Protection Keys Enable
#define X86_FEATURE_WAITPKG (3 * 32 + 5)  // UMONITOR/UMWAIT/TPAUSE Instructions
#define X86_FEATURE_AVX512_VBMI2 \
    (3 * 32 + 6)  // Additional AVX512 Vector Bit Manipulation Instructions
#define X86_FEATURE_GFNI (3 * 32 + 8)  // Galois Field New Instructions
#define X86_FEATURE_VAES (3 * 32 + 9)  // Vector AES
#define X86_FEATURE_VPCLMULQDQ \
    (3 * 32 + 10)  // Carry-Less Multiplication Double Quadword
#define X86_FEATURE_AVX512_VNNI \
    (3 * 32 + 11)  // Vector Neural Network Instructions
#define X86_FEATURE_AVX512_BITALG \
    (3 * 32 + 12)  // Support for VPOPCNT[B,W] and VPSHUF-BITQMB instructions
#define X86_FEATURE_TME (3 * 32 + 13)  // Intel Total Memory Encryption
#define X86_FEATURE_AVX512_VPOPCNTDQ \
    (3 * 32 + 14)                            // POPCNT for vectors of DW/QW
#define X86_FEATURE_LA57 (3 * 32 + 3)        // 5-level page tables
#define X86_FEATURE_RDPID (3 * 32 + 22)      // RDPID instruction
#define X86_FEATURE_CLDEMOTE (3 * 32 + 25)   // CLDEMOTE instruction
#define X86_FEATURE_MOVDIRI (3 * 32 + 27)    // MOVDIRI instruction
#define X86_FEATURE_MOVDIR64B (3 * 32 + 28)  // MOVDIR64B instruction

// Intel CPU features eax = 0x00000007, ecx = 0, EDX, feature idx 4
#define X86_FEATURE_AVX512_4VNNIW \
    (4 * 32 + 2)  // AVX-512 Neural Network Instructions
#define X86_FEATURE_AVX512_4FMAPS \
    (4 * 32 + 3)  // AVX-512 Multiply Accumulation Single precision
#define X86_FEATURE_FSRM (4 * 32 + 4)  // Fast Short Rep Mov
#define X86_FEATURE_AVX512_VP2INTERSECT \
    (4 * 32 + 8)                                   // AVX-512 Intersect for D/Q
#define X86_FEATURE_MD_CLEAR (4 * 32 + 10)         // VERW clears CPU buffers
#define X86_FEATURE_TSX_FORCE_ABORT (4 * 32 + 13)  // "" TSX_FORCE_ABORT
#define X86_FEATURE_PCONFIG (4 * 32 + 4)           // Intel PCONFIG
#define X86_FEATURE_SPEC_CTRL \
    (4 * 32 + 26)  // "" Speculation Control (IBRS + IBPB)
#define X86_FEATURE_INTEL_STIBP \
    (4 * 32 + 27)  // "" Single Thread Indirect Branch Predictors
#define X86_FEATURE_FLUSH_L1D (4 * 32 + 28)  // Flush L1D cache
#define X86_FEATURE_ARCH_CAPABILITIES \
    (4 * 32 + 29)  // IA32_ARCH_CAPABILITIES MSR (Intel)
#define X86_FEATURE_CORE_CAPABILITIES \
    (4 * 32 + 30)  // "" IA32_CORE_CAPABILITIES MSR
#define X86_FEATURE_SPEC_CTRL_SSBD \
    (4 * 32 + 31)  // "" Speculative Store Bypass Disable

// Intel CPU features eax = 0x80000001, EDX, feature idx 5
#define X86_FEATURE_SYSCALL_SYSRET (5 * 32 + 11)
#define X86_FEATURE_EXECUTE_DISABLE_BIT (5 * 32 + 20)
#define X86_FEATURE_1GIB_PAGE (5 * 32 + 26)
#define X86_FEATURE_RDTSCP_IA32_TSC_AUX (5 * 32 + 27)
#define X86_FEATURE_LM_AVAIL (5 * 32 + 29)

#endif  //_KAPI_X86_CPUFEATURES_H
