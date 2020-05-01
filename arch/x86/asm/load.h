#ifndef LOAD_H
#define LOAD_H

#include <stdint.h>
#include "../descriptors/gdt.h"

extern "C" {
    void load_gdtr(GDTR * gdtr);
    void load_tr(uint16_t tr);
    void load_idtr(IDTR * tr);
}
#endif