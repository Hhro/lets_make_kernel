#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <stdint.h>

#define GDT_TYPE_CODE           0x0A
#define GDT_TYPE_DATA           0x02
#define GDT_TYPE_TSS            0x09
#define GDT_FLAGS_LOWER_S       0x10
#define GDT_FLAGS_LOWER_DPL0    0x00
#define GDT_FLAGS_LOWER_DPL1    0x20
#define GDT_FLAGS_LOWER_DPL2    0x40
#define GDT_FLAGS_LOWER_DPL3    0x60
#define GDT_FLAGS_LOWER_P       0x80
#define GDT_FLAGS_UPPER_L       0x20
#define GDT_FLAGS_UPPER_DB      0x40
#define GDT_FLAGS_UPPER_G       0x80

#define GDT_FLAGS_LOWER_KERNELCODE ( GDT_TYPE_CODE | GDT_FLAGS_LOWER_S | \
        GDT_FLAGS_LOWER_DPL0 | GDT_FLAGS_LOWER_P )
#define GDT_FLAGS_LOWER_KERNELDATA ( GDT_TYPE_DATA | GDT_FLAGS_LOWER_S | \
        GDT_FLAGS_LOWER_DPL0 | GDT_FLAGS_LOWER_P )
#define GDT_FLAGS_LOWER_TSS ( GDT_FLAGS_LOWER_DPL0 | GDT_FLAGS_LOWER_P )
#define GDT_FLAGS_LOWER_USERCODE ( GDT_TYPE_CODE | GDT_FLAGS_LOWER_S | \
        GDT_FLAGS_LOWER_DPL3 | GDT_FLAGS_LOWER_P )
#define GDT_FLAGS_LOWER_USERDATA ( GDT_TYPE_DATA | GDT_FLAGS_LOWER_S | \
        GDT_FLAGS_LOWER_DPL3 | GDT_FLAGS_LOWER_P )

#define GDT_FLAGS_UPPER_CODE ( GDT_FLAGS_UPPER_G | GDT_FLAGS_UPPER_L )
#define GDT_FLAGS_UPPER_DATA ( GDT_FLAGS_UPPER_G | GDT_FLAGS_UPPER_L )
#define GDT_FLAGS_UPPER_TSS ( GDT_FLAGS_UPPER_G )

#define IDT_TYPE_INTERRUPT      0x0E
#define IDT_TYPE_TRAP           0x0F
#define IDT_FLAGS_DPL0          0x00
#define IDT_FLAGS_DPL1          0x20
#define IDT_FLAGS_DPL2          0x40
#define IDT_FLAGS_DPL3          0x60
#define IDT_FLAGS_P             0x80
#define IDT_FLAGS_IST0          0
#define IDT_FLAGS_IST1          1

#define IDT_FLAGS_KERNEL        ( IDT_FLAGS_DPL0 | IDT_FLAGS_P )
#define IDT_FLAGS_USER          ( IDT_FLAGS_DPL3 | IDT_FLAGS_P )

#define IDT_MAXENTRYCOUNT       100
#define IDTR_STARTADDRESS       ( GDTR_STARTADDRESS + sizeof( GDTR ) + \
        GDT_TABLESIZE + TSS_SEGMENTSIZE )

#define IDT_STARTADDRESS        ( IDTR_STARTADDRESS + sizeof( IDTR ) )

#define IDT_TABLESIZE           ( IDT_MAXENTRYCOUNT * sizeof( IDTENTRY ) )

#define IST_STARTADDRESS        0x700000

#define IST_SIZE                0x100000

#pragma pack( push, 1 )

typedef struct kGDTRStruct {
    uint16_t wLimit;
    uint64_t qwBaseAddress;
    uint16_t wPading;
    uint32_t dwPading;
} GDTR, IDTR;

typedef struct kGDTEntry8Struct {
    uint16_t wLowerLimit;
    uint16_t wLowerBaseAddress;
    uint8_t bUpperBaseAddress1;
    uint8_t bTypeAndLowerFlag;
    uint8_t bUpperLimitAndUpperFlag;
    uint8_t bUpperBaseAddress2;
} GDTENTRY8;

typedef struct kGDTEntry16Struct {
    uint16_t wLowerLimit;
    uint16_t wLowerBaseAddress;
    uint8_t bMiddleBaseAddress1;
    uint8_t bTypeAndLowerFlag;
    uint8_t bUpperLimitAndUpperFlag;
    uint8_t bMiddleBaseAddress2;
    uint32_t dwUpperBaseAddress;
    uint32_t dwReserved;
} GDTENTRY16;

typedef struct kTSSDataStruct {
    uint32_t dwReserved1;
    uint64_t qwRsp[ 3 ];
    uint64_t qwReserved2;
    uint64_t qwIST[ 7 ];
    uint64_t qwReserved3;
    uint16_t wReserved;
    uint16_t wIOMapBaseAddress;
} TSSSEGMENT;

typedef struct kIDTEntryStruct {
    uint16_t wLowerBaseAddress;
    uint16_t wSegmentSelector;
    uint8_t bIST;
    uint8_t bTypeAndFlags;
    uint16_t wMiddleBaseAddress;
    uint32_t dwUpperBaseAddress;
    uint32_t dwReserved;
} IDTENTRY;

#pragma pack(pop)

void initialize_gdt_tss( void );
void initialize_idt_tables(void);

#endif
