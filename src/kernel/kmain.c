#include "uart/uart.h"
#include "syscon.h"
#include "common.h"
#include "spinlock.h"

#define ARCH "RISC-V"
#define MODE 'M'

static spinlock_t print_lock;
volatile int initialized = 0;

void kmain(void) {
	if (get_cpuid() == 0) {
  	uart_init();
		initialized = 1;
		__sync_synchronize();
	}
	else {
		// Wait until the primary core has initialized
		while (initialized == 0) {
			// Busy-wait
		}
		__sync_synchronize();
	}


	// Synchronize all cores before printing
  kprintf("Hello %s World!\n", ARCH);
  kprintf("We are in %c-mode!\n", MODE);
	poweroff();
}
