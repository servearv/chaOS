/* Handles console input and output to console */

#include <stdarg.h>

#include "uart/uart.h"




#define BACKSPACE 0x100
#define C(x) (x - '@')  // Control-x
												

void console_init() {
    uart_init();
}

void console_putc(int c) {
		if (c == BACKSPACE) {
				uart_put('\b');
				uart_put(' ');
				uart_put('\b');
		} else {
				uart_putc(c);
		}
}

int console_write(void) {
		// Move data from kernel buffer to UART
		char buf[16];
		int len = uart_read(buf, sizeof(buf));
		for (int i = 0; i < len; i++) {
				console_putc(buf[i]);
		}
		return len;
}

void console_read(void) {
		// Move data from UART to kernel buffer
		char buf[16];
		int len = uart_read(buf, sizeof(buf));
		for (int i = 0; i < len; i++) {
				// Here you would typically store the character in a kernel buffer
				// For demonstration, we just echo it back
				console_putc(buf[i]);
		}
