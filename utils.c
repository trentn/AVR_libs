#include <avr/io.h>

void clear_clkpr(void) {
	CLKPR = 0x80;
	CLKPR = 0;
}
