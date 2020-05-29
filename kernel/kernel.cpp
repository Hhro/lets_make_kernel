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

extern "C" void kernel_main(void);
extern KeyboardDevice DKeyboard;

void kernel_main(void) {
  arch_init();
  terminal_initialize();

  // Collect CPU information
  cpu_info = CpuInfo();
  cpu_info.CollectCpuInfo();

  if (cpu_info.IsIntel()) {
    kPrintf("Powered by %s\n", cpu_info.cpu_vendor_id());
  }

  // Activate keyboard
  DKeyboard.Activate();
	shell_main();
	
	unreachable_error();
}
