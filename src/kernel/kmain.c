#include "uart.h"
#include "syscon.h"
#include "common.h"

#define ARCH "RISC-V"
#define MODE 'M'

void kmain(void) {
  uart_init(UART_ADDR);

  kprintf("Hello %s World!\n", ARCH);
  kprintf("We are in %c-mode!\n", MODE);

	poweroff();
}
