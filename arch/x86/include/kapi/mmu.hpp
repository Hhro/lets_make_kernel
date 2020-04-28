#ifndef _KAPI_X86_MMU_H
#define _KAPI_X86_MMU_H

#define PML4_SIZE   0x1000
#define PML4_ALIGN  0x1000
#define PML4_ENTRY_SIZE   8
#define PML4_ADDR_TO_ENTRY_IDX(addr)    (((addr)>>39)&0x1FF)

#define PML4E_PRESENT   (1 << 0)
#define PML4E_WRITABLE (1 << 1)
#define PML4E_PRIV_LEVEL    (1 << 2)

#define PDPT_SIZE   0x1000
#define PDPT_ALIGN  0x1000
#define PDPT_ENTRY_SIZE   8
#define PDPT_ADDR_TO_ENTRY_IDX(addr)    (((addr)>>30)&0x1FF)

#define PDPTE_PRESENT   (1 << 0)
#define PDPTE_WRITABLE (1 << 1)
#define PDPTE_PRIV_LEVEL    (1 << 2)

#define PD_SIZE 0x200000
#define PD_ALIGN  0x1000
#define PD_ENTRY_SIZE   8
#define PD_ADDR_TO_ENTRY_IDX(addr)    (((addr)>>21)&0x1FF)

#define PDE_PRESENT   (1 << 0)
#define PDE_WRITABLE (1 << 1)
#define PDE_PRIV_LEVEL    (1 << 2)
#define PDE_HUGE      (1 << 7)

#define PT_SIZE   0x1000
#define PT_ALIGN  0x1000
#define PT_ENTRY_SIZE   8
#define PT_ADDR_TO_ENTRY_IDX(addr)    (((addr)>>12)&0x1FF)

#define PTE_PRESENT   (1 << 0)
#define PTE_WRITABLE (1 << 1)
#define PTE_PRIV_LEVEL    (1 << 2)

#endif
