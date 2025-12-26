#include "uart/uart.h"
#include "syscon.h"
#include "common.h"
#include "spinlock.h"

static spinlock_t print_lock;

#define ARCH "RISC-V"
#define MODE 'M'

void kmain(void) {
  uart_init();
	lock_init(&print_lock, "print_lock");

  kprintf("Hello %s World!\n", ARCH);
  kprintf("We are in %c-mode!\n", MODE);

	poweroff();
}
