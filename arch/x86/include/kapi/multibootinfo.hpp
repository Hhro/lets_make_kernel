#ifndef KAPI_X86_MULTIBOOTINFO_H
#define KAPI_X86_MULTIBOOTINFO_H

#include <kapi/multiboot2.h>

#define GENERATE_GETTER_DECLARATION(tag_type) struct multiboot_tag_ ## tag_type* get_ ## tag_type()
class MultibootInfo {
private:
    bool avail = false;
    multiboot_uint32_t multiboot2_magic_value;
    void *multiboot2_info_struct;
    multiboot_uint32_t total_size;
    struct multiboot_tag_basic_meminfo *basic_meminfo = nullptr;
    struct multiboot_tag_bootdev *bootdev = nullptr;
    struct multiboot_tag_string *cmdline = nullptr;
    struct multiboot_tag_module *module = nullptr;
    struct multiboot_tag_elf_sections *elf_sections = nullptr;
    struct multiboot_tag_mmap *mmap = nullptr;
    struct multiboot_tag_string *boot_loader_name = nullptr;
    struct multiboot_tag_apm *apm = nullptr;
  public:
    MultibootInfo() {};
    MultibootInfo(multiboot_uint32_t multiboot2_magic_value, void *multiboot2_info_struct);
    struct multiboot_tag_basic_meminfo *get_basic_meminfo();
    struct multiboot_tag_bootdev *get_bootdev();
    struct multiboot_tag_string *get_cmdline();
    struct multiboot_tag_module *get_module();
    struct multiboot_tag_elf_sections *get_elf_sections();
    struct multiboot_tag_mmap *get_mmap();
    struct multiboot_tag_string *get_boot_loader_name();
    struct multiboot_tag_apm *get_apm();
};

#undef GENERATE_GETTER_DECLARATION

extern MultibootInfo multibootinfo;

#endif