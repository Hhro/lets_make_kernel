#include <kapi/multiboot2.h>
#include <kapi/multibootinfo.hpp>

MultibootInfo::MultibootInfo(multiboot_uint32_t multiboot2_magic_value, void *multiboot2_info_struct) {
    this->multiboot2_magic_value = multiboot2_magic_value;
    this->multiboot2_info_struct = multiboot2_info_struct;

    if (multiboot2_magic_value == MULTIBOOT2_BOOTLOADER_MAGIC) {
        this->avail = true;
        this->total_size = *(multiboot_uint32_t *) this->multiboot2_info_struct;
        void *cu = (this->multiboot2_info_struct + 8);
        void *end = (this->multiboot2_info_struct + total_size);
        while (cu < end) {
            struct multiboot_tag *tag_view = (struct multiboot_tag *) cu;
            if (tag_view->type == MULTIBOOT_TAG_TYPE_BASIC_MEMINFO)
                this->basic_meminfo = (struct multiboot_tag_basic_meminfo *) cu;
            else if (tag_view->type == MULTIBOOT_TAG_TYPE_BOOTDEV)
                this->bootdev = (struct multiboot_tag_bootdev *) cu;
            else if (tag_view->type == MULTIBOOT_TAG_TYPE_CMDLINE)
                this->cmdline = (struct multiboot_tag_string *) cu;
            else if (tag_view->type == MULTIBOOT_TAG_TYPE_MODULE)
                this->module = (struct multiboot_tag_module *) cu;
            else if (tag_view->type == MULTIBOOT_TAG_TYPE_ELF_SECTIONS)
                this->elf_sections = (struct multiboot_tag_elf_sections *) cu;
            else if (tag_view->type == MULTIBOOT_TAG_TYPE_MMAP)
                this->mmap = (struct multiboot_tag_mmap *) cu;
            else if (tag_view->type == MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME)
                this->boot_loader_name = (struct multiboot_tag_string *) cu;
            else if (tag_view->type == MULTIBOOT_TAG_TYPE_APM)
                this->apm = (struct multiboot_tag_apm *) cu;
            else if (tag_view->type == MULTIBOOT_TAG_TYPE_END)
                break;

            cu = cu + (tag_view->size) + ((tag_view->size % MULTIBOOT_TAG_ALIGN) ? (MULTIBOOT_TAG_ALIGN - tag_view->size % MULTIBOOT_TAG_ALIGN) : 0);
        }
    }
}

struct multiboot_tag_basic_meminfo *MultibootInfo::get_basic_meminfo() {
    return this->basic_meminfo;
}
struct multiboot_tag_bootdev *MultibootInfo::get_bootdev() {
    return this->bootdev;
}
struct multiboot_tag_string *MultibootInfo::get_cmdline() {
    return this->cmdline;
}
struct multiboot_tag_module *MultibootInfo::get_module() {
    return this->module;
}
struct multiboot_tag_elf_sections *MultibootInfo::get_elf_sections() {
    return this->elf_sections;
}
struct multiboot_tag_mmap *MultibootInfo::get_mmap() {
    return this->mmap;
}
struct multiboot_tag_string *MultibootInfo::get_boot_loader_name() {
    return this->boot_loader_name;
}
struct multiboot_tag_apm *MultibootInfo::get_apm() {
    return this->apm;
}

// Global variable

MultibootInfo multibootinfo;