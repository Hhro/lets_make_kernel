#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <vga.h>

#include <common.hpp>
#include <error.hpp>
#include <kapi/cpuinfo.hpp>
#include <keyboard.hpp>
#include <fried/stdio.h>
#include <shell.hpp>
#include <uapi/string.hpp>
#include <buddy_alloc.hpp>
#include <kapi/multibootinfo.hpp>

#ifdef TEST
#include <test.hpp>
#endif

extern "C" void kernel_main(unsigned int multiboot2_magic_value, void *multiboot2_info_struct);
extern KeyboardDevice DKeyboard;

void kernel_main(unsigned int multiboot2_magic_value, void *multiboot2_info_struct) {
  arch_init();
  terminal_initialize();

  // Collect multiboot2 boot info. 
  multibootinfo = MultibootInfo(multiboot2_magic_value, multiboot2_info_struct);

  // Collect CPU information
  cpu_info = CpuInfo();
  cpu_info.CollectCpuInfo();

  if (cpu_info.IsIntel()) {
    printf("Powered by %s\n", cpu_info.cpu_vendor_id());
  }

  // Activate keyboard
  DKeyboard.Activate();
  BAllocator.init();

  // Main

  #ifdef TEST
  test_main();
  puts("TEST");
  #endif
  
  shell_main();

	unreachable_error();
}
