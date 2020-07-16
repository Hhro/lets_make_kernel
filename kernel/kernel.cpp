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

#ifdef TEST
#include <test.hpp>
#endif

extern "C" void kernel_main(void);
extern KeyboardDevice DKeyboard;

void kernel_main(void) {
  arch_init();
  terminal_initialize();

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
