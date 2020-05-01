#ifndef _KAPI_X86_GDT_H
#define _KAPI_X86_GDT_H

#define GDT_ENTRY_SIZE  8

#define GDT_ACCESS_PRESENT  (1 << 7)
#define GDT_ACCESS_PRIV_RING0   (0 << 5)
#define GDT_ACCESS_PRIV_RING3   (3 << 5)
#define GDT_ACCESS_TYPE  (1 << 4)
#define GDT_ACCESS_EXECUTABLE  (1 << 3)
#define GDT_ACCESS_DIRECTION  (1 << 2)
#define GDT_ACCESS_READABLE_WRITABLE  (1 << 1)
#define GDT_ACCESS_ACCESSED  (1 << 0)

#define GDT_FLAG_GRANUALRITY (1 << 3)
#define GDT_FLAG_DB (1 << 2)
#define GDT_FLAG_LONG (1 << 1)

#define PREPARE_GDT_ENTRY(base, limit, flags, access)   \
(\
    (((((base))>>24) & 0xFF) << 56) |   \
    ((((flags)) & 0x0F) << 52) |   \
    (((((limit)) >> 16) & 0x0F) << 48) |   \
    ((((access)) & 0xFF) << 40) |   \
    ((((base)) & 0xFFFFFF) << 16) |   \
    (((limit)) & 0xFFFF)    \
)

/* Null descriptor, never be referenced */
#define GDT_NULL_ENTRY PREPARE_GDT_ENTRY(0, 0, 0, 0)

#define GDT_KERNEL_CODE PREPARE_GDT_ENTRY(0, 0xfffff,\
                    GDT_FLAG_LONG | \
                    GDT_FLAG_GRANUALRITY, \
                    0x9a)

#define GDT_KERNEL_DATA PREPARE_GDT_ENTRY(0, 0xfffff, \
                    GDT_FLAG_LONG | \
                    GDT_FLAG_GRANUALRITY, \
                    0x92)

#define GDT_KERNEL_CODE32 PREPARE_GDT_ENTRY(0, 0xfffff,\
                    GDT_FLAG_DB | \
                    GDT_FLAG_GRANUALRITY, \
                    0x9a)

#define GDT_KERNEL_DATA32 PREPARE_GDT_ENTRY(0, 0xfffff, \
                    GDT_FLAG_DB | \
                    GDT_FLAG_GRANUALRITY, \
                    0x92)

#define GDT_TABLE_ALIGNMENT 0x1000
/* 0x100 entries per GDT */
#define GDT_TABLE_SIZE  0x800
#endif
