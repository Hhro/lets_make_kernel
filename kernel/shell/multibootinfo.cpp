#include <fried/stdio.h>
#include <kapi/multiboot2.h>
#include <kapi/multibootinfo.hpp>

void dump_multibootinfo(char *args) {
    auto *meminfo = multibootinfo.get_basic_meminfo();
    if (meminfo != nullptr)
        printf("mem_lower = %uKB, mem_upper: %uKB\n", 
            meminfo->mem_lower,
            meminfo->mem_upper);
    auto *bootdev = multibootinfo.get_bootdev();
    if (bootdev != nullptr) {
        printf("Boot device 0x%x,%u,%u\n",
            bootdev->biosdev,
            bootdev->slice,
            bootdev->part);
    }
    auto *cmdline = multibootinfo.get_cmdline();
    if (cmdline != nullptr) {
        printf("cmdline = %s\n", 
            cmdline->string);
    }
    auto *module = multibootinfo.get_module();
    if (module != nullptr) {
        printf("Module at 0x%x-0x%x. Command line %s\n",
            module->mod_start,
            module->mod_end,
            module->cmdline);
    }
    auto *mmap = multibootinfo.get_mmap();
    if (mmap != nullptr) {
        printf ("mmap\n");
      
        for (multiboot_memory_map_t *entry = mmap->entries; entry < (((void *)mmap) + mmap->size); entry = (multiboot_memory_map_t *) (((void *) entry) + mmap->entry_size))
            printf (" base_addr = %p,"
                    " length = %llx, type = 0x%x\n",
                    entry->addr, entry->len,
                    (unsigned) entry->type);
    }

}