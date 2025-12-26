#include "uart/uart.h"
#include "syscon.h"
#include "common.h"

#define ARCH "RISC-V"
#define MODE 'M'

void kmain(void) {
  uart_init();

  kprintf("Hello %s World!\n", ARCH);
  kprintf("We are in %c-mode!\n", MODE);

	poweroff();
}
