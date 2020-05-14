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
                    GDT_ACCESS_PRESENT|GDT_ACCESS_PRIV_RING0|GDT_ACCESS_TYPE|GDT_ACCESS_EXECUTABLE|GDT_ACCESS_READABLE_WRITABLE )

#define GDT_KERNEL_DATA PREPARE_GDT_ENTRY(0, 0xfffff, \
                    GDT_FLAG_LONG | \
                    GDT_FLAG_GRANUALRITY, \
                    GDT_ACCESS_PRESENT|GDT_ACCESS_PRIV_RING0|GDT_ACCESS_TYPE|GDT_ACCESS_READABLE_WRITABLE )

#define GDT_KERNEL_CODE32 PREPARE_GDT_ENTRY(0, 0xfffff,\
                    GDT_FLAG_DB | \
                    GDT_FLAG_GRANUALRITY, \
                    GDT_ACCESS_PRESENT|GDT_ACCESS_PRIV_RING0|GDT_ACCESS_TYPE|GDT_ACCESS_EXECUTABLE|GDT_ACCESS_READABLE_WRITABLE )

#define GDT_KERNEL_DATA32 PREPARE_GDT_ENTRY(0, 0xfffff, \
                    GDT_FLAG_DB | \
                    GDT_FLAG_GRANUALRITY, \
                    GDT_ACCESS_PRESENT|GDT_ACCESS_PRIV_RING0|GDT_ACCESS_TYPE|GDT_ACCESS_READABLE_WRITABLE )


#define GDT_TABLE_ALIGNMENT 0x1000
/* 0x100 entries per GDT */
#define GDT_TABLE_SIZE  0x800

#ifndef __ASSEMBLER__
#pragma pack( push, 1 )
struct GDTDescr_8 {
   uint16_t lowerlimit;
   uint16_t base_address1;
   uint8_t base_address2;
   uint8_t access;
   uint8_t upperlimit_flags;
   uint8_t base_address3;
};

struct GDTDescr_16{
   uint16_t lowerlimit;
   uint16_t base_address1;
   uint8_t base_address2;
   uint8_t access;
   uint8_t upperlimit_flags;
   uint8_t base_address3;
   uint32_t base_address4;
   uint32_t reserved;
};

#pragma pack(pop)

void set_GDT_entry8(struct GDTDescr_8 * entry, uint32_t baseaddress, uint32_t limit, uint8_t flags, uint8_t access){
    entry->lowerlimit = limit & 0xffff;
    entry->upperlimit_flags = (flags<<4) | (limit >> 16)&0x0f;
    entry->access = access;
    entry->base_address1 = baseaddress & 0xffff;
    entry->base_address2 = (baseaddress >> 16) & 0xff;
    entry->base_address3 = (baseaddress >> 24) & 0xff;

    return;
}

void set_GDT_entry16(struct GDTDescr_16 * entry, uint64_t baseaddress, uint32_t limit, uint8_t flags, uint8_t access){
    entry->lowerlimit = limit & 0xffff;
    entry->upperlimit_flags = (flags<<4) | (limit >> 16)&0x0f ;
    entry->access = access;
    entry->base_address1 = baseaddress & 0xffff;
    entry->base_address2 = (baseaddress >> 16) & 0xff;
    entry->base_address3 = (baseaddress >> 24) & 0xff;
    entry->base_address4 = baseaddress >> 32;
    entry->reserved = 0;
}

#endif //end assembler


#endif
