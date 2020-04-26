#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

#include <stdint.h>

extern "C" {
    void outport_byte(uint8_t prot, uint8_t data);
    uint8_t inport_byte(uint8_t prot);
}


#endif